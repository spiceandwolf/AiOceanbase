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

#include "ob_gts_local_cache.h"
#include "ob_gts_task_queue.h"
#include "ob_ts_mgr.h"
#include "ob_trans_event.h"

namespace oceanbase {

using namespace common;

namespace transaction {

int ObGTSTaskQueue::init(const ObGTSCacheTaskType& type)
{
  int ret = OB_SUCCESS;
  if (is_inited_) {
    ret = OB_INIT_TWICE;
    TRANS_LOG(WARN, "gts task queue init twice", KR(ret), K(type));
  } else if (GET_GTS != type && WAIT_GTS_ELAPSING != type) {
    ret = OB_INVALID_ARGUMENT;
    TRANS_LOG(WARN, "invalid gts task type", KR(ret), K(type));
  } else {
    task_type_ = type;
    is_inited_ = true;
    TRANS_LOG(INFO, "gts task queue init success", KP(this), K(type));
  }
  return ret;
}

void ObGTSTaskQueue::destroy()
{
  if (is_inited_) {
    is_inited_ = false;
  }
}

void ObGTSTaskQueue::reset()
{
  is_inited_ = false;
  task_type_ = INVALID_GTS_TASK_TYPE;
}

int ObGTSTaskQueue::foreach_task(
    const MonotonicTs srr, const int64_t gts, const int64_t local_trans_version, const MonotonicTs receive_gts_ts)
{
  int ret = OB_SUCCESS;
  if (!is_inited_) {
    ret = OB_NOT_INIT;
  } else if (0 >= srr.mts_ || 0 >= gts) {
    ret = OB_INVALID_ARGUMENT;
    TRANS_LOG(WARN, "invalid argument", KR(ret), K(srr), K(gts));
  } else {
    while (OB_SUCCESS == ret) {
      common::ObLink* data = NULL;
      (void)queue_.pop(data);
      ObTsCbTask* task = static_cast<ObTsCbTask*>(data);
      if (NULL == task) {
        break;
      } else {
        const uint64_t tenant_id = task->get_tenant_id();
        if (GET_GTS == task_type_) {
          if (OB_FAIL(task->get_gts_callback(srr, max(gts, local_trans_version), receive_gts_ts))) {
            if (OB_EAGAIN != ret) {
              TRANS_LOG(WARN, "get gts callback failed", KR(ret), K(srr), K(gts), KP(task));
            }
          } else {
            TRANS_LOG(DEBUG, "get gts callback success", K(srr), K(gts), KP(task));
          }
        } else if (WAIT_GTS_ELAPSING == task_type_) {
          if (OB_FAIL(task->gts_elapse_callback(srr, gts))) {
            if (OB_EAGAIN != ret) {
              TRANS_LOG(WARN, "gts elapse callback failed", KR(ret), K(srr), K(gts), KP(task));
            }
          } else {
            TRANS_LOG(DEBUG, "gts elapse callback success", K(srr), K(gts), KP(task));
          }
        } else {
          ret = OB_ERR_UNEXPECTED;
          TRANS_LOG(WARN, "unknown gts task type", KR(ret), K_(task_type));
        }
        if (OB_EAGAIN == ret) {
          // rewrite ret
          ret = OB_SUCCESS;
          if (OB_FAIL(queue_.push(task))) {
            TRANS_LOG(ERROR, "push gts task failed", KR(ret), KP(task));
          } else {
            TRANS_LOG(DEBUG, "push back gts task", KP(task));
            break;
          }
        } else {
          // do nothing
        }
      }
    }
  }
  return ret;
}

int ObGTSTaskQueue::push(ObTsCbTask* task)
{
  int ret = OB_SUCCESS;
  if (!is_inited_) {
    ret = OB_NOT_INIT;
    TRANS_LOG(WARN, "not inited", KR(ret));
  } else if (NULL == task) {
    ret = OB_INVALID_ARGUMENT;
    TRANS_LOG(WARN, "invalid argument", KR(ret), KP(task));
  } else if (OB_FAIL(queue_.push(task))) {
    TRANS_LOG(ERROR, "push gts task failed", K(ret), KP(task));
  } else {
    TRANS_LOG(DEBUG, "push gts task success", KP(task));
  }
  return ret;
}

}  // namespace transaction
}  // namespace oceanbase
