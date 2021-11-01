#include <sstream>

#include <cassert>
#include "common/log/log.h"
#include "session/session.h"
#include "sql/executor/select_handler.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"

SelectHandler::SelectHandler()
    : db_(nullptr), session_event_(nullptr), trx_(nullptr), selects_(nullptr) {}

SelectHandler::~SelectHandler() {
  if (!select_filters_.empty()) {
    for (size_t i = 0; i < select_filters_.size(); ++i) {
      for (size_t j = 0; j < select_filters_[i].size(); ++j) {
        delete select_filters_[i][j];
        select_filters_[i][j] = nullptr;
      }
    }
  }
  select_filters_.clear();

  if (session_event_->get_response_len() == 0) {
    session_event_->set_response("FAILURE\n");
  }
}

RC SelectHandler::init(const char* db, Query* sql,
                       SessionEvent* session_event) {
  RC rc = RC::SUCCESS;
  db_ = db;
  session_event_ = session_event;
  trx_ = session_event->get_client()->session->current_trx();
  selects_ = &sql->sstr.selection;

  rc = init_tables();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = init_schemas();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = init_conditions();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::shared_ptr<AggregateExeNode> root_exe_node =
      std::make_shared<AggregateExeNode>();
  rc = root_exe_node->init(trx_, this);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  root_exe_node_ = root_exe_node;
  return rc;
}

