/*
 * =====================================================================================
 *
 *       Filename:  GraphProperty.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/9 17:22:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "GraphProperty.h"

namespace WebGame {

  GraphProperty GraphProperty::buildDefault() {
    GraphProperty property;
    AttackNeighbourType neighbour;
    neighbour.push_back(std::make_pair(1,0));
    neighbour.push_back(std::make_pair(-1,0));
    neighbour.push_back(std::make_pair(0,1));
    neighbour.push_back(std::make_pair(0, -1));

    property.addAttackType(DRAGOON, neighbour);

    neighbour.push_back(std::make_pair(1,1));
    neighbour.push_back(std::make_pair(1, -1));
    neighbour.push_back(std::make_pair(-1, 1));
    neighbour.push_back(std::make_pair(-1, -1));
    property.addAttackType(FOOT_SOLDIER, neighbour);

    neighbour.clear();
    neighbour.push_back(std::make_pair(2, 0));
    neighbour.push_back(std::make_pair(-2, 0));
    neighbour.push_back(std::make_pair(0, 2));
    neighbour.push_back(std::make_pair(0, -2));
     neighbour.push_back(std::make_pair(1,1));
    neighbour.push_back(std::make_pair(1, -1));
    neighbour.push_back(std::make_pair(-1, 1));
    neighbour.push_back(std::make_pair(-1, -1));
    property.addAttackType(ARROW_MAN, neighbour);

    return property;
  }
}
