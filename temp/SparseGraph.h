/*
 * =====================================================================================
 *
 *       Filename:  SparseGraph.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/5/26 18:52:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SPARSEGRAPH_H
#define FND_WEBGAME_SPARSEGRAPH_H
#include <vector>
#include <list>
//#include <map>
#include <memory>

//#include "GraphNode.h"
#include "GraphEdge.h"
namespace WebGame {
  class GraphNode;
  class GraphEdge;
  class SparseGraph {
    public:
      typedef std::list<std::shared_ptr<GraphEdge>> Edges;
      typedef GraphEdge EdgeType;
      typedef GraphNode NodeType;
      typedef std::shared_ptr<SparseGraph> pointer;
      explicit SparseGraph(int maxX, int maxY);
      bool addNode(std::shared_ptr<GraphNode> n);
      bool addEdge(std::shared_ptr<GraphEdge> e);
      bool hasEdge(int from, int to)const;
      //bool removeEdge(int from, int to);
      std::shared_ptr<GraphEdge> edge(int from, int to);
      std::shared_ptr<const GraphEdge> edge(int from, int to) const;
      bool hasNode(int index) const;
      std::shared_ptr<GraphNode> node(int index);
      std::shared_ptr<const GraphNode> node(int index) const;
      const Edges& edges(int from) const;
      int nodeSize() const { return m_realNodeSize;}
      int totalSize() const { return m_nodes.size();}
      int width() const { return m_x;}
      int height() const { return m_y;}

      void debugPrint() const;
      static pointer
        createTileGraph(int x, int y);

      
    private:
      int m_x;
      int m_y;
      std::vector<std::shared_ptr<GraphNode>> m_nodes;
      typedef std::vector<Edges> EdgeGroup;
      EdgeGroup m_edges;
      int m_realNodeSize;

    private:
      std::shared_ptr<const GraphEdge> nodeEdge(int from, int to) const;
      std::shared_ptr<GraphEdge> nodeEdge(int from, int to);
      bool isValidNode(std::shared_ptr<const GraphNode>) const;
  };
}
#endif

