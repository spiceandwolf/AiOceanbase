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

#include "ob_log_resource_collector.h"

#include "storage/transaction/ob_trans_define.h" // ObTransID

#include "ob_log_part_trans_task.h"     // PartTransTask
#include "ob_log_task_pool.h"           // ObLogTransTaskPool
#include "ob_log_binlog_record_pool.h"  // ObLogBRPool
#include "ob_log_trans_ctx.h"           // TransCtx
#include "ob_log_trans_ctx_mgr.h"       // IObLogTransCtxMgr
#include "ob_log_row_data_index.h"      // ObLogRowDataIndex
#include "ob_log_store_service.h"       // IObStoreService
#include "ob_log_binlog_record.h"       // ObLogBR
#include "ob_log_meta_manager.h"        // IObLogMetaManager
#include "ob_log_instance.h"
#include "ob_log_tenant.h"
#include "ob_log_config.h"

using namespace oceanbase::common;
using namespace oceanbase::transaction;

namespace oceanbase
{
namespace liboblog
{

ObLogResourceCollector::ObLogResourceCollector() :
    inited_(false),
    br_pool_(NULL),
    trans_ctx_mgr_(NULL),
    meta_manager_(NULL),
    store_service_(NULL),
    br_thread_num_(0),
    br_count_(0),
    total_part_trans_task_count_(0),
    ddl_part_trans_task_count_(0),
    dml_part_trans_task_count_(0),
    hb_part_trans_task_count_(0),
    other_part_trans_task_count_(0)
{
}

ObLogResourceCollector::~ObLogResourceCollector()
{
  destroy();
}

int ObLogResourceCollector::init(const int64_t thread_num,
    const int64_t thread_num_for_br,
    const int64_t queue_size,
    IObLogBRPool *br_pool,
    IObLogTransCtxMgr *trans_ctx_mgr,
    IObLogMetaManager *meta_manager,
    IObStoreService *store_service)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(inited_)) {
    LOG_ERROR("ResourceCollector init twice");
    ret = OB_INIT_TWICE;
  } else if (OB_UNLIKELY(thread_num <= 0)
      || OB_UNLIKELY(thread_num_for_br <= 0)
      || OB_UNLIKELY(thread_num_for_br >= thread_num)
      || OB_UNLIKELY(queue_size <= 0)
      || OB_ISNULL(br_pool)
      || OB_ISNULL(trans_ctx_mgr)
      || OB_ISNULL(meta_manager)
      || OB_ISNULL(store_service)) {
    LOG_ERROR("invalid arguments", K(thread_num), K(thread_num_for_br), K(queue_size),
        K(br_pool), K(trans_ctx_mgr), K(meta_manager), K(store_service));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(RCThread::init(thread_num, queue_size))) {
    LOG_ERROR("init ResourceCollector threads fail", KR(ret), K(thread_num), K(queue_size));
  } else {
    br_pool_ = br_pool;
    trans_ctx_mgr_ = trans_ctx_mgr;
    meta_manager_ = meta_manager;
    store_service_ = store_service;
    br_thread_num_ = thread_num_for_br;
    br_count_ = 0;
    total_part_trans_task_count_ = 0;
    ddl_part_trans_task_count_ = 0;
    dml_part_trans_task_count_ = 0;
    hb_part_trans_task_count_ = 0;
    other_part_trans_task_count_ = 0;
    inited_ = true;

    LOG_INFO("init ResourceCollector succ", K(thread_num), K(thread_num_for_br), K(queue_size));
  }
  return ret;
}

void ObLogResourceCollector::destroy()
{
  RCThread::destroy();
  inited_ = false;
  br_pool_ = NULL;
  trans_ctx_mgr_ = NULL;
  meta_manager_ = NULL;
  store_service_ = NULL;
  br_thread_num_ = 0;
  br_count_ = 0;
  total_part_trans_task_count_ = 0;
  ddl_part_trans_task_count_ = 0;
  dml_part_trans_task_count_ = 0;
  hb_part_trans_task_count_ = 0;
  other_part_trans_task_count_ = 0;
}

