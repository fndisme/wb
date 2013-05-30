/*
 * =====================================================================================
 *
 *       Filename:  TimeoutQueue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年06月13日 14时31分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
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

#include "webgame/utility/TimeoutQueue.h"
#include <vector>
#include <algorithm>

namespace Utility {

  TimeoutQueue::Id TimeoutQueue::add(
      int64_t now,
      int64_t delay,
      Callback callback) {
    Id id = nextId_++;
    timeouts_.insert(Event(id, now + delay, -1, std::move(callback)));
    return id;
  }

  TimeoutQueue::Id TimeoutQueue::addRepeating(
      int64_t now,
      int64_t interval,
      Callback callback) {
    return addRepeatingWithDelay(now, interval, interval, callback) ;
  }

  TimeoutQueue::Id TimeoutQueue::addRepeatingWithDelay(
      int64_t now,
      int64_t delay,
      int64_t interval,
      Callback callback) {
    Id id = nextId_++;
    timeouts_.insert(Event(id, now + delay, interval, std::move(callback)));
    return id;
  }


  int64_t TimeoutQueue::nextExpiration() const {
    return (timeouts_.empty() ? std::numeric_limits<int64_t>::max() :
        timeouts_.get<BY_EXPIRATION>().begin()->expiration);
  }

  bool TimeoutQueue::erase(Id id) {
    return timeouts_.get<BY_ID>().erase(id) > 0;
  }

  bool TimeoutQueue::pause(Id id, int64_t delaytime) {
    auto& byId = timeouts_.get<BY_ID>() ;
    auto iter = byId.find(id) ;
    if(iter == byId.end()) return false ;
    auto event(std::move(*iter)) ;
    event.expiration += delaytime ;
    byId.erase(iter) ;
    timeouts_.insert(event);
    return true ;
  }

  int64_t TimeoutQueue::runInternal(int64_t now, bool onceOnly) {
    auto& byExpiration = timeouts_.get<BY_EXPIRATION>();
    int64_t nextExp;
    do {
      auto end = byExpiration.upper_bound(now);
      std::vector<Event> expired;
      std::move(byExpiration.begin(), end, std::back_inserter(expired));
      byExpiration.erase(byExpiration.begin(), end);
      std::for_each(expired.begin(), expired.end(), [now, this](Event& event) {
        // Reinsert if repeating, do this before executing callbacks
        // so the callbacks have a chance to call erase
        if (event.repeatInterval >= 0) {
          timeouts_.insert(TimeoutQueue::Event(event.id, now + event.repeatInterval,
              event.repeatInterval, event.callback));
        }
      }) ;

      // Call callbacks
      std::for_each(expired.begin(), expired.end(), [now](Event& event) {
        event.callback(event.id, now);
      }) ;
      nextExp = nextExpiration();
    } while (!onceOnly && nextExp <= now);
    return nextExp;
  }

} // namespace Utility


