#include "CcbNewGachaLayer.h"
#include "CcbManager.h"
#include "GachaDataMgr.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "MusicCtrl.h"
#include "GlobalData.h"
#include "PacketDataMgr.h"
#include "FlyTextLayer.h"
#include "Instruments.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "ResourceMusic.h"
#include "GuideData.h"
#include "ShopDataMgr.h"
#include "GuideBtnPos.h"
#include "EnumDefines.h"
#include "CcbGachaBoardLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

static CcbNewGachaLayer* m_shared = NULL;

CcbNewGachaLayer::~CcbNewGachaLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonGoCharge);
    CC_SAFE_RELEASE_NULL(m_pControlButtonTicket);
    CC_SAFE_RELEASE_NULL(m_pSpriteTicket);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTicket);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFFreeTimes);
    CC_SAFE_RELEASE_NULL(m_pNodeFree);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip1);
    CC_SAFE_RELEASE_NULL(m_pControlButtonDiamond);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip2);
}

//-- copy this to CcbManager
/*
//CcbManager.h
CCNode* LoadCcbNewGachaLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbNewGachaLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbNewGachaLayer", CcbNewGachaLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_new.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbNewGachaLayer* CcbNewGachaLayer::GetCurScene() {
    return m_shared;
}

bool CcbNewGachaLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
	return true;
}

void CcbNewGachaLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    g_GachaData->ClearGachaPet();
    CGameSession::SendLotteryInfo();
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonDiamond, GuideBtnPos::E_GACHA_ADV_FREE);
    }
}

void CcbNewGachaLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction( CCSequence::create(
                                        CCDelayTime::create(0.1f),
                                        CCCallFunc::create(this, callfunc_selector(CcbNewGachaLayer::addGuideLayer)),
                                        NULL
                                        )
                    );
}

void CcbNewGachaLayer::onExit()
{
    m_shared = NULL;
	CCLayer::onExit();
}

void CcbNewGachaLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbNewGachaLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
        GuideData::GetInstance()->setStepId(GuideData::E_GUIDE_TRIGGER_END_GACHA);
    }
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_1_GACHA,
                                             GuideData::E_GUIDE_TRIGGER_END_GACHA,
                                             NULL
                                             );
}

// Inhert MemberVariableAssigner
bool CcbNewGachaLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGoCharge", CCControlButton*, this->m_pControlButtonGoCharge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTicket", CCControlButton*, this->m_pControlButtonTicket);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTicket", CCSprite*, this->m_pSpriteTicket);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTicket", CCLabelTTF*, this->m_pLabelTTFTicket);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFreeTimes", CCLabelTTF*, this->m_pLabelTTFFreeTimes);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeFree", CCNode*, this->m_pNodeFree);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip1", CCSprite*, this->m_pSpriteTip1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDiamond", CCControlButton*, this->m_pControlButtonDiamond);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip2", CCSprite*, this->m_pSpriteTip2);
	return false;
}

bool CcbNewGachaLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbNewGachaLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbNewGachaLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbNewGachaLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGoCharge", CcbNewGachaLayer::onPressControlButtonGoCharge);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTicket", CcbNewGachaLayer::onPressControlButtonTicket);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDiamond", CcbNewGachaLayer::onPressControlButtonDiamond);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbNewGachaLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
   
    m_pControlButtonDiamond->setZoomWithParent(true);
    m_pControlButtonTicket->setZoomWithParent(true);
    
    m_nTicketCnt = g_PacketDataMgr->GetItemCountByIndex(E_LOTTERY_JUNIOR_ITEM_ID);
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", m_nTicketCnt);
    m_pLabelTTFTicket->setString(strBuf64);
}

#pragma mark Private Method
void CcbNewGachaLayer::onPressControlButtonGoCharge(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    g_ShopData->SetCurShopShowType(1);
    CGameSession::SendRequestStorePayList();
}

void CcbNewGachaLayer::onPressControlButtonTicket(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_GachaData->setByType(E_LOTTERY_TYPE_JUNIOR);
    showGachaBoard();
}

void CcbNewGachaLayer::onPressControlButtonDiamond(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_GachaData->setByType(E_LOTTERY_TYPE_SENIOR);
    showGachaBoard();
}

void CcbNewGachaLayer::loadData()
{
    //奖券抽
    //CD
    m_dwFreeLeftTime = g_GachaData->getFreeLeftTime();
    setFreeLeftTime();
    
    //钻石抽
    m_dwLeftTime = g_GachaData->dwLeftTime();
    setLeftTime();
    
//    if (g_GachaData->getIsBoardOpen()) {
//        showGachaBoard();
//    }
}

void CcbNewGachaLayer::changeToFree()
{
    m_pLabelTTFTime->setString(GET_STR(Str_cur_free));
}

void CcbNewGachaLayer::updateTime(float cTime)
{
    if (m_dwLeftTime > 0) {
        m_dwLeftTime--;
        m_pLabelTTFTime->setString(getLeftTimeFromInt(m_dwLeftTime)->getCString());
    } else {
        m_pLabelTTFTime->setString(GET_STR(Str_cur_free));
        m_pSpriteTip2->setVisible(true);
    }
    
    if (m_dwFreeLeftTime > 0) {
        m_dwFreeLeftTime--;
        m_pLabelTTFFreeTimes->setString(getLeftTimeFromInt(m_dwFreeLeftTime)->getCString());
    } else {
        if(g_GachaData->getFreeCnt() > 0)
        {
            m_pSpriteTip1->setVisible(true);
            m_pLabelTTFFreeTimes->setString(CCString::createWithFormat(GET_STR(Str_ticket_free_cnt), g_GachaData->getFreeCnt(), g_GachaData->getFreeCntMax())->getCString());
        }
        else{
            m_pLabelTTFFreeTimes->setString(GET_STR(Str_no_ticket_free));
        }
    }
    
    if (m_dwLeftTime <= 0 && m_dwFreeLeftTime <= 0){
        unschedule(schedule_selector(CcbNewGachaLayer::updateTime));
    }
}

void CcbNewGachaLayer::setLeftTime()
{
    unschedule(schedule_selector(CcbNewGachaLayer::updateTime));
    if (m_dwLeftTime > 0) {
        m_pSpriteTip2->setVisible(false);
        m_pLabelTTFTime->setString(getLeftTimeFromInt(m_dwLeftTime)->getCString());
        schedule(schedule_selector(CcbNewGachaLayer::updateTime), 1.0f);
    }
    else{
        m_pSpriteTip2->setVisible(true);
        m_pLabelTTFTime->setString(GET_STR(Str_cur_free));
    }
}

void CcbNewGachaLayer::setFreeLeftTime()
{
    unschedule(schedule_selector(CcbNewGachaLayer::updateTime));
    m_pSpriteTip1->setVisible(false);
    if (m_dwFreeLeftTime > 0) {
        m_pLabelTTFFreeTimes->setString(getLeftTimeFromInt(m_dwFreeLeftTime)->getCString());
        schedule(schedule_selector(CcbNewGachaLayer::updateTime), 1.0f);
    }
    else{
        if(g_GachaData->getFreeCnt() > 0)
        {
            m_pSpriteTip1->setVisible(true);
            m_pLabelTTFFreeTimes->setString(CCString::createWithFormat(GET_STR(Str_ticket_free_cnt), g_GachaData->getFreeCnt(), g_GachaData->getFreeCntMax())->getCString());
        }
        else{
            m_pLabelTTFFreeTimes->setString(GET_STR(Str_no_ticket_free));
        }
    }
}

void CcbNewGachaLayer::showGachaBoard()
{
    if (!m_GachaBoardLayer) {
        m_GachaBoardLayer = dynamic_cast<CcbGachaBoardLayer*>(CcbManager::sharedManager()->LoadCcbGachaBoardLayer());
        addChild(m_GachaBoardLayer, 99);
    }
    m_GachaBoardLayer->onShow();
    m_GachaBoardLayer->setCDTime(m_dwLeftTime, m_dwFreeLeftTime);
}

#pragma Public Method
void CcbNewGachaLayer::handlerDollarShow(uint32 dwDollar) {
    if (dwDollar > 0) { // 花钱，跳提示框}
        PetLoadingLayer::sharedLayer()->End();
        CCString* strHint = CCString::createWithFormat( GET_STR(Str_gacha_tip), dwDollar );
        SystemMessage::showSystemMessage(1, this, strHint->getCString(), this, false, 1, GET_STR(Str_warning));
    } else {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendReqLottery(CGachaDataMgr::Get()->byType(), CGachaDataMgr::Get()->byIsTen());
        if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
            GuideData::GetInstance()->connectToServer();        // Send 803 to server
        }
    }
}

void CcbNewGachaLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendReqLottery(CGachaDataMgr::Get()->byType(), CGachaDataMgr::Get()->byIsTen());
}



