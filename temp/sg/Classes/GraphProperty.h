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
#include <map>
namespace WebGame {
  class GraphProperty {
    public:
      enum {
        FOOT_SOLDIER,
        DRAGOON,
        ARROW_MAN,
      };
      typedef std::vector<std::pair<int, int> > AttackNeighbourType;
      void addAttackType(int type, AttackNeighbourType const& info) {
        m_attackRange.insert(std::make_pair(type, info));
      }
      bool hasAttackType(int type) const { return m_attackRange.count(type);}
      const AttackNeighbourType& attackType(int type) const {
        std::map<int,AttackNeighbourType>::const_iterator iter = m_attackRange.find(type);
        return (*iter).second;
      }
      static
        GraphProperty buildDefault();
    private:
      std::map<int, AttackNeighbourType> m_attackRange;

  };
}
#endif
