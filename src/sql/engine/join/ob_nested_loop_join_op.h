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

#ifndef OCEANBASE_SQL_ENGINE_JOIN_OB_NESTED_LOOP_JOIN_OP_
#define OCEANBASE_SQL_ENGINE_JOIN_OB_NESTED_LOOP_JOIN_OP_

#include "sql/engine/join/ob_basic_nested_loop_join_op.h"
#include "sql/engine/basic/ob_chunk_datum_store.h"

namespace oceanbase {
namespace sql {
class ObNestedLoopJoinSpec : public ObBasicNestedLoopJoinSpec {
  OB_UNIS_VERSION_V(1);

public:
  static const int64_t DEFAULT_BATCH_SIZE = 1000;
  ObNestedLoopJoinSpec(common::ObIAllocator& alloc, const ObPhyOperatorType type)
      : ObBasicNestedLoopJoinSpec(alloc, type), use_group_(false), batch_size_(DEFAULT_BATCH_SIZE)
  {}

public:
  // for group nested loop join.
  bool use_group_;
  int64_t batch_size_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObNestedLoopJoinSpec);
};

// Nest loop join has no expression result overwrite problem:
//
// LEFT:
// Only overwrite by get row from left_store_ (left_store_iter_.get_next_row())
// in batch nest loop join. When get the last row of the batch from store, left child's output
// is recovered, it's safe to get row from child again (read next batch).
//
// RIGHT:
// Overwrite in blank_right_row(), right child is iterated end when blanked.
//
class ObNestedLoopJoinOp : public ObBasicNestedLoopJoinOp {
public:
  enum ObJoinState { JS_JOIN_END = 0, JS_READ_LEFT, JS_READ_RIGHT, JS_STATE_COUNT };
  enum ObFuncType { FT_ITER_GOING = 0, FT_ITER_END, FT_TYPE_COUNT };

  ObNestedLoopJoinOp(ObExecContext& exec_ctx, const ObOpSpec& spec, ObOpInput* input);

  virtual int inner_open() override;
  virtual int switch_iterator() override;
  virtual int rescan() override;
  virtual int inner_get_next_row() override;
  virtual void destroy() override
  {
    left_store_.reset();
    left_store_iter_.reset();
    last_store_row_.reset();
    if (nullptr != mem_context_) {
      DESTROY_CONTEXT(mem_context_);
      mem_context_ = nullptr;
    }
    ObBasicNestedLoopJoinOp::destroy();
  }

private:
  // state operation and transfer function type.
  typedef int (ObNestedLoopJoinOp::*state_operation_func_type)();
  typedef int (ObNestedLoopJoinOp::*state_function_func_type)();
  int join_row_with_semi_join();
  // JS_JOIN_END state operation and transfer functions.
  int join_end_operate();
  int join_end_func_end();
  // JS_READ_LEFT state operation and transfer functions.
  int read_left_operate();
  int group_read_left_operate();
  int deep_copy_dynamic_obj();
  int read_left_func_going();
  int read_left_func_end();
  // JS_READ_RIGHT state operation and transfer functions.
  int read_right_operate();
  int read_right_func_going();
  int read_right_func_end();
  // state operations and transfer functions array.
  state_operation_func_type state_operation_func_[JS_STATE_COUNT];
  state_function_func_type state_function_func_[JS_STATE_COUNT][FT_TYPE_COUNT];
  bool is_full() const;
  // used for rescan and switch iter
  virtual void reset_buf_state();
  int set_param_null();

public:
  ObJoinState state_;
  // for bnl join
  lib::MemoryContext mem_context_;
  ObChunkDatumStore left_store_;
  ObChunkDatumStore::Iterator left_store_iter_;
  bool is_left_end_;
  ObChunkDatumStore::ShadowStoredRow last_store_row_;
  bool save_last_row_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObNestedLoopJoinOp);
};

}  // end namespace sql
}  // end namespace oceanbase
#endif
