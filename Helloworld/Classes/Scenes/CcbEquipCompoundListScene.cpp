//
//  CcbEquipCompoundScene.cpp
//  HelloWorld
//
//  Created by jun on 14-2-17.
//
//

#include "CcbEquipCompoundListScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbEquipCompoundListScene::CcbEquipCompoundListScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipCompoundListScene::~CcbEquipCompoundListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipCompoundListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipCompoundListScene* pLayer = CcbEquipCompoundListScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipCompoundListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipCompoundListScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipCompoundListLayer(this));
    return true;
}

void CcbEquipCompoundListScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_choose_rune));
}

void CcbEquipCompoundListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipCompoundListScene::onExit()
{
	CCLayer::onExit();
}

void CcbEquipCompoundListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

