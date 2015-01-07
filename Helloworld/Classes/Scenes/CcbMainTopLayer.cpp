#include "CcbMainTopLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "MailDataMgr.h"
#include "TaskDataMgr.h"
#include "EventDataMgr.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "Role.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "PetLoadingLayer.h"
#include "GlobalData.h"
#include "EnumDefines.h"
#include "WorldInfoDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMainTopLayer::~CcbMainTopLayer()
{
    CGameSession::GetRole()->Detach(this);
	CC_SAFE_RELEASE_NULL(m_pControlButtonActive);
	CC_SAFE_RELEASE_NULL(m_pSpriteActiveNum);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReward);
	CC_SAFE_RELEASE_NULL(m_pSpriteSysRewardNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonMystery);
    CC_SAFE_RELEASE_NULL(m_pSpriteMysteryNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAchieve);
    CC_SAFE_RELEASE_NULL(m_pSpriteAchieveNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonDailyquest);
    CC_SAFE_RELEASE_NULL(m_pSpriteDailyquestNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEvent7);
    CC_SAFE_RELEASE_NULL(m_pSpriteEvent7Num);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEvent30);
    CC_SAFE_RELEASE_NULL(m_pSpriteEvent30Num);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMainTopLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMainTopLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMainTopLayer", CcbMainTopLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/top3.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMainTopLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::GetRole()->Attach(this);
	return true;
}

void CcbMainTopLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    this->setOpacity(0);
    
    CRole* pRole = CGameSession::GetRole();
    //30tian
    if (pRole->GetbyThirtyRewStatus() == E_REW_STATUS_CAN) {
        m_pSpriteEvent30Num->setVisible(true);
        m_pSpriteEvent30Num->getParent()->setVisible(true);
    }
    else{
        m_pSpriteEvent30Num->setVisible(false);
        //30天领完就不显示了
        if(pRole->GetdwThirtyRewDay() >= 30){
            m_pSpriteEvent30Num->getParent()->setVisible(false);
        }
        
    }
}

void CcbMainTopLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction(CCFadeIn::create(TRANS_DUR*0.5));
    
    // reward tip
    uint32 dwSysRewardNum = CMailDataMgr::Get()->GetSysRewardNum();
    if (dwSysRewardNum > 0)
    {
        m_pSpriteSysRewardNum->setVisible(true);
        showEff();
    }
    else {
        m_pSpriteSysRewardNum->setVisible(false);
    }
    
    if ( g_TaskData->GetAchieveAwardCount() ) {
//        m_pSpriteAchieveNum->setVisible(true);
    } else {
        m_pSpriteAchieveNum->setVisible(false);
    }
    
    if ( g_TaskData->GetDailyAwardCount() || g_TaskData->GetAchieveAwardCount()) {
        m_pSpriteDailyquestNum->setVisible(true);
    } else {
        m_pSpriteDailyquestNum->setVisible(false);
    }
    
    // active tip
    CRole* pRole = CGameSession::GetRole();
    if (pRole->GetbyNotiActive()) {
        m_pSpriteActiveNum->setVisible(true);
    } else {
        m_pSpriteActiveNum->setVisible(false);
    }
    
    //mystery
    if (pRole->GetbyNotiMystery() || WorldInfoDataMgr::Get()->getMJShopOpen()) {
        m_pSpriteMysteryNum->setVisible(true);
    } else {
        m_pSpriteMysteryNum->setVisible(false);
    }
    
    //7tian
    if (pRole->GetbySevenRewStatus() == E_REW_STATUS_CAN) {
        m_pSpriteEvent7Num->setVisible(true);
    }
    else{
        m_pSpriteEvent7Num->setVisible(false);
    }
    
    
}

void CcbMainTopLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMainTopLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    this->runAction(CCFadeOut::create(TRANS_DUR*0.5));
}

void CcbMainTopLayer::setOpacity(GLubyte opacity)
{
    if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>( pObject );
			if (pRGBAProtocol)
			{
                pRGBAProtocol->setOpacity(opacity);
			}
		}
	}
}

// Inhert MemberVariableAssigner
bool CcbMainTopLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonActive", CCControlButton*, this->m_pControlButtonActive);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteActiveNum", CCSprite*, this->m_pSpriteActiveNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReward", CCControlButton*, this->m_pControlButtonReward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSysRewardNum", CCSprite*, this->m_pSpriteSysRewardNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMystery", CCControlButton*, this->m_pControlButtonMystery);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMysteryNum", CCSprite*, this->m_pSpriteMysteryNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAchieve", CCControlButton*, this->m_pControlButtonAchieve);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAchieveNum", CCSprite*, this->m_pSpriteAchieveNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDailyquest", CCControlButton*, this->m_pControlButtonDailyquest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDailyquestNum", CCSprite*, this->m_pSpriteDailyquestNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvent7", CCControlButton*, this->m_pControlButtonEvent7);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEvent7Num", CCSprite*, this->m_pSpriteEvent7Num);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvent30", CCControlButton*, this->m_pControlButtonEvent30);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEvent30Num", CCSprite*, this->m_pSpriteEvent30Num);
	return false;
}

