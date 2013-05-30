/*
 * =====================================================================================
 *
 *       Filename:  FlowControler.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月02日 16时55分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_FLOWCONTROLER_H
#define FND_WEBGAME_FLOWCONTROLER_H
#include <algorithm>
#include <memory>
#include <queue>
#include <tuple>
#include <boost/container/deque.hpp>
#include "get_pointer.h"
#include "DataCache.h"

namespace WebGame {
  template<typename NetConnection> 
    class FlowControler {
      enum FlowState {
        FS_BUSY,
        FS_LOOSE
      } ;
      public:
        typedef typename NetConnection::data_type data_type ;
        typedef std::shared_ptr<NetConnection> pointer_type ;
        typedef std::weak_ptr<NetConnection> weak_pointer_type ;
        typedef FlowControler<NetConnection> class_type ;

        void make_message_delay(pointer_type nc, DataCache::const_pointer cache) {
          m_send_informations.push_back(std::make_tuple(nc, cache)) ;

        }
        void make_message_delay(pointer_type nc, const data_type& db) {
          make_message_delay(nc, make_cached(db)) ;
        }

        void net_busy() { m_state = FS_BUSY ;}
        void net_loose() { m_state = FS_LOOSE ;}
        void busy_size(size_t s) { m_busy_size = s ;}
        void poll() ;
        void flow_size(size_t s) { m_flow_size = s ;}
        size_t size() const { return m_send_informations.size() ;}
        FlowControler() :
          m_send_informations{},
          m_flow_size(1000),
          m_state(FS_LOOSE),
          m_busy_size(500){}
      private:
        typedef std::tuple<weak_pointer_type, DataCache::const_pointer> SenderPair ;
        typedef boost::container::deque<SenderPair> SendGroup ;

        FlowControler(class_type const&) = delete ;
        class_type& operator = (class_type const&) = delete ;

        SendGroup m_send_informations ;
        size_t m_flow_size ;
        FlowState m_state ;
        size_t m_busy_size ;
        void send_and_pop_front_message() ;
    } ;

  template<typename NetConnection>
    void FlowControler<NetConnection>::send_and_pop_front_message() {
      weak_pointer_type wnc ;
      DataCache::const_pointer cache ;
      std::tie(wnc, cache) = m_send_informations.front() ;
      if(auto nc = wnc.lock()) {
        nc->send_async_message(cache) ;
      }
      m_send_informations.pop() ;
    }

  template<typename NetConnection>
    void FlowControler<NetConnection>::poll() {
      size_t max_send_size = (m_state == FS_LOOSE ? m_flow_size : m_busy_size) ;
      max_send_size = std::min(max_send_size, size()) ;
      if(max_send_size != 0) {
        weak_pointer_type wnc ;
        DataCache::const_pointer cache ;
        auto iter = m_send_informations.begin(), iter_end = m_send_informations.begin() + max_send_size ;
        std::for_each(iter, iter_end, [](SenderPair& sendinfo) {
            if(auto nc = std::get<0>(sendinfo).lock()) {
            nc->send_async_message(std::get<1>(sendinfo)) ;
            }
            }) ;
        m_send_informations.erase(iter, iter_end) ;

      }
    }
}
#endif
