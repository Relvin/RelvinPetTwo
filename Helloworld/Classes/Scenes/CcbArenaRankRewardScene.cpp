//
//  CcbArenaRankRewardScene.cpp
//  HelloWorld
//
//  Created by jun on 14-6-10.
//
//

#include "CcbArenaRankRewardScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbArenaRankRewardScene::CcbArenaRankRewardScene()
{
    m_pLabelTTFName = NULL;
}

CcbArenaRankRewardScene::~CcbArenaRankRewardScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbArenaRankRewardScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbArenaRankRewardScene* pLayer = CcbArenaRankRewardScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbArenaRankRewardScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbArenaRankRewardScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbArenaRankRewardLayer(this));
    return true;
}

void CcbArenaRankRewardScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_rank_reward));
}

void CcbArenaRankRewardScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaRankRewardScene::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRankRewardScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
