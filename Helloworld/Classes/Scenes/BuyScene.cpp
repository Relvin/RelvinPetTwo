//
//  BuyScene.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-23.}
//
//

#include "BuyScene.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"

BuyScene::~BuyScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* BuyScene::scene()
{
    CCScene* pScene = CCScene::create();
    BuyScene* pLayer = BuyScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool BuyScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadBuyMiddleLayer(this));
    return true;
}

void BuyScene::onEnter()
{
    CCLayer::onEnter();
//    m_pLabelTTFName->setStrokeForLabelTTF(ccBLACK, 1.0);
    m_pLabelTTFName->setString(GET_STR(Str_shop));
}

void BuyScene::onExit()
{
    CCLayer::onExit();
}

void BuyScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void BuyScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool BuyScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName );
	return false;
}

bool BuyScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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



