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

#include <iostream>
#include <sstream>
#include <iterator>
#include <string.h>
#include "share/ob_define.h"
#include "ob_admin_executor.h"
#include "clog_tool/ob_admin_clog_v2_executor.h"
#include "usec_tool/ob_admin_usec_executor.h"
#include "slog_tool/ob_admin_slog_executor.h"
#include "dumpsst/ob_admin_dumpsst_executor.h"
#include "dumpsst/ob_admin_cmp_micro_executor.h"
#include "archive_tool/ob_admin_log_archive_executor.h"
#include "backup_tool/ob_admin_dump_backup_data_executor.h"

using namespace oceanbase::common;
using namespace oceanbase::tools;

void print_usage()
{
  fprintf(stderr,
      "\nUSAGE:\n"
      "        ob_admin clog_tool\n"
      "        ob_admin usec_tool\n"
      "        ob_admin slog_tool\n"
      "        ob_admin dumpsst\n"
      "        ob_admin archive_tool\n"
      "        ob_admin dump_backup\n");
}

int main(int argc, char *argv[])
{
  int ret = 0;
  OB_LOGGER.set_log_level("INFO");
  OB_LOGGER.set_file_name("ob_admin.log", true, false, "ob_admin_rs.log");
  const char *log_level = getenv("OB_ADMIN_LOG_LEVEL");
  if (NULL != log_level) {
    OB_LOGGER.set_log_level(log_level);
  }
  std::ostringstream ss;
  copy(argv, argv + argc, std::ostream_iterator<char *>(ss, " "));
  _OB_LOG(INFO, "cmd: [%s]", ss.str().c_str());

  ObAdminExecutor *executor = NULL;
  if (argc < 2) {
    print_usage();
  } else {
    if (0 == strcmp("clog_tool", argv[1])) {
      executor = new ObAdminClogV2Executor();
    } else if (0 == strcmp("usec_tool", argv[1])) {
      executor = new ObAdminUsecExecutor();
    } else if (0 == strcmp("slog_tool", argv[1])) {
      executor = new ObAdminSlogExecutor();
    } else if (0 == strcmp("dumpsst", argv[1])) {
      executor = new ObAdminDumpsstExecutor();
    } else if (0 == strcmp("cmp_micro", argv[1])) {
      executor = new ObAdminCmpMicroExecutor();
    } else if (0 == strcmp("archive_tool", argv[1])) {
      executor = new ObAdminLogArchiveExecutor();
    } else if (0 == strcmp("dump_backup", argv[1])) {
      executor = new ObAdminDumpBackupDataExecutor();
    } else {
      print_usage();
    }

    if (NULL != executor) {
      if (OB_FAIL(executor->execute(argc, argv))) {
        COMMON_LOG(WARN, "Fail to executor cmd, ", K(ret));
      }
      delete executor;
    }
  }
  return ret;
}
