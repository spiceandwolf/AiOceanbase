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

#define USING_LOG_PREFIX SQL_ENG

#include "sql/engine/expr/ob_expr_export_set.h"
#include "lib/oblog/ob_log.h"
#include "share/object/ob_obj_cast.h"
#include "sql/session/ob_sql_session_info.h"
using namespace oceanbase::common;
namespace oceanbase {
namespace sql {

ObExprExportSet::ObExprExportSet(ObIAllocator& alloc)
    : ObStringExprOperator(alloc, T_FUN_SYS_EXPORT_SET, N_EXPORT_SET, MORE_THAN_TWO)
{
  need_charset_convert_ = false;
}

ObExprExportSet::~ObExprExportSet()
{}

int ObExprExportSet::calc_result_typeN(ObExprResType& type, ObExprResType* types_array,
    int64_t param_num, common::ObExprTypeCtx& type_ctx) const
{
  int ret = OB_SUCCESS;
  if (3 != param_num && 4 != param_num && 5 != param_num) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("Export_Set() should have three or four or five arguments", K(ret), K(param_num));
  } else if (OB_ISNULL(types_array) || OB_ISNULL(type_ctx.get_session())) {
    ret = OB_ERR_UNEXPECTED;
    LOG_WARN("unexpected error. types_array or session null", K(ret), KP(types_array),
        KP(type_ctx.get_session()));
  } else {
    // deduce length
    // Maximum occurrences of on and of in result
    const uint64_t MAX_BIT_NUM = 64;
    // Maximum occurrences of sep in result
    const uint64_t MAX_SEP_NUM = 63;
    const int64_t on_len = types_array[1].get_length();
    const int64_t off_len = types_array[2].get_length();
    int64_t sep_len = 1;
    int64_t str_num = 2;
    const uint64_t max_len = std::max(on_len, off_len);
    // when bits exceed uint_max or int_min, ob is not compatible to mysql.
    types_array[0].set_calc_type(common::ObIntType);
    types_array[1].set_calc_type(common::ObVarcharType);
    types_array[2].set_calc_type(common::ObVarcharType);
    if (3 < param_num) {
      sep_len = types_array[3].get_length();
      str_num = 3;
      types_array[3].set_calc_type(common::ObVarcharType);
      if (4 < param_num) {
        types_array[4].set_calc_type(common::ObIntType);
      }
    }
    common::ObLength len = static_cast<common::ObLength>(MAX_BIT_NUM * max_len + 
        MAX_SEP_NUM * sep_len);
    type.set_length(len);
    type.set_varchar();
    // set collation_type for string type
    OZ(ObExprOperator::aggregate_charsets_for_string_result_with_comparison(
        type, &types_array[1], str_num, type_ctx.get_coll_type()));
    for (int64_t i = 1; OB_SUCC(ret) && i <= str_num; ++i) {
      types_array[i].set_calc_meta(type);
    }
  }
  return ret;
}

int ObExprExportSet::calc_resultN(ObObj& result, const ObObj* objs_array, int64_t param_num,
    ObExprCtx& expr_ctx) const
{
  int ret = OB_SUCCESS;
  if (OB_ISNULL(expr_ctx.calc_buf_)) {
    ret = OB_NOT_INIT;
    LOG_WARN("calc_buf of expr_ctx is NULL", K(ret));
  } else if (3 == param_num) {
    ObObj tmp_n_bits;
    ObObj tmp_sep;
    tmp_n_bits.set_int(64);
    tmp_sep.set_string(common::ObVarcharType, ObCharsetUtils::get_const_str(
        objs_array[1].get_collation_type(), ','));
    if (OB_FAIL(calc_export_set(result, objs_array[0], objs_array[1], objs_array[2], 
        tmp_sep, tmp_n_bits, expr_ctx))) {
      LOG_WARN("calc_export_set failed", K(ret));
    }
  } else if (4 == param_num) {
    ObObj tmp_n_bits;
    tmp_n_bits.set_int(64);
    if (OB_FAIL(calc_export_set(result, objs_array[0], objs_array[1], objs_array[2],
        objs_array[3], tmp_n_bits, expr_ctx))) {
      LOG_WARN("calc_export_set failed", K(ret));
    }
  } else if (5 == param_num) {
    if (OB_FAIL(calc_export_set(result, objs_array[0], objs_array[1], objs_array[2],
        objs_array[3], objs_array[4], expr_ctx))) {
      LOG_WARN("calc_export_set failed", K(ret));
    }
  }

  return ret;
}

int ObExprExportSet::calc_export_set(ObObj& result, const ObObj& bits, const ObObj& on,
    const ObObj& off, const ObObj& sep, const ObObj& n_bits, ObExprCtx& expr_ctx) const
{
  int ret = OB_SUCCESS;
  if (bits.is_null() || on.is_null() || off.is_null() || sep.is_null() || n_bits.is_null()) {
    result.set_null();
  } else if (OB_ISNULL(expr_ctx.calc_buf_)) {
    ret = OB_NOT_INIT;
    LOG_WARN("varchar buffer not init", K(ret));
  } else {
    int64_t tmp_local_bits;
    uint64_t local_bits;
    ObString local_on;
    ObString local_off;
    ObString local_sep;
    int64_t local_n_bits;
    ObString res;
    local_on = on.get_string();
    local_off = off.get_string();
    local_sep = sep.get_string();
    if (OB_FAIL(bits.get_int(tmp_local_bits))) {
      LOG_WARN("fail to get bit", K(ret), K(bits));
    } else if (FALSE_IT(local_bits = static_cast<uint64_t>(tmp_local_bits))) {
    } else if (OB_FAIL(n_bits.get_int(local_n_bits))) {
      LOG_WARN("fail to get int", K(ret), K(n_bits));
    } else if (OB_FAIL(calc_export_set_inner(res, local_bits, local_on, local_off,
        local_sep, local_n_bits, *expr_ctx.calc_buf_))) {
      LOG_WARN("do export set failed", K(ret));
    } else {
      result.set_string(result_type_.get_type(), res);
      result.set_collation(result_type_);
    }
  }
  return ret;
}

int ObExprExportSet::calc_export_set_inner(ObString& ret_str, const uint64_t bits,
    const ObString& on, const ObString& off, const ObString& sep, const int64_t n_bits,
    ObExprStringBuf& string_buf)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(n_bits == 0)) {
    // Return empty string
    ret_str.reset();
  } else if (OB_UNLIKELY(on.length() <= 0 && off.length() <= 0 && sep.length() <= 0)) {
    ret_str.reset();
  } else {
    const uint64_t MAX_BIT_NUM = 64UL;
    uint64_t local_n_bits = static_cast<uint64_t>(n_bits);
    local_n_bits = std::min(MAX_BIT_NUM, local_n_bits);
    const int64_t length_on = on.length();
    const int64_t length_off = off.length();
    const int64_t length_sep = sep.length();
    int64_t tot_length = 0;  // total length for the result.
    uint64_t i;
    const uint64_t mask = 1;
    //compute tot_length and save ans
    tot_length += (local_n_bits - 1) * length_sep;
    for (i = 0; i < local_n_bits; ++i) {
      if (bits & (mask << i)){
        tot_length += length_on;
      } else {
        tot_length += length_off;
      }
    }
    // Avoid realloc
    if (OB_UNLIKELY(tot_length <= 0)) {
      // tot_length equals to 0 indicates that length_to is zero and "to" is empty string
      ret_str.reset();
    } else {
      char* buf = static_cast<char*>(string_buf.alloc(tot_length));
      if (OB_ISNULL(buf)) {
        ret = OB_ALLOCATE_MEMORY_FAILED;
        LOG_ERROR("alloc memory failed.", K(ret), K(tot_length));
      } else {
        // Core function
        char* tmp_buf = buf;
        if (local_n_bits > 0) {
          if (bits & mask) {
            MEMCPY(tmp_buf, on.ptr(), length_on);
            tmp_buf += length_on;
          } else {
            MEMCPY(tmp_buf, off.ptr(), length_off);
            tmp_buf += length_off;
          }
        }
        for (i = 1; i < local_n_bits; ++i) {
          MEMCPY(tmp_buf, sep.ptr(), length_sep);
          tmp_buf += length_sep;
          if (bits & (mask << i)) {
            MEMCPY(tmp_buf, on.ptr(), length_on);
            tmp_buf += length_on;
          } else {
            MEMCPY(tmp_buf, off.ptr(), length_off);
            tmp_buf += length_off;
          }
        }
        ret_str.assign_ptr(buf, static_cast<int32_t>(tot_length));
      }
    }
  }
  return ret;
}

