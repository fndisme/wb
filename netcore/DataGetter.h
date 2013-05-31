/*
 * =====================================================================================
 *
 *       Filename:  DataGetter.h
 *
 *    Description:  
 *
 * =====================================================================================
 */
#ifndef FND_DATA_GETTER_H
#define FND_DATA_GETTER_H

#include <memory>
#include <deque>
#include <functional>
#include <type_traits>
#include <boost/noncopyable.hpp> 
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include "webgame/netcore/PoolBuffer.h"
#include "webgame/shared/identity_type.h"
#include "webgame/netcore/NetConnectionStorage.h"

namespace {
  template<typename T, typename NetConnection> void dummy(const T&, std::shared_ptr<NetConnection>) {}
}

namespace WebGame {
  namespace NetCore {
    template<typename NetConnection>
      class DataGetter : boost::noncopyable {
        public:
          typedef typename NetConnection::data_type block_type ;
          typedef typename NetConnection::NotLockType NotLockType ;
          typedef typename NetConnection::ActiveManageMessageType ActiveManageMessageType ;
          typedef std::deque<block_type> nc_data_block_deque_type ;
          typedef typename NetConnection::pointer net_connection_pointer ;
          typedef DataGetter<NetConnection> class_type ;
          typedef std::function<void(const block_type&, net_connection_pointer)> deal_message_type ;
          deal_message_type messageDealer;

          explicit DataGetter(
              std::shared_ptr<NetConnection> conn,
              size_t buffer_size,
              bool can_change_pool_size = true) ; 

          typedef std::shared_ptr<NetConnection> SystemConnectionPointer ;
          void start(SystemConnectionPointer) ;
          bool receiveAsyncMessage(block_type& type) ;

        private:
          boost::asio::ip::tcp::socket& m_socket ;
          boost::asio::strand& m_strand ;
          bool m_can_change_pool_size ;
          PoolBuffer<4098> m_pool_buffer ;
          nc_data_block_deque_type m_blocks ;
          block_type m_current_block ;
          bool hasStockMessage() const ;
          const block_type& headMessage() const ; 
          void popHeadStockMessage(); 
          void dealMessage(net_connection_pointer nc) ;
          size_t avaliableBytes() const { return m_pool_buffer.avaliableBytes() ;}
          bool importBody() ; 
          size_t bodySize() const ; 
          char* data() ; 
          size_t headerSize() const  ;
          bool importHeader() ; 
          HandleAllocator m_receive_allocator ;
          void setMaxBodySize(size_t size) ; 
          void initOrUninitDealMessage(const std::true_type&, net_connection_pointer nc) ; 
          void initOrUninitDealMessage(const std::false_type&, net_connection_pointer nc) ; 
          //void handle_receive_data_header(SystemConnectionPointer, const boost::system::error_code& error) ;
          void handleReceiveDataHeader(SystemConnectionPointer, const boost::system::error_code& error) ;
          void handleReceiveDataBody(SystemConnectionPointer, const boost::system::error_code& error) ;
      } ;
  }
}
#include "webgame/netcore/DataGetter_inl.h"
#endif
