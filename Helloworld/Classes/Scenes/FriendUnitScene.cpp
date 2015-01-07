//
//  FriendUnitScene.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/20.
//
//

#include "FriendUnitScene.h"
#include "CcbManager.h"

USING_NS_CC;

CCScene* FriendUnitScene::scene() {
    CCScene* pScene = CCScene::create();
    FriendUnitScene* pLayer = FriendUnitScene::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool FriendUnitScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbFriendUnitLayer(this));
    return true;
}

void FriendUnitScene::onEnter() {
    CCLayer::onEnter();
    m_pLabelTTFName->setString("好友界面");
}

void FriendUnitScene::onEnterTransitionDidFinish() {
    CCLayer::onEnterTransitionDidFinish();
}

void FriendUnitScene::onExit() {
    CCLayer::onExit();
}

void FriendUnitScene::onExitTransitionDidStart() {
    CCLayer::onExitTransitionDidStart();
}

bool FriendUnitScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode ) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    return false;
}

bool FriendUnitScene::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue) {
    // 可以删除这个方法，如果删除后没有问题的话。}
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }
    
    return bRet;
}


