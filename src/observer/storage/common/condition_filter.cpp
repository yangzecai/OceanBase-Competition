/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/7.
//

#include <math.h>
#include <stddef.h>

#include "common/log/log.h"
#include "condition_filter.h"
#include "record_manager.h"
#include "sql/executor/select_handler.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"

int condition_float_compare(float f1, float f2) {
  float result = f1 - f2;
  if (result < 1e-6 && result > -1e-6) {
    return 0;
  }
  return result > 0 ? 1 : -1;
}

using namespace common;

ConditionFilter::~ConditionFilter() {}

DefaultConditionFilter::DefaultConditionFilter() {
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter() {}

RC DefaultConditionFilter::init(const ConDesc& left, const ConDesc& right,
                                AttrType left_type, AttrType right_type,
                                CompOp comp_op) {
  if (left_type < CHARS || left_type > SUB_QUERYS) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d",
              left_type);
    return RC::INVALID_ARGUMENT;
  }

  if (right_type < CHARS || right_type > SUB_QUERYS) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d",
              right_type);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d",
              comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  left_type_ = left_type;
  right_type_ = right_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

bool DefaultConditionFilter::is_match_type(AttrType left_type,
                                           AttrType right_type) const {
  if (left_type == INTS && right_type == FLOATS) {
    return true;
  } else if (left_type == FLOATS && right_type == INTS) {
    return true;
  } else if (left_type != SUB_QUERYS && right_type == SUB_QUERYS) {
    return true;
  } else if (left_type == right_type) {
    return true;
  } else {
    return false;
  }
}

RC DefaultConditionFilter::init(const Table& table,
                                const Condition& condition) {
  const TableMeta& table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta* field_left =
        table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(),
               condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();
    left.attr_nullable = field_left->nullable();

    left.value = nullptr;

    type_left = field_left->type();
  } else {
    left.is_attr = false;
    left.value = condition.left_value.data;  // ??????type ??????????????????
    if (condition.left_value.type == NULLS) {
      left.value_is_null = true;
    } else {
      left.value_is_null = false;
    }
    type_left = condition.left_value.type;

    left.attr_length = 0;
    left.attr_offset = 0;
    left.attr_nullable = false;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta* field_right =
        table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(),
               condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    right.attr_nullable = field_right->nullable();

    type_right = field_right->type();

    right.value = nullptr;
  } else {
    right.is_attr = false;
    right.value = condition.right_value.data;
    if (condition.right_value.type == NULLS) {
      right.value_is_null = true;
    } else {
      right.value_is_null = false;
    }
    type_right = condition.right_value.type;

    right.attr_length = 0;
    right.attr_offset = 0;
    right.attr_nullable = false;
  }

  if (type_left == NULLS || type_right == NULLS) {
    type_left = NULLS;
    type_right = NULLS;
  }

  if (!is_match_type(type_left, type_right)) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, type_left, type_right, condition.comp);
}

