//
//  CcbArenaRankScene.cpp
//  HelloWorld
//
//  Created by jun on 13-11-6.
//
//

#include "CcbArenaRankScene.h"
#include "CcbManager.h"
#include "ArenaDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbArenaRankScene::CcbArenaRankScene()
{
    m_pLabelTTFName = NULL;
}

CcbArenaRankScene::~CcbArenaRankScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbArenaRankScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbArenaRankScene* pLayer = CcbArenaRankScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbArenaRankScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbArenaRankScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbArenaRankLayer(this));
    return true;
}

void CcbArenaRankScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_rank));
}

void CcbArenaRankScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaRankScene::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRankScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
