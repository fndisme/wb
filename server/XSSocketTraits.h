/*
 * =====================================================================================
 *
 *       Filename:  XSSocketTraits.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年01月26日 17时30分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_XSSOCKETTRAITS_H
#define FND_WEBGAME_XSQSOCKETTRAITS_H
#include <memory>
#include <boost/bind.hpp>
#include <xs.hpp>
#include <pantheios/pantheios.hpp>
#include <pantheios/assert.h>
namespace WebGame
{
  namespace Server {
  namespace XSSocketTraits
  {
    typedef xs::socket_t socket_t ;
    typedef xs::context_t context_t ;
    typedef xs::message_t message_t ;
    typedef xs::pollitem_t pollitem_t ;
    constexpr int eventPollIn() {
      return XS_POLLIN ;
    }
    constexpr int optionIdentity() {
      return XS_IDENTITY ;
    }
    constexpr int optionLinger() {
      return XS_LINGER ;
    }
    constexpr int typeDealer() {
      return XS_DEALER ;
    }
    constexpr int typeSub() {
      return XS_SUB ;
    }
    constexpr int optionSubscribe() {
      return XS_SUBSCRIBE ;
    }
    constexpr int typePub() {
      return XS_PUB ;
    }
    constexpr int typeRouter() {
      return XS_ROUTER ;
    }
    constexpr int optionSetHighWaterMark() {
      return XS_SNDHWM ;
    }
    template<typename C>
      int poll(C& c, long timeout) {
        return xs::poll(&(c[0]), c.size(), timeout) ;
      }

    inline int wait(long timeout) {
      return xs::poll(nullptr, 0, timeout) ;
    }

    template<typename Container>
      void sendScatterMessage(Container&& container,
          socket_t& socket) {
        if(container.empty()) return ;
        std::for_each(container.cbegin(), container.cend(),
            [&socket](typename Container::const_reference v) {
            size_t sendsize = socket.send(v->data(), v->totalSize()) ; // we dont
            // set XS_DONTWAIT, SO no EAGAIN
            PANTHEIOS_ASSERT(sendsize == v->totalSize()) ;
            }) ;
      }
    template<typename Container>
      void sendAllGroupMessage(Container&& container,
          socket_t& socket) {
        PANTHEIOS_ASSERT(!container.empty()) ;
        auto iter = container.cbegin(), iter_end = container.cend() ;
        while(true) {
          auto oldpos = iter++ ;
          int sendmore = (iter == iter_end) ? 0 : XS_SNDMORE ;
          auto db = *oldpos;
          // we dont set ZMQ_DONTWAIT so no EAGAIN
          size_t sendsize = socket.send(static_cast<const void*>(db->data()),
              db->totalSize(), sendmore) ;
          PANTHEIOS_ASSERT(sendsize == db->totalSize()) ;
          if(!sendmore) break ;
        }
        PANTHEIOS_ASSERT(iter == iter_end) ;
      }

    template<typename D, typename Fun, typename Strand>
      void absorbHeaderDispatchMesage(socket_t& socket, const Fun& fun, Strand& s) {
        message_t headermsg ;
        bool status = socket.recv(&headermsg) ;
        if(!status)  {
          pantheios::log_WARNING("no receive header error ") ;
          return ;
        }
        std::string header(static_cast<const char*>(headermsg.data()),
            static_cast<const char*>(headermsg.data()) + headermsg.size()) ;
        int hasmore(0) ;
        size_t more_size = sizeof hasmore ;
        headermsg.getmsgopt(XS_MORE, &hasmore, &more_size) ;

        while(hasmore) {
          message_t msg ;
          status = socket.recv(&msg);
          PANTHEIOS_ASSERT(status) ;

          auto db = std::make_shared<D>();
          bool ok = db->importFromArray(static_cast<const void*>(msg.data()), msg.size()) ;
          if(ok)
            s.dispatch(boost::bind(fun, header, db));
          else {
            pantheios::log_WARNING("not parse db ok..... IGNORE") ;
          }

          msg.getmsgopt(XS_MORE, &hasmore, &more_size) ;

        }
      }

    template<typename D, typename Fun, typename Strand>
      void absorbAndDispatchMessage(socket_t& socket, Fun fun, Strand& strand) {
        while(true) {
          message_t msg ;
          bool status = socket.recv(&msg);

          if(!status) break ; // because bolock

          std::shared_ptr<D> db = std::make_shared<D>();
          bool ok = db->importFromArray(static_cast<const void*>(msg.data()), msg.size()) ;

          if(ok) {
            strand.dispatch([fun,db](){fun(db);});
          } else {
            pantheios::log_WARNING("absorb not valid message.... Ignore") ;
          }

          int has_more(0);
          size_t more_size = sizeof has_more ;
          msg.getmsgopt(XS_MORE, &has_more, &more_size) ;
          if(!has_more) break ;
        }
      }


    template<typename Container, typename Header>
      void sendAllGroupMessage(Container&& container,
          Header&& header,
          socket_t& socket) {
        // we not set ZMQ_DONTWAIT do no EAGAIN, if error throw exception
        size_t sendsize = socket.send(static_cast<const void*>(header.data()), header.size(), XS_SNDMORE) ;
        PANTHEIOS_ASSERT(sendsize == header.size()) ;
        sendAllGroupMessage(std::move(container), socket) ;
      }
  }
  }
}
#endif

