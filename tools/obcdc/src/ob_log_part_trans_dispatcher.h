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

#ifndef OCEANBASE_LIBOBLOG_OB_LOG_PART_TRANS_DISPATCHER_H__
#define OCEANBASE_LIBOBLOG_OB_LOG_PART_TRANS_DISPATCHER_H__

#include "lib/hash/ob_linear_hash_map.h"          // ObLinearHashMap
#include "lib/hash_func/murmur_hash.h"            // murmurhash
#include "lib/lock/ob_small_spin_lock.h"          // ObByteLock
#include "common/ob_partition_key.h"              // ObPartitionKey
#include "storage/transaction/ob_trans_define.h"  // ObTransID, ObRedoLogIdArray

#include "ob_log_task_pool.h"                     // ObLogTransTaskPool
#include "ob_log_part_trans_task.h"               // PartTransTask
#include "ob_log_part_trans_task_queue.h"         // SafePartTransTaskQueue

namespace oceanbase
{
namespace liboblog
{

// ObTransID + PKey: Uniquely identifies a partitioned task
struct PartTransID
{
  transaction::ObTransID  trans_id_;
  common::ObPartitionKey  pkey_;

  PartTransID(const transaction::ObTransID &trans_id, const common::ObPartitionKey &pkey);
  bool operator == (const PartTransID &part_trans_id) const;
  uint64_t hash() const;

  TO_STRING_KV(K_(trans_id), K_(pkey));
};

struct PartTransDispatchInfo
{
  uint64_t    last_dispatch_log_id_;
  int64_t     current_checkpoint_;
  int64_t     pending_task_count_;        // The total number of tasks waiting, both in the queue and in the Map
  int64_t     task_count_in_queue_;       // Number of queued tasks

  const char  *next_task_type_;
  uint64_t    next_trans_log_id_;
  bool        next_trans_committed_;
  bool        next_trans_ready_to_commit_;
  int64_t     next_trans_global_version_;

  PartTransDispatchInfo();

  TO_STRING_KV(
      K_(last_dispatch_log_id),
      K_(current_checkpoint),
      K_(pending_task_count),
      K_(task_count_in_queue),
      K_(next_task_type),
      K_(next_trans_log_id),
      K_(next_trans_committed),
      K_(next_trans_ready_to_commit),
      K_(next_trans_global_version));
};

class PartTransDispatcher;
struct TransCommitInfo
{
  uint64_t log_id_;
  int64_t log_ts_;

  TransCommitInfo(const uint64_t log_id, const int64_t log_ts);
  TransCommitInfo()  { reset(); }
  ~TransCommitInfo() { reset(); }
  void reset();

  TO_STRING_KV(
      K_(log_id),
      K_(log_ts));
};
typedef common::ObLinearHashMap<PartTransID, PartTransTask*, PartTransDispatcher> PartTransTaskMap;
typedef common::ObLinearHashMap<transaction::ObTransID, TransCommitInfo, PartTransDispatcher> TransCommitMap;
typedef ObLogTransTaskPool<PartTransTask> TaskPool;
class IObLogFetcherDispatcher;

class PartTransDispatcher
{
public:
  PartTransDispatcher(const char *pkey_str,
      TaskPool &task_pool,
      PartTransTaskMap &task_map,
      TransCommitMap &trans_commit_map,
      IObLogFetcherDispatcher &dispatcher);
  virtual ~PartTransDispatcher();

public:
  // Class global variable
  // count the number of tasks in the Fetcher partition
  static int64_t  g_part_trans_task_count;

public:
  int init(const common::ObPartitionKey &pkey, const int64_t start_tstamp);

  // Generate heartbeat task
  int heartbeat(const common::ObPartitionKey &pkey,
      const int64_t tstamp);

  // Pending task on output queue, ready for output
  // Note: the task must be a DML transaction or a DDL transaction
  int prepare_task(PartTransTask &task);

  // Dispatch tasks in the ready state, that is, tasks that have been committed
  int dispatch_part_trans(volatile bool &stop_flag, int64_t &pending_task_count);

  // 分派下线分区任务
  int dispatch_offline_partition_task(const common::ObPartitionKey &pkey, volatile bool &stop_flag);

  // DDL: Clear all tasks and revert all tasks to free memory
  // DML: Clear all tasks located in task_map_, and task itself wait callback to free
  int clean_task(const common::ObPartitionKey &pkey);

