#include "CcbTowerMainLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "TowerDataMgr.h"
#include "CcbTowerRewardListLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "BackCtrl.h"
#include "Role.h"
#include "FlyTextLayer.h"
#include "SystemMessage.h"
#include "GlobalData.h"
#include "CcbTowerMainScene.h"
#include "Instruments.h"
#include "GuideBtnPos.h"
#include "CcbJumpTipLayer.h"
#include "MainBottomInnerLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbTowerMainLayer::~CcbTowerMainLayer()
{
    m_curScene = NULL;
	CC_SAFE_RELEASE_NULL(m_pSpriteBg);
	CC_SAFE_RELEASE_NULL(m_pSpritePet_1);
	CC_SAFE_RELEASE_NULL(m_pSpritePet_2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGo);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReset);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSweep);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
	CC_SAFE_RELEASE_NULL(m_pLayerTime);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFlood);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMissionDesc);
	CC_SAFE_RELEASE_NULL(m_pSpriteHeart);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBox);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRank);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTowerMainLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTowerMainLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTowerMainLayer", CcbTowerMainLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_main.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbTowerMainLayer* CcbTowerMainLayer::m_curScene = NULL;

bool CcbTowerMainLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
	return true;
}

void CcbTowerMainLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
    
    g_TowerDataMgr->SetEnterTowerState(false);
    schedule(schedule_selector(CcbTowerMainLayer::onUpdate));
}

void CcbTowerMainLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction( CCSequence::create(
                                        CCDelayTime::create(0.1f),
                                        CCCallFunc::create(this, callfunc_selector(CcbTowerMainLayer::addGuideLayer)),
                                        NULL
                                        ) );
}

void CcbTowerMainLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonGo, GuideBtnPos::E_GO_TOWER);
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_3_TOWER,
                                                 GuideData::E_SYS_GUIDE_4_TOWER,
                                                 NULL
                                                 );
    }
}

void CcbTowerMainLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTowerMainLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTowerMainLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
    
//    if (pTarget == this && 0 == strcmp(pMemberVariableName, "m_pSpriteBg")) {
//        CCSprite* pOldVar = this->m_pSpriteBg;
//        this->m_pSpriteBg = dynamic_cast<CCSprite*>(pNode);
//        CC_ASSERT(this->m_pSpriteBg);
//        if (pOldVar != this->m_pSpriteBg) {
//            CC_SAFE_RELEASE(pOldVar);
//            this->m_pSpriteBg->retain();
//        }
//        return true; 
//    }
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet_1", CCSprite*, this->m_pSpritePet_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePet_2", CCSprite*, this->m_pSpritePet_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGo", CCControlButton*, this->m_pControlButtonGo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReset", CCControlButton*, this->m_pControlButtonReset);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSweep", CCControlButton*, this->m_pControlButtonSweep);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTime", CCLayer*, this->m_pLayerTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFlood", CCLabelTTF*, this->m_pLabelTTFFlood);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMissionDesc", CCLabelTTF*, this->m_pLabelTTFMissionDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHeart", CCSprite*, this->m_pSpriteHeart);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBox", CCControlButton*, this->m_pControlButtonBox);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRank", CCControlButton*, this->m_pControlButtonRank);

	return false;
}

bool CcbTowerMainLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTowerMainLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTowerMainLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTowerMainLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGo", CcbTowerMainLayer::onPressControlButtonGo);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReset", CcbTowerMainLayer::onPressControlButtonReset);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSweep", CcbTowerMainLayer::onPressControlButtonSweep);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbTowerMainLayer::onPressControlButtonBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBox", CcbTowerMainLayer::onPressControlButtonBox);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRank", CcbTowerMainLayer::onPressControlButtonRank);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTowerMainLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pLabelTTFTime->setString(GET_STR(Str_time_zero));
    m_pSpritePet_1->setVisible(false);
    m_pSpritePet_2->setVisible(false);
    CreateData();
}

