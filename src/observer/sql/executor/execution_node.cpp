/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/execution_node.h"
#include "common/log/log.h"
#include "storage/common/table.h"

int index_of_field_in_schema_without_aggregate(const TupleField& field,
                                               const TupleSchema& schema) {
  size_t field_num = schema.fields().size();
  for (size_t i = 0; i < field_num; ++i) {
    if (schema.field(i) == field) {
      return i;
    }
  }
  return -1;
}

SelectExeNode::SelectExeNode() : trx_(nullptr), table_(nullptr) {}

SelectExeNode::~SelectExeNode() {
  for (DefaultConditionFilter*& filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC SelectExeNode::init(
    Trx* trx, Table* table, TupleSchema&& tuple_schema,
    std::vector<DefaultConditionFilter*>&& condition_filters) {
  trx_ = trx;
  table_ = table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

void record_reader(const char* data, void* context) {
  TupleRecordConverter* converter = (TupleRecordConverter*)context;
  converter->add_record(data);
}
RC SelectExeNode::execute(TupleSet& tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter**)condition_filters_.data(),
                        condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(trx_, &condition_filter, -1, (void*)&converter,
                             record_reader);
}

JoinExeNode::JoinExeNode() : trx_(nullptr) {}

JoinExeNode::~JoinExeNode() {
  for (ExecutionNode* sub_node : sub_nodes_) {
    delete sub_node;
  }
  sub_nodes_.clear();
}

RC JoinExeNode::init(Trx* trx, SelectHandler* handler) {
  RC rc = RC::SUCCESS;
  trx_ = trx;
  for (const TupleSchema& sub_select_schema : handler->select_schemas_) {
    tuple_schema_.append(sub_select_schema);
  }
  join_filter_ = std::move(handler->join_filter_);
  sub_nodes_.resize(handler->tables_.size(), nullptr);
  for (size_t i = 0; i < sub_nodes_.size(); ++i) {
    SelectExeNode* select_exe_node = new SelectExeNode();
    sub_nodes_[i] = select_exe_node;
    rc = select_exe_node->init(trx_, handler->tables_[i],
                               std::move(handler->select_schemas_[i]),
                               std::move(handler->select_filters_[i]));
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

RC JoinExeNode::execute(TupleSet& tuple_set) {
  RC rc = RC::SUCCESS;
  std::vector<TupleSet> tuple_sets_raw(sub_nodes_.size());
  for (size_t i = 0; i < sub_nodes_.size(); ++i) {
    rc = sub_nodes_[i]->execute(tuple_sets_raw[i]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);

  std::vector<int> tuple_indexes;
  add_tuple_dfs(tuple_set, tuple_sets_raw, tuple_indexes);

  return rc;
}

void JoinExeNode::add_tuple_dfs(TupleSet& tuple_set,
                                const std::vector<TupleSet>& tuple_sets_raw,
                                std::vector<int>& tuple_indexes) {
  if (tuple_indexes.size() == tuple_sets_raw.size()) {
    if (filter(tuple_sets_raw, tuple_indexes)) {
      Tuple tuple_new;
      for (size_t i = 0; i < tuple_sets_raw.size(); ++i) {
        const Tuple& tuple_raw = tuple_sets_raw[i].get(tuple_indexes[i]);
        for (size_t j = 0; j < tuple_raw.size(); ++j) {
          tuple_new.add(tuple_raw.get_pointer(j));
        }
      }
      tuple_set.add(std::move(tuple_new));
      return;
    }
  }

  int tuple_set_index = tuple_indexes.size();
  int tuple_num = tuple_sets_raw[tuple_set_index].size();
  for (size_t i = 0; i < tuple_num; ++i) {
    tuple_indexes.push_back(i);
    add_tuple_dfs(tuple_set, tuple_sets_raw, tuple_indexes);
    tuple_indexes.pop_back();
  }
}

bool JoinExeNode::filter(const std::vector<TupleSet>& tuple_sets_raw,
                         std::vector<int>& tuple_indexes) const {
  std::vector<const Tuple&> tuples_raw;
  for (size_t i = 0; i < tuple_sets_raw.size(); ++i) {
    tuples_raw.push_back(tuple_sets_raw[i].get(tuple_indexes[i]));
  }
  for (const JoinFilter& condition : join_filter_) {
    const TupleValue& left_value =
        tuples_raw[condition.left_tuple_set_index].get(
            condition.left_field_index);
    const TupleValue& right_value =
        tuples_raw[condition.right_tuple_set_index].get(
            condition.right_field_index);
    int cmp_result = left_value.compare(right_value);
    bool pass = false;
    switch (condition.comp) {
      case EQUAL_TO:
        pass = (cmp_result == 0);
        break;
      case LESS_EQUAL:
        pass = (cmp_result <= 0);
        break;
      case NOT_EQUAL:
        pass = (cmp_result != 0);
        break;
      case LESS_THAN:
        pass = (cmp_result < 0);
        break;
      case GREAT_EQUAL:
        pass = (cmp_result >= 0);
        break;
      case GREAT_THAN:
        pass = (cmp_result > 0);
        break;
      default:
        LOG_PANIC("condition.comp_op uninitialized");
        break;
    }
    if (!pass) {
      return false;
    }
  }
  return true;
}

ProjectExeNode::ProjectExeNode() : trx_(nullptr), sub_node_(nullptr) {}

ProjectExeNode::~ProjectExeNode() {
  delete sub_node_;
  sub_node_ = nullptr;
}

RC ProjectExeNode::init(Trx* trx, SelectHandler* handler) {
  RC rc = RC::SUCCESS;
  trx_ = trx;
  tuple_schema_ = std::move(handler->project_schema_);
  if (handler->tables_.size() == 1) {
    SelectExeNode* select_exe_node = new SelectExeNode();
    sub_node_ = select_exe_node;
    rc = select_exe_node->init(trx_, handler->tables_[0],
                               std::move(handler->select_schemas_[0]),
                               std::move(handler->select_filters_[0]));
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else {
    JoinExeNode* join_exe_node = new JoinExeNode();
    sub_node_ = join_exe_node;
    rc = join_exe_node->init(trx_, handler);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
}

RC ProjectExeNode::execute(TupleSet& tuple_set) {
  TupleSet tuple_set_raw;
  RC rc = sub_node_->execute(tuple_set_raw);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  size_t project_schema_num = tuple_schema_.fields().size();
  std::vector<int> attr_ptr(project_schema_num, -1);
  std::vector<int> agg_ptr(project_schema_num, -1);
  for (size_t i = 0; i < project_schema_num; ++i) {
    const TupleField& tuple_field = tuple_schema_.field(i);
    if (!tuple_field.is_aggregate()) {
      attr_ptr[i] = index_of_field_in_schema_without_aggregate(
          tuple_field, tuple_set_raw.schema());
      if (attr_ptr[i] == -1) {
        return RC::SCHEMA_FIELD_MISSING;
      }
    } else {
      return RC::GENERIC_ERROR;
    }
  }

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  for (size_t row = 0; row < tuple_set_raw.size(); ++row) {
    const Tuple& tuple_raw = tuple_set_raw.get(row);
    Tuple tuple_new;
    for (size_t col = 0; col < project_schema_num; ++col) {
      int value_index_in_tuple_raw = attr_ptr[col];
      if (value_index_in_tuple_raw != -1) {
        tuple_new.add(tuple_raw.get_pointer(value_index_in_tuple_raw));
      } else {
        return RC::GENERIC_ERROR;
      }
    }
    tuple_set.add(std::move(tuple_new));
  }
}
