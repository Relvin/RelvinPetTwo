//
//  MainLayer.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-15.}
//
//

#include "MainLayer.h"
#include "Defines.h"
#include "CcbManager.h"
#include "MusicCtrl.h"
#include "MailDataMgr.h"
#include "BackCtrl.h"
#include "CcbMainTeamLayer.h"
#include "TeamCtrl.h"
#include "PetLoadingLayer.h"
#include "ShopDataMgr.h"
#include "StageScene.h"
#include "CcbGMLayer.h"
#include "UISupport.h"
#include "GuideData.h"
#include "EffectLayer.h"
#include "EnumDefines.h"
#include "GlobalData.h"
#include "ChatDataMgr.h"
#include "GuideBtnPos.h"
#include "CcbChatLayer.h"
#include "ChallengeCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

static MainLayer* m_shared = NULL;

MainLayer::~MainLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerTeam);
	CC_SAFE_RELEASE_NULL(m_pLayerBottom);
	CC_SAFE_RELEASE_NULL(m_pLayerHead);
    CC_SAFE_RELEASE_NULL(m_pLayerSocialUnit);
    CC_SAFE_RELEASE_NULL(m_pControlButtonExpand);
	CC_SAFE_RELEASE_NULL(m_pControlButtonChat);
    CC_SAFE_RELEASE_NULL(m_pControlButtonFriend);
    
	CC_SAFE_RELEASE_NULL(m_pControlButtonRecharge);
    CC_SAFE_RELEASE_NULL(m_pLayerQuest);
    CC_SAFE_RELEASE_NULL(m_pSpriteQuest);
    CC_SAFE_RELEASE_NULL(m_pControlButtonQuest);
    m_shared = NULL;
}


bool MainLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
    CMailDataMgr::Get()->SetMainLayerPt(this);
	return true;
}

void MainLayer::onEnter()
{
	CCLayer::onEnter();
    loadTeam();
    BackCtrl::ClearSceneStack();
    CCLog("main scene statck cnt:%d", CCDirector::sharedDirector()->GetSceneStackCnt());
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_main_scene));
    addEff();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonQuest, GuideBtnPos::E_ADVENTURE);
    }
    ChallengeCtrl::Get()->setChallengePetChoose(false);
    
}

MainLayer* MainLayer::GetCurLayer() {
    return m_shared;
}

void MainLayer::onExit()
{
	CCLayer::onExit();
}

SEL_CallFuncN MainLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

SEL_MenuHandler MainLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

bool MainLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTeam", CCLayer*, this->m_pLayerTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CCLayer*, this->m_pLayerHead);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerSocialUnit", CCLayer*, this->m_pLayerSocialUnit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExpand", CCControlButton*, this->m_pControlButtonExpand);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChat", CCControlButton*, this->m_pControlButtonChat);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFriend", CCControlButton*, this->m_pControlButtonFriend);
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRecharge", CCControlButton*, this->m_pControlButtonRecharge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerQuest", CCLayer*, this->m_pLayerQuest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteQuest", CCSprite*, this->m_pSpriteQuest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonQuest", CCControlButton*, this->m_pControlButtonQuest);
    return false;
}

bool MainLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


SEL_CCControlHandler MainLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChat", MainLayer::onPressControlButtonChat);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRecharge", MainLayer::onPressControlButtonRecharge);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonQuest", MainLayer::onPressControlButtonQuest);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExpand", MainLayer::onPressControlButtonExpand);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFriend", MainLayer::onPressControlButtonFriend);
	return NULL;
}

void MainLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 从MainScene Replace到其他页面后回来，还需要显示之前的页面}
    
    m_pPointUnitOrg = m_pLayerSocialUnit->getPosition();
    m_pPointUnitDes = ccp(-2.0f, m_pLayerSocialUnit->getPositionY());
    
    CCLabelTTF* lblGm = CCLabelTTF::create("GM", "", 24);
    lblGm->setColor(ccRED);
    CCMenuItemLabel *btnGm = CCMenuItemLabel::create(lblGm, this, menu_selector(MainLayer::onGM));
    btnGm->setPosition(ccp(40, CCDirector::sharedDirector()->getWinSize().height*0.95));
    CCMenu *menu = CCMenu::create(btnGm, NULL);
    menu->setPosition(CCPointZero);
    menu->setTouchPriority(kCCMenuHandlerPriority - 1);
