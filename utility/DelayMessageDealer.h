/*
 * =====================================================================================
 *
 *       Filename:  DelayMessageDealer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月15日 10时13分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_DELAYMESSAGEDEALER_H
#define FND_WEBGAME_DELAYMESSAGEDEALER_H
#include <functional>
#include <vector>
#include <boost/noncopyable.hpp>
#include "webgame/shared/Platform.h"

namespace WebGame {
  namespace Utility {
  class DelayMessageDealer : boost::noncopyable {
    public:
    typedef std::function<void()> Function ;
    ~DelayMessageDealer() NOEXCEPT {
      for(auto& f : m_dealers) f() ;
    }
    void addDealer(Function&& f) {
      m_dealers.emplace_back(std::move(f)) ;
    }
    DelayMessageDealer() {} 
    DelayMessageDealer(DelayMessageDealer&& rhs) :
      m_dealers(std::move(rhs.m_dealers)) {}
    private:
    std::vector<Function> m_dealers ; 
  } ;
  }
}
#endif

