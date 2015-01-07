//
//  CcbMailListScene.cpp
//  HelloWorld
//
//  Created by jun on 13-11-18.
//
//

#include "CcbMailListScene.h"
#include "CcbManager.h"
#include "MailDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbMailListScene::CcbMailListScene()
{
    m_pLabelTTFName = NULL;
}

CcbMailListScene::~CcbMailListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}
    
CCScene* CcbMailListScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbMailListScene* pLayer = CcbMailListScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    
    return pScene;
}


bool CcbMailListScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbMailListLayer(this));
    return true;
}



void CcbMailListScene::onEnter()
{
    CCLayer::onEnter();         
    m_pLabelTTFName->setString(GET_STR(Str_system_email));
}
void CcbMailListScene::onExit()
{
    CCLayer::onExit();
}

void CcbMailListScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

void CcbMailListScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

// Inhert MemberVariableAssigner
bool CcbMailListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}


