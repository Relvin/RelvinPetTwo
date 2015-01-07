#include "StageLayer.h"
#include "CcbManager.h"
#include "StageNode.h"
#include "MapScene.h"
#include "StageScene.h"
#include "GameSession.h"
#include "Role.h"
#include "BackCtrl.h"
#include "GuideData.h"
#include "CcbSystemBootInfoLayer.h"
#include "TowerDataMgr.h"

#include "CCScrollViewWithBar.h"
#include "UISupport.h"
#include "CcbItemIconLayer.h"
#include "PetLoadingLayer.h"

#include "GlobalData.h"
#include "CCFlowFire.h"
#include "MusicCtrl.h"
#include "CcbActiveStageLayer.h"
#include "ActivityScene.h"
#include "CheckPointMgr.h"
#include "GuideBtnPos.h"
#include "ChallengeCtrl.h"
#include "FightAI.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

static const int Reward_tag = 10;
//static const int Reward_2_tag = 20;
//static const int Reward_3_tag = 30;
static const int Node_offset = 0;
static const int Icon_offset = 1;
static const int Cnt_offset = 3;
static const int Btn_offset = 4;
static const int Get_offset = 5;

static StageLayer* m_shared = NULL;

StageLayer::~StageLayer()
{
    m_shared = NULL;
    
	CC_SAFE_RELEASE_NULL(m_pLayerHeaderBack);
	CC_SAFE_RELEASE_NULL(m_pControlButtonEditTeam);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGetCnt);
	CC_SAFE_RELEASE_NULL(m_pLayerUp);
	CC_SAFE_RELEASE_NULL(m_pLayerDown);
    
    CC_SAFE_RELEASE_NULL(m_pSpriteReward);
    CC_SAFE_RELEASE_NULL(m_pLayerView);
    CC_SAFE_RELEASE_NULL(m_pControlButtonStarGet);
    CC_SAFE_RELEASE_NULL(m_pControlButtonFightBot);
//    m_vecCell.clear();
}


bool StageLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
	return true;
}

StageLayer* StageLayer::getCurLayer() {
    return m_shared;
}

static const float expand = 5.0f;

void StageLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    winSize = CCDirector::sharedDirector()->getWinSize();
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    m_fUpOffset = m_pLayerUp->getPositionX() + winSize.width;
    m_pLayerUp->setPositionX(m_fUpOffset);
}

void StageLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    GlobalData::GetCurTime();
    
    CCSize tableSize;
    // 星级奖励}
    int bonusId;
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
        int curStarCnt = StageCtrl::Get()->curStarCnt();
        
        CCString* strCnt = CCString::createWithFormat("%d", curStarCnt);
        m_pLabelTTFGetCnt->setString(strCnt->getCString());
        
        // 有星级奖励的table size}
        tableSize = CCSizeMake(getWidth(m_pLayerView), getBottom(m_pLayerUp) - getWorldPos(m_pLayerView).y + expand);
        
        bonusId = 100 * StageCtrl::Get()->kind() + MapCtrl::nSelectedMapId;
        StageBonusConfig::STC_CONFIG_BONUS* pStageBonus = GET_CONFIG_STC(StageBonusConfig, bonusId);
        
        m_byStarRew = StageCtrl::Get()->starGet();
        for (int i = 0; i < 3; i++) {
            if (pStageBonus->wRewardNeed[i] && pStageBonus->dwRewardId[i]) {
                CCString* strCnt = CCString::createWithFormat("%d", pStageBonus->wRewardNeed[i]);
                m_vecStarCnt[i]->setString(strCnt->getCString());
                
                m_vecRewardIcon[i]->loadIndexData(pStageBonus->dwRewardId[i]);
                m_vecRewardIcon[i]->showIconOnly();
                m_vecRewardIcon[i]->setBtnEnable(true);
                m_vecRewardIcon[i]->showCnt(pStageBonus->dwRewardCnt[i]);
                m_vecRewardIcon[i]->setCntFont(15.0f);
                
                bool bAlreadyGet = m_byStarRew >> i;
                if (bAlreadyGet) {
                    m_vecSpriteGet[i]->setVisible(true);
                    m_vecButtonGet[i]->setEnabled(false);
                    m_vecRewardIcon[i]->setBtnEnable(false);
                } else if (curStarCnt >= pStageBonus->wRewardNeed[i]) {
                    m_vecSpriteGet[i]->setVisible(false);
                    m_vecButtonGet[i]->setEnabled(true);
                    m_vecRewardIcon[i]->setBtnEnable(false);
                    
                    std::vector<CCPoint> arrPoint;
                    arrPoint.push_back(ccp(getLeft(m_vecButtonGet[i]) + 2, getBottom(m_vecButtonGet[i]) + 2));
                    arrPoint.push_back(ccp(getLeft(m_vecButtonGet[i]) + 2, getTop(m_vecButtonGet[i]) - 2));
                    arrPoint.push_back(ccp(getRight(m_vecButtonGet[i]) - 2, getTop(m_vecButtonGet[i]) - 2));
                    arrPoint.push_back(ccp(getRight(m_vecButtonGet[i]) - 2, getBottom(m_vecButtonGet[i]) + 2));
                    
                    CCFlowFire* fire1 = CCFlowFire::createPolygon(arrPoint);
                    fire1->setPosition(CCPointZero);
                    fire1->setAnchorPoint(CCPointZero);
                    m_vecNodeStars[i]->addChild(fire1, 10, 99);
                    
                } else {
                    m_vecSpriteGet[i]->setVisible(false);
                    m_vecButtonGet[i]->setEnabled(false);
                    m_vecRewardIcon[i]->setBtnEnable(true);
                }
            } else {
                m_vecNodeStars[i]->setVisible(false);
            }
        }
        
    } else if ( StageCtrl::Get()->kind() == StageCtrl::kActivityStage ) {   // 活动关卡不需要星级奖励}
        tableSize = CCSizeMake(getWidth(m_pLayerView), getBottom(m_pLayerHeaderBack) - getWorldPos(m_pLayerView).y + expand);
        m_pSpriteReward->setVisible(false);
    }
    
    m_rect = CCRectMake(getLeft(m_pLayerDown), getTop(m_pLayerDown), tableSize.width, tableSize.height);
    
    tableCnt();
    m_pLayerView->setContentSize(tableSize);
    CCTableViewWithBar* pTable = NULL;
    if (!m_pTableList) {
        m_pTableList = CCTableView::create(this, tableSize);
        m_pTableList->setDirection( kCCScrollViewDirectionVertical );
        m_pTableList->setBounceable(true);
        
        pTable = CCTableViewWithBar::create(m_pTableList);
        pTable->setAnchorPoint(ccp(0.5, 0));
        pTable->ignoreAnchorPointForPosition(false);
        pTable->setPosition(ccp(getWidth(m_pLayerView)*0.5, 0));
        
        m_pLayerView->addChild(pTable);
    }
    m_pTableList->reloadData();
    
    
    if (pTable) {
        pTable->checkIsShow(m_nTableCnt, cellSizeForTable(m_pTableList));
    }
    
    CGameSession::Attach(this);
    
    GlobalData::GetCurTime();

    bool bFirst = true;
    m_bRestored = false;
    
    // 星级奖励进场效果}
    m_pLayerUp->runAction(CCMoveBy::create(TRANS_DUR*0.5, ccp(-winSize.width, 0.0f)));
    
    
//    m_fDelay = (m_vecCell.size()) * m_fDelta;
//    for (int i = 0; i < m_vecCell.size(); i++) {
//        if (m_vecCell[i]->getParent()->getParent()) {
//            m_vecCell[i]->runAction(CCSequence::create(CCDelayTime::create(m_fDelay), CCMoveTo::create(TRANS_DUR*0.5, ccp(m_fLeftGap, 0)), NULL));
//            if (bFirst) {
//                bFirst = false;
//                this->runAction(CCSequence::create(CCDelayTime::create(TRANS_DUR*0.5+m_fDelay), CCCallFunc::create(this, callfunc_selector(StageLayer::setTouchRestore)), NULL));
//            }
//        }
//        m_fDelay -= m_fDelta;
//    }
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(StageLayer::setTouchRestore)),
                                       NULL
                                       )
                    );
    
    CcbSystemBootInfoLayer::showSystemBootInfo(GuideData::GetInstance()->getSysLockId(), this);
    
    GlobalData::GetCurTime();
    
    if (StageCtrl::Get()->fromJump()) {
        uint32 dwStageId = StageCtrl::Get()->dropStage();
        m_pTableList->scrollToIndex(dwStageId % 1000 - 1);
    }
    
    if (StageCtrl::Get()->kind() == StageCtrl::kActivityStage
        && ChallengeCtrl::Get()->getChallengeType() == ChallengeCtrl::kMoneyCat) {
        CCNode* catDesNode = CcbManager::sharedManager()->LoadCcbCoinCatDesLayer();
        if (catDesNode) {
            catDesNode->setPosition(ccp(getWidth(m_pLayerView)*0.5, 10));
            catDesNode->setAnchorPoint(ccp(0.5, 0));
            catDesNode->ignoreAnchorPointForPosition(false);
            m_pLayerView->addChild(catDesNode);
        }
    }
    
    // Map地图点的对话移到这里
