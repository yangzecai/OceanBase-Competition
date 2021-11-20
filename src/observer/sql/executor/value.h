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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>

#include <ostream>
#include <string>
#include "sql/parser/parse_defs.h"

class TupleValue {
 public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream& os) const = 0;
  virtual int compare(const TupleValue& other) const = 0;
  virtual const void* get() const = 0;
  virtual AttrType type() const = 0;

 private:
};

class IntValue : public TupleValue {
 public:
  explicit IntValue(int value) : value_(value) {}

  void to_string(std::ostream& os) const override { os << value_; }

  int compare(const TupleValue& other) const override {
    const IntValue& int_other = (const IntValue&)other;
    return value_ - int_other.value_;
  }
  const void* get() const override { return &value_; }
  AttrType type() const override { return INTS; }

 private:
  int value_;
};

class FloatValue : public TupleValue {
 public:
  explicit FloatValue(float value) : value_(value) {}

  void to_string(std::ostream& os) const override {
    char str[64];
    snprintf(str, sizeof(str), "%.2f", value_);
    int tail = strlen(str) - 1;
    for (; tail >= 1; --tail) {
      if (str[tail] != '0') {
        break;
      } else {
        str[tail] = '\0';
      }
    }
    if (str[tail] == '.') {
      str[tail] = '\0';
    }
    os << str;
  }

  int compare(const TupleValue& other) const override {
    const FloatValue& float_other = (const FloatValue&)other;
    float result = value_ - float_other.value_;
    if (result > 0) {  // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  const void* get() const override { return &value_; }
  AttrType type() const override { return FLOATS; }

 private:
  float value_;
};

class StringValue : public TupleValue {
 public:
  StringValue(const char* value, int len) : value_(value, len) {}
  explicit StringValue(const char* value) : value_(value) {}

  void to_string(std::ostream& os) const override { os << value_; }

  int compare(const TupleValue& other) const override {
    const StringValue& string_other = (const StringValue&)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  const void* get() const override { return value_.data(); }
  AttrType type() const override { return CHARS; }

 private:
  std::string value_;
};

class DateValue : public TupleValue {
 public:
  explicit DateValue(int timestamp) : value_(timestamp) {}

  void to_string(std::ostream& os) const override {
    time_t timestamp = static_cast<time_t>(value_);
    tm* time = gmtime(&timestamp);
    int year = time->tm_year + 1900;
    int month = time->tm_mon + 1;
    int day = time->tm_mday;
    char s[16];
    sprintf(s, "%04d-%02d-%02d", year, month, day);
    os << s;
  }

  int compare(const TupleValue& other) const override {
    const DateValue& date_other = (const DateValue&)other;
    return value_ - date_other.value_;
  }

  const void* get() const override { return &value_; }
  AttrType type() const override { return DATES; }

 private:
  int value_;
};

class NullValue : public TupleValue {
 public:
  NullValue() {}

  void to_string(std::ostream& os) const override { os << "null"; }

  int compare(const TupleValue& other) const override { return -2; }

  const void* get() const override { return nullptr; }
  AttrType type() const override { return NULLS; }
};

class TextValue : public TupleValue {
 public:
  explicit TextValue(std::string text_data) {
    if (text_data.size() > 4096) {
      text_data.resize(4096);
    }
    value_ = text_data;
  }

  void to_string(std::ostream& os) const override { os << value_; }

  int compare(const TupleValue& other) const override { return -2; }

  const void* get() const override { return nullptr; }
  AttrType type() const override { return TEXTS; }

 private:
  std::string value_;
};

#endif  //__OBSERVER_SQL_EXECUTOR_VALUE_H_
