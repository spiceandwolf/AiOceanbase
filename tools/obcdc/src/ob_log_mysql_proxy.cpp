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

#define USING_LOG_PREFIX OBLOG

#include "ob_log_mysql_proxy.h"                           // ObLogMysqlProxy

#include "lib/mysqlclient/ob_mysql_server_provider.h"     // ObMySQLServerProvider
#include "ob_log_utils.h"                                 // is_mysql_client_errno
#include "share/ob_thread_mgr.h"

using namespace oceanbase::common;
using namespace oceanbase::common::sqlclient;

namespace oceanbase
{
namespace liboblog
{

ObLogMysqlProxy::ObLogMysqlProxy() : inited_(false),
                                     connection_pool_(),
                                     mysql_proxy_()
{
  cluster_user_[0] = '\0';
  cluster_password_[0] = '\0';
  cluster_db_name_[0] = '\0';
}

ObLogMysqlProxy::~ObLogMysqlProxy()
{
  destroy();
}

int ObLogMysqlProxy::init(ServerProviderType *server_provider,
    const char *cluster_user,
    const char *cluster_password,
    const char *cluster_db_name,
    const int64_t sql_conn_timeout_us,
    const int64_t sql_query_timeout_us,
    const bool enable_ssl_client_authentication)
{
  int ret = OB_SUCCESS;
  int64_t user_pos = 0;
  int64_t password_pos = 0;
  int64_t db_pos = 0;

  if (OB_UNLIKELY(inited_)) {
    LOG_ERROR("ObLogMysqlProxy has been initialized");
    ret = OB_INIT_TWICE;
  } else if (OB_ISNULL(server_provider)
      || OB_ISNULL(cluster_user)
      || OB_ISNULL(cluster_password)
      || OB_ISNULL(cluster_db_name)
      || OB_UNLIKELY(sql_conn_timeout_us <= 0)
      || OB_UNLIKELY(sql_query_timeout_us <= 0)) {
    LOG_ERROR("invalid argument", K(server_provider),
        K(cluster_user), K(cluster_password), K(cluster_db_name), K(sql_conn_timeout_us),
        K(sql_query_timeout_us));
    ret = OB_INVALID_ARGUMENT;
  } else if (OB_FAIL(TG_START(lib::TGDefIDs::LogMysqlPool))) {
    LOG_ERROR("init connection pool timer fail", KR(ret));
  } else if (OB_FAIL(databuff_printf(cluster_user_, sizeof(cluster_user_), user_pos, "%s", cluster_user))) {
    LOG_ERROR("print cluster_user fail", KR(ret), K(user_pos), K(cluster_user));
  } else if (OB_FAIL(databuff_printf(cluster_password_, sizeof(cluster_password_), password_pos, "%s", cluster_password))) {
    LOG_ERROR("print cluster_password fail", KR(ret), K(password_pos), K(cluster_password));
  } else if (OB_FAIL(databuff_printf(cluster_db_name_, sizeof(cluster_db_name_), db_pos, "%s", cluster_db_name))) {
    LOG_ERROR("print cluster_db_name fail", KR(ret), K(db_pos), K(cluster_db_name));
  } else {
    ObConnPoolConfigParam conn_pool_config;
    conn_pool_config.reset();

    // Configure refresh interval
    // 1. The default is the shortest refresh time when no connection is available
    // 2. When a connection is available, the actual refresh time is (connection_refresh_interval * 50)
    conn_pool_config.connection_refresh_interval_ = 1L * 1000L * 1000L; // us
    conn_pool_config.sqlclient_wait_timeout_ = sql_conn_timeout_us / 1000000L; // s
    conn_pool_config.connection_pool_warn_time_ = 10L * 1000L * 1000L;  // us
    conn_pool_config.long_query_timeout_ = sql_query_timeout_us;     // us
    conn_pool_config.sqlclient_per_observer_conn_limit_ = 20;   // us

    _LOG_INFO("mysql connection pool: sql_conn_timeout_us=%ld us, "
        "sqlclient_wait_timeout=%ld sec, sql_query_timeout_us=%ld us, "
        "long_query_timeout=%ld us, connection_refresh_interval=%ld us, "
        "connection_pool_warn_time=%ld us, sqlclient_per_observer_conn_limit=%ld",
        sql_conn_timeout_us, conn_pool_config.sqlclient_wait_timeout_,
        sql_query_timeout_us, conn_pool_config.long_query_timeout_,
        conn_pool_config.connection_refresh_interval_, conn_pool_config.connection_pool_warn_time_,
        conn_pool_config.sqlclient_per_observer_conn_limit_);

    connection_pool_.update_config(conn_pool_config);
    connection_pool_.set_server_provider(server_provider);
    if (! enable_ssl_client_authentication) {
      connection_pool_.disable_ssl();
    }
    if (OB_FAIL(connection_pool_.set_db_param(cluster_user_,
        cluster_password_,
        cluster_db_name_))) {
      LOG_ERROR("set connection pool db param fail", KR(ret), K(cluster_user_),
          K(cluster_password_), K(cluster_db_name_));
    } else if (OB_FAIL(connection_pool_.start(lib::TGDefIDs::LogMysqlPool))) {
      // launch ConnectinPool
      LOG_ERROR("start connection pool fail", KR(ret));
    } else if (OB_FAIL(mysql_proxy_.init(&connection_pool_))) { // init MySQL Proxy
      LOG_ERROR("init mysql proxy fail", KR(ret));
    } else {
      LOG_INFO("ObLogMysqlProxy init succ", "use_ssl", connection_pool_.is_use_ssl());
      inited_ = true;
    }
  }

  return ret;
}

void ObLogMysqlProxy::destroy()
{
  inited_ = false;

  connection_pool_.stop();
  TG_DESTROY(lib::TGDefIDs::LogMysqlPool);

  cluster_user_[0] = '\0';
  cluster_password_[0] = '\0';
  cluster_db_name_[0] = '\0';
}

} // namespace liboblog
} // namespace oceanbase
