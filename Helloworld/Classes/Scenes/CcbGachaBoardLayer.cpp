#include "CcbGachaBoardLayer.h"
//#include "CcbManager.h"
#include "GachaDataMgr.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "PacketDataMgr.h"
#include "EnumDefines.h"
#include "MusicCtrl.h"
#include "Instruments.h"
#include "ResourceStringClient.h"
#include "BackCtrl.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "FlyTextLayer.h"
#include "CcbJumpTipLayer.h"
#include "GuideData.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define moveTime 120            //2秒

CcbGachaBoardLayer::~CcbGachaBoardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerPetScroll);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontTitle);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
	CC_SAFE_RELEASE_NULL(m_pControlButtonPreview);
	CC_SAFE_RELEASE_NULL(m_pControlButtonLeft);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRight);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTicket);
	CC_SAFE_RELEASE_NULL(m_pSpriteTicket);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTicket);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTicketDes);
	CC_SAFE_RELEASE_NULL(m_pNodeType1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTicketFreeTimes);
	CC_SAFE_RELEASE_NULL(m_pNodeType2);
	CC_SAFE_RELEASE_NULL(m_pNodeTicket);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOne);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTen);
	CC_SAFE_RELEASE_NULL(m_pSpriteText_ChaoZhi);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFOneDollar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTenDollar);
	CC_SAFE_RELEASE_NULL(m_pLabelBMFontLeftCnt);
	CC_SAFE_RELEASE_NULL(m_pNodeDiamond);
	CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
    CC_SAFE_RELEASE_NULL(m_pSpriteTextLastGet);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGachaBoardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGachaBoardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGachaBoardLayer", CcbGachaBoardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbGachaBoardLayer.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGachaBoardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbGachaBoardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideData::GetInstance()->onlyRmGuideLayer();
    }
    
    loadData();
}

void CcbGachaBoardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(CcbGachaBoardLayer::restoreTouch)),
                                 NULL
                                 )
              );
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
//        if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
//            GuideData::GetInstance()->setStepId(GuideData::E_GUIDE_TRIGGER_END_GACHA);
//        }
        
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonOne, GuideBtnPos::E_GACHA_ONCE);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonClose, GuideBtnPos::E_GACHA_BOARD_CLOSE);
        this->runAction(
                        CCSequence::create(
                                           CCDelayTime::create(0.1f),
                                           CCCallFunc::create(this, callfunc_selector(CcbGachaBoardLayer::addGuideLayer)),
                                           NULL
                                           )
                        );
    }
}

void CcbGachaBoardLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void CcbGachaBoardLayer::addGuideLayer() {
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_ONCE_GACHA,
//                                             GuideData::E_GUIDE_TRIGGER_6_GACHA,
                                             NULL
                                             );
}

void CcbGachaBoardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbGachaBoardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGachaBoardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetScroll", CCLayer*, this->m_pLayerPetScroll);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontTitle", CCLabelBMFont*, this->m_pLabelBMFontTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPreview", CCControlButton*, this->m_pControlButtonPreview);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLeft", CCControlButton*, this->m_pControlButtonLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRight", CCControlButton*, this->m_pControlButtonRight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTicket", CCControlButton*, this->m_pControlButtonTicket);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTicket", CCSprite*, this->m_pSpriteTicket);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTicket", CCLabelTTF*, this->m_pLabelTTFTicket);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTicketDes", CCLabelTTF*, this->m_pLabelTTFTicketDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeType1", CCNode*, this->m_pNodeType1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTicketFreeTimes", CCLabelTTF*, this->m_pLabelTTFTicketFreeTimes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeType2", CCNode*, this->m_pNodeType2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTicket", CCNode*, this->m_pNodeTicket);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOne", CCControlButton*, this->m_pControlButtonOne);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTen", CCControlButton*, this->m_pControlButtonTen);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteText_ChaoZhi", CCSprite*, this->m_pSpriteText_ChaoZhi);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFOneDollar", CCLabelTTF*, this->m_pLabelTTFOneDollar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTenDollar", CCLabelTTF*, this->m_pLabelTTFTenDollar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelBMFontLeftCnt", CCLabelBMFont*, this->m_pLabelBMFontLeftCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeDiamond", CCNode*, this->m_pNodeDiamond);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTextLastGet", CCSprite*, this->m_pSpriteTextLastGet);

	return false;
}

