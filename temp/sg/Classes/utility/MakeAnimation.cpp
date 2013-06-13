/*
 * =====================================================================================
 *
 *       Filename:  MakeAnimation.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/6/13 14:23:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include "MakeAnimation.h"
#include <cassert>
using namespace cocos2d;
namespace WebGame {

  static cocos2d::CCActionInterval* createRFAnimFormTexture(
      cocos2d::CCTexture2D* pTexture,
      const MoveInfo& moveInfo,
      const cocos2d::CCSize& frameSize,
      int frames,
      float frameTime,
      int moveTimesPerStep) {
    CCAnimation* animation = CCAnimation::create();
    for( int i = 0;i < frames; i++){
      CCRect rect(frameSize.width * i,
          moveInfo.Direction * frameSize.height,
          frameSize.width,
          frameSize.height);
      animation->addSpriteFrame(CCSpriteFrame::createWithTexture(pTexture,
            rect));
    }
    animation->setDelayPerUnit(frameTime);
    CCAnimate* action = CCAnimate::create(animation);
    return CCRepeat::create(action, moveInfo.Step * moveTimesPerStep);
  }


  static CCActionInterval* createMoveStep(
      const CCSize& size,
      const MoveInfo& info,
      float moveSpeed) {
    CCPoint moved(0, 0);
    switch (info.Direction) {
      case MoveInfo::LEFT:
        {
          moved.x = -size.width * info.Step;
          break;
        }
      case MoveInfo::RIGHT:
        {
          moved.x = size.width * info.Step;
          break;
        }
      case MoveInfo::UP:
        {
          moved.y = size.height * info.Step;
          break;
        }
      case MoveInfo::DOWN:
        {
          moved.y = -size.height * info.Step;
          break;
        }
      default:
        assert(false);
        break;
    }
    CCMoveBy* moveBy = CCMoveBy::create(moveSpeed, moved);
    return moveBy;
  }
}


CCActionInterval* WebGame::createMoveAnimationAction(
      const std::string& baseName,
      const std::vector<MoveInfo>& moveInfo,
      const cocos2d::CCSize& tileSize,
      int frameSize,
      float frameTime,
      int timesPerStep,
      float moveSpeed) {
  CCTexture2D* tex =
    CCTextureCache::sharedTextureCache()->textureForKey(baseName.c_str());
  CCArray* arr = CCArray::create();
  for(int i = 0 ; i < moveInfo.size() ; ++i) {
    CCActionInterval* act = WebGame::createRFAnimFormTexture(
        tex, moveInfo[i],
        tileSize,
        frameSize,
        frameTime,
        timesPerStep);
    assert(act);
    CCActionInterval* moveStep = WebGame::createMoveStep(
        tileSize,
        moveInfo[i],
        moveSpeed);
    assert(moveStep);
    CCSpawn* spawn = CCSpawn::create(act, moveStep, 0);
    arr->addObject(spawn);
  }
  CCSequence* seq = CCSequence::create(arr);
  return seq;
}
