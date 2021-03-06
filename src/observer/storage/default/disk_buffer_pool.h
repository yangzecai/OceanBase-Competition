/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//
#ifndef __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
#define __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <vector>

#include "rc.h"

typedef int PageNum;

//
#define BP_INVALID_PAGE_NUM (-1)
#define BP_PAGE_SIZE (1 << 12)
#define BP_PAGE_DATA_SIZE (BP_PAGE_SIZE - sizeof(PageNum))
#define BP_FILE_SUB_HDR_SIZE (sizeof(BPFileSubHeader))
#define BP_BUFFER_SIZE 50
#define MAX_OPEN_FILE 1024

typedef struct {
  PageNum page_num;
  char data[BP_PAGE_DATA_SIZE];
} Page;
// sizeof(Page) should be equal to BP_PAGE_SIZE

typedef struct {
  PageNum page_count;
  int allocated_pages;
} BPFileSubHeader;

typedef struct {
  bool dirty;
  unsigned int pin_count;
  unsigned long acc_time;
  int file_desc;
  Page page;
} Frame;

typedef struct {
  bool open;
  Frame* frame;
} BPPageHandle;

class BPFileHandle {
 public:
  BPFileHandle() { memset(this, 0, sizeof(*this)); }

 public:
  bool bopen;
  const char* file_name;
  int file_desc;
  Frame* hdr_frame;
  Page* hdr_page;
  char* bitmap;
  BPFileSubHeader* file_sub_header;
};

class BPManager {
 public:
  BPManager(int size = BP_BUFFER_SIZE) {
    this->size = size;
    frame = new Frame[size];
    allocated = new bool[size];
    for (int i = 0; i < size; i++) {
      allocated[i] = false;
      frame[i].pin_count = 0;
    }
  }

  ~BPManager() {
    delete[] frame;
    delete[] allocated;
    size = 0;
    frame = nullptr;
    allocated = nullptr;
  }

  Frame* alloc();

  Frame* get(int file_desc, PageNum page_num);

  RC dispose(Frame* buf);

  RC dispose(int file_desc, PageNum page_num);

  RC flush(Frame* f);

  RC force_page(int file_desc, PageNum page_num);

  RC force_all_pages(int file_desc);

  Frame* getFrame() { return frame; }

  bool* getAllocated() { return allocated; }

 private:
  int size;
  Frame* frame = nullptr;
  bool* allocated = nullptr;
};

class DiskBufferPool {
 public:
  /**
   * ???????????????????????????????????????????????????
   */
  RC create_file(const char* file_name);

  /**
   * ???????????????????????????????????????????????????
   */
  RC remove_file(int file_id);

  /**
   * ??????????????????????????????????????????????????????ID
   * @return
   */
  RC open_file(const char* file_name, int* file_id);

  /**
   * ??????fileID?????????????????????
   */
  RC close_file(int file_id);

  /**
   * ????????????ID?????????????????????????????????????????????????????????????????????
   * @return
   */
  RC get_this_page(int file_id, PageNum page_num, BPPageHandle* page_handle);

  /**
   * ???????????????????????????????????????????????????????????????????????????????????????????????????
   * ?????????????????????????????????????????????????????????????????????????????????
   * ?????????????????????????????????????????????????????????????????????????????????
   */
  RC allocate_page(int file_id, BPPageHandle* page_handle);

  /**
   * ????????????????????????????????????????????????
   */
  RC get_page_num(BPPageHandle* page_handle, PageNum* page_num);

  /**
   * ??????????????????????????????????????????????????????
   */
  RC get_data(BPPageHandle* page_handle, char** data);

  /**
   * ????????????????????????pageNum?????????????????????????????????
   */
  RC dispose_page(int file_id, PageNum page_num);

  /**
   * ?????????????????????????????????????????? ?????????????????? ????????????????????????pinned page
   * @param file_handle
   * @param page_num ???????????????page_num ??????????????????
   */
  RC force_page(int file_id, PageNum page_num);

  /**
   * ?????????????????????????????????????????????????????????????????????????????????????????????
   * ????????????????????????????????????????????????????????????????????????????????????
   */
  RC mark_dirty(BPPageHandle* page_handle);

  /**
   * ?????????????????????pageHandle???????????????????????????????????????
   * ?????????GetThisPage???AllocatePage??????????????????????????????????????????
   * ?????????????????????????????????????????????????????????????????????????????????????????????
   * ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
   */
  RC unpin_page(BPPageHandle* page_handle);

  /**
   * ????????????????????????
   */
  RC get_page_count(int file_id, int* page_count);

  RC flush_all_pages(int file_id);

 protected:
  RC allocate_block(Frame** buf);
  RC dispose_block(Frame* buf);

  /**
   * ?????????????????????????????????????????????????????????pinned page
   * @param file_handle
   * @param page_num ???????????????page_num ??????????????????
   */
  RC force_page(BPFileHandle* file_handle, PageNum page_num);
  RC force_all_pages(BPFileHandle* file_handle);
  RC check_file_id(int file_id);
  RC check_page_num(PageNum page_num, BPFileHandle* file_handle);
  RC load_page(PageNum page_num, BPFileHandle* file_handle, Frame* frame);
  RC flush_block(Frame* frame);

 private:
  BPManager bp_manager_;
  BPFileHandle* open_list_[MAX_OPEN_FILE] = {nullptr};
};

DiskBufferPool* theGlobalDiskBufferPool();

#endif  //__OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
