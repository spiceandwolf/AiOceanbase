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

#ifndef OCEANBASE_LIBOBLOG_CONFIG_H__
#define OCEANBASE_LIBOBLOG_CONFIG_H__

#include <map>
#include "share/ob_define.h"
#include "share/parameter/ob_parameter_macro.h"
#include "share/config/ob_common_config.h"    // ObInitConfigContainer

#include "ob_log_common.h"
#include "ob_log_fake_common_config.h"        // ObLogFakeCommonConfig

////////////// Define member variables of type INT, no limit on maximum value //////////////
// DEF: default value
// MIN: minimum value
//
// Note: DEF, MIN must be literal values, not variable names
#define T_DEF_INT_INFT(name, SCOPE, DEF, MIN, NOTE) \
    public: \
      static const int64_t default_##name = (DEF); \
      DEF_INT(name, SCOPE, #DEF, "[" #MIN ",]", NOTE);

////////////// Define INT type member variable //////////////
// DEF: default value
// MIN: minimum value
// MAX: maximum value
//
// Note: DEF, MIN, MAX must be literal values, not variable names
#define T_DEF_INT(name, SCOPE, DEF, MIN, MAX, NOTE) \
    public: \
      static const int64_t default_##name = (DEF); \
      static const int64_t max_##name = (MAX); \
      DEF_INT(name, SCOPE, #DEF, "[" #MIN "," #MAX "]", NOTE);

////////////// Define INT type member variable //////////////
// DEF: default value, 0 or 1
//
// Note: DEF must be a literal value, not a variable name
#define T_DEF_BOOL(name, SCOPE, DEF, NOTE) \
    public: \
      static const int64_t default_##name = DEF; \
      DEF_INT(name, SCOPE, #DEF, "[0,1]", NOTE);

namespace oceanbase
{
namespace liboblog
{
class ObLogConfig : public common::ObInitConfigContainer
{
  typedef std::map<std::string, std::string> ConfigMap;

public:
  ObLogConfig() : inited_(false), common_config_(), config_file_buf1_(NULL), config_file_buf2_(NULL)
  {
    rpc_tenant_id = common::OB_EXT_LOG_TENANT_ID;
  }

  virtual ~ObLogConfig() { destroy(); }

  int init();
  void destroy();
  static ObLogConfig &get_instance();

public:
  int check_all();
  void print() const;
  int load_from_buffer(const char *config_str,
      const int64_t config_str_len,
      const int64_t version = 0,
      const bool check_name = false);
  int load_from_file(const char *config_file,
      const int64_t version = 0,
      const bool check_name = false);
  int load_from_map(const ConfigMap& configs,
      const int64_t version = 0,
      const bool check_name = false);
  int dump2file(const char *file) const;

  common::ObCommonConfig &get_common_config() { return common_config_; }

  // remove quotes of cluster_url
  int format_cluster_url();

public:

#ifdef OB_CLUSTER_PARAMETER
#undef OB_CLUSTER_PARAMETER
#endif
#define OB_CLUSTER_PARAMETER(args...) args
  // Liboblog config.
  // max memory occupied by liboblog: 20G
  DEF_CAP(memory_limit, OB_CLUSTER_PARAMETER, "20G", "[2G,]", "memory limit");
  // Preserve the lower bound of system memory in %, in the range of 10% ~ 80%
  // i.e.: ensure that the system memory remaining cannot be lower than this percentage based on the memory occupied by liboblog
  DEF_INT(system_memory_avail_percentage_lower_bound, OB_CLUSTER_PARAMETER, "10", "[10, 80]", "system memory avail upper bound");
  DEF_CAP(tenant_manager_memory_upper_limit, OB_CLUSTER_PARAMETER, "5G", "[1G,]", "tenant manager memory upper limit");
  DEF_INT(dml_parser_thread_num, OB_CLUSTER_PARAMETER, "5", "[1,]", "DML parser thread number");
  DEF_INT(ddl_parser_thread_num, OB_CLUSTER_PARAMETER, "1", "[1,]", "DDL parser thread number");
  DEF_INT(sequencer_thread_num, OB_CLUSTER_PARAMETER, "5", "[1,]", "sequencer thread number");
  DEF_INT(sequencer_queue_length, OB_CLUSTER_PARAMETER, "102400", "[1,]", "sequencer queue length");
  DEF_INT(formatter_thread_num, OB_CLUSTER_PARAMETER, "10", "[1,]", "formatter thread number");
  DEF_INT(formatter_batch_stmt_count, OB_CLUSTER_PARAMETER, "100", "[1,]", "formatter batch stmt count");
  DEF_INT(committer_queue_length, OB_CLUSTER_PARAMETER, "102400", "[1,]", "committer queue length");
  DEF_INT(committer_thread_num, OB_CLUSTER_PARAMETER, "1", "[1,]", "committer thread number");
  DEF_INT(storager_thread_num, OB_CLUSTER_PARAMETER, "10", "[1,]", "storager thread number");
  DEF_INT(storager_queue_length, OB_CLUSTER_PARAMETER, "102400", "[1,]", "storager queue length");
  DEF_INT(data_processor_thread_num, OB_CLUSTER_PARAMETER, "10", "[1,]", "data_processor thread number");
  DEF_INT(data_processor_queue_length, OB_CLUSTER_PARAMETER, "102400", "[1,]", "data_processor queue length");
  DEF_INT(cached_schema_version_count, OB_CLUSTER_PARAMETER, "32", "[1,]", "cached schema version count");
  DEF_INT(history_schema_version_count, OB_CLUSTER_PARAMETER, "16", "[1,]", "history schema version count");
  DEF_INT(resource_collector_thread_num, OB_CLUSTER_PARAMETER, "10", "[1,]", "resource collector thread number");
  DEF_INT(resource_collector_thread_num_for_br, OB_CLUSTER_PARAMETER, "7", "[1,]", "binlog record resource collector thread number");
  DEF_INT(instance_num, OB_CLUSTER_PARAMETER, "1", "[1,]", "store instance number");
  DEF_INT(instance_index, OB_CLUSTER_PARAMETER, "0", "[0,]", "store instance index, start from 0");
  DEF_INT(part_trans_task_prealloc_count, OB_CLUSTER_PARAMETER, "300000", "[1,]",
      "partition trans task pre-alloc count");
  DEF_INT(part_trans_task_active_count_upper_bound, OB_CLUSTER_PARAMETER, "200000", "[1,]",
      "active partition trans task count upper bound");
  DEF_INT(storager_task_count_upper_bound, OB_CLUSTER_PARAMETER, "1000", "[1,]",
      "storager task count upper bound");
  DEF_INT(storager_mem_percentage, OB_CLUSTER_PARAMETER, "2", "[1,]",
      "storager memory percentage");
  T_DEF_BOOL(skip_recycle_data, OB_CLUSTER_PARAMETER, 0, "0:not_skip, 1:skip")
  DEF_INT(part_trans_task_reusable_count_upper_bound, OB_CLUSTER_PARAMETER, "10240", "[1,]",
      "reusable partition trans task count upper bound");
  DEF_INT(ready_to_seq_task_upper_bound, OB_CLUSTER_PARAMETER, "20000", "[1,]",
      "ready to sequencer task count upper bound");
  DEF_INT(part_trans_task_dynamic_alloc, OB_CLUSTER_PARAMETER, "1", "[0,1]", "partition trans task dynamic alloc");
  DEF_CAP(part_trans_task_page_size, OB_CLUSTER_PARAMETER, "8KB", "[1B,]", "partition trans task page size");
  DEF_INT(part_trans_task_prealloc_page_count, OB_CLUSTER_PARAMETER, "20000", "[1,]",
      "partition trans task prealloc page count");
  // Log_level=INFO in the startup scenario, and then optimize the schema to WARN afterwards
  DEF_STR(init_log_level, OB_CLUSTER_PARAMETER, "ALL.*:INFO;SHARE.SCHEMA:INFO", "log level: DEBUG, TRACE, INFO, WARN, USER_ERR, ERROR");
  DEF_STR(log_level, OB_CLUSTER_PARAMETER, "ALL.*:INFO;SHARE.SCHEMA:WARN", "log level: DEBUG, TRACE, INFO, WARN, USER_ERR, ERROR");
  // root server info for oblog, seperated by `;` between multi rootserver, a root server info format as `ip:rpc_port:sql_port`
  DEF_STR(rootserver_list, OB_CLUSTER_PARAMETER, "|", "OB RootServer list");
  DEF_STR(cluster_url, OB_CLUSTER_PARAMETER, "|", "OB configure url");
  DEF_STR(cluster_user, OB_CLUSTER_PARAMETER, "", "OB login user");
  DEF_STR(cluster_password, OB_CLUSTER_PARAMETER, "", "OB login password");
  DEF_STR(cluster_db_name, OB_CLUSTER_PARAMETER, "oceanbase", "OB login database name");
  DEF_STR(config_fpath, OB_CLUSTER_PARAMETER, DEFAULT_CONFIG_FPATN, "configuration file path");
  DEF_STR(timezone, OB_CLUSTER_PARAMETER, DEFAULT_TIMEZONE_INFO, "timezone info");
  // tenant_name.db_name.table_name
  DEF_STR(tb_white_list, OB_CLUSTER_PARAMETER, "*.*.*", "tb-select white list");
  DEF_STR(tb_black_list, OB_CLUSTER_PARAMETER, "|", "tb-select black list");
  // tenant_name.tablegroup_name
  DEF_STR(tablegroup_white_list, OB_CLUSTER_PARAMETER, "*.*", "tablegroup-select white list");
  DEF_STR(tablegroup_black_list, OB_CLUSTER_PARAMETER, "|", "tablegroup-select black list");

  DEF_STR(data_start_schema_version, OB_CLUSTER_PARAMETER, "|", "tenant:schema_version");
  // cluster id black list, using vertical line separation, for example cluster_id_black_list=100|200|300
  // Default value: 2^31 - 10000, this is a special cluster ID agreed in OCP for deleting historical data scenarios
  // liboblog filters REDO data from deleted historical data scenarios by default
  DEF_STR(cluster_id_black_list, OB_CLUSTER_PARAMETER, "2147473648", "cluster id black list");

  // minimum value of default cluster id blacklist value
  // The minimum value is: 2^31 - 10000 = 2147473648
  // This definition can only be a literal value
  T_DEF_INT_INFT(cluster_id_black_value_min, OB_CLUSTER_PARAMETER, 2147473648, 1, "min cluster id black value");

  // The maximum value of the default cluster id blacklist value
  // Maximum value: 2^31 - 1 = 2147483647
  // This definition can only be a literal value
  T_DEF_INT_INFT(cluster_id_black_value_max, OB_CLUSTER_PARAMETER, 2147483647, 1, "max cluster id black value");

  DEF_INT(log_entry_task_prealloc_count, OB_CLUSTER_PARAMETER, "100000", "[1,]", "log entry task pre-alloc count");

  DEF_INT(binlog_record_prealloc_count, OB_CLUSTER_PARAMETER, "100000", "[1,]", "binlog record pre-alloc count");

  DEF_STR(store_service_path, OB_CLUSTER_PARAMETER, "./storage", "store sevice path");

  // Whether to do ob version compatibility check
  // default value '0:not_skip'
  T_DEF_BOOL(skip_ob_version_compat_check, OB_CLUSTER_PARAMETER, 0, "0:not_skip, 1:skip")

  // default DFT_BR(LogRecordImpl), add DFT_BR_PB
  // passed in via IObLog::init interface
  // string LogMsgFactory::DFT_ColMeta = "ColMetaImpl";
  // string LogMsgFactory::DFT_TableMeta = "TableMetaImpl";
  // string LogMsgFactory::DFT_DBMeta = "DBMetaImpl";
  // string LogMsgFactory::DFT_METAS = "MetaDataCollectionsImpl";
  // string LogMsgFactory::DFT_BR = "LogRecordImpl";
  // string LogMsgFactory::DFT_BR_PB = "BinlogRecordProtobuf";
  DEF_STR(drc_message_factory_binlog_record_type, OB_CLUSTER_PARAMETER, "LogRecordImpl", "LogMsgFactory::DFT_BR");

  // whether to check ObTraceId
  T_DEF_BOOL(need_verify_ob_trace_id, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  // ObTraceId, Configurable, default is default
  DEF_STR(ob_trace_id, OB_CLUSTER_PARAMETER, "default", "ob trace id");
  // Whether to turn on the verification mode
  // 1. verify dml unique id
  // 2. Verify ddl binlog record: schema version
  T_DEF_BOOL(enable_verify_mode, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  DEF_INT(enable_dump_pending_trans_info, OB_CLUSTER_PARAMETER, "0", "[0,1]",
      "enable dump pending transaction information");

  DEF_INT(log_clean_cycle_time_in_hours, OB_CLUSTER_PARAMETER, "24", "[0,]",
      "clean log cycle time in hours, 0 means not to clean log");

  T_DEF_BOOL(skip_dirty_data, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  T_DEF_BOOL(skip_reversed_schema_verison, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  T_DEF_BOOL(skip_rename_tenant_ddl, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to sort the list of participants within a distributed transaction
  // Scenario: online business does not need to enable this configuration item; this configuration item is only for obtest test scenario.
  // After each restart of obtest, the list of participants in the observer is random. In order to ensure consistent case results,
  // the list of participants needs to be sorted to ensure consistent results each time
  T_DEF_BOOL(sort_trans_participants, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to allow globally unique indexes to be located in multiple instances
  // For example, in a count bin scenario, there is no strong reliance on global unique indexes to resolve dependencies
  T_DEF_BOOL(enable_global_unique_index_belong_to_multi_instance, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  ////////////////////////////// Fetcher config //////////////////////////////
  //
  // ------------------------------------------------------------------------
  //          Configurations that do not support dynamic changes
  // ------------------------------------------------------------------------
  // liboblog support multiple working mode, default is storage
  // 1. storage: transaction data is stored, can support large transactions
  // 2. memory: transaction data is not stored, it means better performance, but may can not support large transactions
  DEF_STR(working_mode, OB_CLUSTER_PARAMETER, "storage", "liboblog working mode");
  T_DEF_INT_INFT(rocksdb_write_buffer_size, OB_CLUSTER_PARAMETER, 64, 16, "write buffer size[M]");

  T_DEF_BOOL(fetcher_mock_mode, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  T_DEF_INT_INFT(io_thread_num, OB_CLUSTER_PARAMETER, 4, 1, "io thread number");
  T_DEF_INT_INFT(rpc_tenant_id, OB_CLUSTER_PARAMETER, 1, 1, "tenant id used in rpc");
  T_DEF_INT(svr_finder_thread_num, OB_CLUSTER_PARAMETER, 4, 1, 32, "svr finder thread num");
  T_DEF_INT(fetcher_heartbeat_thread_num, OB_CLUSTER_PARAMETER, 4, 1, 32, "fetcher heartbeat thread num");
  T_DEF_INT(idle_pool_thread_num, OB_CLUSTER_PARAMETER, 4, 1, 32, "idle pool thread num");
  T_DEF_INT(dead_pool_thread_num, OB_CLUSTER_PARAMETER, 1, 1, 32, "dead pool thread num");
  T_DEF_INT(stream_worker_thread_num, OB_CLUSTER_PARAMETER, 8, 1, 64, "stream worker thread num");
  T_DEF_INT(start_log_id_locator_thread_num, OB_CLUSTER_PARAMETER, 4, 1, 32, "start log id locator thread num");
  T_DEF_INT_INFT(start_log_id_locator_locate_count, OB_CLUSTER_PARAMETER, 3, 1, "start log id locator locate count");
  // Whether to skip the starting log ID positioning result consistency check, i.e. whether there is a positioning log bias scenario
  T_DEF_BOOL(skip_start_log_id_locator_result_consistent_check, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  T_DEF_INT_INFT(svr_stream_cached_count, OB_CLUSTER_PARAMETER, 16, 1, "cached svr stream object count");
  T_DEF_INT_INFT(fetch_stream_cached_count, OB_CLUSTER_PARAMETER, 16, 1, "cached fetch stream object count");

  // region
  DEF_STR(region, OB_CLUSTER_PARAMETER, "default_region", "OB region");

  // Number of globally cached RPC results
  T_DEF_INT_INFT(rpc_result_cached_count, OB_CLUSTER_PARAMETER, 16, 1, "cached rpc result object count");

  // Number of active partitions in memory
  // This value can be used as a reference for the number of data structure objects cached at the partition level
  T_DEF_INT_INFT(active_partition_count, OB_CLUSTER_PARAMETER, 10000, 1, "active partition count in memory");

  // Maximum number of partitions currently supported
  T_DEF_INT_INFT(partition_count_upper_limit, OB_CLUSTER_PARAMETER, 2000000, 1, "max partition count supported");

  // Maximum number of threads using systable helper
  T_DEF_INT(access_systable_helper_thread_num, OB_CLUSTER_PARAMETER, 64, 48, 1024, "access systable helper thread num");

  // Global starting schema version, all tenants set to one version, only valid for schema non-split mode
  T_DEF_INT_INFT(global_data_start_schema_version, OB_CLUSTER_PARAMETER, 0, 0,
      "data start schema version for all tenant");
  // ------------------------------------------------------------------------


  // ------------------------------------------------------------------------
  //              configurations which supports dynamically modify
  // ------------------------------------------------------------------------
  T_DEF_INT_INFT(mysql_connect_timeout_sec, OB_CLUSTER_PARAMETER, 40, 1, "mysql connection timeout in seconds");
  T_DEF_INT_INFT(mysql_query_timeout_sec, OB_CLUSTER_PARAMETER, 30, 1, "mysql query timeout in seconds");
  T_DEF_INT_INFT(start_log_id_locator_rpc_timeout_sec, OB_CLUSTER_PARAMETER, 60, 1,
      "start log id locator rpc timeout in seconds");
  T_DEF_INT_INFT(start_log_id_locator_batch_count, OB_CLUSTER_PARAMETER, 2000, 1, "start log id locator batch count");
  T_DEF_INT(svr_finder_sql_batch_count, OB_CLUSTER_PARAMETER, 1, 1, 200, "svr_finder sql batch count");

  // server blacklist, default is|,means no configuration, support configuration single/multiple servers
  // Single: SEVER_IP1:PORT1
  // Multiple: SEVER_IP1:PORT1|SEVER_IP2:PORT2|SEVER_IP3:PORT3
  DEF_STR(server_blacklist, OB_CLUSTER_PARAMETER, "|", "server black list");
  DEF_STR(sql_server_blacklist, OB_CLUSTER_PARAMETER, "|", "sql server black list");

  T_DEF_INT_INFT(heartbeater_rpc_timeout_sec, OB_CLUSTER_PARAMETER, 60, 1, "heartbeater rpc timeout in seconds");
  T_DEF_INT_INFT(heartbeater_batch_count, OB_CLUSTER_PARAMETER, 2000, 1, "heartbeater batch count");
  T_DEF_INT_INFT(svr_list_update_interval_sec, OB_CLUSTER_PARAMETER, 600, 1, "svr list update interval in seconds");
  T_DEF_INT_INFT(leader_info_update_interval_sec, OB_CLUSTER_PARAMETER, 600, 1, "leader update interval in seconds");
  T_DEF_INT_INFT(heartbeat_interval_sec, OB_CLUSTER_PARAMETER, 1, 1, "leader update interval in seconds");

  T_DEF_INT_INFT(stream_life_time_sec, OB_CLUSTER_PARAMETER, 60, 1, "fetch log stream life time in seconds");
  T_DEF_INT_INFT(stream_max_partition_count, OB_CLUSTER_PARAMETER, 5000, 1, "fetch log stream max partition count");
  T_DEF_INT_INFT(stream_feedback_interval_sec, OB_CLUSTER_PARAMETER, 3, 0,
      "fetch log stream feedback interval in seconds, 0 means need feedback info always");
  T_DEF_INT_INFT(fetch_log_rpc_timeout_sec, OB_CLUSTER_PARAMETER, 15, 1, "fetch log rpc timeout in seconds");
  T_DEF_INT_INFT(fetch_log_cnt_per_part_per_round, OB_CLUSTER_PARAMETER, 8000, 1,
      "fetch log count in one rpc for one partition in one round");

  // Maximum observer log retention time in minutes
  // Used to start the logging locating process, if all servers return less than the lower bound and
  // the start timestamp is within the log saving time, we consider it possible to force a start.
  // Doing so can greatly alleviate the startup failure problem caused by 2.0 restarting liboblog
  T_DEF_INT_INFT(observer_clog_save_time_minutes, OB_CLUSTER_PARAMETER, 120, 1, "observer clog save time in minutes");

  // Forced start mode, used for operation and maintenance processing
  // Auto-start mode can take effect only when all servers return OB_ERR_OUT_OF_LOWER_BOUND
  // Forced start mode, only requires at least one server to return OB_ERR_OUT_OF_LOWER_BOUND
  // default off
  T_DEF_BOOL(enable_force_start_mode, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Upper limit of progress difference between partitions, in seconds
  T_DEF_INT_INFT(progress_limit_sec_for_dml, OB_CLUSTER_PARAMETER, 3, 1, "dml progress limit in seconds");
  T_DEF_INT_INFT(progress_limit_sec_for_ddl, OB_CLUSTER_PARAMETER, 3600, 1, "ddl progress limit in seconds");


  // Partition timeout in seconds
  // If the logs are not fetched after a certain period of time, the stream will be cut
  T_DEF_INT_INFT(partition_timeout_sec, OB_CLUSTER_PARAMETER, 15, 1, "partition timeout in seconds");
  // Timeout time for partitions for lagging copies
  //
  // If logs are not fetched for more than a certain period of time on a lagging copy, cut the stream
  T_DEF_INT_INFT(partition_timeout_sec_for_lagged_replica, OB_CLUSTER_PARAMETER, 3, 1,
      "partition timeout for lagged replica in seconds");

	// cache update interval of sys table __all_server
  T_DEF_INT_INFT(all_server_cache_update_interval_sec, OB_CLUSTER_PARAMETER, 5, 1,
			           "__all_server table cache update internal in seconds");

	// cache update interval of sys table __all_zone
  T_DEF_INT_INFT(all_zone_cache_update_interval_sec, OB_CLUSTER_PARAMETER, 5, 1,
			           "__all_zone table cache update internal in seconds");

  // pause fetcher
  T_DEF_BOOL(pause_fetcher, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Maximum number of tasks supported by the timer
  T_DEF_INT_INFT(timer_task_count_upper_limit, OB_CLUSTER_PARAMETER, 1024, 1, "max timer task count");
  // Timer task timing time
  T_DEF_INT_INFT(timer_task_wait_time_msec, OB_CLUSTER_PARAMETER, 100, 1, "timer task wait time in milliseconds");

  // the upper limit observer takes  for the log rpc processing time
  // Print RPC chain statistics logs if this limit is exceeded
  T_DEF_INT_INFT(rpc_process_handler_time_upper_limit_msec, OB_CLUSTER_PARAMETER, 200, 1,
      "observer fetch log rpc process handler timer upper limit");

  // Survival time of server to blacklist, in seconds
  T_DEF_INT_INFT(blacklist_survival_time_sec, OB_CLUSTER_PARAMETER, 30, 1, "blacklist-server surival time in seconds");

  // The maximum time the server can be blacklisted, in minutes
  T_DEF_INT_INFT(blacklist_survival_time_upper_limit_min, OB_CLUSTER_PARAMETER, 4, 1, "blacklist-server survival time upper limit in minute");

  // The server is blacklisted in the partition, based on the time of the current server service partition - to decide whether to penalize the survival time
  // When the service time is less than a certain interval, a doubling-live-time policy is adopted
  // Unit: minutes
  T_DEF_INT_INFT(blacklist_survival_time_penalty_period_min, OB_CLUSTER_PARAMETER, 1, 1, "blacklist survival time punish interval in minute");

  // Blacklist history expiration time, used to delete history
  T_DEF_INT_INFT(blacklist_history_overdue_time_min, OB_CLUSTER_PARAMETER, 30, 10, "blacklist history overdue in minute");

  // Clear blacklist history period, unit: minutes
  T_DEF_INT_INFT(blacklist_history_clear_interval_min, OB_CLUSTER_PARAMETER, 20, 10, "blacklist history clear interval in minute");

  // Check the need for active cut-off cycles, in minutes
  T_DEF_INT_INFT(check_switch_server_interval_min, OB_CLUSTER_PARAMETER, 30, 1, "check switch server interval in minute");

  // Print the number of partitions with the slowest progress of the Fetcher module
  T_DEF_INT_INFT(print_fetcher_slowest_part_num, OB_CLUSTER_PARAMETER, 10, 1, "print fetcher slowest partition num");

  // Maximum number of RPC results per RPC
  T_DEF_INT_INFT(rpc_result_count_per_rpc_upper_limit, OB_CLUSTER_PARAMETER, 16, 1,
      "max rpc result count per rpc");

  // Whether to print RPC processing information
  // Print every RPC processing
  // No printing by default
  T_DEF_BOOL(print_rpc_handle_info, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  T_DEF_BOOL(print_stream_dispatch_info, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // ------------------------------------------------------------------------
  // Print partition heartbeat information
  T_DEF_BOOL(print_partition_heartbeat_info, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  // Print partition service information
  T_DEF_BOOL(print_partition_serve_info, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  // Print partition not in service information
  T_DEF_BOOL(print_participant_not_serve_info, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  // Print the svr list of each partition update, off by default
  T_DEF_BOOL(print_partition_server_list_update_info, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  // Whether to use the new partitioning algorithm
  // Enabled by default, according to the new partitioning method: table_id+part_id
  // Temporarily keep the old partitioning method with rollback capability
  T_DEF_BOOL(enable_new_partition_hash_algorithm, OB_CLUSTER_PARAMETER, 1, "0:disabled, 1:enabled");
  // Whether to sequentially output within a transaction
  // Not on by default (partition-by-partition output)
  T_DEF_BOOL(enable_output_trans_order_by_sql_operation, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");
  // ------------------------------------------------------------------------
  // Test mode, used only in obtest and other test tool scenarios
  T_DEF_BOOL(test_mode_on, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether check tenant status for each schema request with tenant_id under test mode, default disabled
  T_DEF_BOOL(test_mode_force_check_tenant_status, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to allow the output of the current transaction's major_version in test mode, not allowed by default
  T_DEF_BOOL(test_output_major_version, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // The number of times sqlServer cannot get the rs list in test mode
  T_DEF_INT_INFT(test_mode_block_sqlserver_count, OB_CLUSTER_PARAMETER, 0, 0,
      "mock times of con't get rs list under test mode");

  // Number of REDO logs ignored in test mode
  T_DEF_INT_INFT(test_mode_ignore_redo_count, OB_CLUSTER_PARAMETER, 0, 0,
      "ignore redo log count under test mode");

  // Test checkpoint mode, used only in obtest and other test tool scenarios
  T_DEF_BOOL(test_checkpoint_mode_on, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // test mode, whether to block the participant list confirmation process, and if so, how long to block
  // Equal to 0, means no blocking
  // greater than 0 means blocking time in seconds
  //
  // The purpose is to delay the participant list confirmation process and wait for the participant information to be confirmed before operating
  T_DEF_INT_INFT(test_mode_block_verify_participants_time_sec, OB_CLUSTER_PARAMETER, 0, 0,
      "time in seconds to block to verify participants list");

  // test mode, whether blocking committer processing task, if blocking, how long to block
  // equal to 0, means no blocking
  // greater than 0, means blocking time in seconds
  //
  // test drop tenant, committer processing task delayed, wait long enough to ensure tenant structure can be deleted
  T_DEF_INT_INFT(test_mode_block_committer_handle_time_sec, OB_CLUSTER_PARAMETER, 0, 0,
      "time in seconds to block to verify tenant has been dropped");

  // In test mode, set the upper limit of the number of tasks consumed by the committer at one time
  T_DEF_INT_INFT(test_mode_committer_handle_trans_count_upper_limit, OB_CLUSTER_PARAMETER, 0, 0,
      "commiter handle trans count upper limit under test mode");

  // test mode, whether blocking create table DDL, if blocking, how long blocking
  // Equal to 0, means no blocking
  // greater than 0 means blocking time in seconds
  //
  // The purpose is to block the create table DDL, test PG filtering
  T_DEF_INT_INFT(test_mode_block_create_table_ddl_sec, OB_CLUSTER_PARAMETER, 0, 0,
      "time in seconds to block to create table");

  // test mode, whether blocking alter table DDL, if blocking, how long blocking
  // Equal to 0, means no blocking
  // greater than 0 means blocking time in seconds
  //
  // The purpose is to block alter table DDL, test PG filtering
  T_DEF_INT_INFT(test_mode_block_alter_table_ddl_sec, OB_CLUSTER_PARAMETER, 0, 0,
      "time in seconds to block to alter table");

  // test mode, whether blocking filter row process, if blocking, how long to block
  // Equal to 0, means no blocking
  // greater than 0, means blocking time in seconds
  //
  // The purpose is to block filter row, test PG filtering
  T_DEF_INT_INFT(test_mode_block_parser_filter_row_data_sec, OB_CLUSTER_PARAMETER, 0, 0,
      "time in seconds to block to filter row data");

  // INNER_HEARTBEAT_INTERVAL
  T_DEF_INT_INFT(output_inner_heartbeat_interval_msec, OB_CLUSTER_PARAMETER, 100, 1, "output heartbeat interval in seconds");

  // Output heartbeat interval to external, default 3s
  T_DEF_INT_INFT(output_heartbeat_interval_sec, OB_CLUSTER_PARAMETER, 3, 1, "output heartbeat interval in seconds");

  // Whether to have incremental backup mode
  // Off by default; if it is, then incremental backup mode
  T_DEF_BOOL(enable_backup_mode, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to expose no primary key table hidden primary key to the public
  // 1. DRC linking is off by default; if it is in effect, output the hidden primary key
  // 2. Backup is on by default
  T_DEF_BOOL(enable_output_hidden_primary_key, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Ignore inconsistencies in the number of HBase mode put columns or not
  // Do not skip by default
  T_DEF_BOOL(skip_hbase_mode_put_column_count_not_consistency, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to ignore the transaction log for exceptions
  // Do not skip by default
  T_DEF_BOOL(skip_abnormal_trans_log, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to allow hbase schema to take effect
  // off by default; if it is, then convert the hbase table T timestamp field to a positive number
  T_DEF_BOOL(enable_hbase_mode, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to allow timestamp->utc integer time
  // 1. off by default, the timestamp field is converted to year-month-day format based on time zone information.
  // 2. When configured on, the timestamp field is synchronized to integer
  T_DEF_BOOL(enable_convert_timestamp_to_unix_timestamp, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Whether to output invisible columns externally
  // 1. DRC link is off by default; if valid, output hidden primary key
  // 2. Backup is on by default
  T_DEF_BOOL(enable_output_invisible_column, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // The point in time when the sql server used for querying in SYSTABLE HELPER changes, i.e., the periodic rotation of the sql server
  T_DEF_INT_INFT(sql_server_change_interval_sec, OB_CLUSTER_PARAMETER, 60, 1,
      "change interval of sql server in seconds");

  // Check if version matches, default 600s
  T_DEF_INT_INFT(cluster_version_refresh_interval_sec, OB_CLUSTER_PARAMETER, 600, 1, "cluster version refresh interval in seconds");

  // Oracle mode table/database may have case, and case sensitive
  // default enable_oracle_mode_match_case_sensitive=0 whitelist match is consistent with mysql behavior, match is not sensitive
  // enable_oracle_mode_match_case_sensitive=1 allow match sensitive
  T_DEF_BOOL(enable_oracle_mode_match_case_sensitive, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

   // Switch: Whether to format the module to print the relevant logs
  // No printing by default
  T_DEF_BOOL(enable_formatter_print_log, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // switch: whether to get the tenant schema version
  // Not on by default
  T_DEF_BOOL(enable_get_tenant_refreshed_schema_version, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // Switch: Whether to enable SSL authentication: including MySQL and RPC
  // Disabled by default
  T_DEF_BOOL(ssl_client_authentication, OB_CLUSTER_PARAMETER, 0, "0:disabled, 1:enabled");

  // SSL external kms info
  // 1. Local file mode: ssl_external_kms_info=file
  DEF_STR(ssl_external_kms_info, OB_CLUSTER_PARAMETER, "|", "ssl external kms info");

#undef OB_CLUSTER_PARAMETER

private:
  static const int64_t OBLOG_MAX_CONFIG_LENGTH = 5 * 1024 * 1024;  // 5M

private:
  bool                  inited_;
  ObLogFakeCommonConfig common_config_;

  // for load_from_file
  char                  *config_file_buf1_;
  // for load_from_buffer
  char                  *config_file_buf2_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObLogConfig);
};

#define TCONF (::oceanbase::liboblog::ObLogConfig::get_instance())

} // namespace liboblog
} // namespace oceanbase
#endif /* OCEANBASE_LIBOBLOG_CONFIG_H__ */
