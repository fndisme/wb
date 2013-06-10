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

    property.addAttackType(JUNIOR_LORD, neighbour);
    property.addAttackType(JUNIOR_DRAGOON, neighbour);

    neighbour.push_back(std::make_pair(1,1));
    neighbour.push_back(std::make_pair(1, -1));
    neighbour.push_back(std::make_pair(-1, 1));
    neighbour.push_back(std::make_pair(-1, -1));
    property.addAttackType(SENIOR_DRAGOON, neighbour);
    property.addAttackType(JUNIOR_FOOT_SOLDIER, neighbour);
    property.addAttackType(SENIOR_FOOT_SOLDIER, neighbour);
    property.addAttackType(SENIOR_LOARD, neighbour);

    neighbour.clear();
    neighbour.push_back(std::make_pair(2, 0));
    neighbour.push_back(std::make_pair(-2, 0));
    neighbour.push_back(std::make_pair(0, 2));
    neighbour.push_back(std::make_pair(0, -2));
    neighbour.push_back(std::make_pair(1,1));
    neighbour.push_back(std::make_pair(1, -1));
    neighbour.push_back(std::make_pair(-1, 1));
    neighbour.push_back(std::make_pair(-1, -1));

    property.addAttackType(JUNIOR_ARROWMAN, neighbour);
    neighbour.push_back(std::make_pair(3, 0));
    neighbour.push_back(std::make_pair(2, 1));
    neighbour.push_back(std::make_pair(2, -1));
    neighbour.push_back(std::make_pair(1, 2));
    neighbour.push_back(std::make_pair(1, -2));
    neighbour.push_back(std::make_pair(0, 3));
    neighbour.push_back(std::make_pair(0, -3));
    neighbour.push_back(std::make_pair(-1, 2));
    neighbour.push_back(std::make_pair(-1, -2));
    neighbour.push_back(std::make_pair(-2, 1));
    neighbour.push_back(std::make_pair(-2, -1));
    neighbour.push_back(std::make_pair(-3, 0));
    property.addAttackType(SENIOR_ARROWMAN, neighbour);

    return property;
  }
}