int ObLogResourceCollector::start()
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_FAIL(RCThread::start())) {
    LOG_ERROR("start ResourceCollector threads fail", KR(ret));
  } else {
    LOG_INFO("start ResourceCollector threads succ", KR(ret));
  }
  return ret;
}

void ObLogResourceCollector::stop()
{
  if (inited_) {
    RCThread::stop();
    LOG_INFO("stop ResourceCollector threads succ");
  }
}

void ObLogResourceCollector::mark_stop_flag()
{
  if (inited_) {
    RCThread::mark_stop_flag();
  }
}

int ObLogResourceCollector::revert(PartTransTask *task)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(task)) {
    LOG_ERROR("invalid argument", K(task));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(push_task_into_queue_(*task))) {
    if (OB_IN_STOP_STATE != ret) {
      LOG_ERROR("push task into queue fail", KR(ret), K(task));
    }
  } else {
    // NOTE: After entering the queue, the task may be recycled at any time and cannot be further referenced
  }

  return ret;
}

int ObLogResourceCollector::revert(const int record_type, ObLogBR *br)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br)) {
    LOG_ERROR("invalid argument", K(br));
    ret = OB_INVALID_ARGUMENT;
  } else {
    if (EDDL == record_type) {
      PartTransTask *part_trans_task = NULL;

      if (OB_ISNULL(part_trans_task = static_cast<PartTransTask *>(br->get_host()))) {
        LOG_ERROR("binlog record host is invalid", K(br), K(br->get_host()));
        ret = OB_INVALID_ARGUMENT;
      } else if (OB_FAIL(dec_ref_cnt_and_try_to_revert_task_(part_trans_task))) {
        if (OB_IN_STOP_STATE != ret) {
          LOG_ERROR("dec_ref_cnt_and_try_to_revert_task_ fail", KR(ret), KPC(part_trans_task));
        }
      } else {}
    } else {
      // Recycle asynchronously in case of HEARTBEAT、BEGIN、COMMIT、DML
      if (OB_FAIL(push_task_into_queue_(*br))) {
        if (OB_IN_STOP_STATE != ret) {
          LOG_ERROR("push task into queue fail", KR(ret), K(br), "record_type", print_record_type(record_type));
        }
      } else {
        // NOTE: After entering the queue, the task may be recycled at any time and cannot be further referenced
        br = NULL;
      }
    }
  }

  return ret;
}

int ObLogResourceCollector::revert_unserved_task(const bool is_rollback_row,
    ObLogRowDataIndex &row_data_index)
{
  int ret = OB_SUCCESS;
  ObLogBR *br = row_data_index.get_binlog_record();

  if (OB_UNLIKELY(! row_data_index.is_valid())) {
    LOG_ERROR("row_data_index is not valid", K(row_data_index));
    ret = OB_INVALID_ARGUMENT;
  } else {
    // Storager mode, br is NULL
    if (NULL == br) {
      if (! is_rollback_row) {
        if (OB_FAIL(del_store_service_data_(row_data_index))) {
          LOG_ERROR("del_store_service_data_", KR(ret), K(row_data_index));
        }
      }
    } else {
      // Memory mode
      if (OB_FAIL(dec_ref_cnt_and_try_to_recycle_log_entry_task_(*br))) {
        LOG_ERROR("dec_ref_cnt_and_try_to_recycle_log_entry_task_ fail", KR(ret));
      } else if (OB_FAIL(revert_single_binlog_record_(br))) {
        LOG_ERROR("revert binlog record fail", KR(ret), K(br));
      } else {
        br = NULL;
      }
    }
  }

  return ret;
}

int ObLogResourceCollector::revert_log_entry_task(ObLogEntryTask *log_entry_task)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(revert_log_entry_task_(log_entry_task))) {
    LOG_ERROR("revert_log_entry_task_ fail", KR(ret), KPC(log_entry_task));
  } else {
    log_entry_task = NULL;
  }

  return ret;
}