//    MapCtrl::setMapPointClicked(MapCtrl::kMapStarNormal, MapCtrl::nSelectedMapId);
    if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage && !MapCtrl::bMapPointClicked) {
        // 增加对话
        m_nTalkIdx = 0;
        m_bShowMapTalk = true;
        
        CheckPointMgr::Get()->loadTalkData(MapCtrl::nSelectedMapId, 0, 0);
        CheckPointMgr::Get()->addMapTalk(m_nTalkIdx, this);
    }
    
    PetLoadingLayer::sharedLayer()->End();
}

void StageLayer::setTouchRestore()
{
//    for (int i = 0; i < m_vecCell.size(); i++) {
//        m_vecCell[i]->stopAllActions();
//        if (m_vecCell[i]->getPositionX() != m_fLeftGap) {
//            m_vecCell[i]->setPositionX(m_fLeftGap);
//        }
//    }
    m_bRestored = true;
    
    if (MapCtrl::bNeedShowNextMessage) {
        MapCtrl::bNeedShowNextMessage = false;
        // 需要展示跳转到下一关卡的弹版
        this->addChild(CcbManager::sharedManager()->LoadCcbMapPointJumpLayer(this));
    }
    
    if (!m_bShowMapTalk) {
        addGuideLayer();
    } else {
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_GUIDE_TRIGGER_FIR_2_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_MAP_2_TALK,
                                                 NULL
                                                 );
    }
}

void StageLayer::addGuideLayer() {
    // 如果新手第一场战斗中间断线，重新上线，将不存在说话弹版那步，需要跳过。}
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (wTrigger == GuideData::E_GUIDE_TRIGGER_FIR_2_ATTACK)
    {
        CGameSession::GetRole()->SetwGuideTrigger(GuideData::E_GUIDE_TRIGGER_FIR_3_ATTACK);
    }
    else if (wTrigger == GuideData::E_SYS_GUIDE_2_CAT) {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("active_guide_end");
#endif
    }
    
    if ( CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV ) {
        //        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonStarGet, GuideBtnPos::E_FULL_STAR);
        runAction(
                  CCSequence::create(
                                     CCDelayTime::create(0.1f),
                                     CCCallFunc::create(this, callfunc_selector(StageLayer::addFullStarPos)),
                                     NULL
                                     )
                  );
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_GUIDE_TRIGGER_FIR_3_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_SEC_2_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_THI_2_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_TEAM,
                                                 GuideData::E_GUIDE_TRIGGER_GACHA,
                                                 GuideData::E_GUIDE_TRIGGER_1_PRESS_MAIN,
                                                 GuideData::E_GUIDE_TRIGGER_2_FOUR_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_2_PRESS_MAIN,
                                                 GuideData::E_GUIDE_TRIGGER_2_FIVE_ATTACK,
                                                 GuideData::E_GUIDE_TRIGGER_GET_STAR,
                                                 
                                                 GuideData::E_SYS_GUIDE_2_CAT,
                                                 GuideData::E_SYS_GUIDE_3_HERO,
                                                 GuideData::E_SYS_GUIDE_4_HERO,
                                                 NULL
                                                 );
    }
}

void StageLayer::addFullStarPos() {
    GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonStarGet, GuideBtnPos::E_FULL_STAR);
}

void StageLayer::onExit()
{
	CCLayer::onExit();
}

void StageLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    m_pLayerUp->runAction(CCMoveBy::create(TRANS_DUR*0.5, ccp(winSize.width, 0.0f)));
    
//    m_fDelay = m_fDelta;
//    for (int i = m_vecCell.size() - 1; i >= 0; i--) {
//        if (m_vecCell[i]->getParent()->getParent()) {
//            m_vecCell[i]->runAction(CCSequence::create(CCDelayTime::create(m_fDelay), CCMoveBy::create(TRANS_DUR*0.5, ccp(winSize.width, 0)), NULL));
//            m_fDelay += m_fDelta;
//        }
//    }
    CGameSession::Detach(this);
}

