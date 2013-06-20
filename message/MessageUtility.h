/*
 * =====================================================================================
 *
 *       Filename:  game_message_util.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011-11-8 10:17:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GAME_MESSAGE_UTIL_H
#define FND_WEBGAME_GAME_MESSAGE_UTIL_H
#include "webgame/shared/identity_type.h"
#include "webgame/message/DataBlock.h"

size_t messageBodySize(const ::google::protobuf::Message* const msg) ;
size_t messageBodySize(const ::google::protobuf::Message& msg) ;

size_t total_message_size(const WebGame::Message::DataBlock::header_type& header,
		const ::google::protobuf::Message* const msg) ;
void pack_cache_message(const WebGame::Message::DataBlock::header_type&,
		const ::google::protobuf::Message* msg,
		void* buffer,
		size_t buffer_size) ;
void make_cache_header(void* buffer, int type, size_t body_size, WebGame::player_tt id) ;
void make_cache_body(void* buffer, const ::google::protobuf::Message* msg, size_t buffer_size) ;



template<typename T>
void pack_cache_message(const T& msg, void* buffer, size_t buffer_size, WebGame::player_tt id) {
	assert(buffer_size >= ::WebGame::Message::DataBlock::headerSize() + msg.ByteSize())  ;
		auto body_size = msg.ByteSize() ;
		make_cache_header(buffer, T::value, body_size, id) ;
		make_cache_body(static_cast<void*>(static_cast<char*>(buffer) + WebGame::Message::DataBlock::headerSize()),
				&msg, body_size) ;
}

template<typename T>
void pack_EBO_body(void* buffer, size_t /* cache_size*/, WebGame::player_tt id, T* = 0) {
	assert(T::empty_body == 1) ;
	make_cache_header(buffer, T::value, 0, id) ;
}
#endif
