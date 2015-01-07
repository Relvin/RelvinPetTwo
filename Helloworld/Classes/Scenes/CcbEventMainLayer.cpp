#include "CcbEventMainLayer.h"
#include "CcbManager.h"
#include "EventDataMgr.h"
#include "GuideData.h"
#include "CcbEventIconLayer.h"
#include "UISupport.h"
#include "PetLoadingLayer.h"
#include "EnumDefines.h"

CcbEventMainLayer::~CcbEventMainLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerEventPos);
	CC_SAFE_RELEASE_NULL(m_pLayerTitleViewSize);
	CC_SAFE_RELEASE_NULL(m_pLayerTitleParent);

    CC_SAFE_RELEASE_NULL(_firstRechargeLayer);
    CC_SAFE_RELEASE_NULL(_growPlanLayer);
    CC_SAFE_RELEASE_NULL(_reward30Layer);
    CC_SAFE_RELEASE_NULL(_reward7Layer);
    CC_SAFE_RELEASE_NULL(_recoverEngeryLayer);
    CC_SAFE_RELEASE_NULL(_mySteryShopLayer);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventMainLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventMainLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventMainLayer", CcbEventMainLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_main.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventMainLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    g_EventData->SetEventMainLayer(this);
    
    CGameSession::SendRequestActiveList();
	return true;
}

void CcbEventMainLayer::onEnter()
{
	CCLayer::onEnter();
    CGameSession::Attach(this);
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEventMainLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    ChangeEvent();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEventMainLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
}

void CcbEventMainLayer::addGuideLayer()
{
//    GuideData::GetInstance()->addGuideofEnum(
//                                             GuideData::E_GUIDE_TRIGGER_2_REWARD,
//                                             NULL
//                                             );
}

void CcbEventMainLayer::onExit()
{
    CGameSession::Detach(this);
	CCLayer::onExit();
}

void CcbEventMainLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventMainLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEventPos", CCLayer*, this->m_pLayerEventPos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTitleViewSize", CCLayer*, this->m_pLayerTitleViewSize);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTitleParent", CCLayer*, this->m_pLayerTitleParent);

	return false;
}

bool CcbEventMainLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventMainLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventMainLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventMainLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventMainLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_clipRect.origin = getWorldPos(m_pLayerTitleViewSize);
    m_clipRect.size = m_pLayerTitleViewSize->getContentSize();
    g_EventData->loadEventType();
    
    m_pTableView = CCTableView::create(this, m_pLayerTitleViewSize->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pTableView->setPosition(ccp(m_pLayerTitleViewSize->getPositionX() - m_pLayerTitleViewSize->getContentSize().width * 0.5,
                               m_pLayerTitleViewSize->getPositionY() - m_pLayerTitleViewSize->getContentSize().height * 0.5));
    m_pTableView->setDelegate(this);
//    g_EventData->SetCurShowEventType(SHOW_FIRST_RECHARGE);
    m_pTableView->reloadData();
    if ((g_EventData->GetCurShowEventType() - 1) != 0 && (g_EventData->GetCurShowEventType() - 1) < g_EventData->getEventType().size() + g_EventData->getEventsChangeable().size()) {
        m_pTableView->scrollToIndex(g_EventData->GetCurShowEventType() - 1);
    }
    
    m_pLayerTitleParent->addChild(m_pTableView, 1, 111);
    
}

CCSize CcbEventMainLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(60, 60);
}

CCTableViewCell* CcbEventMainLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbEventIconLayer(this);
        pCell->addChild(pNode, 1, 1);
    }
    CcbEventIconLayer* pNode = (CcbEventIconLayer*)pCell->getChildByTag(1);
    if (pNode)
    {
        if (idx >= g_EventData->getEventType().size()) {
            pNode->SetShowData(g_EventData->getEventsChangeable()[idx - g_EventData->getEventType().size()].dwActiveId);
        }
        else
        {
            pNode->SetShowData(g_EventData->getEventType()[idx]);
        }
        
        pNode->m_pControlButtonEvent->setClipRect(m_clipRect);
    }
    
    return pCell;
}