bool DefaultConditionFilter::filter(const Record& rec) const {
  if (left_type_ == NULLS) {
    if (comp_op_ != IS_NULL && comp_op_ != IS_NOT_NULL) {
      return false;
    }
    if (left_.is_attr && comp_op_ == IS_NOT_NULL &&
        (!left_.attr_nullable ||
         '\0' == *(rec.data + left_.attr_offset + left_.attr_length))) {
      return true;
    } else if (left_.is_attr && comp_op_ == IS_NULL && left_.attr_nullable &&
               '\1' == *(rec.data + left_.attr_offset + left_.attr_length)) {
      return true;
    } else if (!left_.is_attr && left_.value_is_null) {
      return comp_op_ == IS_NULL;
    } else if (!left_.is_attr && !left_.value_is_null) {
      return comp_op_ == IS_NOT_NULL;
    }
    return false;
  }

  char* left_value = nullptr;
  char* right_value = nullptr;

  if (left_.is_attr) {  // value
    left_value = (char*)(rec.data + left_.attr_offset);
  } else {
    left_value = (char*)left_.value;
  }

  if (right_.is_attr) {
    right_value = (char*)(rec.data + right_.attr_offset);
  } else {
    right_value = (char*)right_.value;
  }

  if (right_type_ != SUB_QUERYS) {
    int cmp_result = 0;
    if (left_type_ == right_type_) {
      switch (left_type_) {
        case CHARS: {  // ???????????????????????????????????????
          // ??????C?????????????????????
          cmp_result = strcmp(left_value, right_value);
        } break;
        case INTS: {
          // ???????????????????????????
          // ???int???float??????????????????????????????,???????????????????????????????????????
          int left = *(int*)left_value;
          int right = *(int*)right_value;
          cmp_result = (int)(left - right);
        } break;
        case FLOATS: {
          float left = *(float*)left_value;
          float right = *(float*)right_value;
          cmp_result = condition_float_compare(left, right);
        } break;
        case DATES: {
          int left = *(int*)left_value;
          int right = *(int*)right_value;
          cmp_result = left - right;
        } break;
        default: {
        }
      }
    } else {
      if (left_type_ == INTS && right_type_ == FLOATS) {
        float left = (float)(*(int*)left_value);
        float right = *(float*)right_value;
        cmp_result = condition_float_compare(left, right);
      } else if (left_type_ == FLOATS && right_type_ == INTS) {
        float left = *(float*)left_value;
        float right = (float)(*(int*)right_value);
        cmp_result = condition_float_compare(left, right);
      } else {
        LOG_PANIC("Never should print this.");
        return false;
      }
    }

    switch (comp_op_) {
      case EQUAL_TO:
        return 0 == cmp_result;
      case LESS_EQUAL:
        return cmp_result <= 0;
      case NOT_EQUAL:
        return cmp_result != 0;
      case LESS_THAN:
        return cmp_result < 0;
      case GREAT_EQUAL:
        return cmp_result >= 0;
      case GREAT_THAN:
        return cmp_result > 0;

      default:
        return false;
        break;
    }
  } else {  // left_type_ == SUB_QUERYS || right_type_ == SUB_QUERYS
    TupleSet* sub_query_result_set = ((TupleSet*)right_value);
    if (sub_query_result_set->size() == 0 && comp_op_ != NOT_IN) {
      return false;
    }
    AttrType sub_query_type = sub_query_result_set->schema().field(0).type();
    if (left_type_ != sub_query_type) {
      return false;
    }
    std::shared_ptr<TupleValue> left_tuple_value;
    switch (left_type_) {
      case INTS:
        left_tuple_value = std::make_shared<IntValue>(*(int*)left_value);
        break;
      case FLOATS:
        left_tuple_value = std::make_shared<FloatValue>(*(float*)left_value);
        break;
      case CHARS:
        left_tuple_value = std::make_shared<StringValue>(left_value, 4);
        break;
      case DATES:
        left_tuple_value = std::make_shared<DateValue>(*(int*)left_value);
        break;
      default:
        return false;
        break;
    }

    for (const Tuple& tuple : sub_query_result_set->tuples()) {
      const TupleValue& right_tuple_value = tuple.get(0);
      int cmp_result = left_tuple_value->compare(right_tuple_value);
      if (cmp_result == 0) {
        if (comp_op_ == OP_IN) {
          return true;
        } else if (comp_op_ == NOT_IN) {
          return false;
        } else {
          LOG_PANIC("Never should print this.");
          return false;
        }
      }
    }
    if (comp_op_ == OP_IN) {
      return false;
    } else if (comp_op_ == NOT_IN) {
      return true;
    } else {
      LOG_PANIC("Never should print this.");
      return false;
    }
  }

  LOG_PANIC("Never should print this.");
  return false;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter() {
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter* filters[],
                                  int filter_num, bool own_memory) {
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter* filters[],
                                  int filter_num) {
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table& table, const Condition* conditions,
                                  int condition_num) {
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter** condition_filters = new ConditionFilter*[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter* default_condition_filter =
        new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter**)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record& rec) const {
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}

CorrelationFilter::~CorrelationFilter() {}

RC CorrelationFilter::init(const Table* parent_table,
                           Correlation parent_to_child,
                           Correlation child_to_parent, const char* db,
                           Selects* child_selects, Trx* trx,
                           Condition* condition) {
  parent_table_ = parent_table;
  parent_to_child_ = parent_to_child;
  child_to_parent_ = child_to_parent;
  db_ = db;
  child_selects_ = child_selects;
  trx_ = trx;
  condition_ = condition;

  return RC::SUCCESS;
}

bool CorrelationFilter::filter(const Record& rec) const {
  const TableMeta& table_meta = parent_table_->table_meta();
  const FieldMeta* field =
      table_meta.field(parent_to_child_.rel_attr.attribute_name);

  parent_to_child_.value->type = field->type();
  parent_to_child_.value->data = rec.data + field->offset();

  SelectHandler select_handler;
  RC rc = select_handler.init(db_, child_selects_, trx_);
  if (rc != RC::SUCCESS) {
    return false;
  }
  TupleSet result_set;
  rc = select_handler.handle(result_set);
  if (rc != RC::SUCCESS) {
    return false;
  }

  if (result_set.size() == 0) {
    return false;
  }

  const std::shared_ptr<TupleValue> tuple_value =
      result_set.tuples()[0].get_pointer(0);

  child_to_parent_.value->type = tuple_value->type();
  child_to_parent_.value->data = const_cast<void*>(tuple_value->get());

  rc = condition_filter_.init(*parent_table_, *condition_);
  if (rc != RC::SUCCESS) {
    return false;
  }
  return condition_filter_.filter(rec);
}