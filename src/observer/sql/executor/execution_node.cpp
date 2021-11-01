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
#include "sql/executor/select_handler.h"
#include "storage/common/table.h"

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
  handler->select_schemas_.clear();
  handler->select_filters_.clear();

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
        for (int j = 0; j < tuple_raw.size(); ++j) {
          tuple_new.add(tuple_raw.get_pointer(j));
        }
      }
      tuple_set.add(std::move(tuple_new));
    }
    return;
  }

  int tuple_set_index = tuple_indexes.size();
  int tuple_num = tuple_sets_raw[tuple_set_index].size();
  for (int i = 0; i < tuple_num; ++i) {
    tuple_indexes.push_back(i);
    add_tuple_dfs(tuple_set, tuple_sets_raw, tuple_indexes);
    tuple_indexes.pop_back();
  }
}

bool JoinExeNode::filter(const std::vector<TupleSet>& tuple_sets_raw,
                         std::vector<int>& tuple_indexes) const {
  std::vector<const Tuple*> tuples_raw;
  for (size_t i = 0; i < tuple_sets_raw.size(); ++i) {
    tuples_raw.push_back(&tuple_sets_raw[i].get(tuple_indexes[i]));
  }
  for (const JoinFilter& condition : join_filter_) {
    const TupleValue& left_value =
        tuples_raw[condition.left_tuple_set_index]->get(
            condition.left_field_index);
    const TupleValue& right_value =
        tuples_raw[condition.right_tuple_set_index]->get(
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

SortExeNode::SortExeNode()
    : trx_(nullptr), selects_(nullptr), sub_node_(nullptr) {}

SortExeNode::~SortExeNode() {}

RC SortExeNode::init(Trx* trx, SelectHandler* handler) {
  RC rc = RC::SUCCESS;
  trx_ = trx;
  selects_ = handler->selects_;
  if (selects_->order_num == 0) {
    return RC::GENERIC_ERROR;
  }

  if (handler->tables_.size() == 1) {
    SelectExeNode* select_exe_node = new SelectExeNode();
    sub_node_ = select_exe_node;
    rc = select_exe_node->init(trx_, handler->tables_[0],
                               std::move(handler->select_schemas_[0]),
                               std::move(handler->select_filters_[0]));
    if (rc != RC::SUCCESS) {
      return rc;
    }
    handler->select_schemas_.clear();
    handler->select_filters_.clear();
  } else {
    JoinExeNode* join_exe_node = new JoinExeNode();
    sub_node_ = join_exe_node;
    rc = join_exe_node->init(trx_, handler);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

RC SortExeNode::execute(TupleSet& tuple_set) {
  tuple_set.clear();
  RC rc = sub_node_->execute(tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::vector<std::pair<size_t, OrderType>> orders;
  for (size_t i = 0; i < selects_->order_num; ++i) {
    const Order& order = selects_->orders[i];
    const char* table_name = nullptr;
    if (selects_->relation_num == 1) {
      table_name = selects_->relations[0];
    } else {
      table_name = order.attr.relation_name;
    }
    int index_of_field = tuple_set.schema().index_of_field(
        table_name, order.attr.attribute_name);
    if (index_of_field == -1) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    orders.push_back(std::make_pair(index_of_field, order.type));
  }

  tuple_set.sort_tuples([&orders](const Tuple& lhs, const Tuple& rhs) {
    for (const auto& col_index_and_order : orders) {
      size_t col_index = col_index_and_order.first;
      const OrderType& order_type = col_index_and_order.second;
      int cmp_result = lhs.get(col_index).compare(rhs.get(col_index));
      if (cmp_result < 0) {
        return order_type == ORDER_ASC ? true : false ;
      } else if (cmp_result > 0) {
        return order_type == ORDER_ASC ? false : true;
      } else {
        continue;
      }
    }
    return false;
  });

  return rc;
}

ProjectExeNode::ProjectExeNode()
    : trx_(nullptr), sub_node_(nullptr), single_table_name_(nullptr) {}

ProjectExeNode::~ProjectExeNode() {
  delete sub_node_;
  sub_node_ = nullptr;
}

RC ProjectExeNode::init(Trx* trx, SelectHandler* handler) {
  RC rc = RC::SUCCESS;
  trx_ = trx;
  tuple_schema_ = std::move(handler->project_schema_);
  if (handler->tables_.size() == 1) {
    single_table_name_ = handler->tables_[0]->name();
  }

  if (handler->selects_->order_num > 0) {
    SortExeNode* sort_exe_node = new SortExeNode();
    sub_node_ = sort_exe_node;
    rc = sort_exe_node->init(trx_, handler);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else if (handler->tables_.size() == 1) {
    SelectExeNode* select_exe_node = new SelectExeNode();
    sub_node_ = select_exe_node;
    rc = select_exe_node->init(trx_, handler->tables_[0],
                               std::move(handler->select_schemas_[0]),
                               std::move(handler->select_filters_[0]));
    if (rc != RC::SUCCESS) {
      return rc;
    }
    handler->select_schemas_.clear();
    handler->select_filters_.clear();
  } else {
    JoinExeNode* join_exe_node = new JoinExeNode();
    sub_node_ = join_exe_node;
    rc = join_exe_node->init(trx_, handler);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

std::shared_ptr<TupleValue> create_tuple_value(const Value& value) {
  std::shared_ptr<TupleValue> ret = nullptr;
  switch (value.type) {
    case INTS: {
      int data = *(int*)(value.data);
      ret = std::make_shared<IntValue>(data);
    } break;
    case FLOATS: {
      float data = *(float*)(value.data);
      ret = std::make_shared<FloatValue>(data);
    } break;
    case CHARS: {
      const char* data = (char*)(value.data);
      ret = std::make_shared<StringValue>(data, strlen(data));
    } break;
    case DATES: {
      int data = *(int*)(value.data);
      ret = std::make_shared<DateValue>(data);
    } break;
    default: {
      LOG_PANIC("Unsupported field type. type=%d", value.type);
    }
  }
  return ret;
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
  std::unordered_map<int, std::shared_ptr<TupleValue>> agg_values;
  for (size_t i = 0; i < project_schema_num; ++i) {
    const TupleField& tuple_field = tuple_schema_.field(i);
    if (!tuple_field.is_aggregate()) {
      attr_ptr[i] = tuple_set_raw.schema().index_of_field(
          tuple_field.table_name(), tuple_field.field_name());
      if (attr_ptr[i] == -1) {
        return RC::SCHEMA_FIELD_MISSING;
      }
    } else {
      const Aggregate* aggregate = tuple_schema_.aggregate(i);
      if (aggregate == nullptr) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      if (aggregate->is_attr) {
        const char* table_name = aggregate->attr.relation_name;
        if (table_name == nullptr) {
          if (single_table_name_ == nullptr) {
            return RC::SCHEMA_FIELD_MISSING;
          }
          table_name = single_table_name_;
        }
        agg_ptr[i] = tuple_set_raw.schema().index_of_field(
            table_name, aggregate->attr.attribute_name);
        if (agg_ptr[i] == -1) {
          return RC::SCHEMA_FIELD_MISSING;
        }
      } else {
        agg_values[i] = create_tuple_value(aggregate->value);
      }
    }
  }

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  for (int row = 0; row < tuple_set_raw.size(); ++row) {
    const Tuple& tuple_raw = tuple_set_raw.get(row);
    Tuple tuple_new;
    for (size_t col = 0; col < project_schema_num; ++col) {
      int value_index_in_tuple_raw = -1;
      if (attr_ptr[col] != -1) {
        value_index_in_tuple_raw = attr_ptr[col];
      } else if (agg_ptr[col] != -1) {
        value_index_in_tuple_raw = agg_ptr[col];
      }

      if (value_index_in_tuple_raw != -1) {
        tuple_new.add(tuple_raw.get_pointer(value_index_in_tuple_raw));
      } else {
        tuple_new.add(agg_values[col]);
      }
    }
    tuple_set.add(std::move(tuple_new));
  }

  return rc;
}

AggregateExeNode::AggregateExeNode() : trx_(nullptr), sub_node_(nullptr) {}

AggregateExeNode::~AggregateExeNode() {
  delete sub_node_;
  sub_node_ = nullptr;
}

RC AggregateExeNode::init(Trx* trx, SelectHandler* handler) {
  ProjectExeNode* project_exe_node = new ProjectExeNode();
  sub_node_ = project_exe_node;
  return project_exe_node->init(trx_, handler);
}

RC AggregateExeNode::execute(TupleSet& tuple_set) {
  tuple_set.clear();
  RC rc = sub_node_->execute(tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::map<int, AggregateResult> aggregate_results;
  const TupleSchema& schema = tuple_set.schema();
  for (size_t col = 0; col < schema.fields().size(); ++col) {
    if (schema.field(col).is_aggregate()) {
      const Aggregate* aggregate = schema.aggregate(col);
      if (aggregate == nullptr) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      AggregateResult result;
      rc = calculate_aggregate(tuple_set, col, *aggregate, result);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      aggregate_results[col] = result;
    }
  }

  if (!aggregate_results.empty()) {
    rc = merge_aggregate(aggregate_results, tuple_set);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC AggregateExeNode::calculate_aggregate(const TupleSet& tuple_set, int col,
                                         const Aggregate& aggregate,
                                         AggregateResult& result) const {
  if (aggregate.type == AGG_COUNT) {
    result.value = std::make_shared<IntValue>(tuple_set.size());
    result.tuple_index = -1;

  } else if (aggregate.type == AGG_MAX) {
    if (tuple_set.size() == 0) {
      return RC::GENERIC_ERROR;
    }
    std::shared_ptr<TupleValue> max_value = tuple_set.get(0).get_pointer(col);
    int max_row = 0;
    for (int i = 1; i < tuple_set.size(); ++i) {
      const Tuple& tuple = tuple_set.get(i);
      if (tuple.get_pointer(col)->compare(*max_value) > 0) {
        max_value = tuple.get_pointer(col);
        max_row = i;
      }
    }
    result.value = max_value;
    result.tuple_index = max_row;

  } else if (aggregate.type == AGG_MIN) {
    if (tuple_set.size() == 0) {
      return RC::GENERIC_ERROR;
    }
    std::shared_ptr<TupleValue> min_value = tuple_set.get(0).get_pointer(col);
    int min_row = 0;
    for (int i = 1; i < tuple_set.size(); ++i) {
      const Tuple& tuple = tuple_set.get(i);
      if (tuple.get_pointer(col)->compare(*min_value) < 0) {
        min_value = tuple.get_pointer(col);
        min_row = i;
      }
    }
    result.value = min_value;
    result.tuple_index = min_row;

  } else if (aggregate.type == AGG_AVG) {
    if (tuple_set.size() == 0) {
      return RC::GENERIC_ERROR;
    }
    float avg = 0;
    const std::type_info& value_type = typeid(tuple_set.get(0).get(col));
    if (typeid(IntValue) == value_type) {
      int sum = 0;
      for (int row = 0; row < tuple_set.size(); ++row) {
        sum += *(int*)tuple_set.get(row).get(col).get();
      }
      avg = (float)sum / tuple_set.size();
    } else if (typeid(FloatValue) == value_type) {
      float sum = 0;
      for (int row = 0; row < tuple_set.size(); ++row) {
        sum += *(float*)tuple_set.get(row).get(col).get();
      }
      avg = sum / tuple_set.size();
    } else {
      return GENERIC_ERROR;
    }
    result.value = std::make_shared<FloatValue>(avg);
    result.tuple_index = -1;

  } else {
    LOG_PANIC("should not print this message");
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}

RC AggregateExeNode::merge_aggregate(
    const std::map<int, AggregateResult>& aggregate_results,
    TupleSet& tuple_set) const {
  if (tuple_set.size() == 0 && tuple_set.schema().has_attribute()) {
    return RC::GENERIC_ERROR;
  }

  RC rc = RC::SUCCESS;
  Tuple tuple;

  int base_tuple_index = -1;
  for (const auto& result : aggregate_results) {
    base_tuple_index = result.second.tuple_index;
    if (base_tuple_index != -1) {
      break;
    }
  }
  if (base_tuple_index == -1) {
    if (tuple_set.size() > 0) {
      base_tuple_index = 0;
    }
  }
  if (base_tuple_index != -1) {
    const Tuple& base_tuple = tuple_set.get(base_tuple_index);
    for (int i = 0; i < base_tuple.size(); ++i) {
      tuple.add(base_tuple.get_pointer(i));
    }
  } else {
    for (size_t i = 0; i < aggregate_results.size(); ++i) {
      tuple.add(nullptr);
    }
  }

  for (const auto& result : aggregate_results) {
    int col = result.first;
    rc = tuple.set_pointer(col, result.second.value);
    if (rc != SUCCESS) {
      return rc;
    }
  }
  tuple_set.clear_tuples();
  tuple_set.add(std::move(tuple));
  return rc;
}
