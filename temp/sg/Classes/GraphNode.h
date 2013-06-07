/*
 * =====================================================================================
 *
 *       Filename:  GraphNode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/5/26 18:25:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GRAPHNODE_H
#define FND_WEBGAME_GRAPHNODE_H
#include <memory>
namespace WebGame {
  //const int invalidGraphIndex = -1;
  class GraphNode {
    public:
      typedef std::shared_ptr<GraphNode> pointer;
      typedef std::shared_ptr<const GraphNode> const_pointer;
      int index() const { return m_index;}
      
      //bool isValid() const { return m_index > invalidGraphIndex;} 
      virtual ~GraphNode() {}
      int x() const { return m_x;}
      int y() const { return m_y;}
      int type() const { return m_type;}
      void setType(int t) { m_type = t;}

      static pointer create(int index, int x, int y, int type) {
        return pointer(new GraphNode(index, x, y, type));
      }
    private:
      int m_index;
      int m_x;
      int m_y;
      int m_type;
    
    private:
      explicit GraphNode(int index, int x, int y, int type) : m_index(index),
      m_x(x),
      m_y(y),
      m_type(type){}
  };
}

#endif

