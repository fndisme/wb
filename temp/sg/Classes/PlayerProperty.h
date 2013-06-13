/*
 * =====================================================================================
 *
 *       Filename:  PlayerProperty.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/13 17:27:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_PLAYER_PROPERTY_H
#define FND_WEBGAME_PLAYER_PROPERTY_H
namespace WebGame {
  class PlayerPropertyMeta {
    public:
      int job() const;
      int level() const;
      int physicsAttack() const;
      int physicsDefence() const;
      int energyAttack() const;
      int energyDefence() const;
      int magicAttack() const;
      int magicDefence() const;
      int lucky() const;
      int weight() const;
      int power() const;
      int speed() const;
      int moveStep() const;
      int killSkill() const;
      int ability() const;
  };
}
#endif
