#include "CcbEventGrowPlanFrameLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "EventDataMgr.h"
#include "EnumDefines.h"
#include "MusicCtrl.h"

CcbEventGrowPlanFrameLayer::~CcbEventGrowPlanFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
	CC_SAFE_RELEASE_NULL(m_pLayerRewardIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGet);
	CC_SAFE_RELEASE_NULL(m_pSpriteGetYet);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventGrowPlanFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventGrowPlanFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventGrowPlanFrameLayer", CcbEventGrowPlanFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_grow_plan_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventGrowPlanFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}


// Inhert MemberVariableAssigner
bool CcbEventGrowPlanFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRewardIcon", CCLayer*, this->m_pLayerRewardIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGet", CCScrollButton*, this->m_pControlButtonGet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteGetYet", CCSprite*, this->m_pSpriteGetYet);

	return false;
}

bool CcbEventGrowPlanFrameLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbEventGrowPlanFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventGrowPlanFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventGrowPlanFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGet", CcbEventGrowPlanFrameLayer::onPressControlButtonGet);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventGrowPlanFrameLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    m_pLabelTTFTitle->noStroke();
    m_index = 0;
    m_touchFlag = false;
    m_pTableView = CCTableView::create(this, m_pLayerRewardIcon->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerRewardIcon->addChild(m_pTableView);
    
}

void CcbEventGrowPlanFrameLayer::onEnter()
{
    CCLayer::onEnter();
    m_pTableView->reloadData();
    if (m_pTableView->getContentSize().width <= m_pTableView->getViewSize().width) {
        m_pTableView->setTouchEnabled(false);
    }
    else
    {
        m_pTableView->setTouchEnabled(true);
    }
}

void CcbEventGrowPlanFrameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}


void CcbEventGrowPlanFrameLayer::onExit()
{
    CCLayer::onExit();
}

void CcbEventGrowPlanFrameLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

void CcbEventGrowPlanFrameLayer::onPressControlButtonGet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        // TODO:
        if (m_index == 0 || m_touchFlag) {
            return;
        }
        
        CGameSession::SendGrowUpReward(m_index);
    }
    else
    {
        if (m_touchFlag) {
            return;
        }
        CGameSession::SendGetActiveRewardByActIdAndCellId(g_EventData->GetCurShowEventType(),m_pChangeableCellInfo->dwRewId);
    }
    m_touchFlag = true;
	
}

void CcbEventGrowPlanFrameLayer::loadData(int index)
{
    m_index = index;
    uint8 byState = 0;
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        GrowPlanConfig::STC_GROW_PLAN_CONFIG* pConfig = GET_CONFIG_STC(GrowPlanConfig, m_index);
        if (!pConfig)
        {
            return;
        }
        
        m_pLabelTTFTitle->setString(pConfig->strTitle.c_str());
        
        byState = g_EventData->GetGrowPlanState(m_index);
    }
    else
    {
        
       STC_EVENT_CHANGEABLE_INFO* pChangeableInfo = g_EventData->getEventChangeableInfoByActiveId(g_EventData->GetCurShowEventType());
        if (!pChangeableInfo && m_index >= pChangeableInfo->m_vecCells.size()) {
            m_pChangeableCellInfo = NULL;
            return;
        }
        
        m_pChangeableCellInfo = &pChangeableInfo->m_vecCells[m_index];
        m_pLabelTTFTitle->setString(m_pChangeableCellInfo->strRewDesc.c_str());
        byState = m_pChangeableCellInfo->byStatus;
    }
    
    if (byState == E_REW_STATUS_CAN)//领取状态}
    {
        m_pControlButtonGet->setVisible(true);
        m_pControlButtonGet->setEnabled(true);
        m_pSpriteGetYet->setVisible(false);
    }
    else if (byState == E_REW_STATUS_DONE)//领过}
    {
        m_pControlButtonGet->setVisible(false);
        m_pSpriteGetYet->setVisible(true);
    }
    else//不可领}
    {
        m_pControlButtonGet->setVisible(true);
        m_pControlButtonGet->setEnabled(false);
        m_pSpriteGetYet->setVisible(false);
    }

}

void CcbEventGrowPlanFrameLayer::setClipRect(CCRect rect)
{
    m_ClipRect = rect;
//    m_pLayerIcon->setClipRect(rect);
    m_pControlButtonGet->setClipRect(rect);
}

#pragma mark - TableView Functions -
CCTableViewCell* CcbEventGrowPlanFrameLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbItemIconLayer(this);
        pNode->setAnchorPoint(ccp(0,0.5));
        pNode->setPosition(ccp(5,m_pLayerRewardIcon->getContentSize().height * 0.5f));
        pNode->setScale(0.85f);
        pCell->addChild(pNode);
        pNode->setTag(0);
    }
    CcbItemIconLayer* pItemIcon = (CcbItemIconLayer *)pCell->getChildByTag(0);
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        GrowPlanConfig::STC_GROW_PLAN_CONFIG* pConfig = GET_CONFIG_STC(GrowPlanConfig, m_index);
        
        if (pConfig && pItemIcon) {
            pItemIcon->loadIndexData(E_UNITE_TYPE_SPECIAL* E_UNITE_BASE_FABIO + E_SPECIAL_ID_DOLLAR);
            pItemIcon->showIconOnly();
            pItemIcon->showCnt(pConfig->dwCount);
        }
    }
    else
    {
            pItemIcon->loadIndexData(m_pChangeableCellInfo->m_vecRewardItems[idx].dwUniteId);
            pItemIcon->showIconOnly();
            pItemIcon->showCnt(m_pChangeableCellInfo->m_vecRewardItems[idx].dwuniteCnt);
    }
    
    return pCell;
}

unsigned int CcbEventGrowPlanFrameLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        return 1;
    }
    else
    {
        if (!m_pChangeableCellInfo) {
            return 0;
        }
        return m_pChangeableCellInfo->m_vecRewardItems.size();
    }
}

CCSize CcbEventGrowPlanFrameLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(45, 52);
}

