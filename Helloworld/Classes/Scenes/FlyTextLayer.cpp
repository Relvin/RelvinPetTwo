//
//  FlyTextLayer.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-6-22.}
//
//

#include "FlyTextLayer.h"
#include "Defines.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "ResourceDefine.h"
#include "UISupport.h"
#include "ResourceStringClient.h"
#include "PacketDataMgr.h"

#define Tips_Tag 719


FlyTextLayer::FlyTextLayer() {
    m_pLabelBMFontText = NULL;
    m_delay = 0;
}

FlyTextLayer::~FlyTextLayer()
{
    
}

void FlyTextLayer::showText(uint8 kType, int num, float delay)
{
    FlyTextLayer* pLayer = FlyTextLayer::create(kType, num, delay);
    if (pLayer) {
        CCScene* pCurScene = CCDirector::sharedDirector()->getRunningScene();
        if (pCurScene) {
            pCurScene->addChild(pLayer, 999);
        }
    }
}

void FlyTextLayer::showTips(std::string strText)
{
    FlyTextLayer* pLayer = FlyTextLayer::create(strText);
    if (pLayer) {
        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        if (pScene) {
            if (pScene->getChildByTag(Tips_Tag)) {
                pScene->removeChildByTag(Tips_Tag);
            }
            pScene->addChild(pLayer, 999, Tips_Tag);
        }
    }
}

void FlyTextLayer::showBuffText(std::string strText, bool isUp, CCPoint pos, float delay, float scale, CCNode* node)
{
    FlyTextLayer* pLayer = FlyTextLayer::create(strText, isUp, delay, scale);
    if (pLayer) {
        pLayer->setPosition(pos);
//        pLayer->setScale(scale);
//        pLayer->ignoreAnchorPointForPosition(false);
//        pLayer->setAnchorPoint(ccp(0.5, 0.5));
        if (node) {
            node->addChild(pLayer, 700);
            return;
        }
        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        if (pScene) {
            pScene->addChild(pLayer, 999);
        }
    }
}

