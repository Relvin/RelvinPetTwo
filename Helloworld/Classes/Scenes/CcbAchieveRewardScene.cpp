//
//  CcbAchieveRewardScene.cpp
//  HelloWorld
//
//  Created by jun on 14-4-4.
//
//

#include "CcbAchieveRewardScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbAchieveRewardScene::CcbAchieveRewardScene()
{
    m_pLabelTTFName = NULL;
}

CcbAchieveRewardScene::~CcbAchieveRewardScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbAchieveRewardScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbAchieveRewardScene* pLayer = CcbAchieveRewardScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbAchieveRewardScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbAchieveRewardScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbAchieveRewardLayer(this));
    return true;
}

void CcbAchieveRewardScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_achievement));
}

void CcbAchieveRewardScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAchieveRewardScene::onExit()
{
	CCLayer::onExit();
}

void CcbAchieveRewardScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