int ObLogResourceCollector::dec_ref_cnt_and_try_to_revert_task_(PartTransTask *part_trans_task)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(part_trans_task)) {
    LOG_ERROR("invalid arguments", K(part_trans_task));
    ret = OB_INVALID_ARGUMENT;
  } else {
    // Decrement the reference count of partitionk transaction task
    // The partition transaction task needs to be recycled if the reference count becomes 0
    // Cannot continue to reference partition transaction tasks after that time, since partitioned transaction tasks may be recalled at any time
    const bool need_revert_part_trans_task = (part_trans_task->dec_ref_cnt() == 0);

    if (need_revert_part_trans_task) {
      if (OB_FAIL(revert(part_trans_task))) {
        if (OB_IN_STOP_STATE != ret) {
          LOG_ERROR("revert PartTransTask fail", KR(ret), K(part_trans_task));
        }
      } else {
        part_trans_task = NULL;
      }
    } else {
      // Cannot continue to access partition transaction task when do not need to recycle it
    }
  }

  return ret;
}

int ObLogResourceCollector::revert_log_entry_task_(ObLogEntryTask *log_entry_task)
{
  int ret = OB_SUCCESS;
 IObLogEntryTaskPool *log_entry_task_pool = TCTX.log_entry_task_pool_;

  if (OB_ISNULL(log_entry_task)) {
    LOG_ERROR("log_entry_task is NULL");
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_ISNULL(log_entry_task_pool)) {
    LOG_ERROR("log_entry_task_pool is NULL");
    ret = OB_ERR_UNEXPECTED;
  } else {
    const bool is_test_mode_on = TCONF.test_mode_on != 0;
    if (is_test_mode_on) {
      LOG_INFO("LogEntryTask-free", "LogEntryTask", *log_entry_task, "addr", log_entry_task);
    }

    log_entry_task->~ObLogEntryTask();
    log_entry_task_pool->free(log_entry_task);
  }

  return ret;
}

int ObLogResourceCollector::revert_participants_(const int64_t thread_index,
    PartTransTask *participants)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(participants)) {
    LOG_ERROR("invalid arguments", K(participants));
    ret = OB_INVALID_ARGUMENT;
  } else {
    PartTransTask *task = participants;

    while (OB_SUCCESS == ret && NULL != task) {
      PartTransTask *next = task->next_task();
      task->set_next_task(NULL);

      if (OB_FAIL(recycle_part_trans_task_(thread_index, task))) {
        if (OB_IN_STOP_STATE != ret) {
          LOG_ERROR("recycle_part_trans_task_ fail", KR(ret), K(thread_index), KPC(task));
        }
      } else {
        task = next;
      }
    }

    task = NULL;
  }

  return ret;
}

int ObLogResourceCollector::push_task_into_queue_(ObLogResourceRecycleTask &task)
{
  int ret = OB_SUCCESS;
  static uint64_t part_trans_task_push_seq = 0;
  static uint64_t br_push_seq = 0;
  uint64_t hash_value = 0;

  if (task.is_part_trans_task()) {
    hash_value = ATOMIC_FAA(&part_trans_task_push_seq, 1);
    hash_value = (hash_value % (RCThread::get_thread_num() - br_thread_num_)) + br_thread_num_;

    PartTransTask *part_trans_task = static_cast<PartTransTask *>(&task);

    if (OB_ISNULL(part_trans_task)) {
      LOG_ERROR("invalid argument", K(part_trans_task));
      ret = OB_ERR_UNEXPECTED;
    } else {
      do_stat_(*part_trans_task, true/*need_accumulate_stat*/);
    }
  } else if (task.is_binlog_record_task()) {
    (void)ATOMIC_AAF(&br_count_, 1);

    hash_value = ATOMIC_FAA(&br_push_seq, 1);
    hash_value = hash_value % br_thread_num_;
  } else {}

  // push to thread queue, asynchronous recycling
  while (OB_SUCC(ret) && ! RCThread::is_stoped()) {
    ret = RCThread::push(&task, hash_value, DATA_OP_TIMEOUT);

    if (OB_TIMEOUT != ret) {
      break;
    }
  }
  // Note: After a task is pushed to the queue, it may be recycled quickly and the task cannot be accessed later

  if (RCThread::is_stoped()) {
    ret = OB_IN_STOP_STATE;
  }

  return ret;
}

