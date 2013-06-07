/*
 * =====================================================================================
 *
 *       Filename:  SpritePool.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/6 23:04:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_SPRITEPOOL_H
#define FND_WEBGAME_SPRITEPOOL_H
#include "cocos2d.h"
#include <vector>

namespace WebGame {
  class SpritePool {
    public:
      SpritePool() {
        m_array = cocos2d::CCArray::create();
        m_array->retain();
      }
      ~SpritePool() {
        m_array->release();
      }
      void addSprite(cocos2d::CCSprite* s) {
        m_array->addObject(s);
        m_pool.push_back(s);
      }

      void reback(cocos2d::CCSprite* s) {
        m_pool.push_back(s);
      }

      cocos2d::CCSprite* getSprite() {
        cocos2d::CCSprite* s = m_pool.back();
        m_pool.pop_back();
      }
    private:
      cocos2d::CCArray* m_array;
      std::vector<cocos2d::CCSprite*> m_pool;
  };
}
#endif

