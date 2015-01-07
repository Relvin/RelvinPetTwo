//
//  CcbAccountBindingScene.cpp
//  HelloWorld
//
//  Created by jun on 14-5-12.
//
//

#include "CcbAccountBindingScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbAccountBindingScene::CcbAccountBindingScene()
{
    m_pLabelTTFName = NULL;
}

CcbAccountBindingScene::~CcbAccountBindingScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbAccountBindingScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbAccountBindingScene* pLayer = CcbAccountBindingScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbAccountBindingScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbAccountBindingScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbAccountBindingLayer(this));
    return true;
}

void CcbAccountBindingScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_userid_lock));
}

void CcbAccountBindingScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAccountBindingScene::onExit()
{
	CCLayer::onExit();
}

void CcbAccountBindingScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}