//
//  CcbShopNormalListScene.cpp
//  HelloWorld
//
//  Created by jun on 14-3-24.
//
//

#include "CcbShopNormalListScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbShopNormalListScene::CcbShopNormalListScene()
{
    m_pLabelTTFName = NULL;
}

CcbShopNormalListScene::~CcbShopNormalListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbShopNormalListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbShopNormalListScene* pLayer = CcbShopNormalListScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbShopNormalListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbShopNormalListScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbShopNormalListLayer(this));
    return true;
}

void CcbShopNormalListScene::onEnter()
{
	CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_shop_buy));
    }
    
}

void CcbShopNormalListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopNormalListScene::onExit()
{
	CCLayer::onExit();
}

void CcbShopNormalListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}