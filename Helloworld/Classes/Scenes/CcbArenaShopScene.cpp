//
//  CcbArenaShopScene.cpp
//  HelloWorld
//
//  Created by jun on 14-4-14.
//
//

#include "CcbArenaShopScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
CcbArenaShopScene::CcbArenaShopScene()
{
    m_pLabelTTFName = NULL;
}

CcbArenaShopScene::~CcbArenaShopScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbArenaShopScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbArenaShopScene* pLayer = CcbArenaShopScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbArenaShopScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbArenaShopScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbArenaShopLayer(this));
    return true;
}

void CcbArenaShopScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_arena_shop));
}

void CcbArenaShopScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaShopScene::onExit()
{
	CCLayer::onExit();
}

void CcbArenaShopScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}