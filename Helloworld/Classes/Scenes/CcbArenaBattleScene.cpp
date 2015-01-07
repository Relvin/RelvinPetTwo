//
//  CcbArenaBattleScene.cpp
//  HelloWorld
//
//  Created by jun on 13-11-6.
//
//

#include "CcbArenaBattleScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbArenaBattleScene::CcbArenaBattleScene()
{
    m_pLabelTTFName = NULL;
}

CcbArenaBattleScene::~CcbArenaBattleScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbArenaBattleScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbArenaBattleScene* pLayer = CcbArenaBattleScene::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CcbArenaBattleScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbArenaBattleScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbArenaBattleLayer(this));
    return true;
}

void CcbArenaBattleScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_arena_list));
}

void CcbArenaBattleScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaBattleScene::onExit()
{
	CCLayer::onExit();
}

void CcbArenaBattleScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}


