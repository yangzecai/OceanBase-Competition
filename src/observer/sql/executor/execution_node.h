/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/13.
//

#ifndef __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
#define __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_

#include <vector>

#include "sql/executor/tuple.h"
#include "storage/common/condition_filter.h"

class Table;
class Trx;
class SelectHandler;

class ExecutionNode {
 public:
  ExecutionNode() = default;
  virtual ~ExecutionNode() = default;

  virtual RC execute(TupleSet& tuple_set) = 0;
};

class SelectExeNode : public ExecutionNode {
 public:
  SelectExeNode();
  virtual ~SelectExeNode();

  RC init(Trx* trx, Table* table, TupleSchema&& tuple_schema,
          std::vector<DefaultConditionFilter*>&& condition_filters);

  RC execute(TupleSet& tuple_set) override;

 private:
  Trx* trx_;
  Table* table_;
  TupleSchema tuple_schema_;
  std::vector<DefaultConditionFilter*> condition_filters_;
};

class JoinExeNode : public ExecutionNode {
 public:
  struct JoinFilter {
    int left_tuple_set_index;
    int left_field_index;
    int right_tuple_set_index;
    int right_field_index;
    CompOp comp;
  };

  JoinExeNode();
  virtual ~JoinExeNode();

  RC init(Trx* trx, SelectHandler* handler);
  RC execute(TupleSet& tuple_set) override;

 private:
  void add_tuple_dfs(TupleSet& tuple_set,
                     const std::vector<TupleSet>& tuple_sets_raw,
                     std::vector<int>& tuple_indexes);
  bool filter(const std::vector<TupleSet>& tuple_sets_raw,
              std::vector<int>& tuple_indexes) const;

  Trx* trx_;
  TupleSchema tuple_schema_;
  std::vector<JoinFilter> join_filter_;
  std::vector<ExecutionNode*> sub_nodes_;
};

class SortExeNode : public ExecutionNode {
 public:
  SortExeNode();
  virtual ~SortExeNode();

  RC init(Trx* trx, ExecutionNode*&& sub_nodes);
  RC execute(TupleSet& tuple_set) override;
};

class ProjectExeNode : public ExecutionNode {
 public:
  ProjectExeNode();
  virtual ~ProjectExeNode();

  RC init(Trx* trx, SelectHandler* handler);
  RC execute(TupleSet& tuple_set) override;

 private:
  Trx* trx_ = nullptr;
  TupleSchema tuple_schema_;
  TupleSet tuple_set_;
  ExecutionNode* sub_node_;
  const char* single_table_name_;
};

#endif  //__OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