int ObLogResourceCollector::recycle_part_trans_task_(const int64_t thread_index,
    PartTransTask *task)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(task)) {
    LOG_ERROR("invalid argument", K(task));
    ret = OB_INVALID_ARGUMENT;
  } else {
    if (task->is_ddl_trans()) {
      if (OB_FAIL(revert_dll_all_binlog_records_(task))) {
        // Reclaim all Binlog Records within a DDL partitioned transaction
        LOG_ERROR("revert_dll_all_binlog_records_ fail", KR(ret), K(*task));
      }
    }
    LOG_DEBUG("[ResourceCollector] recycle part trans task", K(thread_index), K(*task));

    do_stat_(*task, false/*need_accumulate_stat*/);

    // recycle resource
    task->revert();
    task = NULL;
  }

  return ret;
}

int ObLogResourceCollector::handle(void *data,
    const int64_t thread_index,
    volatile bool &stop_flag)
{
  int ret = OB_SUCCESS;
  ObLogResourceRecycleTask *recycle_task = NULL;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_UNLIKELY(stop_flag)) {
    ret = OB_IN_STOP_STATE;
  } else if (OB_ISNULL(data)) {
    LOG_ERROR("invalid argument", K(data));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_ISNULL(recycle_task = static_cast<ObLogResourceRecycleTask *>(data))) {
    LOG_ERROR("recycle_task is NULL", K(recycle_task));
    ret = OB_ERR_UNEXPECTED;
  } else {
    ObLogResourceRecycleTask::TaskType task_type = recycle_task->get_task_type();

    if (recycle_task->is_part_trans_task()) {
      PartTransTask *task = static_cast<PartTransTask *>(recycle_task);

      // DML/DDL
      if (task->is_ddl_trans() || task->is_dml_trans()) {
        // Guaranteed reference count of 0
        if (OB_UNLIKELY(0 != task->get_ref_cnt())) {
          LOG_ERROR("can not revert part trans task, ref_cnt is not zero", K(*task));
          ret = OB_INVALID_ARGUMENT;
        } else {
          bool enable_create = false;
          TransCtx *trans_ctx = NULL;
          bool all_participant_revertable = false;
          // Copy the Trans ID to avoid invalidating the Trans ID when the PartTransTask is recycled
          ObTransID trans_id = task->get_trans_id();

          if (OB_FAIL(trans_ctx_mgr_->get_trans_ctx(trans_id, trans_ctx, enable_create))) {
            LOG_ERROR("get trans_ctx fail", KR(ret), K(trans_id), K(*task));
          }
          // Increase the number of participants that can be recycled
          else if (OB_FAIL(trans_ctx->inc_revertable_participant_count(all_participant_revertable))) {
            LOG_ERROR("trans_ctx.inc_revertable_participant_count fail", KR(ret), K(*trans_ctx));
          }
          // Recycle the distributed transaction if all participants are available for recycling
          else if (all_participant_revertable) {
            PartTransTask *participants = trans_ctx->get_participant_objs();

            if (OB_FAIL(trans_ctx->revert_participants())) {
              LOG_ERROR("trans_ctx.revert_participants fail", KR(ret), K(*trans_ctx));
            } else if (OB_FAIL(trans_ctx_mgr_->remove_trans_ctx(trans_id))) {
              LOG_ERROR("remove trans_ctx fail", KR(ret), K(trans_id), K(trans_ctx));
            }
            // recycle all participants
            else if (NULL != participants && OB_FAIL(revert_participants_(thread_index, participants))) {
              if (OB_IN_STOP_STATE != ret) {
                LOG_ERROR("revert_participants_ fail", KR(ret), K(thread_index), K(participants), K(trans_id));
              }
            } else {
              participants = NULL;
            }
          } else {
            // do nothing
          }

          if (NULL != trans_ctx) {
            int err = trans_ctx_mgr_->revert_trans_ctx(trans_ctx);
            if (OB_SUCCESS != err) {
              LOG_ERROR("revert_trans_ctx fail", K(err));
              ret = OB_SUCCESS == ret ? err : ret;
            }
          }

          task = NULL;
        }
      } else {
        // All other tasks are recycled directly
        if (OB_FAIL(recycle_part_trans_task_(thread_index, task))) {
          if (OB_IN_STOP_STATE != ret) {
            LOG_ERROR("recycle_part_trans_task_ fail", KR(ret), K(thread_index), KPC(task));
          }
        } else {
          task = NULL;
        }
      }
    } else if (recycle_task->is_binlog_record_task()) {
      // HEARTBEAT、BEGIN、COMMIT、INSERT、DELETE、UPDATE
      ObLogBR *task = static_cast<ObLogBR *>(recycle_task);
      int record_type = RecordType::EUNKNOWN;

      if (OB_ISNULL(task)) {
        LOG_ERROR("ObLogBR task is NULL");
        ret = OB_ERR_UNEXPECTED;
      } else if (task->get_record_type(record_type)) {
        LOG_ERROR("ObLogBR task get_record_type fail", KR(ret));
      } else {
        if (HEARTBEAT == record_type || EBEGIN == record_type || ECOMMIT == record_type) {
          br_pool_->free(task);
        } else {
          if (OB_FAIL(revert_dml_binlog_record_(*task))) {
            if (OB_IN_STOP_STATE != ret) {
              LOG_ERROR("revert_dml_binlog_record_ fail", KR(ret), KPC(task));
            }
          } else {}
        }
        (void)ATOMIC_AAF(&br_count_, -1);
        task = NULL;
      }
    } else {
      LOG_ERROR("task type not supported", K(recycle_task), K(thread_index),
          "task_type", ObLogResourceRecycleTask::print_task_type(task_type));
      ret = OB_NOT_SUPPORTED;
    }
  }

  return ret;
}

