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

#ifndef OCEANBASE_SQL_RESOLVER_CMD_OB_VARIALBLE_SET_RESOLVER_
#define OCEANBASE_SQL_RESOLVER_CMD_OB_VARIALBLE_SET_RESOLVER_

#include "sql/resolver/ob_stmt_resolver.h"
#include "sql/resolver/cmd/ob_variable_set_resolver.h"
#include "sql/resolver/cmd/ob_variable_set_stmt.h"

namespace oceanbase {
namespace sql {
class ObVariableSetResolver : public ObStmtResolver {
public:
  explicit ObVariableSetResolver(ObResolverParams &params);
  virtual ~ObVariableSetResolver();

  virtual int resolve(const ParseNode &parse_tree);
  int resolve_set_variable(
      const ParseNode &set_node, ObVariableSetStmt::VariableSetNode &var_node, ObVariableSetStmt *variable_set_stmt);
  int resolve_set_names(const ParseNode &set_node, ObVariableSetStmt::NamesSetNode &names_node);

private:
  DISALLOW_COPY_AND_ASSIGN(ObVariableSetResolver);
};

class ObAlterSessionSetResolver : public ObStmtResolver {
public:
  explicit ObAlterSessionSetResolver(ObResolverParams &params);
  virtual ~ObAlterSessionSetResolver();

  virtual int resolve(const ParseNode &parse_tree);

private:
  DISALLOW_COPY_AND_ASSIGN(ObAlterSessionSetResolver);
};

}  // namespace sql
}  // namespace oceanbase
#endif /* OCEANBASE_SQL_RESOLVER_CMD_OB_VARIALBLE_SET_RESOLVER_ */
