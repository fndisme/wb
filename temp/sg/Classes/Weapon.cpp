/*
 * =====================================================================================
 *
 *       Filename:  Weapon.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/14 13:00:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "Weapon.h"
#include "cocos2d.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

std::vector<WebGame::PhysicsWeapon> WebGame::loadWeapons(const std::string& jsonFile) {
  std::vector<PhysicsWeapon> weapons;
  using boost::property_tree::ptree;
  ptree pt;
  try {
    read_json(jsonFile, pt);
  } catch(std::exception& error) {
    cocos2d::CCLog("error %s", error.what());
    return weapons;
  }

  for(const auto& v: pt.get_child("data")) {
    PhysicsWeapon w;
    w.Type = v.second.get<int>("type");
    w.Id = v.second.get<int>("id");
    w.Rank = v.second.get<int>("rank");
    w.HitRate = v.second.get<int>("hit_rate");
    w.Power = v.second.get<int>("power");
    w.KillRate = v.second.get<int>("kill_rate");
    w.LowRange = v.second.get<int>("low_range");
    w.HighRange = v.second.get<int>("high_range");
    w.Weight = v.second.get<int>("weight");
    w.Endure = v.second.get<int>("endure");
    w.Price = v.second.get<int>("price");
    w.Name = v.second.get<std::string>("name");
    w.PictureName = v.second.get<std::string>("picture_name");
    w.Description = v.second.get<std::string>("description");
    weapons.push_back(w);
  }

  return weapons;
}
