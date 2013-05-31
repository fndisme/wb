/*
 * =====================================================================================
 *
 *       Filename:  ZPollInManager.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-2-2 17:49:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_ZPOOLINMANAGER_H
#define FND_WEBGAME_ZPOOLINMANAGER_H
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <pantheios/pantheios.hpp>
#include <pantheios/assert.h>

#include "ZSocketDef.h"
namespace WebGame {
  namespace Server {
  class ZPollInManager : boost::noncopyable {
    public:
      typedef std::function<void ()> ActionFunctionType ;
      enum OrderType {
        OT_DELAYED,
        OT_FRONT
      } ;
      void registerWriteActor(const ActionFunctionType& fun, OrderType order = OT_DELAYED) {
        if(order == OT_DELAYED)
          m_absolute_functions.push_back(fun) ;
        else m_fronter_functions.push_back(fun) ;
      }

      void registerReadActor(void* socket, const ActionFunctionType& fun) {
        //xs_pollitem_t item ;
        QSocketTratis::pollitem_t item ;
        item.socket = socket ;
        //item.events = XS_POLLIN ;
        item.events = QSocketTratis::eventPollIn();
        item.revents = 0 ;
        m_pollers.push_back(item) ;
        m_functions.push_back(fun) ;
      }
      int pollOne(int ms) {
        int rc = 0 ;
        for(auto& v : m_fronter_functions) v() ;
        if(!m_pollers.empty())  {
          rc = QSocketTratis::poll(m_pollers, ms) ;

          //rc = zmq::poll(&(m_pollers[0]), m_pollers.size(), ms) ;
          if(rc != 0) {
            for(size_t i = 0, size = m_pollers.size() ; i < size ; ++i) {
              if(m_pollers[i].revents & QSocketTratis::eventPollIn()) {
                m_functions[i]() ;
              }
            }
          }
        } else {
          //xs::poll(nullptr, 0, ms) ;
          //zmq::poll(nullptr, 0, ms) ;
          QSocketTratis::wait(ms) ;
        }

        for(auto& v : m_absolute_functions) v() ;
        return rc ;

      }
      void poll(int ms = 1) {
        PANTHEIOS_ASSERT(boost::this_thread::get_id() == m_threadId);
        while(pollOne(ms) > 0) {
        }
      }

      int eventPoll(int ms = 1) {
        int events = 0 ;
        while(true) {
          int size = pollOne(ms) ;
          if(size == 0) return events ;
          events += size ;
        }
        return events ;
      }

      explicit ZPollInManager(const boost::thread::id& id) :
        m_pollers(),
        m_functions(),
        m_absolute_functions(),
        m_fronter_functions(),
        m_threadId(id)
      {}
    private:
      //typedef std::vector<xs::pollitem_t> PollGroupType ;
      typedef std::vector<QSocketTratis::pollitem_t> PollGroupType ;
      PollGroupType m_pollers ;
      typedef std::vector<ActionFunctionType> ActorGroupType ;
      ActorGroupType m_functions ;
      ActorGroupType m_absolute_functions ;
      ActorGroupType m_fronter_functions ;
      boost::thread::id m_threadId;
      //ZPollInManager(const ZPollInManager&) = delete ;
      //ZPollInManager& operator = (ZPollInManager const&) = delete ;
  } ;
  }
}
#endif
