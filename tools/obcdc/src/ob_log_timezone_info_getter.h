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

#ifndef OCEANBASE_LIBOBLOG_TIMEZONE_INFO_GETTER_H__
#define OCEANBASE_LIBOBLOG_TIMEZONE_INFO_GETTER_H__

#include "lib/mysqlclient/ob_mysql_proxy.h"               // ObMySQLProxy
#include "lib/timezone/ob_timezone_info.h"                // ObTZInfoMap
#include "lib/lock/ob_spin_lock.h"                        // ObSpinLock
#include "common/ob_queue_thread.h"                       // ObCond
#include "ob_log_tenant_mgr.h"                            // ObLogTenantMgr
#include "ob_log_instance.h"                              //TCTX

namespace oceanbase
{
namespace omt
{
class ObTenantTimezoneGuard;
}
namespace liboblog
{
///////////////////////////////////// IObLogTimeZoneInfoGetter /////////////////////////////////
class IObLogTimeZoneInfoGetter
{
public:
  virtual ~IObLogTimeZoneInfoGetter() {}

public:
  virtual int start() = 0;
  virtual void stop() = 0;
  virtual void mark_stop_flag() = 0;

  // Init by ObLogTenant initialisation
  virtual int init_tz_info_wrap(const uint64_t tenant_id,
      int64_t &tz_info_map_version,
      common::ObTZInfoMap &tz_info_map,
      common::ObTimeZoneInfoWrap &tz_info_wrap) = 0;

  /// Refresh timezone info until successful (try refreshing several times)
  virtual int fetch_tenant_timezone_info_util_succ(const uint64_t tenant_id,
      common::ObTZInfoMap *tz_info_map) = 0;
};


///////////////////////////////////// ObLogTimeZoneInfoGetter /////////////////////////////////

class IObLogErrHandler;
class IObLogSysTableHelper;
class IObLogTenantMgr;

class ObLogTimeZoneInfoGetter : public IObLogTimeZoneInfoGetter
{
  static const int64_t SLEEP_TIME_ON_SCHEMA_FAIL = 500 * 1000;
  static const int64_t QUERY_TIMEZONE_INFO_VERSION_INTERVAL = 100 * 1000 * 1000;

public:
  ObLogTimeZoneInfoGetter();
  virtual ~ObLogTimeZoneInfoGetter();

public:
  int init(const char *timezone_str,
      common::ObMySQLProxy &mysql_proxy,
      IObLogSysTableHelper &systable_helper,
      IObLogTenantMgr &tenant_mgr,
      IObLogErrHandler &err_handler);
  void destroy();

public:
  virtual int start();
  virtual void stop();
  virtual void mark_stop_flag() { ATOMIC_STORE(&stop_flag_, true); }

  // Init by ObLogTenant initialisation
  virtual int init_tz_info_wrap(const uint64_t tenant_id,
      int64_t &tz_info_map_version,
      common::ObTZInfoMap &tz_info_map,
      common::ObTimeZoneInfoWrap &tz_info_wrap);

  virtual int fetch_tenant_timezone_info_util_succ(const uint64_t tenant_id,
      common::ObTZInfoMap *tz_info_map);

  // for init interface OTTZ_MGR.tenant_tz_map_getter_
  static int get_tenant_timezone_map(const uint64_t tenant_id,
      common::ObTZMapWrap &tz_map_wrap);

private:
  static void *tz_thread_func_(void *args);
  void tz_routine();

  // 1. local maintenance of timezone info version
  // 2. Periodically query all_zone table - time_zone_info_version:
  // update timezone info when changes occur
  // otherwise not updated (updating timezone info involves multiple table joins)
  int query_timezone_info_version_and_update_();

  bool need_fetch_timezone_info_by_tennat_() const;

  // 1. Check the version first, if the version has not changed, then do not refresh
  // 2. Refresh only if the version has changed
  //
  // @retval OB_SUCCESS         Success
  // @retval OB_ENTRY_NOT_EXIST tenant not exist
  // @retval other_error_code   Fail
  int refresh_tenant_timezone_info_based_on_version_(const uint64_t tenant_id);

  // 1. For versions below 226, there is one global copy of the timezone internal table and only one timezone_verison
  // 2. From version 226, the timezone internal table is split into tenants, each with a timezone_verison; if timezone_version is not available, the tenant has not imported a timezone table
  //
  // @retval OB_SUCCESS         Success
  // @retval OB_ENTRY_NOT_EXIST tenant not exist
  // @retval other_error_code   Fail
  int query_timezone_info_version_(const uint64_t tenant_id,
      int64_t &timezone_info_version);

  // refresh timezone info
  int refresh_timezone_info_();
  int refresh_tenant_timezone_info_(const uint64_t tenant_id, common::ObTZInfoMap *tz_info_map);
  int refresh_all_tenant_timezone_info_();

private:
  bool                  inited_;
  pthread_t             tz_tid_;
  common::ObCond        tz_cond_;
  volatile bool         stop_flag_ CACHE_ALIGNED;

  common::ObMySQLProxy  *mysql_proxy_;

  IObLogSysTableHelper  *systable_helper_;
  IObLogErrHandler      *err_handler_;

  common::ObSpinLock    lock_;
  IObLogTenantMgr       *tenant_mgr_;
  // save for init tz_info_wrap
  const char            *timezone_str_;
private:
  DISALLOW_COPY_AND_ASSIGN(ObLogTimeZoneInfoGetter);
};
} // namespace liboblog
} // namespace oceanbase
#endif
