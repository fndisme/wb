/*
 * =====================================================================================
 *
 *       Filename:  GameProperty.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/14 14:41:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GAMEPROPERTY_H
#define FND_WEBGAME_GAMEPROPERTY_H
#include <string>
#include <vector>
#include "PlayerMeta.h"
namespace WebGame {
  class GameProperty {
    public:
      const PlayerMeta* playerMeta(int id) const;
      void initPlayerMetaFromFile(const std::string& fileName);
    private:
      std::vector<PlayerMeta> m_playerMetas;
  };
}
#endif
