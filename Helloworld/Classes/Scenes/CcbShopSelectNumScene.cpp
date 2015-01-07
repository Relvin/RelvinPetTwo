//
//  CcbShopSelectNumScene.cpp
//  HelloWorld
//
//  Created by jun on 13-12-26.
//
//

#include "CcbShopSelectNumScene.h"
#include "CcbManager.h"

CcbShopSelectNumScene::CcbShopSelectNumScene()
{
    m_pLabelTTFName = NULL;
}

CcbShopSelectNumScene::~CcbShopSelectNumScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbShopSelectNumScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbShopSelectNumScene* pLayer = CcbShopSelectNumScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbShopSelectNumScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbShopSelectNumScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbShopSelecNumLayer());
    return true;
}

void CcbShopSelectNumScene::onEnter()
{
	CCLayer::onEnter();
}

void CcbShopSelectNumScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopSelectNumScene::onExit()
{
	CCLayer::onExit();
}

void CcbShopSelectNumScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
