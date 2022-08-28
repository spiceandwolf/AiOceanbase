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

#define USING_LOG_PREFIX OBLOG_FETCHER

#include "ob_log_part_trans_dispatcher.h"   // PartTransDispatcher

#include "share/ob_errno.h"                 // OB_SUCCESS
#include "lib/utility/ob_macro_utils.h"     // OB_UNLIKELY
#include "lib/oblog/ob_log_module.h"        // LOG_ERROR

#include "ob_log_fetcher_dispatcher.h"      // IObLogFetcherDispatcher
#include "ob_log_utils.h"

using namespace oceanbase::common;

namespace oceanbase
{
namespace liboblog
{
int64_t PartTransDispatcher::g_part_trans_task_count = 0;

PartTransID::PartTransID(const transaction::ObTransID &trans_id, const common::ObPartitionKey &pkey) :
    trans_id_(trans_id), pkey_(pkey)
{}

bool PartTransID::operator == (const PartTransID &part_trans_id) const
{
  return trans_id_ == part_trans_id.trans_id_ && pkey_ == part_trans_id.pkey_;
}

uint64_t PartTransID::hash() const
{
  uint64_t hv = trans_id_.hash();
  return murmurhash(&hv, sizeof(hv), pkey_.hash());
}

//////////////////////////////////// PartTransDispatchInfo ///////////////////////////////////

PartTransDispatchInfo::PartTransDispatchInfo() :
    last_dispatch_log_id_(OB_INVALID_ID),
    current_checkpoint_(OB_INVALID_VERSION),
    pending_task_count_(0),
    task_count_in_queue_(0),
    next_task_type_("INVALID"),
    next_trans_log_id_(OB_INVALID_ID),
    next_trans_committed_(false),
    next_trans_ready_to_commit_(false),
    next_trans_global_version_(OB_INVALID_VERSION)
{}

//////////////////////////////////// TransCommitInfo ///////////////////////////////////

void TransCommitInfo::reset()
{
  log_id_ = OB_INVALID_ID;
  log_ts_ = OB_INVALID_TIMESTAMP;
}

TransCommitInfo::TransCommitInfo(const uint64_t log_id, const int64_t log_ts) :
    log_id_(log_id),
    log_ts_(log_ts)
{
}

//////////////////////////////////// PartTransDispatcher ///////////////////////////////////

PartTransDispatcher::PartTransDispatcher(const char *pkey_str,
    TaskPool &task_pool,
    PartTransTaskMap &task_map,
    TransCommitMap &trans_commit_map,
    IObLogFetcherDispatcher &dispatcher):
    pkey_(),
    pkey_str_(pkey_str),
    task_pool_(task_pool),
    task_map_(task_map),
    trans_commit_map_(trans_commit_map),
    dispatcher_(dispatcher),
    task_queue_(),
    init_dispatch_progress_(OB_INVALID_TIMESTAMP),
    last_dispatch_progress_(OB_INVALID_TIMESTAMP),
    last_dispatch_log_id_(OB_INVALID_ID),
    task_count_only_in_map_(0),
    checkpoint_(OB_INVALID_VERSION),
    created_trans_count_(0),
    last_created_trans_count_(0),
    last_stat_time_(get_timestamp()),
    dispatch_lock_()
{}

PartTransDispatcher::~PartTransDispatcher()
{
  // TODO: Consider cleaning up the data, but make sure to call clean_task to empty the task when the partition is offline
  // That is, task_queue and task_map should not have tasks from this partition in them
  // If want to clean tasks here, we need to save the pkey, but for the time being, don't need to save the pkey in order to optimise memory usage
  if (task_queue_.size() > 0) {
    LOG_ERROR("task_queue_ is not empty", K(task_queue_.size()), KPC(task_queue_.top()));
  }

  pkey_.reset();
  pkey_str_ = NULL;
  init_dispatch_progress_ = OB_INVALID_TIMESTAMP;
  last_dispatch_progress_ = OB_INVALID_TIMESTAMP;
  last_dispatch_log_id_ = OB_INVALID_ID;
  task_count_only_in_map_ = 0;
  checkpoint_ = OB_INVALID_VERSION;
  created_trans_count_ = 0;
  last_created_trans_count_ = 0;
  last_stat_time_ = 0;
}

int PartTransDispatcher::init(const common::ObPartitionKey &pkey,
    const int64_t start_tstamp)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(OB_INVALID_TIMESTAMP == start_tstamp)) {
    LOG_ERROR("invalid argument", K(start_tstamp));
    ret = OB_INVALID_ARGUMENT;
  } else {
    pkey_ = pkey;
    // Only the necessary fields are initialized here, all other fields are initialized during construction
    // 1. When there is a transaction in the partition with the same timestamp as the start timestamp and it has not been sent,
    // it is possible that the heartbeat will fall back because it takes the "pending task timestamp-1".
    // 2. so initialize progress to start timestamp-1
    init_dispatch_progress_ = start_tstamp - 1;
    last_dispatch_progress_ = start_tstamp - 1;
  }
  return ret;
}

