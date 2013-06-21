/*
 * =====================================================================================
 *
 *       Filename:  dummy_client.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011-9-2 13:38:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *        Company:
 *
 * =====================================================================================
 */
#ifndef FND_DUMMY_CLIENT_H
#define FND_DUMMY_CLIENT_H
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>
#include <stlsoft/memory/auto_buffer.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <deque>
#include <vector>
#include <map>
#include "webgame/message/DataBlock.h"
#include "webgame/netcore/Connection.h"
#include "webgame/utility/MessageManager.h"
#include "webgame/netcore/DefaultNetConnectionDef.h"
#include	"webgame/netcore/TimerEventFwd.h"
namespace WebGame {
  namespace Mock {
    class DummyClient : boost::noncopyable {
      public:
        typedef WebGame::NetCore::DefaultNetConnectType ConnectionType;
        typedef ConnectionType::DecoderType DecoderType;
        void run() ;
        DummyClient(boost::asio::io_service&,
            boost::asio::strand& readStrand,
            boost::asio::strand& writeStrand,
            const std::string& init_file, player_tt id,
            boost::mutex& mutex,
            const DecoderType& decoder
            ) ;
        virtual ~DummyClient();
        void parse_cmd() ;
        void start() ;
        void update() ;
        void outside_command(const std::string& cmd) ;
      protected:
        typedef std::tuple<const ConnectionType::data_type&,
                ConnectionType::pointer>& message_handler_parameter_type ;
        typedef WebGame::Utility::MessageManager<int,
                message_handler_parameter_type> message_handler_type ;

        template<typename Func>
            void addHandler(int v, Func f) {
                m_message_handler.add(v, f) ;
            }
      private:
        boost::asio::io_service& m_io_service ;
        boost::mutex& m_mutex ;
        ConnectionType::pointer m_loginer ;
        ConnectionType::pointer m_connection ;
        ConnectionType::pointer m_unity_connection ;
        ConnectionType::pointer m_db_connection ;
        player_tt m_id ;
        bool handle_parse_message(const std::string&,
            const std::vector<std::string>&, WebGame::Message::DataBlock& db, int&) ;
        bool parse_message(WebGame::Message::DataBlock& db, const std::string& msg, int&) ;
        void handle_server_data(const ConnectionType::data_type& db,
            ConnectionType::pointer nc) ;
        void init_unity_handlers() ;
        void handle_server_db_data(const ConnectionType::data_type& db,
            ConnectionType::pointer nc) ;
        void handle_server_unity_data(const ConnectionType::data_type& db,
            ConnectionType::pointer nc) ;
        void handle_server_error(const boost::system::error_code&,
            ConnectionType::pointer nc) ;
        message_handler_type m_message_handler ;
        message_handler_type m_unity_handler ;
        NetCore::TimerEventPonter m_heart_beat_timer ;
        void deal_with_client_net_property(message_handler_parameter_type) ;
        void deal_HeartBeat(message_handler_parameter_type) const;
        void handle_heart_beat() ;
        void init_flash_handlers() ;
        void init_property(const std::string& file_name) ;
        void initNetContex() ;
        void handle_login_result(message_handler_parameter_type) ;
        std::string m_server_address;
        std::string m_port;
        virtual void doInitHandler() {}

        virtual bool doParse(const std::string&,
            const std::vector<std::string>&, WebGame::Message::DataBlock& db, int&) {return false;}

    } ;
  }
}
#endif
