//
//  CcbDailyQuestRewardScene.cpp
//  HelloWorld
//
//  Created by jun on 14-4-4.
//
//

#include "CcbDailyQuestRewardScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbDailyQuestRewardScene::CcbDailyQuestRewardScene()
{
    m_pLabelTTFName = NULL;
}

CcbDailyQuestRewardScene::~CcbDailyQuestRewardScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbDailyQuestRewardScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbDailyQuestRewardScene* pLayer = CcbDailyQuestRewardScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbDailyQuestRewardScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbDailyQuestRewardScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbDailyQuestRewardLayer(this));
    return true;
}

void CcbDailyQuestRewardScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_everyday_task));
}

void CcbDailyQuestRewardScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbDailyQuestRewardScene::onExit()
{
	CCLayer::onExit();
}

void CcbDailyQuestRewardScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
