/*
 * =====================================================================================
 *
 *       Filename:  Weapon.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/13 20:34:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_WEAPON_H
#define FND_WEBGAME_WEAPON_H
#include <string>
#include <vector>
namespace WebGame {
  struct PhysicsWeapon {
    int Type;
    int Id;
    int Rand;
    int HitRate;
    int Power;
    int KillRate;
    int LowRange;
    int HighRange;
    int Weight;
    int Endure;
    int Price;
    std::string Name;
    std::string PictureName;
    std::string Description;
  };

  std::vector<PhysicsWeapon> loadWeapons(
      const std::string& weapon);
}
#endif