int ObLogResourceCollector::revert_dml_binlog_record_(ObLogBR &br)
{
  int ret = OB_SUCCESS;
  PartTransTask *part_trans_task = NULL;
  ObLogRowDataIndex *row_data_index = NULL;
  const bool is_serilized = br.is_serilized();

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(row_data_index = static_cast<ObLogRowDataIndex *>(br.get_host()))) {
    LOG_ERROR("row_data_index is NULL", K(br));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_ISNULL(part_trans_task = static_cast<PartTransTask*>(row_data_index->get_host()))) {
    LOG_ERROR("part_trans_task is NULL", KPC(row_data_index));
    ret = OB_ERR_UNEXPECTED;
  } else if (is_serilized) {
    const bool skip_recycle_data = TCONF.skip_recycle_data != 0;
    if (! skip_recycle_data) {
      if (OB_FAIL(del_store_service_data_(*row_data_index))) {
        LOG_ERROR("del_store_service_data_ fail", KR(ret), KPC(row_data_index));
      }
    }
  } else {
    if (OB_FAIL(dec_ref_cnt_and_try_to_recycle_log_entry_task_(br))) {
      LOG_ERROR("dec_ref_cnt_and_try_to_recycle_log_entry_task_ fail", KR(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(revert_single_binlog_record_(&br))) {
      LOG_ERROR("revert_single_binlog_record_ fail", KR(ret));
    }
  }

  if (OB_SUCC(ret)) {
    if (OB_FAIL(dec_ref_cnt_and_try_to_revert_task_(part_trans_task))) {
      if (OB_IN_STOP_STATE != ret) {
        LOG_ERROR("dec_ref_cnt_and_try_to_revert_task_ fail", KR(ret), KPC(part_trans_task));
      }
    }
  }

  return ret;
}

int ObLogResourceCollector::del_store_service_data_(ObLogRowDataIndex &row_data_index)
{
  int ret = OB_SUCCESS;
  std::string key;

  if (OB_FAIL(row_data_index.get_storage_key(key))) {
    LOG_ERROR("get_storage_key fail", KR(ret), "key", key.c_str());
  } else {
    const uint64_t tenant_id = row_data_index.get_tenant_id();
    ObLogTenantGuard guard;
    ObLogTenant *tenant = NULL;
    void *column_family_handle = NULL;

    if (OB_FAIL(TCTX.get_tenant_guard(tenant_id, guard))) {
      LOG_ERROR("get_tenant_guard fail", KR(ret), K(tenant_id));
    } else {
      tenant = guard.get_tenant();
      column_family_handle = tenant->get_cf();
    }

    if (OB_SUCC(ret)) {
      if (OB_FAIL(store_service_->del(column_family_handle, key))) {
        LOG_ERROR("store_service_ del fail", KR(ret), K(key.c_str()), K(row_data_index));
      } else {
        LOG_DEBUG("store_service_ del succ", K(key.c_str()), K(row_data_index));
      }
    }
  }

  return ret;
}

int ObLogResourceCollector::del_trans_(const uint64_t tenant_id,
    const ObString &trans_id_str)
{
  int ret = OB_SUCCESS;
  std::string begin_key;
  std::string end_key;
  begin_key.append(trans_id_str.ptr());
  begin_key.append("_");
  end_key.append(trans_id_str.ptr());
  end_key.append("_");
  end_key.append("}");
  ObLogTenantGuard guard;
  ObLogTenant *tenant = NULL;
  void *column_family_handle = NULL;
  if (OB_FAIL(TCTX.get_tenant_guard(tenant_id, guard))) {
    LOG_ERROR("get_tenant_guard fail", KR(ret), K(tenant_id));
  } else {
    tenant = guard.get_tenant();
    column_family_handle = tenant->get_cf();
  }
  if (OB_SUCC(ret)) {
    if (OB_FAIL(store_service_->del_range(column_family_handle, begin_key, end_key))) {
      LOG_ERROR("store_service_ del fail", KR(ret), "begin_key", begin_key.c_str(),
          "end_key", end_key.c_str());
    } else {
      LOG_INFO("store_service_ del succ", KR(ret), "begin_key", begin_key.c_str(),
          "end_key", end_key.c_str());
    }
  }
  return ret;
}

int ObLogResourceCollector::dec_ref_cnt_and_try_to_recycle_log_entry_task_(ObLogBR &br)
{
  int ret = OB_SUCCESS;
  ObLogEntryTask *log_entry_task = static_cast<ObLogEntryTask *>(br.get_log_entry_task());

  if (OB_ISNULL(log_entry_task)) {
    LOG_ERROR("log_entry_task is NULL");
    ret = OB_ERR_UNEXPECTED;
  } else {
    if (TCONF.test_mode_on) {
      LOG_INFO("revert_dml_binlog_record", KPC(log_entry_task));
    }
    const bool need_revert_log_entry_task = (log_entry_task->dec_row_ref_cnt() == 0);

    if (need_revert_log_entry_task) {
      if (OB_FAIL(revert_log_entry_task_(log_entry_task))) {
        LOG_ERROR("revert_log_entry_task_ fail", KR(ret), KPC(log_entry_task));
      } else {
        log_entry_task = NULL;
      }
    }
  }

  return ret;
}

int ObLogResourceCollector::revert_dll_all_binlog_records_(PartTransTask *task)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(task)) {
    LOG_ERROR("invalid argument", K(task));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_UNLIKELY(! task->is_ddl_trans())) {
    LOG_ERROR("is not ddl trans, unexpected", KPC(task));
    ret = OB_ERR_UNEXPECTED;
  } else {
    const StmtList &stmt_list = task->get_stmt_list();
    DdlStmtTask *stmt_task = static_cast<DdlStmtTask *>(stmt_list.head_);

    // Iterate through all statements, get all Binlog Records and reclaim them
    // FIXME: the Binlog Record contains references to memory allocated by the PartTransTask.
    // They should be actively freed here, but as PartTransTask will release the memory uniformly when it is reclaimed
    // memory in the Binlog Record is not actively freed here
    while (OB_SUCC(ret) && NULL != stmt_task) {
      DdlStmtTask *next = static_cast<DdlStmtTask *>(stmt_task->get_next());
      ObLogBR *br = stmt_task->get_binlog_record();
      stmt_task->set_binlog_record(NULL);

      if (OB_FAIL(revert_single_binlog_record_(br))) {
        LOG_ERROR("revert_single_binlog_record_ fail", KR(ret));
      }

      stmt_task = next;
    }
  }

  return ret;
}

