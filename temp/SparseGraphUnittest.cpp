/*
 * =====================================================================================
 *
 *       Filename:  SparseGraphUnittest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/3 11:57:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "gtest/gtest.h"
#include "SparseGraph.h"
using namespace WebGame;

TEST(SparseGraph, create) {
  SparseGraph g(5,5);
  EXPECT_EQ(25, g.totalSize());
  for(int i = 0 ; i < 25; ++i)
    EXPECT_EQ(false, g.hasNode(i));
}

TEST(SparseGraph, createTileGraph) {
  auto p = SparseGraph::createTileGraph(5, 5);
  EXPECT_EQ(25, p->totalSize());
  for(int i = 0 ; i < 25; ++i)
    EXPECT_EQ(true, p->hasNode(i));
  for(int i = 0 ; i < 5; ++i)
    for(int j = 0 ; j < 4; ++j) {
      int left = i * 5 + j;
      int right = i * 5 + j + 1;
      EXPECT_EQ(true, p->hasEdge(left, right));
      EXPECT_EQ(true, p->hasEdge(right, left));
    }
  EXPECT_EQ(true, p->hasEdge(3,4));
  for(int i = 0 ; i < 4; ++i)
    for(int j = 0 ; j < 5; ++j) {
      int top = i * 5 + j;
      int bottom = (i + 1) * 5 + j;
      EXPECT_EQ(true, p->hasEdge(top, bottom));
      EXPECT_EQ(true, p->hasEdge(bottom, top));
    }
}

