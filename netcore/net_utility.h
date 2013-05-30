#ifndef FND_NET_UTILITY_H
#define FND_NET_UTILITY_H
#include <memory>
#include <boost/asio.hpp>
#include "webgame/message/DataBlockFwd.h"
//#include "net_connection.h"
namespace WebGame {
	bool read_a_sync_message(boost::asio::ip::tcp::socket&,
			Message::DataBlock&) ;
	bool read_a_sync_message(boost::asio::ip::tcp::socket&,
			Message::DataBlock&,
			boost::system::error_code&) ;
	bool write_a_sync_message(boost::asio::ip::tcp::socket&,
			const Message::DataBlock&,
			const char* buffer,
			size_t max_buffer_size) ;
	bool write_a_sync_message(boost::asio::ip::tcp::socket&,
			const Message::DataBlock&,
			const char* buffer,
			size_t max_buffer_size,
			boost::system::error_code&) ;
}
#endif
