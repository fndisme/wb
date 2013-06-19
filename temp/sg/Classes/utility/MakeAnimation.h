/*
 * =====================================================================================
 *
 *       Filename:  MakeAnimation.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/13 14:21:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_MAKEANIMATION_H
#define FND_WEBGAME_MAKEANIMATION_H
#include <string>
#include <vector>
#include "cocos2d.h"
namespace WebGame {
  struct MoveInfo {
    enum {
      DOWN = 0,
      LEFT = 1,
      UP = 2,
      RIGHT = 3,
    };
    int Direction;
    int Step;
    MoveInfo(int dir, int step) :
      Direction(dir),
      Step(step) {}
    explicit MoveInfo(const cocos2d::CCPoint& p);
  };


  cocos2d::CCActionInterval* createMoveAnimationAction(
      const std::string& baseName,
      const std::vector<MoveInfo>& moveInfo,
      const cocos2d::CCSize& tileSize,
      int frameSize,
      float frameTime,
      int timesPerStep,
      float moveSpeed);

  cocos2d::CCActionInterval* createMoveAction(
      const std::vector<MoveInfo>& moveInfo,
      const cocos2d::CCSize& tileSize,
      float moveSpeed);
  cocos2d::CCActionInterval* createAnimation(
      const std::string& baseName,
      const std::vector<MoveInfo>& moveInfo,
      const cocos2d::CCSize& tileSize,
      int frameSize,
      float frameTime,
      int timesPerStep);


}
#endif
