//
//  CcbTowerMainScene.cpp
//  MyGame
//
//  Created by jun on 14-7-10.
//
//

#include "CcbTowerMainScene.h"
#include "CcbManager.h"
#include "SystemMessage.h"
#include "GameSession.h"
#include "AnalysicsManager.h"

static CcbTowerMainScene* m_shared = NULL;

CcbTowerMainScene* CcbTowerMainScene::getCurScene() {
    return m_shared;
}

CcbTowerMainScene::CcbTowerMainScene()
{

}

CcbTowerMainScene::~CcbTowerMainScene()
{
    m_shared = NULL;
}

CCScene* CcbTowerMainScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbTowerMainScene* pLayer = CcbTowerMainScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}


bool CcbTowerMainScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbTowerMainLayer(this));
    
    m_shared = this;
    return true;
}

void CcbTowerMainScene::onEnter()
{
	CCLayer::onEnter();
}

void CcbTowerMainScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbTowerMainScene::onExit()
{
	CCLayer::onExit();
}

void CcbTowerMainScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbTowerMainScene::systemMessageOKTapped(SystemMessage *systemMessage) {
    if (systemMessage->getParam() == 1) {
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_tower");
        CGameSession::SendResetTowerFloor();
    }
    else if (systemMessage->getParam() == 2){
        CGameSession::SendFightTower(2);
    }
    
}

