/*
* Copyright 2012 GJY, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


/*
* Copyright 2012 Facebook, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**
* Simple timeout queue. Call user-specified callbacks when their timeouts
* expire.
*
* This class assumes that "time" is an int64_t and doesn't care about time
* units (seconds, milliseconds, etc). You call runOnce() / runLoop() using
* the same time units that you use to specify callbacks.
*
* @author Tudor Bosman (tudorb@fb.com)
*/







/* I need a function pause (mostly add time for a ID to call).
 * so I change the file.
 **/
 

/*
 * =====================================================================================
 *
 *       Filename:  TimeoutQueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月13日 14时19分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef UTILITY_TIMEOUTQUEUE_H_
#define UTILITY_TIMEOUTQUEUE_H_ 

#include <stdint.h>
#include <functional>
#include <boost/noncopyable.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

namespace Utility {

class TimeoutQueue : boost::noncopyable {
 public:
  typedef int64_t Id;
  typedef std::function<void(Id, int64_t)> Callback;

  TimeoutQueue() : timeouts_(), nextId_(1) { }
  //TimeoutQueue& operator = (TimeoutQueue const& ) = delete ;
  //TimeoutQueue(const TimeoutQueue&) = delete ;

  /**
* Add a one-time timeout event that will fire "delay" time units from "now"
* (that is, the first time that run*() is called with a time value >= now
* + delay).
*/
  Id add(int64_t now, int64_t delay, Callback callback);

  /**
* Add a repeating timeout event that will fire every "interval" time units
* (it will first fire when run*() is called with a time value >=
* now + interval).
*
* run*() will always invoke each repeating event at most once, even if
* more than one "interval" period has passed.
*/
  Id addRepeating(int64_t now, int64_t interval, Callback callback);

  /** 
   * Add a repeating timeout event that will fire every 'inteval" time units
   * (but it will first fire when run*() is called with a time value >= 
   * now + delay)
   * run*() will always invoke each repeating event at most once, even if
   * more than one "interval" period has passed.
   */
  Id addRepeatingWithDelay(int64_t now, int64_t delay, int64_t interval, Callback) ;

  /**
* Erase a given timeout event, returns true if the event was actually
* erased and false if it didn't exist in our queue.
*/
  bool erase(Id id);

  /**
* Pause a timer to delay some time
*
* Return false if the the id timer not existed.
*
*/
  bool pause(Id id, int64_t delay) ;

  /**
* Process all events that are due at times <= "now" by calling their
* callbacks.
*
* Callbacks are allowed to call back into the queue and add / erase events;
* they might create more events that are already due. In this case,
* runOnce() will only go through the queue once, and return a "next
* expiration" time in the past or present (<= now); runLoop()
* will process the queue again, until there are no events already due.
*
* Note that it is then possible for runLoop to never return if
* callbacks re-add themselves to the queue (or if you have repeating
* callbacks with an interval of 0).
*
* Return the time that the next event will be due (same as
* nextExpiration(), below)
*/
  int64_t runOnce(int64_t now) { return runInternal(now, true); }
  int64_t runLoop(int64_t now) { return runInternal(now, false); }

  /**
* Return the time that the next event will be due.
*/
  int64_t nextExpiration() const;

 private:
  int64_t runInternal(int64_t now, bool runOnce);

  struct Event {
    Id id;
    int64_t expiration;
    int64_t repeatInterval;
    Callback callback ;
    Event(Event&& event) :
      id(event.id),
      expiration(event.expiration),
      repeatInterval(event.repeatInterval),
      callback(std::move(event.callback)) {}
    Event(const Event& event) :
      id(event.id),
      expiration(event.expiration),
      repeatInterval(event.repeatInterval),
      callback(event.callback) {}
    Event(Id id_,
        int64_t expiration_,
        int64_t repeatInterval_,
        Callback&& callback_) :
      id(id_),
      expiration(expiration_),
      repeatInterval(repeatInterval_),
      callback(std::move(callback_)) {}
    Event(Id id_,
        int64_t expiration_,
        int64_t repeatInterval_,
        const Callback& callback_) :
      id(id_),
      expiration(expiration_),
      repeatInterval(repeatInterval_),
      callback(callback_) {}

  };

  typedef boost::multi_index_container<
    Event,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_unique<boost::multi_index::member<
        Event, Id, &Event::id
      >>,
      boost::multi_index::ordered_non_unique<boost::multi_index::member<
        Event, int64_t, &Event::expiration
      >>
    >
  > Set;

  enum {
    BY_ID=0,
    BY_EXPIRATION=1
  };

  Set timeouts_;
  Id nextId_;
};

} // namespace folly

#endif /* UTILITY_TIMEOUTQUEUE_H_*/