#ifdef DEBUG
    addChild(menu, 1);
#endif
    
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (GlobalData::bLoginAccount) {
        GlobalData::bLoginAccount = false;
        if (
            wTrigger >= GuideData::E_GUIDE_END_TRIGGER &&
            wTrigger != GuideData::E_SYS_GUIDE_EQUIP &&
            wTrigger != GuideData::E_SYS_GUIDE_CAT &&
            wTrigger != GuideData::E_SYS_GUIDE_HERO &&
            wTrigger != GuideData::E_SYS_GUIDE_1_JJC &&
            wTrigger != GuideData::E_SYS_GUIDE_1_TOWER &&
            wTrigger != GuideData::E_SYS_GUIDE_BADGE
            ) {
            CGameSession::SendNoticeGet();
        }
    }
    if (ChatDataMgr::Get()->msgCnt(CHAT_CHANNEL_WOLRD) == 0) {
        CGameSession::SendGetChat();
    }
}

void MainLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

void MainLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(MainLayer::restoreTouch)),
                                 NULL
                                 )
              );
}

void MainLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void MainLayer::onPressControlButtonChat(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CCNode* pChatLayer = dynamic_cast<CcbChatLayer*>(CcbManager::sharedManager()->LoadCcbChatLayer(this));
    addChild(pChatLayer, 99);
}

void MainLayer::onPressControlButtonRecharge(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    g_ShopData->SetCurShopShowType(1);
    CGameSession::SendRequestStorePayList();
}

void MainLayer::onPressControlButtonQuest(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    if (!m_bCanTouchBtn) {
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    StageCtrl::Get()->setKind(StageCtrl::kNormalStage);
    CGameSession::SendNormalMap();
}

void MainLayer::onPressControlButtonExpand(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CCPoint _pos = m_pLayerSocialUnit->getPosition();
    if (_pos.equals(m_pPointUnitOrg)) {
        m_pLayerSocialUnit->runAction(CCMoveTo::create(0.5f, m_pPointUnitDes));
        m_pControlButtonExpand->setRotationY(180);
    } else if (_pos.equals(m_pPointUnitDes)) {
        m_pLayerSocialUnit->runAction(CCMoveTo::create(0.5f, m_pPointUnitOrg));
        m_pControlButtonExpand->setRotationY(0);
    }
    return;
}

void MainLayer::onPressControlButtonFriend(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kFriendUnitScene);
}

void MainLayer::loadTeam()
{
    dynamic_cast<CcbMainTeamLayer*>(m_pLayerTeam)->setTeamId(CTeamCtrl::GetCurTeamId());
}

void MainLayer::onGM(CCObject *sender)
{
    CCScene *scene = GMScene::scene();
    CCDirector::sharedDirector()->pushScene(scene);
}

#define ADD_EFFECT( valueEnum, m_pLocate, m_pParent, zOrder )  \
{   \
EffectLayer* pEffectLayer = EffectLayer::create( valueEnum, -1, fFps);  \
pEffectLayer->ignoreAnchorPointForPosition(false);  \
CCPoint locate = m_pLocate->getPosition();  \
if (valueEnum == E_ANI_EFFECT_MAIN_JJC_BG) {    \
pEffectLayer->setScale(1.1f);   \
}   \
if (zOrder == nEffText) {  \
m_pLocate->setZOrder(nSprite);  \
}   \
pEffectLayer->setAnchorPoint(ccp(0.5f, 0.5f)); \
pEffectLayer->setPosition(locate);    \
m_pParent->addChild(pEffectLayer, zOrder);  \
pEffectLayer->onRun();  \
}   \

void MainLayer::addEff() {
    float fFps = 1.0/10.0f;
    int nEffBg = 1, nSprite = 2, nEffText = 3;
    
    // 冒险背景}
    ADD_EFFECT(E_ANI_EFFECT_MAIN_ADVENTURE_BG, m_pControlButtonQuest, m_pLayerQuest, nEffBg);
    // 冒险文字流光}
    ADD_EFFECT(E_ANI_EFFECT_MAIN_ADVENTURE_TEXT, m_pSpriteQuest, m_pLayerQuest, nEffText);
}