bool CcbGachaBoardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbGachaBoardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGachaBoardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGachaBoardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbGachaBoardLayer::onPressControlButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPreview", CcbGachaBoardLayer::onPressControlButtonPreview);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbGachaBoardLayer::onPressControlButtonLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbGachaBoardLayer::onPressControlButtonRight);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTicket", CcbGachaBoardLayer::onPressControlButtonTicket);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOne", CcbGachaBoardLayer::onPressControlButtonOne);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTen", CcbGachaBoardLayer::onPressControlButtonTen);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGachaBoardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_byType = 0;
    m_curMoveTime = 0;
    m_stopTime = 0;
    m_moveFlag = false;
    winSize = CCDirector::sharedDirector()->getWinSize();
    m_fMoveX = winSize.width / moveTime;
    
    m_fCurX = getWidth(m_pLayerPetScroll)*0.5;
    m_fPerX = m_fCurX + winSize.width;
    m_fNextX = m_fCurX - winSize.width;
    
    
//    m_pLayerPetScroll->setTag(101);
    m_layerRect.origin = getWorldPos(getChildByTag(101));
    m_layerRect.size = getChildByTag(101)->getContentSize();
    
    m_pControlButtonLeft->setTag(1);
    m_pControlButtonRight->setTag(2);
    
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pControlButtonPreview->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pControlButtonLeft->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pControlButtonRight->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pControlButtonTicket->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pControlButtonOne->setTouchPriority(kCCMenuHandlerPriority - 16);
    m_pControlButtonTen->setTouchPriority(kCCMenuHandlerPriority - 16);
    
    m_pLabelTTFTime->setString(GET_STR(Str_cur_free));
    
    m_pSpriteText_ChaoZhi->runAction(CCRepeatForever::create(
                                                             CCSequence::create(
                                                                                CCShow::create(),
                                                                                CCDelayTime::create(1.0),
                                                                                CCHide::create(),
                                                                                CCDelayTime::create(0.6),
                                                                                NULL)));
    
}



void CcbGachaBoardLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->setVisible(false);
    g_GachaData->setIsBoardOpen(false);
    
//    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
//        GuideData::GetInstance()->addGuideofEnum(
//                                                 GuideData::E_GUIDE_TRIGGER_END_GACHA,
//                                                 NULL
//                                                 );
//    }
}

void CcbGachaBoardLayer::onPressControlButtonPreview(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_GachaData->setGachaFlag(true);
    
    BackCtrl::InsertNextScene(kPetTujian);
}

void CcbGachaBoardLayer::onPressControlButtonLeft(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if(m_moveFlag)
    {
        return;
    }
    
    m_moveFlag = true;
    //已到位，暂停中,向后减一

    if (m_stopTime > 0) {
        arrPetPaint[1]->runAction(CCMoveTo::create(0.5, ccp(m_fNextX, getHeight(m_pLayerPetScroll)*0.5)));
        arrPetPaint[2]->runAction(CCSequence::create(
                                                     CCMoveTo::create(0.5, ccp(m_fCurX, getHeight(m_pLayerPetScroll)*0.5)),
                                                     CCCallFuncO::create(this, callfuncO_selector(CcbGachaBoardLayer::openTouch), pSender),
                                                     NULL));
    }
    else{
        arrPetPaint[0]->runAction(CCMoveTo::create(0.5, ccp(m_fNextX, getHeight(m_pLayerPetScroll)*0.5)));
        arrPetPaint[1]->runAction(CCMoveTo::create(0.5, ccp(m_fCurX, getHeight(m_pLayerPetScroll)*0.5)));
        arrPetPaint[2]->runAction(CCSequence::create(
                                                     CCMoveTo::create(0.5, ccp(m_fPerX, getHeight(m_pLayerPetScroll)*0.5)),
                                                     CCCallFuncO::create(this, callfuncO_selector(CcbGachaBoardLayer::openTouch), pSender),
                                                     NULL));
    }
    
    
}

