//
//  CcbAwardCenterScene.cpp
//  HelloWorld
//
//  Created by jun on 14-4-4.
//
//

#include "CcbAwardCenterScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbAwardCenterScene::CcbAwardCenterScene()
{
    m_pLabelTTFName = NULL;
}

CcbAwardCenterScene::~CcbAwardCenterScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbAwardCenterScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbAwardCenterScene* pLayer = CcbAwardCenterScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbAwardCenterScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbAwardCenterScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbAwardCenterLayer(this));
    return true;
}

void CcbAwardCenterScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_reward_room));
}

void CcbAwardCenterScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAwardCenterScene::onExit()
{
	CCLayer::onExit();
}

void CcbAwardCenterScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}