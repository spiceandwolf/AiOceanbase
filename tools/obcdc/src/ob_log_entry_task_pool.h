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

#ifndef OCEANBASE_SRC_LIBOBLOG_OB_LOG_ENTRY_TASK_POOL_
#define OCEANBASE_SRC_LIBOBLOG_OB_LOG_ENTRY_TASK_POOL_

#include "lib/objectpool/ob_small_obj_pool.h"   // ObSmallObjPool
#include "common/ob_partition_key.h"            // ObPartitionKey
#include "ob_log_part_trans_task.h"             // ObLogEntryTask

namespace oceanbase
{
namespace liboblog
{
class IObLogEntryTaskPool
{
public:
  virtual ~IObLogEntryTaskPool() {}

public:
  virtual int alloc(ObLogEntryTask *&task,
      void *host) = 0;
  virtual void free(ObLogEntryTask *task) = 0;
  virtual int64_t get_alloc_count() const = 0;
  virtual void print_stat_info() const = 0;
};

//////////////////////////////////////////////////////////////////////////////

// ObLogEntryTaskPool
class ObLogEntryTaskPool : public IObLogEntryTaskPool
{
  typedef common::ObSmallObjPool<ObLogEntryTask> LogEntryTaskPool;

public:
  ObLogEntryTaskPool();
  virtual ~ObLogEntryTaskPool();

public:
  int alloc(ObLogEntryTask *&log_entry_task,
      void *host);
  void free(ObLogEntryTask *log_entry_task);
  int64_t get_alloc_count() const;
  void print_stat_info() const;

public:
  int init(const int64_t fixed_task_count);
  void destroy();

private:
  bool             inited_;
  LogEntryTaskPool pool_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObLogEntryTaskPool);
};

} // namespace liboblog
} // namespace oceanbase
#endif