int ObLogResourceCollector::revert_single_binlog_record_(ObLogBR *br)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(! inited_)) {
    LOG_ERROR("ResourceCollector has not been initialized");
    ret = OB_NOT_INIT;
  } else if (OB_ISNULL(br)) {
    LOG_ERROR("br is NULL");
    ret = OB_INVALID_ARGUMENT;
  } else {
    const bool is_serilized = br->is_serilized();

    if (! is_serilized) {
      ILogRecord *br_data = NULL;

      if (OB_ISNULL(br_data = br->get_data())) {
        LOG_ERROR("binlog record data is invalid", K(br));
        ret = OB_INVALID_ARGUMENT;
      } else {
        ITableMeta *tblMeta = NULL;
        // recycle Table Meta of binlog record
        if (0 != br_data->getTableMeta(tblMeta)) {
          LOG_ERROR("getTableMeta fail");
          ret = OB_ERR_UNEXPECTED;
        } else if (NULL != tblMeta) {
          meta_manager_->revert_table_meta(tblMeta);
          br_data->setTableMeta(NULL);
        }

        // recycle DB Meta of binlog record
        if (NULL != br_data->getDBMeta()) {
          meta_manager_->revert_db_meta(br_data->getDBMeta());
          br_data->setDBMeta(NULL);
        }
      }
    }

    if (OB_SUCC(ret)) {
      br_pool_->free(br);
      br = NULL;
    }
  }

  return ret;
}

