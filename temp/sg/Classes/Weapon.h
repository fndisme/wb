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
    int Rank;
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
  class Weapon {
    public:
      Weapon(const PhysicsWeapon& meta, int endure) :
        m_meta(meta),
        m_endudre(endure) {}
      int endure() const { return m_endudre;}
      bool isValid() const { return m_endudre > 0;}
      void consume() { m_endudre --; }
      const PhysicsWeapon& meta() const { return m_meta;}
    private:
      PhysicsWeapon m_meta;
      int m_endudre;
  };
}
#endif
