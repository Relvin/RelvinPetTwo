#include "StageNode.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "CcbItemIconLayer.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "MapScene.h"
#include "CCScrollButton.h"
#include "EffectLayer.h"
#include "CcbManager.h"
#include "Role.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"
#include "ResourcePic.h"
#include "MusicCtrl.h"
#include "GlobalData.h"
#include "CcbManager.h"
#include "SystemMessage.h"
#include "StageLayer.h"
#include "CheckPointMgr.h"
#include "GuideData.h"
#include "GuideBtnPos.h"
#include "PacketDataMgr.h"
#include "EnumDefines.h"
#include "CcbJumpTipLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define Max_Reward_Cnt 2
#define Effect_Tag 377327

#define Fight_Tag 1
#define Sweep_Tag 2

static const int Star_Tag = 10;

StageNode::~StageNode()
{
    CGameSession::Detach(this);
	CC_SAFE_RELEASE_NULL(m_pControlButtonStage);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pLayerDrop);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSaoDang);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFight);
	CC_SAFE_RELEASE_NULL(m_pSpriteNew);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCnt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergy);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
	CC_SAFE_RELEASE_NULL(m_pSpriteClear);
    CC_SAFE_RELEASE_NULL(m_pNodeBoss);
    CC_SAFE_RELEASE_NULL(m_pSpriteSweep);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTicketNum);
}


bool StageNode::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::Attach(this);
	return true;
}

void StageNode::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

#define SWITCH_STAR( bShow )    \
{   \
    for (i = 0; i < starCnt; i++) { \
        m_vecStarts[i]->setVisible(bShow);  \
    }   \
}   \

void StageNode::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    setInfo();
    m_pTableView->reloadData();
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(0.2f),
                                 CCCallFunc::create(this, callfunc_selector(StageNode::restoreTouch)),
                                 NULL
                                 )
              );
}

void StageNode::restoreTouch() {
    m_bCanTouchBtn = true;
}

void StageNode::onExit()
{
	CCLayer::onExit();
}

void StageNode::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();

}

// Inhert MemberVariableAssigner
bool StageNode::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStage", CCScrollButton*, this->m_pControlButtonStage);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDrop", CCLayer*, this->m_pLayerDrop);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSaoDang", CCScrollButton*, this->m_pControlButtonSaoDang);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFight", CCScrollButton*, this->m_pControlButtonFight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNew", CCSprite*, this->m_pSpriteNew);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCnt", CCLabelTTF*, this->m_pLabelTTFLeftCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteClear", CCSprite*, this->m_pSpriteClear);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeBoss", CCNode*, this->m_pNodeBoss);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSweep", CCSprite*, this->m_pSpriteSweep);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTicketNum", CCLabelTTF*, this->m_pLabelTTFTicketNum);
	return false;
}

bool StageNode::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN StageNode::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName ) {
    
	return NULL;
}

SEL_MenuHandler StageNode::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName ) {
    
	return NULL;
}

SEL_CCControlHandler StageNode::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName ) {
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSaoDang", StageNode::onPressControlButtonSaoDang);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFight", StageNode::onPressControlButtonFight);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void StageNode::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_vecStarts.clear();

    for (int i = 0; i < 3; i++) {
        CCSprite* m_pSpriteStar = dynamic_cast<CCSprite*>(getChildByTag(Star_Tag + i));
        m_vecStarts.push_back(m_pSpriteStar);
    }

    if (CGameSession::GetRole()->GetwRoleLv() < SWEEP_LV) {
        m_pControlButtonSaoDang->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_disable_pic)), CCControlStateNormal);
        m_pControlButtonSaoDang->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_disable_pic)), CCControlStateHighlighted);
    }
    
    m_pTableView = CCTableView::create(this, m_pLayerDrop->getContentSize());
    m_pTableView->setDirection( kCCScrollViewDirectionHorizontal );
    m_pTableView->setDelegate(this);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerDrop->addChild(m_pTableView, 1);
}

void StageNode::onPressControlButtonSaoDang(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CRole* pRole = CGameSession::GetRole();
    
    if (pRole->GetwRoleLv() < SWEEP_LV) {
        snprintf(strBuf64, BUFFER_SIZE_64, GET_STR(Str_open_sweep), SWEEP_LV);
        FlyTextLayer::showTips(strBuf64);
        return;
    }
    if (CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID) == 0) {
        CCString* pStr = CCString::createWithFormat("%s", GET_STR(Str_free_sweep_not_enough));
        FlyTextLayer::showTips(pStr->getCString());
        return;
    }
    
    StageCtrl::Get()->setSelectedStage(m_nSelectedStage);
    
    if (StageCtrl::Get()->kind() == 2 && m_wLeftCnt == 0) {
        // 需要付费购买
        showBuyMessage(Sweep_Tag);
    }
    else
    {
        CCNode* pSweepNode = CcbManager::sharedManager()->LoadCcbSweepLayer(this);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        pSweepNode->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
        CCDirector::sharedDirector()->getRunningScene()->addChild(pSweepNode, 10);
    }
}

