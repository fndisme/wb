/*
 * =====================================================================================
 *
 *       Filename:  graphBFSFillUnittest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/3 16:54:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "gtest/gtest.h"
#include "GraphNode.h"
#include "GraphBFSFill.h"
#include "SparseGraph.h"
using namespace WebGame;

TEST(GraphBFSFill, init) {
  SparseGraph::pointer p = SparseGraph::createTileGraph(5,5);
  typedef GraphBFSFill<SparseGraph> Fill;
  Fill s(*p, 0, 4);

  auto nodes = s.canMoveToNode();
  for(auto node : nodes) {
    std::cout << node << " " ;
  }
  std::cout << std::endl;
}