unsigned int CcbEventMainLayer::numberOfCellsInTableView(CCTableView *table)
{
    return g_EventData->getEventType().size() + g_EventData->getEventsChangeable().size();
}

void CcbEventMainLayer::ChangeEvent()
{
    if (m_pLayerEventPos->getChildByTag(321))
    {
        m_pLayerEventPos->removeChildByTag(321);
    }
    
    CCNode* pNode = NULL;
    int nEventType = 0;
    
    
    if (g_EventData->getEventType().size() != 0) {
        nEventType = g_EventData->getEventType()[0];
    }
    if (g_EventData->GetCurShowEventType() > SHOW_TYPE_MAX) {
        for (int i = 0; i < g_EventData->getEventsChangeable().size(); i++) {
            if (g_EventData->GetCurShowEventType() == g_EventData->getEventsChangeable()[i].dwActiveId) {
                nEventType =g_EventData->GetCurShowEventType();
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < g_EventData->getEventType().size(); i++) {
            if (g_EventData->GetCurShowEventType() == g_EventData->getEventType()[i]) {
                nEventType =g_EventData->GetCurShowEventType();
                break;
            }
        }
    }
    
    
    switch (nEventType)
    {
        case SHOW_FIRST_RECHARGE:
            pNode = CcbManager::sharedManager()->LoadCcbEventFirstRechargeLayer(this);
            break;
        case SHOW_RECOVER_ENERGY:
            pNode = CcbManager::sharedManager()->LoadCcbEventRecoverEngergyLayer(this);
            break;
//        case SHOW_MY_STERY_SHOP:
//            pNode = CcbManager::sharedManager()->LoadCcbEventMySteryShopLayer(this);
//            break;
        default:
            if (nEventType != SHOW_GROW_PLAN) {
                CGameSession::SendRequestActiveInfoById(nEventType);
                STC_EVENT_CHANGEABLE_INFO* m_pChangeableInfo = g_EventData->getEventChangeableInfoByActiveId(g_EventData->GetCurShowEventType());
                if (m_pChangeableInfo ) {
                    if (m_pChangeableInfo->byNoticeType == E_ACTIVE_BLOAD_TYPE_NOTICE) {
                        pNode = CcbManager::sharedManager()->LoadCcbEventAnnounceLayer();
                    }
                    else
                    {
                        pNode = CcbManager::sharedManager()->LoadCcbEventGrowPlanLayer(this);
                    }
                }
            }
            else
            {
                pNode = CcbManager::sharedManager()->LoadCcbEventGrowPlanLayer(this);
            }
            break;
    }
    
    if (pNode)
    {
        m_pLayerEventPos->addChild(pNode, 10, 321);
    }
    for (int i = 0; i < g_EventData->getEventType().size() + g_EventData->getEventsChangeable().size(); i++) {
        CCTableViewCell* cell = m_pTableView->cellAtIndex(i);
        if (!cell) {
            continue;
        }
        CcbEventIconLayer* pNode = (CcbEventIconLayer*)cell->getChildByTag(1);
        if (!pNode) {
            continue;
        }
        if (pNode->m_showType == g_EventData->GetCurShowEventType()) {
            pNode->isSelected(true);
            continue;
        }
        pNode->isSelected(false);
    }
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.5f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEventMainLayer::removeLoading)),
                                       NULL
                                       )
                    );
}

void CcbEventMainLayer::removeLoading() {
    PetLoadingLayer::sharedLayer()->End();
}

void CcbEventMainLayer::RefeashLayer()
{
    if (m_pTableView) {
        CCPoint offpos = m_pTableView->getContentOffset();
        m_pTableView->reloadData();
        if (offpos.y < m_pTableView->getViewSize().height - m_pTableView->getContentSize().height) {
            offpos.y = m_pTableView->getViewSize().height - m_pTableView->getContentSize().height;
        }
        m_pTableView->setContentOffset(offpos);
    }
    
    if (!m_pLayerEventPos->getChildByTag(321)) {
        this->ChangeEvent();
    }
    
}



