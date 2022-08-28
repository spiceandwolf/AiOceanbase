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

#ifndef _ALL_MOCK_H_
#define _ALL_MOCK_H_

#ifndef private
#define private public
#endif
#ifndef protected
#define protected public
#endif

#include "observer/ob_server.h"

using namespace oceanbase::storage;

void all_mock_init()
{
  static bool inited = false;
  if (!inited) {
    OBSERVER.init_global_context();
    OBSERVER.init_schema();
    OBSERVER.init_tz_info_mgr();
    ((ObPartitionService*)GCTX.par_ser_)->cp_fty_ = &OBSERVER.partition_cfy_;
    ((ObPartitionService*)GCTX.par_ser_)->txs_ = OBSERVER.partition_cfy_.get_trans_service();
    ((ObPartitionService*)GCTX.par_ser_)->is_inited_ = true;
    inited = true;
  }
}

#endif /* _ALL_MOCK_H_ */
