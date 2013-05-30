#ifndef FND_GAME_WEB_GAME_NET_ACCETOR_H
#define FND_GAME_WEB_GAME_NET_ACCETOR_H
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif
#include <algorithm>
#include <functional>
#include	<type_traits>
#include <boost/bind.hpp>
#include <pantheios/pantheios.hpp>
#include <boost/container/set.hpp>
#include <boost/system/system_error.hpp>
#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include	"net_acceptor_property.h"
#include "webgame/message/DataCache.h"


namespace WebGame {
  namespace NetCore {

  template<typename NetConnection>
    class Acceptor {
      public:
        typedef typename NetConnection::data_type data_type ;
        typedef typename NetConnection::NotLockType NotLockType ;
        typedef NetConnection net_connection_type ;
        typedef std::shared_ptr<net_connection_type > nc_pointer_type ;
        typedef nc_pointer_type value_type ;
        typedef std::function<bool (nc_pointer_type, const boost::system::error_code&)>
          net_acceptor_connect_function_type ;
        typedef std::function<void (nc_pointer_type)> net_acceptor_connect_successed_function_type ;
        typedef Acceptor<NetConnection> class_type ;
        typedef std::unique_ptr<class_type> pointer ;
        typedef net_acceptor_property<NetConnection> NetAcceptorProperty ;
        static pointer create(boost::asio::strand& readStrand,
            boost::asio::strand& writeStrand,
            int port,
            const NetAcceptorProperty& p,
            const NetAcceptorOption& option = NetAcceptorOption()) ;
        void  asyncConnect() ;
        template<typename T>
          void postMessage(std::shared_ptr<T> msg) const {
            data_type db ;
            db.setBody(msg);
            postMessage(db) ;
          }
        typedef std::function<void (nc_pointer_type)> EventFunc ;

        class_type& operator = (class_type const&) = delete ;
        Acceptor(class_type const&) = delete ;


        void processInplaceAction(EventFunc func) {
          std::for_each(m_connections.begin(), m_connections.end(), func) ;
        }

        template<typename Cond, typename Fun>
          void processAction(Cond con, Fun fun) {
            typedef std::vector<value_type> nc_group_type ;
            nc_group_type groups;
            std::copy_if(m_connections.begin(), m_connections.end(),
                std::back_inserter(groups),
                con) ;
            std::for_each(groups.begin(), groups.end(), fun) ;
          }
        template<typename T>
          void postMessage(int id, std::shared_ptr<T> msg) const {
            data_type db ;
            db.setHeaderId(id) ;
            db.setBody(msg) ;
            postMessage(db) ;
          }
        void postMessage(Message::DataCache::const_pointer db) const ;
        void postMessage(const data_type& db) const ;
        void postMessageExcept(Message::DataCache::const_pointer db, nc_pointer_type nc) const ;
        void postMessageExcept(const data_type& db,nc_pointer_type nc) const ;
        void stopAll() ;
        size_t connectionSize() const ;
        int sendBufferSize() ;
        void setSendBufferSize(int newsize) ;
        int receiveBufferSize() ;
        void setReceiveBufferSize(int newsize) ;
      private:

        // timer event
        boost::asio::strand& m_readStrand;
        boost::asio::strand& m_writeStrand;
        typedef boost::container::set<nc_pointer_type> connection_container_type ;
        connection_container_type m_connections ;
        nc_pointer_type m_current_conection ;
        typename net_connection_type::HandleDataBlockFunctionType messageCallback;
        typename net_connection_type::HandleErrorFunctionType errorCallback;
        net_acceptor_connect_function_type checkCallback;
        net_acceptor_connect_successed_function_type successedCallback;
        int m_port ;
        boost::asio::ip::tcp::acceptor m_acceptor ;

        // handles
        void handleNewConnection(const boost::system::error_code& error) ;
        void doPostMessage(const data_type& db) const ;
        void doPostMessageExcept(const data_type& db, nc_pointer_type nc) const ;
        void doPostMessage(Message::DataCache::const_pointer) const ;
        void doPostMessageExcept(Message::DataCache::const_pointer, nc_pointer_type nc) const ;

        void removeConnection(const boost::system::error_code& e, nc_pointer_type nc) ;
        // for thread safe...

        void start(const NetAcceptorProperty& prop, const NetAcceptorOption& option) ;
        Acceptor(boost::asio::strand& readStrand, 
            boost::asio::strand& writeStrand, int port) ;
        int m_data_getter_cache_size ;
        void stopAccpetNewConnection() ;
    } ;
  }
}
#include	"webgame/netcore/AcceptorInl.h"

#endif
