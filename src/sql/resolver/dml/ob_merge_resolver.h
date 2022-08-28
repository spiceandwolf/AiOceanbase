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

#ifndef OCEANBASE_SQL_RESOLVER_DML_OB_MERGE_RESOLVER_H_
#define OCEANBASE_SQL_RESOLVER_DML_OB_MERGE_RESOLVER_H_
#include "sql/resolver/dml/ob_insert_resolver.h"
#include "sql/resolver/dml/ob_merge_stmt.h"
namespace oceanbase {
namespace share {
namespace schema {
class ObColumnSchemaV2;
}
}  // namespace share
namespace sql {
class ObMergeResolver : public ObInsertResolver {
public:
  enum MergeNodeField {
    TARGET_NODE = 0,
    SOURCE_NODE,
    MATCH_COND_NODE,
    UPDATE_CLAUSE_NODE,
    INSERT_CLAUSE_NODE,
    HINT_NODE,
    MERGE_FILED_COUNT
  };
  enum MergeResolveClause { NONE_CLAUSE, MATCH_CLAUSE, INSERT_COLUMN_CLAUSE, INSERT_VALUE_CLAUSE, INSERT_WHEN_CLAUSE };

public:
  explicit ObMergeResolver(ObResolverParams& params);
  virtual ~ObMergeResolver();
  virtual int resolve(const ParseNode& parse_tree);

protected:
  virtual int add_assignment(
      ObTablesAssignments& assigns, const TableItem* table_item, const ColumnItem* col_item, ObAssignment& assign);

private:
  int resolve_target_relation(const ParseNode* target_node);
  int resolve_source_relation(const ParseNode* source_node);
  int resolve_match_condition(const ParseNode* condition_node);
  int resolve_insert_clause(const ParseNode* insert_node);
  int expand_insert_value_exprs();
  int expand_value_expr(
      ObRawExpr*& expr, const ObIArray<ObColumnRefRawExpr*>& columns, const ObIArray<ObRawExpr*>& values);
  int resolve_update_clause(const ParseNode* update_node);
  int resolve_where_conditon(const ParseNode* condition_node, common::ObIArray<ObRawExpr*>& condition_exprs);
  virtual int find_value_desc(uint64_t column_id, ObRawExpr*& output_ref, uint64_t index = 0);
  virtual int replace_column_ref(common::ObArray<ObRawExpr*>* value_row, ObRawExpr*& expr);
  int add_rowkey_columns();
  int build_rowkey_expr(
      uint64_t table_id, const share::schema::ObColumnSchemaV2& column_schema, ObColumnRefRawExpr*& column_expr);
  int generate_rowkeys_exprs();
  int check_insert_clause();
  int check_column_validity(ObColumnRefRawExpr* col);
  int add_delete_refered_column_ids();
  int add_delete_related_column_to_stmt(uint64_t table_id, common::ObIArray<ObColumnRefRawExpr*>& column_items);
  int add_delete_refered_column_exprs(uint64_t table_id);
  int resolve_table(const ParseNode& parse_tree, TableItem*& table_item);
  ObMergeStmt* get_merge_stmt()
  {
    return static_cast<ObMergeStmt*>(stmt_);
  }
  int resolve_generate_table(const ParseNode& table_node, const ParseNode* alias_node, TableItem*& table_item);
  virtual int resolve_column_ref_expr(const ObQualifiedName& q_name, ObRawExpr*& real_ref_expr) override;
  virtual int resolve_column_ref_for_subquery(const ObQualifiedName& q_name, ObRawExpr*& real_ref_expr) override;
  int resolve_multi_table_merge_info();
  int check_stmt_validity();
  int get_equal_columns(ObIArray<ObString>& equal_cols);

private:
  // merge into x using y on (...) update set x.c1 = upd_val insert x.c1 values(ins_val)
  // update clause and insert clause, each has its own check constraint expression,
  // The difference is that the column ref expr in the check constraint expression is a different new value
  // The col ref of the check constraint corresponding to the update clause points to upd_val
  // The col ref of the check constraint corresponding to the insert clause points to ins_val
  int replace_col_ref_for_check_cst();

  ObSEArray<ObRawExpr*, 4, common::ModulePageAllocator, true> join_column_exprs_;
  MergeResolveClause resolve_clause_;
};
}  // namespace sql
}  // namespace oceanbase
#endif /* OCEANBASE_SQL_RESOLVER_DML_OB_MERGE_RESOLVER_H_ */
