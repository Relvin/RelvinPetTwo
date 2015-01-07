//
//  CcbExchangeCodeScene.cpp
//  HelloWorld
//
//  Created by jun on 14-4-22.
//
//

#include "CcbExchangeCodeScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbExchangeCodeScene::CcbExchangeCodeScene()
{
    m_pLabelTTFName = NULL;
}

CcbExchangeCodeScene::~CcbExchangeCodeScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbExchangeCodeScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbExchangeCodeScene* pLayer = CcbExchangeCodeScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbExchangeCodeScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbExchangeCodeScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbExchangeCodeLayer(this));
    return true;
}

void CcbExchangeCodeScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_exchange_reward));
}

void CcbExchangeCodeScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbExchangeCodeScene::onExit()
{
	CCLayer::onExit();
}

void CcbExchangeCodeScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
