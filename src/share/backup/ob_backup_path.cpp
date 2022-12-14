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

#define USING_LOG_PREFIX SHARE
#include "ob_backup_path.h"

using namespace oceanbase;
using namespace common;
using namespace share;

ObBackupPath::ObBackupPath() : cur_pos_(0)
{
  path_[0] = '\0';
}

ObBackupPath::~ObBackupPath()
{
  reset();
}

void ObBackupPath::reset()
{
  path_[0] = '\0';
  cur_pos_ = 0;
}

int ObBackupPath::trim_right_backslash()
{
  int ret = OB_SUCCESS;
  for (int64_t pos = cur_pos_ - 1; pos >= 0; --pos) {
    if (path_[pos] == '/') {
      path_[pos] = '\0';
      --cur_pos_;
    } else {
      break;
    }
  }

  return ret;
}

int ObBackupPath::init(const common::ObString& backup_root_path)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ != 0) {
    ret = OB_INIT_TWICE;
    LOG_WARN("cannot init twice", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(
                 path_, sizeof(path_), cur_pos_, "%.*s", backup_root_path.length(), backup_root_path.ptr()))) {
    OB_LOG(WARN, "fail to backup_root_path", K(ret), K(backup_root_path));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }

  return ret;
}

int ObBackupPath::join_incarnation(const uint64_t incarnation)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(path_, sizeof(path_), cur_pos_, "/%s_%lu", OB_STR_INCARNATION, incarnation))) {
    LOG_WARN("failed to join incarnation", K(ret), K(incarnation), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }

  return ret;
}

int ObBackupPath::join(const common::ObString& str_path)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (str_path.length() <= 0) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(ret), K(str_path));
  } else if (OB_FAIL(databuff_printf(path_, sizeof(path_), cur_pos_, "/%.*s", str_path.length(), str_path.ptr()))) {
    LOG_WARN("failed to join path", K(ret), K(str_path), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join(const uint64_t int_path)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(path_, sizeof(path_), cur_pos_, "/%lu", int_path))) {
    LOG_WARN("failed to join int path", K(ret), K(int_path), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join(const int64_t v)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", KR(ret), K(*this));
  } else if (OB_UNLIKELY(v < 0)) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", KR(ret), K(v));
  } else if (OB_FAIL(databuff_printf(path_, sizeof(path_), cur_pos_, "/%ld", v))) {
    LOG_WARN("failed to databuff_printf", KR(ret), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    LOG_WARN("fail to trim_right_backslash", K(ret));
  } else { /*do nothing*/
  }
  return ret;
}

