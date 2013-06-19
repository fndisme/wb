/*
 * =====================================================================================
 *
 *       Filename:  LockGuard.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/19 17:43:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_UTILITY_LOCKGUARD_H
#define FND_WEBGAME_UTILITY_LOCKGUARD_H
#include <boost/noncopyable.hpp>
namespace WebGame {
namespace Utility {
template<typename T>
  class LockGuard : boost::noncopyable {
    public:
      explicit LockGuard(T& o) : m_object(o) { m_object.lock(); }
      ~LockGuard() { m_object.unlock();}
    private:
      T& m_object;
  };
}
}
#endif
