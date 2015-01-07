#include "MainBottomInnerLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "GlobalData.h"
#include "EventDataMgr.h"
#include "GuideData.h"
#include "CcbShowGetLayer.h"
#include "SystemMessage.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "StageScene.h"
#include "ArenaDataMgr.h"
#include "GuideBtnPos.h"
#include "CcbWorldBossLayer.h"
#include "PetCtrl.h"
#include "GachaDataMgr.h"
#include "ChallengeCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

static MainBottomInnerLayer* m_shared = NULL;

MainBottomInnerLayer::~MainBottomInnerLayer()
{
    CGameSession::GetRole()->Detach(this);
	CC_SAFE_RELEASE_NULL(m_pControlButtonHome);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTeam);
	CC_SAFE_RELEASE_NULL(m_pControlButtonActive);
	CC_SAFE_RELEASE_NULL(m_pControlButtonArena);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGacha);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShop);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumHome);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumPet);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumActiveMap);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumArena);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumGacha);
	CC_SAFE_RELEASE_NULL(m_pSpriteNumShop);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadMainBottomInnerLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadMainBottomInnerLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "MainBottomInnerLayer", MainBottomInnerLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/bottom_btns.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

MainBottomInnerLayer* MainBottomInnerLayer::GetInstance() {
    return m_shared;
}

bool MainBottomInnerLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    CGameSession::GetRole()->Attach(this);
	return true;
}

void MainBottomInnerLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonTeam, GuideBtnPos::E_BOTTOM_PET);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonHome, GuideBtnPos::E_BOTTOM_MAIN);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonGacha, GuideBtnPos::E_BOTTOM_GACHA);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonActive, GuideBtnPos::E_BOTTOM_TIAOZHAN);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonArena, GuideBtnPos::E_BOTTOM_JJC);
    }
//    CCLOG("MainBottomInnerLayer onEnter");2
}

void MainBottomInnerLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(MainBottomInnerLayer::restoreTouch)),
                                 NULL
                                 )
              );
    m_shared = this;
//    CCLOG("MainBottomInnerLayer onEnterTransition");4
}

void MainBottomInnerLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void MainBottomInnerLayer::onExit()
{
	CCLayer::onExit();
//    CCLOG("MainBottomInnerLayer onExit");3
}

void MainBottomInnerLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
//    CCLOG("MainBottomInnerLayer onExitTransition");1
    m_shared = NULL;
}

// Inhert MemberVariableAssigner
bool MainBottomInnerLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonHome", CCControlButton*, this->m_pControlButtonHome);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTeam", CCControlButton*, this->m_pControlButtonTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonActive", CCControlButton*, this->m_pControlButtonActive);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonArena", CCControlButton*, this->m_pControlButtonArena);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGacha", CCControlButton*, this->m_pControlButtonGacha);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShop", CCControlButton*, this->m_pControlButtonShop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumHome", CCSprite*, this->m_pSpriteNumHome);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumPet", CCSprite*, this->m_pSpriteNumPet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumActiveMap", CCSprite*, this->m_pSpriteNumActiveMap);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumArena", CCSprite*, this->m_pSpriteNumArena);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumGacha", CCSprite*, this->m_pSpriteNumGacha);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumShop", CCSprite*, this->m_pSpriteNumShop);


	return false;
}

bool MainBottomInnerLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN MainBottomInnerLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler MainBottomInnerLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler MainBottomInnerLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonHome", MainBottomInnerLayer::onPressControlButtonHome);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTeam", MainBottomInnerLayer::onPressControlButtonTeam);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonActive", MainBottomInnerLayer::onPressControlButtonActive);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonArena", MainBottomInnerLayer::onPressControlButtonArena);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGacha", MainBottomInnerLayer::onPressControlButtonGacha);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShop", MainBottomInnerLayer::onPressControlButtonShop);

	return NULL;
}

