/*
 * =====================================================================================
 *
 *       Filename:  SparseGraph.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/5/26 19:11:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "SparseGraph.h"
#include <cassert>
#include <iostream>

#include "GraphNode.h"
#include "GraphEdge.h"

#define THIS_CLASS WebGame::SparseGraph

THIS_CLASS::SparseGraph(int maxX, int maxY) :
  m_x(maxX),
  m_y(maxY),
  m_nodes(maxX * maxY, GraphNode::pointer()),
  m_edges(maxX * maxY),
  m_realNodeSize(0){
    assert(maxX * maxY> 0);
  }

bool THIS_CLASS::hasNode(int index) const {
  return index < static_cast<int>(m_nodes.size()) && m_nodes[index];
}

WebGame::GraphNode::pointer THIS_CLASS::node(int index) {
  assert(hasNode(index));
  return m_nodes[index];
}

bool THIS_CLASS::hasEdge(int from, int to) const {
  if (!hasNode(from) || !hasNode(to)) return false;
  if (nodeEdge(from, to)) return true;
  return false;
}

bool THIS_CLASS::addEdge(GraphEdge::pointer e) {
  assert(e);

  if (e->from() == e->to()) return false; // not valid for n -> n
  if (!hasNode(e->from()) || !hasNode(e->to())) return false;
  if (nodeEdge(e->from(), e->to())) return false;
  m_edges[e->from()].push_back(e);
  return true;
}

WebGame::GraphEdge::const_pointer THIS_CLASS::edge(int from, int to) const {
  if (!hasNode(from) || !hasNode(to)) return GraphEdge::const_pointer();
  return nodeEdge(from, to);
}

WebGame::GraphEdge::pointer THIS_CLASS::edge(int from, int to) {
  if (!hasNode(from) || !hasNode(to)) return GraphEdge::pointer();
  return nodeEdge(from, to);
}

const THIS_CLASS::Edges& THIS_CLASS::edges(int from) const {
  assert(from >= 0);
  assert(from < static_cast<int>(m_edges.size()));

  return m_edges[from];
}

WebGame::GraphEdge::pointer THIS_CLASS::nodeEdge(int from, int to) {
  assert(hasNode(from));
  assert(hasNode(to));

  for (auto& e : m_edges[from]) 
    if (e->to() == to) return e;
  return GraphEdge::pointer();
}

WebGame::GraphEdge::const_pointer THIS_CLASS::nodeEdge(int from, int to) const {
  assert(hasNode(from));
  assert(hasNode(to));

  for(auto& e : m_edges[from]) 
    if (e->to() == to) return e;
  return GraphEdge::const_pointer();
}

void THIS_CLASS::debugPrint() const {
  for (int i = 0 ; i < m_y ; ++i) {
    for (int j = 0 ; j < m_x ; ++j) {
      if (auto p = m_nodes[i * m_y + j]) {
        std::cout << "(" << p->x() << "," << p->y() << ")  ";
      } else {
        std::cout << "      ";
      }
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;

  for(auto& edges : m_edges) {
    for(auto edge : edges) {
      std::cout << "e(" << edge->from() << ":" << edge->to() << " " ;
    }
    std::cout << std::endl;
  }
}

bool THIS_CLASS::isValidNode(GraphNode::const_pointer n) const {
  if (n->x() < 0 || n->x() >= m_x) return false;
  if (n->y() < 0 || n->y() >= m_y) return false;
  return true;
}

bool THIS_CLASS::addNode(GraphNode::pointer n) {
  if (!n) return false;
  if (!isValidNode(n)) return false;
  if (n->index() < 0 || n->index() >= static_cast<int>(m_nodes.size())) return false;
  if (m_nodes[n->index()]) return false;
  m_nodes[n->index()] = n;
  ++m_realNodeSize;
  assert(m_realNodeSize <= static_cast<int>(m_nodes.size()));
  return true;
}

WebGame::GraphNode::const_pointer THIS_CLASS::node(int index) const {
  assert(hasNode(index));
  return m_nodes[index];
}

THIS_CLASS::pointer THIS_CLASS::createTileGraph(int x, int y) {
  THIS_CLASS::pointer graph(new THIS_CLASS(x,y));
  for(int i = 0 ; i < y ; ++i)
    for(int j = 0 ; j < x ; ++j) {
      NodeType::pointer node(NodeType::create(i * x + j, j, i, 0));
      graph->addNode(node);
    }

  for(int i = 0 ; i < y - 1; ++i)
    for( int j = 0 ; j < x -1 ; ++j) {
      int left = i * x + j;
      int right = i * x + j + 1;
      auto edge = EdgeType::create(left, right);
      graph->addEdge(edge);
      edge = EdgeType::create(right, left);
      graph->addEdge(edge);
      int top = left;
      int bottom = left + x;
      edge = EdgeType::create(top, bottom);
      graph->addEdge(edge);
      edge = EdgeType::create(bottom, top);
      graph->addEdge(edge);
    }

  for(int i = 0 ; i < y - 1; ++i) {
    int top = i * x + (x - 1);
    int bottom = top + x;
    auto edge = EdgeType::create(top, bottom);
    graph->addEdge(edge);
    edge = EdgeType::create(bottom, top);
    graph->addEdge(edge);
  }


  int base = (y -1 ) * x;
  for(int i = 0 ; i < x - 1; ++i) {
    int left = base + i;
    int right = left + 1;
    auto edge = EdgeType::create(left, right);
    graph->addEdge(edge);
    edge = EdgeType::create(right, left);
    graph->addEdge(edge);
  }

  return graph;
}
