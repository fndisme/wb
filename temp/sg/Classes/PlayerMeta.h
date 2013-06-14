/*
 * =====================================================================================
 *
 *       Filename:  PlayerMeta.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/14 13:58:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_PLAYERMETA_H
#define FND_WEBGAME_PLAYERMETA_H
#include <string>
#include <vector>
namespace WebGame {
  struct PlayerMeta {
    int Id;
    int Type;
    int Rank;
    int Level;

    int PhysicsAttack;
    int PhysicsDefence;
    int EnergyAttack;
    int EnergyDefence;
    int MagicAttack;
    int MagicDefence;

    int Power;
    int Blood;
    int Lucky;
    int Skill;
    int KillSkill;
    int CanUsedWeapon;
    int Speed;
    int MoveStep;
    int Evade;

    int PhysicsAttackGrowthRate;
    int PhysicsDefenceGrowthRate;
    int EnergyAttackGrowthRate;
    int EnergyDefenceGrowthRate;
    int MagicAttackGrowthRate;
    int MagicDefenceGrowthRate;
    int PowerGrowthRate;
    int BloodGrowthRate;
    int LuckyGrowthRate;
    int SkillGrowthRate;
    int KillSkillGrowthRate;
    int SpeedGrowthRate;
    int EvadeGrowthRate;

  };
  std::vector<PlayerMeta> loadPlayerMetas(
      const std::string& weapon);

}
#endif