// The heartbeat interface only produces heartbeat tasks, it does not consume them
// requires only one producer, no need to add production lock here
int PartTransDispatcher::heartbeat(const common::ObPartitionKey &pkey, const int64_t hb_tstamp)
{
  int ret = OB_SUCCESS;
  PartTransTask *task = NULL;

  if (OB_UNLIKELY(OB_INVALID_TIMESTAMP == hb_tstamp)) {
    LOG_ERROR("invalid heartbeat timestamp", K(hb_tstamp), K(pkey));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_ISNULL(task = task_pool_.get(pkey_str_, pkey))) {
    LOG_ERROR("alloc part trans task fail", K(task));
    ret = OB_ALLOCATE_MEMORY_FAILED;
  } else if (OB_FAIL(task->init_part_heartbeat_info(pkey, hb_tstamp))) {
    LOG_ERROR("init_part_heartbeat_info fail", KR(ret), K(pkey), K(hb_tstamp), KPC(task));
  } else {
    push_task_queue_(*task);
  }

  if (OB_SUCCESS != ret && NULL != task) {
    task->revert();
    task = NULL;
  }

  return ret;
}

void PartTransDispatcher::update_status_after_consume_task_(const int64_t task_tstamp,
    const uint64_t prepare_log_id)
{
  if (OB_INVALID_TIMESTAMP != task_tstamp) {
    last_dispatch_progress_ = std::max(last_dispatch_progress_, task_tstamp);
  }

  if (OB_INVALID_ID != prepare_log_id) {
    last_dispatch_log_id_ = prepare_log_id;
  }
}

int PartTransDispatcher::dispatch_part_trans_task_(PartTransTask &task, volatile bool &stop_flag)
{
  int ret = OB_SUCCESS;
  // Save the basic information of the task in advance, the output will not be accessible afterwards
  int64_t task_tstamp = task.get_timestamp();
  // Note: prepare_log_id is only valid for DDL and DML types
  uint64_t prepare_log_id = task.get_prepare_log_id();

  if (OB_INVALID_TIMESTAMP != task_tstamp) {
    // Check if progress is backed up
    // The progress here may indeed be backwards because the start time of the target partition is the maximum value
    // calculated based on the DDL partition transaction's prepare log timestamp and schema_version,
    // in order to prevent the heartbeat timestamp from being backwards; whereas the target partition's own transaction
    // timestamp is generated locally, and although the master guarantees that the prepare log timestamp is greater
    // than or equal to the GTS time, but only if the target partition and the DDL partition are the same tenant can
    // their own prepare timestamp be guaranteed by GTS to be greater than or equal to the DDL partition transaction's
    // prepare timestamp. However, if the DDL partition and the target partition are not the same tenant, GTS does
    // not have a corresponding guarantee. Therefore, it is normal for data progress to be rolled back here. But it is
    // dangerous. This problem can only be completely solved when the schema is split within the tenant.
    if (OB_UNLIKELY(task_tstamp < last_dispatch_progress_)) {
      LOG_WARN("partition dispatch progress is rollback, we should check it",
          "task_tstamp", TS_TO_STR(task_tstamp),
          "last_dispatch_progress", TS_TO_STR(last_dispatch_progress_),
          K(last_dispatch_log_id_),
          K(task),
          K(stop_flag));
    }
  }

  if (OB_FAIL(handle_before_fetcher_dispatch_(task))) {
    LOG_ERROR("handle_before_fetcher_dispatch_ fail", KR(ret), K(task));
  } else if (OB_FAIL(dispatcher_.dispatch(task, stop_flag))) {
    if (OB_IN_STOP_STATE != ret) {
      LOG_ERROR("fetcher dispatch task fail", KR(ret), K(task));
    }
  } else {
    // Task output successful, update progress values
    update_status_after_consume_task_(task_tstamp, prepare_log_id);
  }

  // Regardless of whether the dispatch task completes successfully or not, reset the task information recorded by the queue
  task_queue_.reset_dispatched_task_info();
  return ret;
}

