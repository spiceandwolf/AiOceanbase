/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#define USING_LOG_PREFIX OBLOG

#include "ob_log_instance.h"

#include "lib/oblog/ob_log_module.h"        // LOG_ERROR
#include "lib/file/file_directory_utils.h"  // FileDirectoryUtils
#include "share/ob_version.h"               // build_version
#include "share/ob_tenant_mgr.h"            // ObTenantManager
#include "share/system_variable/ob_system_variable.h" // ObPreProcessSysVars
#include "share/ob_time_utility2.h"         // ObTimeUtility2
#include "sql/ob_sql_init.h"                // init_sql_factories
#include "observer/ob_server_struct.h"      // GCTX
#include "observer/omt/ob_tenant_timezone_mgr.h"  // OTTZ_MGR
#include "common/ob_clock_generator.h"

#include "ob_log_common.h"
#include "ob_log_config.h"                // ObLogConfig
#include "ob_log_utils.h"                 // ob_log_malloc
#include "ob_log_meta_manager.h"          // ObLogMetaManager
#include "ob_log_sql_server_provider.h"   // ObLogSQLServerProvider
#include "ob_log_schema_getter.h"         // ObLogSchemaGetter
#include "ob_log_timezone_info_getter.h"  // ObLogTimeZoneInfoGetter
#include "ob_log_committer.h"             // ObLogCommitter
#include "ob_log_formatter.h"             // ObLogFormatter
#include "ob_log_storager.h"              // ObLogStorager
#include "ob_log_data_processor.h"        // ObLogDataProcessor
#include "ob_log_sequencer1.h"            // ObLogSequencer
#include "ob_log_part_trans_parser.h"     // ObLogPartTransParser
#include "ob_log_dml_parser.h"            // ObLogDmlParser
#include "ob_log_ddl_parser.h"            // ObLogDdlParser
#include "ob_log_fetcher.h"               // ObLogFetcher
#include "ob_log_part_trans_task.h"       // PartTransTask
#include "ob_log_table_matcher.h"         // ObLogTableMatcher
#include "ob_log_trans_ctx_mgr.h"         // ObLogTransCtxMgr
#include "ob_log_trans_ctx.h"             // TransCtx
#include "ob_log_resource_collector.h"    // ObLogResourceCollector
#include "ob_log_binlog_record_pool.h"    // ObLogBRPool
#include "ob_log_ddl_handler.h"           // ObLogDDLHandler
#include "ob_log_start_schema_matcher.h"  // ObLogStartSchemaMatcher
#include "ob_log_tenant_mgr.h"            // IObLogTenantMgr
#include "ob_log_rocksdb_store_service.h" // RocksDbStoreService

#include "ob_log_trace_id.h"

#define INIT(v, type, args...) \
    do {\
      if (OB_SUCC(ret)) { \
        type *tmp_var = NULL; \
        if (OB_ISNULL(tmp_var = new(std::nothrow) type())) { \
          _LOG_ERROR("construct %s fail", #type); \
          ret = OB_ALLOCATE_MEMORY_FAILED; \
        } else if (OB_FAIL(tmp_var->init(args))) { \
          _LOG_ERROR("init %s fail, ret=%d", #type, ret); \
          delete tmp_var; \
          tmp_var = NULL; \
        } else { \
          v = tmp_var; \
          _LOG_INFO("init component \'%s\' succ", #type); \
        } \
      } \
    } while (0)

#define DESTROY(v, type) \
    do {\
      if (NULL != v) { \
        type *var = static_cast<type *>(v); \
        (void)var->destroy(); \
        delete v; \
        v = NULL; \
      } \
    } while (0)

using namespace oceanbase::common;

namespace oceanbase
{
using namespace share;
namespace liboblog
{

ObLogInstance *ObLogInstance::instance_ = NULL;

ObLogInstance *ObLogInstance::get_instance()
{
  if (NULL == instance_) {
    instance_ = new(std::nothrow) ObLogInstance();
  }

  return instance_;
}

// Here is the chicken and egg problem, assuming that ObLogInstance has already been created when get_ref_instance() is called
ObLogInstance &ObLogInstance::get_ref_instance()
{
  if (NULL == instance_) {
    LOG_ERROR("ObLogInstance is NULL", K(instance_));
  }
  return *instance_;
}

void ObLogInstance::destroy_instance()
{
  if (NULL != instance_) {
    _LOG_INFO("ObLogInstance %p destroy", instance_);
    delete instance_;
    instance_ = NULL;
  }
}

ObLogInstance::ObLogInstance() :
    inited_(false),
    oblog_major_(0),
    oblog_minor_(0),
    oblog_patch_(0),
    timer_tid_(0),
    sql_tid_(0),
    flow_control_tid_(0),
    err_cb_(NULL),
    global_errno_(0),
    handle_error_flag_(0),
    disable_redirect_log_(false),
    log_clean_cycle_time_us_(0),
    output_dml_br_count_(0),
    output_ddl_br_count_(0),
    stop_flag_(true),
    last_heartbeat_timestamp_micro_sec_(0),
    is_assign_log_dir_valid_(false),
    br_index_in_trans_(0),
    part_trans_task_count_(0),
    trans_task_pool_alloc_(),
    start_tstamp_(0),
    is_schema_split_mode_(false),
    drc_message_factory_binlog_record_type_(),
    working_mode_(WorkingMode::UNKNOWN_MODE),
    mysql_proxy_(),
    timezone_info_getter_(NULL),
    hbase_util_(),
    obj2str_helper_(),
    br_queue_(),
    trans_task_pool_(),
    log_entry_task_pool_(NULL),
    store_service_(NULL),
    br_pool_(NULL),
    trans_ctx_mgr_(NULL),
    meta_manager_(NULL),
    resource_collector_(NULL),
    server_provider_(NULL),
    schema_getter_(NULL),
    tb_matcher_(NULL),
    ss_matcher_(NULL),
    systable_helper_(NULL),
    committer_(NULL),
    storager_(NULL),
    data_processor_(NULL),
    formatter_(NULL),
    sequencer_(NULL),
    part_trans_parser_(NULL),
    dml_parser_(NULL),
    ddl_parser_(NULL),
    ddl_handler_(NULL),
    fetcher_(NULL),
    trans_stat_mgr_(NULL),
    tenant_mgr_(NULL)
{
  MEMSET(assign_log_dir_, 0, sizeof(assign_log_dir_));
  MEMSET(ob_trace_id_str_, 0, sizeof(ob_trace_id_str_));
}

ObLogInstance::~ObLogInstance()
{
  destroy();

  LOG_INFO("====================liboblog end====================");
}

int ObLogInstance::init(const char *config_file,
      const uint64_t start_tstamp_sec,
      ERROR_CALLBACK err_cb /* = NULL */)
{
  const int64_t start_tstamp_usec = start_tstamp_sec * _SEC_;
  return init_with_start_tstamp_usec(config_file, start_tstamp_usec, err_cb);
}

int ObLogInstance::init_with_start_tstamp_usec(const char *config_file,
      const uint64_t start_tstamp_usec,
      ERROR_CALLBACK err_cb /* = NULL */)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(inited_)) {
    LOG_ERROR("instance has been initialized");
    ret = OB_INIT_TWICE;
  } else if (OB_ISNULL(config_file)) {
    LOG_ERROR("invalid arguments", K(config_file));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(init_logger_())) { // First initialize the logging module
    LOG_ERROR("init_logger_ fail", KR(ret));
  } else if (OB_FAIL(TCONF.init())) {
    LOG_ERROR("config init fail", KR(ret));
  } else if (OB_FAIL(TCONF.load_from_file(config_file))) {
    LOG_ERROR("load config from file fail", KR(ret), K(config_file));
  } else if (OB_FAIL(init_common_(start_tstamp_usec, err_cb))) {
    LOG_ERROR("init_common_ fail", KR(ret), K(start_tstamp_usec), K(err_cb));
  } else {
    inited_ = true;
  }

  return ret;
}

int ObLogInstance::init(const std::map<std::string, std::string>& configs,
    const uint64_t start_tstamp_sec,
    ERROR_CALLBACK err_cb /* = NULL */ )
{
  int ret = OB_SUCCESS;
  const int64_t start_tstamp_usec = start_tstamp_sec * _SEC_;

  if (OB_FAIL(init_with_start_tstamp_usec(configs, start_tstamp_usec, err_cb))) {
    LOG_ERROR("init fail", KR(ret), K(start_tstamp_usec));
  }

  return ret;
}

int ObLogInstance::init_with_start_tstamp_usec(const std::map<std::string, std::string>& configs,
    const uint64_t start_tstamp_usec,
    ERROR_CALLBACK err_cb /* = NULL */ )
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(inited_)) {
    LOG_ERROR("instance has been initialized");
    ret = OB_INIT_TWICE;
  } else if (OB_FAIL(init_logger_())) { // First initialize the logging module
    LOG_ERROR("init_logger_ fail", KR(ret));
  } else if (OB_FAIL(TCONF.init())) {
    LOG_ERROR("config init fail", KR(ret));
  } else if (OB_FAIL(TCONF.load_from_map(configs))) {
    LOG_ERROR("load config from map fail", KR(ret));
  } else if (OB_FAIL(init_common_(start_tstamp_usec, err_cb))) {
    // handle error
  } else {
    inited_ = true;
  }

  return ret;
}

int ObLogInstance::set_assign_log_dir(const char *log_dir, const int64_t log_dir_len)
{
  int ret = OB_SUCCESS;

  if (OB_ISNULL(log_dir) || OB_UNLIKELY(log_dir_len > OB_MAX_FILE_NAME_LENGTH)) {
    ret = OB_INVALID_ARGUMENT;
  } else {
    (void)snprintf(assign_log_dir_, sizeof(assign_log_dir_), "%.*s", static_cast<int>(log_dir_len), log_dir);
    is_assign_log_dir_valid_ = true;
  }

  return ret;
}

int ObLogInstance::set_data_start_ddl_schema_version(const uint64_t tenant_id,
    const int64_t data_start_ddl_schema_version)
{
  int ret = OB_SUCCESS;
  ObLogTenant *tenant = NULL;
  ObLogTenantGuard guard;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (! stop_flag_) {
    LOG_ERROR("ObLogInstance have already started, can not set data start ddl schema version",
        K(stop_flag_), K(tenant_id), K(data_start_ddl_schema_version));
    ret = OB_NOT_SUPPORTED;
  } else if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id)
        || OB_UNLIKELY(OB_INVALID_TIMESTAMP == data_start_ddl_schema_version)) {
    LOG_ERROR("invalid argument", K(tenant_id), K(data_start_ddl_schema_version));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(get_tenant_guard(tenant_id, guard))) {
    if (OB_ENTRY_NOT_EXIST != ret) {
      LOG_ERROR("get_tenant_guard fail", KR(ret), K(tenant_id));
    }
  } else if (OB_ISNULL(tenant = guard.get_tenant())) {
    LOG_ERROR("tenant is null", K(tenant_id), K(tenant));
    ret = OB_ERR_UNEXPECTED;
  } else {
    tenant->update_global_data_schema_version(data_start_ddl_schema_version);
  }

  return ret;
}

int ObLogInstance::get_start_schema_version(const uint64_t tenant_id,
    const bool is_create_tenant_when_backup,
    int64_t &start_schema_version)
{
  int ret = OB_SUCCESS;
  ObLogTenant *tenant = NULL;
  ObLogTenantGuard guard;
  start_schema_version = OB_INVALID_TIMESTAMP;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (! is_create_tenant_when_backup && ! stop_flag_) {
    LOG_ERROR("ObLogInstance have already started, can not get start schema version",
        K(stop_flag_), K(tenant_id), K(is_create_tenant_when_backup), K(start_schema_version));
    ret = OB_NOT_SUPPORTED;
  } else if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id)) {
    LOG_ERROR("invalid argument", K(tenant_id));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(get_tenant_guard(tenant_id, guard))) {
    if (OB_ENTRY_NOT_EXIST != ret) {
      LOG_ERROR("get_tenant_guard fail", KR(ret), K(tenant_id));
    }
  } else if (OB_ISNULL(tenant = guard.get_tenant())) {
    LOG_ERROR("tenant is null", K(tenant_id), K(tenant));
    ret = OB_ERR_UNEXPECTED;
  } else {
    start_schema_version = tenant->get_start_schema_version();
  }

  return ret;
}

int ObLogInstance::set_start_global_trans_version(const int64_t start_global_trans_version)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_UNLIKELY(OB_INVALID_TIMESTAMP == start_global_trans_version)) {
    LOG_ERROR("invalid argument", K(start_global_trans_version));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_ISNULL(fetcher_)) {
    LOG_ERROR("fetcher_ is null", K(fetcher_));
    ret = OB_ERR_UNEXPECTED;
  } else if (OB_FAIL(fetcher_->set_start_global_trans_version(start_global_trans_version))) {
    LOG_ERROR("fetcher_ set_start_global_trans_version fail", KR(ret), K(start_global_trans_version));
  } else {
    LOG_INFO("set_start_global_trans_version succ", K(start_global_trans_version));
  }

  return ret;
}

