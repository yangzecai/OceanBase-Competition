#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_SETS_JOINER_H__
#define __OBSERVER_SQL_EXECUTOR_TUPLE_SETS_JOINER_H__

#include <functional>
#include <map>

#include "rc.h"
#include "sql/executor/tuple.h"
#include "sql/parser/parse_defs.h"

struct JoinCondition {
  int left_tuple_set_index;
  int left_field_index;
  int right_tuple_set_index;
  int right_field_index;
  CompOp comp_op;
};

class TupleSetsJoiner {
 public:
  TupleSetsJoiner();
  RC init(const char* db, const Selects* selects,
          const std::vector<TupleSet>& tuple_sets);
  void execute();
  void print(std::ostream& os) { joined_tuple_set_.print(os); }

 private:
  RC init_conditions();
  RC make_schema();

  const Table* get_table(const char* table_name) const;
  const Table* get_table(const std::string& table_name) const;

  void make_tuples_dfs(std::vector<int>& tuple_indexes);
  std::vector<const Tuple*> load_tuples(
      const std::vector<int>& tuple_indexes) const;
  void add_or_filter_tuple(const std::vector<int>& tuple_indexes);
  bool filter_tuple(const std::vector<int>& tuple_indexes) const;
  void scan_tuple_values(
      const std::vector<int>& tuple_indexes,
      std::function<void(std::shared_ptr<TupleValue>)>) const;

  const char* db_;
  const std::vector<TupleSet>* tuple_sets_;
  const Selects* selects_;
  TupleSet joined_tuple_set_;
  std::vector<JoinCondition> join_conditions_;
  std::map<std::pair<std::string, std::string>, size_t> field_indexes_;
  std::map<std::string, const Table*> tables_;
  std::vector<int> tuple_sets_scan_order_;
};

#endif