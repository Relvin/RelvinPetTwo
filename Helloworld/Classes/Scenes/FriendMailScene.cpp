//
//  FriendMailScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-25.}
//
//

#include "FriendMailScene.h"
#include "CcbManager.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

CCScene* FriendMailScene::scene() {
    CCScene* pScene = CCScene::create();
    FriendMailScene* pLayer = FriendMailScene::create();
    
    pScene->addChild(pLayer);
    return pScene;
}

bool FriendMailScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbFriendMailLayer(this));
    return true;
}

void FriendMailScene::onEnter() {
    CCLayer::onEnter();
    this->m_pLabelTTFName->setString(GET_STR(Str_email_write));
}

void FriendMailScene::onExit() {
    CCLayer::onExit();
}

bool FriendMailScene::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    return false;
}

