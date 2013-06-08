/*
 * =====================================================================================
 *
 *       Filename:  TileMask.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/8 16:25:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_TILEMASK_H
#define FND_WEBGAME_TILEMASK_H
#include <vector>
#include "cocos2d.h"

namespace WebGame {
  class TileMask : public cocos2d::CCNode {
    public:
      static TileMask*
        create(cocos2d::CCTexture2D* tex,
            const cocos2d::CCPoint& pos,
            const cocos2d::CCPoint& mapPos,
            const cocos2d::CCSize& tileSize,
            const std::vector<cocos2d::CCPoint>& tilepos);
  };
}
#endif
