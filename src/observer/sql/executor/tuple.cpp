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

#include <algorithm>

#include "common/log/log.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"

Tuple::Tuple(const Tuple& other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple&& other) noexcept : values_(std::move(other.values_)) {}

Tuple& Tuple::operator=(Tuple&& other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {}

// add (Value && value)
void Tuple::add(TupleValue* value) { values_.emplace_back(value); }
void Tuple::add(const std::shared_ptr<TupleValue>& other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) { add(new IntValue(value)); }

void Tuple::add(float value) { add(new FloatValue(value)); }

void Tuple::add(const char* s, int len) { add(new StringValue(s, len)); }

void Tuple::add_date(int timestamp) { add(new DateValue(timestamp)); }

void Tuple::add_null() { add(new NullValue()); }
////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table* table, TupleSchema& schema) {
  const char* table_name = table->name();
  const TableMeta& table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta* field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(AttrType type, const char* table_name,
                      const char* field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char* table_name,
                                    const char* field_name) {
  for (const auto& field : fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::add(const Aggregate& aggregate) {
  aggregates_.insert(std::make_pair(fields_.size(), aggregate));
  add(UNDEFINED, "", "");
}

void TupleSchema::append(const TupleSchema& other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto& field : other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char* table_name,
                                const char* field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField& field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream& os, bool multi_table) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(),
                                               end = --fields_.end();
       iter != end; ++iter) {
    if (iter->is_aggregate()) {
      print_aggregate(os, iter - fields_.begin());
    } else {
      if (multi_table) {
        os << iter->table_name() << ".";
      }
      os << iter->field_name();
    }
    os << " | ";
  }

  if (fields_.back().is_aggregate()) {
    print_aggregate(os, fields_.end() - fields_.begin() - 1);
  } else {
    if (multi_table) {
      os << fields_.back().table_name() << ".";
    }
    os << fields_.back().field_name();
  }
  os << std::endl;
}

void TupleSchema::print_aggregate(std::ostream& os,
                                  size_t aggregate_index) const {
  if (aggregates_.find(aggregate_index) == aggregates_.end()) {
    return;
  }
  const Aggregate& aggregate = aggregates_.at(aggregate_index);
  switch (aggregate.type) {
    case AGG_COUNT:
      os << "count";
      break;
    case AGG_MAX:
      os << "max";
      break;
    case AGG_MIN:
      os << "min";
      break;
    case AGG_AVG:
      os << "avg";
      break;
    default:
      LOG_PANIC("should not print this message");
      break;
  }
  os << '(';
  if (aggregate.is_attr) {
    const RelAttr& attribute = aggregate.attr;
    if (attribute.relation_name != nullptr) {
      os << attribute.relation_name << '.';
    }
    os << attribute.attribute_name;
  } else {
    const Value& value = aggregate.value;
    switch (value.type) {
      case CHARS: {
        if (0 == strcmp((char*)value.data, "*")) {
          os << (char*)value.data;
        } else {
          os << '\'' << (char*)value.data << '\'';
        }
      } break;
      case INTS:
        os << *(int*)value.data;
        break;
      case FLOATS: {
        FloatValue float_value(*(float*)value.data);
        float_value.to_string(os);
      } break;
      case DATES: {
        DateValue date_value(*(int*)value.data);
        date_value.to_string(os);
      } break;
      default:
        LOG_PANIC("should not print this message");
        break;
    }
  }
  os << ')';
}
/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet&& other)
    : tuples_(std::move(other.tuples_)), schema_(other.schema_) {
  other.schema_.clear();
}

TupleSet& TupleSet::operator=(TupleSet&& other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple&& tuple) { tuples_.emplace_back(std::move(tuple)); }

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream& os, bool multi_table) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os, multi_table);

  for (const Tuple& item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>>& values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator
             iter = values.begin(),
             end = --values.end();
         iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::sort_tuples(
    std::function<bool(const Tuple& lhs, const Tuple& rhs)> less_func) {
  std::sort(tuples_.begin(), tuples_.end(), less_func);
}

void TupleSet::set_schema(const TupleSchema& schema) { schema_ = schema; }

const TupleSchema& TupleSet::get_schema() const { return schema_; }

bool TupleSet::is_empty() const { return tuples_.empty(); }

int TupleSet::size() const { return tuples_.size(); }

const Tuple& TupleSet::get(int index) const { return tuples_[index]; }

const std::vector<Tuple>& TupleSet::tuples() const { return tuples_; }

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table* table, TupleSet& tuple_set)
    : table_(table), tuple_set_(tuple_set) {}

void TupleRecordConverter::add_record(const char* record) {
  const TupleSchema& schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta& table_meta = table_->table_meta();
  for (const TupleField& field : schema.fields()) {
    const FieldMeta* field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    if (field_meta->nullable() &&
        '\1' == *(record + field_meta->offset() + field_meta->len())) {
      tuple.add_null();
      continue;
    }
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      } break;
      case FLOATS: {
        float value = *(float*)(record + field_meta->offset());
        tuple.add(value);
      } break;
      case CHARS: {
        const char* s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      } break;
      case DATES: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add_date(value);
      } break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}
