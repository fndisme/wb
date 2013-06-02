/*
 * =====================================================================================
 *
 *       Filename:  make_cache_message.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-1 18:29:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_MAKECACHEMESSAGE_H
#define FND_WEBGAME_MAKECACHEMESSAGE_H
#include <cassert>
#include <functional>
#include <type_traits>
#include "webgame/message/DataCache.h"
#include "webgame/message/DataBlock.h"
#include "webgame/message/MessageUtility.h"
namespace WebGame {
  namespace Message {
    template<typename T>
      DataCache::const_pointer easyDataBlockCache(T&& msg,  player_tt pid)
      {
        static_assert(std::is_reference<T>::value ||
            std::is_rvalue_reference<decltype(msg)>::value, "need ref") ;
        static_assert(std::is_base_of< ::google::protobuf::Message,
            typename std::remove_const< typename std::remove_reference<T>::type>::type >::value  == true,
            "must be protobuf") ;

        return makeCached(std::forward<T>(msg), WebGame::Message::DataBlock::headerSize(), pid) ;
      }

    template<typename T>
      DataCache::const_pointer easySystemCache(T&& msg)
      {
        static_assert(std::is_reference<T>::value ||
            std::is_rvalue_reference<decltype(msg)>::value, "need ref") ;
        static_assert(std::is_base_of< ::google::protobuf::Message,
            typename std::remove_const< typename std::remove_reference<T>::type>::type >::value  == true,
            "must be protobuf") ;

        return makeCached(std::forward<T>(msg), WebGame::Message::DataBlock::headerSize(), player_tt(0)) ;
      }

    template<typename T>
      DataCache::const_pointer easyEmptyBody(player_tt id = player_tt(0))
      {
        return makeCached<T>(WebGame::Message::DataBlock::headerSize(), id) ;
      }
  }
}
#endif