void StageNode::onPressControlButtonFight(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    StageCtrl::Get()->setSelectedStage(m_nSelectedStage);
    
    // fix bug, when stay in stage 2003, will trigger equip guide more than once.
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
    GlobalData::bFirst2003 = false;
    if (stc.byStatus && StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        if (stc.wStageId == 2003 || stc.wStageId == 3002) {
            GlobalData::bFirst2003 = true;
        }
    }
    
    CheckPointMgr::Get()->clrTalkData();
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage && m_bNew) {
        CheckPointMgr::Get()->loadTalkData(0, m_wStageId, true);
        if (CheckPointMgr::Get()->talkPadCnt() > 0) {
            CheckPointMgr::Get()->addStageTalk(0, StageLayer::getCurLayer());
            
            GuideData::GetInstance()->addGuideofEnum(
                                                     GuideData::E_GUIDE_TRIGGER_FRI_4_ATTACK,
                                                     GuideData::E_GUIDE_TRIGGER_THI_3_ATTACK,
                                                     NULL
                                                     );
            
            return;
        }
    }
    
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {

        if (StageCtrl::Get()->kind() == 2 && m_wLeftCnt == 0) {
            showBuyMessage(Fight_Tag);
        } else {
            CGameSession::SendStartBattle(StageCtrl::Get()->kind(), MapCtrl::nSelectedMapId, m_wStageId, false);
            PetLoadingLayer::sharedLayer()->WaitForPacket();
        }
    }
}


#pragma mark Public Method

void StageNode::SetNodeData(int idx) {
    m_nSelectedStage = idx;
    StageCtrl::Get()->setSelectStageId(m_nSelectedStage);
}

