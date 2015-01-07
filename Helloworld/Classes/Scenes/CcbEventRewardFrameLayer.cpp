#include "CcbEventRewardFrameLayer.h"
//#include "CcbManager.h"
#include "Role.h"
#include "GameSession.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"

CcbEventRewardFrameLayer::~CcbEventRewardFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteGetYet);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGet);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon1);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon2);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon3);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLoginBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLoginDay);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventRewardFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventRewardFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventRewardFrameLayer", CcbEventRewardFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_reward_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventRewardFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEventRewardFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEventRewardFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEventRewardFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEventRewardFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventRewardFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGetYet", CCSprite*, this->m_pSpriteGetYet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGet", CCScrollButton*, this->m_pControlButtonGet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon1", CcbItemIconLayer*, this->m_pLayerIcon1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon2", CcbItemIconLayer*, this->m_pLayerIcon2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon3", CcbItemIconLayer*, this->m_pLayerIcon3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon4", CcbItemIconLayer*, this->m_pLayerIcon4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLoginBg", CCLabelTTF*, this->m_pLabelTTFLoginBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLoginDay", CCLabelTTF*, this->m_pLabelTTFLoginDay);
    
	return false;
}

bool CcbEventRewardFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventRewardFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventRewardFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventRewardFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGet", CcbEventRewardFrameLayer::onPressControlButtonGet);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventRewardFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLabelTTFLoginBg->noStroke();
//    m_pLabelTTFLoginDay->noStroke();
    m_pControlButtonGet->setTouchPriority(kCCMenuHandlerPriority - 20);
    arrIcon.push_back(m_pLayerIcon1);
    arrIcon.push_back(m_pLayerIcon2);
    arrIcon.push_back(m_pLayerIcon3);
    arrIcon.push_back(m_pLayerIcon4);
}


void CcbEventRewardFrameLayer::onPressControlButtonGet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CRole* pRole = CGameSession::GetRole();
    if (pRole)
    {
        if (pRole->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_1_GET_STAR) {
            GuideData::GetInstance()->setStepId(GuideData::E_GUIDE_END_TRIGGER);
            GuideData::GetInstance()->connectToServer();
        }
        
        if (m_byType == E_EVENT_REWARD_DAY_7 && pRole->GetbySevenRewStatus() == E_REW_STATUS_CAN)
        {
            CGameSession::SendEarnSevenReward();
            PetLoadingLayer::sharedLayer()->WaitForPacket();
        }
        else if (m_byType == E_EVENT_REWARD_DAY_30 && pRole->GetbyThirtyRewStatus() == E_REW_STATUS_CAN)
        {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendEarnThirtyReward();
        }
        else
        {
            FlyTextLayer::showTips(GET_STR(Str_get_tommorrow));
        }
    }
}

void CcbEventRewardFrameLayer::loadData(uint32 index, uint8 byType)
{
    m_byType = byType;
    
    CCString* str = CCString::createWithFormat("%d", index);
    m_pLabelTTFLoginDay->setString(str->getCString());
    int count = 0;
    if (m_byType == E_EVENT_REWARD_DAY_7) {
        EventReward7Config::STC_EVENT_REWARD_7_CONFIG* pConfig = GET_CONFIG_STC(EventReward7Config, index);
        if (pConfig)
        {
            for (int i = 0; i < 4; i++)
            {
                if (pConfig->dwItemID[i] == 0)
                {
                    continue;
                }
                arrIcon[count]->loadIndexData(pConfig->dwItemID[i]);
                arrIcon[count]->showCnt(pConfig->dwItemCount[i]);
                count++;
            }
            
        }
    }
    else if(m_byType == E_EVENT_REWARD_DAY_30)
    {
        EventReward30Config::STC_EVENT_REWARD_30_CONFIG* pConfig = GET_CONFIG_STC(EventReward30Config, index);
        if (pConfig)
        {
            for (int i = 0; i < 4; i++)
            {
                if (pConfig->dwItemID[i] == 0)
                {
                    continue;
                }
                arrIcon[count]->setVisible(true);
                arrIcon[count]->loadIndexData(pConfig->dwItemID[i]);
                arrIcon[count]->showCnt(pConfig->dwItemCount[i]);
                count++;
            }
        }
    }
    
    for (; count < arrIcon.size(); count++) {
        arrIcon[count]->setVisible(false);
    }
    
    CRole* pRole = CGameSession::GetRole();
    uint16 day = pRole->GetdwSevenRewDay();
    uint8 state = pRole->GetbySevenRewStatus();
    if (m_byType == E_EVENT_REWARD_DAY_30) {
        day = pRole->GetdwThirtyRewDay();
        state = pRole->GetbyThirtyRewStatus();
    }
    if( day > index )//过去的天数}
    {
        m_pControlButtonGet->setVisible(false);
        m_pSpriteGetYet->setVisible(true);
    }
    else if (day == index)//当天}
    {
        if (state == E_REW_STATUS_CAN)//可领状态}
        {
            m_pControlButtonGet->setEnabled(true);
            m_pControlButtonGet->setVisible(true);
            m_pSpriteGetYet->setVisible(false);
        }
        else//当前领过的状态}
        {
            m_pControlButtonGet->setVisible(false);
            m_pSpriteGetYet->setVisible(true);
        }
    }
    else//领取时间未到}
    {
        m_pControlButtonGet->setVisible(true);
        m_pControlButtonGet->setEnabled(false);
        m_pSpriteGetYet->setVisible(false);
    }
    
}

void CcbEventRewardFrameLayer::setClipRect(cocos2d::CCRect rect)
{
    m_pControlButtonGet->setClipRect(rect);
    for (int i = 0; i < 4; i++)
    {
        arrIcon[i]->setClipRect(rect);
    }
}

