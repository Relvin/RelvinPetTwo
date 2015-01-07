#include "CcbArenaIndexLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "ArenaDataMgr.h"
#include "CcbArenaRewardLayer.h"
#include "ConfigGet.h"
#include "ConfigData.h"
#include "PetLoadingLayer.h"
#include "CcbArenaMyInfoLayer.h"
#include "GuideData.h"
#include "ResourceStringClient.h"
#include "CcbArenaReportLayer.h"
#include "MusicCtrl.h"
#include "UISupport.h"
#include "ErrorMsg.h"
#include "GuideBtnPos.h"

CcbArenaIndexLayer::~CcbArenaIndexLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonRank);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTeam);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReportBack);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReport);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBattle);
	CC_SAFE_RELEASE_NULL(m_pControlButtonExchange);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
	CC_SAFE_RELEASE_NULL(m_pLayerArenaReward);
    CC_SAFE_RELEASE_NULL(m_pLayerMyInfo);
    CC_SAFE_RELEASE_NULL(m_pLayerMyInfoParent);
    m_curScene = NULL;
}

CcbArenaIndexLayer* CcbArenaIndexLayer::m_curScene = NULL;

bool CcbArenaIndexLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
	return true;
}

bool CcbArenaIndexLayer::InitData()
{
    PetLoadingLayer::sharedLayer()->End();
    CcbArenaRewardLayer *pRewardLayer = (CcbArenaRewardLayer*)m_pLayerArenaReward;
    ARENA_PLAYER_INFO tempInfo = CArenaDataMgr::Get()->GetPlayerInfo();
    
    //如果有奖励则不显示时间，没有奖励显示倒计时}
    if ((tempInfo.byIsReward == 0 || tempInfo.byIsReward == 2) && (tempInfo.dwLeftTime > CArenaDataMgr::Get()->getLostTime()) )
    {
        //CCLOG("%d######%f", tempInfo.dwLeftTime, CArenaDataMgr::Get()->getLostTime());
        m_dwLeftTime = tempInfo.dwLeftTime - CArenaDataMgr::Get()->getLostTime();
        
        pRewardLayer->m_pLabelTTFTime->setString("");
        //pRewardLayer->m_pLabelTTFTime->setVisible(true);
        //pRewardLayer->m_pControlButtonReward->setEnabled(false);
        g_ArenaData->SetCanRequestReward(false);
    }
    else
    {
        m_dwLeftTime = 0;
        //pRewardLayer->m_pLabelTTFTime->setVisible(false);
        ((CcbArenaRewardLayer*)m_pLayerArenaReward)->m_pLabelTTFTime->setString(GET_STR(Str_can_reward));
        pRewardLayer->m_pControlButtonReward->setEnabled(true);
        g_ArenaData->SetCanRequestReward(true);
    }
    
    return true;
}

void CcbArenaIndexLayer::onUpdate(float delta)
{
    if (m_dwLeftTime == 0)
    {
        return;
    }
    static float lostTime = 0;
    lostTime = lostTime + delta;
    
    if (lostTime >= 1)
    {
        m_dwLeftTime = m_dwLeftTime - 1;
        lostTime = 0;
        
        uint32 dwHour = m_dwLeftTime / 3600;
        uint32 dwMin = (m_dwLeftTime / 60) % 60;
        uint32 dwSec = m_dwLeftTime % 60;
        
        CCString* strHour = CCString::createWithFormat("%d", dwHour);
        CCString* strMin = CCString::createWithFormat("%d", dwMin);
        CCString* strSec = CCString::createWithFormat("%d", dwSec);
        if (dwMin < 10)
        {
            strMin = CCString::createWithFormat("0%d", dwMin);
        }
        if (dwSec < 10)
        {
            strSec = CCString::createWithFormat("0%d", dwSec);
        }
        CCString* strTime = CCString::createWithFormat("%s:%s:%s", strHour->getCString(), strMin->getCString(), strSec->getCString());
        
        ((CcbArenaRewardLayer*)m_pLayerArenaReward)->m_pLabelTTFTime->setString(strTime->getCString());
        
        if (m_dwLeftTime == 0)
        {
            ((CcbArenaRewardLayer*)m_pLayerArenaReward)->m_pLabelTTFTime->setString(GET_STR(Str_can_reward));
            
            ((CcbArenaRewardLayer*)m_pLayerArenaReward)->setEffectVisible(true);
            g_ArenaData->SetCanRequestReward(true);
        }
    }
}

void CcbArenaIndexLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    CGameSession::SendEnterArenaSceneRequest();
//    schedule(schedule_selector(CcbArenaIndexLayer::onUpdate));
    CGameSession::Attach(this);
    m_pControlButtonReport->setVisible(true);
    m_pControlButtonReportBack->setVisible(false);
}

void CcbArenaIndexLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbArenaIndexLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbArenaIndexLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonBattle, GuideBtnPos::E_JJC_START);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonExchange, GuideBtnPos::E_SHENGWANG);
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_2_JJC,
                                                 GuideData::E_SYS_GUIDE_6_JJC,
                                                 NULL
                                                 );
    }
}

void CcbArenaIndexLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbArenaIndexLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaIndexLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRank", CCControlButton*, this->m_pControlButtonRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTeam", CCControlButton*, this->m_pControlButtonTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReportBack", CCControlButton*, this->m_pControlButtonReportBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReport", CCControlButton*, this->m_pControlButtonReport);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBattle", CCControlButton*, this->m_pControlButtonBattle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExchange", CCControlButton*, this->m_pControlButtonExchange);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerArenaReward", CCLayer*, this->m_pLayerArenaReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMyInfo", CCLayer*, this->m_pLayerMyInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMyInfoParent", CCLayer*, this->m_pLayerMyInfoParent);
    
	return false;
}


bool CcbArenaIndexLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaIndexLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaIndexLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaIndexLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRank", CcbArenaIndexLayer::onPressControlButtonRank);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTeam", CcbArenaIndexLayer::onPressControlButtonTeam);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReportBack", CcbArenaIndexLayer::onPressControlButtonReportBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReport", CcbArenaIndexLayer::onPressControlButtonReport);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBattle", CcbArenaIndexLayer::onPressControlButtonBattle);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExchange", CcbArenaIndexLayer::onPressControlButtonExchange);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbArenaIndexLayer::onPressControlButtonBack);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaIndexLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pControlButtonReportBack->setTouchPriority(kCCMenuHandlerPriority-10);
    m_pControlButtonRank->setTouchPriority(kCCMenuHandlerPriority-10);
    m_pControlButtonBattle->setTouchPriority(kCCMenuHandlerPriority-10);
    m_pControlButtonTeam->setTouchPriority(kCCMenuHandlerPriority-10);
    m_pControlButtonBack->setTouchPriority(kCCMenuHandlerPriority-10);
    ((CcbArenaRewardLayer*)m_pLayerArenaReward)->setEffectVisible(false);
}

void CcbArenaIndexLayer::onPressControlButtonBattle(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendArenaBattleListRequest();
}

void CcbArenaIndexLayer::RefeashLayer()
{
    CcbArenaRewardLayer *pRewardLayer = (CcbArenaRewardLayer*)m_pLayerArenaReward;
    ARENA_PLAYER_INFO tempInfo = CArenaDataMgr::Get()->GetPlayerInfo();
    
    //如果有奖励则不显示时间，没有奖励显示倒计时}
    if (tempInfo.byIsReward == 0 || tempInfo.byIsReward == 2)
    {
        m_dwLeftTime = tempInfo.dwLeftTime - CArenaDataMgr::Get()->getLostTime();
        pRewardLayer->m_pLabelTTFTime->setString("");
        pRewardLayer->setEffectVisible(false);
        g_ArenaData->SetCanRequestReward(false);
    }
    else
    {
        m_dwLeftTime = 0;
        pRewardLayer->m_pLabelTTFTime->setString(GET_STR(Str_can_reward));
        pRewardLayer->setEffectVisible(true);
        g_ArenaData->SetCanRequestReward(true);
    }
}

void CcbArenaIndexLayer::onPressControlButtonExchange(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendRequestArenaShopList();    
}

void CcbArenaIndexLayer::onPressControlButtonRank(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendArenaRankListRequest();
}

void CcbArenaIndexLayer::onPressControlButtonTeam(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    BackCtrl::InsertNextScene(kTeamScene);
}

void CcbArenaIndexLayer::onPressControlButtonReportBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    m_pLayerMyInfoParent->removeChildByTag(1324, true);
    m_pControlButtonReport->setVisible(true);
    m_pControlButtonReportBack->setVisible(false);
}

void CcbArenaIndexLayer::onPressControlButtonReport(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));

    CCNode* pReportNode = CcbManager::sharedManager()->LoadCcbArenaReportLayer(this);
    m_pLayerMyInfoParent->addChild(pReportNode, 1999, 1324);
    
    m_pControlButtonReport->setVisible(false);
    m_pControlButtonReportBack->setVisible(true);
}

void CcbArenaIndexLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    BackCtrl::BacktoUpperScene();
}

bool CcbArenaIndexLayer::NotifyErrorMsg(uint16 wErrorNo)
{
    if (wErrorNo == ERROR_MSG_ARENA_REWARD_HAVED) {
        CGameSession::SendEnterArenaSceneRequest();
        return true;
    }
    return false;
}