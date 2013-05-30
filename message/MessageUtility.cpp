/*
 * =====================================================================================
 *
 *       Filename:  game_message_util.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-8 10:22:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */

#include	"webgame/message/MessageUtility.h"
#include <pantheios/assert.h>
size_t message_body_size(const ::google::protobuf::Message* const msg) {
	return msg ? msg->ByteSize() : 0 ;
}
size_t message_body_size(const ::google::protobuf::Message& msg) {
	return  msg.ByteSize() ;
}

size_t total_message_size(const data_exchange::header& header,
		const ::google::protobuf::Message* const msg) {
	return header.ByteSize() + message_body_size(msg) ;
}

void pack_cache_message(const data_exchange::header& header,
		const ::google::protobuf::Message* msg,
		void* buffer,
		size_t buffer_size) {
	PANTHEIOS_ASSERT(buffer) ;
	PANTHEIOS_ASSERT(total_message_size(header, msg) <= buffer_size) ;
	auto header_size = header.ByteSize() ;
	auto ok = header.SerializeToArray(buffer, header_size) ;
	PANTHEIOS_ASSERT(ok) ;
	if(msg) {
	ok = msg->SerializeToArray(static_cast<void*>(static_cast<char*>(buffer) + header_size),
			buffer_size - header_size) ;
	PANTHEIOS_ASSERT(ok) ;
	}
}

void make_cache_body(void* buffer, const ::google::protobuf::Message* msg, size_t bodysize) {
	PANTHEIOS_ASSERT(msg) ;
	bool ok = msg->SerializeToArray(buffer, bodysize) ;
	PANTHEIOS_ASSERT(ok) ;
}

void make_cache_header(void* buffer, int message_type, size_t body_size, WebGame::player_tt id) {
	data_exchange::header header ;
	header.set_id(id.base_type_value()) ;
	header.set_type(message_type) ;
	header.set_size(body_size) ;
	header.SerializeToArray(buffer, header.ByteSize()) ;
}