int ObLogInstance::init_logger_()
{
  int ret = OB_SUCCESS;
  char log_dir[OB_MAX_FILE_NAME_LENGTH];
  char log_file[OB_MAX_FILE_NAME_LENGTH];
  char stderr_log_file[OB_MAX_FILE_NAME_LENGTH];

  if (is_assign_log_dir_valid_) {
    (void)snprintf(log_dir, sizeof(log_dir), "%s", assign_log_dir_);
    (void)snprintf(log_file, sizeof(log_file), "%s%s", assign_log_dir_, DEFAULT_LOG_FILE_NAME);
    (void)snprintf(stderr_log_file, sizeof(stderr_log_file), "%s%s", assign_log_dir_, DEFAULT_STDERR_LOG_FILE_NAME);
  } else {
    (void)snprintf(log_dir, sizeof(log_dir), "%s", DEFAULT_LOG_DIR);
    (void)snprintf(log_file, sizeof(log_file), "%s", DEFAULT_LOG_FILE);
    (void)snprintf(stderr_log_file, sizeof(stderr_log_file), "%s", DEFAULT_STDERR_LOG_FILE);
  }

  if (OB_FAIL(common::FileDirectoryUtils::create_full_path(log_dir))) {
    LOG_ERROR("FileDirectoryUtils create_full_path fail", KR(ret), K(log_dir));
  } else {
    easy_log_level = EASY_LOG_INFO;
    OB_LOGGER.set_max_file_size(MAX_LOG_FILE_SIZE);
    OB_LOGGER.set_file_name(log_file, disable_redirect_log_, false);
    OB_LOGGER.set_log_level("INFO");
    OB_LOGGER.disable_thread_log_level();

    if (! disable_redirect_log_) {
      // Open the stderr log file
      // and redirects stderr to that log file
      int32_t stderr_log_fd = open(stderr_log_file, O_RDWR | O_CREAT | O_APPEND | O_LARGEFILE, 0644);
      if (OB_UNLIKELY(stderr_log_fd <= 0)) {
        LOG_ERROR("failed to open stderror log, which fd should be greater than 0", K(stderr_log_fd));
      } else {
        dup2(stderr_log_fd, 2);
        close(stderr_log_fd);
        stderr_log_fd = -1;
      }
    }

    _LOG_INFO("====================libobcdc start====================");
    _LOG_INFO("libobcdc CE %s %s", PACKAGE_VERSION, RELEASEID);
    _LOG_INFO("BUILD_VERSION: %s", build_version());
    _LOG_INFO("BUILD_TIME: %s %s", build_date(), build_time());
    _LOG_INFO("BUILD_FLAGS: %s", build_flags());
    _LOG_INFO("Copyright (c) 2022 Ant Group Co., Ltd.");
    _LOG_INFO("======================================================");
    _LOG_INFO("\n");
  }

  return ret;
}

#define MPRINT(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)

void ObLogInstance::print_version()
{
  MPRINT("libobcdc CE %s %s", PACKAGE_VERSION, RELEASEID);
  MPRINT("REVISION: %s", build_version());
  MPRINT("BUILD_TIME: %s %s", build_date(), build_time());
  MPRINT("BUILD_FLAGS: %s\n", build_flags());
  MPRINT("Copyright (c) 2022 Ant Group Co., Ltd.");
  MPRINT();
}

// ObKVGlobalCache rely on ObTenantManager
int ObLogInstance::init_global_tenant_manager_()
{
  int ret = OB_SUCCESS;
  static const int64_t DEFAULT_TENANT_COUNT = 2;
  static const int64_t SCHEMA_CACHE_MEM_LIMIT_LOWER_BOUND = 0;
  static const int64_t SCHEMA_CACHE_MEM_LIMIT_UPPER_BOUND = 1L << 31L; // 2G
  ObTenantManager &tenant_manager = ObTenantManager::get_instance();
  const int64_t tenant_manager_memory_upper_limit = TCONF.tenant_manager_memory_upper_limit.get();

  if (OB_FAIL(tenant_manager.init(DEFAULT_TENANT_COUNT))) {
    LOG_ERROR("init tenant manager fail", KR(ret));
  }
  // The SYS tenant is used only for the Schema Cache module, and it allocates the memory that occupies the share of the SYS tenant
  else if (OB_FAIL(tenant_manager.add_tenant(OB_SYS_TENANT_ID))) {
    LOG_ERROR("add OB SYS tenant fail", KR(ret));
  } else if (OB_FAIL(tenant_manager.set_tenant_mem_limit(OB_SYS_TENANT_ID,
      SCHEMA_CACHE_MEM_LIMIT_LOWER_BOUND,
      SCHEMA_CACHE_MEM_LIMIT_UPPER_BOUND))) {
    LOG_ERROR("set_tenant_mem_limit fail for OB SYS tenant", KR(ret));
  } else if (OB_FAIL(tenant_manager.add_tenant(OB_SERVER_TENANT_ID))) {
    LOG_ERROR("add OB SERVER tenant fail", KR(ret));
  } else if (OB_FAIL(tenant_manager.set_tenant_mem_limit(OB_SERVER_TENANT_ID, 0, tenant_manager_memory_upper_limit))) {
    LOG_ERROR("set_tenant_mem_limit fail for OB SERVER tenant", KR(ret));
  } else {
    LOG_INFO("ObTenantManager add_tenant succ",
        "tenant_manager_memory_upper_limit", SIZE_TO_STR(tenant_manager_memory_upper_limit));
  }

  return ret;
}

int ObLogInstance::init_global_kvcache_()
{
  int ret = OB_SUCCESS;
  static const int64_t KV_CACHE_WASH_TIMER_INTERVAL_US = 60 * _SEC_;
  static const int64_t DEFAULT_BUCKET_NUM = 10000000L;
  static const int64_t DEFAULT_MAX_CACHE_SIZE = 1024L * 1024L * 1024L * 1024L;  //1T

  // init schema cache
  if (OB_FAIL(ObKVGlobalCache::get_instance().init(DEFAULT_BUCKET_NUM,
      DEFAULT_MAX_CACHE_SIZE,
      lib::ACHUNK_SIZE,
      KV_CACHE_WASH_TIMER_INTERVAL_US))) {
    LOG_ERROR("Fail to init ObKVGlobalCache", KR(ret));
  } else if (OB_FAIL(lib::ObResourceMgr::get_instance().set_cache_washer(ObKVGlobalCache::get_instance()))) {
    LOG_ERROR("Fail to set_cache_washer", KR(ret));
  } else {
    LOG_INFO("ObKVGlobalCache init succ", "max_cached_size", SIZE_TO_STR(DEFAULT_QUEUE_SIZE));
  }

  return ret;
}

// FIXME: when refreshing the schema, construct "generated column" schema depends on the default system variables, require initialization
// The specific function is: ObSchemaUtils::cascaded_generated_column()
//
// This situation is only temporary, the subsequent "generated column" logic will decouple the schema and the default system variables.
// Once decoupled, there is no need to initialize system variables here
// After decoupling, there is no need to initialize system variables here.
int ObLogInstance::init_sys_var_for_generate_column_schema_()
{
  int ret = OB_SUCCESS;
  ::oceanbase::sql::init_sql_factories();

  if (OB_FAIL(ObPreProcessSysVars::init_sys_var())){
    LOG_ERROR("PreProcessing init system variable failed", KR(ret));
  } else {
    // success
  }
  return ret;
}

#include "lib/alloc/alloc_struct.h"
int ObLogInstance::init_common_(uint64_t start_tstamp_usec, ERROR_CALLBACK err_cb)
{
  int ret = OB_SUCCESS;
  int64_t current_timestamp_usec = get_timestamp();

  if (start_tstamp_usec <= 0) {
    start_tstamp_usec =  current_timestamp_usec;
    _LOG_INFO("start liboblog from current timestamp: %ld", start_tstamp_usec);
  }

  if (OB_SUCC(ret)) {
    err_cb_ = err_cb;
    global_errno_ = 0;
    handle_error_flag_ = 0;
    start_tstamp_ = start_tstamp_usec;
    is_schema_split_mode_ = false;

    // set pid file
    write_pid_file_();

    // 1. set the initialization log level to ensure that the schema prints an INFO log at startup
    // 2. Change the schema to WARN after the startup is complete
    OB_LOGGER.set_mod_log_levels(TCONF.init_log_level.str());

    // 校验配置项是否满足期望
    if (OB_FAIL(TCONF.check_all())) {
      LOG_ERROR("check config fail", KR(ret));
    } else if (OB_FAIL(dump_config_())) {
      LOG_ERROR("dump_config_ fail", KR(ret));
    } else if (OB_FAIL(trans_task_pool_alloc_.init(TASK_POOL_ALLOCATOR_TOTAL_LIMIT,
        TASK_POOL_ALLOCATOR_HOLD_LIMIT,
        TASK_POOL_ALLOCATOR_PAGE_SIZE))) {
      LOG_ERROR("init fifo allocator fail", KR(ret));
    } else if (OB_FAIL(trans_task_pool_.init(&trans_task_pool_alloc_,
        TCONF.part_trans_task_prealloc_count,
        TCONF.part_trans_task_page_size,
        1 == TCONF.part_trans_task_dynamic_alloc,
        TCONF.part_trans_task_prealloc_page_count))) {
      LOG_ERROR("init task pool fail", KR(ret));
    } else if (OB_FAIL(hbase_util_.init())) {
      LOG_ERROR("init hbase_util_ fail", KR(ret));
    } else if (OB_FAIL(br_queue_.init(DEFAULT_QUEUE_SIZE))) {
      LOG_ERROR("init binlog record queue fail", KR(ret));
    } else if (OB_FAIL(init_global_tenant_manager_())) {
      LOG_ERROR("init_global_tenant_manager_ fail", KR(ret));
    } else if (OB_FAIL(init_global_kvcache_())) {
      LOG_ERROR("init_global_kvcache_ fail", KR(ret));
    } else if (OB_FAIL(init_sys_var_for_generate_column_schema_())) {
      LOG_ERROR("init_sys_var_for_generate_column_schema_ fail", KR(ret));
    } else if (OB_FAIL(init_components_(start_tstamp_usec))) {
      LOG_ERROR("init_components_ fail", KR(ret), K(start_tstamp_usec));
    } else {
      stop_flag_ = true;
      timer_tid_ = 0;
      sql_tid_ = 0;
      flow_control_tid_ = 0;
      output_dml_br_count_ = 0;
      output_ddl_br_count_ = 0;
      last_heartbeat_timestamp_micro_sec_ = start_tstamp_usec;
      log_clean_cycle_time_us_ = TCONF.log_clean_cycle_time_in_hours * _HOUR_;
      part_trans_task_count_ = 0;
    }
  }

  if (OB_SUCC(ret)) {
    LOG_INFO("init liboblog succ", K_(is_schema_split_mode), K_(start_tstamp),
        "start_tstamp", TS_TO_STR(start_tstamp_),
        "working_mode", print_working_mode(working_mode_),
        K(err_cb));
  }

  if (OB_SUCC(ret)) {
    // After startup, set the log level to prevent schema from printing INFO logs
    OB_LOGGER.set_mod_log_levels(TCONF.log_level.str());
  }

  return ret;
}

int ObLogInstance::dump_config_()
{
  int ret = OB_SUCCESS;
  const char *config_fpath = TCONF.config_fpath.str();

  // dump config to log
  TCONF.print();

  // Create the corresponding directory
  char *p = strrchr(const_cast<char*>(config_fpath), '/');
  if (NULL != p) {
    char dir_buffer[OB_MAX_FILE_NAME_LENGTH];
    snprintf(dir_buffer, OB_MAX_FILE_NAME_LENGTH, "%.*s", (int)(p - config_fpath), config_fpath);
    common::FileDirectoryUtils::create_full_path(dir_buffer);
  }

  if (OB_SUCC(ret)) {
    // dump config to file
    if (OB_FAIL(TCONF.dump2file(config_fpath))) {
      LOG_ERROR("config dump2file fail", KR(ret), K(config_fpath));
    } else {
      LOG_INFO("dump config to file succ", K(config_fpath));
    }
  }

  return ret;
}

int32_t ObLogInstance::get_pid_()
{
  return static_cast<int32_t>(getpid());
}

int ObLogInstance::init_self_addr_()
{
  int ret = OB_SUCCESS;
  static const int64_t BUF_SIZE = 128;
  char BUFFER[BUF_SIZE];
  int32_t self_pid = get_pid_();
  ObString local_ip(sizeof(BUFFER), 0, BUFFER);

  if (OB_FAIL(get_local_ip(local_ip))) {
    LOG_ERROR("get_local_ip fail", KR(ret), K(local_ip));
  } else if (!get_self_addr().set_ip_addr(local_ip, self_pid)) {
    LOG_ERROR("self addr set ip addr error", K(local_ip), K(self_pid));
  } else {
    // succ
  }

  return ret;
}

int ObLogInstance::init_schema_split_mode_(const int64_t sys_schema_version)
{
  int ret = OB_SUCCESS;
  bool bool_ret = false;
  int64_t split_schema_version = 0;
  int64_t timeout = GET_SCHEMA_TIMEOUT_ON_START_UP;

  if (OB_ISNULL(schema_getter_)) {
    ret = OB_ERR_UNEXPECTED;
  }
  // After determining the starting schema version of the sys tenant, determine the split schema version
  // Note: this order cannot be changed, otherwise liboblog will not see the dynamic change of split schema version
  else if (OB_FAIL(schema_getter_->load_split_schema_version(split_schema_version, timeout))) {
    LOG_ERROR("load_split_schema_version fail", KR(ret), K(timeout));
  } else {
    // 1. split_schema_version is an invalid value, which means it must be a non-split schema
    // 2. split_schema_version is a valid value, which determines whether the cluster is in split mode by comparing the sys tenant schema version
    // 3. split_schema_version is 0, which means the cluster is started in schema split mode, so it must be split mode
    if (split_schema_version < 0) {
      bool_ret = false;
    } else if (0 == split_schema_version) {
      bool_ret = true;
    } else if (sys_schema_version < split_schema_version) {
      bool_ret = false;
    } else {
      bool_ret = true;
    }

    ATOMIC_STORE(&is_schema_split_mode_, bool_ret);
  }

  LOG_INFO("init schema split mode", KR(ret), K_(is_schema_split_mode), K(split_schema_version),
      K(sys_schema_version));
  return ret;
}

