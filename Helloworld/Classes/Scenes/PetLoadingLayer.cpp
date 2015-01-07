//
//  PetBattleLodingScene.cpp
//  HelloWorld
//
//  Created by long on 13-9-13.
//
//

#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "GlobalData.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

PetLoadingLayer * PetLoadingLayer::m_pShared = NULL;

#define Loading_Tag 70261


bool PetLoadingLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    this->setTouchEnabled(true);
    
    return true;
}

void PetLoadingLayer::onEnter()
{
    CCLayer::onEnter();
}

void PetLoadingLayer::onExit()
{
    CCLayer::onExit();
    unschedule(schedule_selector(PetLoadingLayer::updateSelf));
}

void PetLoadingLayer::WaitForPacket(bool _delay)
{
	if (this->getParent() != NULL)
	{
		return ;
	}
    
    CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
    scene->addChild(this, 10000);
    
    if (getChildByTag(Loading_Tag)) {
        getChildByTag(Loading_Tag)->removeFromParent();
    }
    
    m_bDelay = _delay;
    m_nRetainCnt = MAX_WAITING;
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    if (!m_bDelay) {
        addLoadLayer();
    }
    
    unschedule(schedule_selector(PetLoadingLayer::updateSelf));
    schedule(schedule_selector(PetLoadingLayer::updateSelf), 1.0f);
}

void PetLoadingLayer::CoverCouched()
{
    this->WaitForPacket(true);
    m_nRetainCnt = 1000;
}


void PetLoadingLayer::End()
{
	if (this->getParent())
    {
		this->removeFromParentAndCleanup(false);
    }
}

bool PetLoadingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void PetLoadingLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 5 * kCCMenuHandlerPriority + 2, true);
}

void PetLoadingLayer::updateSelf(float dTime)
{
    if (m_nRetainCnt <= 0) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_need_reconnect), this, true, 0, GET_STR(Str_tishi), true);
        unschedule(schedule_selector(PetLoadingLayer::updateSelf));

        if (getChildByTag(Loading_Tag)) {
            getChildByTag(Loading_Tag)->removeFromParent();
        }
        return;
    }

    m_nRetainCnt--;

    if (m_bDelay && m_nRetainCnt == MAX_WAITING - 2) {
        if (getChildByTag(Loading_Tag)) {
            getChildByTag(Loading_Tag)->removeFromParent();
        }
        
        addLoadLayer();
    }
}

void PetLoadingLayer::systemMessageOKTapped(SystemMessage *systemMessage) {
    addLoadLayer();
    
    m_nRetainCnt = MAX_WAITING;
    schedule(schedule_selector(PetLoadingLayer::updateSelf), 1.0f);
}

void PetLoadingLayer::addLoadLayer() {
    CCNode* m_pLoadingLayer = CcbManager::sharedManager()->LoadLoadingLayer();
    m_pLoadingLayer->setAnchorPoint(ccp(0.5, 0.5));
    m_pLoadingLayer->setPosition(ccp(winSize.width*0.5, winSize.height/2));
    addChild(m_pLoadingLayer, 2, Loading_Tag);
}