int PartTransDispatcher::handle_before_fetcher_dispatch_(PartTransTask &task)
{
  int ret = OB_SUCCESS;

  if (task.is_dml_trans()) {
    if (OB_FAIL(handle_dml_trans_before_fetcher_dispatch_(task))) {
      LOG_ERROR("handle_dml_trans_before_fetcher_dispatch_ fail", KR(ret), K(task));
    }
  } else {
    // do nothing
  }

  return ret;
}

int PartTransDispatcher::handle_dml_trans_before_fetcher_dispatch_(PartTransTask &task)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(task.try_to_set_data_ready_status())) {
    LOG_ERROR("try_to_set_data_ready_status fail", KR(ret), K(task));
  }

  return ret;
}

void PartTransDispatcher::push_task_queue_(PartTransTask &task)
{
  task_queue_.push(&task);

  if (task.is_dml_trans() || task.is_ddl_trans()) {
    ATOMIC_INC(&created_trans_count_);
  }

  // Update the global task count when the task queue task count changes
  ATOMIC_INC(&g_part_trans_task_count);
}

PartTransTask* PartTransDispatcher::pop_task_queue_()
{
  PartTransTask *ret = task_queue_.pop();
  if (NULL != ret) {
    // Update the global task count when the task queue task count changes
    ATOMIC_DEC(&g_part_trans_task_count);
  }
  return ret;
}

int PartTransDispatcher::prepare_task(PartTransTask &task)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(! task.is_dml_trans() && ! task.is_ddl_trans())) {
    LOG_ERROR("invalid task which is not DML or DDL task", K(task));
    ret = OB_INVALID_ARGUMENT;
  } else {
    push_task_queue_(task);

    // into the queue, minus the number in the map only
    // Update the global number of tasks at the same time
    ATOMIC_DEC(&task_count_only_in_map_);
    ATOMIC_DEC(&g_part_trans_task_count);
  }
  return ret;
}

int PartTransDispatcher::check_task_ready_(PartTransTask &task, bool &task_is_ready)
{
  int ret = OB_SUCCESS;
  if (task.is_dml_trans() || task.is_ddl_trans()) {
    // checkpoint valid, attempt to update partition commit status (single multipartition transaction)
    if (OB_INVALID_VERSION != checkpoint_) {
      if (OB_FAIL(task.update_trans_committed_status(checkpoint_, *this))) {
        LOG_ERROR("update_trans_committed_status fail", KR(ret), K(checkpoint_), K(task));
      }
    }

    if (OB_SUCC(ret)) {
      task_is_ready = task.is_trans_committed();
      // If the task is ready for output, remove it from the map
      // Note: The logic for removing from map is placed here because the task in map must be a DDL
      // or DML type transaction, other types of task will not be placed in map.
      //
      // In order to be compatible with more types of tasks in the future and other tasks do not need to be
      // removed from the map, DML and DDL type tasks are removed from the map as soon as they are detected as ready.
      if (task_is_ready) {
        PartTransID part_trans_id(task.get_trans_id(), task.get_partition());
        // Requires that it must exist
        if (OB_FAIL(task_map_.erase(part_trans_id))) {
          LOG_ERROR("erase from task map fail", KR(ret), K(part_trans_id), K(task));
        }
      }
    }
  } else {
    // Other types of tasks are ready by default
    task_is_ready = true;
  }
  return ret;
}


int64_t PartTransDispatcher::get_total_task_count_()
{
  // in MAP only + in QUEUE
  return ATOMIC_LOAD(&task_count_only_in_map_) + task_queue_.size();
}

