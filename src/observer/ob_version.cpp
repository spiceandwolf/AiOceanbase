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

#include <stdio.h>
#include "share/ob_version.h"
#include "lib/utility/ob_macro_utils.h"

namespace oceanbase
{
namespace share
{

void get_package_and_svn(char *server_version, int64_t buf_len)
{
  const char *server_version_template = "%s_%s(%s %s)";
  (void) snprintf(server_version, buf_len, server_version_template, PACKAGE_VERSION,
           build_version(), build_date(), build_time());
}

}
}

#ifdef __cplusplus
extern "C" {
#endif

  const char* build_version() { return "1-b4bfa011ceaef428782dcb65ae89190c40b78c2f"; }
  const char* build_time() { return __TIME__; }
  const char* build_date() { return __DATE__; }
  const char* build_flags() { return "Debug"; }
  const char* build_branch() { return "HEAD"; }
  const char* build_info() { return ""; }

#ifdef __cplusplus
}
#endif
