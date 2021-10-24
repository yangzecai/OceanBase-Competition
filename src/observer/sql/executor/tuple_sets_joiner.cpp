#include <string>

#include "common/log/log.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "tuple_sets_joiner.h"

TupleSetsJoiner::TupleSetsJoiner() {}

// FIXME: 此处只有condition校验，其他需要外部保证
RC TupleSetsJoiner::init(const char* db, const Selects* selects,
                         const std::vector<TupleSet>& tuple_sets) {
  db_ = db;
  selects_ = selects;
  tuple_sets_ = &tuple_sets;

  if (selects_->relation_num <= 1) {
    return RC::GENERIC_ERROR;
  }

  for (size_t i = 0; i < selects->relation_num; ++i) {
    tables_[std::string(selects_->relations[i])] =
        DefaultHandler::get_default().find_table(db, selects_->relations[i]);
  }

  RC rc = init_conditions();
  if (rc != SUCCESS) {
    LOG_WARN("Invalid conditions\n");
    return rc;
  }

  rc = make_schema();
  if (rc != SUCCESS) {
    LOG_WARN("something wrong with schema\n");
    return rc;
  }

  for (const TupleField& tuple_field : joined_tuple_set_.schema().fields()) {
    for (size_t i = 0; i < selects_->relation_num; ++i) {
      if (strcmp(tuple_field.table_name(), selects_->relations[i]) == 0) {
        tuple_sets_scan_order_.push_back(i);
      }
    }
  }

  return RC::SUCCESS;
}

void TupleSetsJoiner::execute() {
  std::vector<int> tuple_set_indexes;
  make_tuples_dfs(tuple_set_indexes);
}

void TupleSetsJoiner::make_tuples_dfs(std::vector<int>& tuple_indexes) {
  if (tuple_indexes.size() == tuple_sets_->size()) {
    add_or_filter_tuple(tuple_indexes);
    return;
  }

  int tuple_set_index = tuple_sets_->size() - tuple_indexes.size() - 1;
  int tuple_size = tuple_sets_->at(tuple_set_index).size();
  for (int i = 0; i < tuple_size; ++i) {
    tuple_indexes.push_back(i);
    make_tuples_dfs(tuple_indexes);
    tuple_indexes.pop_back();
  }
}

std::vector<const Tuple*> TupleSetsJoiner::load_tuples(
    const std::vector<int>& tuple_indexes) const {
  std::vector<const Tuple*> tuples(tuple_indexes.size());
  for (size_t i = 0; i < tuple_indexes.size(); ++i) {
    size_t true_tuple_index = tuple_indexes.size() - i - 1;
    tuples[true_tuple_index] =
        &tuple_sets_->at(true_tuple_index).get(tuple_indexes[i]);
  }
  return tuples;
}

void TupleSetsJoiner::add_or_filter_tuple(
    const std::vector<int>& tuple_indexes) {
  if (filter_tuple(tuple_indexes)) {
    Tuple tuple;
    scan_tuple_values(tuple_indexes,
                      [&tuple](std::shared_ptr<TupleValue> tuple_value) {
                        tuple.add(tuple_value);
                      });
    joined_tuple_set_.add(std::move(tuple));
  }
}

void TupleSetsJoiner::scan_tuple_values(
    const std::vector<int>& tuple_indexes,
    std::function<void(std::shared_ptr<TupleValue>)> func) const {
  std::vector<const Tuple*> tuples = load_tuples(tuple_indexes);
  std::vector<int> tuple_ptrs(tuples.size(), 0);

  for (int tuple_set_index : tuple_sets_scan_order_) {
    const Tuple* tuple = tuples[tuple_set_index];
    func(tuple->get_pointer(tuple_ptrs[tuple_set_index]++));
  }
}

