#ifndef __OBSERVER_SQL_EXECUTOR_SELECT_HANDLER_H_
#define __OBSERVER_SQL_EXECUTOR_SELECT_HANDLER_H_

#include <unordered_map>

#include "event/session_event.h"
#include "rc.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "sql/parser/parse_defs.h"

class SelectHandler {
 public:
  SelectHandler();
  ~SelectHandler();
  RC init(const char* db, Selects* selects, Trx* trx,
          const std::vector<Table*>* parent_tables = nullptr);
  RC handle(TupleSet& tuple_set);

  bool is_multi_table() { return tables_.size() > 1; }

 private:
  friend class AggregateExeNode;
  friend class ProjectExeNode;
  friend class SortExeNode;
  friend class JoinExeNode;
  friend class SelectExeNode;

  RC init_tables();
  RC init_schemas();
  RC init_conditions();
  RC init_exe_nodes();

  bool is_aggregate(const RelAttr* attribute);

  int index_of_table(std::string table_name);

  RC add_attribute_to_select_schemas(const RelAttr* attribute);
  RC add_aggregate_to_select_schemas(const Aggregate* aggregate);
  RC add_attribute_to_project_schema(const RelAttr* attribute);
  RC add_aggregate_to_project_schema(const Aggregate* aggregate);
  RC add_attribute_to_schema(const RelAttr* attribute, TupleSchema* schema);
  RC add_aggregate_to_schema(const Aggregate* aggregate, TupleSchema* schema);

  RC add_condition_to_select_filters(const Condition* condition);
  RC add_condition_to_join_filter(const Condition* condition);
  bool is_join_condition(const Condition* condition);

  RC solve_sub_query_if_exist(Condition* condition);

  bool can_merge_parent_tables(const Selects* selects) const;
  RC merge_parent_tables(const std::vector<Table*>& parent_tables);

  const char* db_;
  Trx* trx_;
  Selects* selects_;
  std::vector<Table*> tables_;
  std::vector<TupleSchema> select_schemas_;
  TupleSchema project_schema_;
  std::vector<std::vector<DefaultConditionFilter*>> select_filters_;
  std::vector<JoinExeNode::JoinFilter> join_filter_;
  std::unordered_map<std::string, int> table_indexes_;
  std::shared_ptr<ExecutionNode> root_exe_node_;
};

#endif