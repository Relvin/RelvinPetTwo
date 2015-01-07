#include "CcbActiveStageLayer.h"
#include "CcbManager.h"
#include "CCScrollButton.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "StageScene.h"
#include "GameSession.h"
#include "Role.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "PetLoadingLayer.h"
#include "CcbItemIconLayer.h"
#include "PetCtrl.h"
#include "ActivityScene.h"
#include "GlobalData.h"
#include "SystemMessage.h"
#include "CcbJumpTipLayer.h"
#include "FlyTextLayer.h"


#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

#include "GuideBtnPos.h"
#include "GuideData.h"
#include "ChallengeCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbActiveStageLayer::~CcbActiveStageLayer()
{
    CGameSession::Detach(this);
	CC_SAFE_RELEASE_NULL(m_pLayerDrop);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFight);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCnt);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergy);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttribute);
    CC_SAFE_RELEASE_NULL(m_pLabelOpenLv);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbActiveStageLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbActiveStageLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbActiveStageLayer", CcbActiveStageLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/missionframe_active.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

#pragma mark -Initialize-

bool CcbActiveStageLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::Attach(this);
	return true;
}

void CcbActiveStageLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    setInfo();
    m_pTableDrop->reloadData();
}

void CcbActiveStageLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        if (ChallengeCtrl::Get()->getChallengeType() == ChallengeCtrl::kMoneyCat) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonFight, GuideBtnPos::E_CAT_FIGHT);
        }
    }
}

void CcbActiveStageLayer::onExit()
{
	CCLayer::onExit();
}

void CcbActiveStageLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbActiveStageLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDrop", CCLayer*, this->m_pLayerDrop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFight", CCScrollButton*, this->m_pControlButtonFight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCnt", CCLabelTTF*, this->m_pLabelTTFLeftCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttribute", CCSprite*, this->m_pSpriteAttribute);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelOpenLv", CCLabelTTF*, this->m_pLabelOpenLv);
	return false;
}

bool CcbActiveStageLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbActiveStageLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbActiveStageLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbActiveStageLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFight", CcbActiveStageLayer::onPressControlButtonFight);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbActiveStageLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pTableDrop = CCTableView::create(this, m_pLayerDrop->getContentSize());
    m_pTableDrop->setDirection( kCCScrollViewDirectionHorizontal );
    m_pTableDrop->setDelegate(this);
    m_pTableDrop->setAnchorPoint(CCPointZero);
    m_pTableDrop->setPosition(CCPointZero);
    m_pTableDrop->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerDrop->addChild(m_pTableDrop, 1);
    
}

void CcbActiveStageLayer::onPressControlButtonFight(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    StageCtrl::Get()->setSelectedStage(m_nSelActiveIdx);
    StageCtrl::Get()->setSelectStageId(m_wStageId);
    
    if (m_wLimitLv > CGameSession::GetRole()->GetwRoleLv()) {
        // 显示等级不足}
        CCString* pLimit = CCString::createWithFormat(GET_STR(Str_will_open_at_level), m_wLimitLv);
        FlyTextLayer::showTips(pLimit->getCString());
        return;
    }
    
    if (m_byLeftCnt == 0) {
        //付费购买次数}
        showBuyMessage();
        return;
    } else {
        CGameSession::SendSpecialBattle(StageCtrl::Get()->selectedActivityMapIdx(), m_wStageId, false);
        PetLoadingLayer::sharedLayer()->WaitForPacket();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("active_battle_enter");
#endif
    }
}


#pragma mark Public Method
void CcbActiveStageLayer::SetNodeData(int _idx)
{
    m_nSelActiveIdx = _idx;
}

void CcbActiveStageLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell) {
    
}

static const float fGap = 36.0f;
static const float fOrg = 18.0f;

CCTableViewCell* CcbActiveStageLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();

        CcbItemIconLayer* pIcon = dynamic_cast<CcbItemIconLayer*>( CcbManager::sharedManager()->LoadCcbItemIconLayer(this) );
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
    }
    return pCell;
}

unsigned int CcbActiveStageLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table) {
    return m_nPetCnt + m_nItemCnt;
}

void CcbActiveStageLayer::RefeashLayer() {
    PetLoadingLayer::sharedLayer()->End();
    
    if (m_nSelActiveIdx != StageCtrl::Get()->selectedStageIdx()) {
        return;
    }
    
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->selectedStage();
    // 剩余次数}
    if (m_byAttactCnt != stc.byAttackCnt || m_byMaxAttCnt != stc.byMaxAttCnt || m_byBuyCnt != stc.byBuyCnt) {
        m_byBuyCnt = stc.byBuyCnt;
        m_byAttactCnt = stc.byAttackCnt;
        m_byMaxAttCnt = stc.byMaxAttCnt;

        if (stc.byMaxAttCnt + stc.byBuyCnt > stc.byAttackCnt) {
            m_byLeftCnt = stc.byMaxAttCnt + stc.byBuyCnt - stc.byAttackCnt;
        } else {
            m_byLeftCnt = 0;
        }
        CCString* pLeftCnt = CCString::createWithFormat(GET_STR(Str_cnt_last), m_byLeftCnt);
        m_pLabelTTFLeftCnt->setString(pLeftCnt->getCString());
    }
}

CCSize CcbActiveStageLayer::cellSizeForTable(cocos2d::extension::CCTableView *table) {
    return CCSizeMake(fGap, fGap);
}

CCSize CcbActiveStageLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    return CCSizeMake(fGap, fGap);
}