bool CcbMainTopLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMainTopLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMainTopLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMainTopLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonActive", CcbMainTopLayer::onPressControlButtonActive);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReward", CcbMainTopLayer::onPressControlButtonReward);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMystery", CcbMainTopLayer::onPressControlButtonMystery);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAchieve", CcbMainTopLayer::onPressControlButtonAchieve);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDailyquest", CcbMainTopLayer::onPressControlButtonDailyquest);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvent7", CcbMainTopLayer::onPressControlButtonEvent7);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvent30", CcbMainTopLayer::onPressControlButtonEvent30);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMainTopLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pSpriteSysRewardNum->setVisible(false);
    m_pSpriteActiveNum->setVisible(false);
    m_pSpriteMysteryNum->setVisible(false);
    m_pSpriteAchieveNum->setVisible(false);
    m_pSpriteDailyquestNum->setVisible(false);
}

void CcbMainTopLayer::onPressControlButtonActive(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    
    g_EventData->SetCurShowEventType(SHOW_FIRST_RECHARGE);
    BackCtrl::InsertNextScene(kEventScene);
}

void CcbMainTopLayer::onPressControlButtonReward(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    BackCtrl::InsertNextScene(kMailListScene);
//	BackCtrl::InsertNextScene(kAwardCenterScene);
}

void CcbMainTopLayer::onPressControlButtonMystery(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_MY_STERY_SHOP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    g_EventData->setMyShopType(E_MY_SHOP_MJ);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendReqMJShopList();
    CGameSession::SendReqMySteryShopList();
}

void CcbMainTopLayer::showEff()
{
    CCParticleSystemQuad* eff1 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_1.plist");
    CCParticleSystemQuad* eff2 = CCParticleSystemQuad::create("ccbresources/12monthdate/home/eff_jiangli_2.plist");
    
    eff1->setPosition(m_pControlButtonReward->getPosition());
    m_pControlButtonReward->getParent()->addChild(eff1);
    
    eff2->setPosition(getCenter(m_pControlButtonReward));
    m_pControlButtonReward->getParent()->addChild(eff2);
}

void CcbMainTopLayer::onPressControlButtonAchieve(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    GlobalData::shared()->setDailyLayerType(1);
    BackCtrl::InsertNextScene(kDailyQuestRewardScene);
}

void CcbMainTopLayer::onPressControlButtonDailyquest(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    GlobalData::shared()->setDailyLayerType(0);
    BackCtrl::InsertNextScene(kDailyQuestRewardScene);
}

void CcbMainTopLayer::onPressControlButtonEvent7(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(123)) {
        return;
    }
    
    CCNode* node = CcbManager::sharedManager()->LoadCcbEventReward7Layer(NULL);
    if (node) {
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(ccp(0.5, 0.5));
        node->setPosition(CCDirector::sharedDirector()->getWinSize()*0.5);
        CCDirector::sharedDirector()->getRunningScene()->addChild(node, 999, 123);
    }
}

void CcbMainTopLayer::onPressControlButtonEvent30(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    if (CCDirector::sharedDirector()->getRunningScene()->getChildByTag(123)) {
        return;
    }
    
    CCNode* node = CcbManager::sharedManager()->LoadCcbEventReward30Layer(NULL);
    if (node) {
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(ccp(0.5, 0.5));
        node->setPosition(CCDirector::sharedDirector()->getWinSize()*0.5);
        CCDirector::sharedDirector()->getRunningScene()->addChild(node, 999, 123);
    }
}

#pragma mark Observer Role Delegate
void CcbMainTopLayer::byNotiActiveChanged(uint8 byNotiActive) {
    m_pSpriteActiveNum->setVisible(byNotiActive);
}

void CcbMainTopLayer::byNotiAwardChanged(uint8 byNotiAward) {
    if (byNotiAward) {
        showEff();
    } else {
        // dont need?
    }
    m_pSpriteSysRewardNum->setVisible(byNotiAward);
}

void CcbMainTopLayer::byNotiMysteryChanged(uint8 byNotiMystery) {
    m_pSpriteMysteryNum->setVisible(byNotiMystery | WorldInfoDataMgr::Get()->getMJShopOpen());
}

void CcbMainTopLayer::bySevenRewStatusChanged(uint8 bySevenRewStatus)
{
    if (bySevenRewStatus == E_REW_STATUS_CAN) {
        m_pSpriteEvent7Num->setVisible(true);
    }
    else{
        m_pSpriteEvent7Num->setVisible(false);
    }
}

void CcbMainTopLayer::byThirtyRewStatusChanged(uint8 byThirtyRewStatus)
{
    CRole* pRole = CGameSession::GetRole();
    //30tian
    if (byThirtyRewStatus == E_REW_STATUS_CAN) {
        m_pSpriteEvent30Num->setVisible(true);
        m_pSpriteEvent30Num->getParent()->setVisible(true);
    }
    else{
        m_pSpriteEvent30Num->setVisible(false);
        //30天领完就不显示了
        if(pRole->GetdwThirtyRewDay() >= 30){
            m_pSpriteEvent30Num->getParent()->setVisible(false);
        }
        
    }
    
//    if (byThirtyRewStatus == E_REW_STATUS_CAN) {
//        m_pSpriteEvent30Num->setVisible(true);
//    }
//    else{
//        m_pSpriteEvent30Num->setVisible(false);
//    }
}