/*
 * =====================================================================================
 *
 *       Filename:  GraphNodeUnittest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/3 10:37:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fdh(fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <limits.h>
#include "gtest/gtest.h"
#include "GraphNode.h"
using namespace WebGame;

TEST(GraphNode, create) {
  auto node = GraphNode::create(1, 1, 2, 1);
  EXPECT_EQ(1, node->x());
  EXPECT_EQ(2, node->y());
  EXPECT_EQ(1, node->index());
}


