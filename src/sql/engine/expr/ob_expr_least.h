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

#ifndef _OB_SQL_EXPR_LEAST_H_
#define _OB_SQL_EXPR_LEAST_H_

#include "sql/engine/expr/ob_expr_operator.h"

namespace oceanbase {
namespace sql {
class ObExprBaseLeastGreatest : public ObMinMaxExprOperator {
public:
  explicit ObExprBaseLeastGreatest(
      common::ObIAllocator& alloc, ObExprOperatorType type, const char* name, int32_t param_num);
  virtual ~ObExprBaseLeastGreatest();
  int calc_result_typeN_oracle(ObExprResType &type,
                        ObExprResType *types_stack,
                        int64_t param_num,
                        common::ObExprTypeCtx &type_ctx) const;
  int calc_result_typeN_mysql(ObExprResType &type,
                        ObExprResType *types_stack,
                        int64_t param_num,
                        common::ObExprTypeCtx &type_ctx) const;
  void set_param_type(const ObExprResType &type,
                      ObExprResType *types,
                      int64_t param_num) const;
  static int calc(const ObExpr &expr, ObEvalCtx &ctx, ObDatum &expr_datum, bool least);
  // left < right: return true, else return false.
  static inline bool cmp_integer(const ObDatum &l_datum, const bool l_is_int,
                                 const ObDatum &r_datum, const bool r_is_int)
  {
    bool ret_bool = true;
    if (l_is_int && r_is_int) {
      ret_bool = l_datum.get_int() < r_datum.get_int();
    } else if (!l_is_int && !r_is_int) {
      ret_bool = l_datum.get_uint() < r_datum.get_uint();
    } else if (l_is_int && !r_is_int) {
      ret_bool = l_datum.get_int() < r_datum.get_uint();
    } else {
      ret_bool = l_datum.get_uint() < r_datum.get_int();
    }
    return ret_bool;
  }
private:
  // disallow copy
  DISALLOW_COPY_AND_ASSIGN(ObExprBaseLeastGreatest);
};

class ObExprBaseLeast : public ObExprBaseLeastGreatest {
public:
  explicit ObExprBaseLeast(common::ObIAllocator& alloc, int32_t param_num, ObExprOperatorType type = T_FUN_SYS_LEAST,
      const char* name = N_LEAST);
  virtual ~ObExprBaseLeast();
  virtual int calc_result_typeN(
      ObExprResType& type, ObExprResType* types_stack, int64_t param_num, common::ObExprTypeCtx& type_ctx) const override;
  virtual int calc_resultN(
      common::ObObj& result, const common::ObObj* objs_stack, int64_t param_num, common::ObExprCtx& expr_ctx) const override;
  virtual int cg_expr(ObExprCGCtx& op_cg_ctx, const ObRawExpr& raw_expr, ObExpr& rt_expr) const override;
  static int calc_least(const ObExpr& expr, ObEvalCtx& ctx, ObDatum& expr_datum);

private:
  // disallow copy
  DISALLOW_COPY_AND_ASSIGN(ObExprBaseLeast);
};

class ObExprLeastMySQL : public ObExprBaseLeast {
public:
  explicit ObExprLeastMySQL(common::ObIAllocator& alloc);
  virtual ~ObExprLeastMySQL();
  virtual int calc_result_typeN(
      ObExprResType& type, ObExprResType* types_stack, int64_t param_num, common::ObExprTypeCtx& type_ctx) const;

private:
  DISALLOW_COPY_AND_ASSIGN(ObExprLeastMySQL);
};

class ObExprLeastMySQLInner : public ObExprBaseLeast {
public:
  explicit ObExprLeastMySQLInner(common::ObIAllocator& alloc);
  virtual ~ObExprLeastMySQLInner();
  virtual int calc_result_typeN(
      ObExprResType& type, ObExprResType* types_stack, int64_t param_num, common::ObExprTypeCtx& type_ctx) const;

private:
  DISALLOW_COPY_AND_ASSIGN(ObExprLeastMySQLInner);
};

class ObExprOracleLeast : public ObExprBaseLeast {
public:
  explicit ObExprOracleLeast(common::ObIAllocator& alloc);
  virtual ~ObExprOracleLeast();
  virtual int calc_result_typeN(
      ObExprResType& type, ObExprResType* types_stack, int64_t param_num, common::ObExprTypeCtx& type_ctx) const;

private:
  DISALLOW_COPY_AND_ASSIGN(ObExprOracleLeast);
};

}  // namespace sql
}  // namespace oceanbase
#endif /* _OB_SQL_EXPR_LEAST_H_ */