void CcbGachaBoardLayer::onPressControlButtonRight(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if(m_moveFlag)
    {
        return;
    }
    
    m_moveFlag = true;
    //已到位，暂停中,向前加一
    arrPetPaint[0]->runAction(CCMoveTo::create(0.5, ccp(m_fCurX, getHeight(m_pLayerPetScroll)*0.5)));
    arrPetPaint[1]->runAction(CCSequence::create(
                                                 CCMoveTo::create(0.5, ccp(m_fPerX, getHeight(m_pLayerPetScroll)*0.5)),
                                                 CCCallFuncO::create(this, callfuncO_selector(CcbGachaBoardLayer::openTouch), pSender),
                                                 NULL));
}

void CcbGachaBoardLayer::onPressControlButtonTicket(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if ((m_dwFreeLeftTime > 0 || g_GachaData->getFreeCnt() == 0) && m_nTicketCnt <= 0) {
        PetLoadingLayer::sharedLayer()->End();
        FlyTextLayer::showTips(GET_STR(Str_ticket_not_enough));
        return;
    }
    CGachaDataMgr::Get()->setByIsTen(false);
    CGachaDataMgr::Get()->setByType(E_LOTTERY_TYPE_JUNIOR);
    CGameSession::SendReqLottery(CGachaDataMgr::Get()->byType(), CGachaDataMgr::Get()->byIsTen());
}

void CcbGachaBoardLayer::onPressControlButtonOne(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    CRole* role = CGameSession::GetRole();
    if (m_dwLeftTime > 0 && role->GetdwDollar() < g_GachaData->getOneDollar()) {
        CShowJumpTip::Get()->Show(E_DOLLAR_NOT_ENOUGH);
        return;
    }
    
    CGachaDataMgr::Get()->setByIsTen(false);
    CGachaDataMgr::Get()->setByType(E_LOTTERY_TYPE_SENIOR);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendReqLottery(CGachaDataMgr::Get()->byType(), CGachaDataMgr::Get()->byIsTen());
    // connect to server
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
        GuideData::GetInstance()->connectToServer();
    }
}

void CcbGachaBoardLayer::onPressControlButtonTen(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    CRole* role = CGameSession::GetRole();
    if (role->GetdwDollar() < g_GachaData->getTenDollar()) {
        CShowJumpTip::Get()->Show(E_DOLLAR_NOT_ENOUGH);
        return;
    }
    
    CGachaDataMgr::Get()->setByIsTen(true);
    CGachaDataMgr::Get()->setByType(E_LOTTERY_TYPE_SENIOR);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendReqLottery(CGachaDataMgr::Get()->byType(), CGachaDataMgr::Get()->byIsTen());

}


void CcbGachaBoardLayer::loadData()
{
    //劵
    m_nTicketCnt = g_PacketDataMgr->GetItemCountByIndex(E_LOTTERY_JUNIOR_ITEM_ID);
    CCString* str = CCString::createWithFormat("%d", m_nTicketCnt);
    m_pLabelTTFTicket->setString(str->getCString());
    
    if (m_nTicketCnt > 0) {
        str->initWithFormat(GET_STR(Str_use_ticket), MIN(m_nTicketCnt, 10), MIN(m_nTicketCnt, 10));
        m_pLabelTTFTicketDes->setString(str->getCString());
    }
    else{
        m_pLabelTTFTicketDes->setString(GET_STR(Str_no_ticket));
    }
    
    //钻石
    str->initWithFormat("%d", g_GachaData->getOneDollar());
    m_pLabelTTFOneDollar->setString(str->getCString());
    
    str->initWithFormat("%d", g_GachaData->getTenDollar());
    m_pLabelTTFTenDollar->setString(str->getCString());
    
    str->initWithFormat("%d", g_GachaData->getDollarLeftCnt());
    m_pLabelBMFontLeftCnt->setString(str->getCString());

    m_pLabelBMFontLeftCnt->getParent()->setVisible(g_GachaData->getDollarLeftCnt() > 0);
    m_pSpriteTextLastGet->setVisible(g_GachaData->getDollarLeftCnt() == 0);
}

