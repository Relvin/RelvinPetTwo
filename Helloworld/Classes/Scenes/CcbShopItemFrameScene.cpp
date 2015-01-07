//
//  CcbShopItemFrameScene.cpp
//  HelloWorld
//
//  Created by jun on 13-12-26.
//
//

#include "CcbShopItemFrameScene.h"
#include "CcbManager.h"

CcbShopItemFrameScene::CcbShopItemFrameScene()
{
    m_pLabelTTFName = NULL;
}

CcbShopItemFrameScene::~CcbShopItemFrameScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbShopItemFrameScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbShopItemFrameScene* pLayer = CcbShopItemFrameScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbShopItemFrameScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbShopItemFrameScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbShopItemFrameLayer(this));
    return true;
}

void CcbShopItemFrameScene::onEnter()
{
	CCLayer::onEnter();
}

void CcbShopItemFrameScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopItemFrameScene::onExit()
{
	CCLayer::onExit();
}

void CcbShopItemFrameScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