// init schema module
int ObLogInstance::init_schema_(const int64_t start_tstamp_us, int64_t &sys_start_schema_version)
{
  int ret = OB_SUCCESS;
  const uint64_t sys_tenant_id = OB_SYS_TENANT_ID;
  ObLogSchemaGuard sys_schema_guard;

  INIT(schema_getter_, ObLogSchemaGetter, mysql_proxy_.get_ob_mysql_proxy(),
      &(TCONF.get_common_config()), TCONF.cached_schema_version_count,
      TCONF.history_schema_version_count);

  if (OB_SUCC(ret)) {
    // Get the SYS tenant startup schema version
    // Note: SYS tenants do not need to handle tenant deletion scenarios
    if (OB_FAIL(schema_getter_->get_schema_version_by_timestamp(sys_tenant_id, start_tstamp_us,
        sys_start_schema_version, GET_SCHEMA_TIMEOUT_ON_START_UP))) {
      LOG_ERROR("get_schema_version_by_timestamp fail", KR(ret), K(sys_tenant_id), K(start_tstamp_us));
    }
    // init schema_split_mode
    else if (OB_FAIL(init_schema_split_mode_(sys_start_schema_version))) {
      LOG_ERROR("init schema split mode fail", KR(ret), K(sys_start_schema_version));
    }
  }
  return ret;
}

