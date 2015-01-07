//
//  ChatScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-6-16.}
//
//

#include "ChatScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

USING_NS_CC;

CCScene* ChatScene::scene() {
    CCScene* pScene = CCScene::create();
    ChatScene* pLayer = ChatScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool ChatScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbChatLayer(this));
    
    return true;
}

void ChatScene::onEnter() {
    CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_chat_head));
    }
}

void ChatScene::onExit() {
    CCLayer::onExit();
}

// Inhert MemberVariableAssigner
bool ChatScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	return false;
}

