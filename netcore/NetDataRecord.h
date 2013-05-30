/*
 * =====================================================================================
 *
 *       Filename:  NetDataRecord.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月10日 10时03分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_NETDATARECORD_H
#define FND_WEBGAME_NETDATARECORD_H
#include <cstddef>
#include <stdint.h>

namespace WebGame {
  void prepare_message_to_net_pool(size_t) ;
  void add_record_to_net_poll(size_t i = 1) ;
  size_t current_prepared_message_number_of_net_pool() ;
  uint64_t total_prepared_size() ;
}
#endif

