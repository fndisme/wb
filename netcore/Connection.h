#ifndef FND_GAME_WEB_GAME_NET_CONNECTION_H
#define FND_GAME_WEB_GAME_NET_CONNECTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif
#include	<cassert>
#include <string>
#include <map>
#include <functional>
#include	<memory>
#include	<type_traits>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/signals2.hpp>
#include <boost/random.hpp>
#include <fastformat/fastformat.hpp>
#include <pantheios/assert.h>
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include <pantheios/pan.hpp>
#include <pantheios/inserters/i.hpp>
#include <folly/Optional.h>

#include "webgame/netcore/DataGetter.h"
#include "webgame/netcore/DataSender.h"

#include "net_connection_storage.h"
#include "webgame/message/DataBlock.h"
#include "webgame/shared/identity_type.h"

// create connection easy for async
#include "net_connection_property.h"


namespace WebGame {
  namespace NetCore {

#ifdef  TRINITY_DEBUG
    class net_stream_infomation ;
#else      /* -----  not TRINITY_DEBUG  ----- */
#endif     /* -----  not TRINITY_DEBUG  ----- */
    namespace bs2 = boost::signals2;
    using namespace bs2::keywords;
    template<typename ConnectionTraits>
      class Connection : 
        public std::enable_shared_from_this<Connection<ConnectionTraits> > {
          public:
            typedef typename ConnectionTraits::DataType data_type ;
            typedef typename data_type::IdentityType IdentityType ;
            typedef typename ConnectionTraits::NotLockType NotLockType;
            typedef typename ConnectionTraits::ActiveManageMessageType ActiveManageMessageType ;
            typedef typename ConnectionTraits::NotDelayMessageType NotDelayMessageType ;
            typedef typename ConnectionTraits::ActiveSendHugeData ActiveSendHugeData ;
            typedef Connection<ConnectionTraits> class_type ;
            typedef std::shared_ptr<class_type> pointer ;
            typedef std::shared_ptr<const class_type > const_pointer ;
            typedef DataGetter<class_type> data_getter_type ;
            typedef std::shared_ptr<data_getter_type> data_getter_pointer ;
            enum CloseOption {
              normal = 0,
              send_all_message_and_quit = 1,
            } ;
            enum MessageOption {
              huge_message_mini_size = 4096,
            } ;


            Connection(class_type const&) = delete ;
            class_type& operator = (class_type const&) = delete ;


            typedef typename bs2::signal_type<void (const boost::system::error_code&,
                std::shared_ptr<class_type >), mutex_type<bs2::dummy_mutex> >::type 
              NetConnectSignalType ;
            //typedef boost::signals2::signal<void (const boost::system::error_code&,
            //			std::shared_ptr<class_type >)>
            typedef std::function<void (const boost::system::error_code&, pointer)>
              HandleErrorFunctionType ;
            typedef std::function<void (const data_type&, pointer)>
              HandleDataBlockFunctionType ;
            typedef std::function<void (pointer)>
              HandleAsyncConnectFunctionType ;
            /* --------------------------------------------------------------------------*/
            /**
             * @Synopsis  describe the remote connection
             *
             * @Param nc the connection to be described
             *
             * @Returns  string 
             */
            /* ----------------------------------------------------------------------------*/
            static std::string describeRemoteConnection(const_pointer nc) ;
            static std::string describeRemoteConnection(const class_type& nc) ;

            /* --------------------------------------------------------------------------*/
            /**
             * @Synopsis  help function to create a connection
             *
             * @Param io_service io service
             * @Param option contain the value of connection option
             * @Param property The callback functions when some event create 
             *
             * @Returns  connection. 
             */
            /* ----------------------------------------------------------------------------*/
            static
              pointer createAsyncConnection(boost::asio::io_service& io_service,
                  boost::asio::strand& read,
                  boost::asio::strand& write,
                  const NetConnectionOption& option,
                  const NetConnectionProperty<class_type>& property) ;
            static
              pointer createSyncConnection(boost::asio::io_service& io_service,
                  boost::asio::strand& read,
                  boost::asio::strand& write,
                  const NetConnectionOption& option,
                  const NetConnectionProperty<class_type>& property) ;
            Connection(boost::asio::io_service& io_service,
                boost::asio::strand& readStrand,
                boost::asio::strand& writeStrand,
                data_getter_pointer  getter = data_getter_pointer()) ;
            boost::asio::io_service& ioService() { return m_io_service ;}

            ~Connection() {
              //PANTHEIOS_MESSAGE_ASSERT(is_open(), "must be open....") ;
              m_socket.close() ;
            }

            typedef boost::asio::ip::tcp::socket SystemSocketType ;
            const SystemSocketType& socket() const {return m_socket ;}
            SystemSocketType& socket() {return m_socket ;}
            void sendAsyncMessage(const data_type& db) ;
            void sendAsyncMessage(data_type& db) { sendAsyncMessage(static_cast<const data_type&>(db)) ;}
            template<typename ND>
              void sendAsyncMessage(ND&& msg) {
                sendAsyncMessage(std::forward<ND>(msg), data_type::system_identity()) ;
              }

            template<typename ND>
              void sendAsyncMessage(ND&& msg, typename data_type::IdentityType id) {
                sendAsyncMessage(easy_data_block_cache(std::forward<ND>(msg), id)) ;
              }
            void sendAsyncMessage(Message::DataCache::const_pointer cache) ;
            void sendAsyncMessage(IdentityType pid, const data_type& db) ;
            template<typename DD>
              void sendAsyncMessage(std::shared_ptr<DD> msg) {
                data_type db(msg) ;
                sendAsyncMessage(db) ;
              }
            template<typename DD>
              void sendAsyncMessage(IdentityType pid, std::shared_ptr<DD> msg) {
                data_type db(msg, pid) ;
                sendAsyncMessage(db) ;
              }
            template<typename DD>
              void sendAsyncMessage(IdentityType pid, std::unique_ptr<DD> msg) {
                data_type db(std::move(msg), pid) ;
                sendAsyncMessage(db) ;
              }
            template<typename DD>
              void sendAsyncMessage(std::unique_ptr<DD>&& msg) {
                data_type db(std::move(msg)) ;
                sendAsyncMessage(db) ;
              }
            /**
             * @brief describe socket remote address
             *        if the socket is not valid, exception will throw
             *
             * @return remote address string....
             */
            inline
              std::string describeRemoteAddress() const {
                return socket().remote_endpoint().address().to_string() ;
              }

            inline unsigned short remotePort() const {
              return socket().remote_endpoint().port() ;
            }
            bool receiveAsyncMessage(data_type& db) ;

            void start() {
              m_getter->start(this->shared_from_this()) ;
              //start_receive_message() ;
            }
            void flush() ;
            void setSendBufferSize(size_t new_size) {
              boost::asio::socket_base::send_buffer_size option(new_size);
              socket().set_option(option);
            }
            void setReceiveBufferSize(size_t new_size) {
              boost::asio::socket_base::receive_buffer_size option2(new_size) ;
              socket().set_option(option2) ;
            }
            void startAsyncConnect(const std::string& address,
                const std::string& port, boost::system::error_code& error ) ;
            void syncSendMessage(const data_type& db) {
              writeSyncMessage(m_socket,db) ;
            }
            void syncReceiveMessage(data_type& db) {
              readSyncMessage(m_socket,db) ;
            }
            void startAsyncConnect(const std::string& address, const std::string& port) ;
            bool isOpen() const {return m_need_handle_error && m_socket.is_open() ;}
            void setCloseOption(CloseOption option) ;
            void shutdown(boost::asio::ip::tcp::socket::shutdown_type sd) {
              m_socket.shutdown(sd) ;
            }
            /**
             * @brief when socket error and need remove the resource call it
             *
             * @param error why the socket is error
             */
            void onError(const boost::system::error_code& error =
                boost::system::error_code()) {
              if(needHandlerError()) {
                m_need_handle_error = false ;
                boost::system::error_code handler_error ;
                m_socket.cancel(handler_error) ;
                if(handler_error) {
                  pantheios::log_WARNING("Socket second error :", handler_error.message()) ;
                }
                disconnect(error) ;
              }
            }

            bool needHandlerError() const {
              return m_need_handle_error ;
            }
            void closeSocket() {
              PANTHEIOS_MESSAGE_ASSERT(this->isOpen(), "must open and close....") ;
              m_socket.close() ;
            }
            void resetGetter(data_getter_pointer&& getter)
            { m_getter = std::move(getter) ;}

            size_t availableBytes() const {return socket().available() ;}
            HandleAsyncConnectFunctionType asyncConnect;
            mutable NetConnectSignalType handleError;
            boost::asio::strand& readStrand() { return m_readStrand;}
            boost::asio::strand& writeStrand() { return m_writeStrand;}
            void disconnect(const boost::system::error_code& error) ;
            //bool is_heart_ok() const { return m_heart_state == HB_NORMAL ;}
            bool isNeedHeartBeat() const { return m_heart_state == HB_SEND ;}
            bool isHeartDead() const { return m_heart_state == HB_DEAD ;}
            void decreaseHeartLevel() { if(m_heart_state != HB_DEAD) m_heart_state ++ ;}
            void increaseHeartLevel() { if(m_heart_state != HB_STRONG) m_heart_state -- ;}
            typedef folly::Optional<int64_t> Variant ;
            void variant(int64_t value) { m_value = value ; }
            bool hasVariant() const { return m_value.hasValue() ;}
            const Variant& variant() const {  return m_value ;}
            void eraseVariant() {m_value.clear() ;}
          private:
            boost::asio::io_service& m_io_service ;
            bool m_need_handle_error ;
            boost::asio::strand& m_readStrand;
            boost::asio::strand& m_writeStrand;
            DataSender<class_type>  m_sender ;
            data_getter_pointer m_getter ;
            SystemSocketType m_socket ;
            CloseOption m_close_option ;
            handle_allocator m_send_allocator ;
            void handleSendData(const boost::system::error_code& error) ;
            void handleAsyncConnect(const boost::system::error_code& error,
                boost::asio::ip::tcp::resolver::iterator iterator) ;
            void doFlush() {
              if(m_sender.flush()) realSendInformation() ;
            }
            void realSendInformation() ;
            void poolSendInformation(const data_type& db) {
              m_sender.pack_send_message(db) ;
            }

            enum HeartBeatState {
              HB_STRONG,
              HB_NORMAL,
              HB_SEND,
              HB_DEAD
            } ;

            int m_heart_state ;
            Variant m_value ;
        } ;
  }
}


#include	"webgame/netcore/ConnectionInl.h"

#endif
