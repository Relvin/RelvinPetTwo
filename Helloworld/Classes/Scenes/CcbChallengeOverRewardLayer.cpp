#include "CcbChallengeOverRewardLayer.h"
#include "EnumDefines.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "ChallengeDataMgr.h"
#include "CcbItemIconLayer.h"
#include "ResourceStringClient.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"

CcbChallengeOverRewardLayer::~CcbChallengeOverRewardLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerIcon_1);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon_3);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon_2);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon_4);
    CC_SAFE_RELEASE_NULL(m_pControlButtonGetReward);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pSpriteGetYet);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbChallengeOverRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbChallengeOverRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbChallengeOverRewardLayer", CcbChallengeOverRewardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_rewardlist.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbChallengeOverRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    setTouchEnabled(true);
	// code here
	return true;
}

void CcbChallengeOverRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbChallengeOverRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengeOverRewardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbChallengeOverRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbChallengeOverRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_1", CcbItemIconLayer*, this->m_pLayerIcon_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_3", CcbItemIconLayer*, this->m_pLayerIcon_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_2", CcbItemIconLayer*, this->m_pLayerIcon_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon_4", CcbItemIconLayer*, this->m_pLayerIcon_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGetReward", CCControlButton*, this->m_pControlButtonGetReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGetYet", CCSprite*, this->m_pSpriteGetYet);

	return false;
}

bool CcbChallengeOverRewardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeOverRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeOverRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeOverRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGetReward", CcbChallengeOverRewardLayer::onPressControlButtonGetReward);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbChallengeOverRewardLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChallengeOverRewardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 6);
    m_pControlButtonGetReward->setTouchPriority(kCCMenuHandlerPriority - 6);
    m_pSpriteGetYet->setVisible(false);
    arrItem.push_back(m_pLayerIcon_1);
    arrItem.push_back(m_pLayerIcon_2);
    arrItem.push_back(m_pLayerIcon_3);
    arrItem.push_back(m_pLayerIcon_4);
}



void CcbChallengeOverRewardLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    setVisible(false);
}
void CcbChallengeOverRewardLayer::onPressControlButtonGetReward(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendGetChallengeReward();
}

void CcbChallengeOverRewardLayer::loadData()
{
    STC_CHA_LEVEL_INFO chaInfo = g_ChallengeDataMgr->getCurStageInfo();
    if (chaInfo.wIndexId == 0) {
        return;
    }
    
    //通关奖励物品
    std::map<uint16, ChallengeConfig::STC_CHALLENGE_CONFIG> mapChanllenge = GET_CONFIG_MAP(ChallengeConfig);
    
    std::map<uint16, ChallengeConfig::STC_CHALLENGE_CONFIG>::reverse_iterator it = mapChanllenge.rbegin();
    
    if (it != mapChanllenge.rend()) {
        int len = 0;
        GET_ARRAY_LEN(it->second.dwRewardItem, len);
        int cnt = 0;
        for (int i = 0; i < len; i++) {
            if (!it->second.dwRewardItem[i]) {
                continue;
            }
            arrItem[cnt]->setVisible(true);
            arrItem[cnt]->loadIndexData(it->second.dwRewardItem[i]);
            arrItem[cnt]->showIconOnly();
            arrItem[cnt]->showName();
            arrItem[cnt]->showCnt(it->second.dwRewardItemCnt[i]);
            cnt++;
        }
        for (; cnt < 4; cnt++) {
            arrItem[cnt]->setVisible(false);
        }
    }
    
    
    
    //领奖状态
    m_pControlButtonGetReward->setVisible(true);
    m_pSpriteGetYet->setVisible(false);
    if (chaInfo.byRewStatus == E_REW_STATUS_CAN) {
        m_pControlButtonGetReward->setEnabled(true);
        m_pControlButtonGetReward->setTitleForState(CCString::create(GET_STR(Str_get_reward)), CCControlStateNormal);
        
    }
    else if(chaInfo.byRewStatus == E_REW_STATUS_DONE){
        m_pControlButtonGetReward->setVisible(false);
        m_pSpriteGetYet->setVisible(true);
    }
    else{
        m_pControlButtonGetReward->setTitleForState(CCString::create(GET_STR(Str_weitongguan)), CCControlStateNormal);
        m_pControlButtonGetReward->setEnabled(false);
    }
}

bool CcbChallengeOverRewardLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return isVisible();
}

void CcbChallengeOverRewardLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);
}



