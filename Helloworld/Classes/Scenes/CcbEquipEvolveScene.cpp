//
//  CcbEquipEvolveScene.cpp
//  MyGame
//
//  Created by jun on 14-7-3.
//
//

#include "CcbEquipEvolveScene.h"
#include "CcbManager.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

CcbEquipEvolveScene::CcbEquipEvolveScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipEvolveScene::~CcbEquipEvolveScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipEvolveScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipEvolveScene* pLayer = CcbEquipEvolveScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipEvolveScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipEvolveScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipEvolveLayer(this));
    return true;
}

void CcbEquipEvolveScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_equip_evolve));
}

void CcbEquipEvolveScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipEvolveScene::onExit()
{
	CCLayer::onExit();
}

void CcbEquipEvolveScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

