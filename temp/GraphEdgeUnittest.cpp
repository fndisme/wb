/*
 * =====================================================================================
 *
 *       Filename:  GraphEdgeUnittest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/3 11:15:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "gtest/gtest.h"
#include "GraphEdge.h"
using namespace WebGame;

TEST(GraphEdge, create) {
  auto edge = GraphEdge::create(1, 2);
  EXPECT_EQ(1, edge->from());
  EXPECT_EQ(2, edge->to());
}