int64_t ObLogResourceCollector::get_part_trans_task_count() const
{
  return ATOMIC_LOAD(&total_part_trans_task_count_);
}

void ObLogResourceCollector::do_stat_(PartTransTask &task,
    const bool need_accumulate_stat)
{
  int64_t cnt = 1;

  if (! need_accumulate_stat) {
    cnt = -1;
  }

  (void)ATOMIC_AAF(&total_part_trans_task_count_, cnt);

  if (task.is_ddl_trans()) {
    (void)ATOMIC_AAF(&ddl_part_trans_task_count_, cnt);
  } else if (task.is_dml_trans()) {
    (void)ATOMIC_AAF(&dml_part_trans_task_count_, cnt);
  } else if (task.is_part_heartbeat() || task.is_global_heartbeat()) {
    (void)ATOMIC_AAF(&hb_part_trans_task_count_, cnt);
  } else {
    (void)ATOMIC_AAF(&other_part_trans_task_count_, cnt);
  }
}

void ObLogResourceCollector::print_stat_info() const
{
  _LOG_INFO("[RESOURCE_COLLECTOR] [STAT] BR=%ld TOTAL_PART=%ld DDL=%ld DML=%ld HB=%ld OTHER=%ld",
      br_count_,
      total_part_trans_task_count_,
      ddl_part_trans_task_count_,
      dml_part_trans_task_count_,
      hb_part_trans_task_count_,
      other_part_trans_task_count_);
}

} // namespace liboblog
} // namespace oceanbase