int ObLogInstance::init_components_(const uint64_t start_tstamp_usec)
{
  int ret = OB_SUCCESS;
  IObLogErrHandler *err_handler = this;
  int64_t start_seq = DEFAULT_START_SEQUENCE_NUM;
  const char *config_url = NULL;
  bool skip_dirty_data = (TCONF.skip_dirty_data != 0);
  bool skip_reversed_schema_verison = (TCONF.skip_reversed_schema_verison != 0);
  bool enable_hbase_mode = (TCONF.enable_hbase_mode != 0);
  bool enable_backup_mode = (TCONF.enable_backup_mode != 0);
  bool skip_hbase_mode_put_column_count_not_consistency = (TCONF.skip_hbase_mode_put_column_count_not_consistency != 0);
  bool enable_convert_timestamp_to_unix_timestamp = (TCONF.enable_convert_timestamp_to_unix_timestamp != 0);
  bool enable_output_hidden_primary_key = (TCONF.enable_output_hidden_primary_key != 0);
  bool enable_oracle_mode_match_case_sensitive = (TCONF.enable_oracle_mode_match_case_sensitive != 0);
  const char *rs_list = TCONF.rootserver_list.str();
  const char *cluster_user = TCONF.cluster_user.str();
  const char *cluster_password = TCONF.cluster_password.str();
  const char *cluster_db_name = TCONF.cluster_db_name.str();
  const char *tb_white_list = TCONF.tb_white_list.str();
  const char *tb_black_list = TCONF.tb_black_list.str();
  const char *tg_white_list = TCONF.tablegroup_white_list.str();
  const char *tg_black_list = TCONF.tablegroup_black_list.str();
  int64_t max_cached_trans_ctx_count = MAX_CACHED_TRANS_CTX_COUNT;
  int64_t sql_conn_timeout_us = TCONF.mysql_connect_timeout_sec * _SEC_;
  int64_t sql_query_timeout_us = TCONF.mysql_query_timeout_sec * _SEC_;
  const char *ob_trace_id_ptr = TCONF.ob_trace_id.str();
  const char *drc_message_factory_binlog_record_type_str = TCONF.drc_message_factory_binlog_record_type.str();
  // The starting schema version of the SYS tenant
  int64_t sys_start_schema_version = OB_INVALID_VERSION;
  const char *data_start_schema_version = TCONF.data_start_schema_version.str();
  const char *store_service_path = TCONF.store_service_path.str();
  const char *working_mode_str = TCONF.working_mode.str();
  WorkingMode working_mode = get_working_mode(working_mode_str);
  const bool enable_ssl_client_authentication = (1 == TCONF.ssl_client_authentication);

  drc_message_factory_binlog_record_type_.assign(drc_message_factory_binlog_record_type_str,
      strlen(drc_message_factory_binlog_record_type_str));

  if (OB_UNLIKELY(! is_working_mode_valid(working_mode))) {
    LOG_ERROR("working_mode is not valid", K(working_mode_str), "working_mode", print_working_mode(working_mode));
    ret = OB_INVALID_CONFIG;
  } else {
    working_mode_ = working_mode;

    LOG_INFO("set working mode", K(working_mode_str), K(working_mode_), "working_mode", print_working_mode(working_mode_));
  }

  // init ObTraceId
  if (OB_FAIL(ret)) {
  } else if (TCONF.need_verify_ob_trace_id) {
    if (OB_FAIL(init_ob_trace_id_(ob_trace_id_ptr))) {
      LOG_ERROR("init_ob_trace_id_ fail", KR(ret), K(ob_trace_id_ptr));
    }
  }

  // init self addr
  if (OB_FAIL(ret)) {
  } else if (OB_FAIL(init_self_addr_())) {
    LOG_ERROR("init self addr error", KR(ret));
  }
  // format cluster_url
  else  if (OB_FAIL(TCONF.format_cluster_url())) {
    LOG_ERROR("format config url fail", KR(ret));
  } else {
    config_url = TCONF.cluster_url.str();
  }

  INIT(server_provider_, ObLogSQLServerProvider, config_url, rs_list);

  if (OB_SUCC(ret)) {
    if (OB_FAIL(ObMemoryDump::get_instance().init())) {
      LOG_ERROR("init memory dump fail", K(ret));
    }
  }

  // init ObLogMysqlProxy
  if (OB_SUCC(ret)) {
    if (OB_FAIL(mysql_proxy_.init(server_provider_, cluster_user, cluster_password,
            cluster_db_name, sql_conn_timeout_us, sql_query_timeout_us, enable_ssl_client_authentication))) {
      LOG_ERROR("mysql_proxy_ init fail", KR(ret), K(server_provider_),
          K(cluster_user), K(cluster_password), K(cluster_db_name), K(sql_conn_timeout_us),
          K(sql_query_timeout_us), K(enable_ssl_client_authentication));
    }
  }

  // init ObCompatModeGetter
  if (OB_SUCC(ret)) {
    if (OB_FAIL(share::ObCompatModeGetter::instance().init(&(mysql_proxy_.get_ob_mysql_proxy())))) {
      LOG_ERROR("compat_mode_getter init fail", KR(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(common::ObClockGenerator::init())) {
      LOG_ERROR("failed to init ob clock generator", KR(ret));
    }
  }

  INIT(log_entry_task_pool_, ObLogEntryTaskPool, TCONF.log_entry_task_prealloc_count);

  INIT(store_service_, RocksDbStoreService, store_service_path);

  INIT(br_pool_, ObLogBRPool, TCONF.binlog_record_prealloc_count);

  INIT(trans_ctx_mgr_, ObLogTransCtxMgr, max_cached_trans_ctx_count, TCONF.sort_trans_participants);

  INIT(systable_helper_, ObLogSysTableHelper, *server_provider_,
      TCONF.access_systable_helper_thread_num, TCONF.cluster_user,
      TCONF.cluster_password, TCONF.cluster_db_name);

  INIT(meta_manager_, ObLogMetaManager, &obj2str_helper_, enable_output_hidden_primary_key);

  INIT(resource_collector_, ObLogResourceCollector,
      TCONF.resource_collector_thread_num, TCONF.resource_collector_thread_num_for_br, DEFAULT_QUEUE_SIZE,
      br_pool_, trans_ctx_mgr_, meta_manager_, store_service_);

  // init oblog version，e.g. 2.2.1
  if (OB_SUCC(ret)) {
    if (OB_FAIL(init_oblog_version_components_())) {
      LOG_ERROR("init oblog version components fail", KR(ret));
    }
  }

  // Initialize ObClusterVersion before initializing the schema module
  if (OB_SUCC(ret)) {
    if (OB_FAIL(init_ob_cluster_version_())) {
      LOG_ERROR("init_ob_cluster_version_ fail", KR(ret));
    }
  }

  // check oblog version is greater than or equal to ob version
  if (OB_SUCC(ret)) {
    if (OB_FAIL(check_observer_version_valid_())) {
      LOG_ERROR("check_observer_version_valid_ fail", KR(ret));
    }
  }

  if (OB_SUCC(ret)) {
    // init GCTX
    init_global_context_();
  }

  INIT(tenant_mgr_, ObLogTenantMgr, enable_oracle_mode_match_case_sensitive);

  INIT(timezone_info_getter_, ObLogTimeZoneInfoGetter, TCONF.timezone.str(),
      mysql_proxy_.get_ob_mysql_proxy(), *systable_helper_, *tenant_mgr_, *err_handler);

  if (OB_SUCC(ret)) {
    // init interface for getting tenant timezone map
    OTTZ_MGR.init(ObLogTimeZoneInfoGetter::get_tenant_timezone_map);
  }

  // The initialization of schema depends on the initialization of timezone_info_getter_,
  // and the initialization of timezone_info_getter_ depends on the initialization of tenant_mgr_
  if (OB_SUCC(ret)) {
    // Initialize schema-related modules, split patterns, and SYS tenant starting schema versions based on start-up timestamps
    if (OB_FAIL(init_schema_(start_tstamp_usec, sys_start_schema_version))) {
      LOG_ERROR("init schema fail", KR(ret), K(start_tstamp_usec));
    }
  }

  INIT(tb_matcher_, ObLogTableMatcher, tb_white_list, tb_black_list, tg_white_list, tg_black_list);

  INIT(ss_matcher_, ObLogStartSchemaMatcher, data_start_schema_version);

  INIT(trans_stat_mgr_, ObLogTransStatMgr);

  // After initializing the timezone info getter successfully, initialize the obj2str_helper_
  if (OB_SUCC(ret)) {
    if (OB_FAIL(obj2str_helper_.init(*timezone_info_getter_, hbase_util_, enable_hbase_mode,
            enable_convert_timestamp_to_unix_timestamp, enable_backup_mode, *tenant_mgr_))) {
      LOG_ERROR("init obj2str_helper fail", KR(ret), K(enable_hbase_mode),
          K(enable_convert_timestamp_to_unix_timestamp), K(enable_backup_mode));
    }
  }

  ObLogSysTableHelper::ClusterInfo cluster_info;
  if (OB_SUCC(ret)) {
    if (OB_FAIL(query_cluster_info_(cluster_info))) {
      LOG_ERROR("query_cluster_info_ fail", KR(ret), K(cluster_info));
    }
  }

  INIT(committer_, ObLogCommitter, start_seq, &br_queue_, resource_collector_,
      br_pool_, trans_ctx_mgr_, trans_stat_mgr_, err_handler);

  INIT(storager_, ObLogStorager, TCONF.storager_thread_num, TCONF.storager_queue_length, *store_service_, *err_handler);

  INIT(data_processor_, ObLogDataProcessor, TCONF.data_processor_thread_num, TCONF.data_processor_queue_length,
      working_mode_, *store_service_, *err_handler);

  INIT(formatter_, ObLogFormatter, TCONF.formatter_thread_num, DEFAULT_QUEUE_SIZE, working_mode_,
      &obj2str_helper_, br_pool_, meta_manager_, schema_getter_, storager_, err_handler,
      skip_dirty_data, enable_hbase_mode, hbase_util_, skip_hbase_mode_put_column_count_not_consistency,
      enable_output_hidden_primary_key);

  INIT(sequencer_, ObLogSequencer, TCONF.sequencer_thread_num, TCONF.sequencer_queue_length,
      *trans_ctx_mgr_, *trans_stat_mgr_, *committer_, *data_processor_, *err_handler);

  INIT(part_trans_parser_, ObLogPartTransParser, br_pool_, meta_manager_, cluster_info.cluster_id_);
  INIT(dml_parser_, ObLogDmlParser, TCONF.dml_parser_thread_num, DEFAULT_QUEUE_SIZE, *formatter_,
      *err_handler, *part_trans_parser_);

  INIT(ddl_parser_, ObLogDdlParser, TCONF.ddl_parser_thread_num, DEFAULT_QUEUE_SIZE, *err_handler,
      *part_trans_parser_);

  INIT(ddl_handler_, ObLogDDLHandler, ddl_parser_, sequencer_, err_handler,
      schema_getter_, skip_reversed_schema_verison);

  INIT(fetcher_, ObLogFetcher, dml_parser_, ddl_handler_, err_handler, *systable_helper_,
      &trans_task_pool_, log_entry_task_pool_, committer_, TCONF, start_seq);

  // config tenant mgr
  if (OB_SUCC(ret)) {
    if (OB_FAIL(config_tenant_mgr_(start_tstamp_usec, sys_start_schema_version))) {
      LOG_ERROR("config_tenant_mgr_ fail", KR(ret), K(start_tstamp_usec), K(sys_start_schema_version));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(config_data_start_schema_version_(TCONF.global_data_start_schema_version))) {
      LOG_ERROR("config_data_start_schema_version_ fail", KR(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(update_data_start_schema_version_on_split_mode_())) {
      LOG_ERROR("update_data_start_schema_on_split_mode_ fail", KR(ret));
    }
  }

  LOG_INFO("init all components done", KR(ret), K(start_tstamp_usec), K(sys_start_schema_version),
      K(max_cached_trans_ctx_count), K_(is_schema_split_mode));

  return ret;
}

int ObLogInstance::update_data_start_schema_version_on_split_mode_()
{
  int ret = OB_SUCCESS;

  if (! is_schema_split_mode_ || NULL == tenant_mgr_) {
    //do nothing
  } else if (OB_FAIL(tenant_mgr_->set_data_start_schema_version_on_split_mode())) {
    LOG_ERROR("set_data_start_schema_version_on_split_mode fail", KR(ret),
        K(is_schema_split_mode_), K(tenant_mgr_));
  } else {
    // succ
  }

  return ret;
}

int ObLogInstance::config_data_start_schema_version_(const int64_t global_data_start_schema_version)
{
  int ret = OB_SUCCESS;
  // Currently only supports non-split mode configuration for all tenants, split mode to be supported TODO
  if (! is_schema_split_mode_ && NULL != tenant_mgr_) {
    LOG_INFO("config data start schema version", K(global_data_start_schema_version),
        K_(is_schema_split_mode));

    // Set a uniform starting schema version for all tenants in non-split mode
    if (global_data_start_schema_version <= 0) {
      LOG_INFO("global_data_start_schema_version is not configured under non schema split mode, "
          "need not set data start schema version",
          K(global_data_start_schema_version), K_(is_schema_split_mode));
    } else if (OB_FAIL(tenant_mgr_->set_data_start_schema_version_for_all_tenant(
        global_data_start_schema_version))) {
      LOG_ERROR("set_data_start_schema_version_for_all_tenant fail", KR(ret),
          K(global_data_start_schema_version), K(is_schema_split_mode_));
    }
  }

  return ret;
}

int ObLogInstance::config_tenant_mgr_(const int64_t start_tstamp_usec,
    const int64_t sys_schema_version)
{
  int ret = OB_SUCCESS;

  if (OB_ISNULL(tenant_mgr_) || OB_ISNULL(fetcher_)) {
    LOG_ERROR("invaild argument", K(tenant_mgr_), K(fetcher_));
    ret = OB_INVALID_ARGUMENT;
  }

  // Register the "add partition" callback
  // Called sequentially
  // Committer, Sequencer, Fetcher all need to add partitions dynamically
  if (OB_SUCC(ret)) {
    if (OB_FAIL(tenant_mgr_->register_part_add_callback(fetcher_))) {
      LOG_ERROR("fetcher register_part_add_callback fail", KR(ret), K(fetcher_));
    } else {
      LOG_INFO("register add-partition-callback succ", K_(committer), K_(sequencer), K_(fetcher));
    }
  }

  // Register the "Recycle Partition" callback
  // Called sequentially
  // Fetcher cannot delete immediately, it needs to wait for the partition to be reclaimed, i.e. safely deleted
  if (OB_SUCC(ret)) {
    if (OB_FAIL(tenant_mgr_->register_part_recycle_callback(fetcher_))) {
      LOG_ERROR("fetcher register_part_recycle_callback fail", KR(ret), K(fetcher_));
    } else {
      LOG_INFO("register recycle-partition-callback succ", K_(fetcher));
    }
  }

  // Add all tables for all tenants
  // Beforehand, make sure all callbacks are registered
  if (OB_SUCC(ret)) {
    if (OB_FAIL(tenant_mgr_->add_all_tenants(start_tstamp_usec,
        sys_schema_version,
        GET_SCHEMA_TIMEOUT_ON_START_UP))) {
      LOG_ERROR("add_all_tenants fail", KR(ret), K(start_tstamp_usec), K(sys_schema_version));
    }
  }
  return ret;
}

void ObLogInstance::destroy_components_()
{
  LOG_INFO("destroy all components begin");

  // Destruction by reverse order
  DESTROY(fetcher_, ObLogFetcher);
  DESTROY(ddl_handler_, ObLogDDLHandler);
  DESTROY(ddl_parser_, ObLogDdlParser);
  DESTROY(dml_parser_, ObLogDmlParser);
  DESTROY(part_trans_parser_, ObLogPartTransParser);
  DESTROY(sequencer_, ObLogSequencer);
  DESTROY(formatter_, ObLogFormatter);
  DESTROY(committer_, ObLogCommitter);
  DESTROY(systable_helper_, ObLogSysTableHelper);
  DESTROY(ss_matcher_, ObLogStartSchemaMatcher);
  DESTROY(tb_matcher_, ObLogTableMatcher);
  DESTROY(schema_getter_, ObLogSchemaGetter);
  DESTROY(server_provider_, ObLogSQLServerProvider);
  DESTROY(resource_collector_, ObLogResourceCollector);
  DESTROY(meta_manager_, ObLogMetaManager);
  DESTROY(trans_ctx_mgr_, ObLogTransCtxMgr);
  DESTROY(trans_stat_mgr_, ObLogTransStatMgr);
  DESTROY(timezone_info_getter_, ObLogTimeZoneInfoGetter);
  DESTROY(tenant_mgr_, ObLogTenantMgr);
  DESTROY(log_entry_task_pool_, ObLogEntryTaskPool);
  DESTROY(br_pool_, ObLogBRPool);
  DESTROY(storager_, ObLogStorager);
  DESTROY(data_processor_, ObLogDataProcessor);
  DESTROY(store_service_, RocksDbStoreService);

  LOG_INFO("destroy all components end");
}

void ObLogInstance::destroy()
{
  stop();

  inited_ = false;

  oblog_major_ = 0;
  oblog_minor_ = 0;
  oblog_patch_ = 0;

  destroy_components_();
  err_cb_ = NULL;

  TCONF.destroy();
  stop_flag_ = true;
  last_heartbeat_timestamp_micro_sec_ = 0;
  trans_stat_mgr_ = NULL;
  tenant_mgr_ = NULL;
  global_errno_ = 0;
  handle_error_flag_ = 0;
  disable_redirect_log_ = false;
  log_clean_cycle_time_us_ = 0;
  mysql_proxy_.destroy();
  hbase_util_.destroy();
  obj2str_helper_.destroy();
  br_queue_.destroy();
  timer_tid_ = 0;
  sql_tid_ = 0;
  flow_control_tid_ = 0;

  (void)trans_task_pool_.destroy();
  (void)trans_task_pool_alloc_.destroy();

  output_dml_br_count_ = 0;
  output_ddl_br_count_ = 0;

  ObKVGlobalCache::get_instance().destroy();
  ObTenantManager::get_instance().destroy();
  ObMemoryDump::get_instance().destroy();
  ObClockGenerator::destroy();

  is_assign_log_dir_valid_ = false;
  MEMSET(assign_log_dir_, 0, sizeof(assign_log_dir_));
  MEMSET(ob_trace_id_str_, 0, sizeof(ob_trace_id_str_));
  br_index_in_trans_ = 0;
  part_trans_task_count_ = 0;
  start_tstamp_ = 0;
  is_schema_split_mode_ = false;
}

int ObLogInstance::launch()
{
  int ret = OB_SUCCESS;

  LOG_INFO("launch all components begin");

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (stop_flag_) {
    // Reset global error codes at startup
    global_errno_ = OB_SUCCESS;
    stop_flag_ = false;

    if (OB_FAIL(resource_collector_->start())) {
      LOG_ERROR("start resource collector fail", KR(ret));
    } else if (OB_FAIL(storager_->start())) {
      LOG_ERROR("start storager_ fail", KR(ret));
    } else if (OB_FAIL(data_processor_->start())) {
      LOG_ERROR("start data_processor_ fail", KR(ret));
    } else if (OB_FAIL(committer_->start())) {
      LOG_ERROR("start committer fail", KR(ret));
    } else if (OB_FAIL(formatter_->start())) {
      LOG_ERROR("start formatter fail", KR(ret));
    } else if (OB_FAIL(sequencer_->start())) {
      LOG_ERROR("start sequencer fail", KR(ret));
    } else if (OB_FAIL(dml_parser_->start())) {
      LOG_ERROR("start DML parser fail", KR(ret));
    } else if (OB_FAIL(ddl_parser_->start())) {
      LOG_ERROR("start DDL parser fail", KR(ret));
    } else if (OB_FAIL(ddl_handler_->start())) {
      LOG_ERROR("start fetcher fail", KR(ret));
    } else if (OB_FAIL(fetcher_->start())) {
      LOG_ERROR("start fetcher fail", KR(ret));
    } else if (OB_FAIL(start_threads_())) {
      LOG_ERROR("start_threads_ fail", KR(ret));
    } else if (OB_FAIL(timezone_info_getter_->start())) {
      LOG_ERROR("start_timezone_info_thread_ fail", KR(ret));
    } else {
      LOG_INFO("launch all components end success");
    }
  }

  return ret;
}

void ObLogInstance::stop()
{
  if (inited_) {
    mark_stop_flag();

    LOG_INFO("stop all components begin");

    stop_flag_ = true;

    // stop thread
    wait_threads_stop_();
    // stop timezon info getter
    timezone_info_getter_->stop();

    fetcher_->stop();
    ddl_handler_->stop();
    ddl_parser_->stop();
    dml_parser_->stop();
    sequencer_->stop();
    formatter_->stop();
    storager_->stop();
    data_processor_->stop();
    committer_->stop();
    resource_collector_->stop();

    // set global error code
    global_errno_ = (global_errno_ == OB_SUCCESS ? OB_IN_STOP_STATE : global_errno_);

    LOG_INFO("stop all components end");
  }
}

int ObLogInstance::table_group_match(const char *pattern,
    bool &is_matched,
    const int fnmatch_flags)
{
  UNUSED(pattern);
  UNUSED(is_matched);
  UNUSED(fnmatch_flags);
  // not support
  return OB_NOT_SUPPORTED;
}

int ObLogInstance::get_table_groups(std::vector<std::string> &table_groups)
{
  UNUSED(table_groups);
  // not support
  return OB_NOT_SUPPORTED;
}

int ObLogInstance::get_tenant_ids(std::vector<uint64_t> &tenant_ids)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(tenant_mgr_)) {
    LOG_ERROR("tenant_mgr_ is null", K(tenant_mgr_));
    ret = OB_ERR_UNEXPECTED;
  } else if (OB_FAIL(tenant_mgr_->get_all_tenant_ids(tenant_ids))) {
    LOG_ERROR("get_all_tenant_ids fail", KR(ret));
  } else {
    // succ
  }

  return ret;
}

void ObLogInstance::mark_stop_flag()
{
  if (inited_) {
    LOG_INFO("mark_stop_flag begin");

    fetcher_->mark_stop_flag();
    ddl_handler_->mark_stop_flag();
    ddl_parser_->mark_stop_flag();
    dml_parser_->mark_stop_flag();
    sequencer_->mark_stop_flag();
    formatter_->mark_stop_flag();
    storager_->mark_stop_flag();
    data_processor_->mark_stop_flag();
    committer_->mark_stop_flag();
    resource_collector_->mark_stop_flag();
    timezone_info_getter_->mark_stop_flag();

    LOG_INFO("mark_stop_flag end");
  }
}

int ObLogInstance::next_record(ILogRecord **record, const int64_t timeout_us)
{
  int ret = OB_SUCCESS;
  int32_t major_version = 0;
  uint64_t tenant_id = OB_INVALID_ID;

  if (OB_FAIL(next_record(record, major_version, tenant_id, timeout_us))) {
    if (OB_TIMEOUT != ret && OB_IN_STOP_STATE != ret) {
      LOG_ERROR("next record fail", KR(ret), K(record));
    }
  }

  return ret;
}

int ObLogInstance::next_record(ILogRecord **record,
    int32_t &major_version,
    uint64_t &tenant_id,
    const int64_t timeout_us)
{
  int ret = OB_SUCCESS;
  ILogRecord *pop_record = NULL;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(record)) {
    LOG_ERROR("invalid argument", K(record));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_UNLIKELY(OB_SUCCESS != global_errno_)) {
    // In case of global error, the corresponding error code is returned, except for OB_TIMEOUT
    ret = (OB_TIMEOUT == global_errno_) ? OB_IN_STOP_STATE : global_errno_;
  } else if (OB_FAIL(br_queue_.pop(pop_record, major_version, tenant_id, timeout_us))) {
    if (OB_TIMEOUT != ret) {
      LOG_ERROR("pop binlog record from br_queue fail", KR(ret));
    }
  } else if (OB_ISNULL(pop_record)) {
    LOG_ERROR("pop binlog record from br_queue fail", KR(ret), K(pop_record));
    ret = OB_ERR_UNEXPECTED;
  } else {
    *record = pop_record;
  }

  if (OB_SUCC(ret)) {
    ObLogBR *oblog_br = NULL;

    if (OB_ISNULL(record) || OB_ISNULL(*record)) {
      LOG_ERROR("record is invalid", K(record));
      ret = OB_ERR_UNEXPECTED;
    } else if (OB_ISNULL(oblog_br = reinterpret_cast<ObLogBR *>((*record)->getUserData()))) {
      LOG_ERROR("get user data fail", "br", *record, K(oblog_br));
      ret = OB_ERR_UNEXPECTED;
    } else {
      int record_type = (*record)->recordType();
      int64_t timestamp_usec = (*record)->getTimestamp() * 1000000 + (*record)->getRecordUsec();

      if (HEARTBEAT == record_type) {
        last_heartbeat_timestamp_micro_sec_ =
            std::max(timestamp_usec, last_heartbeat_timestamp_micro_sec_);
      }

      // NOTE: Set the timestamp of the last heartbeat to Checkpoint1 of the data
      (*record)->setCheckpoint(last_heartbeat_timestamp_micro_sec_ / 1000000,
          last_heartbeat_timestamp_micro_sec_ % 1000000);

      if (EDDL == record_type) {
        ATOMIC_INC(&output_ddl_br_count_);
      } else if (EBEGIN == record_type) {
        do_drc_consume_tps_stat_();
      } else if (HEARTBEAT != record_type && ECOMMIT != record_type) {
        ATOMIC_INC(&output_dml_br_count_);
        do_drc_consume_rps_stat_();
      } else {
        // do nothing
      }

      const int64_t part_trans_task_count = oblog_br->get_part_trans_task_count();
      bool need_accumulate_stat = true;
      do_stat_for_part_trans_task_count_(record_type, part_trans_task_count, need_accumulate_stat);
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(verify_ob_trace_id_(*record))) {
      LOG_ERROR("verify_ob_trace_id_ fail", KR(ret), K(record), K(*record));
    } else {
      // do nothing
    }
  }

  if (OB_SUCC(ret)) {
    if (! TCONF.enable_verify_mode) {
      // do nothing
    } else {
      if (OB_FAIL(verify_dml_unique_id_(*record))) {
        LOG_ERROR("verify_dml_unique_id_ fail", KR(ret), K(record), K(*record));
      } else if (OB_FAIL(verify_ddl_schema_version_(*record))) {
        LOG_ERROR("verify_ddl_schema_version_ fail", KR(ret), K(record), K(*record));
      } else {
      }
    }
  }

  return ret;
}

int ObLogInstance::verify_ob_trace_id_(ILogRecord *br)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br)) {
    LOG_ERROR("invalid arguments", K(br));
    ret = OB_INVALID_ARGUMENT;
  } else if (! TCONF.need_verify_ob_trace_id) {
    // do nothing
  } else {
    int record_type = br->recordType();

    if (EINSERT == record_type || EUPDATE == record_type || EDELETE == record_type) {
      // only verify insert\update\delete type
      const ObString ob_trace_id_config(ob_trace_id_str_);
      ObLogBR *oblog_br = NULL;
      ObLogRowDataIndex *row_data_index = NULL;
      PartTransTask *task = NULL;

      if (OB_ISNULL(oblog_br = reinterpret_cast<ObLogBR *>(br->getUserData()))) {
        LOG_ERROR("get user data fail", K(br), K(oblog_br));
        ret = OB_INVALID_ARGUMENT;
      } else if (OB_ISNULL(row_data_index = static_cast<ObLogRowDataIndex *>(oblog_br->get_host()))) {
        LOG_ERROR("row_data_index is NULL", KPC(row_data_index));
        ret = OB_ERR_UNEXPECTED;
      } else if (OB_ISNULL(task = static_cast<PartTransTask *>(row_data_index->get_host()))) {
        LOG_ERROR("part trans task is null", KPC(task));
        ret = OB_ERR_UNEXPECTED;
      } else {
        ObString trace_id;
        const int64_t trace_id_idx = 2;

        if (OB_FAIL(get_br_filter_value_(*br, trace_id_idx, trace_id))) {
          LOG_ERROR("get_br_filter_value_ fail", KR(ret), K(trace_id_idx), K(trace_id));
        } else {
          if (0 == ob_trace_id_config.compare(trace_id)) {
            // succ
          } else {
            LOG_ERROR("verify_ob_trace_id fail", K(trace_id), K(ob_trace_id_config), KPC(task));
            ret = OB_ITEM_NOT_MATCH;
          }
        }
      }
    } // record_type
  }

  return ret;
}