int PartTransDispatcher::dispatch_part_trans(volatile bool &stop_flag, int64_t &pending_task_count)
{
  int ret = OB_SUCCESS;
  ObByteLockGuard guard(dispatch_lock_);

  while (OB_SUCCESS == ret && ! stop_flag) {
    PartTransTask *task = task_queue_.top();
    bool task_is_ready = false;

    // If the task is not ready, exit the loop
    if (NULL == task) {
      ret = OB_EAGAIN;
    } else if (OB_FAIL(check_task_ready_(*task, task_is_ready))) {
      LOG_ERROR("check_task_ready_ fail", KR(ret), KPC(task));
    } else if (! task_is_ready) {
      ret = OB_EAGAIN;
    } else {
      // pop out data
      (void)pop_task_queue_();

      // dispatch the current task
      if (OB_FAIL(dispatch_part_trans_task_(*task, stop_flag))) {
        if (OB_IN_STOP_STATE != ret) {
          LOG_ERROR("dispatch_part_trans_task_ fail", KR(ret), KPC(task));
        }
      } else {
        task = NULL;
      }
    }
  }

  if (stop_flag) {
    ret = OB_IN_STOP_STATE;
  }

  if (OB_EAGAIN == ret) {
    ret = OB_SUCCESS;
  }

  if (OB_SUCCESS == ret) {
    pending_task_count = get_total_task_count_();
  }

  return ret;
}

int PartTransDispatcher::dispatch_offline_partition_task(const common::ObPartitionKey &pkey,
    volatile bool &stop_flag)
{
  int ret = OB_SUCCESS;
  ObByteLockGuard guard(dispatch_lock_);
  PartTransTask *task = NULL;

  // Because offline partitioned tasks are generated in real time and then sent down in real time,
  // it is important to ensure that the task queue is empty and there are no queued tasks ahead
  // Another purpose is to reclaim all memory and avoid memory leaks
  if (OB_UNLIKELY(task_queue_.size() > 0)) {
    LOG_ERROR("there are tasks not dispatched, cat not dispatch offline task",
        "task_queue_size", task_queue_.size());
    ret = OB_STATE_NOT_MATCH;
  } else if (OB_ISNULL(task = task_pool_.get(pkey_str_, pkey))) {
    LOG_ERROR("alloc part trans task fail", K(task));
    ret = OB_ALLOCATE_MEMORY_FAILED;
  } else if (OB_FAIL(task->init_offline_partition_task(pkey))) {
    LOG_ERROR("init_offline_partition_task fail", KR(ret), K(pkey), KPC(task));
  } else if (OB_FAIL(dispatch_part_trans_task_(*task, stop_flag))) {
    if (OB_IN_STOP_STATE != ret) {
      LOG_ERROR("dispatch task fail", KR(ret), KPC(task), K(task));
    }
  } else {
    task = NULL;
  }

  if (OB_FAIL(ret)) {
    if (NULL != task) {
      task->revert();
      task = NULL;
    }
  }

  return ret;
}

struct TaskMapCleaner
{
  bool operator()(const PartTransID &key, PartTransTask *&val)
  {
    bool bool_ret = false;
    const bool is_ddl_part = is_ddl_partition(key.pkey_);

    if (key.pkey_ == pkey_) {
      if (NULL != val && is_ddl_part) {
        val->revert();
      }

      val = NULL;
      bool_ret = true;
      count_++;
    }

    return bool_ret;
  }

  TaskMapCleaner(const ObPartitionKey &pkey) : count_(0), pkey_(pkey) {}

  int64_t               count_;
  const ObPartitionKey  &pkey_;
};

