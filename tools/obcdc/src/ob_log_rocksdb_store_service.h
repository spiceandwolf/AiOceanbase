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

// Copyright 2020-2030 Alibaba Inc. All Rights Reserved.

#ifndef OCEANBASE_LIBOBLOG_OB_LOG_ROCKSDB_IMPL_H_
#define OCEANBASE_LIBOBLOG_OB_LOG_ROCKSDB_IMPL_H_

#include "ob_log_store_service.h"
#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"
#include "rocksdb/iostats_context.h"
#include "rocksdb/perf_context.h"

namespace oceanbase
{
namespace liboblog
{
class RocksDbStoreService : public IObStoreService
{
public:
  RocksDbStoreService();
  virtual ~RocksDbStoreService();
  int init(const std::string &path);
  void destroy();

public:
  // Default ColumnFamily put/get/del
  // Assign ColumnFamily put/get/del
  virtual int put(const std::string &key, const ObSlice &value);
  virtual int put(void *cf_handle, const std::string &key, const ObSlice &value);

  virtual int batch_write(void *cf_handle, const std::vector<std::string> &keys, const std::vector<ObSlice> &values);

  virtual int get(const std::string &key, std::string &value);
  virtual int get(void *cf_handle, const std::string &key, std::string &value);

  virtual int del(const std::string &key);
  virtual int del(void *cf_handle, const std::string &key);
  virtual int del_range(void *cf_handle, const std::string &begin_key, const std::string &end_key);

  virtual int create_column_family(const std::string& column_family_name,
      void *&cf_handle);
  virtual int drop_column_family(void *cf_handle);
  virtual int destory_column_family(void *cf_handle);

  virtual int close();
  virtual void get_mem_usage(const std::vector<uint64_t> ids,
      const std::vector<void *> cf_handles);

private:
  int init_dir_(const char *dir_path);

private:
  bool is_inited_;
  rocksdb::DB *m_db_;
  rocksdb::Options m_options_;
  std::string m_db_path_;
};

}
}

#endif
