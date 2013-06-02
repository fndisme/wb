#include "webgame/netcore/TimerEvent.h"
#include <boost/bind.hpp>
#include <pantheios/pantheios.hpp>
#include <pantheios/inserters.hpp>
#include <pantheios/assert.h>


#ifdef THIS_CLASS
#undef THIS_CLASS
#endif
#define THIS_CLASS WebGame::NetCore::TimerEvent
using WebGame::second_tt ;
using WebGame::times_tt ;
void THIS_CLASS::dummy() {}
void THIS_CLASS::init() {
	if(m_times != zero())
		m_timer.async_wait(
				m_strand.wrap(boost::bind(&TimerEvent::dealEvent,
						this,
						boost::asio::placeholders::error))) ;
}


bool THIS_CLASS::isValid() const {
	return (m_times != zero() && m_seconds >= 0) ||
		(m_times == zero() && m_seconds == 0) ;
}

THIS_CLASS::~TimerEvent() {
	PANTHEIOS_ASSERT(isValid()) ;
	if(m_times != 0) {
		stop() ;
	}
}

void THIS_CLASS::changeTime(second_tt seconds) {
	m_seconds = seconds ;
}

void THIS_CLASS::restart() {
	restart(m_seconds) ;
}

void THIS_CLASS::restart(second_tt seconds) {
	boost::system::error_code error ;
	m_timer.expires_from_now(boost::posix_time::seconds(seconds.base_type_value()),
			error ) ;
	if(error) {
		pantheios::log_DEBUG("TimerEvent_error ", error.message()) ;
	}
	pantheios::log_DEBUG("seconds : ", pantheios::integer(seconds.base_type_value()),
			"act ", pantheios::integer(m_times.base_type_value())) ;
	m_timer.async_wait(m_strand.wrap(boost::bind(&TimerEvent::dealEvent,
					this,
					boost::asio::placeholders::error))) ;

}

void THIS_CLASS::pause(second_tt seconds) {
	PANTHEIOS_ASSERT(m_times != zero()) ;
	PANTHEIOS_ASSERT(isValid()) ;
	auto tm = m_timer.expires_from_now() ;
	long sec = tm.total_seconds() ;
	restart(second_tt(sec + seconds));
}

void THIS_CLASS::dealEvent(const boost::system::error_code& error) {
	if(error == boost::asio::error::operation_aborted || (m_times == zero()) ) {
		pantheios::log_DEBUG("error or not ", error.message(),
				" ", pantheios::integer(m_times.base_type_value())) ;
	} else {

		if(m_times != loopForever()) {
			m_times-- ;
		}

		if(m_times != zero()) {
			m_timer.expires_at(m_timer.expires_at() +
					boost::posix_time::seconds(m_seconds.base_type_value())) ;
			m_timer.async_wait(m_strand.wrap(boost::bind(&TimerEvent::dealEvent,
							this,
							boost::asio::placeholders::error))) ;
		} else {
			changeTime(second_tt(0)) ;
		}
		// TODO on_event must be put the last action because people may change timer
		// property in on_event....
		onEvent() ;
		PANTHEIOS_ASSERT(isValid()) ;
	}
}



THIS_CLASS::TimerEvent(boost::asio::strand& strand,
    times_tt times,
    second_tt seconds) :
  onEvent(THIS_CLASS::dummy),
  m_strand(strand),
  m_timer(strand.get_io_service(), boost::posix_time::seconds(seconds.base_type_value())),
  m_seconds(seconds),
  m_times(times) {
    PANTHEIOS_ASSERT(isValid()) ;
  }


#undef THIS_CLASS

