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
#include	<type_traits>
#include	"DataCache.h"
#include	"game_message.h"
#include	"game_message_util.h"
namespace WebGame
{
template<typename T>
DataCache::const_pointer easy_data_block_cache(T&& msg,  player_tt pid)
{
    static_assert(std::is_reference<T>::value ||
                  std::is_rvalue_reference<decltype(msg)>::value, "need ref") ;
    static_assert(std::is_base_of< ::google::protobuf::Message,
                  typename std::remove_const< typename std::remove_reference<T>::type>::type >::value  == true,
                  "must be protobuf") ;

    return make_cached(std::forward<T>(msg), Fnd::data_block::header_size(), pid) ;
}

template<typename T>
DataCache::const_pointer easy_system_cache(T&& msg)
{
    static_assert(std::is_reference<T>::value ||
                  std::is_rvalue_reference<decltype(msg)>::value, "need ref") ;
    static_assert(std::is_base_of< ::google::protobuf::Message,
                  typename std::remove_const< typename std::remove_reference<T>::type>::type >::value  == true,
                  "must be protobuf") ;


    return make_cached(std::forward<T>(msg), Fnd::data_block::header_size(), player_tt(0)) ;
}

template<typename T>
DataCache::const_pointer easy_empty_body(player_tt id = player_tt(0))
{
    return make_cached<T>(Fnd::data_block::header_size(), id) ;
}
}
#endif
