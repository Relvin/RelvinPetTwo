//
//  CcbArenaResultScene.cpp
//  HelloWorld
//
//  Created by jun on 14-1-13.
//
//

#include "CcbArenaResultScene.h"
#include "CcbManager.h"

CcbArenaResultScene::CcbArenaResultScene()
{
    
}

CCScene* CcbArenaResultScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbArenaResultScene* pLayer = CcbArenaResultScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbArenaResultScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbArenaResultWinLayer(this));
    return true;
}

void CcbArenaResultScene::onEnter()
{
	CCLayer::onEnter();
}

void CcbArenaResultScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaResultScene::onExit()
{
	CCLayer::onExit();
}

void CcbArenaResultScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

CcbArenaResultScene::~CcbArenaResultScene()
{
    
}