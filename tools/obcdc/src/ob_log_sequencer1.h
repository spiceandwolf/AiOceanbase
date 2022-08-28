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

#ifndef OCEANBASE_LIBOBLOG_SEQUENCER_H__
#define OCEANBASE_LIBOBLOG_SEQUENCER_H__

#include <queue>                                    // std::priority_queue
#include <vector>                                   // std::vector
#include "lib/allocator/ob_allocator.h"             // ObIAllocator
#include "lib/thread/ob_multi_fixed_queue_thread.h" // ObMQThread
#include "lib/thread/thread_pool.h"                 // lib::ThreadPool
#include "lib/lock/ob_small_spin_lock.h"            // ObByteLock

#include "ob_log_trans_ctx.h"                       // TransCtx
#include "ob_log_part_trans_task.h"                 // PartTransTask

using namespace oceanbase::logmessage;
namespace oceanbase
{
namespace common
{
class ObString;
}

namespace liboblog
{
class ObLogConfig;
/////////////////////////////////////////////////////////////////////////////////////////
// IObLogSequencer

class IObLogSequencer
{
public:
  enum
  {
    MAX_SEQUENCER_NUM = 64,
    GET_SCHEMA_TIMEOUT = 1 * 1000 * 1000,
  };

  struct SeqStatInfo
  {
    SeqStatInfo() { reset(); }
    ~SeqStatInfo() { reset(); }

    void reset()
    {
      total_part_trans_task_count_ = 0;
      ddl_part_trans_task_count_ = 0;
      dml_part_trans_task_count_ = 0;
      hb_part_trans_task_count_ = 0;
      queue_part_trans_task_count_ = 0;
    }
    int64_t total_part_trans_task_count_ CACHE_ALIGNED;
    int64_t ddl_part_trans_task_count_ CACHE_ALIGNED;
    int64_t dml_part_trans_task_count_ CACHE_ALIGNED;
    int64_t hb_part_trans_task_count_ CACHE_ALIGNED;
    int64_t queue_part_trans_task_count_ CACHE_ALIGNED;
  };

public:
  virtual ~IObLogSequencer() {}
  virtual void configure(const ObLogConfig &config) = 0;

public:
  virtual int start() = 0;
  virtual void stop() = 0;
  virtual void mark_stop_flag() = 0;
  // ObLogFetcherDispatcher single-threaded call
  // ObLogDDLHandler
  // 1. DDL/DML partitioning transaction task
  // 2. Global heartbeat
  virtual int push(PartTransTask *task, volatile bool &stop_flag) = 0;
  virtual void get_task_count(SeqStatInfo &stat_info) = 0;
  virtual int64_t get_thread_num() const = 0;
};


/////////////////////////////////////////////////////////////////////////////////////////

class IObLogTransCtxMgr;
class IObLogTransStatMgr;
class IObLogCommitter;
class IObLogDataProcessor;
class IObLogErrHandler;
class ObLogTenant;

typedef common::ObMQThread<IObLogSequencer::MAX_SEQUENCER_NUM, IObLogSequencer> SequencerThread;

// ObClockGenerator
class ObLogSequencer : public IObLogSequencer, public SequencerThread, public lib::ThreadPool
{
public:
  ObLogSequencer();
  virtual ~ObLogSequencer();

public:
  static bool g_print_participant_not_serve_info;
  void configure(const ObLogConfig &config);

public:
  int start();
  void stop();
  void mark_stop_flag() { SequencerThread::mark_stop_flag(); }
  int push(PartTransTask *task, volatile bool &stop_flag);
  void get_task_count(SeqStatInfo &stat_info);
  int64_t get_thread_num() const { return SequencerThread::get_thread_num(); }
  int handle(void *data, const int64_t thread_index, volatile bool &stop_flag);

public:
  int init(const int64_t thread_num,
      const int64_t queue_size,
      IObLogTransCtxMgr &trans_ctx_mgr,
      IObLogTransStatMgr &trans_stat_mgr,
      IObLogCommitter &trans_committer,
      IObLogDataProcessor &data_processor,
      IObLogErrHandler &err_handler);
  void destroy();

private:
  static const int64_t PRINT_SEQ_INFO_INTERVAL = 10 * _SEC_;
  static const int64_t DATA_OP_TIMEOUT = 1 * _SEC_;
  static const int64_t WAIT_TIMEOUT = 10 * _SEC_;
  typedef liboblog::TransCtxSortElement TrxSortElem;
  typedef liboblog::TransCtxSortElement::TransCtxCmp TrxCmp;
  typedef std::priority_queue<TrxSortElem, std::vector<TrxSortElem>, TrxCmp> TransQueue;

private:
  void run1() final;
  int handle_to_be_sequenced_trans_(TrxSortElem &trx_sort_elem,
      volatile bool &stop_flag);
  int handle_global_hb_part_trans_task_(PartTransTask &part_trans_task,
      volatile bool &stop_flag);
  int handle_part_trans_task_(PartTransTask &part_trans_task,
      volatile bool &stop_flag);

