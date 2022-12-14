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

#include "storage/ob_slog_writer_queue_thread.h"
#include "storage/ob_partition_service.h"
#include "lib/oblog/ob_log_module.h"
#include "share/ob_thread_mgr.h"

namespace oceanbase {
using namespace common;
namespace storage {

ObMsInfoTask& ObMsInfoTask::operator=(const ObMsInfoTask& rv)
{
  if (this != &rv) {
    this->set_pkey(rv.get_pkey());
    this->set_server(rv.get_server());
    this->set_cluster_id(rv.get_cluster_id());
    this->set_ms_log_id(rv.get_ms_log_id());
    this->set_mc_timestamp(rv.get_mc_timestamp());
    this->set_gen_ts(rv.get_gen_ts());
    this->set_replica_num(rv.get_replica_num());
    this->set_ms_proposal_id(rv.get_ms_proposal_id());
    (void)this->update_prev_member_list(rv.get_prev_member_list());
    (void)this->update_curr_member_list(rv.get_curr_member_list());
    STORAGE_LOG(INFO, "assign ObMsInfoTask finished", K(*this));
  }
  return *this;
}

void ObMsInfoTask::set_pkey(const common::ObPartitionKey& pkey)
{
  pkey_ = pkey;
}

void ObMsInfoTask::set_server(const common::ObAddr& server)
{
  server_ = server;
}

void ObMsInfoTask::set_cluster_id(const int64_t cluster_id)
{
  cluster_id_ = cluster_id;
}

void ObMsInfoTask::set_log_type(const clog::ObLogType log_type)
{
  log_type_ = log_type;
}

void ObMsInfoTask::set_ms_log_id(const uint64_t ms_log_id)
{
  ms_log_id_ = ms_log_id;
}

void ObMsInfoTask::set_mc_timestamp(const int64_t mc_timestamp)
{
  mc_timestamp_ = mc_timestamp;
}

void ObMsInfoTask::set_gen_ts(const int64_t gen_ts)
{
  gen_ts_ = gen_ts;
}

void ObMsInfoTask::set_replica_num(const int64_t replica_num)
{
  replica_num_ = replica_num;
}

void ObMsInfoTask::set_ms_proposal_id(const common::ObProposalID& ms_proposal_id)
{
  ms_proposal_id_ = ms_proposal_id;
}

int ObMsInfoTask::update_prev_member_list(const common::ObMemberList& prev_member_list)
{
  int ret = OB_SUCCESS;
  if (OB_SUCCESS != (ret = prev_member_list_.deep_copy(prev_member_list))) {
    STORAGE_LOG(WARN, "prev_member_list deep_copy failed", K(ret), K(pkey_));
  } else {
    STORAGE_LOG(INFO, "update_prev_member_list success", K(*this));
  }
  return ret;
}

int ObMsInfoTask::update_curr_member_list(const common::ObMemberList& curr_member_list)
{
  int ret = OB_SUCCESS;
  if (OB_SUCCESS != (ret = curr_member_list_.deep_copy(curr_member_list))) {
    STORAGE_LOG(WARN, "curr_member_list deep_copy failed", K(ret), K(pkey_));
  } else {
    STORAGE_LOG(INFO, "update_curr_member_list success", K(*this));
  }
  return ret;
}

ObSlogWriterQueueThread::ObSlogWriterQueueThread() : inited_(false), partition_service_(NULL), free_queue_(), tg_id_(-1)
{}

ObSlogWriterQueueThread::~ObSlogWriterQueueThread()
{
  destroy();
}

void ObSlogWriterQueueThread::destroy()
{
  int ret = OB_SUCCESS;
  inited_ = false;
  partition_service_ = NULL;
  ObMsInfoTask *task = nullptr;
  while (OB_SUCC(free_queue_.pop((ObLink *&)task))) {
    if (OB_NOT_NULL(task)) {
      ob_free(task);
    }
  }
  STORAGE_LOG(INFO, "ObSlogWriterQueueThread destroy");
}

int ObSlogWriterQueueThread::init(ObPartitionService* partition_service, int tg_id)
{
  int ret = OB_SUCCESS;
  tg_id_ = tg_id;
  if (inited_) {
    ret = OB_INIT_TWICE;
    STORAGE_LOG(WARN, "ObSlogWriterQueueThread has already been inited", K(ret));
  } else if (OB_ISNULL(partition_service)) {
    ret = OB_INVALID_ARGUMENT;
    STORAGE_LOG(WARN, "invalid argument", K(ret), KP(partition_service));
  } else if (OB_FAIL(TG_SET_HANDLER_AND_START(tg_id_, *this))) {
    STORAGE_LOG(WARN, "ObSimpleThreadPool inited error.", K(ret));
  } else {
    partition_service_ = partition_service;
    inited_ = true;
    STORAGE_LOG(INFO, "ObSlogWriterQueueThread init success", K_(tg_id));
  }
  if (OB_SUCCESS != ret && !inited_) {
    destroy();
  }
  return ret;
}

int ObSlogWriterQueueThread::get_task(ObMsInfoTask*& task)
{
  int ret = OB_SUCCESS;
  if (!inited_) {
    ret = OB_NOT_INIT;
    STORAGE_LOG(WARN, "ObSlogWriterQueueThread not init", K(ret));
  } else if (OB_SUCC(free_queue_.pop((ObLink *&)task))) {
    // do nothing
  } else if (OB_SUCC(alloc_task(task))) {
    // do nothing
  } else {
    STORAGE_LOG(ERROR, "get task failed");
  }
  return ret;
}

int ObSlogWriterQueueThread::alloc_task(ObMsInfoTask *&task)
{
  const ObMemAttr attr(common::OB_SERVER_TENANT_ID, ObModIds::OB_CALLBACK_TASK);
  int ret = OB_SUCCESS;
  if (OB_ISNULL(task = (ObMsInfoTask *)ob_malloc(sizeof(ObMsInfoTask), attr))) {
    ret = OB_ALLOCATE_MEMORY_FAILED;
    STORAGE_LOG(WARN, "alloc task failed");
  } else {
    task = new (task) ObMsInfoTask;
  }
  return ret;
}

void ObSlogWriterQueueThread::free_task(ObMsInfoTask* task)
{
  int tmp_ret = OB_SUCCESS;
  if (!inited_) {
    tmp_ret = OB_NOT_INIT;
    STORAGE_LOG(ERROR, "ObSlogWriterQueueThread not init", K(tmp_ret));
  } else if (OB_ISNULL(task)) {
    tmp_ret = OB_INVALID_ARGUMENT;
    STORAGE_LOG(ERROR, "ObSlogWriterQueueThread invalid argument", K(tmp_ret), K(task));
  } else if (free_queue_.size() >= MAX_FREE_TASK_NUM) {
    ob_free(task);
  } else if (OB_UNLIKELY(OB_SUCCESS != (tmp_ret = free_queue_.push(task)))) {
    STORAGE_LOG(WARN, "push free task failed", K(tmp_ret));
    ob_free(task);
  }
}

int ObSlogWriterQueueThread::push(const ObMsInfoTask* task)
{
  int ret = OB_SUCCESS;
  ObMsInfoTask* saved_task = NULL;
  if (!inited_) {
    ret = OB_NOT_INIT;
    STORAGE_LOG(WARN, "ObSlogWriterQueueThread is not initialized", K(ret));
  } else if (!task->is_valid()) {
    ret = OB_INVALID_ARGUMENT;
    STORAGE_LOG(WARN, "invalid argument", K(ret), K(*task));
  } else if (OB_FAIL(get_task(saved_task))) {
    STORAGE_LOG(WARN, "get free task failed", K(ret));
  } else if (OB_ISNULL(saved_task)) {
    ret = OB_ERR_UNEXPECTED;
    STORAGE_LOG(WARN, "Unexpected error, saved_task shouldn't be null", K(ret));
  } else {
    *saved_task = *task;
    if (OB_SUCC(TG_PUSH_TASK(tg_id_, saved_task))) {
      STORAGE_LOG(TRACE, "push task", K(*saved_task));
    } else {
      free_task(saved_task);
      saved_task = NULL;
    }
    if (REACH_TIME_INTERVAL(10 * 1000 * 1000l)) {
      const int64_t queue_num = TG_GET_QUEUE_NUM(tg_id_);
      STORAGE_LOG(INFO, "ObSlogWriterQueueThread state", K(queue_num));
    }
  }
  return ret;
}

void ObSlogWriterQueueThread::handle(void* task)
{
  ObMsInfoTask* saved_task = static_cast<ObMsInfoTask*>(task);
  if (NULL == saved_task) {
    STORAGE_LOG(WARN, "invalid callback task", KP(saved_task));
  } else {
    int tmp_ret = OB_SUCCESS;
    if (OB_SUCCESS != (tmp_ret = partition_service_->process_ms_info_task(*saved_task))) {
      STORAGE_LOG(WARN, "partition service callback failed", K(*saved_task), K(tmp_ret));
    } else {
      STORAGE_LOG(INFO, "run partition service callback task successfully", K(*saved_task));
    }
    free_task(saved_task);
    saved_task = NULL;
  }
}

}  // namespace storage
}  // namespace oceanbase