// Inhert MemberVariableAssigner
bool StageLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHeaderBack", CCLayer*, this->m_pLayerHeaderBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEditTeam", CCControlButton*, this->m_pControlButtonEditTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGetCnt", CCLabelTTF*, this->m_pLabelTTFGetCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDown", CCLayer*, this->m_pLayerDown);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteReward", CCSprite*, this->m_pSpriteReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerView", CCLayer*, this->m_pLayerView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStarGet", CCControlButton*, this->m_pControlButtonStarGet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFightBot", CCControlButton*, this->m_pControlButtonFightBot);
	return false;
}

bool StageLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN StageLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler StageLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler StageLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEditTeam", StageLayer::onPressControlButtonEditTeam);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGet", StageLayer::onPressControlButtonGet);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFightBot", StageLayer::onPressControlButtonFightBot);
	return NULL;
}

// Inhert CCNodeLoaderListener
void StageLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_vecRewardIcon.clear();
    m_vecNodeStars.clear();
    m_vecStarCnt.clear();
    
//    m_pControlButtonStarGet->setTouchPriority(2*kCCMenuHandlerPriority - 21);
//    m_pControlButtonStarGet_2->setTouchPriority(2*kCCMenuHandlerPriority - 21);
//    m_pControlButtonStarGet_3->setTouchPriority(2*kCCMenuHandlerPriority - 21);
    
    for (int i = 0; i < 3; i++) {
        int Base_tag = Reward_tag + 10 * i;
        CCNode* m_pNodeStar = m_pSpriteReward->getChildByTag(Base_tag + Node_offset);
        m_vecNodeStars.push_back(m_pNodeStar);
        
        CcbItemIconLayer* m_pLayerIcon = dynamic_cast<CcbItemIconLayer*>(m_pNodeStar->getChildByTag(Base_tag+Icon_offset));
        m_vecRewardIcon.push_back(m_pLayerIcon);
        
        CCLabelTTF* m_pLabelTTFStarCnt = dynamic_cast<CCLabelTTF*>(m_pNodeStar->getChildByTag(Base_tag+Cnt_offset));
        m_vecStarCnt.push_back(m_pLabelTTFStarCnt);
        
        CCControlButton* m_pControlButtonGet = dynamic_cast<CCControlButton*>(m_pNodeStar->getChildByTag(Base_tag+Btn_offset));
        m_pControlButtonGet->setTouchPriority(2*kCCMenuHandlerPriority - 21);
        m_vecButtonGet.push_back(m_pControlButtonGet);
        
        CCSprite* m_pSpriteAlreadyGet = dynamic_cast<CCSprite*>(m_pNodeStar->getChildByTag(Base_tag+Get_offset));
        m_vecSpriteGet.push_back(m_pSpriteAlreadyGet);
    }
}

void StageLayer::onPressControlButtonEditTeam(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    BackCtrl::InsertNextScene(kTeamScene);
}

void StageLayer::onPressControlButtonGet(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    CCControlButton* tmpBtn = dynamic_cast<CCControlButton*>(pSender);
    int nTag = tmpBtn->getTag();
    int nOffset = 0;
    
    nOffset = (nTag - Btn_offset) / Reward_tag - 1;
    
    if (MapCtrl::nSelectedMapId == 1 && nOffset == 0 && StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
        GlobalData::bJumpToTwo = true;
    } else {
        GlobalData::bJumpToTwo = false;
    }
    
    CGameSession::SendMapPassStarRew(MapCtrl::nSelectedMapId, StageCtrl::Get()->kind(), nOffset);
    m_vecNodeStars[nOffset]->removeChildByTag(99);
    m_vecSpriteGet[nOffset]->setVisible(true);
    m_vecButtonGet[nOffset]->setEnabled(false);
    m_vecRewardIcon[nOffset]->setBtnEnable(false);
    
    m_byStarRew = m_byStarRew | (0x01 << nOffset);
    StageCtrl::Get()->setStarGet(m_byStarRew);
}

void StageLayer::onPressControlButtonFightBot(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    CRole* role = CGameSession::GetRole();
    
    STC_BATTLE_PRE_DATA perData;
    perData.wUserLv = role->GetwRoleLv();
    perData.dwCurExp = role->GetdwRoleExp();
    perData.dwCurEnergy = role->GetdwEnergy();
    perData.byCurFightCnt = role->GetdwBattleBagCnt();
    FightAI::Get()->setPerData(perData);
    
    CGameSession::SendMapSweep(MapCtrl::nSelectedMapId, StageCtrl::Get()->kind());
}