// Inhert CCNodeLoaderListener
void MainBottomInnerLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    int touchPriority = -1;
    m_pControlButtonHome->setTouchPriority(touchPriority);
    m_pControlButtonTeam->setTouchPriority(touchPriority);
    m_pControlButtonActive->setTouchPriority(touchPriority);
    m_pControlButtonShop->setTouchPriority(touchPriority);
    m_pControlButtonArena->setTouchPriority(touchPriority);
    m_pControlButtonGacha->setTouchPriority(touchPriority);
    
    m_vecTips.clear();

    m_vecTips.push_back(m_pSpriteNumHome);
    m_vecTips.push_back(m_pSpriteNumPet);
    m_vecTips.push_back(m_pSpriteNumActiveMap);
    m_vecTips.push_back(m_pSpriteNumArena);
    m_vecTips.push_back(m_pSpriteNumGacha);
    m_vecTips.push_back(m_pSpriteNumShop);

    CRole* pRole = CGameSession::GetRole();
    m_vecTips[kMain]->setVisible(false);
    m_vecTips[kShop]->setVisible(false);
    m_vecTips[kUnit]->setVisible(pRole->GetbyNotiUnit());
    m_vecTips[kArena]->setVisible(false);
    m_vecTips[kGacha]->setVisible(pRole->GetbyNotiGacha());
    m_vecTips[kYiji]->setVisible(false);
    
    if (GlobalData::shared()->getGachaSwitch()) {
        m_pControlButtonGacha->setVisible(false);
        m_pControlButtonShop->setPosition(m_pControlButtonGacha->getPosition());
    }
}

void MainBottomInnerLayer::onPressControlButtonHome(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
	if (GlobalData::kBottomTag == GlobalData::kMainBottom) {
        return;
    }
    GlobalData::kBottomTag = GlobalData::kMainBottom;

    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_SEC_ATTACK) {
        // 上阵精灵结束，和服务器通信}
        GuideData::GetInstance()->connectToServer();
    }
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    BackCtrl::ChangeRootScene(kMainScene);
    m_pControlButtonHome->setEnabled(false);
}

void MainBottomInnerLayer::onPressControlButtonTeam(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    // 有子菜单，不做限制}
    GlobalData::kBottomTag = GlobalData::kTeamBottom;
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    BackCtrl::ChangeRootScene(kUintScene);
}

void MainBottomInnerLayer::onPressControlButtonShop(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
	if (GlobalData::kBottomTag == GlobalData::kShopBottom) {
        return;
    }
    GlobalData::kBottomTag = GlobalData::kShopBottom;
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendReqShopCnt();
}

void MainBottomInnerLayer::onPressControlButtonGacha(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
	if (GlobalData::kBottomTag == GlobalData::kGachaBottom) {
        return;
    }
    GlobalData::kBottomTag = GlobalData::kGachaBottom;
    CPetCtrl::Get()->setPetTujianShowId(0);
    g_GachaData->setIsBoardOpen(false);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    BackCtrl::InsertNextScene(kGachaScene);
//    CGameSession::SendLotteryInfo();
}


void MainBottomInnerLayer::onPressControlButtonArena(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    if (GlobalData::kBottomTag == GlobalData::kAreanBottom) {
        return;
    }
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ARENA);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    GlobalData::kBottomTag = GlobalData::kAreanBottom;
    if (g_ArenaData->GetPlayerInfo().dwUserId != 0) {
        BackCtrl::ChangeRootScene(kArenaIndexScene);
    }
    else
    {
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        CGameSession::SendEnterArenaSceneRequest();
    }
}

void MainBottomInnerLayer::onPressControlButtonActive(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));

    if (GlobalData::kBottomTag == GlobalData::kActiveMapBottom) {
        return;
    }
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ACTIVITY);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }

    GlobalData::kBottomTag = GlobalData::kActiveMapBottom;
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    StageCtrl::Get()->setFromJump(false);
    ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
    CGameSession::SendSpecialMapList();
}


#pragma mark Touch Delegate
void MainBottomInnerLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool touchInView(CCPoint point) {
    if (point.y >= 0.0 && point.y <= 56.0) {
        return true;
    }
    return false;
}

bool MainBottomInnerLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_pStart = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    if (touchInView(m_pStart)) {
        return true;
    }
    return false;
}

void MainBottomInnerLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!touchInView(m_pStart)) {
        return;
    }
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    if (fabsf(movePoint.x - m_pStart.x) > 10.0) {
    }
    return;
}

void MainBottomInnerLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!touchInView(m_pStart)) {
        return;
    }
}

#pragma mark Observer Role Delegate
void MainBottomInnerLayer::byNotiUnitChanged(uint8 byNotiUnit)
{
    m_vecTips[kUnit]->setVisible(byNotiUnit);
}

void MainBottomInnerLayer::byNotiGachaChanged(uint8 byNotiGacha)
{
    m_vecTips[kGacha]->setVisible(byNotiGacha);
}

void MainBottomInnerLayer::byNotiShopChanged(uint8 byNotiShop)
{
    m_vecTips[kShop]->setVisible(byNotiShop);
}



