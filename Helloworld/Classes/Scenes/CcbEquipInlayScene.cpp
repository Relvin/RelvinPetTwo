//
//  CcbEquipInlayScene.cpp
//  HelloWorld
//
//  Created by jun on 14-2-12.
//
//

#include "CcbEquipInlayScene.h"
#include "CcbManager.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

CcbEquipInlayScene::CcbEquipInlayScene()
{
    m_pLabelTTFName = NULL;
}

CcbEquipInlayScene::~CcbEquipInlayScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbEquipInlayScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbEquipInlayScene* pLayer = CcbEquipInlayScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbEquipInlayScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbEquipInlayScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEquipInlayLayer(this));
    return true;
}

void CcbEquipInlayScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_equip_inlay));
}

void CcbEquipInlayScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipInlayScene::onExit()
{
	CCLayer::onExit();
}

void CcbEquipInlayScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
