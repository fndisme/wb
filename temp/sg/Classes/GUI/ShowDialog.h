/*
 * =====================================================================================
 *
 *       Filename:  ShowDialog.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/6/12 14:47:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (fndisme), fndisme@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef FND_WEBGAME_GUI_SHOWDILAOG_H
#define FND_WEBGAME_GUI_SHOWDILAOG_H
#include <string>
#include "cocos2d.h"
namespace cocos2d {
  namespace extension {
    class CCScale9Sprite;
  }
}
namespace WebGame {
  namespace GUI {
    class ShowDialog : public cocos2d::CCNode,
    public cocos2d::CCTouchDelegate {
      public:

        static
        ShowDialog* create(const std::string& jsonFile);
        bool init();

    virtual void onEnter(); 
    virtual void onExit(); 
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event); 
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event); 
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event); 
        

      private:
        typedef cocos2d::CCNode base_class;
        std::string m_dialog;
        std::string m_nineSpriteName;
        std::string m_animName;
        cocos2d::CCActionInterval* m_anim;
        ShowDialog() : 
          m_background(0),
          m_label(0),
          m_sprite(0) {}

         
        cocos2d::extension::CCScale9Sprite* m_background;
        cocos2d::CCLabelTTF* m_label;
        cocos2d::CCSprite* m_sprite;
    };
  }
}
#endif

