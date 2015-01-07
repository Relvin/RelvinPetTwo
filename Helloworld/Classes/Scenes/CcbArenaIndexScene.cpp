//
//  CcbArenaIndexScene.cpp
//  HelloWorld
//
//  Created by jun on 13-11-6.
//
//

#include "CcbArenaIndexScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"

CcbArenaIndexScene::CcbArenaIndexScene()
{
    m_pLabelTTFName = NULL;
}

CcbArenaIndexScene::~CcbArenaIndexScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* CcbArenaIndexScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbArenaIndexScene* pLayer = CcbArenaIndexScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbArenaIndexScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool CcbArenaIndexScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbArenaIndexLayer(this));
    return true;
}

void CcbArenaIndexScene::onEnter()
{
	CCLayer::onEnter();
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_arena));
}

void CcbArenaIndexScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbArenaIndexScene::onExit()
{
	CCLayer::onExit();
}

void CcbArenaIndexScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}
