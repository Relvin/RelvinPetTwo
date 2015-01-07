//
//  CcbShopGemListScene.cpp
//  HelloWorld
//
//  Created by jun on 14-3-24.
//
//

#include "CcbShopGemListScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbShopGemListScene::CcbShopGemListScene()
{
    m_pLabelTTFName = NULL;
}

CcbShopGemListScene::~CcbShopGemListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbShopGemListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbShopGemListScene* pLayer = CcbShopGemListScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbShopGemListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbShopGemListScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbShopGemListLayer(this));
    return true;
}

void CcbShopGemListScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_buy_dollar));
}

void CcbShopGemListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopGemListScene::onExit()
{
	CCLayer::onExit();
}

void CcbShopGemListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
