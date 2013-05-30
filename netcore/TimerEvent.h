#ifndef FND_GAME_WEB_GAME_TIMER_EVENT_H
#define FND_GAME_WEB_GAME_TIMER_EVENT_H
#include <map>
#include <memory>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/any.hpp>
#include "webgame/shared/identity_type.h"

namespace WebGame {
  namespace NetCore {
    class TimerEvent {
      public:

        typedef TimerEvent class_type;
        typedef boost::function<void ()>
          timer_event_function_type ;
        typedef std::unique_ptr<class_type> pointer ;
        timer_event_function_type onEvent;
        static pointer
          create(boost::asio::strand& strand,
              times_tt times,
              second_tt seconds,
              const timer_event_function_type& func) {
            auto* ev = new TimerEvent(
                strand,
                times,
                seconds) ;
            ev->onEvent = func ;

            auto pp = pointer(ev) ;
            pp->init() ;
            return pp ;
          }

        static pointer create(boost::asio::strand& strand) {
          return create(strand, zero(), second_tt(0),
              TimerEvent::dummy) ;
        }

        static pointer create(boost::asio::strand& strand,
            second_tt seconds,
            const timer_event_function_type& func) {
          return create(strand, loopForever(), seconds, func) ;
        }

        bool stop() {
          boost::system::error_code error ;
          cancel(error) ;
          return error ? false : true ;
        }

        void pause(second_tt seconds) ;
        ~TimerEvent() ;

        TimerEvent(class_type const&) = delete ;
        class_type& operator = (TimerEvent const&) = delete ;

      private:
        static times_tt loopForever() { return times_tt(-1) ;}
        TimerEvent(boost::asio::strand&,
            times_tt times,
            second_tt seconds) ;

        void dealEvent(const boost::system::error_code&) ;
        boost::asio::strand& m_strand ;
        boost::asio::deadline_timer m_timer ;
        second_tt m_seconds ;
        times_tt m_times ;
        static times_tt once() { return times_tt(1) ;}
        static times_tt zero() { return times_tt(0) ;}
        void restart(second_tt seconds) ;
        void init() ;
        static void dummy() ;
        void changeTime(second_tt seconds) ;
        void restart() ;
        void changeActionTimes(times_tt t) { m_times = t ;}
        void changeCallback(const timer_event_function_type& func) {
          onEvent = func ;
        }
        void resetTimer(times_tt t, second_tt sec,
            const timer_event_function_type& func) {
          changeTime(sec);
          changeActionTimes(t) ;
          changeCallback(func) ;
          restart() ;
        }

        void cancel(boost::system::error_code& error) {
          onEvent= TimerEvent::dummy ;
          m_times = zero() ;
          changeTime(second_tt(0)) ;
          m_timer.cancel(error) ;
        }
        bool isValid() const ;
    };
  }
}

#endif