void CcbGachaBoardLayer::setCDTime(uint32 dwLeftTime, uint32 dwFreeLeftTime)
{
    m_dwLeftTime = dwLeftTime;
    m_dwFreeLeftTime = dwFreeLeftTime;
    
    if (m_dwLeftTime > 0) {
        schedule(schedule_selector(CcbGachaBoardLayer::updateTime), 1.0f);
        m_pLabelTTFTime->setVisible(false);
        m_pLabelTTFOneDollar->getParent()->setVisible(true);
    } else {
        m_pLabelTTFTime->setVisible(true);
        m_pLabelTTFOneDollar->getParent()->setVisible(false);
    }
    
    if (m_dwFreeLeftTime > 0) {
        m_pLabelTTFTicketFreeTimes->setString(getLeftTimeFromInt(m_dwFreeLeftTime)->getCString());
        schedule(schedule_selector(CcbGachaBoardLayer::updateTime), 1.0f);
    }
    else{
        if(g_GachaData->getFreeCnt() > 0)
        {
            m_pLabelTTFTicketFreeTimes->setString(CCString::createWithFormat(GET_STR(Str_ticket_free_cnt), g_GachaData->getFreeCnt(), g_GachaData->getFreeCntMax())->getCString());
        }
        else{
            m_pLabelTTFTicketFreeTimes->setString(GET_STR(Str_no_ticket_free));
        }
    }
}
void CcbGachaBoardLayer::updateTime(float cTime)
{
    if (m_dwLeftTime > 0) {
        m_dwLeftTime--;
        m_pLabelTTFTime->setVisible(false);
        m_pLabelTTFOneDollar->getParent()->setVisible(true);
    } else {
        m_pLabelTTFTime->setVisible(true);
        m_pLabelTTFOneDollar->getParent()->setVisible(false);
    }
    
    if (m_dwFreeLeftTime > 0) {
        m_dwFreeLeftTime--;
        m_pLabelTTFTicketFreeTimes->setString(getLeftTimeFromInt(m_dwFreeLeftTime)->getCString());
    } else {
        if(g_GachaData->getFreeCnt() > 0)
        {
            m_pLabelTTFTicketFreeTimes->setString(CCString::createWithFormat(GET_STR(Str_ticket_free_cnt), g_GachaData->getFreeCnt(), g_GachaData->getFreeCntMax())->getCString());
        }
        else{
            m_pLabelTTFTicketFreeTimes->setString(GET_STR(Str_no_ticket_free));
        }
    }
    
    if (m_dwLeftTime <= 0 && m_dwFreeLeftTime <= 0){
        unschedule(schedule_selector(CcbGachaBoardLayer::updateTime));
    }
}

