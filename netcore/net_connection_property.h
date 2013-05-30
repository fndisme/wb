/*
 * =====================================================================================
 *
 *       Filename:  net_connection_property.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-11-9 13:22:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_NET_CONNECTION_PROPERTY_H
#define FND_NET_CONNECTION_PROPERTY_H
#include <string>
#include <functional>
#include <boost/system/system_error.hpp>
namespace WebGame {
	struct NetConnectionOption {
		std::string ServerAddress ;
		std::string Port ;
		size_t GetterBufferSize ;
		NetConnectionOption(const std::string& server_address,
				const std::string& port,
				size_t buffer = 4096L) :
			ServerAddress(server_address),
			Port(port),
			GetterBufferSize(buffer) {}
	} ;

	template<typename NetConnection>
		struct NetConnectionProperty {
			typedef NetConnection net_connection_type ;
			typedef typename net_connection_type::handle_error_function_type handle_error_function_type ;
			typedef typename net_connection_type::handle_data_block_function_type handle_data_block_function_type ;
			typedef typename net_connection_type::handle_async_connect_function_type handle_async_connect_function_type ;
			handle_error_function_type HandleError ;
			handle_data_block_function_type HandleData ;
			handle_async_connect_function_type HandleOk ;
			NetConnectionProperty(const handle_error_function_type& h_e,
					const handle_data_block_function_type& h_d,
					const handle_async_connect_function_type& h_o = handle_async_connect_function_type()) :
				HandleError(h_e),
				HandleData(h_d),
				HandleData(h_o) {}
		} ;
}
#endif
