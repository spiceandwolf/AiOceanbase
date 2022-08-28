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

#ifndef SRC_OBSERVER_VIRTUAL_TABLE_OB_ALL_VIRTUAL_BACKUP_CLEAN_INFO_H_
#define SRC_OBSERVER_VIRTUAL_TABLE_OB_ALL_VIRTUAL_BACKUP_CLEAN_INFO_H_

#include "share/ob_virtual_table_scanner_iterator.h"
#include "share/ob_scanner.h"
#include "common/row/ob_row.h"
#include "share/backup/ob_backup_struct.h"

namespace oceanbase {
namespace storage {
class ObIPartitionGroupIterator;
}
namespace observer {
class ObAllVirtualBackupCleanInfo : public common::ObVirtualTableScannerIterator {
  enum COLUMN_ID_LIST {
    TENANT_ID = common::OB_APP_MIN_COLUMN_ID,
    JOB_ID,
    START_TIME,
    END_TIME,
    INCARNATION,
    TYPE,
    STATUS,
    PARAMETER,
    ERROR_MSG,
    COMMENT,
    CLOG_GC_SNAPSHOT,
    RESULT,
    COPY_ID,
  };

public:
  ObAllVirtualBackupCleanInfo();
  virtual ~ObAllVirtualBackupCleanInfo();
  int init(common::ObMySQLProxy& sql_proxy);
  virtual void reset() override;
  virtual int inner_get_next_row(common::ObNewRow*& row) override;

private:
  int inner_get_next_row_(common::ObNewRow*& row);

private:
  bool is_inited_;
  ObMySQLProxy::MySQLResult res_;
  sqlclient::ObMySQLResult* result_;
  share::ObBackupCleanInfo clean_info_;
  ObArray<uint64_t> tenant_ids_;
  int64_t index_;
  common::ObMySQLProxy* sql_proxy_;
  ObSqlString sql_;

private:
  DISALLOW_COPY_AND_ASSIGN(ObAllVirtualBackupCleanInfo);
};

}  // namespace observer
}  // namespace oceanbase
#endif /* SRC_OBSERVER_VIRTUAL_TABLE_OB_ALL_VIRTUAL_RESERVED_TABLE_MGR_H_ */