int ObBackupPath::join_full_backup_set(const int64_t backup_set_id)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", KR(ret), K(*this));
  } else if (OB_UNLIKELY(backup_set_id < 0)) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret), K(backup_set_id));
  } else if (OB_FAIL(databuff_printf(
                 path_, sizeof(path_), cur_pos_, "/%s_%ld", OB_STRING_BACKUP_FULL_BACKUP_SET, backup_set_id))) {
    LOG_WARN("failed to join full_backup_set", K(ret), K(backup_set_id), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_inc_backup_set(const int64_t backup_set_id)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(
                 path_, sizeof(path_), cur_pos_, "/%s_%ld", OB_STRING_BACKUP_INC_BACKUP_SET, backup_set_id))) {
    LOG_WARN("failed to join inc_backup_set", K(ret), K(backup_set_id), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_meta_index(const int64_t task_id)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(
                 databuff_printf(path_, sizeof(path_), cur_pos_, "/%s_%ld", OB_STRING_BACKUP_META_INDEX, task_id))) {
    LOG_WARN("failed to join sys meta inedx", K(ret), K(task_id), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_meta_file(const int64_t task_id)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(path_, sizeof(path_), cur_pos_, "/%s_%ld", OB_STRING_BACKUP_META_FILE, task_id))) {
    LOG_WARN("failed to join sys meta inedx", K(ret), K(task_id), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_macro_block_file(const int64_t backup_set_id, const int64_t sub_task_id)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(path_,
                 sizeof(path_),
                 cur_pos_,
                 "/%s_%lu.%lu",
                 OB_STRING_BACKUP_MACRO_BLOCK_FILE,
                 backup_set_id,
                 sub_task_id))) {
    LOG_WARN("failed to join macro block file", K(ret), K(backup_set_id), K(sub_task_id), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_macro_block_index(const int64_t backup_set_id, const int64_t retry_cnt)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (0 == retry_cnt &&
             OB_FAIL(databuff_printf(
                 path_, sizeof(path_), cur_pos_, "/%s_%ld", OB_STRING_BACKUP_MACRO_BLOCK_INDEX, backup_set_id))) {
    LOG_WARN("failed to join macro block file", K(ret), K(backup_set_id), K(retry_cnt), K(*this));
  } else if (retry_cnt > 0 && OB_FAIL(databuff_printf(path_,
                                  sizeof(path_),
                                  cur_pos_,
                                  "/%s_%ld.%ld",
                                  OB_STRING_BACKUP_MACRO_BLOCK_INDEX,
                                  backup_set_id,
                                  retry_cnt))) {
    LOG_WARN("failed to join macro block file", K(ret), K(backup_set_id), K(retry_cnt), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_sstable_macro_index(const int64_t backup_set_id, const int64_t retry_cnt)
{
  int ret = OB_SUCCESS;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (0 == retry_cnt &&
             OB_FAIL(databuff_printf(
                 path_, sizeof(path_), cur_pos_, "/%s_%ld", OB_STRING_BACKUP_SSTABLE_MACRO_INDEX, backup_set_id))) {
    LOG_WARN("failed to join macro block file", K(ret), K(backup_set_id), K(retry_cnt), K(*this));
  } else if (retry_cnt > 0 && OB_FAIL(databuff_printf(path_,
                                  sizeof(path_),
                                  cur_pos_,
                                  "/%s_%ld.%ld",
                                  OB_STRING_BACKUP_SSTABLE_MACRO_INDEX,
                                  backup_set_id,
                                  retry_cnt))) {
    LOG_WARN("failed to join macro block file", K(ret), K(backup_set_id), K(retry_cnt), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_archive_pg_key(const common::ObPGKey& pg_key)
{
  int ret = OB_SUCCESS;
  const uint64_t table_id = pg_key.get_table_id();
  const int64_t partition_id = pg_key.get_partition_id();
  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else if (OB_FAIL(databuff_printf(path_, sizeof(path_), cur_pos_, "/%lu_%ld", table_id, partition_id))) {
    LOG_WARN("failed to join archive key", K(ret), K(table_id), K(partition_id), K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "failed to trim right backup slash", K(ret));
  }
  return ret;
}

int ObBackupPath::join_round_and_piece(const int64_t round, const int64_t piece_id, const int64_t piece_create_date)
{
  int ret = OB_SUCCESS;
  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", K(ret), K(*this));
  } else {
    if (OB_BACKUP_NO_SWITCH_PIECE_ID == piece_id) {
      ret = databuff_printf(path_, sizeof(path_), cur_pos_, "/%ld", round);
    } else {
      ret = databuff_printf(path_, sizeof(path_), cur_pos_, "/%ld_%ld_%ld", round, piece_id, piece_create_date);
    }

    if (OB_FAIL(ret)) {
      LOG_WARN("failed to join round_and_piece", K(ret), K(round), K(piece_id), K(piece_create_date), K(*this));
    } else if (OB_FAIL(trim_right_backslash())) {
      OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
    } else { /*do nothing*/
    }
  }
  return ret;
}

common::ObString ObBackupPath::get_obstr() const
{
  return ObString(cur_pos_, path_);
}

ObBackupPath& ObBackupPath::operator=(const ObBackupPath& path)
{
  if (this != &path) {

    if (path.is_empty()) {
      cur_pos_ = 0;
      path_[0] = '\0';
    } else {
      int64_t path_length = path.length();
      MEMCPY(path_, path.get_ptr(), path_length);
      cur_pos_ = path_length;
      path_[path_length] = '\0';
    }
  }
  return *this;
}

uint64_t ObBackupPath::hash() const
{
  uint64_t seed = 0;
  seed = murmurhash(path_, static_cast<int32_t>(strlen(path_)), seed);
  return seed;
}

bool ObBackupPath::operator==(const ObBackupPath& path) const
{
  return (0 == STRCMP(path_, path.get_ptr()) && (cur_pos_ == path.length()));
}

int ObBackupPath::join_backup_set(
    const int64_t full_backup_set_id, const int64_t inc_backup_set_id, const int64_t backup_date)
{
  int ret = OB_SUCCESS;
  const char* backup_type = NULL;

  if (cur_pos_ <= 0) {
    ret = OB_NOT_INIT;
    LOG_WARN("not inited", KR(ret), K(*this));
  } else if (full_backup_set_id <= 0 || inc_backup_set_id <= 0 || inc_backup_set_id < full_backup_set_id ||
             backup_date <= 0) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret), K(full_backup_set_id), K(inc_backup_set_id), K(backup_date));
  } else if (full_backup_set_id == inc_backup_set_id) {
    backup_type = OB_STR_FULL_BACKUP;
  } else {
    backup_type = OB_STR_INC_BACKUP;
  }

  if (OB_FAIL(ret)) {
  } else if (OB_FAIL(databuff_printf(path_,
                 sizeof(path_),
                 cur_pos_,
                 "/%s_%ld_%s_%ld",
                 OB_STRING_BACKUP_FULL_BACKUP_SET,
                 inc_backup_set_id,
                 backup_type,
                 backup_date))) {
    LOG_WARN("failed to join full_backup_set",
        K(ret),
        K(inc_backup_set_id),
        K(full_backup_set_id),
        K(backup_date),
        K(*this));
  } else if (OB_FAIL(trim_right_backslash())) {
    OB_LOG(WARN, "fail to trim_right_backslash", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/
int ObBackupPathUtil::get_cluster_prefix_path(const ObClusterBackupDest& dest, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(path.init(dest.dest_.root_path_))) {
    LOG_WARN("failed to init path", K(ret));
  } else if (OB_FAIL(path.join(dest.cluster_name_))) {
    LOG_WARN("Failed to join cluster name", K(ret));
  } else if (OB_FAIL(path.join(dest.cluster_id_))) {
    LOG_WARN("failed to join cluster_id", K(ret));
  } else if (OB_FAIL(path.join_incarnation(dest.incarnation_))) {
    LOG_WARN("failed to join incarnation", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/cluster_clog_backup_info
int ObBackupPathUtil::get_cluster_clog_backup_info_path(const ObClusterBackupDest& dest, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (OB_FAIL(path.join(OB_STR_CLUSTER_CLOG_BACKUP_INFO))) {
    LOG_WARN("failed to join cluster_clog_backup_info", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/tenant_clog_backup_info
int ObBackupPathUtil::get_tenant_clog_backup_info_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_clog_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get tenant clog path", K(ret), K(tenant_id), K(dest));
  } else if (OB_FAIL(path.join(OB_STR_TENANT_CLOG_BACKUP_INFO))) {
    LOG_WARN("failed to join tenant_clog_backup_info", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/cluster_clog_backup_piece_info
int ObBackupPathUtil::get_cluster_clog_backup_piece_info_path(
    const ObClusterBackupDest& dest, const bool is_backup_backup, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (!is_backup_backup) {
    if (OB_FAIL(path.join(OB_STR_CLUSTER_CLOG_BACKUP_PIECE_INFO))) {
      LOG_WARN("failed to join cluster_clog_backup_piece_info", K(ret));
    }
  } else {
    if (OB_FAIL(path.join(OB_STR_CLUSTER_CLOG_BACKUP_BACKUP_PIECE_INFO))) {
      LOG_WARN("failed to join cluster_clog_backup_backup_piece_info", K(ret));
    }
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/backup_piece_info
// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/backup_backup_piece_info
int ObBackupPathUtil::get_tenant_clog_backup_piece_info_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, const bool is_backup_backup, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();

  if (!dest.is_valid() || OB_INVALID_ID == tenant_id) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(get_tenant_clog_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get tenant clog path", K(ret), K(dest));
  } else if (!is_backup_backup) {
    if (OB_FAIL(path.join(OB_STR_TENANT_CLOG_BACKUP_PIECE_INFO))) {
      LOG_WARN("failed to join tenant_clog_backup_piece_info", K(ret));
    }
  } else {
    if (OB_FAIL(path.join(OB_STR_TENANT_CLOG_BACKUP_BACKUP_PIECE_INFO))) {
      LOG_WARN("failed to join tenant_clog_backup_piece_info", K(ret));
    }
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/piece_dir
int ObBackupPathUtil::get_tenant_clog_backup_piece_dir_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round_id, const int64_t backup_piece_id, const int64_t create_date, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  ObClusterBackupDest cluster_dest;
  char piece_dir_name[OB_BACKUP_PIECE_DIR_NAME_LENGTH];
  path.reset();

  if (!dest.is_valid() || OB_INVALID_ID == tenant_id) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(get_tenant_clog_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get tenant clog path", K(ret), K(tenant_id), K(dest));
  } else {
    if (backup_piece_id != 0) {
      if (OB_FAIL(databuff_printf(
              piece_dir_name, sizeof(piece_dir_name), "%ld_%ld_%ld", round_id, backup_piece_id, create_date))) {
        LOG_WARN("failed to print piece dir name", K(ret), K(round_id), K(backup_piece_id), K(create_date));
      }
    } else {
      if (OB_FAIL(databuff_printf(piece_dir_name, sizeof(piece_dir_name), "%ld", round_id))) {
        LOG_WARN("failed to print piece dir name", K(ret), K(round_id));
      }
    }
  }

  if (FAILEDx(path.join(piece_dir_name))) {
    LOG_WARN("failed to add piece dir", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/single_piece_info
int ObBackupPathUtil::get_tenant_clog_backup_single_piece_info_path(const ObClusterBackupDest& dest,
    const uint64_t tenant_id, const int64_t round_id, const int64_t backup_piece_id, const int64_t create_date,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_clog_backup_piece_dir_path(dest, tenant_id, round_id, backup_piece_id, create_date, path))) {
    LOG_WARN("failed to get tenant clog path", K(ret), K(dest));
  } else if (OB_FAIL(path.join(OB_STR_TENANT_CLOG_SINGLE_BACKUP_PIECE_INFO))) {
    LOG_WARN("failed to join tenant_clog_backup_info", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round
int ObBackupPathUtil::get_cluster_clog_prefix_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date))) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(tenant_id), K(round), K(piece_id), K(piece_create_date), K(ret));
  } else if (OB_FAIL(get_tenant_clog_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get tenant clog path", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join_round_and_piece(round, piece_id, piece_create_date))) {
    LOG_WARN("failed to join round_and_piece", K(tenant_id), K(round), K(piece_id), K(piece_create_date), K(ret));
  } else { /*do nothing*/
  }
  return ret;
}
// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/mount_file
int ObBackupPathUtil::get_tenant_clog_mount_file_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, const int64_t round, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  // mount file is used to detect availability of archvie medium
  const int64_t piece_id = 0;
  const int64_t piece_create_date = 0;

  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round)) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(tenant_id), K(round), K(ret));
  } else if (OB_FAIL(get_cluster_clog_prefix_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get tenant clog path", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join("mount_file"))) {
    LOG_WARN("failed to join round", K(ret));
  }
  return ret;
}

//"oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/data/backup_set_1"
int ObBackupPathUtil::get_tenant_data_full_backup_set_path(
    const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(!path_info.is_valid())) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("ObBackupBaseDataPathInfo is invalid,", K(ret), K(path_info));
  } else if (OB_FAIL(get_tenant_backup_data_path(path_info.dest_, path_info.tenant_id_, path))) {
    LOG_WARN("failed to get tenant backup data path", K(ret), K(path_info));
  } else if (OB_BACKUP_COMPATIBLE_VERSION_V1 == path_info.compatible_) {
    if (OB_FAIL(path.join_full_backup_set(path_info.full_backup_set_id_))) {
      LOG_WARN("failed to join full_backup_set_id_", K(ret));
    }
  } else if (has_independ_inc_backup_set(path_info.compatible_)) {
    if (OB_FAIL(path.join_backup_set(
            path_info.full_backup_set_id_, path_info.inc_backup_set_id_, path_info.backup_date_))) {
      LOG_WARN("failed to join backup_set_id_", K(ret), K(path_info));
    }
  } else {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("path info compatible is invalid", K(ret), K(path_info));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_data_inc_backup_set_path(const ObSimpleBackupSetPath& simple_path, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();
  if (!simple_path.is_valid()) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("simple path is not valid", K(ret), K(simple_path));
  } else if (OB_FAIL(path.init(simple_path.get_simple_path()))) {
    LOG_WARN("failed to init backup path", K(ret), K(simple_path));
  } else if (OB_FAIL(path.join_inc_backup_set(simple_path.backup_set_id_))) {
    LOG_WARN("failed to join inc backup set", K(ret), K(simple_path));
  }
  return ret;
}

// v1: "oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/"
// +"data/backup_set_1/backup_2"
// v2: "oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/"
// +"data/backup_set_2/backup_2"
int ObBackupPathUtil::get_tenant_data_inc_backup_set_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (!path_info.is_valid()) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("get tenant data inc backup set path get invalid argument", K(ret), K(path_info));
  } else if (OB_BACKUP_COMPATIBLE_VERSION_V1 == path_info.compatible_) {
    if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
      LOG_WARN("failed to get full backup path", K(ret));
    } else if (OB_FAIL(path.join_inc_backup_set(path_info.inc_backup_set_id_))) {
      LOG_WARN("failed to join inc_backup_set_id", K(ret));
    }
  } else if (has_independ_inc_backup_set(path_info.compatible_)) {
    if (OB_FAIL(get_tenant_backup_data_path(path_info.dest_, path_info.tenant_id_, path))) {
      LOG_WARN("failed to get tenant backup data path", K(ret), K(path_info));
    } else if (OB_FAIL(path.join_backup_set(
                   path_info.full_backup_set_id_, path_info.inc_backup_set_id_, path_info.backup_date_))) {
      LOG_WARN("failed to join backup_set_id_", K(ret), K(path_info));
    } else if (OB_FAIL(path.join_inc_backup_set(path_info.inc_backup_set_id_))) {
      LOG_WARN("failed to join inc_backup_set_id", K(ret));
    }
  } else {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("path info compatible is invalid", K(ret), K(path_info));
  }
  return ret;
}

// assert task_id is not duplicate
// "oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/data/backup_set_1/backup_2/meta_index_file_1"
int ObBackupPathUtil::get_tenant_data_meta_index_path(
    const ObBackupBaseDataPathInfo& path_info, const int64_t task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join_meta_index(task_id))) {
    LOG_WARN("failed to join sys meta index", K(ret));
  }
  return ret;
}

// for rootserver reform meta index
// "oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/data/backup_set_1/backup_2/meta_index_file"
int ObBackupPathUtil::get_tenant_data_meta_index_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join("/"))) {
    LOG_WARN("failed to set path", K(ret), K(path_info));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_META_INDEX))) {
    LOG_WARN("failed to set path", K(ret), K(path_info));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_data_meta_file_path(
    const share::ObSimpleBackupSetPath& simple_path, const int64_t task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(simple_path, path))) {
    LOG_WARN("failed to get tenant data inc backup set path", K(ret), K(simple_path));
  } else if (OB_FAIL(path.join_meta_file(task_id))) {
    LOG_WARN("failed to join meta file", K(ret), K(task_id));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_data_meta_file_path(
    const ObBackupBaseDataPathInfo& path_info, const int64_t task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join_meta_file(task_id))) {
    LOG_WARN("failed to join meta file", K(ret));
  }
  return ret;
}

