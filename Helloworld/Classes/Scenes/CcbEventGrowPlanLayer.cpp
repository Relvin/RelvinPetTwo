#include "CcbEventGrowPlanLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "CcbEventGrowPlanFrameLayer.h"
#include "ShopDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EventDataMgr.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "ResourceStringClient.h"
#include "CcbGrowPlanTitleLayer.h"
#include "ResourcePic.h"

CcbEventGrowPlanLayer::~CcbEventGrowPlanLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonBuy);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRecharge);
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
    CC_SAFE_RELEASE_NULL(m_tableView);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFText);
    CC_SAFE_RELEASE_NULL(m_pLayerTop);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    CC_SAFE_RELEASE_NULL(m_pLayerTopType);
    CC_SAFE_RELEASE_NULL(m_pGrowPlanTitleLayer);
    CC_SAFE_RELEASE_NULL(m_pSpriteBgType);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventGrowPlanLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventGrowPlanLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventGrowPlanLayer", CcbEventGrowPlanLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_grow_plan.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventGrowPlanLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEventGrowPlanLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbEventGrowPlanLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        m_tableView->reloadData();
        m_bFirstLoad = false;
    }

}

void CcbEventGrowPlanLayer::onExit()
{
    CGameSession::Detach(this);
	CCLayer::onExit();
}

void CcbEventGrowPlanLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventGrowPlanLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBuy", CCControlButton*, this->m_pControlButtonBuy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRecharge", CCControlButton*, this->m_pControlButtonRecharge);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText", CCLabelTTF*, this->m_pLabelTTFText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTop", CCLayer*, this->m_pLayerTop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTopType", CCLayer*, this->m_pLayerTopType);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pGrowPlanTitleLayer", CcbGrowPlanTitleLayer*, this->m_pGrowPlanTitleLayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBgType", CCSprite*, this->m_pSpriteBgType);
    
	return false;
}

bool CcbEventGrowPlanLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbEventGrowPlanLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventGrowPlanLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventGrowPlanLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBuy", CcbEventGrowPlanLayer::onPressControlButtonBuy);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRecharge", CcbEventGrowPlanLayer::onPressControlButtonRecharge);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventGrowPlanLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GET_PIC(Pic_event_packer));
    
    float f_height = CCDirector::sharedDirector()->getWinSize().height - getHeight(m_pLayerTop) - getHeight(m_pLayerTopType) - getHeight(m_pLayerBottom);
    m_pLayerViewSize->setContentSize( CCSizeMake(getWidth(m_pLayerViewSize), f_height) );
//    m_pLayerViewSize->setPositionY(getBottom(m_pLayerParent) - m_pLayerViewSize->getContentSize().height * 0.5 + 5);
    
    m_clipRect.origin = getWorldPos(m_pLayerViewSize);
    m_clipRect.size = m_pLayerViewSize->getContentSize();
    
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        CCSpriteFrame* pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_1.png");
        if (pSpriteFrame) {
            m_pSpriteBgType->setDisplayFrame(pSpriteFrame);
        }
    }
    else
    {
        m_pChangeableInfo = g_EventData->getEventChangeableInfoByActiveId(g_EventData->GetCurShowEventType());
        if (m_pChangeableInfo) {
            CCString *picFilename = CCString::createWithFormat(GET_PIC(Pic_event_bg),m_pChangeableInfo->byRewardBloadType);
            CCSpriteFrame* pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picFilename->getCString());
            if (pSpriteFrame) {
                m_pSpriteBgType->setDisplayFrame(pSpriteFrame);
            }
        }
    }
    
    
    m_tableView = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->retain();
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerViewSize->addChild(m_tableView);
}

void CcbEventGrowPlanLayer::onPressControlButtonBuy(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendBuyGrowUp();
}

void CcbEventGrowPlanLayer::onPressControlButtonRecharge(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    g_ShopData->SetCurShopShowType(E_SHOP_TYPE_RECHARGE);
    CGameSession::SendRequestStorePayList();
}

CCSize CcbEventGrowPlanLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 79);
}

CCTableViewCell* CcbEventGrowPlanLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbEventGrowPlanFrameLayer(this);
        pNode->setPosition(ccp(getWidth(m_pLayerViewSize)*0.5, 0));
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbEventGrowPlanFrameLayer* pNode = (CcbEventGrowPlanFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
            pNode->loadData(idx+1);
        }
        else
        {
            pNode->loadData(idx);
        }
        
    }

    return pCell;
}

unsigned int CcbEventGrowPlanLayer::numberOfCellsInTableView(CCTableView *table)
{
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        return GET_CONFIG_MAP(GrowPlanConfig).size();
    }
    else
    {
        if (!m_pChangeableInfo) {
            return 0;
        }
        return m_pChangeableInfo->m_vecCells.size();
    }
}

void CcbEventGrowPlanLayer::RefeashLayer()
{
    
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        
    }
    else
    {
        m_pChangeableInfo = g_EventData->getEventChangeableInfoByActiveId(g_EventData->GetCurShowEventType());
        if (m_pChangeableInfo) {
            CCString *picFilename = CCString::createWithFormat(GET_PIC(Pic_event_bg),m_pChangeableInfo->byRewardBloadType);
            CCSpriteFrame* pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picFilename->getCString());
            if (pSpriteFrame) {
                m_pSpriteBgType->setDisplayFrame(pSpriteFrame);
            }
        }
        m_pGrowPlanTitleLayer->setShowInfo();
    }
    
    CCPoint offpos = m_tableView->getContentOffset();
    m_tableView->reloadData();
    if (offpos.y > m_tableView->getViewSize().height) {
        offpos.y = m_tableView->getViewSize().height - m_tableView->getContentSize().height;
    }
    else if(offpos.y < m_tableView->getViewSize().height - m_tableView->getContentSize().height)
    {
        offpos.y = m_tableView->getViewSize().height - m_tableView->getContentSize().height;
    }
    if (!m_bFirstLoad) {
        m_tableView->setContentOffset(offpos);
    }
    m_bFirstLoad = false;
    
    
}