void CcbTowerMainLayer::CreateData()
{
    TOWER_INFO showInfo = g_TowerDataMgr->GetTowerInfo();
    //当前层数}
    char szTemp[32] = "";
    sprintf(szTemp, GET_STR(Str_dijiceng), showInfo.dwCurFloor );
    m_pLabelTTFFlood->setString(szTemp);
    g_TowerDataMgr->SetCurBattleFloor(showInfo.dwCurFloor);
    
    //宠物原画}
    string strPicName = g_TowerDataMgr->GetPetBodyPicName(showInfo.dwCurFloor);
    CCTexture2D* t2d = CCTextureCache::sharedTextureCache()->addImage(strPicName.c_str());
    if (t2d) {
        m_pSpritePet_1->initWithTexture(t2d);
        m_pSpritePet_2->initWithTexture(t2d);
        m_pSpritePet_1->setAnchorPoint(ccp(0.5, 0));
        m_pSpritePet_2->setAnchorPoint(ccp(0.5, 0));
    }
    
    //通关条件}
    m_pLabelTTFMissionDesc->setString(g_TowerDataMgr->GetDescByIndex(showInfo.dwCurFloor).c_str());
    
    //挑战次数}
    for (int i = 0; i < 5; i++)
    {
        m_pSpriteHeart->getParent()->removeChildByTag(100 + i);
    }
    m_pSpriteHeart->setOpacity(0);
    for (int i = 0; i < showInfo.byLeftFightCnt; i++)
    {
        CCSprite* pSprite = CCSprite::createWithTexture(m_pSpriteHeart->getTexture());
        pSprite->setPosition(ccp(m_pSpriteHeart->getPositionX() + 20 * i, m_pSpriteHeart->getPositionY()));
        m_pSpriteHeart->getParent()->addChild(pSprite, 1, 100 + i);
    }
    
    //重置}
    m_pControlButtonReset->setTitleForState(CCString::createWithFormat("%s(%d)", GET_STR(Str_reset), MAX(showInfo.byMaxResetCnt - showInfo.byHasResetCnt, 0) ),
                                            CCControlStateNormal);
    
    //扫荡时间}
    if (showInfo.dwLeftTime > g_TowerDataMgr->GetLostTime())
    {
        m_dwLeftTime = showInfo.dwLeftTime - g_TowerDataMgr->GetLostTime();
        m_pLayerTime->setVisible(true);
        m_pControlButtonGo->setEnabled(false);
        
        m_pControlButtonReset->setEnabled(false);
        m_pControlButtonSweep->setEnabled(false);
    }
    else
    {
        m_dwLeftTime = 0;
        m_pLayerTime->setVisible(false);
        m_pControlButtonGo->setEnabled(true);
        
        m_pControlButtonReset->setEnabled(true);
        m_pControlButtonSweep->setEnabled(true);
    }
    
    if (showInfo.byLeftFightCnt == 0) {
        m_pControlButtonGo->setEnabled(false);
    }
}

void CcbTowerMainLayer::RefreshData()
{
    CreateData();
}

void CcbTowerMainLayer::onPressControlButtonGo(CCObject* pSender, CCControlEvent event)
{
    if (CGameSession::GetRole()->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_4_TOWER) {
        GuideData::GetInstance()->onlyRmGuideLayer();
    }
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_pControlButtonGo->setVisible(false);
    onRoad();
}

void CcbTowerMainLayer::onPressControlButtonSweep(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    SystemMessage::showSystemMessage(1, NULL, GET_STR(Str_towe_sweep), CcbTowerMainScene::getCurScene(), true, 2);
}

