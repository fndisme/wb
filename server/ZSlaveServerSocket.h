/*
 * =====================================================================================
 *
 *       Filename:  ZSlaveServerSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012年03月26日 10时16分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZSLAVESERVERSOCKET_H
#define FND_WEBGAME_ZSLAVESERVERSOCKET_H
#include <utility>
#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/lock_guard.hpp>
#include <pantheios/assert.h>
#include "webgame/message/MakeCacheMessage.h"
#include "webgame/server/ZSocketDef.h"
#include "webgame/server/ZPollInManager.h"

namespace WebGame {
  namespace Server {
    template<typename SD,
      typename RD,
      typename C = std::vector<SD> >
        class ZSlaveServerSocket : boost::noncopyable {
          public:
            typedef SD send_data_type ;
            typedef RD read_data_type ;
            typedef C container_type ;
            typedef typename RD::DecoderType DecoderType;
            typedef ZSlaveServerSocket<SD, RD, C> class_type ;
            typedef std::unique_ptr<ZSlaveServerSocket<SD, RD, C> > pointer ;

            typedef boost::function<void (std::shared_ptr<RD>)> MessageDealerFunctionType ;

            ZSlaveServerSocket(
                QSocketTraits::context_t& ctx,
                const DecoderType& decoder,
                std::string const& name,
                std::string const& subaddress,
                std::string const& socketaddress,
                NeedLingerOption nl = NEED_LINGER,
                std::string const& default_filter = "") :
              m_strand(nullptr),
              m_decoder(decoder),
              m_subscriber(new QSocketTraits::socket_t(ctx, QSocketTraits::typeSub())),
              m_socket(new QSocketTraits::socket_t(ctx, QSocketTraits::typeDealer())),
              m_name(name),
              m_send_data(),
              m_dealer_function(),
              m_subscriber_function(),
              m_HWM(1000) {
                init(socketaddress, subaddress, nl == NEED_LINGER, default_filter) ;
              }

            ZSlaveServerSocket(
                boost::asio::strand& strand,
                QSocketTraits::context_t& ctx,
                const DecoderType& decoder,
                std::string const& name,
                std::string const& subaddress,
                std::string const& socketaddress,
                NeedLingerOption nl = NEED_LINGER,
                std::string const& default_filter = "") :
              m_strand(&strand),
              m_decoder(decoder),
              m_subscriber(new QSocketTraits::socket_t(ctx, QSocketTraits::typeSub())),
              m_socket(new QSocketTraits::socket_t(ctx, QSocketTraits::typeDealer())),
              m_name(name),
              m_send_data(),
              m_dealer_function(),
              m_subscriber_function(),
              m_HWM(1000) {
                init(socketaddress, subaddress, nl == NEED_LINGER, default_filter) ;
              }
            ZSlaveServerSocket(
                QSocketTraits::context_t& ctx,
                const DecoderType& decoder,
                std::string const& name,
                std::string const& socketaddress,
                NeedLingerOption nl = NEED_LINGER) :
              m_strand(nullptr),
              m_decoder(decoder),
              m_socket(new QSocketTraits::socket_t(ctx, QSocketTraits::typeDealer())),
              //m_socket(new socket_t(ctx, XS_DEALER)),
              m_name(name),
              m_HWM(1000) {
                init(socketaddress, std::string(), nl == NEED_LINGER, std::string()) ;
              }
            ZSlaveServerSocket(
                boost::asio::strand& strand,
                QSocketTraits::context_t& ctx,
                const DecoderType& decoder,
                std::string const& name,
                std::string const& socketaddress,
                NeedLingerOption nl = NEED_LINGER) :
              m_strand(&strand),
              m_decoder(decoder),
              m_socket(new QSocketTraits::socket_t(ctx, QSocketTraits::typeDealer())),
              //m_socket(new socket_t(ctx, XS_DEALER)),
              m_name(name),
              m_HWM(1000) {
                init(socketaddress, std::string(), nl == NEED_LINGER, std::string()) ;
              }

            ~ZSlaveServerSocket() {}

            void sendMessage(send_data_type d) const {
              boost::lock_guard<boost::mutex> lock(m_mutex);
              m_send_data.push_back(d) ;
            }

            bool is_busy() const {
              boost::lock_guard<boost::mutex> lock(m_mutex);
              return !m_send_data.empty() ;
            }

            template<typename M>
              void sendMessage(M&& msg, player_tt pid = player_tt(0)) const {
                sendMessage(::WebGame::Message::easyDataBlockCache(std::forward<M>(msg), pid)) ;
              }

            void bindPollManager(ZPollInManager* mgr, MessageDealerFunctionType const& func_d,
                MessageDealerFunctionType const& func_s) {
              m_dealer_function = func_d ;
              m_subscriber_function = func_s ;

              mgr->registerWriteActor(std::bind(&class_type::send, this)) ;
              if(m_strand)
                  mgr->registerReadActor(*m_socket, std::bind(&class_type::recv, this)) ;
              else
                  mgr->registerReadActor(*m_socket, std::bind(&class_type::recvNoStrand, this));
              if(m_subscriber)
                mgr->registerReadActor(*m_subscriber, std::bind(&class_type::recvSubscribeMessage, this)) ;
            }

            void bindPollManager(ZPollInManager* mgr,
                MessageDealerFunctionType const& func_d) {
              m_dealer_function = func_d ;
              mgr->registerWriteActor(std::bind(&class_type::send, this)) ;
              if(m_strand)
                  mgr->registerReadActor(*m_socket, std::bind(&class_type::recv, this)) ;
              else
                  mgr->registerReadActor(*m_socket, std::bind(&class_type::recvNoStrand, this));
              assert(!m_subscriber) ;

            }

            void bindPollManager(ZPollInManager* mgr) {
              mgr->registerWriteActor(std::bind(&class_type::send, this)) ;
            }

          private:
            boost::asio::strand* m_strand;
            const DecoderType& m_decoder;
            ZSocketPointer m_subscriber ;
            ZSocketPointer m_socket;
            const std::string m_name ;
            mutable C m_send_data ;
            MessageDealerFunctionType m_dealer_function ;
            MessageDealerFunctionType m_subscriber_function ;
            const int m_HWM ;
            mutable boost::mutex m_mutex;

            void send() {
              C data;
              {
                boost::lock_guard<boost::mutex> lock(m_mutex);
                data.swap(m_send_data);
              }
              if(!data.empty())
                QSocketTraits::sendAllGroupMessage(std::move(data), *m_socket) ;

            }

            void recv() {
              QSocketTraits::absorbAndDispatchMessage<read_data_type>(
                  *m_socket, m_dealer_function, *m_strand, m_decoder) ;
            }

            void recvNoStrand() {
                QSocketTraits::absorbAndDispatchMessage<read_data_type>(
                  *m_socket, m_dealer_function, m_decoder) ;
            }

            void recvSubscribeMessage() {
              PANTHEIOS_ASSERT(m_subscriber) ;
              QSocketTraits::absorbAndDispatchMessage<read_data_type>(
                  *m_subscriber, m_subscriber_function, *m_strand, m_decoder) ;
            }

            void init(const std::string& socketaddress,
                const std::string& subaddress,
                bool need_linger,
                const std::string& default_filter) {
              if(need_linger) {
                int linger = 0 ;
                if(m_subscriber)
                  m_subscriber->setsockopt(QSocketTraits::optionLinger(), &linger, sizeof linger) ;
                m_socket->setsockopt(QSocketTraits::optionLinger(), &linger, sizeof linger) ;
              }

              if(m_subscriber) {
                m_subscriber->setsockopt(QSocketTraits::optionSubscribe(),
                    default_filter.data(),
                    default_filter.size()) ;
                m_subscriber->connect(subaddress.c_str()) ;
              }

              m_socket->setsockopt(QSocketTraits::optionIdentity(), m_name.c_str(), m_name.size()) ;
              m_socket->connect(socketaddress.c_str()) ;
            }
        } ;
  }
}
#endif