RC SelectHandler::handle() {
  TupleSet tuple_set;
  RC rc = root_exe_node_->execute(tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::stringstream ss;
  tuple_set.print(ss, tables_.size() > 1);
  session_event_->set_response(ss.str());

  return rc;
}

RC SelectHandler::init_tables() {
  assert(tables_.empty());
  for (int i = selects_->relation_num - 1; i >= 0; --i) {
    const char* table_name = selects_->relations[i];
    Table* table = DefaultHandler::get_default().find_table(db_, table_name);
    if (table == nullptr) {
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    table_indexes_[table_name] = tables_.size();
    tables_.push_back(table);
  }
  return RC::SUCCESS;
}

RC SelectHandler::init_schemas() {
  assert(!tables_.empty() && select_schemas_.empty());

  RC rc = RC::SUCCESS;
  select_schemas_.resize(tables_.size());

  for (size_t i = 0, j = 0; i < selects_->attr_num; ++i) {
    const RelAttr* attribute = selects_->attributes + i;
    if (!is_aggregate(attribute)) {
      rc = add_attribute_to_project_schema(attribute);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      rc = add_attribute_to_select_schemas(attribute);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else {
      const Aggregate* aggregate = selects_->aggregates + j++;
      if (!aggregate->is_attr && aggregate->value.type == CHARS &&
          strcmp((char*)aggregate->value.data, "*") == 0 &&
          aggregate->type != AGG_COUNT) {
        return RC::SCHEMA_FIELD_NAME_ILLEGAL;
      }
      rc = add_aggregate_to_project_schema(aggregate);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      rc = add_aggregate_to_select_schemas(aggregate);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  for (size_t i = 0; i < selects_->condition_num; ++i) {
    const Condition* condition = selects_->conditions + i;
    if (condition->left_is_attr) {
      rc = add_attribute_to_select_schemas(&condition->left_attr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    if (condition->right_is_attr) {
      rc = add_attribute_to_select_schemas(&condition->right_attr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return rc;
}

RC SelectHandler::init_conditions() {
  assert(!tables_.empty());

  RC rc = RC::SUCCESS;
  select_filters_.resize(tables_.size());

  for (size_t i = 0; i < selects_->condition_num; ++i) {
    const Condition* condition = selects_->conditions + i;
    if (is_join_condition(condition)) {
      rc = add_condition_to_join_filter(condition);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else {
      rc = add_condition_to_select_filters(condition);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return rc;
}

bool SelectHandler::is_aggregate(const RelAttr* attribute) {
  return *attribute->attribute_name == '\0';
}

int SelectHandler::index_of_table(std::string table_name) {
  auto iter = table_indexes_.find(table_name);
  if (iter != table_indexes_.end()) {
    return iter->second;
  } else {
    return -1;
  }
}

RC SelectHandler::add_attribute_to_select_schemas(const RelAttr* attribute) {
  assert(!tables_.empty() && !select_schemas_.empty());
  assert(attribute->attribute_name != nullptr);

  RC rc = RC::SUCCESS;
  const char* table_name = attribute->relation_name;
  char* attr_name = attribute->attribute_name;

  if (table_name == nullptr) {
    if (tables_.size() == 1) {
      rc = add_attribute_to_schema(attribute, &select_schemas_[0]);
      if (rc != RC::SUCCESS) {
        return rc;
      }

    } else if (*attr_name == '*') {
      RelAttr tmp_attribute;
      for (size_t i = 0; i < tables_.size(); ++i) {
        relation_attr_init(&tmp_attribute, tables_[i]->name(), attr_name);
        add_attribute_to_schema(&tmp_attribute, &select_schemas_[i]);
        relation_attr_destroy(&tmp_attribute);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }

    } else {
      return RC::SCHEMA_FIELD_MISSING;
    }

  } else {
    int table_index = index_of_table(table_name);
    if (table_index == -1) {
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }
    RC rc = add_attribute_to_schema(attribute, &select_schemas_[table_index]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}
RC SelectHandler::add_aggregate_to_select_schemas(const Aggregate* aggregate) {
  RC rc = RC::SUCCESS;
  if (aggregate->is_attr) {
    rc = add_attribute_to_select_schemas(&aggregate->attr);
  }
  return rc;
}
RC SelectHandler::add_attribute_to_project_schema(const RelAttr* attribute) {
  RC rc = add_attribute_to_schema(attribute, &project_schema_);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return rc;
}
RC SelectHandler::add_aggregate_to_project_schema(const Aggregate* aggregate) {
  project_schema_.add(*aggregate);
  return RC::SUCCESS;
}

RC SelectHandler::add_attribute_to_schema(const RelAttr* attribute,
                                          TupleSchema* schema) {
  assert(!tables_.empty());

  const char* table_name = attribute->relation_name;
  const char* attr_name = attribute->attribute_name;

  if (table_name == nullptr && *attr_name == '*') {  // *
    for (Table* table : tables_) {
      TupleSchema::from_table(table, *schema);
    }

  } else if (table_name != nullptr && *attr_name == '*') {  // t.*
    int table_index = index_of_table(table_name);
    if (-1 == table_index) {
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }
    Table* table = tables_[table_index];
    TupleSchema::from_table(table, *schema);

  } else if (table_name == nullptr && selects_->relation_num == 1) {  // a
    Table* table = tables_.back();
    const FieldMeta* field_meta = table->table_meta().field(attr_name);
    if (nullptr == field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    schema->add_if_not_exists(field_meta->type(), table->name(),
                              field_meta->name());

  } else if (table_name != nullptr && attr_name != nullptr) {  // t.a
    int table_index = index_of_table(table_name);
    if (-1 == table_index) {
      return RC::SCHEMA_TABLE_NAME_ILLEGAL;
    }
    Table* table = tables_[table_index];
    const FieldMeta* field_meta = table->table_meta().field(attr_name);
    if (nullptr == field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    schema->add_if_not_exists(field_meta->type(), table->name(),
                              field_meta->name());

  } else {
    LOG_PANIC("should not print this message");
    return RC::SCHEMA_FIELD_MISSING;
  }

  return RC::SUCCESS;
}

bool SelectHandler::is_join_condition(const Condition* condition) {
  if (tables_.size() > 1 && condition->left_is_attr &&
      condition->right_is_attr) {
    const char* left_table_name = condition->left_attr.relation_name;
    const char* right_table_name = condition->right_attr.relation_name;
    if (left_table_name != nullptr && right_table_name != nullptr &&
        0 != strcmp(left_table_name, right_table_name)) {
      return true;
    }
  }
  return false;
}
RC SelectHandler::add_condition_to_select_filters(const Condition* condition) {
  RC rc = RC::SUCCESS;
  if (!condition->left_is_attr && !condition->right_is_attr) {
    for (size_t i = 0; i < select_filters_.size(); ++i) {
      DefaultConditionFilter* condition_filter = new DefaultConditionFilter();
      select_filters_[i].push_back(condition_filter);
      rc = condition_filter->init(*tables_[i], *condition);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  } else {
    int table_index = -1;
    if (tables_.size() == 1) {
      table_index = 0;
    } else {
      const char* table_name = nullptr;
      if (condition->left_is_attr) {
        table_name = condition->left_attr.relation_name;
      } else if (condition->right_is_attr) {
        table_name = condition->right_attr.relation_name;
      }
      if (table_name == nullptr) {
        return RC::SCHEMA_FIELD_MISSING;
      }
      table_index = index_of_table(table_name);
      if (table_index == -1) {
        return RC::SCHEMA_FIELD_MISSING;
      }
    }

    DefaultConditionFilter* condition_filter = new DefaultConditionFilter();
    select_filters_[table_index].push_back(condition_filter);
    rc = condition_filter->init(*tables_[table_index], *condition);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return RC::SUCCESS;
}
RC SelectHandler::add_condition_to_join_filter(const Condition* condition) {
  // init_schemas() 已经校验过了
  const char* left_table_name = condition->left_attr.relation_name;
  const char* right_table_name = condition->right_attr.relation_name;
  const char* left_attr_name = condition->left_attr.attribute_name;
  const char* right_attr_name = condition->right_attr.attribute_name;

  JoinExeNode::JoinFilter filter;
  filter.comp = condition->comp;
  filter.left_tuple_set_index = index_of_table(left_table_name);
  filter.right_tuple_set_index = index_of_table(right_table_name);
  filter.left_field_index =
      select_schemas_[filter.left_tuple_set_index].index_of_field(
          left_table_name, left_attr_name);
  filter.right_field_index =
      select_schemas_[filter.right_tuple_set_index].index_of_field(
          right_table_name, right_attr_name);
  join_filter_.push_back(filter);

  return RC::SUCCESS;
}