void CcbGachaBoardLayer::onShow()
{
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbGachaBoardLayer::afterAnimationFinishedCallBack));
//    mAnimationManager->runAnimationsForSequenceNamed("act_show");
    g_GachaData->setIsBoardOpen(true);
    if (m_byType == g_GachaData->byType()) {
        
        arrPetPaint[0]->setPosition(ccp(m_fNextX, getHeight(m_pLayerPetScroll)*0.5));
        arrPetPaint[1]->setPosition(ccp(m_fCurX, getHeight(m_pLayerPetScroll)*0.5));
        arrPetPaint[2]->setPosition(ccp(m_fPerX, getHeight(m_pLayerPetScroll)*0.5));
        m_stopTime = 30;
        m_curMoveTime = 0;
//        arrPetPaint[0]->setVisible(false);
//        arrPetPaint[2]->setVisible(false);
        
        setVisible(true);
        return;
    }
    
    m_byType = g_GachaData->byType();
    if (m_byType == E_LOTTERY_TYPE_JUNIOR) {
        m_pLabelBMFontTitle->setString(GET_STR(Str_gacha_normal));
        m_pControlButtonTicket->getParent()->setVisible(true);
        m_pControlButtonOne->getParent()->setVisible(false);
    }
    else{
        m_pLabelBMFontTitle->setString(GET_STR(Str_gacha_dollar));
        m_pControlButtonTicket->getParent()->setVisible(false);
        m_pControlButtonOne->getParent()->setVisible(true);
    }
    
    loadPet();
    
    setVisible(true);
}

void CcbGachaBoardLayer::afterAnimationFinishedCallBack()
{
//    mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
//    arrPetPaint[0]->setVisible(true);
//    arrPetPaint[2]->setVisible(true);
    
//    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
//        if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_GUIDE_TRIGGER_3_GACHA) {
//            GuideData::GetInstance()->setStepId(GuideData::E_GUIDE_TRIGGER_6_GACHA);
//        }
//        
//        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonOne, GuideBtnPos::E_GACHA_ONCE);
//        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonClose, GuideBtnPos::E_GACHA_BOARD_CLOSE);
//        this->runAction(
//                        CCSequence::create(
//                                           CCDelayTime::create(0.1f),
//                                           CCCallFunc::create(this, callfunc_selector(CcbGachaBoardLayer::addGuideLayer)),
//                                           NULL
//                                           )
//                        );
//    }
}

void CcbGachaBoardLayer::loadPet()
{
    arrCurShowPet.clear();
    m_stopTime = 30;
    if (g_GachaData->byType() == E_LOTTERY_TYPE_JUNIOR) {
        arrCurShowPet = g_GachaData->getAllTicketPet();
    }
    else{
        arrCurShowPet = g_GachaData->getAllDollarPet();
    }
    m_curPage = 0;
    uint16 curId = CPetCtrl::Get()->getPetTujianShowId();
    if (curId != 0) {
        for (int i = 0; i < arrCurShowPet.size(); i++) {
            if (curId == arrCurShowPet[i]) {
                
                m_curPage = i;
                break;
            }
        }
    }
    curId = arrCurShowPet[m_curPage];
    //初始化三张图
    if (!m_petPaintCur) {
        m_petPaintCur = CCSprite::createWithTexture(CPetCtrl::Get()->GetPetBodyTexture(curId));
        m_pLayerPetScroll->addChild(m_petPaintCur);
    }
    else{
        m_petPaintCur->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(curId));
    }
    m_petPaintCur->setPosition(ccp(m_fCurX, getHeight(m_pLayerPetScroll)*0.5));
    
    int perPage = m_curPage - 1;
    if (perPage < 0)
    {
        perPage += arrCurShowPet.size();
    }
    uint16 perId = arrCurShowPet[perPage];
    if (!m_petPaintPer) {
        m_petPaintPer = CCSprite::createWithTexture(CPetCtrl::Get()->GetPetBodyTexture(perId));
        m_pLayerPetScroll->addChild(m_petPaintPer);
    }
    else{
        m_petPaintPer->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(perId));
    }
    m_petPaintPer->setPosition(ccp(m_fPerX, getHeight(m_pLayerPetScroll)*0.5));
    

    int nextPage = m_curPage + 1;
    if (nextPage > arrCurShowPet.size() - 1)
    {
        nextPage = nextPage % arrCurShowPet.size();
    }
    uint16 nextId = arrCurShowPet[nextPage];
    
    if (!m_petPaintNext) {
        m_petPaintNext = CCSprite::createWithTexture(CPetCtrl::Get()->GetPetBodyTexture(nextId));
        m_pLayerPetScroll->addChild(m_petPaintNext);
    }
    else{
        m_petPaintNext->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(nextId));
    }
    m_petPaintNext->setPosition(ccp(m_fNextX, getHeight(m_pLayerPetScroll)*0.5));
    
    arrPetPaint[0] = m_petPaintNext;
    arrPetPaint[1] = m_petPaintCur;
    arrPetPaint[2] = m_petPaintPer;
    
