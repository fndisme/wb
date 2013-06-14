/*
 * =====================================================================================
 *
 *       Filename:  GameProperty.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/14 14:46:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "GameProperty.h"
#include <algorithm>

namespace WebGame {
  const PlayerMeta* GameProperty::playerMeta(int id) const {
    auto iter = std::find_if(m_playerMetas.begin(), m_playerMetas.end(),
        [id](const PlayerMeta& meta) { return meta.Id == id;});
    if(iter == m_playerMetas.end()) return 0;
    return &*iter;
  }
  void GameProperty::initPlayerMetaFromFile(const std::string& fileName) {
    auto metas = loadPlayerMetas(fileName);
    if(!metas.empty()) metas.swap(m_playerMetas);
  }
}
