/*
 * =====================================================================================
 *
 *       Filename:  CircleActor.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月15日 10时21分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_CIRCLEACTOR_H
#define FND_WEBGAME_CIRCLEACTOR_H
//#include <iostream>
#include <pantheios/assert.h>
#include <memory>
#include <boost/circular_buffer.hpp>
namespace WebGame {
  namespace Utility {
  template<typename T>
    class CircleActor {
      public:
        template<typename Act>
          void addAction(size_t position, Act&& act) {
            PANTHEIOS_ASSERT(hasPosition(position)) ;
            PANTHEIOS_ASSERT(isCanAdd(position)) ;
            m_actions[position]->addDealer(std::forward<Act>(act)) ;
          }
        template<typename Act>
          void add_absolute_action(size_t position, Act&& act) {
            PANTHEIOS_ASSERT(hasPosition(position)) ;
            //assert(is_can_add_action()) ;
            m_actions[position]->add_dealer(std::forward<Act>(act)) ;
          }

        bool isCanAdd(size_t position = 0) const { return position != 0 || m_can_add_action ;}
        void lock() { m_can_add_action = false ;}
        void unlock() { m_can_add_action = true ;}
        void action() {
          m_actions.emplace_back(new T) ;
        }
        explicit CircleActor(size_t maxsize) :
          m_actions(maxsize) {
            for(size_t i = 0 ; i < maxsize ; ++i)
              m_actions.emplace_back(new T) ;
          }
        ~CircleActor() noexcept {
          m_can_add_action = false ;
        }

        bool hasPosition(size_t pos) const { return pos < m_actions.size() ;}
      private:
        typedef std::shared_ptr<T> ValueType ;
        typedef boost::circular_buffer<ValueType> BufferType ;
        BufferType m_actions ; 
        bool m_can_add_action = true ;
    } ;
  }
}
#endif

