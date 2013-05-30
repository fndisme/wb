/*
 * =====================================================================================
 *
 *       Filename:  net_acceptor_property.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-10-27 14:42:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_NETCORE_ACCEPTOR_PROPERTY_H
#define FND_WEBGAME_NETCORE_ACCEPTOR_PROPERTY_H
#include	<boost/system/system_error.hpp>
#include	<functional>
namespace WebGame {
	struct NetAcceptorOption {
			bool IsAddressReused ;
			int SendBufferSize ;
			int ReceiveBufferSize ;
			int GetterCacheSize ;
			explicit NetAcceptorOption(
					int cache_size = 4096,
					int sendsize = 8192,
					int receivesize = 4096,
					bool reuse = true) : 
				IsAddressReused(reuse),
				SendBufferSize(sendsize),
				ReceiveBufferSize(receivesize),
				GetterCacheSize(cache_size) {}
	} ;
	template<typename NetConnection>
		struct net_acceptor_property {
			typedef NetConnection net_connection_type ;
			typedef std::function<bool (typename net_connection_type::pointer,
					const boost::system::error_code&)> handle_connection_function_type ;
			typedef std::function<void (typename net_connection_type::pointer)> 
				handle_connect_successed_function_type ;
			handle_connection_function_type HandleConnect ;
			handle_connect_successed_function_type HandleConnectSuccessed ;
			typedef typename net_connection_type::HandleErrorFunctionType handle_error_function_type ;
			handle_error_function_type HandleDataError ;
			typedef typename net_connection_type::HandleDataBlockFunctionType handle_data_block_function_type ;
			handle_data_block_function_type HandleData ;
			net_acceptor_property(const handle_connection_function_type& handle_conn,
					const handle_connect_successed_function_type& conn_succ,
					handle_error_function_type const& data_error,
					handle_data_block_function_type const& handle_data) :
				HandleConnect(handle_conn),
				HandleConnectSuccessed(conn_succ),
				HandleDataError(data_error),
				HandleData(handle_data) {}
		} ;
}
#endif

