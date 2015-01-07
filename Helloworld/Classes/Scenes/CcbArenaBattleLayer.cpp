#include "CcbArenaBattleLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "CcbArenaBattleListLayer.h"
#include "ArenaDataMgr.h"
#include "PetCtrl.h"
#include "ResourceStringClient.h"
#include "ResourceStringConverter.h"
#include "ConfigGet.h"
#include "GameSession.h"
#include "Role.h"
#include "PetLoadingLayer.h"
#include "GuideData.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "GuideBtnPos.h"

CcbArenaBattleLayer::~CcbArenaBattleLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonTeam);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRank);
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFBuyCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxRank);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRankText);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRankText2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRankReward);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaBattleLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaBattleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaBattleLayer", CcbArenaBattleLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_battle.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbArenaBattleLayer* CcbArenaBattleLayer::m_curScene = NULL;

bool CcbArenaBattleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
    
    return true;
}

bool CcbArenaBattleLayer::InitData()
{
    m_table = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setPosition(CCPointZero);
    m_table->setAnchorPoint(CCPointZero);
    m_pLayerViewSize->addChild(m_table, 1, 1234);
    m_table->setTouchPriority(kCCMenuHandlerPriority - 21);
    
    
    return true;
}

void CcbArenaBattleLayer::onEnter()
{
	CCLayer::onEnter();
    m_table->reloadData();
    m_table->scrollToIndex(cellNum-1);
}

void CcbArenaBattleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbArenaBattleLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbArenaBattleLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_4_JJC,
                                                 NULL
                                                 );
    }
}

void CcbArenaBattleLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaBattleLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaBattleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTeam", CCControlButton*, this->m_pControlButtonTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRank", CCControlButton*, this->m_pControlButtonRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFBuyCnt", CCLabelTTF*, this->m_pLabelTTFBuyCnt);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxRank", CCLabelTTF*, this->m_pLabelTTFMaxRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankText", CCLabelTTF*, this->m_pLabelTTFRankText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankText2", CCLabelTTF*, this->m_pLabelTTFRankText2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRankReward", CCLabelTTF*, this->m_pLabelTTFRankReward);
	return false;
}

bool CcbArenaBattleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaBattleLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaBattleLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaBattleLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTeam", CcbArenaBattleLayer::onPressControlButtonTeam);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRank", CcbArenaBattleLayer::onPressControlButtonRank);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaBattleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_clipRect.origin = getWorldPos(m_pLayerViewSize);
    m_pLayerViewSize->setContentSize(CCSizeMake(getWidth(m_pLayerViewSize), getBottom(getChildByTag(333)) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerViewSize->getContentSize();
    m_touchFlag = false;
    cellNum = CArenaDataMgr::Get()->GetBattleList().size();
    if (cellNum > 10) {
        cellNum = 10;
    }
    
    uint8 buyCnt = g_ArenaData->getBuyUseCnt();
    int cnt = 0;
    VipShowConfig::STC_VIP_SHOW_CONFIG* vipCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
    if (vipCfg && vipCfg->wArenaBuyMax > buyCnt) {
        cnt = vipCfg->wArenaBuyMax - buyCnt;
    }
    m_pLabelTTFBuyCnt->setString(CCString::createWithFormat("%d", cnt)->getCString());
    
    ArenaRewardConfig::STC_ARENA_REWARD_CONFIG *pConfig = GET_CONFIG_STC(ArenaRewardConfig, g_ArenaData->GetPlayerInfo().byGroupId);
    m_pLabelTTFRankReward->setString(CCString::createWithFormat("%d",pConfig->dwReputationMax)->getCString());
    m_pLabelTTFMaxRank->setString(CCString::createWithFormat("%d",CArenaDataMgr::Get()->GetPlayerInfo().dwMaxRank)->getCString());
    m_pLabelTTFRank->setString(CCString::createWithFormat("%d",CArenaDataMgr::Get()->GetPlayerInfo().dwRank)->getCString());
    
    m_pLabelTTFMaxRank->noStroke();
    m_pLabelTTFRank->noStroke();
    m_pLabelTTFRankText->noStroke();
    m_pLabelTTFRankText2->noStroke();
    
    InitData();
}


void CcbArenaBattleLayer::onPressControlButtonTeam(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_touchFlag) {
        return;
    }
    m_touchFlag = true;
    BackCtrl::InsertNextScene(kTeamScene);
}

void CcbArenaBattleLayer::onPressControlButtonRank(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_touchFlag) {
        return;
    }
    m_touchFlag = true;
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendArenaRankListRequest();
}


CCSize CcbArenaBattleLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 85 + 5);
}

CCTableViewCell* CcbArenaBattleLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbArenaBattleListLayer* pCcbNode = dynamic_cast<CcbArenaBattleListLayer*>(CcbManager::sharedManager()->LoadCcbArenaBattleListLayer(this));
        pCcbNode->setPosition(ccp(getWidth(m_pLayerViewSize)*0.5, 0));
        pCcbNode->setAnchorPoint(ccp(0.5, 0));
        pCcbNode->ignoreAnchorPointForPosition(false);
        pCcbNode->setClipRect(m_clipRect);
        pCell->addChild(pCcbNode, 1, 123);
    }
    
    CcbArenaBattleListLayer *pNode = (CcbArenaBattleListLayer*)pCell->getChildByTag(123);
    if (pNode) {
        pNode->loadData(idx, E_ARENA_NOMALE);
    }
    
    return pCell;
}

unsigned int CcbArenaBattleLayer::numberOfCellsInTableView(CCTableView *table)
{
    return cellNum;
}

void CcbArenaBattleLayer::handlerBuyPointResult()
{
    CCPoint off = m_table->getContentOffset();
    m_table->reloadData();
    m_table->setContentOffset(off);
}


