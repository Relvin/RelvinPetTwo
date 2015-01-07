//
//  GachaScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-22.}
//
//

#include "GachaScene.h"
#include "CcbManager.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

GachaScene::~GachaScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* GachaScene::scene()
{
    CCScene* pScene = CCScene::create();
    GachaScene* pLayer = GachaScene::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool GachaScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbNewGachaLayer(this));
    return true;
}

void GachaScene::onEnter()
{
    CCLayer::onEnter();
}

void GachaScene::onExit()
{
    CCLayer::onExit();
}

void GachaScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    m_pLabelTTFName->setString(GET_STR(Str_gacha_head));
}

void GachaScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool GachaScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	return false;
}