int ObLogInstance::verify_ddl_schema_version_(ILogRecord *br)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br)) {
    LOG_ERROR("invalid arguments", K(br));
    ret = OB_INVALID_ARGUMENT;
  } else {
    int record_type = br->recordType();

    if (EDDL == record_type) {
      ObLogBR *oblog_br = NULL;
      PartTransTask *task = NULL;
      int64_t new_cols_count = 0;
      BinLogBuf *new_cols = br->newCols((unsigned int &)new_cols_count);
      int64_t ddl_schema_version_index = 1;

      // Currently ddl br only synchronizes two columns, ddl_stmt_str and ddl_schema_version
      if (OB_ISNULL(oblog_br = reinterpret_cast<ObLogBR *>(br->getUserData()))) {
        LOG_ERROR("get user data fail", K(br), K(oblog_br));
        ret = OB_INVALID_ARGUMENT;
      } else if (OB_ISNULL(task = static_cast<PartTransTask *>(oblog_br->get_host()))) {
        LOG_ERROR("part trans task is null", KPC(task));
        ret = OB_ERR_UNEXPECTED;
      } else if (OB_UNLIKELY(2 != new_cols_count)) {
        LOG_ERROR("ddl br new cols count is not equal 2", K(new_cols_count));
        ret = OB_ERR_UNEXPECTED;
      } else {
        ObString br_ddl_schema_version(new_cols[ddl_schema_version_index].buf_used_size,
            new_cols[ddl_schema_version_index].buf);

        int64_t ddl_schema_version = oblog_br->get_ddl_schema_version();
        const int64_t ddl_schema_version_str_len = DdlStmtTask::MAX_DDL_SCHEMA_VERSION_STR_LENGTH;
        char ddl_schema_version_str[ddl_schema_version_str_len];
        int64_t pos = 0;

        if (OB_FAIL(databuff_printf(ddl_schema_version_str, ddl_schema_version_str_len,
              pos, "%ld", ddl_schema_version))) {
          LOG_ERROR("databuff_printf fail", KR(ret), K(ddl_schema_version),
            K(ddl_schema_version_str), K(pos));
        } else if (0 == br_ddl_schema_version.compare(ddl_schema_version_str)) {
          // succ
        } else {
          LOG_ERROR("verify_ddl_schema_version_ fail", K(br_ddl_schema_version),
              K(ddl_schema_version_str), KPC(task));
          ret = OB_ITEM_NOT_MATCH;
        }
      }
    }
  }

  return ret;
}

int ObLogInstance::verify_dml_unique_id_(ILogRecord *br)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br)) {
    LOG_ERROR("invalid arguments", K(br));
    ret = OB_INVALID_ARGUMENT;
  } else {
    // Adding a self-checking adjacent record is a different scenario
    static ObPartitionKey last_pkey;
    static uint64_t last_prepare_log_id = OB_INVALID_ID;
    static int32_t last_log_offset = 0;
    static uint64_t last_row_index = OB_INVALID_ID;

    int record_type = br->recordType();

    if (EINSERT == record_type || EUPDATE == record_type || EDELETE == record_type) {
      // only verify insert\update\delete type
      ObLogBR *oblog_br = NULL;
      ObLogRowDataIndex *row_data_index = NULL;
      PartTransTask *task = NULL;

      if (OB_ISNULL(oblog_br = reinterpret_cast<ObLogBR *>(br->getUserData()))) {
        LOG_ERROR("get user data fail", K(br), K(oblog_br));
        ret = OB_INVALID_ARGUMENT;
      } else if (OB_ISNULL(row_data_index = static_cast<ObLogRowDataIndex *>(oblog_br->get_host()))) {
        LOG_ERROR("row_data_index is NULL", KPC(row_data_index));
        ret = OB_ERR_UNEXPECTED;
      } else if (OB_ISNULL(task = static_cast<PartTransTask *>(row_data_index->get_host()))) {
        LOG_ERROR("part trans task is null", KPC(task));
        ret = OB_ERR_UNEXPECTED;
      } else {
        // binlog record set unique id
        ObString br_unique_id;
        const int64_t br_unique_id_idx = 1;
        common::ObString dml_unique_id;
        const ObString &pkey_and_log_id_str = task->get_pkey_and_log_id_str();
        const int32_t log_offset = row_data_index->get_log_offset();
        uint64_t row_index = row_data_index->get_row_no();
        DmlStmtUniqueID dml_stmt_unique_id(pkey_and_log_id_str, log_offset, row_index);

        if (OB_UNLIKELY(! dml_stmt_unique_id.is_valid())) {
          LOG_ERROR("dml_stmt_unique_id is not valid", K(dml_stmt_unique_id));
          ret = OB_INVALID_ARGUMENT;
        } else if (OB_FAIL(get_br_filter_value_(*br, br_unique_id_idx, br_unique_id))) {
          LOG_ERROR("get_br_filter_value_ fail", KR(ret), K(br_unique_id_idx), K(br_unique_id));
        } else {
          const int64_t buf_len = dml_stmt_unique_id.get_dml_unique_id_length() + 1;
          // verify current br
          char buf[buf_len];
          int64_t pos = 0;

          if (OB_FAIL(dml_stmt_unique_id.customized_to_string(buf, buf_len, pos))) {
            LOG_ERROR("init_dml_unique_id_ fail", KR(ret), K(buf_len), K(pos));
          } else {
            dml_unique_id.assign_ptr(buf, static_cast<int32_t>(pos));

            if (0 == br_unique_id.compare(dml_unique_id)) {
              // succ
            } else {
              LOG_ERROR("verify_dml_unique_id_ fail", K(br_unique_id), K(dml_unique_id), KPC(task));
              ret = OB_ITEM_NOT_MATCH;
            }
          }

          if (OB_SUCC(ret)) {
            // Verify Adjacent br
            if (OB_INVALID_ID == last_prepare_log_id) {
              // won't verify for the first time
            } else {
              if (last_pkey == task->get_partition()
                  && last_prepare_log_id == task->get_prepare_log_id()
                  && last_log_offset == log_offset
                  && last_row_index == row_index) {
                LOG_ERROR("current br_unique_id should not be equal to last_br_unique_id",
                    K(br_unique_id), KPC(task), K(row_index),
                    K(last_pkey), K(last_prepare_log_id), K(last_log_offset), K(last_row_index));
                ret = OB_ERR_UNEXPECTED;
              } else {
                // succ
              }
            }
          } // OB_SUCC(ret)

          if (OB_SUCC(ret)) {
            last_pkey = task->get_partition();
            last_prepare_log_id = task->get_prepare_log_id();
            last_log_offset = log_offset;
            last_row_index = row_index;
          }
        }
      }
    }
  }

  return ret;
}

int ObLogInstance::get_br_filter_value_(ILogRecord &br,
    const int64_t idx,
    common::ObString &str)
{
  int ret = OB_SUCCESS;
  LogRecordImpl *br_impl = NULL;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br_impl = dynamic_cast<LogRecordImpl *>(&br))) {
    LOG_ERROR("invalid arguments", K(br_impl));
    ret = OB_INVALID_ARGUMENT;
  } else {
    unsigned int filter_rv_count = 0;
    const BinLogBuf *filter_value = br_impl->filterValues((unsigned int &) filter_rv_count);
    const BinLogBuf *str_buf = filter_value + idx;

    if (OB_ISNULL(str_buf)) {
      LOG_ERROR("str_buf is NULL");
      ret = OB_ERR_UNEXPECTED;
    } else {
      str.assign_ptr(str_buf->buf, str_buf->buf_used_size);
    }
  }

  return ret;
}

void ObLogInstance::release_record(ILogRecord *record)
{
  int ret = OB_SUCCESS;
  if (inited_ && NULL != record) {
    int record_type = record->recordType();
    ObLogBR *br = reinterpret_cast<ObLogBR *>(record->getUserData());

    if (OB_ISNULL(br)) {
      LOG_ERROR("binlog record user data is NULL", K(record));
      ret = OB_ERR_UNEXPECTED;
    } else {
      if (EDDL == record_type) {
        ATOMIC_DEC(&output_ddl_br_count_);
      } else if (EBEGIN == record_type) {
        do_drc_release_tps_stat_();
      } else if (HEARTBEAT != record_type && ECOMMIT != record_type) {
        ATOMIC_DEC(&output_dml_br_count_);
        do_drc_release_rps_stat_();
      } else {
        // do nothing
      }

      const int64_t part_trans_task_count = br->get_part_trans_task_count();
      bool need_accumulate_stat = false;
      do_stat_for_part_trans_task_count_(record_type, part_trans_task_count, need_accumulate_stat);

      if (OB_FAIL(resource_collector_->revert(record_type, br))) {
        if (OB_IN_STOP_STATE != ret) {
          LOG_ERROR("revert binlog record fail", KR(ret), K(br),
              "record_type", print_record_type(record_type));
        }
      } else {
        br = NULL;
        record = NULL;
      }
    }
  }
}

void ObLogInstance::handle_error(const int err_no, const char *fmt, ...)
{
  static const int64_t MAX_ERR_MSG_LEN = 1024;
  static char err_msg[MAX_ERR_MSG_LEN];

  if (inited_) {
    // Call the error callback only once
    if (0 == ATOMIC_CAS(&handle_error_flag_, 0, 1)) {
      va_list ap;
      va_start(ap, fmt);
      vsnprintf(err_msg, sizeof(err_msg), fmt, ap);
      va_end(ap);

      global_errno_ = (err_no == OB_SUCCESS ? OB_IN_STOP_STATE : err_no);
      _LOG_INFO("HANDLE_ERROR: err_cb=%p, errno=%d, errmsg=\"%s\"", err_cb_, err_no, err_msg);

      if (NULL != err_cb_) {
        ObLogError err;
        err.level_ = ObLogError::ERR_ABORT; // FIXME: Support for other types of error levels
        err.errno_ = err_no;
        err.errmsg_ = err_msg;

        LOG_INFO("ERROR_CALLBACK begin", KP(err_cb_));
        err_cb_(err);
        LOG_INFO("ERROR_CALLBACK end", KP(err_cb_));
      } else {
        LOG_ERROR("No ERROR CALLBACK function available, abort now");
      }

      // notify other module to stop
      mark_stop_flag();
    }
  }
}

int32_t ObLogInstance::get_log_level() const
{
  return OB_LOGGER.get_log_level();
}

const char *ObLogInstance::get_log_file() const
{
  return DEFAULT_LOG_FILE;
}

void ObLogInstance::write_pid_file_()
{
  int pid_file_fd = -1;
  const char *pid_file = DEFAULT_PID_FILE;
  char pid_file_dir[32] = {};

  (void)snprintf(pid_file_dir, sizeof(pid_file_dir), "%s", DEFAULT_PID_FILE_DIR);
  common::FileDirectoryUtils::create_full_path(pid_file_dir);

  pid_file_fd = open(pid_file, O_RDWR | O_CREAT, 0600);
  if (OB_UNLIKELY(pid_file_fd < 0)) {
    LOG_ERROR("open pid file fail", K(pid_file), K(pid_file_fd), K(errno), KERRMSG);
  } else {
    char buf[32] = {};
    (void)snprintf(buf, sizeof(buf), "%d\n", getpid());
    (void)ftruncate(pid_file_fd, 0);

    ssize_t len = strlen(buf);
    ssize_t nwrite = write(pid_file_fd, buf, len);
    if (OB_UNLIKELY(len != nwrite)) {
      LOG_ERROR("write pid file fail", K(pid_file), K(pid_file_fd),
          K(buf), K(len), K(errno), KERRMSG);
    }

    close(pid_file_fd);
    pid_file_fd = -1;
  }
}