bool TupleSetsJoiner::filter_tuple(
    const std::vector<int>& tuple_indexes) const {
  std::vector<const Tuple*> tuples = load_tuples(tuple_indexes);

  for (const JoinCondition& condition : join_conditions_) {
    const TupleValue& left_value =
        tuples[condition.left_tuple_set_index]->get(condition.left_field_index);
    const TupleValue& right_value =
        tuples[condition.right_tuple_set_index]->get(
            condition.right_field_index);
    
    // FIXME: 不同类型间比较
    int cmp_result = left_value.compare(right_value);

    bool pass = false;
    switch (condition.comp_op) {
      case EQUAL_TO:
        pass = (0 == cmp_result);
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

RC TupleSetsJoiner::make_schema() {
  TupleSchema schema;
  int attr_num = selects_->attr_num;
  const RelAttr* attributes = selects_->attributes;

  if (attr_num == 1 && attributes[0].relation_name == nullptr &&
      0 == strcmp("*", attributes[0].attribute_name)) {
    for (int i = selects_->relation_num - 1; i >= 0; --i) {
      TupleSchema::from_table(get_table(selects_->relations[i]), schema);
    }
  } else {
    for (int i = attr_num - 1; i >= 0; --i) {
      const RelAttr& attr = attributes[i];
      if (attr.relation_name == nullptr) {
        LOG_WARN("The table name for the attribute is not specified. %s",
                 attr.attribute_name);
        return RC::SCHEMA_FIELD_NAME_ILLEGAL;
      }
      const Table* table = get_table(attr.relation_name);
      if (0 == strcmp("*", attr.attribute_name)) {
        TupleSchema::from_table(table, schema);
      } else {
        const FieldMeta* field_meta =
            table->table_meta().field(attr.attribute_name);
        if (nullptr == field_meta) {
          LOG_WARN("No such field. %s.%s", table->name(), attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        schema.add_if_not_exists(field_meta->type(), table->name(),
                                 field_meta->name());
      }
    }
  }
  joined_tuple_set_.set_schema(schema);
  return RC::SUCCESS;
}

const Table* TupleSetsJoiner::get_table(const char* table_name) const {
  if (table_name == nullptr) {
    return nullptr;
  }
  std::string table_name_str = std::string(table_name);
  return get_table(table_name_str);
}

const Table* TupleSetsJoiner::get_table(const std::string& table_name) const {
  if (tables_.find(table_name) == tables_.end()) {
    return nullptr;
  } else {
    return tables_.at(table_name);
  }
}

RC TupleSetsJoiner::init_conditions() {
  for (size_t i = 0; i < selects_->condition_num; ++i) {
    const Condition& condition = selects_->conditions[i];

    if (condition.left_is_attr && !condition.right_is_attr) {
      if (condition.left_attr.relation_name == nullptr) {
        return RC::SCHEMA_TABLE_NAME_ILLEGAL;
      }
      const Table* left_table = get_table(condition.left_attr.relation_name);
      if (left_table == nullptr) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      // FIXME: 这里可能忽略了不同value类型之间转换
      if (RC::SUCCESS !=
          left_table->check_attribute_value_valid(
              condition.left_attr.attribute_name, &condition.right_value)) {
        return RC::SCHEMA_FIELD_MISSING;
      }

    } else if (!condition.left_is_attr && condition.right_is_attr) {
      if (condition.right_attr.relation_name == nullptr) {
        return RC::SCHEMA_TABLE_NAME_ILLEGAL;
      }
      const Table* right_table = get_table(condition.right_attr.relation_name);
      if (right_table == nullptr) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      // FIXME: 这里可能忽略了不同value类型之间转换
      if (RC::SUCCESS !=
          right_table->check_attribute_value_valid(
              condition.right_attr.attribute_name, &condition.left_value)) {
        return RC::SCHEMA_FIELD_MISSING;
      }

    } else if (condition.left_is_attr && condition.right_is_attr &&
               0 != strcmp(condition.left_attr.relation_name,
                           condition.right_attr.relation_name)) {
      if (condition.left_attr.relation_name == nullptr ||
          condition.right_attr.relation_name == nullptr) {
        return RC::SCHEMA_TABLE_NAME_ILLEGAL;
      }

      const Table* left_table = get_table(condition.left_attr.relation_name);
      const Table* right_table = get_table(condition.right_attr.relation_name);
      if (nullptr == left_table || nullptr == right_table) {
        return RC::SCHEMA_FIELD_MISSING;
      }

      if ((RC::SUCCESS != left_table->check_attribute_valid(
                              condition.left_attr.attribute_name)) ||
          (RC::SUCCESS != right_table->check_attribute_valid(
                              condition.right_attr.attribute_name))) {
        return RC::SCHEMA_FIELD_MISSING;
      }

      JoinCondition join_condition;
      memset(&join_condition, 0, sizeof(join_condition));
      join_condition.comp_op = condition.comp;
      bool left_pass = false, right_pass = false;

      for (size_t j = 0; j < tuple_sets_->size(); ++j) {
        const char* table_name =
            tuple_sets_->at(j).schema().field(0).table_name();

        if (0 == strcmp(table_name, condition.left_attr.relation_name)) {
          int field_index = tuple_sets_->at(j).schema().index_of_field(
              table_name, condition.left_attr.attribute_name);
          if (field_index == -1) {
            return RC::SCHEMA_FIELD_MISSING;
          }

          join_condition.left_tuple_set_index = j;
          join_condition.left_field_index = field_index;
          left_pass = true;
          continue;

        } else if (0 ==
                   strcmp(table_name, condition.right_attr.relation_name)) {
          int field_index = tuple_sets_->at(j).schema().index_of_field(
              table_name, condition.right_attr.attribute_name);
          if (field_index == -1) {
            return RC::SCHEMA_FIELD_MISSING;
          }

          join_condition.right_tuple_set_index = j;
          join_condition.right_field_index = field_index;
          right_pass = true;
          continue;
        }

        if (left_pass && right_pass) {
          break;
        }
      }

      if (!left_pass || !right_pass) {
        LOG_PANIC("should not print this message");
        return RC::SCHEMA_FIELD_MISSING;
      }

      join_conditions_.push_back(std::move(join_condition));
    }
  }

  return RC::SUCCESS;
}