//    arrPetPaint[0]->setVisible(false);
//    arrPetPaint[2]->setVisible(false);
    
    setPetStar();
    unschedule(schedule_selector(CcbGachaBoardLayer::updateForMove));
    m_curMoveTime = 0;
    schedule(schedule_selector(CcbGachaBoardLayer::updateForMove));
}

void CcbGachaBoardLayer::setPetStar()
{
    uint16 curId = arrCurShowPet[m_curPage];
    PetConfig::STC_PET_CONFIG * cfg = GET_CONFIG_STC(PetConfig, curId);
    if (cfg) {
        //星级}
        m_pSpriteLvStar->removeAllChildren();
        m_pSpriteLvStar->setContentSize(CCSizeMake(m_pSpriteLvStar->getTexture()->getContentSize().width, getHeight(m_pSpriteLvStar)));
        for (int i = 1; i < cfg->byStarLv; i++) {
            CCSprite *star = CCSprite::createWithTexture(m_pSpriteLvStar->getTexture());
            m_pSpriteLvStar->setContentSize(star->getContentSize());
            star->setAnchorPoint(ccp(0, 0));
            star->setPosition(ccp(i*(getWidth(star) + 1), 0));
            m_pSpriteLvStar->addChild(star);
        }
        m_pSpriteLvStar->setContentSize(CCSizeMake((getWidth(m_pSpriteLvStar)+1)*cfg->byStarLv, getHeight(m_pSpriteLvStar)));
    }
}

void CcbGachaBoardLayer::changePage(int off)
{
    CCSprite* petPer = arrPetPaint[2];
    CCSprite* petCur = arrPetPaint[1];
    CCSprite* petNext = arrPetPaint[0];

    m_curPage = (m_curPage + arrCurShowPet.size() + off) % arrCurShowPet.size();
    
    int nextPage = (m_curPage+ arrCurShowPet.size() + off) % arrCurShowPet.size();
    
    uint16 nextId = arrCurShowPet[nextPage];
    
    setPetStar();
    if (off > 0) {
        petPer->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(nextId));
        petPer->setPosition(ccp(m_fNextX, getHeight(m_pLayerPetScroll)*0.5));
        arrPetPaint[0] = petPer;
        arrPetPaint[1] = petNext;
        arrPetPaint[2] = petCur;
    }
    else{
        petNext->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(nextId));
        petNext->setPosition(ccp(m_fPerX, getHeight(m_pLayerPetScroll)*0.5));
        arrPetPaint[0] = petCur;
        arrPetPaint[1] = petPer;
        arrPetPaint[2] = petNext;
    }
}

void CcbGachaBoardLayer::updateForMove(float cTime)
{
    if (m_moveFlag) {
        return;
    }
    
    if (m_stopTime > 0) {
        m_stopTime--;
        return;
    }
    
    if (m_curMoveTime < moveTime) {
        m_curMoveTime++;
        for (int i = 0; i < 3; i++) {
            arrPetPaint[i]->setPositionX(arrPetPaint[i]->getPositionX() + m_fMoveX);
        }
    }
    else{
        //走完一张了,停顿半秒
        m_stopTime = 30;
        m_curMoveTime = 0;
        changePage(1);
    }
}

void CcbGachaBoardLayer::openTouch(CCObject* node)
{
    int tag = ((CCNode*)node)->getTag();
    if (tag == 1 && m_stopTime > 0) {
        changePage(-1);
    }
    else if(tag == 2){
        changePage(1);
    }
    m_moveFlag = false;
    m_curMoveTime = 0;
    m_stopTime = 30;
}