void *ObLogInstance::timer_thread_func_(void *args)
{
  if (NULL != args) {
    ObLogInstance *instance = static_cast<ObLogInstance *>(args);
    instance->timer_routine();
  }

  return NULL;
}

void *ObLogInstance::sql_thread_func_(void *args)
{
  if (NULL != args) {
    ObLogInstance *instance = static_cast<ObLogInstance *>(args);
    instance->sql_thread_routine();
  }

  return NULL;
}

void *ObLogInstance::flow_control_thread_func_(void *args)
{
  if (NULL != args) {
    ObLogInstance *instance = static_cast<ObLogInstance *>(args);
    instance->flow_control_thread_routine();
  }

  return NULL;
}

void ObLogInstance::sql_thread_routine()
{
  int ret = OB_SUCCESS;
  const static int64_t THREAD_INTERVAL = 1 * _SEC_;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else {
    while (! stop_flag_ && OB_SUCCESS == ret) {
      int64_t cluster_version_refresh_interval_sec = TCONF.cluster_version_refresh_interval_sec * _SEC_;

      // refresh SQL SERVER list
      if (REACH_TIME_INTERVAL(REFRESH_SERVER_LIST_INTERVAL)) {
        ObLogSQLServerProvider *server_provider = static_cast<ObLogSQLServerProvider *>(server_provider_);
        if (OB_ISNULL(server_provider)) {
          LOG_ERROR("server_provider is NULL", K(server_provider));
          ret = OB_ERR_UNEXPECTED;
        } else {
          server_provider->call_refresh_server_list();
        }
      }

      // refresh cluster version
      if (REACH_TIME_INTERVAL(cluster_version_refresh_interval_sec)) {
        (void)update_cluster_version_();

        // check observer versin <= liboblog version
        if (OB_FAIL(check_observer_version_valid_())) {
          LOG_ERROR("check_observer_version_valid_ fail", KR(ret));
        }
      }

      usleep(THREAD_INTERVAL);
    }

    if (stop_flag_) {
      ret = OB_IN_STOP_STATE;
    }

    if (OB_SUCCESS != ret && OB_IN_STOP_STATE != ret) {
      handle_error(ret, "sql thread exits, err=%d", ret);
      stop_flag_ = true;
    }
  }

  LOG_INFO("instance sql thread exits", KR(ret), K_(stop_flag));
}

void ObLogInstance::flow_control_thread_routine()
{
  int ret = OB_SUCCESS;
  const static int64_t THREAD_INTERVAL = 100 * 1000;  // Flow control takes 100ms at a time

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else {
    while (! stop_flag_ && OB_SUCCESS == ret) {
      // flow control
      global_flow_control_();

      usleep(THREAD_INTERVAL);
    }

    if (stop_flag_) {
      ret = OB_IN_STOP_STATE;
    }

    if (OB_SUCCESS != ret && OB_IN_STOP_STATE != ret) {
      handle_error(ret, "flow control thread exits, err=%d", ret);
      stop_flag_ = true;
    }
  }

  LOG_INFO("instance flow control thread exits", KR(ret), K_(stop_flag));
}

void ObLogInstance::timer_routine()
{
  int ret = OB_SUCCESS;
  const static int64_t TIMER_INTERVAL = 1 * _SEC_;
  const static int64_t PRINT_INTERVAL = 10 * _SEC_;
  int64_t clean_log_interval = CLEAN_LOG_INTERVAL;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("instance has not been initialized");
    ret = OB_NOT_INIT;
  } else {
    while (! stop_flag_ && OB_SUCCESS == ret) {
      // Periodic reload configuration
      if (REACH_TIME_INTERVAL(RELOAD_CONFIG_INTERVAL)) {
        reload_config_();
      }

      // Periodic printing of statistical information
      if (REACH_TIME_INTERVAL(PRINT_INTERVAL)) {
        print_tenant_memory_usage_();
        schema_getter_->print_stat_info();
        tenant_mgr_->print_stat_info();
        trans_task_pool_.print_stat_info();
        log_entry_task_pool_->print_stat_info();
        br_pool_->print_stat_info();
        trans_ctx_mgr_->print_stat_info();
        print_trans_stat_();
        resource_collector_->print_stat_info();
        data_processor_->print_stat_info();
      }

      // Periodic memory recycling
      if (REACH_TIME_INTERVAL(ObLogSchemaGetter::RECYCLE_MEMORY_INTERVAL)) {
        schema_getter_->try_recycle_memory();
      }

      // Cycle Cleanup Log
      int64_t clean_cycle = ATOMIC_LOAD(&log_clean_cycle_time_us_);
      clean_log_interval = std::min(clean_log_interval, clean_cycle);
      if (clean_cycle > 0 && REACH_TIME_INTERVAL(clean_log_interval)) {
        clean_log_();
      }

      usleep(TIMER_INTERVAL);
    }

    if (stop_flag_) {
      ret = OB_IN_STOP_STATE;
    }

    if (OB_SUCCESS != ret && OB_IN_STOP_STATE != ret) {
      handle_error(ret, "timer thread exits, err=%d", ret);
      stop_flag_ = true;
    }
  }

  LOG_INFO("instance timer thread exits", KR(ret), K_(stop_flag));
}

int ObLogInstance::start_threads_()
{
  int ret = OB_SUCCESS;
  int pthread_ret = 0;

  if (OB_UNLIKELY(0 != timer_tid_)) {
    LOG_ERROR("timer thread has been started", K(timer_tid_));
    ret = OB_NOT_SUPPORTED;
  } else if (0 != (pthread_ret = pthread_create(&timer_tid_, NULL, timer_thread_func_, this))) {
    LOG_ERROR("start timer thread fail", K(pthread_ret), KERRNOMSG(pthread_ret));
    ret = OB_ERR_UNEXPECTED;
  } else if (OB_UNLIKELY(0 != sql_tid_)) {
    LOG_ERROR("sql thread has been started", K(sql_tid_));
    ret = OB_NOT_SUPPORTED;
  } else if (0 != (pthread_ret = pthread_create(&sql_tid_, NULL, sql_thread_func_, this))) {
    LOG_ERROR("start sql thread fail", K(pthread_ret), KERRNOMSG(pthread_ret));
    ret = OB_ERR_UNEXPECTED;
  } else if (OB_UNLIKELY(0 != flow_control_tid_)) {
    LOG_ERROR("flow control thread has been started", K(flow_control_tid_));
    ret = OB_NOT_SUPPORTED;
  } else if (0 != (pthread_ret = pthread_create(&flow_control_tid_, NULL, flow_control_thread_func_, this))) {
    LOG_ERROR("start flow control thread fail", K(pthread_ret), KERRNOMSG(pthread_ret));
    ret = OB_ERR_UNEXPECTED;
  } else {
    LOG_INFO("start instance threads succ", K(timer_tid_), K(sql_tid_), K(flow_control_tid_));
  }

  return ret;
}

void ObLogInstance::wait_threads_stop_()
{
  if (0 != timer_tid_) {
    int pthread_ret = pthread_join(timer_tid_, NULL);
    if (0 != pthread_ret) {
      LOG_ERROR("join timer thread fail", K(timer_tid_), K(pthread_ret),
          KERRNOMSG(pthread_ret));
    } else {
      LOG_INFO("stop timer thread succ", K(timer_tid_));
    }

    timer_tid_ = 0;
  }

  if (0 != sql_tid_) {
    int pthread_ret = pthread_join(sql_tid_, NULL);
    if (0 != pthread_ret) {
      LOG_ERROR("join sql thread fail", K(sql_tid_), K(pthread_ret),
          KERRNOMSG(pthread_ret));
    } else {
      LOG_INFO("stop sql thread succ", K(sql_tid_));
    }

    sql_tid_ = 0;
  }

  if (0 != flow_control_tid_) {
    int pthread_ret = pthread_join(flow_control_tid_, NULL);
    if (0 != pthread_ret) {
      LOG_ERROR("join flow control thread fail", K(flow_control_tid_), K(pthread_ret),
          KERRNOMSG(pthread_ret));
    } else {
      LOG_INFO("stop flow control thread succ", K(flow_control_tid_));
    }

    flow_control_tid_ = 0;
  }
}

void ObLogInstance::reload_config_()
{
  int ret = OB_SUCCESS;
  ObLogConfig &config = TCONF;
  const char *default_config_fpath = DEFAULT_CONFIG_FPATN;

  _LOG_INFO("====================reload config begin====================");

  if (OB_FAIL(config.load_from_file(default_config_fpath))) {
    LOG_ERROR("load_from_file fail", KR(ret), K(default_config_fpath));
  } else {
    LOG_INFO("reset log level", "log_level", config.log_level.str());
    OB_LOGGER.set_mod_log_levels(config.log_level.str());

    ATOMIC_STORE(&log_clean_cycle_time_us_, config.log_clean_cycle_time_in_hours * _HOUR_);

    if (0 != config.enable_dump_pending_trans_info) {
      dump_pending_trans_info_();
    }

    // config fetcher
    if (OB_NOT_NULL(fetcher_)) {
      fetcher_->configure(config);
    }

    // config sequencer
    if (OB_NOT_NULL(sequencer_)) {
      sequencer_->configure(config);
    }

    // config committer_
    if (OB_NOT_NULL(committer_)) {
      committer_->configure(config);
    }

    // config server_provider_
    if (OB_NOT_NULL(server_provider_)) {
      ObLogSQLServerProvider *oblog_server_provider = static_cast<ObLogSQLServerProvider *>(server_provider_);

      if (OB_ISNULL(oblog_server_provider)) {
        LOG_ERROR("oblog_server_provider is NULL", K(oblog_server_provider));
        ret = OB_ERR_UNEXPECTED;
      } else {
        oblog_server_provider->configure(config);
      }
    }
  }

  _LOG_INFO("====================reload config end====================");
}

void ObLogInstance::print_tenant_memory_usage_()
{
  lib::ObMallocAllocator *mallocator = lib::ObMallocAllocator::get_instance();

  if (OB_ISNULL(mallocator)) {
    LOG_ERROR("mallocator is NULL, can not print_tenant_memory_usage");
  } else {
    mallocator->print_tenant_memory_usage(OB_SYS_TENANT_ID);
    mallocator->print_tenant_ctx_memory_usage(OB_SYS_TENANT_ID);
    mallocator->print_tenant_memory_usage(OB_SERVER_TENANT_ID);
    mallocator->print_tenant_ctx_memory_usage(OB_SERVER_TENANT_ID);
  }
}