// Iterate through all tasks, ready or not, and revert them directly
// The aim is to clear all tasks
int PartTransDispatcher::clean_task(const common::ObPartitionKey &pkey)
{
  int ret = OB_SUCCESS;
  TaskMapCleaner map_cleaner(pkey);
  const bool is_ddl_part = is_ddl_partition(pkey);

  // Clearance tasks are also a form of consumption and require the addition of a consumption lock
  ObByteLockGuard guard(dispatch_lock_);

  // First recycle all tasks in the queue, which may all be in the map, so delete the corresponding data items in the map at the same time
  // pop out the tasks in the queue, whether they are ready or not
  PartTransTask *task = NULL;
  int64_t task_queue_size = task_queue_.size();

  while (NULL != (task = pop_task_queue_()) && OB_SUCCESS == ret) {
    // Delete DML and DDL type transactions from map
    if (task->is_dml_trans() || task->is_ddl_trans()) {
      PartTransID part_trans_id(task->get_trans_id(), task->get_partition());
      if (OB_FAIL(task_map_.erase(part_trans_id))) {
        // It is normal for Map not to exist–
        if (OB_ENTRY_NOT_EXIST == ret) {
          ret = OB_SUCCESS;
        } else {
          LOG_ERROR("erase from task map fail", KR(ret), K(part_trans_id), K(task));
        }
      }
    }

    if (OB_SUCCESS == ret) {
      // Update state after consumption is complete
      update_status_after_consume_task_(task->get_timestamp(), task->get_prepare_log_id());
      // 回收任务
      if (is_ddl_part) {
        task->revert();
      }
    }
  }

  if (OB_SUCCESS == ret) {
    // Clear all tasks in the Map that are not in the queue
    if (OB_FAIL(task_map_.remove_if(map_cleaner))) {
      LOG_ERROR("remove from map fail", KR(ret), K(pkey));
    } else {
      // Subtract the number of tasks that are only in the map
      (void)ATOMIC_AAF(&g_part_trans_task_count, -map_cleaner.count_);
      (void)ATOMIC_AAF(&task_count_only_in_map_, -map_cleaner.count_);
    }
  }

  if (OB_SUCCESS == ret) {
    if (task_count_only_in_map_ != 0) {
      LOG_ERROR("task_count_only_in_map_ != 0 after clean all task, unexcepted error",
          K(task_count_only_in_map_), K(pkey), K(task_queue_size),
          "task_map_size", map_cleaner.count_);
      ret = OB_ERR_UNEXPECTED;
    }
  }

  LOG_INFO("part trans resolver clean task", KR(ret), K(pkey), K(task_queue_size),
      "task_map_size", map_cleaner.count_,
      K(task_count_only_in_map_), K(last_dispatch_progress_), K(last_dispatch_log_id_));

  return ret;
}

int PartTransDispatcher::insert_commit_trans(const transaction::ObTransID &trans_id,
    const TransCommitInfo &trans_commit_info)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(trans_commit_map_.insert(trans_id, trans_commit_info))) {
    if (OB_ENTRY_EXIST != ret) {
      LOG_ERROR("trans_commit_map insert fail", KR(ret), K(trans_id), K(trans_commit_info));
    } else {
      // return success if exist
      ret = OB_SUCCESS;
    }
  }

  return ret;
}

int PartTransDispatcher::remove_task(const bool is_ddl_part, const PartTransID &trans_id)
{
  int ret = OB_SUCCESS;
  // To remove a task from a Queue and therefore add a lock
  ObByteLockGuard guard(dispatch_lock_);
  PartTransTask *task = NULL;

  // Remove the corresponding task from the Map and return the object value
  if (OB_FAIL(task_map_.erase(trans_id, task))) {
    if (OB_ENTRY_NOT_EXIST == ret) {
      ret = OB_SUCCESS;
    } else {
      LOG_ERROR("get task from map fail", KR(ret), K(trans_id));
    }
  } else if (OB_ISNULL(task)) {
    LOG_ERROR("invalid task", K(task), K(trans_id));
    ret = OB_ERR_UNEXPECTED;
  } else {
    bool exist_in_queue = false;
    // Picking tasks from a Queue's chain
    task_queue_.remove(task, exist_in_queue);

    // ddl revert task
    if (is_ddl_part) {
      task->revert();
      task = NULL;
    } else {
      bool is_unserved_part_trans_task_can_be_recycled = false;
      if (OB_FAIL(task->handle_unserved_part_trans(is_unserved_part_trans_task_can_be_recycled))) {
        LOG_ERROR("handle_unserved_part_trans fail", KR(ret), K(task));
      } else if (is_unserved_part_trans_task_can_be_recycled) {
        task->revert();
        task = NULL;
      }
    }

    if (! exist_in_queue) {
      ATOMIC_DEC(&task_count_only_in_map_);
    }

    ATOMIC_DEC(&g_part_trans_task_count);
  }

  return ret;
}

int PartTransDispatcher::find_commit_trans_info(const transaction::ObTransID &trans_id,
    bool &is_commit_trans)
{
  int ret = OB_SUCCESS;
  is_commit_trans = false;
  TransCommitInfo trans_commit_info;

  if (OB_FAIL(trans_commit_map_.get(trans_id, trans_commit_info))) {
    if (OB_ENTRY_NOT_EXIST != ret) {
      LOG_ERROR("get part trans task fail", KR(ret), K(trans_id));
    } else {
      ret = OB_SUCCESS;
      is_commit_trans = false;
    }
  } else {
    is_commit_trans = true;
  }

  return ret;
}

