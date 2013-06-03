/*
 * =====================================================================================
 *
 *       Filename:  GrpahDFSSearchUnittest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/3 15:50:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <limits.h>
#include "gtest/gtest.h"
#include "GraphNode.h"
#include "GraphDFSSearch.h"
#include "SparseGraph.h"
using namespace WebGame;

TEST(GraphDFSSearch, init) {
  SparseGraph::pointer p = SparseGraph::createTileGraph(5,5);
  typedef GraphDFSSearch<SparseGraph> Search;
  Search s(*p, 0, 23);

  EXPECT_EQ(true, s.hasRoute());

  auto l = s.pathToTarget();
  for(auto node : l) {
    std::cout << node << " <-- ";
  }
  std::cout << std::endl;

  
}

