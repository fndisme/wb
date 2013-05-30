/*
 * =====================================================================================
 *
 *       Filename:  net_stream_infomation.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011-2-10 9:43:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fndisme (), fndisme@163.com
 *        Company:  AC SH
 *
 * =====================================================================================
 */
#ifndef FND_WEB_GAME_NET_STREAM_INFOMATION_H
#define FND_WEB_GAME_NET_STREAM_INFOMATION_H
#include	<algorithm>
#include	<boost/bind.hpp>
#include	<boost/noncopyable.hpp>
#include	<boost/tuple/tuple.hpp>
#include	<pantheios/pantheios.hpp>
#include	<pantheios/inserters.hpp>
#include	<pantheios/pan.hpp>
#include	<pantheios/inserters/i.hpp>
#include	<map>
namespace WebGame {
  class net_stream_infomation : boost::noncopyable {
    typedef net_stream_infomation class_type ;
    public:
    class data_infomation {
      typedef data_infomation class_type ;
      public:
      size_t total_data_size() const { return m_total_size ;}
      size_t total_data_size(int type) {
        return boost::get<SIZE>(m_data[type]) ;
      }
      size_t total_transfer_data_times() const { return m_total_times ;}
      size_t total_transfer_data_times(int type) { return boost::get<TIMES>(
          m_data[type]) ;}

      size_t max_single_data_size() const {return m_max_data_size ;}
      size_t min_single_data_size() const {return m_min_data_size ;}
      void begin_transfer() { m_total_size++ ;}
      void end_transfer(int type, size_t size) {
        boost::get<TIMES>(m_data[type]) ++ ;
        boost::get<SIZE>(m_data[type]) += size ;
        m_total_size += size ;
        if(size > m_max_data_size) m_max_data_size = size ;
        if(size < m_min_data_size) m_min_data_size = size ;
      }
      //friend net_stream_infomation ;
      data_infomation() :
        m_total_size(0),
        m_total_times(0),
        m_max_data_size(0),
      m_min_data_size(1000000) {}
      void log(const char* header) {
        pan::log_DEBUG(header, " 总数据量 :", pan::i(m_total_size),
            "总次数:", pan::i(m_total_times),
            "单次最大数据:", pan::i(m_max_data_size),
            "单次最小数据:", pan::i(m_min_data_size)) ;
        for(iterator iter = begin(), iter_end = end() ;
            iter != iter_end ;
            ++iter) {
          pan::log_DEBUG("消息类型:", pan::i((*iter).first),
              "数据量：", pan::i(boost::get<SIZE>((*iter).second)),
              "次数:", pan::i(boost::get<TIMES>((*iter).second))) ;
        }
      }

      
      
      private:
      typedef boost::tuple<size_t, size_t> value_type ;
      enum { SIZE, TIMES} ;
      typedef std::map<int, value_type> datas_type ;
      size_t m_total_size ;
      size_t m_total_times ;
      size_t m_max_data_size ;
      size_t m_min_data_size ;

      datas_type m_data ;
      public:
      typedef datas_type::const_iterator iterator ;
      iterator begin() const { return m_data.begin() ;}
      iterator end() const { return m_data.end() ;}
    } ;
    public:
    typedef data_infomation::iterator iterator ;
    data_infomation& sender()  { return m_sender ;}
    data_infomation& receiver()  { return m_receiver ;}
    inline void begin_receive() { m_receiver.begin_transfer() ;}
    inline void end_receive(int type, size_t size) { m_receiver.end_transfer(type, size) ;}
    inline void begin_send() { m_sender.begin_transfer() ;}
    inline void end_send(int type, size_t size) { m_sender.end_transfer(type, size) ;}
    private:
    data_infomation m_sender ;
    data_infomation m_receiver ;
    
  } ;
}
#endif