#pragma mark - CCTableView Delegate -
void StageLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    if ( cell ) {
        CCLog("cell touched at index:%i", cell->getIdx());
    }
}

CCTableViewCell* StageLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCLayer* pNode;
        
        // 精英关卡和普通关卡要用不同的ccb}
        if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
            pNode = dynamic_cast<StageNode* >( CcbManager::sharedManager()->LoadStageNode(this) );
        } else if (StageCtrl::Get()->kind() == StageCtrl::kActivityStage) {
            pNode = dynamic_cast<CcbActiveStageLayer*>( CcbManager::sharedManager()->LoadCcbActiveStageLayer(this) );
        }
        
        if (!pNode) {
            return NULL;
        }
//        m_vecCell.push_back(pNode);
        
        m_fCellWidth = pNode->getContentSize().width;
        m_fCellHeight = pNode->getContentSize().height;
        
        m_fLeftGap = (getWidth(m_pLayerView) - m_fCellWidth) * 0.5;
        
        if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
            dynamic_cast<StageNode* >( pNode )->SetNodeData(idx);
            dynamic_cast<StageNode* >( pNode )->setClipRect(m_rect);
        } else if (StageCtrl::Get()->kind() == StageCtrl::kActivityStage) {
            dynamic_cast<CcbActiveStageLayer* >( pNode )->SetNodeData(idx);
            dynamic_cast<CcbActiveStageLayer* >( pNode )->setClipRect(m_rect);
        }
        pNode->setAnchorPoint(CCPointZero); // 由于StageNode没有ignoreAnchorPoint,所以这里的设置没有效果，仍旧按照(0,0)锚点来定坐标}
        // 此处增加这个原因是由于有些极端情况下，pNode被创建出来还在320的位置}
//        if (m_bRestored) {
            pNode->setPosition(ccp(m_fLeftGap, 0));
//        } else {
//            pNode->setPosition(ccp(winSize.width, 0));
//        }
        pCell->addChild(pNode);
        pNode->setTag(123);
    } else {
        if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
            StageNode* pNode = dynamic_cast<StageNode* >(pCell->getChildByTag(123));
            dynamic_cast<StageNode* >( pNode )->SetNodeData(idx);
            dynamic_cast<StageNode* >(pNode)->setClipRect(m_rect);
        } else if (StageCtrl::Get()->kind() == StageCtrl::kActivityStage) {
            CcbActiveStageLayer* pNode = dynamic_cast<CcbActiveStageLayer* >(pCell->getChildByTag(123));
            dynamic_cast<CcbActiveStageLayer* >( pNode )->SetNodeData(idx);
            dynamic_cast<CcbActiveStageLayer* >( pNode )->setClipRect(m_rect);
        }
    }
    return pCell;
}

unsigned int StageLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_nTableCnt;
}

CCSize StageLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(m_fCellWidth, m_fCellHeight);
}

#pragma mark - Private Method -
void StageLayer::tableCnt()
{
    m_nTableCnt = 0;
    if (StageCtrl::Get()->stageCnt() != 0) {
        
        if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage || StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {      // 普通和精英关卡}
            uint16 curMapId = MapCtrl::nSelectedMapId;
            
            CRole *pRole = CGameSession::GetRole();
            uint16 myMapId;
            uint16 wMyStageId;
            if (StageCtrl::Get()->kind() == StageCtrl::kNormalStage) {
                myMapId = pRole->GetwPassMapId() + 1;
                wMyStageId = pRole->GetwPassStageId();
                m_pControlButtonFightBot->setVisible(false);
                
                CCNode *pChildNode = NULL;
                for (int i = 0; i < 3; i++) {
                    pChildNode = m_pSpriteReward->getChildByTag(10 + i * 10);
                    pChildNode->setPosition(ccp(75, 0) + pChildNode->getPosition());
                }
            }
            else if (StageCtrl::Get()->kind() == StageCtrl::kSpecialStage) {
                myMapId = pRole->GetwHeroMap() + 1;
                wMyStageId = pRole->GetwHeroStage();
            }
            
            if (curMapId < myMapId) {
                // 如果请求的是已经通过的Map点，返回完整的stage关卡数量}
                m_newTag = -1;
                m_nTableCnt = StageCtrl::Get()->stageCnt();
            } else if (curMapId == myMapId) {
                // 如果请求的是没有完全通过的Map点，应该放出已经通过的关卡点+1（需要新挑战的关卡）}
                // 有种极端情况是完全通过前一个地图点，刚刚开启下一个地图点，此时只显示一个关卡}
                if (wMyStageId / 1000 < myMapId) {      // 只显示一个stage node，当前新地图点}
                    m_newTag = 1;
                } else {        // 显示通过的stage node}
                    m_newTag = wMyStageId % 1000 + 1;
                }
                m_nTableCnt = m_newTag;
            } else {
                CCMessageBox("Map ID Error", "error");
            }
        } else if (StageCtrl::Get()->kind() == StageCtrl::kActivityStage) {
            m_nTableCnt = StageCtrl::Get()->stageCnt();
            m_pControlButtonFightBot->setVisible(false);
            CCNode *pChildNode = NULL;
            for (int i = 0; i < 3; i++) {
                pChildNode = m_pSpriteReward->getChildByTag(10 + i * 10);
                pChildNode->setPosition(ccp(75, 0) + pChildNode->getPosition());
            }
        }
    }
}

