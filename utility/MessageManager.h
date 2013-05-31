/*
 * =====================================================================================
 *
 *       Filename:  messageHandle.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2009-3-3 10:05:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  Artcoding, Shanghai, China
 *
 * =====================================================================================
 */
#ifndef FND_GAME_OT2_MESSAGEHANDLE_H_
#define FND_GAME_OT2_MESSAGEHANDLE_H_
#include <cassert>
#include <stdexcept>
#include <functional>
#include <boost/noncopyable.hpp>
#include	"webgame/utility/TinyFinder.h"
namespace WebGame {
namespace Utility {
  template<typename Key, typename FuncParam>
  class MessageManager : boost::noncopyable {
  public:
    typedef MessageManager<Key, FuncParam>   class_type ;
    typedef Key                             key_type ;
    typedef FuncParam                       function_para_type ;
    //typedef FuncParam*                      function_para_pointer ;
  public:
    typedef std::function<void (const function_para_type&)> function_type ;
    typedef TinyFinder<key_type, function_type > HandleMap ;

    void add(const key_type& k, const function_type& func) {
      handleMap.insert(k, func) ;
    }
		bool dispatch(const key_type& k, const function_para_type& param) const{
			if(!isRegistered(k)) return false ;
			(handleMap.value(k))(param) ;
			return true ;
    }
    bool isRegistered(const key_type& k) const {
      return handleMap.hasValue(k) ;
    }
		void lock() { handleMap.makeFinal() ;}
    MessageManager() : handleMap() {}

  private:
    HandleMap handleMap ;
    //MessageManager(class_type const&) = delete ;
    //class_type& operator = (class_type const&) = delete ;
  } ;
}
}
#endif

