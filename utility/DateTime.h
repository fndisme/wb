#ifndef FND_UTILITY_DATE_TIME_H
#define FND_UTILITY_DATE_TIME_H
#include <ctime>
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
namespace WebGame {
namespace Utility {
  inline std::time_t to(const boost::posix_time::ptime& p) {
    if(p.is_not_a_date_time()) return 0 ;
    if(p.is_pos_infinity()) return (time_t) -1 ;
    boost::posix_time::ptime start(boost::gregorian::date(1970,1,1)) ;
    boost::posix_time::time_duration du = p - start ;
    return du.total_seconds() ;
  }

  inline std::time_t to(const std::chrono::system_clock::time_point& tp) {
    return std::chrono::system_clock::to_time_t(tp) ;
  }

  inline boost::posix_time::ptime now() {
    return boost::posix_time::ptime(boost::posix_time::second_clock::local_time()) ;
  }

  inline std::time_t nowAs_time_t() {
    return to_time_t(now()) ;
  }

  inline std::time_t inteval(long day, long hours = 0, long minutes = 0) {
    
    boost::posix_time::time_duration du( day * 24 + hours, minutes, 0, 0) ;
    return du.total_seconds() ;
  }
  
  inline boost::posix_time::ptime theDayOfBegin() {
    return boost::posix_time::ptime(boost::gregorian::day_clock::local_day()) ;
  }

  inline std::time_t theDayOfBeginAs_time_t() {
    return to(theDayOfBegin()) ;
  }

  inline int64_t currentTickOfTheDay() {
    return nowAs_time_t() - theDayOfBeginAs_time_t() ;
  }

  constexpr inline int64_t oneDaySeconds() {
    return  60 * 60 * 24;
  }

  inline int64_t totalSecond(int day) {
    return day * oneDaySeconds() ;
  }


  //inline int64_t tick_to_next_time_of_day(int secondsofday) {
  inline int64_t tickToNextTimeOfDay(int secondsofday) {
    assert(secondsofday >= 0) ;
    assert(secondsofday < oneDaySeconds()) ;

    int64_t ntick = secondsofday - currentTickOfTheDay() ;
    if(ntick > 0) return ntick ;
    return ntick + oneDaySeconds();
  }

  inline int currentYear() {
    return boost::gregorian::day_clock::local_day().year() ;
  }

  inline int currentMonth() {
    return boost::gregorian::day_clock::local_day().month() ;
  }

  inline int currentDayOfMonth() {
    return boost::gregorian::day_clock::local_day().day() ;
  }

  inline std::time_t make_time_t(int year,
                                        int month,
                                        int day) {
    return to(boost::posix_time::ptime(boost::gregorian::date(year, month, day))) ;
  }

  inline bool is_now_time_between(int hour_begin, int minute_begin,
      int hour_end, int minute_end) {
    assert(hour_begin <= hour_end) ;
    time_t inteval = nowAs_time_t() - theDayOfBeginAs_time_t() ;
    auto start = inteval(0, hour_begin, minute_begin) ;
    if(inteval < start) return false ;
    return inteval <= inteval(0, hour_end, minute_end) ;
  }
}
}
#endif
