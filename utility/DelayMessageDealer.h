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
//#include <algorithm>
//#include <iostream>
#include <functional>
#include <vector>

namespace WebGame {
  namespace Utility {
  class DelayMessageDealer {
    public:
    typedef std::function<void()> Function ;
    ~DelayMessageDealer() noexcept {
      for(auto& f : m_dealers) f() ;
    }
    void addDealer(Function&& f) {
      m_dealers.emplace_back(std::move(f)) ;
    }
    DelayMessageDealer() {} 
    DelayMessageDealer(const DelayMessageDealer& lhs) = delete ; 
    DelayMessageDealer& operator = (const DelayMessageDealer&) = delete;
    DelayMessageDealer(DelayMessageDealer&& rhs) :
      m_dealers(std::move(rhs.m_dealers)) {}
    private:
    std::vector<Function> m_dealers ; 
  } ;
  }
}
#endif

