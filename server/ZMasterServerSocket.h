/*
 * =====================================================================================
 *
 *       Filename:  ZMasterServerSocket.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012年03月26日 13时08分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZMASTERSERVERSOCKET_H
#define FND_WEBGAME_ZMASTERSERVERSOCKET_H
#include <string>
#include <utility>
#include <algorithm>
#include <memory>
#include <boost/asio.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/noncopyable.hpp>
#include <pantheios/assert.h>
#include "webgame/server/ZSocketDef.h"
#include "webgame/server/ZSlaveDef.h"
#include "webgame/server/ZPollInManager.h"
//#include "webgame/server/ZSocketUtility.h"
#include "webgame/shared/identity_type.h"

namespace WebGame {
namespace Server {
template<typename SD,
         typename RD,
         typename C = std::vector<SD> >
class ZMasterServerSocket : boost::noncopyable {
public:
    typedef SD send_data_type ;
    typedef send_data_type CacheDataType ;
    typedef RD read_data_type ;
    typedef typename read_data_type::DecoderType DecoderType;
    typedef C container_type ;
    typedef ZMasterServerSocket<SD, RD, C> class_type ;
    typedef std::unique_ptr<ZMasterServerSocket<SD, RD, C> > pointer ;

    typedef std::function<void (const std::string& , std::shared_ptr<RD>)>
      MessageDealerFunctionType ;
    typedef boost::container::flat_map<SlaveServerNameType, container_type> MessageGroupType ;

    enum DirectionEnum {
        ZM_BOTH,
        ZM_RECEIVE
    } ;

    ZMasterServerSocket(
        boost::asio::strand& strand,
        QSocketTraits::context_t& ctx,
        const DecoderType& decoder,
        std::string const& publishaddress,
        std::string const& socketaddress,
        const ZSockOption& option = ZSockOption()) :
      m_strand(strand),
      m_decoder(decoder),
      m_publisher(new QSocketTraits::socket_t(ctx, QSocketTraits::typePub())),
      m_socket(new QSocketTraits::socket_t(ctx, QSocketTraits::typeRouter())),
      m_messages(),
      m_publishMessage(),
      m_HWM(option.HWM != 0 ? option.HWM : 1000) {

        init(publishaddress, socketaddress, option.LingerOption == NEED_LINGER) ;
      }

    ZMasterServerSocket(
        boost::asio::strand& strand,
        QSocketTraits::context_t& ctx,
        const DecoderType& decoder,
        std::string const& socketaddress,
        const ZSockOption& option = ZSockOption()) :
        m_strand(strand),
        m_decoder(decoder),
        m_socket(new QSocketTraits::socket_t(ctx, QSocketTraits::typeRouter())),
        m_HWM(option.HWM != 0 ? option.HWM : 1000) {
        init(std::string(), socketaddress, option.LingerOption == NEED_LINGER) ;

    }

    void sendMessage(const SlaveServerNameType& name, send_data_type msg) const {
        assert(sizeof(msg) <= 3 * sizeof(void *)) ;
        boost::lock_guard<boost::mutex> lock(m_mutex);
        m_messages[name].push_back(msg) ;
    }

    void sendMessage(const std::string& name, send_data_type msg) const {
        assert(sizeof(msg) <= 3 * sizeof(void *)) ;
        boost::lock_guard<boost::mutex> lock(m_mutex);
        m_messages[SlaveServerNameType(name)].push_back(msg) ;
    }


    void publishMessage(send_data_type msg) const {
        assert(sizeof(msg) <= 3 * sizeof(void *)) ;
        PANTHEIOS_ASSERT(m_publisher) ;
        boost::lock_guard<boost::mutex> lock(m_mutex);
        m_publishMessage.push_back(msg) ;
    }

    template<typename M>
    void sendMessage(const SlaveServerNameType& name,
                     M&& msg,
                     player_tt pid = player_tt(0)) const {
        sendMessage(name, easy_data_block_cache(msg, pid)) ;
    }

    template<typename M>
    void sendMessage(const std::string& name,
                     M&& msg,
                     player_tt pid = player_tt(0)) const {
        sendMessage(name, easy_data_block_cache(msg, pid)) ;
    }

    template<typename M>
    void publishMessage(M&& msg) const {
        publishMessage(easy_data_block_cache(msg, player_tt(0))) ;
    }

    void bindPollManager(ZPollInManager* mgr,
                              const MessageDealerFunctionType& func,
                              DirectionEnum direction = ZM_BOTH) {
      if(direction == ZM_BOTH) {
        mgr->registerWriteActor(std::bind(&class_type::sendToSlave, this)) ;
        if(m_publisher)
          mgr->registerWriteActor(std::bind(&class_type::sendPublishMessage, this)) ;
      }

      m_dealer_function = func ;
      mgr->registerReadActor(*m_socket, std::bind(&class_type::recv, this)) ;
    }

private:
    boost::asio::strand& m_strand;
    const DecoderType& m_decoder;
    ZSocketPointer m_publisher ;
    ZSocketPointer m_socket ;

    mutable MessageGroupType m_messages ;
    mutable container_type m_publishMessage ;

    MessageDealerFunctionType m_dealer_function ;
    const int m_HWM ; /// high water mark
    mutable boost::mutex m_mutex;

    void recv() {
        QSocketTraits::absorbHeaderDispatchMesage<read_data_type>(
            *m_socket,
            m_dealer_function,
            m_strand,
            m_decoder) ;
    }

    void sendPublishMessage() {
        PANTHEIOS_ASSERT(m_publisher) ;

      container_type data;
      {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        data.swap(m_publishMessage);
      }
        QSocketTraits::sendScatterMessage(data,
                *m_publisher, m_HWM) ;
    }

    void sendToSlave() {

      MessageGroupType messages;
      {
        boost::lock_guard<boost::mutex> lock(m_mutex);
        messages.swap(m_messages);
      }

      for(auto& v : messages) {
        if(v.second.empty()) continue;
        QSocketTraits::sendAllGroupMessage(v.second, v.first.get(),
                    *m_socket) ;
      }
    }

    void init(const std::string& publishaddress,
              const std::string& socketaddress,
              bool need_linger) {
      if(m_publisher)
        m_publisher->setsockopt(QSocketTraits::optionSetHighWaterMark(),
                                &(m_HWM), sizeof(m_HWM)) ;
      m_socket->setsockopt(QSocketTraits::optionSetHighWaterMark(),
                           &(m_HWM), sizeof(m_HWM)) ;


      if(m_publisher)
        m_publisher->bind(publishaddress.c_str()) ;

      m_socket->bind(socketaddress.c_str()) ;

      if(need_linger) {
        int linger = 0 ;
        if(m_publisher)
          m_publisher->setsockopt(QSocketTraits::optionLinger(),
                                  &linger, sizeof linger) ;
        m_socket->setsockopt(QSocketTraits::optionLinger(),
                             &linger, sizeof linger) ;

      }
    }
} ;
}
}


#endif
