/*
 * =====================================================================================
 *
 *       Filename:  timer_event_fwd.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-12-31 10:34:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_TIMER_EVENT_FWD_H
#define FND_WEBGAME_TIMER_EVENT_FWD_H
#include <memory>
#include <boost/function.hpp>
namespace WebGame {
  namespace NetCore {
	class TimerEvent;
  typedef boost::function<void ()> timer_event_function_type ;
 
	typedef std::unique_ptr<TimerEvent> timer_event_pointer ;
  }
}
#endif