bool CcbGachaBoardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!isVisible()) {
        return false;
    }
    CCPoint p = this->convertToWorldSpace(pTouch->getLocation());
    m_tTouchPoint = p;//this->convertTouchToNodeSpace(pTouch);
    m_fTouchLength = 0.0f;
    
    return true;
}

void CcbGachaBoardLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPointNow = this->convertTouchToNodeSpace(pTouch);
    //    CCLog("touchPointNow.x %f", touchPointNow.y);
    m_fTouchLength = touchPointNow.x - m_tTouchPoint.x;
    m_fTouchHeight = touchPointNow.y - m_tTouchPoint.y;
}

void CcbGachaBoardLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    const float fOffset = 25.0f;
#else
    const float fOffset = 15.0f;
#endif
    if (!m_bCanTouchBtn) {
        return;
    }
    
    if (m_moveFlag) {
        return;
    }
    
    if (m_fTouchLength > fOffset || m_fTouchHeight > fOffset) {
        return;
    }
    
    CCRect rect;
    CCPoint p = this->convertToWorldSpace(pTouch->getLocation());
    
    rect.origin = getWorldPos(m_pLayerPetScroll);
    rect.size = m_pLayerPetScroll->getContentSize();
    if (!rect.containsPoint(p)) {
        return;
    }
    
    for ( int i = 0; i < 3; i++) {
        CCNode* node = arrPetPaint[i];
        if (!node || !node->isVisible()) {
            continue;
        }
        rect.origin = getWorldPos(node);
        rect.size = node->getContentSize();
        if (rect.containsPoint(p)) {
            
            CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
            uint16 page = m_curPage + 1 - i;
            page = (page + arrCurShowPet.size()) % arrCurShowPet.size();
            CPetCtrl::Get()->setPetTujianShowId(arrCurShowPet[page]);
            BackCtrl::InsertNextScene(kShowPetTujian);
            return;
        }
    }
    
}


void CcbGachaBoardLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 15, true);
}

#pragma mark - Visit Function -
void CcbGachaBoardLayer::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!m_bVisible)
    {
        return;
    }
    kmGLPushMatrix();
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
    }
    
    this->transform();
    
    CCNode* pNode = NULL;
    unsigned int i = 0;
    
    if(m_pChildren && m_pChildren->count() > 0)
    {
        sortAllChildren();
        // draw children zOrder < 0
        ccArray *arrayData = m_pChildren->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            
            if ( pNode && pNode->getZOrder() < 0 )
            {
                if (pNode->getTag() == 101) {
                    //     kmGLPushMatrix();
                    glEnable(GL_SCISSOR_TEST);
                    CCEGLView::sharedOpenGLView()->setScissorInPoints(m_layerRect.origin.x, m_layerRect.origin.y, m_layerRect.size.width, m_layerRect.size.height);
                    pNode->visit();
                    glDisable(GL_SCISSOR_TEST);
                    //    kmGLPopMatrix();
                }else
                    pNode->visit();
            }
            else
            {
                break;
            }
        }
        // self draw
        this->draw();
        
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            if (pNode)
            {
                if (pNode->getTag() == 101)
                {
                    kmGLPushMatrix();
                    glEnable(GL_SCISSOR_TEST);
                    CCEGLView::sharedOpenGLView()->setScissorInPoints(m_layerRect.origin.x, m_layerRect.origin.y, m_layerRect.size.width, m_layerRect.size.height);
                    pNode->visit();
                    glDisable(GL_SCISSOR_TEST);
                    kmGLPopMatrix();
                }else
                    pNode->visit();
            }
        }
    }
    else
    {
        this->draw();
    }
    
    // reset for next frame
    m_uOrderOfArrival = 0;
    
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }
    
    kmGLPopMatrix();
}