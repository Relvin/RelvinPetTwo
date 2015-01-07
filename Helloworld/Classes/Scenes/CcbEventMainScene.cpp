//
//  CcbEventMainScene.cpp
//  HelloWorld
//
//  Created by jun on 14-3-11.
//
//

#include "CcbEventMainScene.h"
#include "CcbManager.h"

CcbEventMainScene::CcbEventMainScene()
{
    
}

CcbEventMainScene::~CcbEventMainScene()
{
    
}

CCScene* CcbEventMainScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEventMainScene* pLayer = CcbEventMainScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEventMainScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEventMainLayer(this));
    return true;
}

void CcbEventMainScene::onEnter()
{
	CCLayer::onEnter();
}

void CcbEventMainScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventMainScene::onExit()
{
	CCLayer::onExit();
}

void CcbEventMainScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

