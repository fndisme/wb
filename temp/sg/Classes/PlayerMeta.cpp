/*
 * =====================================================================================
 *
 *       Filename:  PlayerMeta.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/14 14:26:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "PlayerMeta.h"
#include "cocos2d.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::vector<WebGame::PlayerMeta> WebGame::loadPlayerMetas(const std::string& jsonFile) {
  std::vector<PlayerMeta> metas;
  using boost::property_tree::ptree;
  ptree pt;
  try {
    read_json(jsonFile, pt);
  } catch(std::exception& error) {
    cocos2d::CCLog("error %s", error.what());
    return metas;
  }

  for(const auto& v: pt.get_child("data")) {
    PlayerMeta m;
    m.Id = v.second.get<int>("id");
    m.Type = v.second.get<int>("type");
    m.Rank = v.second.get<int>("rank");
    m.Level = v.second.get<int>("level");

    m.PhysicsAttack = v.second.get<int>("physics_attack");
    m.PhysicsDefence = v.second.get<int>("physics_defence");
    m.EnergyAttack = v.second.get<int>("energy_attack");
    m.EnergyDefence = v.second.get<int>("energy_defence");
    m.MagicAttack = v.second.get<int>("magic_attack");
    m.MagicDefence = v.second.get<int>("magic_defence");

    m.Power = v.second.get<int>("power");
    m.Blood = v.second.get<int>("blood");
    m.Lucky = v.second.get<int>("lucky");
    m.Skill = v.second.get<int>("skill");
    m.KillSkill = v.second.get<int>("kill_skill");
    m.CanUsedWeapon = v.second.get<int>("can_used_weapon");
    m.Speed = v.second.get<int>("speed");
    m.MoveStep = v.second.get<int>("move_step");
    m.Evade = v.second.get<int>("evade");

    m.PhysicsAttackGrowthRate = v.second.get<int>("physics_attack_growth_rate");
    m.PhysicsDefenceGrowthRate = v.second.get<int>("physics_defence_growth_rate");
    m.EnergyAttackGrowthRate = v.second.get<int>("energy_attack_growth_rate");
    m.EnergyDefenceGrowthRate = v.second.get<int>("energy_defence_growth_rate");
    m.MagicAttackGrowthRate = v.second.get<int>("magic_attack_growth_rate");
    m.MagicDefenceGrowthRate = v.second.get<int>("magic_defence_growth_rate");
    m.PowerGrowthRate = v.second.get<int>("power_growth_rate");
    m.BloodGrowthRate = v.second.get<int>("blood_growth_rate");
    m.LuckyGrowthRate = v.second.get<int>("lucky_growth_rate");
    m.SkillGrowthRate = v.second.get<int>("skill_growth_rate");
    m.KillSkillGrowthRate = v.second.get<int>("kill_skill_growth_rate");
    m.SpeedGrowthRate = v.second.get<int>("speed_growth_rate");
    m.EvadeGrowthRate = v.second.get<int>("evade_growth_rate");
    metas.push_back(m);
  }

  return metas;
}