/// Global traffic control
/// Principle: 1. Keep the total number of active Partition Transaction Tasks (PartTransTask) under control by referring to the number of
///        Match the production rate with the consumption rate to avoid OOM
///            2. Consider liboblog memory usage, when the memory usage reaches a certain limit, flow control should be performed to avoid OOM
///
/// Implementation: 1. Check the number of active partition transaction tasks periodically, and when it exceeds the upper bound, check whether there are enough reusable
///        Partitioned transaction tasks, if they exist, stop Fetcher; otherwise, turn on Fetcher.
//                  2. periodically check the total memory occupied by liboblog, and when it exceeds the upper bound, check if there are enough reusable
//         partitioned transaction tasks, if they exist, stop Fetcher; otherwise turn on Fetcher.
void ObLogInstance::global_flow_control_()
{
  int ret = OB_SUCCESS;

  if (inited_) {
    if (OB_ISNULL(fetcher_) || OB_ISNULL(dml_parser_)
        || OB_ISNULL(formatter_)
        || OB_ISNULL(ddl_handler_) || OB_ISNULL(resource_collector_)) {
      LOG_ERROR("invalid arguments", K(fetcher_), K(dml_parser_),
          K(formatter_), K(ddl_handler_), K(resource_collector_));
      ret = OB_ERR_UNEXPECTED;
    } else {
      int64_t part_trans_task_active_count_upper_bound =
        TCONF.part_trans_task_active_count_upper_bound;
      int64_t part_trans_task_reusable_count_upper_bound =
        TCONF.part_trans_task_reusable_count_upper_bound;
      int64_t ready_to_seq_task_upper_bound =
        TCONF.ready_to_seq_task_upper_bound;
      int64_t storager_task_count_upper_bound =
        TCONF.storager_task_count_upper_bound;
      int64_t storager_mem_percentage =
        TCONF.storager_mem_percentage;
      double system_memory_avail_percentage_lower_bound =
        static_cast<double>(TCONF.system_memory_avail_percentage_lower_bound) / 100;
      int64_t memory_limit = TCONF.memory_limit.get();

      int64_t total_part_trans_task_count = trans_task_pool_.get_total_count();
      int64_t active_part_trans_task_count = trans_task_pool_.get_alloc_count();
      int64_t active_log_entry_task_count = log_entry_task_pool_->get_alloc_count();
      int64_t reusable_part_trans_task_count = 0;
      int64_t ready_to_seq_task_count = 0;

      int64_t fetcher_part_trans_task_count = fetcher_->get_part_trans_task_count();
      int64_t dml_parser_part_trans_task_count = 0;
      int64_t br_queue_part_trans_task_count = br_queue_.get_part_trans_task_count();
      int64_t out_part_trans_task_count = get_out_part_trans_task_count_();
      int64_t resource_collector_part_trans_task_count = resource_collector_->get_part_trans_task_count();
      int64_t committer_ddl_part_trans_task_count = 0;
      int64_t committer_dml_part_trans_task_count = 0;
      int64_t committer_br_count = 0;
      committer_->get_part_trans_task_count(committer_ddl_part_trans_task_count,
          committer_dml_part_trans_task_count,
          committer_br_count);

      int64_t memory_hold = get_memory_hold_();
      int64_t system_memory_avail = get_memory_avail_();
      int64_t system_memory_limit = get_memory_limit_();
      int64_t system_memory_avail_lower_bound =
        static_cast<int64_t>(static_cast<double>(system_memory_limit) * system_memory_avail_percentage_lower_bound);
      bool need_slow_down_fetcher = false;

      if (OB_FAIL(get_task_count_(ready_to_seq_task_count, reusable_part_trans_task_count))) {
        LOG_ERROR("get_task_count fail", KR(ret), K(ready_to_seq_task_count),
            K(reusable_part_trans_task_count));
      } else if (OB_FAIL(dml_parser_->get_log_entry_task_count(dml_parser_part_trans_task_count))) {
        LOG_ERROR("DML parser get_log_entry_task_count fail", KR(ret), K(dml_parser_part_trans_task_count));
      } else {
        int64_t storager_task_count = 0;
        storager_->get_task_count(storager_task_count);

        // Use the following policy for global traffic control:
        // need_slow_down = (active partitioned transaction tasks exceed the upper limit || liboblog takes up more memory than the upper limit || system free memory is less than a certain percentage)
        // && (reusable transaction tasks exceeds limit || Parser and Sequencer module cache tasks exceeds limit)
        bool condition1 = (active_part_trans_task_count >= part_trans_task_active_count_upper_bound)
          || (memory_hold >= memory_limit)
          || (system_memory_avail < system_memory_avail_lower_bound);
        bool condition2 = (reusable_part_trans_task_count >= part_trans_task_reusable_count_upper_bound)
          || (ready_to_seq_task_count > ready_to_seq_task_upper_bound);
        bool condition3 = (storager_task_count > storager_task_count_upper_bound) && (memory_hold >= storager_mem_percentage * memory_limit);

        need_slow_down_fetcher = (condition1 && condition2) || (condition3);

        // Get the number of active distributed transactions after sequencing, including sequenced, formatted, and committed
        int64_t seq_trans_count =
          trans_ctx_mgr_->get_trans_count(TransCtx::TRANS_CTX_STATE_SEQUENCED);
        int64_t committed_trans_count =
          trans_ctx_mgr_->get_trans_count(TransCtx::TRANS_CTX_STATE_COMMITTED);

        bool current_fetcher_is_paused = fetcher_->is_paused();

        // Print logs: 1. on status changes; 2. cyclical printing
        bool need_print_state = (current_fetcher_is_paused != need_slow_down_fetcher);

        if (need_print_state || REACH_TIME_INTERVAL(PRINT_GLOBAL_FLOW_CONTROL_INTERVAL)) {
          _LOG_INFO("[STAT] [FLOW_CONTROL] NEED_SLOW_DOWN=%d "
              "PAUSED=%d MEM=%s/%s "
              "AVAIL_MEM=%s/%s "
              "READY_TO_SEQ=%ld/%ld "
              "PART_TRANS(TOTAL=%ld,ACTIVE=%ld/%ld,REUSABLE=%ld/%ld) "
              "LOG_TASK(ACTIVE=%ld) "
              "STORE(%ld/%ld) "
              "[FETCHER=%ld DML_PARSER=%ld "
              "COMMITER=%ld USER_QUEUE=%ld OUT=%ld RC=%ld] "
              "DIST_TRANS(SEQ=%ld,COMMITTED=%ld)",
              need_slow_down_fetcher, current_fetcher_is_paused,
              SIZE_TO_STR(memory_hold), SIZE_TO_STR(memory_limit),
              SIZE_TO_STR(system_memory_avail), SIZE_TO_STR(system_memory_avail_lower_bound),
              ready_to_seq_task_count, ready_to_seq_task_upper_bound,
              total_part_trans_task_count,
              active_part_trans_task_count, part_trans_task_active_count_upper_bound,
              reusable_part_trans_task_count, part_trans_task_reusable_count_upper_bound,
              active_log_entry_task_count,
              storager_task_count, storager_task_count_upper_bound,
              fetcher_part_trans_task_count, dml_parser_part_trans_task_count,
              committer_ddl_part_trans_task_count + committer_dml_part_trans_task_count,
              br_queue_part_trans_task_count, out_part_trans_task_count,
              resource_collector_part_trans_task_count,
              seq_trans_count, committed_trans_count);
        }
      }

      if (OB_SUCC(ret)) {
        // 1. Traffic control requires fetcher to be suspended
        // 2. The configuration item forces the fetcher to be suspended
        int64_t config_pause_fetcher = TCONF.pause_fetcher;
        if (need_slow_down_fetcher || 0 != config_pause_fetcher) {
          LOG_INFO("[STAT] [FLOW_CONTROL] [CONFIG] [PAUSE_FETCHER]",
              K(need_slow_down_fetcher), K(config_pause_fetcher));
          fetcher_->pause();
        }
        // 3. Recovery fetcher in other cases
        else {
          if (fetcher_->is_paused()) {
            LOG_INFO("[STAT] [FLOW_CONTROL] [RESUME_FETCHER]");
            fetcher_->resume();
          }
        }
      }
    } // else
  } // inited
}

void ObLogInstance::dump_pending_trans_info_()
{
  int ret = OB_SUCCESS;

  if (NULL != trans_ctx_mgr_) {
    const char *file = DEFAULT_PENDING_TRANS_INFO_FILE;
    int fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0600);
    static const int64_t BUFFER_SIZE = 2 << 26;
    char *buffer = static_cast<char *>(ob_log_malloc(BUFFER_SIZE));

    if (OB_UNLIKELY(fd < 0)) {
      LOG_ERROR("open pending trans info file fail", K(file), K(fd),
          K(errno), KERRMSG);
      ret = OB_ERR_UNEXPECTED;
    } else if (OB_ISNULL(buffer)) {
      LOG_ERROR("allocate memory for pending trans info fail", K(BUFFER_SIZE));
      ret = OB_ALLOCATE_MEMORY_FAILED;
    } else {
      int64_t pos = 0;

      (void)databuff_printf(buffer, BUFFER_SIZE, pos, "============================== BEGIN ");
      (void)ObTimeUtility2::usec_to_str(get_timestamp(), buffer, BUFFER_SIZE, pos);
      (void)databuff_printf(buffer, BUFFER_SIZE, pos, " ==============================\n");

      if (OB_FAIL(trans_ctx_mgr_->dump_pending_trans_info(buffer, BUFFER_SIZE, pos))) {
        LOG_ERROR("dump pending trans info fail", KR(ret), K(buffer), K(BUFFER_SIZE), K(pos));
      } else {
        (void)databuff_printf(buffer, BUFFER_SIZE, pos,
            "============================== END ==============================;\n");
      }

      if (OB_SUCC(ret)) {
        int64_t total_size = pos;
        char *ptr = buffer;

        while (OB_SUCC(ret) && total_size > 0) {
          ssize_t nwrite = 0;
          nwrite = write(fd, ptr, static_cast<int>(total_size));

          if (nwrite >= 0) {
            total_size -= nwrite;
            ptr += nwrite;
          } else {
            LOG_ERROR("write pending trans info file fail",
                K(nwrite), K(total_size), K(file), K(fd), K(errno), KERRMSG, KP(ptr));
            ret = OB_IO_ERROR;
            break;
          }
        }
      }
    }

    if (fd >= 0) {
      if (OB_FAIL(fsync(fd))) {
        LOG_ERROR("failed to execute fsync file", K(ret), K(fd));
      } else if (OB_FAIL(close(fd))) {
        LOG_ERROR("failed to execute close file", K(ret), K(fd));
      } else {
        fd = -1;
      }
    }

    if (NULL != buffer) {
      ob_log_free(buffer);
      buffer = NULL;
    }
  }
}

void ObLogInstance::clean_log_()
{
  int64_t cycle_time = log_clean_cycle_time_us_;
  const static int64_t PRINT_TIME_BUF_SIZE = 64;
  const static int64_t CMD_BUF_SIZE = 1024;
  static char print_time_buf[PRINT_TIME_BUF_SIZE];
  static char cmd_buf[CMD_BUF_SIZE];
  static const char *print_time_format = "%Y-%m-%d %H:%i:%s";
  static const char *cmd_time_format = "%Y%m%d%H%i%s";
  static const char *log_file = "removed_log_files";

  if (cycle_time > 0) {
    int64_t print_time_pos = 0;
    int64_t cmd_pos = 0;
    int64_t base_time = get_timestamp() - cycle_time;
    int64_t begin_time = get_timestamp();

    (void)ObTimeUtility2::usec_format_to_str(base_time, print_time_format,
        print_time_buf, PRINT_TIME_BUF_SIZE, print_time_pos);

    (void)databuff_printf(cmd_buf, CMD_BUF_SIZE, cmd_pos,
        "echo `date` > log/%s; base_time=", log_file);

    (void)ObTimeUtility2::usec_format_to_str(base_time, cmd_time_format,
        cmd_buf, CMD_BUF_SIZE, cmd_pos);

    (void)databuff_printf(cmd_buf, CMD_BUF_SIZE, cmd_pos, "; "
        "for file in `find log/ | grep \"liboblog.log.\" | grep -v err`; "
        "do "
        "num=`echo $file | cut -d '.' -f 3`; "
        "if [ $num -lt $base_time ]; "
        "then "
        "echo $file >> log/%s; "
        "rm $file -f; "
        "fi "
        "done", log_file);

    (void)system(cmd_buf);

    _LOG_INFO("[STAT] [CLEAN_LOG] BASE_TIME='%.*s' EXE_TIME=%ld CYCLE_TIME=%ld CMD=%s",
        (int)print_time_pos, print_time_buf, get_timestamp() - begin_time,
        cycle_time, cmd_buf);
  }
}

int64_t ObLogInstance::get_memory_hold_()
{
  return lib::get_memory_used();
}

int64_t ObLogInstance::get_memory_avail_()
{
  return lib::get_memory_avail();
}

int64_t ObLogInstance::get_memory_limit_()
{
  return lib::get_memory_limit();
}

int ObLogInstance::get_task_count_(int64_t &ready_to_seq_task_count,
    int64_t &part_trans_task_resuable_count)
{
  int ret = OB_SUCCESS;
  ready_to_seq_task_count = 0;
  part_trans_task_resuable_count = 0;

  if (OB_ISNULL(fetcher_) || OB_ISNULL(dml_parser_) || OB_ISNULL(formatter_)
      || OB_ISNULL(storager_)
      || OB_ISNULL(sequencer_) || OB_ISNULL(data_processor_) || OB_ISNULL(committer_)
      || OB_ISNULL(ddl_handler_) || OB_ISNULL(resource_collector_)) {
    LOG_ERROR("invalid arguments", K(fetcher_), K(dml_parser_), K(formatter_), K(storager_),
        K(sequencer_), K(data_processor_), K(committer_), K(ddl_handler_), K(resource_collector_));
    ret = OB_ERR_UNEXPECTED;
  } else {
    // I. Get the number of tasks to be processed by each module
    int64_t dml_parser_log_count = 0;
    int64_t formatter_br_count = 0;
    int64_t formatter_log_count = 0;
    int64_t storager_task_count = 0;
    struct IObLogSequencer::SeqStatInfo seq_stat_info;
    int64_t data_processor_task_count = 0;
    int64_t committer_pending_dml_trans_count = committer_->get_dml_trans_count();

    if (OB_FAIL(dml_parser_->get_log_entry_task_count(dml_parser_log_count))) {
      LOG_ERROR("parser get_log_entry_task_count fail", KR(ret), K(dml_parser_log_count));
    } else if (OB_FAIL(formatter_->get_task_count(formatter_br_count, formatter_log_count))) {
      LOG_ERROR("formatter get_task_count fail", KR(ret), K(formatter_br_count), K(formatter_log_count));
    } else {
      storager_->get_task_count(storager_task_count);
      sequencer_->get_task_count(seq_stat_info);
      data_processor_->get_task_count(data_processor_task_count);

      // Count the number of partitioned tasks to be ordered
      ready_to_seq_task_count = dml_parser_log_count + formatter_log_count + storager_task_count;
    }

    // II. Get the number of reusable tasks for each module
    // 1. count by module
    // 2. The number of reusable tasks in the overall partition includes the following components:
    //   (1) tasks held by committer
    //   (2) Tasks held by br_queue
    //   (3) Tasks held by users that have not been returned
    //   (4) tasks held by resource_collector
    if (OB_SUCC(ret)) {
      int64_t committer_ddl_part_trans_task_count = 0;
      int64_t committer_dml_part_trans_task_count = 0;
      int64_t committer_br_count = 0;

      int64_t fetcher_part_trans_task_count = fetcher_->get_part_trans_task_count();
      committer_->get_part_trans_task_count(committer_ddl_part_trans_task_count,
          committer_dml_part_trans_task_count,
          committer_br_count);
      int64_t ddl_handle_part_trans_task_count = ddl_handler_->get_part_trans_task_count();
      int64_t br_queue_part_trans_task_count = br_queue_.get_part_trans_task_count();
      int64_t out_part_trans_task_count = get_out_part_trans_task_count_();
      int64_t resource_collector_part_trans_task_count = resource_collector_->get_part_trans_task_count();
      int64_t dml_br_count_in_user_queue = br_queue_.get_dml_br_count();
      int64_t dml_br_count_output = output_dml_br_count_;

      // Get the number of DDL Binlog Records in the user queue
      int64_t ddl_br_count_in_user_queue = br_queue_.get_ddl_br_count();
      int64_t ddl_br_count_output = output_ddl_br_count_;

      part_trans_task_resuable_count = committer_ddl_part_trans_task_count
        + committer_dml_part_trans_task_count
        + br_queue_part_trans_task_count
        + out_part_trans_task_count
        + resource_collector_part_trans_task_count;

      // Print monitoring items
      if (REACH_TIME_INTERVAL(PRINT_GLOBAL_FLOW_CONTROL_INTERVAL)) {
        _LOG_INFO("------------------------------------------------------------");
        _LOG_INFO("[TASK_COUNT_STAT] [FETCHER] [PART_TRANS_TASK=%ld]", fetcher_part_trans_task_count);
        _LOG_INFO("[TASK_COUNT_STAT] [DML_PARSER] [LOG_TASK=%ld]", dml_parser_log_count);
        _LOG_INFO("[TASK_COUNT_STAT] [DDL_HANDLE] [PART_TRANS_TASK=%ld]", ddl_handle_part_trans_task_count);
        _LOG_INFO("[TASK_COUNT_STAT] [FORMATTER] [BR=%ld LOG_TASK=%ld]", formatter_br_count, formatter_log_count);
        _LOG_INFO("[TASK_COUNT_STAT] [STORAGER] [LOG_TASK=%ld]", storager_task_count);
        _LOG_INFO("[TASK_COUNT_STAT] [SEQUENCER] [PART_TRANS_TASK(QUEUE=%ld TOTAL=[%ld][DDL=%ld DML=%ld HB=%ld])]",
            seq_stat_info.queue_part_trans_task_count_, seq_stat_info.total_part_trans_task_count_,
            seq_stat_info.ddl_part_trans_task_count_, seq_stat_info.dml_part_trans_task_count_, seq_stat_info.hb_part_trans_task_count_);
        _LOG_INFO("[TASK_COUNT_STAT] [DATA_PROCESSIR] [ROW_TASK=%ld]", data_processor_task_count);
        _LOG_INFO("[TASK_COUNT_STAT] [COMMITER] [DML_TRANS=%ld DDL_PART_TRANS_TASK=%ld DML_PART_TRANS_TASK=%ld] BR_COUNT=%ld",
            committer_pending_dml_trans_count,
            committer_ddl_part_trans_task_count,
            committer_dml_part_trans_task_count,
            committer_br_count);
        _LOG_INFO("[TASK_COUNT_STAT] [USER_QUEQUE] [PART_TRANS_TASK=%ld] [DDL_BR=%ld] [DML_BR=%ld]",
            br_queue_part_trans_task_count,
            ddl_br_count_in_user_queue,
            dml_br_count_in_user_queue);
        _LOG_INFO("[TASK_COUNT_STAT] [OUT] [PART_TRANS_TASK=%ld] [DDL_BR=%ld] [DML_BR=%ld]", out_part_trans_task_count,
            ddl_br_count_output, dml_br_count_output);
        _LOG_INFO("[TASK_COUNT_STAT] [RESOURCE_COLLECTOR] [PART_TRANS_TASK=%ld]",
            resource_collector_part_trans_task_count);
      }
    }
  }

  return ret;
}