void CcbActiveStageLayer::setClipRect(cocos2d::CCRect rect) {
    m_rect = rect;
    m_pControlButtonFight->setClipRect(rect);
}

#pragma mark Private Method
void CcbActiveStageLayer::setInfo()
{
    StageCtrl::STC_STAGE stc = StageCtrl::Get()->stageWithIdx(m_nSelActiveIdx);
    m_wStageId = stc.wStageId;
    m_pLabelTTFName->setString(stc.strName.c_str());
    
    // 属性}
    if (m_wIconId != stc.wIconId) {
        m_wIconId = stc.wIconId;
        CCSpriteFrame* pAttrSf = CPetCtrl::Get()->GetPetNaturePicSF(m_wIconId);
        m_pSpriteAttribute->setDisplayFrame(pAttrSf);
    }
    
    // 消耗体力}
    if (m_byCostEnergy != stc.byCostEnergy) {
        m_byCostEnergy = stc.byCostEnergy;
        CCString* pCostEnergy = CCString::createWithFormat(GET_STR(Str_energy_cost), m_byCostEnergy);
        m_pLabelTTFEnergy->setString(pCostEnergy->getCString());
    }
    
    // 剩余次数}
    if (m_byAttactCnt != stc.byAttackCnt || m_byMaxAttCnt != stc.byMaxAttCnt || m_byBuyCnt != stc.byBuyCnt) {
        m_byBuyCnt = stc.byBuyCnt;
        m_byAttactCnt = stc.byAttackCnt;
        m_byMaxAttCnt = stc.byMaxAttCnt;

        if (stc.byMaxAttCnt + stc.byBuyCnt > stc.byAttackCnt) {
            m_byLeftCnt = stc.byMaxAttCnt + stc.byBuyCnt - stc.byAttackCnt;
        } else {
            m_byLeftCnt = 0;
        }
        CCString* pLeftCnt = CCString::createWithFormat(GET_STR(Str_cnt_last), m_byLeftCnt);
        m_pLabelTTFLeftCnt->setString(pLeftCnt->getCString());
    }
    // 关卡开启等级}
    if (m_wLimitLv != stc.wRoleLvLimit) {
        m_wLimitLv = stc.wRoleLvLimit;
        if (m_wLimitLv != 0) {
            CCString* pLimitString = CCString::createWithFormat(GET_STR(Str_open_at_lv), m_wLimitLv);
            m_pLabelOpenLv->setString(pLimitString->getCString());
        } else {
            m_pLabelOpenLv->setVisible(false);
        }
    }
    
    m_vecDropId.clear();
    m_nPetCnt= stc.m_vecPetId.size();
    m_nItemCnt= stc.m_vecItemId.size();
    
    for (int i = 0; i < stc.m_vecPetId.size(); i++) {
        m_vecDropId.push_back(stc.m_vecPetId[i]);
    }
    for (int i = 0; i < stc.m_vecItemId.size(); i++) {
        m_vecDropId.push_back(stc.m_vecItemId[i]);
    }
}


void CcbActiveStageLayer::showBuyMessage()
{
    VipBuyConfig::STC_CONFIG_VIP_BUY* pVipBuyCfg = GET_CONFIG_STC(VipBuyConfig, m_byBuyCnt + 1);
    int nDollarCost = 0;
    
    // 总公可购买次数
    VipShowConfig::STC_VIP_SHOW_CONFIG* pVipShowCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
    
    if (ChallengeCtrl::Get()->getChallengeType() == ChallengeCtrl::kMoneyCat) {
        nDollarCost = pVipBuyCfg->wMoneyCat;
        m_byLeftBuyCnt = pVipShowCfg->wMoneyCatBuyMax - m_byBuyCnt;
    } else if (ChallengeCtrl::Get()->getChallengeType() == ChallengeCtrl::kEggTag) {
        nDollarCost = pVipBuyCfg->wSpecialStage;
        m_byLeftBuyCnt = pVipShowCfg->wActivityBuyMax - m_byBuyCnt;
    } else {
        CCString* pString = CCString::create(GET_STR(Str_cishuyiman));
        SystemMessage::showSystemMessage(0, NULL, pString->getCString());
        return;
    }
    
    if (m_byLeftBuyCnt == 0) {
        CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
        return;
    }
    
    CCString* pString = CCString::createWithFormat("%s\n%s", GET_STR(Str_show_buy_message), GET_STR(Str_today_left));
    snprintf(strBuf512, BUFFER_SIZE_512, pString->getCString(), nDollarCost, m_byLeftBuyCnt);
    SystemMessage::showSystemMessage(1, NULL, strBuf512, this, true);
}


void CcbActiveStageLayer::systemMessageOKTapped(SystemMessage *systemMessage) {
    if (m_byLeftBuyCnt > 0) {
        if (ChallengeCtrl::Get()->getChallengeType() == ChallengeCtrl::kMoneyCat) {
            CGameSession::SendBuyStageFightCnt(E_BUY_STAGE_MONEY_CAT, m_wStageId);
        } else if (ChallengeCtrl::Get()->getChallengeType() == ChallengeCtrl::kEggTag) {
            CGameSession::SendBuyStageFightCnt(E_BUY_STAGE_ACTIVE, m_wStageId);
        }
        PetLoadingLayer::sharedLayer()->WaitForPacket();
    } else {
//        FlyTextLayer::showTips(GET_STR(Str_vip_need_up));
        CShowJumpTip::Get()->Show(E_VIP_NOT_ENOUGH);
        return;
    }
}