// "oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/data/backup_set_1/data/table_id/part_id"
int ObBackupPathUtil::get_tenant_pg_data_path(
    const ObBackupBaseDataPathInfo& path_info, const int64_t table_id, const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get full backup path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to part_id", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_pg_data_path(
    const ObBackupPath& base_path, const int64_t table_id, const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path = base_path;
  if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to part_id", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_sstable_macro_index_path(const ObBackupBaseDataPathInfo& path_info, const int64_t table_id,
    const int64_t part_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_data_path(path_info, table_id, part_id, path))) {
    LOG_WARN("failed to get pg data path", K(ret));
  } else if (OB_FAIL(path.join_sstable_macro_index(path_info.inc_backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join sstable_macro_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_macro_block_index_path(const ObBackupBaseDataPathInfo& path_info, const int64_t table_id,
    const int64_t part_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_data_path(path_info, table_id, part_id, path))) {
    LOG_WARN("failed to get pg data path", K(ret));
  } else if (OB_FAIL(path.join_macro_block_index(path_info.inc_backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_macro_block_index_path(const share::ObSimpleBackupSetPath& simple_path,
    const int64_t table_id, const int64_t part_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(path.init(simple_path.get_simple_path()))) {
    LOG_WARN("failed to init path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to part_id", K(ret));
  } else if (OB_FAIL(path.join_macro_block_index(simple_path.backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_macro_block_file_path(const ObBackupBaseDataPathInfo& path_info, const int64_t table_id,
    const int64_t part_id, const int64_t full_backup_set_id, const int64_t inc_backup_set_id, const int64_t sub_task_id,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  ObBackupBaseDataPathInfo new_path_info;
  const ObBackupBaseDataPathInfo* path_info_ptr = NULL;

  if (OB_BACKUP_COMPATIBLE_VERSION_V1 == path_info.compatible_) {
    path_info_ptr = &path_info;
  } else if (has_independ_inc_backup_set(path_info.compatible_)) {
    if (OB_FAIL(new_path_info.set(path_info.dest_,
            path_info.tenant_id_,
            full_backup_set_id,
            inc_backup_set_id,
            path_info.backup_date_,
            path_info.compatible_))) {
      LOG_WARN("failed to set path info", K(ret), K(path_info));
    } else {
      path_info_ptr = &new_path_info;
    }
  } else {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("backup path info compatible is invalid", K(ret), K(path_info));
  }

  if (OB_FAIL(ret)) {
  } else if (OB_FAIL(get_tenant_pg_data_path(*path_info_ptr, table_id, part_id, path))) {
    LOG_WARN("failed to get pg data path", K(ret));
  } else if (OB_FAIL(path.join_macro_block_file(inc_backup_set_id, sub_task_id))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }

  return ret;
}

int ObBackupPathUtil::get_major_macro_block_file_path(const ObBackupBaseDataPathInfo& path_info, const int64_t table_id,
    const int64_t part_id, const int64_t backup_set_id, const int64_t sub_task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_major_data_path(path_info, table_id, part_id, path))) {
    LOG_WARN("failed to get tenant pg major data path", K(ret), K(path_info));
  } else if (OB_FAIL(path.join_macro_block_file(backup_set_id, sub_task_id))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_major_macro_block_file_path(const ObSimpleBackupSetPath& simple_path, const int64_t table_id,
    const int64_t part_id, const int64_t backup_set_id, const int64_t sub_task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_major_data_path(simple_path, table_id, part_id, path))) {
    LOG_WARN("failed to get tenant pg major data path", K(ret), K(simple_path));
  } else if (OB_FAIL(path.join_macro_block_file(backup_set_id, sub_task_id))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_minor_macro_block_file_path(const ObBackupBaseDataPathInfo& path_info, const int64_t table_id,
    const int64_t part_id, const int64_t backup_set_id, const int64_t backup_task_id, const int64_t sub_task_id,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_pg_minor_data_path(path_info, table_id, part_id, backup_task_id, path))) {
    LOG_WARN("failed to get tenant pg major data path", K(ret), K(path_info));
  } else if (OB_FAIL(path.join_macro_block_file(backup_set_id, sub_task_id))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_minor_macro_block_file_path(const ObSimpleBackupSetPath& simple_path, const int64_t table_id,
    const int64_t part_id, const int64_t backup_set_id, const int64_t backup_task_id, const int64_t sub_task_id,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_pg_minor_data_path(simple_path, table_id, part_id, backup_task_id, path))) {
    LOG_WARN("failed to get tenant pg major data path", K(ret), K(simple_path));
  } else if (OB_FAIL(path.join_macro_block_file(backup_set_id, sub_task_id))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_cluster_data_backup_info_path(const ObClusterBackupDest& dest, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get cluster prefix path", K(ret), K(dest));
  } else if (OB_FAIL(path.join(OB_STRING_CLUSTER_DATA_BACKUP_INFO))) {
    LOG_WARN("failed to join cluster data backup info", K(ret), K(dest));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_data_backup_info_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_backup_data_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get tenant backup data path", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(OB_STRING_TENANT_DATA_BACKUP_INFO))) {
    LOG_WARN("failed to join tenant data backup info", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_backup_set_info_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get tenant data full backup set path", K(ret), K(path_info));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_SET_INFO))) {
    LOG_WARN("failed to join cluster backup set info", K(ret), K(path_info));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_sys_pg_list_path(const ObSimpleBackupSetPath& simple_path, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(simple_path, path))) {
    LOG_WARN("failed to get tenant data inc backup set path", KR(ret), K(simple_path));
  } else if (OB_FAIL(path.join(OB_STRING_SYS_PG_LIST))) {
    LOG_WARN("failed to join normal pg list", KR(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_sys_pg_list_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_SYS_PG_LIST))) {
    LOG_WARN("failed to join sys pg list", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_normal_pg_list_path(const ObSimpleBackupSetPath& simple_path, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(simple_path, path))) {
    LOG_WARN("failed to get tenant data inc backup set path", KR(ret), K(simple_path));
  } else if (OB_FAIL(path.join(OB_STRING_NORMAL_PG_LIST))) {
    LOG_WARN("failed to join normal pg list", KR(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_normal_pg_list_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_NORMAL_PG_LIST))) {
    LOG_WARN("failed to join normal pg list", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_info_path(const ObClusterBackupDest& dest, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get cluster prefix path", K(ret), K(dest));
  } else if (OB_FAIL(path.join(OB_STRING_TENANT_INFO))) {
    LOG_WARN("failed to join tenant info", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_name_info_path(const ObClusterBackupDest& dest, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get cluster prefix path", K(ret), K(dest));
  } else if (OB_FAIL(path.join(OB_STRING_TENANT_NAME_INFO))) {
    LOG_WARN("failed to join tenant info", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_locality_info_path(const ObSimpleBackupSetPath& simple_path, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(simple_path, path))) {
    LOG_WARN("failed to get tenant data inc backup set path", KR(ret), K(simple_path));
  } else if (OB_FAIL(path.join(OB_STRING_TENANT_LOCALITY_INFO))) {
    LOG_WARN("failed to join tenant locality info", KR(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_locality_info_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_TENANT_LOCALITY_INFO))) {
    LOG_WARN("failed to join tenant locality info", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_backup_diagnose_path(const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_inc_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get inc backup path", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_TENANT_DIAGNOSE_INFO))) {
    LOG_WARN("failed to join tenant diagnose info", K(ret));
  }
  return ret;
}

// TODO() make ObArchivePathUtil use same func

int ObBackupPathUtil::get_tenant_clog_data_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_clog_prefix_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get cluster clog prefix path", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join data", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_clog_index_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_cluster_clog_prefix_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get cluster clog prefix path", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_INDEX)))) {
    LOG_WARN("failed to join data", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_table_clog_data_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, const int64_t table_id,
    const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_clog_data_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get tenant clog data path", K(ret), K(dest));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to join table id", K(ret), K(table_id));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to join partition id", K(ret), K(part_id));
  }
  return ret;
}

int ObBackupPathUtil::get_table_clog_index_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, const int64_t table_id,
    const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_clog_index_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get tenant clog index path", K(ret), K(dest));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to join table id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to join partition id", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_table_data_path(
    const ObBackupBaseDataPathInfo& path_info, const int64_t table_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get full backup path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to table_id", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_backup_data_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_clog_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_CLOG))) {
    LOG_WARN("failed to join OB_STRING_BACKUP_CLOG", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_path(const ObClusterBackupDest& dest, const uint64_t tenant_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (OB_FAIL(path.join(tenant_id))) {
    LOG_WARN("failed to join teannt_id", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_cluster_clog_info(const ObClusterBackupDest& dest, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_CLOG_INFO))) {
    LOG_WARN("failed to join clog_info", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_cluster_clog_info_file_path(
    const ObClusterBackupDest& dest, const common::ObString& file_name, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get_cluster_prefix_path", K(ret), K(dest), K(path));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_CLOG_INFO))) {
    LOG_WARN("failed to join clog_info", K(ret));
  } else if (OB_FAIL(path.join(file_name))) {
    LOG_WARN("failed to join file name", K(ret), K(file_name));
  }
  return ret;
}

// 3.x backup minor and major new interface
int ObBackupPathUtil::get_tenant_pg_major_data_path(
    const ObBackupBaseDataPathInfo& path_info, const int64_t table_id, const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get full backup path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to join table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to join part_id", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_MJAOR_DATA))) {
    LOG_WARN("failed to join major data string", K(ret), K(OB_STRING_MJAOR_DATA));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_pg_major_data_path(
    const ObSimpleBackupSetPath& simple_path, const int64_t table_id, const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(path.init(simple_path.get_simple_path()))) {
    LOG_WARN("failed to init path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to part_id", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_MJAOR_DATA))) {
    LOG_WARN("failed to join major data string", K(ret), K(OB_STRING_MJAOR_DATA));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/archive_key/
int ObBackupPathUtil::get_clog_archive_key_prefix(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date))) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(tenant_id), K(round), K(piece_id), K(piece_create_date), K(ret));
  } else if (OB_FAIL(get_cluster_clog_prefix_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get clog prefix", K(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_ARCHIVE_KEY))) {
    LOG_WARN("failed to join archive_key", KR(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_pg_minor_data_path(const ObBackupBaseDataPathInfo& path_info, const int64_t table_id,
    const int64_t part_id, const int64_t task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_minor_dir_path(path_info, table_id, part_id, path))) {
    LOG_WARN("failed to get tenant pg minor dir path", K(ret), K(path_info), K(table_id), K(part_id));
  } else if (OB_FAIL(path.join(task_id))) {
    LOG_WARN("failed to join task_id", K(ret), K(task_id));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_pg_minor_data_path(const ObSimpleBackupSetPath& simple_path, const int64_t table_id,
    const int64_t part_id, const int64_t task_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_minor_dir_path(simple_path, table_id, part_id, path))) {
    LOG_WARN("failed to get tenant pg minor dir path", K(ret), K(simple_path), K(table_id), K(part_id));
  } else if (OB_FAIL(path.join(task_id))) {
    LOG_WARN("failed to join task_id", K(ret), K(task_id));
  }
  return ret;
}

// "oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/data/backup_set_1/
// data/table_id/part_id/major_data/macro_block_index_xxx.xxx"
int ObBackupPathUtil::get_major_macro_block_index_path(const ObBackupBaseDataPathInfo& path_info,
    const int64_t table_id, const int64_t part_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_data_path(path_info, table_id, part_id, path))) {
    LOG_WARN("failed to get pg data path", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_MJAOR_DATA))) {
    LOG_WARN("failed to join major data string", K(ret), K(OB_STRING_MJAOR_DATA));
  } else if (OB_FAIL(path.join_macro_block_index(path_info.inc_backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_major_macro_block_index_path(const ObSimpleBackupSetPath& simple_path, const int64_t table_id,
    const int64_t part_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(path.init(simple_path.get_simple_path()))) {
    LOG_WARN("failed to init backup path", K(ret));
  } else if (OB_FAIL(get_tenant_pg_data_path(path, table_id, part_id, path))) {
    LOG_WARN("failed to get tenant pg data path", KR(ret), K(simple_path), K(table_id), K(part_id));
  } else if (OB_FAIL(path.join(OB_STRING_MJAOR_DATA))) {
    LOG_WARN("failed to join major data string", K(ret), K(OB_STRING_MJAOR_DATA));
  } else if (OB_FAIL(path.join_macro_block_index(simple_path.backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_minor_macro_block_index_path(const ObBackupBaseDataPathInfo& path_info,
    const int64_t table_id, const int64_t part_id, const int64_t task_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_data_path(path_info, table_id, part_id, path))) {
    LOG_WARN("failed to get pg data path", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_MINOR_DATA))) {
    LOG_WARN("failed to join minor data string", K(ret), K(OB_STRING_MINOR_DATA));
  } else if (OB_FAIL(path.join(task_id))) {
    LOG_WARN("failed to join task id", K(ret), K(task_id));
  } else if (OB_FAIL(path.join_macro_block_index(path_info.inc_backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_minor_macro_block_index_path(const ObSimpleBackupSetPath& simple_path, const int64_t table_id,
    const int64_t part_id, const int64_t task_id, const int64_t retry_cnt, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_pg_minor_dir_path(simple_path, table_id, part_id, path))) {
    LOG_WARN("failed to get tenant pg minor dir path", KR(ret), K(simple_path), K(table_id), K(part_id));
  } else if (OB_FAIL(path.join(task_id))) {
    LOG_WARN("failed to join task id", K(ret), K(task_id));
  } else if (OB_FAIL(path.join_macro_block_index(simple_path.backup_set_id_, retry_cnt))) {
    LOG_WARN("failed to join macro_block_index", K(ret));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/archive_key/tid_pid
int ObBackupPathUtil::get_clog_archive_key_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, const common::ObPGKey& pg_key,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date)) ||
      OB_UNLIKELY(!pg_key.is_valid())) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(tenant_id), K(round), K(piece_id), K(piece_create_date), K(pg_key), K(ret));
  } else if (OB_FAIL(get_cluster_clog_prefix_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get clog prefix", KR(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_ARCHIVE_KEY))) {
    LOG_WARN("failed to join archive key", KR(ret), K(OB_STRING_BACKUP_ARCHIVE_KEY));
  } else if (OB_FAIL(path.join_archive_pg_key(pg_key))) {
    LOG_WARN("failed to join pg key", KR(ret), K(pg_key));
  }
  return ret;
}

int ObBackupPathUtil::get_cluster_backup_set_file_info_path(
    const ObClusterBackupDest& dest, const bool is_backup_backup, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_cluster_prefix_path(dest, path))) {
    LOG_WARN("failed to get cluster prefix path", K(ret), K(dest));
  } else if (is_backup_backup) {
    if (OB_FAIL(path.join(OB_STR_CLUSTER_BACKUP_BACKUP_SET_FILE_INFO))) {
      LOG_WARN("failed to join cluster data backup info", K(ret), K(dest));
    }
  } else {
    if (OB_FAIL(path.join(OB_STR_CLUSTER_BACKUP_SET_FILE_INFO))) {
      LOG_WARN("failed to join cluster data backup info", K(ret), K(dest));
    }
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_backup_set_file_info_path(
    const ObClusterBackupDest& dest, const uint64_t tenant_id, const bool is_backup_backup, ObBackupPath& path)
{
  int ret = OB_SUCCESS;

  if (OB_FAIL(get_tenant_backup_data_path(dest, tenant_id, path))) {
    LOG_WARN("failed to get tenant backup data path", K(ret), K(dest), K(tenant_id));
  } else if (is_backup_backup) {
    if (OB_FAIL(path.join(OB_STR_TENANT_BACKUP_BACKUP_SET_FILE_INFO))) {
      LOG_WARN("failed to join tenant data backup info", K(ret));
    }
  } else {
    if (OB_FAIL(path.join(OB_STR_TENANT_BACKUP_SET_FILE_INFO))) {
      LOG_WARN("failed to join cluster data backup info", K(ret), K(dest));
    }
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_single_backup_set_info_path(
    const ObSimpleBackupSetPath& simple_path, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  path.reset();
  if (OB_FAIL(path.init(simple_path.get_simple_path()))) {
    LOG_WARN("failed to init backup path", K(ret));
  } else if (OB_FAIL(path.join(OB_STR_SINGLE_BACKUP_SET_INFO))) {
    LOG_WARN("failed to join backup set info", K(ret));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_single_backup_set_info_path(
    const ObBackupBaseDataPathInfo& path_info, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get tenant data full backup set path", K(ret), K(path_info));
  } else if (OB_FAIL(path.join(OB_STR_SINGLE_BACKUP_SET_INFO))) {
    LOG_WARN("failed to join cluster backup set info", K(ret), K(path_info));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/piece_id/data/tid
int ObBackupPathUtil::get_table_clog_data_dir_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, const uint64_t table_id,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date)) ||
      table_id == 0) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(tenant_id), K(round), K(piece_id), K(piece_create_date), K(table_id), K(ret));
  } else if (OB_FAIL(get_tenant_clog_backup_piece_data_dir_path(
                 dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get clog prefix", KR(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to join table id", KR(ret), K(table_id));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/piece_id/index/tid
int ObBackupPathUtil::get_table_clog_index_dir_path(const ObClusterBackupDest& dest, const uint64_t tenant_id,
    const int64_t round, const int64_t piece_id, const int64_t piece_create_date, const uint64_t table_id,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date)) ||
      table_id == 0) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(tenant_id), K(round), K(piece_id), K(piece_create_date), K(table_id), K(ret));
  } else if (OB_FAIL(get_tenant_clog_backup_piece_index_dir_path(
                 dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get clog prefix", KR(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to join table id", KR(ret), K(table_id));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/piece_id/data
int ObBackupPathUtil::get_tenant_clog_backup_piece_data_dir_path(const ObClusterBackupDest& dest,
    const uint64_t tenant_id, const int64_t round, const int64_t piece_id, const int64_t piece_create_date,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date))) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(ret), K(tenant_id), K(round), K(piece_id), K(piece_create_date));
  } else if (OB_FAIL(
                 get_tenant_clog_backup_piece_dir_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get clog prefix", KR(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_DATA))) {
    LOG_WARN("failed to join path", KR(ret), K(OB_STRING_BACKUP_DATA));
  }
  return ret;
}

// oss:/backup/cluster_name/cluster_id/incarnation_1/tenant_id/clog/round/piece_id/index
int ObBackupPathUtil::get_tenant_clog_backup_piece_index_dir_path(const ObClusterBackupDest& dest,
    const uint64_t tenant_id, const int64_t round, const int64_t piece_id, const int64_t piece_create_date,
    ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(OB_INVALID_TENANT_ID == tenant_id) || OB_UNLIKELY(0 >= round) ||
      OB_UNLIKELY(0 != piece_id && (0 >= piece_create_date || OB_INVALID_TIMESTAMP == piece_create_date))) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(ret), K(tenant_id), K(round), K(piece_id), K(piece_create_date));
  } else if (OB_FAIL(
                 get_tenant_clog_backup_piece_dir_path(dest, tenant_id, round, piece_id, piece_create_date, path))) {
    LOG_WARN("failed to get clog prefix", KR(ret), K(dest), K(tenant_id));
  } else if (OB_FAIL(path.join(OB_STRING_BACKUP_INDEX))) {
    LOG_WARN("failed to join path", KR(ret), K(OB_STRING_BACKUP_INDEX));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_pg_minor_dir_path(
    const ObBackupBaseDataPathInfo& path_info, const int64_t table_id, const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(get_tenant_data_full_backup_set_path(path_info, path))) {
    LOG_WARN("failed to get full backup path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to join table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to part_id", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_MINOR_DATA))) {
    LOG_WARN("failed to join major data string", K(ret), K(OB_STRING_MINOR_DATA));
  }
  return ret;
}

int ObBackupPathUtil::get_tenant_pg_minor_dir_path(
    const ObSimpleBackupSetPath& simple_path, const int64_t table_id, const int64_t part_id, ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  if (OB_FAIL(path.init(simple_path.get_simple_path()))) {
    LOG_WARN("failed to init path", K(ret));
  } else if (OB_FAIL(path.join(ObString::make_string(OB_STRING_BACKUP_DATA)))) {
    LOG_WARN("failed to join tenant_id", K(ret));
  } else if (OB_FAIL(path.join(table_id))) {
    LOG_WARN("failed to table_id", K(ret));
  } else if (OB_FAIL(path.join(part_id))) {
    LOG_WARN("failed to part_id", K(ret));
  } else if (OB_FAIL(path.join(OB_STRING_MINOR_DATA))) {
    LOG_WARN("failed to join major data string", K(ret), K(OB_STRING_MINOR_DATA));
  }
  return ret;
}

int ObBackupMountFile::get_mount_file_path(
    const ObLogArchiveBackupInfo& backup_info, ObClusterBackupDest& cluster_dest, share::ObBackupPath& path)
{
  int ret = OB_SUCCESS;
  share::ObBackupDest dest;
  cluster_dest.reset();
  path.reset();

  if (backup_info.status_.tenant_id_ != OB_SYS_TENANT_ID) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("only sys tenant need check mount file", K(ret), K(backup_info));
  } else if (OB_FAIL(dest.set(backup_info.backup_dest_))) {
    LOG_WARN("failed to set dest", K(ret), K(backup_info));
  } else if (OB_STORAGE_FILE != dest.device_type_) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("only support create mount file for nfs", K(ret), K(backup_info));
  } else if (OB_FAIL(cluster_dest.set(dest, OB_START_INCARNATION))) {
    LOG_WARN("failed to set cluster dest", K(ret), K(dest));
  } else if (OB_FAIL(ObBackupPathUtil::get_tenant_clog_mount_file_path(
                 cluster_dest, backup_info.status_.tenant_id_, backup_info.status_.round_, path))) {
    LOG_WARN("failed to get_cluster_clog_mount_file_path", K(ret), K(backup_info));
  }

  return ret;
}

int ObBackupMountFile::create_mount_file(const ObLogArchiveBackupInfo& backup_info)
{
  int ret = OB_SUCCESS;
  share::ObBackupPath path;
  ObClusterBackupDest cluster_dest;
  ObStorageUtil util(false /*no need retry*/);
  const static int64_t MOUNT_FILE_BUF_LENGTH = 64;
  int64_t pos = 0;
  bool is_exist = false;
  char buf[MOUNT_FILE_BUF_LENGTH];

  if (OB_FAIL(ObBackupMountFile::get_mount_file_path(backup_info, cluster_dest, path))) {
    LOG_WARN("failed to get_mount_file_path", K(ret), K(backup_info));
  } else if (OB_FAIL(util.mk_parent_dir(path.get_obstr(), cluster_dest.get_storage_info()))) {
    LOG_WARN("failed to mk dir", K(ret), K(path));
  } else if (OB_FAIL(util.is_exist(path.get_obstr(), cluster_dest.get_storage_info(), is_exist))) {
    LOG_WARN("failed to check is exist", K(ret), K(path));
  } else if (!is_exist) {
    if (OB_FAIL(databuff_printf(buf, sizeof(buf), pos, "%ld", backup_info.status_.round_))) {
      LOG_WARN("failed to print round", K(ret), K(backup_info));
    } else if (OB_FAIL(util.write_single_file(path.get_obstr(), cluster_dest.get_storage_info(), buf, pos))) {
      LOG_WARN("failed to write mount file", K(ret), K(path), K(pos), K(backup_info));
    } else {
      FLOG_INFO("[BACKUP_MOUNT_FILE]succeed to create mount file", K(backup_info), K(path));
    }
  }

  return ret;
}

int ObBackupMountFile::check_mount_file(const ObLogArchiveBackupInfo& backup_info)
{
  int ret = OB_SUCCESS;
  share::ObBackupPath path;
  ObClusterBackupDest cluster_dest;
  ObStorageUtil util(false /*no need retry*/);
  bool is_exist = false;

  if (OB_FAIL(ObBackupMountFile::get_mount_file_path(backup_info, cluster_dest, path))) {
    LOG_WARN("failed to get_mount_file_path", K(ret), K(backup_info));
  } else if (OB_FAIL(util.is_exist(path.get_obstr(), cluster_dest.get_storage_info(), is_exist))) {
    LOG_WARN("failed to read mount file", K(ret), K(path), K(backup_info));
  } else if (!is_exist) {
    // mk parent dir will force nfs renew dentry
    if (OB_FAIL(util.mk_parent_dir(path.get_obstr(), cluster_dest.get_storage_info()))) {
      LOG_WARN("failed to mk dir", K(ret), K(path));
    } else if (OB_FAIL(util.is_exist(path.get_obstr(), cluster_dest.get_storage_info(), is_exist))) {
      LOG_WARN("failed to read mount file", K(ret), K(path), K(backup_info));
    } else if (!is_exist) {
      ret = OB_BACKUP_MOUNT_FILE_NOT_VALID;
      LOG_ERROR("[BACKUP_MOUNT_FILE]check backup mount file is not exist, maybe nfs is not mounted properly",
          K(ret),
          K(path),
          K(backup_info));
    }
  }

  return ret;
}

int ObBackupMountFile::need_check_mount_file(const ObLogArchiveBackupInfo& info, bool& need_check)
{
  int ret = OB_SUCCESS;
  share::ObBackupDest dest;
  need_check = true;

  if (!info.is_valid()) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid args", K(ret), K(info));
  } else if (OB_FAIL(dest.set(info.backup_dest_))) {
    LOG_WARN("failed to set dest", K(ret), K(info));
  } else if (OB_STORAGE_FILE != dest.device_type_) {
    need_check = false;
  }

  return ret;
}
