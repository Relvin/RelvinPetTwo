//
//  CcbVipListScene.cpp
//  HelloWorld
//
//  Created by jun on 14-6-5.
//
//

#include "CcbVipListScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbVipListScene::CcbVipListScene()
{
    m_pLabelTTFName = NULL;
}

CcbVipListScene::~CcbVipListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbVipListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbVipListScene* pLayer = CcbVipListScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbVipListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbVipListScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
//    addChild(CcbManager::sharedManager()->LoadCcbVipListLayer(this));
    return true;
}

void CcbVipListScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_vip));
}

void CcbVipListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbVipListScene::onExit()
{
	CCLayer::onExit();
}

void CcbVipListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