#pragma mark - Observer Delegate -
void StageLayer::RefeashLayer()
{
    CCString* strCnt = CCString::createWithFormat("%d", StageCtrl::Get()->curStarCnt());
    m_pLabelTTFGetCnt->setString(strCnt->getCString());
    if (m_pTableList) {
        m_pTableList->reloadData();
    }
}

void StageLayer::showStep() {
    m_nTalkIdx++;
    
    if (!MapCtrl::bMapPointClicked) {
        // Map Talk
        if ( m_nTalkIdx >= CheckPointMgr::Get()->talkPadCnt() ) {
            MapCtrl::bMapPointClicked = true;
            if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
                GuideData::GetInstance()->addGuideofEnum(
                                                         GuideData::E_GUIDE_TRIGGER_FIR_3_ATTACK,
                                                         NULL
                                                         );
            }
            m_nTalkIdx = 0;
            return;
        }
        CheckPointMgr::Get()->addMapTalk(m_nTalkIdx, this);
    } else {
        // Stage Talk
        if (m_nTalkIdx >= CheckPointMgr::Get()->talkPadCnt()) {
            uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
            if (
                wTrigger == GuideData::E_GUIDE_TRIGGER_TEAM ||
                wTrigger == GuideData::E_GUIDE_TRIGGER_THI_END_ATTACK
                ) {
                GuideData::GetInstance()->onlyRmGuideLayer();
            }
            
            // 开战
            CGameSession::SendStartBattle(StageCtrl::Get()->kind(), MapCtrl::nSelectedMapId, StageCtrl::Get()->selectedStage().wStageId, false);
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            return;
        }
        CheckPointMgr::Get()->addStageTalk(m_nTalkIdx, this);
    }
}

#pragma mark - System Message Protocol -
void StageLayer::systemMessageOKTapped(SystemMessage *systemMessage) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    StageCtrl::Get()->setKind(StageCtrl::Get()->kind());
////    CGameSession::SendNormalMap();
//    //TODO:Junie 22最好不要写死
//    if (MapCtrl::nSelectedMapId < 22) {
//        MapCtrl::nSelectedMapId++;
//    }
//
//    MapConfig::STC_MAP_CONFIG* pMapConfig = GET_CONFIG_STC(MapConfig, MapCtrl::nSelectedMapId);
//    if (pMapConfig) {
//        StageCtrl::Get()->setCurMapPointName(pMapConfig->strName);
//        StageCtrl::Get()->setFromJump(false);
//        CGameSession::SendReqStageInfo(StageCtrl::Get()->kind(), MapCtrl::nSelectedMapId);
//    }
// 此处只处理跳转到第二章地图的情况，其他的跳转由MapJumpLayer处理
    MapCtrl::nSelectedMapId = 2;
    
    MapConfig::STC_MAP_CONFIG* pMapConfig = GET_CONFIG_STC(MapConfig, MapCtrl::nSelectedMapId);
    if (pMapConfig) {
        StageCtrl::Get()->setCurMapPointName(pMapConfig->strName);
        StageCtrl::Get()->setFromJump(false);
        CGameSession::SendReqStageInfo(StageCtrl::Get()->kind(), MapCtrl::nSelectedMapId);
    }
}