int ObExprExportSet::cg_expr(ObExprCGCtx&, const ObRawExpr&, ObExpr& rt_expr) const
{
  int ret = OB_SUCCESS;
  CK(3 == rt_expr.arg_cnt_ || 4 == rt_expr.arg_cnt_ || 5 == rt_expr.arg_cnt_);
  rt_expr.eval_func_ = &eval_export_set;
  return ret;
}

int ObExprExportSet::eval_export_set(const ObExpr& expr, ObEvalCtx& ctx, ObDatum& expr_datum)
{
  int ret = OB_SUCCESS;
  ObDatum* bits = NULL;
  ObDatum* on = NULL;
  ObDatum* off = NULL;
  ObDatum* sep = NULL; 
  ObDatum* n_bits = NULL;
  int64_t max_size = 0;
  if (OB_FAIL(expr.eval_param_value(ctx, bits, on, off, sep, n_bits))) {
    LOG_WARN("evaluate parameters failed", K(ret));
  } else if (bits->is_null() || on->is_null() || off->is_null()) {
    expr_datum.set_null();
  } else if (OB_NOT_NULL(sep) && sep->is_null()) {
    expr_datum.set_null();
  } else if (OB_NOT_NULL(n_bits) && n_bits->is_null()) {
    expr_datum.set_null();
  } else {
    ObExprStrResAlloc expr_res_alloc(expr, ctx);
    ObString output;
    //default parm
    ObString sep_parm;
    int64_t n_bits_parm;
    if (OB_ISNULL(sep)) {
      sep_parm = ObCharsetUtils::get_const_str(expr.datum_meta_.cs_type_, ',');
    } else {
      sep_parm = sep->get_string();
    }
    if (OB_ISNULL(n_bits)) {
      n_bits_parm = 64;
    } else {
      n_bits_parm = n_bits->get_uint64();
    }
    if (OB_FAIL(calc_export_set_inner(output, bits->get_uint64(), on->get_string(),
        off->get_string(), sep_parm, n_bits_parm, expr_res_alloc))) {
      LOG_WARN("do export set failed", K(ret));
    } else {
      expr_datum.set_string(output);
    }
  }
  return ret;
}

}  // namespace sql
}  // namespace oceanbase
