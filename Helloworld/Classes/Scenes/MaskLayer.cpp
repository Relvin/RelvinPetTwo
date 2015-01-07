//
//  MaskLayer.cpp
//  HelloWorld
//
//  Created by long on 13-10-22.
//
//

#include "MaskLayer.h"
#include "UISupport.h"
#include "ResourceDefine.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

MaskLayer::MaskLayer()
{
    m_bDark = true;
}

MaskLayer::~MaskLayer()
{
    CCLog("delloc mask layer");
}

MaskLayer *MaskLayer::create(std::vector<cocos2d::CCRect> arrRect, bool allDark)
{
    return MaskLayer::create(arrRect, CCDirector::sharedDirector()->getWinSize(), allDark, NULL);
}

MaskLayer *MaskLayer::create(std::vector<cocos2d::CCRect> arrRect)
{
    return MaskLayer::create(arrRect, CCDirector::sharedDirector()->getWinSize(), true, NULL);
}


MaskLayer *MaskLayer::create(CCNode* shape, bool allDark)
{
    std::vector<cocos2d::CCRect> arrRect;
    return MaskLayer::create(arrRect, CCDirector::sharedDirector()->getWinSize(), allDark, shape);
}

MaskLayer *MaskLayer::create(std::vector<cocos2d::CCRect> arrRect, cocos2d::CCSize contentSize, bool allDark, CCNode *shape)
{
    MaskLayer *pRet = new MaskLayer();
    if (pRet && pRet->init(arrRect, contentSize, allDark, shape))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}


bool MaskLayer::init(std::vector<cocos2d::CCRect> arrRect, cocos2d::CCSize contentSize, bool allDark, CCNode *shape)
{
    if (!CCLayer::init()) {
        return false;
    }
    setTouchEnabled(true);
    m_arrRect = arrRect;
    this->setContentSize(contentSize);
    
    m_bDark = allDark;
    
    CCLayerColor * maskL;
    maskL = CCLayerColor::create(ccc4(0, 0, 0, 255));

    maskL->setContentSize(contentSize);
    maskL->setAnchorPoint(CCPointZero);
    if (m_bDark) {
    maskL->setOpacity(180);
    } else {
        maskL->setOpacity(0);
    }
    maskL->setPosition(CCPointZero);
    
    CCClippingNode *holesClipper = CCClippingNode::create();
    holesClipper->setInverted(true);
    holesClipper->setAlphaThreshold( 0.05f );

    holesClipper->addChild(maskL);
    
    addChild(holesClipper);
    
    CCNode *holes = CCNode::create();
    
    if (shape) {
        holes->addChild(shape);
    }
    else{
    
        for (int i = 0; i < m_arrRect.size(); i++) {
            CCRect rect = m_arrRect[i];
            CCScale9Sprite *sh = CCScale9Sprite::create(PIC_DEFAULT);
            sh->setPreferredSize(rect.size);
            //        shape->setScaleX(rect.size.width / shape->getContentSize().width);
            //        shape->setScaleY(rect.size.height / shape->getContentSize().height);
            sh->setAnchorPoint(CCPointZero);
            sh->setPosition(rect.origin);
            holes->addChild(sh);
        }
    }
    holes->setAnchorPoint(CCPointZero);
    holes->setPosition(CCPointZero);
    holesClipper->setStencil(holes);
    return true;
}



void MaskLayer::onEnter() {
    CCLayer::onEnter();
}

void MaskLayer::onExit() {
    CCLayer::onExit();
}

bool MaskLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isVisible()) {
        return false;
    }
    CCPoint p = CCDirector::sharedDirector()->getNowScene()->convertToNodeSpace(pTouch->getLocation());
    CCLog(" touch point : %f ~~~ %f", p.x, p.y);
    if (!boundingBox().containsPoint(p)) {
        return false;
    }
    CCPoint pToWorld = getWorldPos(this);
    CCLog(" pToWorld point : %f ~~~ %f", pToWorld.x, pToWorld.y);
    for (int i = 0; i < m_arrRect.size(); i++) {
        CCRect rect = m_arrRect[i];
        rect.origin = ccpAdd(pToWorld,  m_arrRect[i].origin);
        if (rect.containsPoint(p)) {
            return false;
        }
    }
    return true;
}

void MaskLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority  * 4, true);
}
