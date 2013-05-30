/*
 * =====================================================================================
 *
 *       Filename:  HeartBeatSystem.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012-1-31 11:27:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *        Company:  GJY
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_HEARTBEATSYSTEM_H
#define FND_WEBGAME_HEARTBEATSYSTEM_H
#include <assert.h>
#include "identity_type.h"

namespace WebGame
{
class HeartBeatSystem
{
public:
    HeartBeatSystem(second_tt rate, second_tt answertime) :
        m_heart_beat(0),
        m_heart_beat_rate(rate),
        m_max_answering_time(answertime),
        m_factor(m_max_answering_time.base_type_value() / m_heart_beat_rate.base_type_value()) {
        assert(m_max_answering_time > m_heart_beat_rate) ;
        assert(m_factor >= 1) ;
    }

    times_tt heart_beat() const {
        return m_heart_beat ;
    }
    second_tt max_answer_time() const {
        return m_max_answering_time ;
    }
    void beat() {
        ++m_heart_beat ;
    }
    bool is_alive(times_tt heart) const {
        return heart + m_factor >= m_heart_beat ;
    }

    second_tt beat_rate() const {
        return m_heart_beat_rate ;
    }

private:
    times_tt m_heart_beat ;
    const second_tt m_heart_beat_rate ;
    const second_tt m_max_answering_time ;
    const int m_factor ;
} ;
}

#endif
