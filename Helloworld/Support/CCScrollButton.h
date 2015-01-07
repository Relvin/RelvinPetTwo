//
//  ScrollMenu.h
//  HelloWorld
//
//  Created by long on 13-7-29.
//
//

#ifndef __HelloWorld__CCScrollButton__
#define __HelloWorld__CCScrollButton__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCScrollButton : public CCControlButton
{
public:
    CCScrollButton();
    ~CCScrollButton();
    
    /**
     @brief 创建完全的透明按钮 */
    static CCScrollButton* create();
    static CCScrollButton* create(CCNode* label, CCScale9Sprite* backgroundSprite);
    static CCScrollButton* create(std::string title, const char * fontName, float fontSize);
    static CCScrollButton* create(CCScale9Sprite* sprite);
    /**
     @brief 创建带高亮的透明按钮 */
    static CCScrollButton* createTransWithHightLight();
    virtual bool init();
    virtual bool initWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite);
    virtual bool initWithTitleAndFontNameAndFontSize(std::string title, const char * fontName, float fontSize);
    virtual bool initWithBackgroundSprite(CCScale9Sprite* sprite);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void setClipRect(CCRect rect){clipRect = rect;};
private:
    bool isMove;
    CCPoint touchPoint;
    CCRect clipRect;
};


class CCScrollButtonLoader : public CCControlButtonLoader {
    
public:
    virtual ~CCScrollButtonLoader() {};
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCScrollButtonLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCScrollButton);

};

#endif /* defined(__HelloWorld__ScrollMenu__) */
