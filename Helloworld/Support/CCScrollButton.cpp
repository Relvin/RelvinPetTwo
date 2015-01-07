//
//  ScrollMenu.cpp
//  HelloWorld
//
//  Created by long on 13-7-29.
//
//

#include "CCScrollButton.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
static const float fOffset = 25.0f;
#else
static const float fOffset = 15.0f;
#endif

CCScrollButton::CCScrollButton()
{
    clipRect = CCRectZero;
}

CCScrollButton::~CCScrollButton()
{
    
}

CCScrollButton* CCScrollButton::create()
{
    CCScrollButton *pControlButton = new CCScrollButton();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
}
CCScrollButton* CCScrollButton::create(CCNode* label, CCScale9Sprite* backgroundSprite)
{
    CCScrollButton *pRet = new CCScrollButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}
CCScrollButton* CCScrollButton::create(std::string title, const char * fontName, float fontSize)
{
    CCScrollButton *pRet = new CCScrollButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}
CCScrollButton* CCScrollButton::create(CCScale9Sprite* sprite)
{
    CCScrollButton *pRet = new CCScrollButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}
CCScrollButton* CCScrollButton::createTransWithHightLight()
{
    CCScrollButton *pControlButton = new CCScrollButton();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        CCScale9Sprite *sSpriteSelected = CCScale9Sprite::create("ccbresources/12monthdate/button/button_bluehighlight_2.png");
        pControlButton->setBackgroundSpriteForState(sSpriteSelected, CCControlStateHighlighted);
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
}
bool CCScrollButton::init()
{
    return this->initWithLabelAndBackgroundSprite(CCLabelTTF::create("", "Helvetica", 12), CCScale9Sprite::create());
}

bool CCScrollButton::initWithLabelAndBackgroundSprite(CCNode* node, CCScale9Sprite* backgroundSprite)
{
    
    if (!CCControlButton::initWithLabelAndBackgroundSprite(node, backgroundSprite)) {
        return false;
    }
    setTouchEnabled(true);
    return true;
}

bool CCScrollButton::initWithTitleAndFontNameAndFontSize(std::string  title, const char * fontName, float fontSize)
{
    CCLabelTTF *label = CCLabelTTF::create(title.c_str(), fontName, fontSize);
    return this->initWithLabelAndBackgroundSprite(label, CCScale9Sprite::create());
}

bool CCScrollButton::initWithBackgroundSprite(CCScale9Sprite* sprite)
{
    CCLabelTTF *label = CCLabelTTF::create("", "Arial", 30);
    return this->initWithLabelAndBackgroundSprite(label, sprite);
}

bool CCScrollButton::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    isMove = false;
    touchPoint = CCDirector::sharedDirector()->getNowScene()->convertToNodeSpace(touch->getLocation());
    if (!clipRect.equals(CCRectZero) && !clipRect.containsPoint(touch->getLocation())) {
        return false;
    }
    return CCControlButton::ccTouchBegan(touch, event);
}

void CCScrollButton::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
    CCPoint touchPointNow = CCDirector::sharedDirector()->getNowScene()->convertToNodeSpace(touch->getLocation());
//    CCLog("touchPointNow.x %f", touchPointNow.y);
    double d = sqrt((touchPointNow.x - touchPoint.x)*(touchPointNow.x - touchPoint.x) + (touchPointNow.y - touchPoint.y)*(touchPointNow.y - touchPoint.y));
//    CCLog("滑动距离: %f", d);
    if (fabsf(d) > fOffset) {
        isMove = true;
        setHighlighted(false);
    }
    CCControlButton::ccTouchMoved(touch, event);
}
void CCScrollButton::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (!isMove) {
        CCControlButton::ccTouchEnded(touch, event);
    }
    else
    {
        setHighlighted(false);
    }
}
void CCScrollButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isMove) {
        CCControlButton::ccTouchCancelled(pTouch, pEvent);
    }
    else
    {
        setHighlighted(false);
    }
}
