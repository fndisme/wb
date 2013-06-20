/*
 * =====================================================================================
 *
 *       Filename:  NetDataRecord.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012年08月10日 10时05分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "NetDataRecord.h"
#include <atomic>

namespace {
  static std::atomic<size_t> gCurrentPreparedMessageSize = 0;
  static std::atomic<size_t> gTotalPreparedMessageSize = 0;
  static std::atomic<size_t> gTotalSendMessageNumber = 0;
  static std::atomic<uint64_t> gTotalSendMessageSize = 0;
}

namespace WebGame {
  void prepare_message_to_net_pool(size_t size) {
    gCurrentPreparedMessageSize++;
    gTotalPreparedMessageSize++;
    gTotalSendMessageSize += size;
  }

  void add_record_to_net_poll(size_t i) {
    gCurrentPreparedMessageSize -= i;
    gTotalSendMessageNumber += i;
  }

  size_t current_prepared_message_number_of_net_pool() {
    return gCurrentPreparedMessageSize;
  }

  uint64_t total_prepared_size() {
    return gTotalSendMessageSize;
  }
}
