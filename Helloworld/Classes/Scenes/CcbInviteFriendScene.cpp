//
//  CcbInviteFriendScene.cpp
//  HelloWorld
//
//  Created by jun on 14-4-23.
//
//

#include "CcbInviteFriendScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

CcbInviteFriendScene::CcbInviteFriendScene()
{
    m_pLabelTTFName = NULL;
}

CcbInviteFriendScene::~CcbInviteFriendScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbInviteFriendScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbInviteFriendScene* pLayer = CcbInviteFriendScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbInviteFriendScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbInviteFriendScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbInviteFriendLayer(this));
    return true;
}

void CcbInviteFriendScene::onEnter()
{
	CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_friend_invite));
}

void CcbInviteFriendScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbInviteFriendScene::onExit()
{
	CCLayer::onExit();
}

void CcbInviteFriendScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