// No concurrent update of task queues involved, just application data structures, no locking required
int PartTransDispatcher::alloc_task(const PartTransID &trans_id, PartTransTask *&task)
{
  int ret = OB_SUCCESS;

  if (OB_ISNULL(task = task_pool_.get(pkey_str_, pkey_))) {
    LOG_ERROR("alloc part trans task fail", K(task));
    ret = OB_ALLOCATE_MEMORY_FAILED;
  }
  // Inserted into Map for subsequent queries based on TransID
  else if (OB_FAIL(task_map_.insert(trans_id, task))) {
    task->revert();
    task = NULL;
    LOG_ERROR("insert part trans task fail", KR(ret), K(trans_id));
  } else {
    // This task is only in MAP, not in QUEUE
    ATOMIC_INC(&task_count_only_in_map_);
    ATOMIC_INC(&g_part_trans_task_count);
  }

  return ret;
}

int PartTransDispatcher::get_task(const PartTransID &trans_id, PartTransTask *&task)
{
  int ret = OB_SUCCESS;

  task = NULL;
  if (OB_FAIL(task_map_.get(trans_id, task))) {
    if (OB_ENTRY_NOT_EXIST != ret) {
      LOG_ERROR("get part trans task fail", KR(ret), K(trans_id));
    }
  } else if (OB_ISNULL(task)) {
    LOG_ERROR("part_trans_task is NULL");
    ret = OB_ERR_UNEXPECTED;
  } else {
    if (! task->is_served()) {
      ret = OB_INVALID_ERROR;
    }
  }

  return ret;
}

// dispatch_progress information does not use dispatch locks, uses task_queue_ locks, risky when getting dispatch_info
//
// 1. get progress based on last dispatch progress
// 2. Update dispatch progress if there are tasks that are dispatching or ready to be dispatched
int PartTransDispatcher::get_dispatch_progress(int64_t &dispatch_progress,
    PartTransDispatchInfo &dispatch_info)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(OB_INVALID_TIMESTAMP == last_dispatch_progress_)) {
    LOG_ERROR("invalid last_dispatch_progress_", K(last_dispatch_progress_));
    ret = OB_NOT_INIT;
  }
  // Get PartTransDispatcher member values without locking
  else {
    // The default is to take the progress of the last issue
    dispatch_progress = ATOMIC_LOAD(&last_dispatch_progress_);
    dispatch_info.last_dispatch_log_id_ = ATOMIC_LOAD(&last_dispatch_log_id_);
    dispatch_info.current_checkpoint_ = ATOMIC_LOAD(&checkpoint_);

    // Access is not atomic and may be biased
    dispatch_info.pending_task_count_ = get_total_task_count_();

    // Update dispatch progress based on the task being dispatched
    task_queue_.update_dispatch_progress_by_task_queue(dispatch_progress, dispatch_info);
  }

  return ret;
}

double PartTransDispatcher::get_tps()
{
  int64_t current_timestamp = get_timestamp();
  int64_t local_created_trans_count = ATOMIC_LOAD(&created_trans_count_);
  int64_t local_last_created_trans_count = ATOMIC_LOAD(&last_created_trans_count_);
  int64_t local_last_stat_time = last_stat_time_;
  int64_t delta_create_count = local_created_trans_count - local_last_created_trans_count;
  int64_t delta_time = current_timestamp - local_last_stat_time;
  double create_tps = 0.0;

  // Update the last statistics
  last_created_trans_count_ = local_created_trans_count;
  last_stat_time_ = current_timestamp;

  if (delta_time > 0) {
    create_tps = (double)(delta_create_count) * 1000000.0 / (double)delta_time;
  }

  return create_tps;
}

int PartTransDispatcher::update_checkpoint(int64_t new_checkpoint)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(OB_INVALID_VERSION == new_checkpoint)) {
    LOG_ERROR("invalid argument", K(new_checkpoint));
    ret = OB_INVALID_ARGUMENT;
  } else {
    // prepare log records the checkpoint, which is not guaranteed to be incremented due to concurrent transaction scenarios
    // so checkpoint is only updated when it is bigger
    if (new_checkpoint > checkpoint_) {
      ATOMIC_STORE(&checkpoint_, new_checkpoint);
    }
  }

  return ret;
}

}
}
