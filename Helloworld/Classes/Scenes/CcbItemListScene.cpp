//
//  CcbItemListScene.cpp
//  HelloWorld
//
//  Created by jun on 13-11-26.
//
//

#include "CcbItemListScene.h"
#include "CcbManager.h"
#include "ItemDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbItemListScene::CcbItemListScene()
{
    m_pLabelTTFName = NULL;
}

CcbItemListScene::~CcbItemListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbItemListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbItemListScene* pLayer = CcbItemListScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbItemListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbItemListScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbItemListLayer(this));
    return true;
}

void CcbItemListScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_all_item));

}

void CcbItemListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbItemListScene::onExit()
{
	CCLayer::onExit();
}

void CcbItemListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