  // First prepare the transaction context
  // If it is confirmed that the partitioned transaction is not serviced, the transaction context returned is empty
  // Note: if a partitioned transaction is returned as being in service, this does not mean that the partitioned transaction is necessarily in service,
  // and the final confirmation of whether the partitioned transaction is in service will have to wait until it is added to the list of participants
  int prepare_trans_ctx_(PartTransTask &part_trans_task,
      bool &is_part_trans_served,
      TransCtx *&trans_ctx,
      volatile bool &stop_flag);
  int handle_not_served_trans_(PartTransTask &part_trans_task, volatile bool &stop_flag);
  int handle_participants_ready_trans_(const bool is_dml_trans,
      TransCtx *trans_ctx,
      volatile bool &stop_flag);
  // Once the participants are gathered, the entire DML transaction is processed
  int handle_dml_trans_(const uint64_t tenant_id, TransCtx &trans_ctx, volatile bool &stop_flag);
  int recycle_resources_after_trans_ready_(TransCtx &trans_ctx, ObLogTenant &tenant);
  int push_task_into_data_processor_(ObLogRowDataIndex &row_data_index, volatile bool &stop_flag);
  int push_task_into_committer_(PartTransTask *task,
      const int64_t task_count,
      volatile bool &stop_flag,
      ObLogTenant *tenant);
  void do_stat_for_part_trans_task_count_(PartTransTask &part_trans_task,
      const int64_t task_count);

  // Constructs a chain of all statement binlogs of partitioned transactions in a distributed transaction for output to the user queue
  int build_binlog_record_list_(TransCtx &trans_ctx,
      PartTransTask *part,
      ObLogRowDataIndex *&br_head,
      ObLogRowDataIndex *&br_tail,
      uint64_t &valid_br_num,
      int64_t &valid_part_trans_task_count,
      volatile bool &stop_flag);
  // Build the binlog_record list in the order of the partitions in the PartTransTask list
  int build_binlog_record_list_order_by_partition_(TransCtx &trans_ctx,
      PartTransTask *part,
      ObLogRowDataIndex *&br_head,
      ObLogRowDataIndex *&br_tail,
      uint64_t &valid_br_num,
      int64_t &valid_part_trans_task_count,
      volatile bool &stop_flag);
  int handle_br_of_part_trans_task_(TransCtx &trans_ctx,
      PartTransTask *part,
      int64_t &valid_br_num,
      ObLogRowDataIndex *&br_head,
      ObLogRowDataIndex *&br_tail);
  // Build a binlog_record chain by sequencing statements within a transaction according to sql_no
  int build_binlog_record_list_order_by_sql_no_(TransCtx &trans_ctx,
      PartTransTask *part,
      ObLogRowDataIndex *&br_head,
      ObLogRowDataIndex *&br_tail,
      uint64_t &valid_br_num,
      int64_t &valid_part_trans_task_count,
      volatile bool &stop_flag);
  // Add DML binlog_record to br_list and count information/print logs etc.
  int add_br_to_br_list_and_statics_(TransCtx &trans_ctx,
      ObLogRowDataIndex *row_data_index,
      ObLogRowDataIndex *&br_head,
      ObLogRowDataIndex *&br_tail,
      uint64_t &valid_br_num,
      int64_t &valid_part_trans_task_count);
  // Add the DML binlog_record to the binlog_record list for output to the user queue
  int add_dml_br_to_binlog_record_list_(TransCtx &trans_ctx,
      ObLogRowDataIndex *row_data_index,
      ObLogRowDataIndex *&br_head,
      ObLogRowDataIndex *&br_tail);

  struct StmtSequerenceCompFunc
  {
    // Statement sort operator: current sort based on sql_no, used to find the minimum value of the heap, used only for sorting DML statements
    bool operator()(const ObLogRowDataIndex *task1, const ObLogRowDataIndex *task2)
    {
      return task1->get_row_seq_no() > task2->get_row_seq_no();
    }
  };

  // 1. statistics on transaction tps and rps (rps before and after Formatter filtering)
  // 2. count tenant rps information
  int do_trans_stat_(const uint64_t tenant_id, const int64_t total_stmt_cnt);

private:
  bool                      inited_;
  uint64_t                  round_value_;
  uint64_t                  heartbeat_round_value_;

  IObLogTransCtxMgr         *trans_ctx_mgr_;
  IObLogTransStatMgr        *trans_stat_mgr_;
  IObLogCommitter           *trans_committer_;
  IObLogDataProcessor       *data_processor_;
  IObLogErrHandler          *err_handler_;

  int64_t                   global_checkpoint_ CACHE_ALIGNED;
  int64_t                   last_global_checkpoint_ CACHE_ALIGNED;
  uint64_t                  global_seq_ CACHE_ALIGNED;
  uint64_t                  br_committer_queue_seq_ CACHE_ALIGNED;
  TransQueue                trans_queue_;
  common::ObByteLock        trans_queue_lock_;

  // Counting the number of partitioned tasks owned by Sequencer
  int64_t                   total_part_trans_task_count_ CACHE_ALIGNED;
  int64_t                   ddl_part_trans_task_count_ CACHE_ALIGNED;
  int64_t                   dml_part_trans_task_count_ CACHE_ALIGNED;
  int64_t                   hb_part_trans_task_count_ CACHE_ALIGNED;
  // Counting the number of partitioned tasks owned by the Sequencer queue
  int64_t                   queue_part_trans_task_count_ CACHE_ALIGNED;

private:
  DISALLOW_COPY_AND_ASSIGN(ObLogSequencer);
};


} // namespace liboblog
} // namespace oceanbase
#endif /* OCEANBASE_LIBOBLOG_SEQUENCER_H__ */
