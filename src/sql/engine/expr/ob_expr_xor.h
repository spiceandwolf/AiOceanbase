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

#ifndef _OB_EXPR_XOR_H_
#define _OB_EXPR_XOR_H_

#include "sql/engine/expr/ob_expr_operator.h"

namespace oceanbase {
namespace sql {
class ObExprXor : public ObLogicalExprOperator {
public:
  ObExprXor();
  explicit ObExprXor(common::ObIAllocator& alloc);
  virtual ~ObExprXor(){};

  virtual int calc_result_typeN(
      ObExprResType& type, ObExprResType* types_stack, int64_t param_num, common::ObExprTypeCtx& type_ctx) const;

  virtual int calc_result2(
      common::ObObj& result, const common::ObObj& obj1, const common::ObObj& obj2, common::ObExprCtx& expr_ctx) const;
  virtual int calc_resultN(
      common::ObObj& result, const common::ObObj* objs, int64_t param_num, common::ObExprCtx& expr_ctx) const;
  static int calc(
      common::ObObj& res, const common::ObObj& left, const common::ObObj& right, common::ObExprCtx& expr_ctx);

  virtual int cg_expr(ObExprCGCtx& op_cg_ctx, const ObRawExpr& raw_expr, ObExpr& rt_expr) const override;
  static int eval_xor(const ObExpr& expr, ObEvalCtx& ctx, ObDatum& expr_datum);

private:
  static int calc_res_with_one_param_null(
      common::ObObj &res, const common::ObObj &left, const common::ObObj &right, common::ObExprCtx &expr_ctx);

private:
  DISALLOW_COPY_AND_ASSIGN(ObExprXor);
};
}  // namespace sql
}  // namespace oceanbase
#endif /* _OB_EXPR_OR_H_ */
