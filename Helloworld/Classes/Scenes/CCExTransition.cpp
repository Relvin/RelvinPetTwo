//
//  CCExTransition.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-6-24.}
//
//

#include "CCExTransition.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
//#include "CcbManager.h"
#include "LoadingLayer.h"

const unsigned int kFogTag = 0xF09F09;

CCTransitionFog::CCTransitionFog()
{
    
}

CCTransitionFog::~CCTransitionFog()
{
    
}

CCTransitionFog* CCTransitionFog::create(float duration, cocos2d::CCScene *scene) {
    CCTransitionFog* pTrans = new CCTransitionFog();
    pTrans->initWithDuration(duration, scene);
    pTrans->autorelease();
    return pTrans;
}

bool CCTransitionFog::initWithDuration(float t, cocos2d::CCScene *scene)
{
    if (!CCTransitionScene::initWithDuration(t, scene)) {
        return false;
    }
    return true;
}

void CCTransitionFog::onEnter()
{
    CCTransitionScene::onEnter();
    
    CCSprite* pCloud = CCSprite::create(GET_PIC(Pic_begin_cloud));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    pCloud->setAnchorPoint(CCPointZero);
    pCloud->setPosition(ccp(winSize.width, 0.0f));
    
    float fSpriteW = pCloud->getContentSize().width;
    CCMoveBy* pMoveLeftAction = CCMoveBy::create(m_fDuration/2, ccp(-fSpriteW, 0.0f));
    CCMoveBy* pMoveRightAction = CCMoveBy::create(m_fDuration/2, ccp(fSpriteW, 0.0f));

    pCloud->runAction( CCSequence::create(pMoveLeftAction, pMoveRightAction, NULL) );
    addChild(pCloud, 99, kFogTag);
    
    m_pInScene->setVisible(false);
    CCActionInterval* pInAction = (CCActionInterval*)CCSequence::create(
                                                                        CCScaleTo::create(m_fDuration/2, 1.5f),
                                                                        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),
                                                                        CCDelayTime::create(m_fDuration/2),
                                                                        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
                                                                        NULL
                                                                        );
    m_pOutScene->runAction(pInAction);
}

void CCTransitionFog::onExit()
{
    removeChildByTag(kFogTag);
    CCTransitionScene::onExit();
}



CCTransitionLoading::CCTransitionLoading()
{
    
}

CCTransitionLoading::~CCTransitionLoading()
{
    
}

CCTransitionLoading* CCTransitionLoading::create(float duration, cocos2d::CCScene *scene) {
    CCTransitionLoading* pTrans = new CCTransitionLoading();
    pTrans->initWithDuration(duration, scene);
    pTrans->autorelease();
    return pTrans;
}

bool CCTransitionLoading::initWithDuration(float t, cocos2d::CCScene *scene)
{
    if (!CCTransitionScene::initWithDuration(t, scene)) {
        return false;
    }
    return true;
}

void CCTransitionLoading::onEnter()
{
    CCTransitionScene::onEnter();
    

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    LoadingLayer *layer = LoadingLayer::create();
    layer->setAnchorPoint(ccp(0.5, 0.5));
    layer->setPosition(ccp(winSize.width*0.5, winSize.height/2));
    layer->setTag(1);
    this->addChild(layer);
    
    m_pInScene->setVisible(false);
    CCActionInterval* pInAction = (CCActionInterval*)CCSequence::create(
                                                                        CCDelayTime::create(m_fDuration/2),
                                                                        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::hideOutShowIn)),
//                                                                        CCDelayTime::create(m_fDuration/2),
                                                                        CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
                                                                        NULL
                                                                        );
    m_pOutScene->runAction(pInAction);
}

void CCTransitionLoading::onExit()
{
    removeChildByTag(1);
    CCTransitionScene::onExit();
}