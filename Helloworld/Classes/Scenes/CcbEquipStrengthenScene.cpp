//
//  CcbEquipStrengthenScene.cpp
//  HelloWorld
//
//  Created by jun on 14-2-17.
//
//

#include "CcbEquipStrengthenScene.h"
#include "CcbManager.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

CcbEquipStrengthenScene::CcbEquipStrengthenScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipStrengthenScene::~CcbEquipStrengthenScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipStrengthenScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipStrengthenScene* pLayer = CcbEquipStrengthenScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipStrengthenScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipStrengthenScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipStrengthenLayer(this));
    return true;
}

void CcbEquipStrengthenScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_equip_enhance));
}

void CcbEquipStrengthenScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipStrengthenScene::onExit()
{
	CCLayer::onExit();
}

void CcbEquipStrengthenScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}