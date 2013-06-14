/*
 * =====================================================================================
 *
 *       Filename:  GraphProperty.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/9 15:45:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GRAPHPROPERTY_H
#define FND_WEBGAME_GRAPHPROPERTY_H
#include <string>
#include <map>
#include <vector>
#include "Terrain.h"
#include "Weapon.h"
namespace WebGame {
  class GraphProperty {
    public:
      enum {
        JUNIOR_LORD,
        JUNIOR_DRAGOON,
        SENIOR_DRAGOON,
        SENIOR_LOARD,
        JUNIOR_FOOT_SOLDIER,
        SENIOR_FOOT_SOLDIER,
        JUNIOR_ARROWMAN,
        SENIOR_ARROWMAN,
      };
      typedef std::vector<std::pair<int, int> > AttackNeighbourType;
      void addAttackType(int type, AttackNeighbourType const& info) {
        m_attackRange.insert(std::make_pair(type, info));
      }
      bool hasAttackType(int type) const { return m_attackRange.count(type) == 1;}
      const AttackNeighbourType& attackType(int type) const {
        std::map<int,AttackNeighbourType>::const_iterator iter = m_attackRange.find(type);
        return (*iter).second;
      }
      bool hasTerrain(int type) const { return m_terrainMeta.count(type);}
      static
        GraphProperty buildDefault();
      static GraphProperty buildFromFile(const std::string& fileName);
    private:
      std::map<int, AttackNeighbourType> m_attackRange;
      std::map<int, Terrain> m_terrainMeta;
      std::vector<PhysicsWeapon> m_weapons;
  };
}
#endif