void CcbTowerMainLayer::onPressControlButtonReset(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    TOWER_INFO showInfo = g_TowerDataMgr->GetTowerInfo();
    if (showInfo.byHasResetCnt == 0) {
        CGameSession::SendResetTowerFloor();
    } else {
        VipShowConfig::STC_VIP_SHOW_CONFIG* pVipShowCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
        if (pVipShowCfg->wTowerResetMax >= showInfo.byHasResetCnt) {
            // 可以重置
            VipBuyConfig::STC_CONFIG_VIP_BUY* pVipBuyCfg = GET_CONFIG_STC(VipBuyConfig, showInfo.byHasResetCnt);
            
            CCString* pStr = CCString::createWithFormat("%s\n%s", GET_STR(Str_buy_tower_reset), GET_STR(Str_today_left));
            snprintf(strBuf512, BUFFER_SIZE_512, pStr->getCString(), pVipBuyCfg->wTower, pVipShowCfg->wTowerResetMax - showInfo.byHasResetCnt + 1);
            SystemMessage::showSystemMessage(1, NULL, strBuf512, CcbTowerMainScene::getCurScene(), true, 1);
        } else {
            CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
            return;
        }
    }
}

void CcbTowerMainLayer::onPressControlButtonBox(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));

    CCNode *pLayer = CcbManager::sharedManager()->LoadCcbTowerRewardListLayer(this);
    if (getChildByTag(111))
    {
        removeChildByTag(111);
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pLayer->setPosition(winSize*0.5);
    pLayer->ignoreAnchorPointForPosition(false);
    pLayer->setAnchorPoint(ccp(0.5, 0.5));
    addChild(pLayer, 100, 111);
}

void CcbTowerMainLayer::onPressControlButtonRank(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    CGameSession::SendRequestTowerRank();
}

void CcbTowerMainLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    BackCtrl::BacktoUpperScene();
}

void CcbTowerMainLayer::onUpdate(float delta)
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
        //qqqqqqqqqqqqq其实有个通用接口转换时间的getLeftTimeFromInt(cdTime)  #include "CcbChallengeLayer.h"}

        CCString* strTime = getLeftTimeFromInt(m_dwLeftTime);//CString::createWithFormat("%s:%s:%s", strHour->getCString(), strMin->getCString(), strSec->getCString());
        
        m_pLabelTTFTime->setString(strTime->getCString());
        
        if (m_dwLeftTime % 15 == 0)
        {
            CGameSession::SendRequestTowerInfo();
        }
        
        if (m_dwLeftTime == 0)
        {
            m_pLayerTime->setVisible(false);
            m_pControlButtonGo->setEnabled(true);
        }
    }
}

void CcbTowerMainLayer::onRoad()
{
    m_bCanTouchBtn = false;
    if (MainBottomInnerLayer::GetInstance()) {
        MainBottomInnerLayer::GetInstance()->setBtnTouchEnable(false);
    }
    mAnimationManager->runAnimationsForSequenceNamed("road");
    m_pSpritePet_1->setVisible(false);
    m_pSpritePet_2->setVisible(false);
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(1.0),
                                       CCCallFunc::create(this, callfunc_selector(CcbTowerMainLayer::onShowPet)),
                                       CCDelayTime::create(1.0),
                                       CCCallFunc::create(this, callfunc_selector(CcbTowerMainLayer::onBattle)),
                                       NULL
                                       )
                    );
}

void CcbTowerMainLayer::onShowPet()
{
    mAnimationManager->runAnimationsForSequenceNamed("showpet");
}

void CcbTowerMainLayer::onBattle()
{
    g_TowerDataMgr->SetEnterTowerState(true);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendFightTower(1);
}

void CcbTowerMainLayer::showRank()
{
    CCNode *pLayer = CcbManager::sharedManager()->LoadCcbTowerRankListLayer();
    if (getChildByTag(112))
    {
        removeChildByTag(112);
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pLayer->setPosition(winSize*0.5);
    pLayer->ignoreAnchorPointForPosition(false);
    pLayer->setAnchorPoint(ccp(0.5, 0.5));
    addChild(pLayer, 100, 112);
}

//void CcbTowerMainLayer::systemMessageOKTapped(SystemMessage *systemMessage) {
//    CGameSession::SendResetTowerFloor();
//}