  // Delete partition transaction task with PartTransID, and revert memory
  // 1. Call this function when handle abort log
  // 2. Call this function when handle unserved partition transaction-prepare log
  //
  // For DML partition transaction task:
  // 1. Remove PartTransTask from task_queue_, but can not revert memory
  // 2. Mark the PartTransTask status is UNSERVED, it cat revert memory until all LogEntryTask callback
  int remove_task(const bool is_ddl_part, const PartTransID &trans_id);

  int insert_commit_trans(const transaction::ObTransID &trans_id,
      const TransCommitInfo &trans_commit_info);

  // Look up transaction table based on trans_id, determine if it is a commit transaction
  int find_commit_trans_info(const transaction::ObTransID &trans_id,
      bool &is_commit_trans);

  // Assign a task based on trans_id
  int alloc_task(const PartTransID &trans_id, PartTransTask *&task);

  // Get the corresponding task based on trans_id
  int get_task(const PartTransID &trans_id, PartTransTask *&task);

  // Get the progress of the assignment and ensure atomicity
  int get_dispatch_progress(int64_t &progress, PartTransDispatchInfo &dispatch_info);

  // Get TPS information
  double get_tps();

  const common::ObPartitionKey &get_partition() const { return pkey_; }
  const char *get_pkey_str() const { return pkey_str_; }

  int64_t get_checkpoint() const { return ATOMIC_LOAD(&checkpoint_); }

  int update_checkpoint(int64_t checkpoint);

public:
  TO_STRING_KV(K_(pkey_str),
      K_(init_dispatch_progress),
      K_(last_dispatch_progress),
      K_(last_dispatch_log_id),
      K_(task_count_only_in_map),
      "task_queue_size", task_queue_.size(),
      K_(checkpoint));

protected:
  void update_status_after_consume_task_(const int64_t task_tstamp, const uint64_t prepare_log_id);
  int dispatch_part_trans_task_(PartTransTask &task, volatile bool &stop_flag);
  int handle_before_fetcher_dispatch_(PartTransTask &task);
  int handle_dml_trans_before_fetcher_dispatch_(PartTransTask &task);
  void push_task_queue_(PartTransTask &task);
  PartTransTask* pop_task_queue_();
  int64_t get_total_task_count_();
  int check_task_ready_(PartTransTask &task, bool &task_is_ready);

protected:
  common::ObPartitionKey  pkey_;
  const char              *pkey_str_;

  // Constructors initialise variables
  TaskPool                &task_pool_;
  // Map is shared globally by all partitions and holds all transactions that have not yet been committed
  PartTransTaskMap        &task_map_;                   // Map for assembling partitioned transactions
  // Shared globally by all partitions, transaction information with commit status is stored
  TransCommitMap          &trans_commit_map_;
  IObLogFetcherDispatcher &dispatcher_;

  // Partitioned transaction sequencing queue
  //
  // holds the tasks in this partition that have been prepped but not yet exported, which have an intersection with the tasks in task_map_
  // special treatment of tasks in the intersection when recycling tasks
  //
  // The queue itself is thread-safe and internally lock-controlled
  SafeTaskWithRecordQueue task_queue_;

  int64_t                 init_dispatch_progress_;  // init progress
  int64_t                 last_dispatch_progress_;  // dispatch progress
  uint64_t                last_dispatch_log_id_;    // The last log ID of the task that has been output, the prepare log ID
  int64_t                 task_count_only_in_map_;  // Number of tasks in map only

  // 1. maintain a partition level checkpoint value for single machine multipartition transaction posting
  // 2. advance this value in both the partition resolution prepare log and the checkpoint log
  // 3. ensure monotonic incrementing
  int64_t                 checkpoint_;

  // Statistical values
  int64_t                 created_trans_count_;         // Number of created transactions counted
  int64_t                 last_created_trans_count_;    // Number of last created transactions counted
  int64_t                 last_stat_time_;              // time of last statistical

  // consumption lock, if you want to consume tasks in task_queue_, you have to add this lock
  //
  // The usage model for this class is: single-threaded production, multi-threaded consumption
  //
  // The mutual exclusion between production and consumption is guaranteed by the lock on task_queue_ itself,
  // while the mutual exclusion between consumption and consumption is guaranteed by dispatch_lock_.
  //
  // In order to ensure that get_dispatch_progress() accesses the next element to be dispatched is atomic,
  // i.e. the whole process from popping out of the queue to dispatch completion has to be atomic for get_dispatch_progress(),
  // otherwise the dispatched progress obtained is not correct. therefore, get_dispatch_progress() should also add dispatch_lock_
  common::ObByteLock      dispatch_lock_;

private:
  DISALLOW_COPY_AND_ASSIGN(PartTransDispatcher);
};

}
}

#endif