#pragma mark Private Method
// 这个方法放在哪里都差不多，放在onEnter(), onEnterTransitionDidFinish()和SetNodeData()中都差不多}
void StageNode::setInfo()
{
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->stageWithIdx(m_nSelectedStage);
    m_wStageId = stc.wStageId;
    m_pLabelTTFName->setString(stc.strName.c_str());
    m_wLimiteLv = stc.wRoleLvLimit;
    int starCnt = m_vecStarts.size();
    
    // 消耗体力}
    if (m_byCostEnergy != stc.byCostEnergy) {
        m_byCostEnergy = stc.byCostEnergy;
        CCString* pCostEnergy = CCString::createWithFormat(GET_STR(Str_energy_cost), stc.byCostEnergy);
        m_pLabelTTFEnergy->setString(pCostEnergy->getCString());
    }
    
    if (m_wIconId != stc.wIconId) {
        m_wIconId = stc.wIconId;
        CCSpriteFrame* pAttrSf = CPetCtrl::Get()->GetPetNaturePicSF(stc.wIconId);
        m_pSpriteAttribute->setDisplayFrame(pAttrSf);
        
        // Head Icon
        m_pLayerIcon->loadIndexData(stc.wIconId);
        m_pLayerIcon->showIconOnly();
        m_pLayerIcon->setBtnEnable(false);
    }

    // status 1: 新关卡 0: 已通关关卡}
    // 活动关卡没有星级概念}
    unsigned int i = 0;
    m_bNew = stc.byStatus;
    if (stc.byStatus) {     // 新关卡}
        m_pSpriteClear->setVisible(false);
        m_pControlButtonSaoDang->setVisible(false);
        
        // 只有新关卡才引导，不会引导到未开放的旧关卡，如果取不到位置，说明是旧关卡，GM命令改，忽略
        if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
            GuideBtnPos::Get()->addNodeWorldPos(this, GuideBtnPos::E_STAGE_TOP);
        }
        
        // 新关卡，隐藏星星和已领取的图片}
        SWITCH_STAR(false);
        
        if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
            m_pControlButtonStage->setEnabled(true);
            m_pControlButtonFight->setVisible(false);
            
            if (getChildByTag(234) != NULL) {
                getChildByTag(234)->stopAllActions();
                getChildByTag(234)->removeFromParentAndCleanup(true);
            }
            // 开战动画}
            EffectLayer* fightEff = EffectLayer::create(E_ANI_EFFECT_START_FIGHT, -1, 1.0/10);
            fightEff->setPosition(m_pSpriteNew->getPosition());
            fightEff->ignoreAnchorPointForPosition(false);
            fightEff->setAnchorPoint(ccp(0.5, 0.5));
            
            addChild(fightEff, 1, 234);
            fightEff->onRun();
        }
    }
    else    // 以及通关过}
    {    //区分三星和非三星}
        m_pSpriteClear->setVisible(true);
        m_pControlButtonFight->setVisible(true);
        m_pSpriteNew->setVisible(false);
        m_pControlButtonStage->setEnabled(false);
        
        if (getChildByTag(234) != NULL) {
            getChildByTag(234)->stopAllActions();
            getChildByTag(234)->removeFromParentAndCleanup(true);
        }
        
        m_byStarCnt = 0;
        // 显示星星数量}
        if (m_byStarCnt != stc.byStarCnt) {
        m_byStarCnt = stc.byStarCnt;
            SWITCH_STAR(true);
            
            for (i = 0; i < stc.byStarCnt; i++) {
                CCTexture2D* pFullStar = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_star_mission));
                m_vecStarts[i]->setTexture(pFullStar);
            }
            
            if (i == starCnt) {
                m_pControlButtonSaoDang->setVisible(true);
            } else {
                m_pControlButtonSaoDang->setVisible(false);
            }
            
            for (i = stc.byStarCnt; i < starCnt; i++) {
                CCTexture2D* pNullStar = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_star_mission_bg));
                m_vecStarts[i]->setTexture(pNullStar);
            }
        }
    }

    if (stc.byFlag) {
        m_pNodeBoss->setVisible(true);
    } else {
        m_pNodeBoss->setVisible(false);
    }
    
    updateLeftCnt(stc);
    
    m_vecDropId.clear();
    m_nPetCnt = stc.m_vecPetId.size();
    m_nItemCnt = stc.m_vecItemId.size();
    
    for (i = 0; i < stc.m_vecPetId.size(); ++i) {
        m_vecDropId.push_back(stc.m_vecPetId[i]);
    }
    for (i = 0; i < stc.m_vecItemId.size(); ++i) {
        m_vecDropId.push_back(stc.m_vecItemId[i]);
    }
    
    // add guide drop effect
    if (StageCtrl::Get()->fromJump() && StageCtrl::Get()->dropStage() == m_wStageId) {
        CCNode* pEffectNode = CcbManager::sharedManager()->LoadCcbStageEffLayer();
        pEffectNode->setPosition(CCPointZero);
        this->addChild(pEffectNode, 60, Effect_Tag);
    } else if (getChildByTag(Effect_Tag)) {
        getChildByTag(Effect_Tag)->removeFromParent();
    }
}


#pragma mark ObserverMsg Delegate
void StageNode::RefeashLayer()
{
    if (m_nSelectedStage != StageCtrl::Get()->selectedStageIdx()) {
        return;
    }
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
    updateLeftCnt(stc);
    PetLoadingLayer::sharedLayer()->End();
}

#pragma mark TableView Delegate
static const float fGap = 36.0f;
static const float fOrg = 18.0f;
CCTableViewCell* StageNode::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbItemIconLayer* pIcon = dynamic_cast<CcbItemIconLayer*>(CcbManager::sharedManager()->LoadCcbItemIconLayer(this));
        
        pIcon->setScale(0.6f);
        pIcon->loadIndexData(m_vecDropId[idx]);
        pIcon->showIconOnly();
        pIcon->setAnchorPoint(ccp(0.5, 0.5));
        pIcon->setPosition(ccp(fOrg, fOrg));
        if (m_vecDropId[idx] / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
            pIcon->setBtnEnable(false);
        } else {
            pIcon->setBtnEnable(true);
        }
        pIcon->setClipRect(m_rect);
        
        if (CGameSession::GetRole()->GetwGuideTrigger() < GuideData::E_GUIDE_END_TRIGGER) {
            pIcon->setBtnEnable(false);
        }
        
        pCell->addChild(pIcon);
        pIcon->setTag(123);
    } else {
        CcbItemIconLayer* pIcon = dynamic_cast<CcbItemIconLayer*>(pCell->getChildByTag(123));
        if (!pIcon) {
            return NULL;
        }
        pIcon->loadIndexData(m_vecDropId[idx]);
        pIcon->showIconOnly();
        if (m_vecDropId[idx] / E_UNITE_BASE_FABIO == E_UNITE_TYPE_PET) {
            pIcon->setBtnEnable(false);
        } else {
            pIcon->setBtnEnable(true);
        }
        pIcon->setClipRect(m_rect);
        
        if (CGameSession::GetRole()->GetwGuideTrigger() < GuideData::E_GUIDE_END_TRIGGER) {
            pIcon->setBtnEnable(false);
        }
    }
    return pCell;
}

