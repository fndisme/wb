/*
 * =====================================================================================
 *
 *       Filename:  GraphEdge.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/5/26 18:48:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GRAPHEDGE_H
#define FND_WEBGAME_GRAPHEDGE_H
#include <memory>
#include <boost/noncopyable.hpp>
namespace WebGame {
  class GraphEdge : boost::noncopyable {
    public:
      typedef std::shared_ptr<GraphEdge> pointer;
      typedef std::shared_ptr<const GraphEdge> const_pointer;
      int from() const {return m_from;}
      int to() const {return m_to;}
      static pointer create(int from, int to) {
        return pointer(new GraphEdge(from, to));
      }

      GraphEdge(int f, int t) : m_from(f), m_to(t) {}
    private:
      int m_from;
      int m_to;

  };
}
#endif
