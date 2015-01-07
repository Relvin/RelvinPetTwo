//
//  CcbSettingsScene.cpp
//  HelloWorld
//
//  Created by jun on 14-5-9.
//
//

#include "CcbSettingsScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbSettingsScene::CcbSettingsScene()
{
    m_pLabelTTFName = NULL;
}

CcbSettingsScene::~CcbSettingsScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbSettingsScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbSettingsScene* pLayer = CcbSettingsScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbSettingsScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbSettingsScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbSettingsLayer(this));
    return true;
}

void CcbSettingsScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_system));
}

void CcbSettingsScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSettingsScene::onExit()
{
	CCLayer::onExit();
}

void CcbSettingsScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