unsigned int StageNode::numberOfCellsInTableView(cocos2d::extension::CCTableView *table) {
    return m_nPetCnt + m_nItemCnt;
}

CCSize StageNode::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    return CCSizeMake(fGap, fGap);
}

void StageNode::setClipRect(cocos2d::CCRect rect) {
    m_rect = rect;
    m_pControlButtonFight->setClipRect(rect);
    m_pControlButtonSaoDang->setClipRect(rect);
    m_pControlButtonStage->setClipRect(rect);
}


void StageNode::systemMessageOKTapped(SystemMessage *systemMessage) {
        if (m_wLeftBuyCnt > 0) {
            if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
                CGameSession::SendBuyStageFightCnt(E_BUY_STAGE_NORMAL, m_wStageId);
            } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
                CGameSession::SendBuyStageFightCnt(E_BUY_STAGE_HERO, m_wStageId);
            }
            PetLoadingLayer::sharedLayer()->WaitForPacket();
        } else {
//            FlyTextLayer::showTips(GET_STR(Str_vip_need_up));
            CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
            return;
        }
}

void StageNode::showBuyMessage(int _param) {
    VipBuyConfig::STC_CONFIG_VIP_BUY* pVipBuyCfg = GET_CONFIG_STC(VipBuyConfig, m_wBuyCnt + 1);
    int nDollarCost = 0;
    
    // 总共可购买次数
    VipShowConfig::STC_VIP_SHOW_CONFIG* pVipShowCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
    
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        nDollarCost = pVipBuyCfg->wNormalStage;
        m_wLeftBuyCnt = pVipShowCfg->wStageBuyMax - m_wBuyCnt;
    } else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        nDollarCost = pVipBuyCfg->wHeroStage;
        m_wLeftBuyCnt = pVipShowCfg->wHStageBuyMax - m_wBuyCnt;
    }
    CCString* pStr = CCString::createWithFormat("%s\n%s", GET_STR(Str_show_buy_message), GET_STR(Str_today_left));
    snprintf(strBuf512, BUFFER_SIZE_512, pStr->getCString(), nDollarCost, m_wLeftBuyCnt);
    SystemMessage::showSystemMessage(1, NULL, strBuf512, this, true, _param);
}

void StageNode::updateLeftCnt(StageCtrl::STC_STAGE stc) {
    // 剩余次数}
    if (m_byAttackCnt != stc.byAttackCnt || m_byMaxAttCnt != stc.byMaxAttCnt || m_wBuyCnt != stc.byBuyCnt) {
        m_wBuyCnt = stc.byBuyCnt;
        m_byAttackCnt = stc.byAttackCnt;
        m_byMaxAttCnt = stc.byMaxAttCnt;
        
        if (stc.byMaxAttCnt + stc.byBuyCnt > stc.byAttackCnt) {
            m_wLeftCnt = stc.byMaxAttCnt + stc.byBuyCnt - stc.byAttackCnt;
        } else {
            m_wLeftCnt = 0;
        }
        if (StageCtrl::Get()->kind() == 1) {
            m_pLabelTTFLeftCnt->setVisible(false);
        }
        else
        {
            CCString* pLeftCnt = CCString::createWithFormat(GET_STR(Str_cnt_last), m_wLeftCnt);
            m_pLabelTTFLeftCnt->setString(pLeftCnt->getCString());
            m_pLabelTTFLeftCnt->setVisible(true);
        }
        
    }
    
//    m_pSpriteSweep->setTexture(CCTextureCache::sharedTextureCache()->addImage(CPacketDataMgr::Get()->GetItemIconByIndex(E_SWEEP_ITEM_ID).c_str()));
//    
//    int nSweepItemCnt = CPacketDataMgr::Get()->GetItemCountByIndex(E_SWEEP_ITEM_ID);
//    m_pLabelTTFTicketNum->setString(CCString::createWithFormat("X%d",nSweepItemCnt)->getCString());
//    
    if ( StageCtrl::Get()->kind() == 2 && m_wLeftCnt == 0) {
        m_pControlButtonSaoDang->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_disable_pic)), CCControlStateNormal);
        m_pControlButtonSaoDang->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_disable_pic)), CCControlStateHighlighted);
    } else {
        m_pControlButtonSaoDang->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_able_pic)), CCControlStateNormal);
        m_pControlButtonSaoDang->setBackgroundSpriteForState(CCScale9Sprite::create(GET_PIC(Btn_able_pic)), CCControlStateHighlighted);
    }
}