FlyTextLayer* FlyTextLayer::create(uint8 kType, int num, float delay)
{
    FlyTextLayer* pLayer = new FlyTextLayer();
    if (pLayer && pLayer->init(kType, num, delay)) {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

FlyTextLayer* FlyTextLayer::create(std::string strText)
{
    FlyTextLayer* pLayer = new FlyTextLayer();
    if (pLayer && pLayer->init(strText)) {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

FlyTextLayer* FlyTextLayer::create(std::string strText, bool isUp, float delay, float scale)
{
    FlyTextLayer* pLayer = new FlyTextLayer();
    if (pLayer && pLayer->init(strText, isUp, delay, scale)) {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void FlyTextLayer::onEnter()
{
    CCLayer::onEnter();
    
    if (t_type == kErrorText) {
        CCFadeOut* _fadeOut = CCFadeOut::create(1.0f);
        
        this->runAction(
                        CCSequence::create(
                                            _fadeOut,
                                           CCCallFunc::create(this, callfunc_selector(FlyTextLayer::destorySelf)),
                                           NULL)
                        );
    } else if (t_type == kProperty) {
        CCMoveBy* _moveBy = CCMoveBy::create(1.0f, ccp(0, 50));
        CCFadeOut* _fadeOut = CCFadeOut::create(0.3f);
        
        this->runAction(
                        CCSequence::create(CCHide::create(),
                                            CCDelayTime::create(m_delay),
                                            CCShow::create(),
                                            _moveBy,
                                            _fadeOut,
                                            CCCallFunc::create(this, callfunc_selector(FlyTextLayer::destorySelf)),
                                           NULL)
                        );
    }
    else if (t_type == kBuffText){
        CCMoveBy* _moveBy = CCMoveBy::create(0.5f, ccp(0, 20));
        CCFadeOut* _fadeOut = CCFadeOut::create(0.3f);
        
        this->runAction(
                        CCSequence::create(CCHide::create(),
                                           CCDelayTime::create(m_delay),
                                           CCShow::create(),
                                           _moveBy,
                                           _fadeOut,
                                           CCCallFunc::create(this, callfunc_selector(FlyTextLayer::destorySelf)),
                                           NULL)
                        );
    }
    
}

void FlyTextLayer::onExit() {
    CCLayer::onExit();
}

void FlyTextLayer::destorySelf()
{
    this->removeFromParent();
}

#define MONEY_PATH "ccbresources/font/font3.fnt"
#define ADD_PATH "ccbresources/font/font2.fnt"
#define SUB_PATH "ccbresources/font/font1.fnt"

bool FlyTextLayer::init(std::string strText)
{
    if (!CCLayer::init()) {
        return false;
    }
    t_type = kErrorText;
    
    winSize= CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSpriteBg = CCSprite::create(GET_PIC(Pic_fly_text_bg));
    pSpriteBg->setAnchorPoint(ccp(0.5, 0.5));
    pSpriteBg->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    addChild(pSpriteBg, 999);
    
    CCLabelTTF* m_pLabelTTFText = CCLabelTTF::create(strText.c_str(), FONT_HEL, 14.0f, CCSizeMake(300.0f, 0.0f), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    m_pLabelTTFText->setColor(ccWHITE);
    m_pLabelTTFText->setAnchorPoint(ccp(0.5, 0.5));
    m_pLabelTTFText->setPosition(ccp(getWidth(pSpriteBg)*0.5, getHeight(pSpriteBg)*0.5));
    pSpriteBg->addChild(m_pLabelTTFText, 2);
    return true;
}

bool FlyTextLayer::init(uint8 kType, int num, float delay)
{
    if (!CCLayer::init()) {
        return false;
    }
    t_type = kProperty;
    m_delay = delay;
    setVisible(false);
    if (kType == kMoneyAdd) {
        sprintf(szBuf, "%sx%d", GET_STR(Str_money), num);
        m_pLabelBMFontText = CCLabelBMFont::create(szBuf, MONEY_PATH);
    }
    else if (kType == kEnergyAdd)
    {
        m_pLabelBMFontText = CCLabelBMFont::create(CCString::createWithFormat("%s +%d",GET_STR(Str_Get_Energy),num)->getCString(), ADD_PATH);
    }
    else{
        if (num < 0)
        {
            sprintf(szBuf, "%s%d", g_PacketDataMgr->getAttrText(kType).c_str(), num);
            m_pLabelBMFontText = CCLabelBMFont::create(szBuf, SUB_PATH);
        }
        else{
            sprintf(szBuf, "%s+%d", g_PacketDataMgr->getAttrText(kType).c_str(), num);
            m_pLabelBMFontText = CCLabelBMFont::create(szBuf, ADD_PATH);
        }
        m_pLabelBMFontText->setScale(0.8);
    }

    winSize= CCDirector::sharedDirector()->getWinSize();
    m_pLabelBMFontText->setAnchorPoint(ccp(0.5, 0.5));
    m_pLabelBMFontText->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    addChild(m_pLabelBMFontText, 999);
    return true;
}

bool FlyTextLayer::init(std::string strText, bool isUp, float delay, float scale)
{
    if (!CCLayer::init()) {
        return false;
    }
    t_type = kBuffText;
    m_delay = delay;

    if (isUp)
    {
        m_pLabelBMFontText = CCLabelBMFont::create(strText.c_str(), ADD_PATH);
    }
    else{
        m_pLabelBMFontText = CCLabelBMFont::create(strText.c_str(), SUB_PATH);
    }
    m_pLabelBMFontText->setScale(scale);
    
    
    winSize= CCDirector::sharedDirector()->getWinSize();
    m_pLabelBMFontText->setAnchorPoint(ccp(0.5, 0.5));
    m_pLabelBMFontText->setPosition(CCPointZero);
    this->setContentSize(m_pLabelBMFontText->getContentSize());
    addChild(m_pLabelBMFontText, 999);
    return true;
}


