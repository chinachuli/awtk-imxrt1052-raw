/**
 * File:   theme_gen.cc
 * Author: AWTK Develop Team
 * Brief:  theme_gen interface
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-01-14 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "theme_gen.h"
#include "tkc/utils.h"
#include "base/enums.h"
#include "base/theme.h"
#include "tkc/buffer.h"
#include "tkc/types_def.h"

Style::Style() {
}

Style::Style(const string& widget_type, const string& name, const string& state) {
  this->widget_type = widget_type;
  this->name = name;
  this->state = state;
}

Style::~Style() {
}

bool Style::AddInt(const string& name, int32_t value) {
  for (vector<NameIntValue>::iterator i = this->int_values.begin(); i != this->int_values.end();
       i++) {
    if (i->name == name) {
      i->value = value;
      return true;
    }
  }

  this->int_values.push_back(NameIntValue(name, value));

  return true;
}

bool Style::AddString(const string& name, const string& value) {
  for (vector<NameStringValue>::iterator i = this->str_values.begin(); i != this->str_values.end();
       i++) {
    if (i->name == name) {
      i->value = value;
      return true;
    }
  }

  this->str_values.push_back(NameStringValue(name, value));

  return true;
}

bool Style::Reset() {
  this->int_values.clear();
  this->str_values.clear();

  return true;
}

bool Style::Merge(Style& other) {
  for (vector<NameIntValue>::iterator i = other.int_values.begin(); i != other.int_values.end();
       i++) {
    this->AddInt(i->name, i->value);
  }

  for (vector<NameStringValue>::iterator i = other.str_values.begin(); i != other.str_values.end();
       i++) {
    this->AddString(i->name, i->value);
  }

  return true;
}

uint8_t* Style::Output(uint8_t* buff, uint32_t max_size) {
  uint32_t size = 0;
  uint8_t* p = buff;
  uint8_t* end = buff + max_size;
  return_value_if_fail(buff != NULL && max_size > 32, NULL);

  size = this->int_values.size();
  save_uint32(p, size);
  printf("  size=%d widget_type=%s name=%s state=%s\n", size, this->widget_type.c_str(),
         this->name.c_str(), this->state.c_str());
  for (vector<NameIntValue>::iterator i = this->int_values.begin(); i != this->int_values.end();
       i++) {
    const string& name = i->name;
    uint32_t value = i->value;
    style_int_data_t data;

    data.value = value;
    tk_strncpy(data.name, name.c_str(), TK_NAME_LEN);

    return_value_if_fail((end - p) > sizeof(data), NULL);
    memcpy(p, &data, sizeof(data));
    p += sizeof(data);

    printf("    %s=0x%08x\n", data.name, data.value);
  }

  return_value_if_fail((end - p) > 32, NULL);

  size = this->str_values.size();
  save_uint32(p, size);
  for (vector<NameStringValue>::iterator i = this->str_values.begin(); i != this->str_values.end();
       i++) {
    style_str_data_t data;
    const string& name = i->name;
    const string& value = i->value;

    tk_strncpy(data.name, name.c_str(), TK_NAME_LEN);
    tk_strncpy(data.value, value.c_str(), TK_NAME_LEN);

    return_value_if_fail((end - p) > sizeof(data), NULL);
    memcpy(p, &data, sizeof(data));
    p += sizeof(data);

    printf("    %s=%s\n", data.name, data.value);
  }

  return p;
}

bool ThemeGen::AddStyle(const Style& style) {
  this->styles.push_back(style);

  return true;
}

uint8_t* ThemeGen::Output(uint8_t* buff, uint32_t max_size) {
  uint32_t nr = this->styles.size();
  uint8_t* end = buff + max_size;
  theme_header_t* header = (theme_header_t*)buff;
  uint32_t data_start = sizeof(theme_header_t) + nr * sizeof(theme_item_t);
  theme_item_t* item = (theme_item_t*)(buff + sizeof(theme_header_t));
  uint8_t* p = buff + data_start;

  return_value_if_fail(p != NULL && max_size > data_start + 128, NULL);

  memset(buff, 0x00, max_size);

  header->magic = THEME_MAGIC;
  header->version = 0;
  header->nr = nr;

  for (vector<Style>::iterator iter = this->styles.begin(); iter != this->styles.end(); iter++) {
    item->offset = p - buff;
    tk_strncpy(item->state, iter->state.c_str(), TK_NAME_LEN);
    tk_strncpy(item->name, iter->name.c_str(), TK_NAME_LEN);
    tk_strncpy(item->widget_type, iter->widget_type.c_str(), TK_NAME_LEN);

    p = iter->Output(p, end - p);
    item++;
  }

  return p;
}
