//
//  FriendScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-8.}
//
//

#include "FriendScene.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "PetLoadingLayer.h"

#include "CcbFriendLayer.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "FriendCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark FriendScene

CCScene* FriendScene::scene()
{
    CCScene* pScene = CCScene::create();
    FriendScene* pLayer = FriendScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool FriendScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbFriendLayer(this));
    return true;
}

void FriendScene::onEnter()
{
    CCLayer::onEnter();
    
    if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromCapture) {
        this->m_pLabelTTFName->setString(GET_STR(Str_capture_list));
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromRescue) {
        this->m_pLabelTTFName->setString(GET_STR(Str_rescue_list));
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendList) {
        this->m_pLabelTTFName->setString(GET_STR(Str_friend_list));
    } else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromTotalMail) {
        this->m_pLabelTTFName->setString(GET_STR(Str_email_search));
    }
//    else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendApply) {
//        this->m_pLabelTTFName->setString(GET_STR(Str_friend_request_list));
//    }
//    else if (FriendCtrl::Get()->getFromType() == FriendCtrl::kFromFriendMail) {
//        this->m_pLabelTTFName->setString("好友邮件");}
//    }
    
}

void FriendScene::onExit()
{
    CCLayer::onExit();
}

void FriendScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void FriendScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool FriendScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool FriendScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
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
