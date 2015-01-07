#include "CcbSweepLayer.h"
//#include "CcbManager.h"
#include "StageScene.h"
#include "Role.h"
#include "GameSession.h"
#include "GlobalData.h"
#include "PetLoadingLayer.h"
#include "FightAI.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "PacketDataMgr.h"
#include "EnumDefines.h"
#include "Instruments.h"
#include "WorldInfoDataMgr.h"
#include "FlyTextLayer.h"
#include "ConfigData.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_SWEEP_CNT 5

static CcbSweepLayer* s_share = NULL;

CcbSweepLayer* CcbSweepLayer::shareInstance()
{
    return s_share;
}

CcbSweepLayer::~CcbSweepLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonPlus);
	CC_SAFE_RELEASE_NULL(m_pControlButtonMinus);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCnt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergy);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftInfo);
    CC_SAFE_RELEASE_NULL(m_pSpriteTicket);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClear);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCostDaimond);
    CC_SAFE_RELEASE_NULL(m_pLabelCountDown);
    s_share = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSweepLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSweepLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSweepLayer", CcbSweepLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_bot.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSweepLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    s_share = this;
	return true;
}

void CcbSweepLayer::onEnter()
{
	CCLayer::onEnter();
    CGameSession::Attach(this);
    CGameSession::GetRole()->Detach(this);
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSweepLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSweepLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::GetRole()->Detach(this);
    CGameSession::Detach(this);
}

void CcbSweepLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSweepLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPlus", CCControlButton*, this->m_pControlButtonPlus);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMinus", CCControlButton*, this->m_pControlButtonMinus);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCnt", CCLabelTTF*, this->m_pLabelTTFCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftInfo", CCLabelTTF*, this->m_pLabelTTFLeftInfo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTicket", CCSprite*, this->m_pSpriteTicket);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClear", CCControlButton*, this->m_pControlButtonClear);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostDaimond", CCLabelTTF*, this->m_pLabelTTFCostDaimond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelCountDown", CCLabelTTF*, this->m_pLabelCountDown);
	return false;
}

bool CcbSweepLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSweepLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSweepLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSweepLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPlus", CcbSweepLayer::onPressControlButtonPlus);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMinus", CcbSweepLayer::onPressControlButtonMinus);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbSweepLayer::onPressControlButtonOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbSweepLayer::onPressControlButtonBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClear", CcbSweepLayer::onPressControlButtonClear);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSweepLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
    m_wStageId = stc.wStageId;
    
    uint8 byLastCnt = MAX_SWEEP_CNT;
    if (StageCtrl::Get()->kind() == 2)
    {
        byLastCnt = stc.byMaxAttCnt + stc.byBuyCnt - stc.byAttackCnt;
    }
    
    m_byCostEnergy = stc.byCostEnergy;
    CRole* pRole = CGameSession::GetRole();
    uint32 dwCurEnergy = pRole->GetdwEnergy();
    
    /*
     1. 最大值10
     2. 最大剩余次数(<10)
     3. 最大体力值(<10)
     */
    m_nMaxCnt = (byLastCnt * m_byCostEnergy < dwCurEnergy) ? byLastCnt : (dwCurEnergy / m_byCostEnergy);
    m_nMaxCnt = m_nMaxCnt > CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID) ? CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID) : m_nMaxCnt;
    m_nMaxCnt = m_nMaxCnt > MAX_SWEEP_CNT ? MAX_SWEEP_CNT : m_nMaxCnt;
    
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", m_nMaxCnt);
    m_pLabelTTFCnt->setString(strBuf64);
    
    int nCostAllEnergy = m_nMaxCnt * m_byCostEnergy;
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", nCostAllEnergy);
    m_pLabelTTFEnergy->setString(strBuf64);
    
    m_pControlButtonPlus->setEnabled(false);
    if (m_nMaxCnt == 0) {
        m_pControlButtonMinus->setEnabled(false);
    }
    m_pControlButtonOk->setEnabled(false);
    m_nCurCnt = m_nMaxCnt;
    
    int priority = kCCMenuHandlerPriority * 2 - 1;
    m_pControlButtonMinus->setTouchPriority(priority);
    m_pControlButtonBack->setTouchPriority(priority);
    m_pControlButtonOk->setTouchPriority(priority);
    m_pControlButtonPlus->setTouchPriority(priority);
    
    CCString* pString = CCString::createWithFormat("%d/%d",m_nCurCnt , CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID));
    m_pLabelTTFLeftInfo->setString(pString->getCString());
    
    
    m_pSpriteTicket->setTexture(CCTextureCache::sharedTextureCache()->addImage(CPacketDataMgr::Get()->GetItemIconByIndex(E_SWEEP_ITEM_ID).c_str()));
    
    m_pCountDown = ReCountDown::create(m_pLabelCountDown);
    this->addChild(m_pCountDown);
    m_pCountDown->setDelegate(this);
    m_pCountDown->setTime(pRole->GetdwSweepCDTime());
    m_pCountDown->startUpdateCountDown();
    m_pControlButtonClear->setTouchPriority(priority);
    
}

