//
//  CcbEquipListScene.cpp
//  HelloWorld
//
//  Created by jun on 14-2-11.
//
//

#include "CcbEquipListScene.h"
#include "CcbManager.h"
#include "CcbPetShowLayer.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

CcbEquipListScene::CcbEquipListScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipListScene::~CcbEquipListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipListScene* pLayer = CcbEquipListScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipListScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipListLayer(this));
    return true;
}

void CcbEquipListScene::onEnter()
{
	CCLayer::onEnter();
    if (g_EquipData->GetEquipListShowMode() == E_SHOW_LIST_PET
        || g_EquipData->GetEquipListShowMode() == E_SHOW_LIST_ALL)
    {
        m_pLabelTTFName->setString(GET_STR(Str_unit_4));
    }
    else if (g_EquipData->GetEquipListShowMode() == E_SHOW_LIST_INPLAY)
    {
        m_pLabelTTFName->setString(GET_STR(Str_unit_5));
    }
}

void CcbEquipListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipListScene::onExit()
{
//    CcbPetShowLayer::m_bIsChangePetEnable = true;
	CCLayer::onExit();
}

void CcbEquipListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