void ObLogInstance::do_drc_consume_tps_stat_()
{
  if (OB_ISNULL(trans_stat_mgr_)) {
    LOG_ERROR("trans_stat is null", K(trans_stat_mgr_));
  } else {
    trans_stat_mgr_->do_drc_consume_tps_stat();
  }
}

void ObLogInstance::do_drc_consume_rps_stat_()
{
  if (OB_ISNULL(trans_stat_mgr_)) {
    LOG_ERROR("trans_stat is null", K(trans_stat_mgr_));
  } else {
    trans_stat_mgr_->do_drc_consume_rps_stat();
  }
}

void ObLogInstance::do_drc_release_tps_stat_()
{
  if (OB_ISNULL(trans_stat_mgr_)) {
    LOG_ERROR("trans_stat is null", K(trans_stat_mgr_));
  } else {
    trans_stat_mgr_->do_drc_release_tps_stat();
  }
}

void ObLogInstance::do_drc_release_rps_stat_()
{
  if (OB_ISNULL(trans_stat_mgr_)) {
    LOG_ERROR("trans_stat is null", K(trans_stat_mgr_));
  } else {
    trans_stat_mgr_->do_drc_release_rps_stat();
  }
}

void ObLogInstance::do_stat_for_part_trans_task_count_(int record_type,
    int64_t part_trans_task_count,
    bool need_accumulate_stat)
{
  if ((EDDL == record_type) || (EBEGIN == record_type)) {
    if (need_accumulate_stat) {
      // hold by user
      (void)ATOMIC_AAF(&part_trans_task_count_, part_trans_task_count);
    } else {
      // return by user
      (void)ATOMIC_AAF(&part_trans_task_count_, -part_trans_task_count);
    }
  } else {
    // do nothing
  }
}

void ObLogInstance::print_trans_stat_()
{
  if (OB_ISNULL(trans_stat_mgr_)) {
    LOG_ERROR("trans_stat is null", K(trans_stat_mgr_));
  } else {
    trans_stat_mgr_->print_stat_info();
  }
}

int ObLogInstance::init_ob_trace_id_(const char *ob_trace_id_ptr)
{
  int ret = OB_SUCCESS;
  int64_t pos = 0;

  if (OB_ISNULL(ob_trace_id_ptr)) {
    LOG_ERROR("ob_trace_id_ptr is null", K(ob_trace_id_ptr));
    ret = OB_ERR_UNEXPECTED;
  } else if (OB_FAIL(databuff_printf(ob_trace_id_str_, sizeof(ob_trace_id_str_), pos, "%s",
          ob_trace_id_ptr))) {
    LOG_ERROR("databuff_printf ob_trace_id_str_ fail", K(ob_trace_id_str_), K(pos), K(ob_trace_id_ptr));
  } else {
    LOG_INFO("init_ob_trace_id_ succ", K(ob_trace_id_str_), K(ob_trace_id_ptr));
  }

  return ret;
}

int ObLogInstance::query_cluster_info_(ObLogSysTableHelper::ClusterInfo &cluster_info)
{
  int ret = OB_SUCCESS;
  cluster_info.reset();
  bool done = false;

  if (OB_ISNULL(systable_helper_)) {
    LOG_ERROR("systable_helper_ is null", K(systable_helper_));
    ret = OB_ERR_UNEXPECTED;
  } else {
    while (! done && OB_SUCCESS == ret) {
      if (OB_FAIL(systable_helper_->query_cluster_info(cluster_info))) {
        LOG_WARN("systable_helper_ query_cluster_info fail", KR(ret), K(cluster_info));
      } else {
        done = true;
      }

      if (OB_NEED_RETRY == ret) {
        ret = OB_SUCCESS;
        usleep(100L * 1000L);
      }
    }
  }

  return ret;
}

// init cluster version
int ObLogInstance::init_ob_cluster_version_()
{
  int ret = OB_SUCCESS;
  uint64_t min_observer_version = OB_INVALID_ID;

  if (OB_FAIL(query_cluster_min_observer_version_(min_observer_version))) {
    LOG_ERROR("query_cluster_min_observer_version_ fail", KR(ret), K(min_observer_version));
  } else if (OB_FAIL(ObClusterVersion::get_instance().init(min_observer_version))) {
    LOG_ERROR("ObClusterVersion init fail", KR(ret), K(min_observer_version));
  } else {
    LOG_INFO("OceanBase cluster version init succ", "cluster_version", ObClusterVersion::get_instance());
  }

  return ret;
}

// Query the smallest version of the cluster until it succeeds
int ObLogInstance::query_cluster_min_observer_version_(uint64_t &min_observer_version)
{
  int ret = OB_SUCCESS;
  bool done = false;

  if (OB_ISNULL(systable_helper_)) {
    LOG_ERROR("systable_helper_ is null", K(systable_helper_));
    ret = OB_ERR_UNEXPECTED;
  } else {
    while (! done && OB_SUCCESS == ret) {
      if (OB_FAIL(systable_helper_->query_cluster_min_observer_version(min_observer_version))) {
        LOG_WARN("systable_helper_ query_cluster_min_observer_version fail", KR(ret), K(min_observer_version));
      } else {
        done = true;
      }

      if (OB_NEED_RETRY == ret) {
        ret = OB_SUCCESS;
        usleep(100L * 1000L);
      }
    }
  }

  return ret;
}

// update cluster version
void ObLogInstance::update_cluster_version_()
{
  int ret = OB_SUCCESS;
  uint64_t min_observer_version = OB_INVALID_ID;

  if (OB_NOT_NULL(systable_helper_)) {
    if (OB_FAIL(systable_helper_->query_cluster_min_observer_version(min_observer_version))) {
      if (OB_NEED_RETRY == ret) {
        LOG_WARN("systable_helper_ query_cluster_min_observer_version fail", KR(ret), K(min_observer_version));
        ret = OB_SUCCESS;
      } else {
        LOG_ERROR("systable_helper_ query_cluster_min_observer_version fail", KR(ret), K(min_observer_version));
      }
    } else {
      ObClusterVersion::get_instance().update_cluster_version(min_observer_version);
      LOG_INFO("OceanBase cluster version update succ", "cluster_version", ObClusterVersion::get_instance());
    }
  }
}

int ObLogInstance::check_ob_version_legal_(const uint64_t ob_version)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(OB_INVALID_ID == ob_version)) {
    ret = OB_INVALID_DATA;
    LOG_WARN("ob_version is invalid", KR(ret), K(ob_version));
  } else {
    // do nothing
  }
  return ret;
}

int ObLogInstance::check_observer_version_valid_()
{
  int ret = OB_SUCCESS;

  const uint64_t ob_version = GET_MIN_CLUSTER_VERSION();
  uint32_t ob_major = 0;
  uint16_t ob_minor = 0;
  uint16_t ob_patch = 0;
  cal_version_components(ob_version, ob_major, ob_minor, ob_patch);
  if (0 != TCONF.skip_ob_version_compat_check) {
    _LOG_INFO("skip_ob_version_compat_check is true, skip check, observer_version(%u.%hu.%hu)",
        ob_major, ob_minor, ob_patch);
  } else if (OB_FAIL(check_ob_version_legal_(ob_version))) {
    _LOG_WARN("check ob version illegal, observer_version(%u.%hu.%hu), skip it",
        ob_major, ob_minor, ob_patch);
    ret = OB_SUCCESS;
  } else if ((oblog_major_ >=3 && ob_major == 1)) {
    ret = OB_VERSION_NOT_MATCH;
    _LOG_ERROR("oblog_version(%u.%hu.%hu) don't support observer_version(%u.%hu.%hu)",
        oblog_major_, oblog_minor_, oblog_patch_, ob_major, ob_minor, ob_patch);
  } else if (oblog_major_ > ob_major
      || (oblog_major_ == ob_major && oblog_minor_ >= ob_minor)) {
    _LOG_INFO("oblog_version(%u.%hu.%hu) compatible with observer_version(%u.%hu.%hu)",
        oblog_major_, oblog_minor_, oblog_patch_, ob_major, ob_minor, ob_patch);
  } else {
    ret = OB_VERSION_NOT_MATCH;
    _LOG_ERROR("oblog_version(%u.%hu.%hu) not compatible with observer_version(%u.%hu.%hu), "
        "oblog_version is too old, need upgrade",
        oblog_major_, oblog_minor_, oblog_patch_, ob_major, ob_minor, ob_patch);
  }

  return ret;
}

void ObLogInstance::init_global_context_()
{
   // The schema module relies on this value to determine the working mode, setting it to invalid means old mode is used.
   // For versions below 2.2, liboblog should start in old mode, and switch schema working mode when schema splitting is detected.
   // For version 2.2 or higher, liboblog can start in new mode.
   (void)GCTX.set_split_schema_version(OB_INVALID_VERSION);
   (void)GCTX.set_split_schema_version_v2(OB_INVALID_VERSION);

   // There is no need for liboblog to connect to a backup library, if there is, the value should be maintained.
   share::ObClusterInfo cluster_info;
   share::ObRedoTransportOption redo_option;
   ObSEArray<int64_t, 1> sync_cluster_id;
   cluster_info.cluster_type_ = PRIMARY_CLUSTER;
   cluster_info.cluster_id_ = 1;
   cluster_info.set_switch_timestamp(1);
   cluster_info.version_ = 1;
}

int ObLogInstance::init_oblog_version_components_()
{
  int ret = OB_SUCCESS;
  uint64_t oblog_version = 0;
  if (OB_FAIL(ObClusterVersion::get_version(PACKAGE_VERSION, oblog_version))) {
    LOG_ERROR("get_version fail", KR(ret), K(PACKAGE_VERSION), K(oblog_version));
  } else {
    cal_version_components(oblog_version, oblog_major_, oblog_minor_, oblog_patch_);
  }

  if (OB_SUCC(ret)) {
    LOG_INFO("init oblog_version components succ", K(PACKAGE_VERSION), K(oblog_version),
        K(oblog_major_), K(oblog_minor_), K(oblog_patch_));
  }
  return ret;
}

int ObLogInstance::get_tenant_guard(const uint64_t tenant_id, ObLogTenantGuard &guard)
{
  int ret = OB_SUCCESS;
  if (OB_ISNULL(tenant_mgr_)) {
    LOG_ERROR("tenant_mgr is NULL", K(tenant_mgr_));
    ret = OB_ERR_UNEXPECTED;
  } else if (OB_FAIL(tenant_mgr_->get_tenant_guard(tenant_id, guard))) {
    if (OB_ENTRY_NOT_EXIST != ret) {
      LOG_ERROR("get_tenant_guard fail", KR(ret), K(tenant_id), K(guard));
    }
  } else {
    // success
  }
  return ret;
}

}
}