void CcbSweepLayer::refreashText()
{
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", m_nCurCnt);
    m_pLabelTTFCnt->setString(strBuf64);
    
    int nCostAllEnergy = m_nCurCnt * m_byCostEnergy;
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", nCostAllEnergy);
    m_pLabelTTFEnergy->setString(strBuf64);
}

void CcbSweepLayer::RefeashLayer()
{
    CRole *pRole = CGameSession::GetRole();
    m_pCountDown->setTime(pRole->GetdwSweepCDTime());
    m_pCountDown->startUpdateCountDown();
    m_pControlButtonOk->setEnabled(false);
    
}

void CcbSweepLayer::dwSweepCDTimeChanged(uint32 dwSweepCDTime)
{
    m_pCountDown->setTime(dwSweepCDTime);
    m_pCountDown->startUpdateCountDown();
    m_pControlButtonOk->setEnabled(false);
}

#pragma mark - Button Functions -
void CcbSweepLayer::onPressControlButtonPlus(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	m_nCurCnt++;
    if (m_nClearCDDollar == 0) {
        m_pControlButtonOk->setEnabled(true);
    }
    
    m_pControlButtonMinus->setEnabled(true);
    if (m_nCurCnt >= m_nMaxCnt) {
        m_pControlButtonPlus->setEnabled(false);
    }
    CCString* pString = CCString::createWithFormat("%d/%d",m_nCurCnt , CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID));
    m_pLabelTTFLeftInfo->setString(pString->getCString());
    
    refreashText();
}

void CcbSweepLayer::onPressControlButtonMinus(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	m_nCurCnt--;
    m_pControlButtonPlus->setEnabled(true);
    if (m_nCurCnt <= 0) {
        m_pControlButtonMinus->setEnabled(false);
        m_pControlButtonOk->setEnabled(false);
    }
    CCString* pString = CCString::createWithFormat("%d/%d",m_nCurCnt , CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID));
    m_pLabelTTFLeftInfo->setString(pString->getCString());
    
    refreashText();
}

void CcbSweepLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    removeFromParent();
    CRole*role = CGameSession::GetRole();
    STC_BATTLE_PRE_DATA perData;
    perData.wUserLv = role->GetwRoleLv();
    perData.dwCurExp = role->GetdwRoleExp();
    perData.dwCurEnergy = role->GetdwEnergy() - m_nCurCnt* StageCtrl::Get()->selectedStage().byCostEnergy;
    perData.byCurFightCnt = role->GetdwBattleBagCnt();
    FightAI::Get()->setPerData(perData);
    
    CGameSession::SendStageSweep(m_wStageId, StageCtrl::Get()->kind(), m_nCurCnt);
}

void CcbSweepLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	removeFromParent();
}

void CcbSweepLayer::onPressControlButtonClear(cocos2d::CCObject *pSender, CCControlEvent event)
{
    if (m_nClearCDDollar != 0) {
        CGameSession::SendClearSweepCDTime(ENUM_CLEARCD,m_nClearCDDollar);
    }
}

#pragma mark - Touch Functions -
void CcbSweepLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority * 2, true);
}

bool CcbSweepLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

#pragma mark - CountDown Functions -
void CcbSweepLayer::countDownScheduleCallBack(float cTime,CountType type)
{
    int nDollarMult = ceil(cTime / 60.0f);
    nDollarMult = nDollarMult > 5 ? 5 : nDollarMult;
    if (type == ENUM_COMPLETE)
    {
        m_pLabelCountDown->getParent()->setVisible(false);
        m_nClearCDDollar = 0;
        m_pControlButtonOk->setEnabled(true);
    }
    else if (type == ENUM_START)
    {
        m_pLabelCountDown->getParent()->setVisible(true);
        
        VipShowConfig::STC_VIP_SHOW_CONFIG* pVipShowCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
        
        if (pVipShowCfg && pVipShowCfg->bySweepCanClear == 1) {
            m_pControlButtonClear->getParent()->setVisible(true);
            m_nClearCDDollar = nDollarMult * WorldInfoDataMgr::Get()->getSweepCDDollar();
            m_pLabelTTFCostDaimond->setString(CCString::createWithFormat("X%d",m_nClearCDDollar)->getCString());
        }
        else
        {
            m_pControlButtonClear->getParent()->setVisible(false);
        }
    }
    else
    {
        if ((int)cTime % 60 == 0) {
            m_nClearCDDollar = nDollarMult * WorldInfoDataMgr::Get()->getSweepCDDollar();
            m_pLabelTTFCostDaimond->setString(CCString::createWithFormat("X%d",m_nClearCDDollar)->getCString());
        }
    }
    
    
}

#pragma mark - Receive Function -
void CcbSweepLayer::handlerClearSweepCDTimeResult(WorldPacket& packet)
{
    uint16 wError = 0;
    packet >> wError;
    if (wError != 0) {
        FlyTextLayer::showTips(GET_ERROR_STR(wError));
        return;
    }
    uint8 byType = 0;
    uint32 dwDollar = 0;
    packet >> byType >> dwDollar;
    if (byType == ENUM_CLEARCD) {
        m_nClearCDDollar = 0;
        m_pControlButtonOk->setEnabled(true);
        m_pLabelCountDown->getParent()->setVisible(false);
    }
    

}
