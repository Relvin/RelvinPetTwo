//
//  CcbEquipCompoundInfoScene.cpp
//  HelloWorld
//
//  Created by jun on 14-2-18.
//
//

#include "CcbEquipCompoundInfoScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbEquipCompoundInfoScene::CcbEquipCompoundInfoScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipCompoundInfoScene::~CcbEquipCompoundInfoScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipCompoundInfoScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipCompoundInfoScene* pLayer = CcbEquipCompoundInfoScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipCompoundInfoScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipCompoundInfoScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipCompoundInfoLayer(this));
    return true;
}

void CcbEquipCompoundInfoScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_compound));
}

void CcbEquipCompoundInfoScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipCompoundInfoScene::onExit()
{
	CCLayer::onExit();
}

void CcbEquipCompoundInfoScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}