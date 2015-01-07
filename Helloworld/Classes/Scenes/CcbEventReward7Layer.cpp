#include "CcbEventReward7Layer.h"
#include "CcbManager.h"
#include "CcbEventRewardFrameLayer.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "Role.h"
#include "GameSession.h"
#include "CcbItemInfoButtonLayer.h"
#include "UISupport.h"
#include "MusicCtrl.h"

CcbEventReward7Layer::~CcbEventReward7Layer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerEventViewSize);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventReward7Layer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventReward7Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventReward7Layer", CcbEventReward7LayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_reward_7.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEventReward7Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbEventReward7Layer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
}

void CcbEventReward7Layer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    loadData();
}

void CcbEventReward7Layer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
}

void CcbEventReward7Layer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventReward7Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEventViewSize", CCLayer*, this->m_pLayerEventViewSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	return false;
}

bool CcbEventReward7Layer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventReward7Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventReward7Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventReward7Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbEventReward7Layer::onPressControlButtonClose);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventReward7Layer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 21);
    
    m_clitRect.origin = getWorldPos(m_pLayerEventViewSize);
    m_clitRect.size = m_pLayerEventViewSize->getContentSize();
    
    m_tableView = CCTableView::create(this, m_pLayerEventViewSize->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerEventViewSize->addChild(m_tableView);
    
}

void CcbEventReward7Layer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    setVisible(false);
    removeFromParent();
}

void CcbEventReward7Layer::loadData()
{
    m_tableView->reloadData();
    CRole* pRole = CGameSession::GetRole();
    m_tableView->scrollToIndex(pRole->GetdwSevenRewDay() - 1);
}


CCSize CcbEventReward7Layer::cellSizeForTable(CCTableView *table)
{
    return CCSize(getWidth(m_pLayerEventViewSize), 96 + 5);
}

CCTableViewCell* CcbEventReward7Layer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CcbEventRewardFrameLayer *pNode = (CcbEventRewardFrameLayer*)CcbManager::sharedManager()->LoadCcbEventRewardFrameLayer(this);
        pNode->setPosition(getWidth(m_pLayerEventViewSize)*0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
        pNode->setClipRect(m_clitRect);
    }
    
    CcbEventRewardFrameLayer *pNode = (CcbEventRewardFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(idx+1, E_EVENT_REWARD_DAY_7);
        
    }//end if (pNode)
    
    return pCell;
}

unsigned int CcbEventReward7Layer::numberOfCellsInTableView(CCTableView *table)
{
    return 7;
}

void CcbEventReward7Layer::RefeashLayer()
{
    m_tableView->reloadData();
    CRole* role = CGameSession::GetRole();
    m_tableView->scrollToIndex(role->GetdwSevenRewDay() - 1);
}

bool CcbEventReward7Layer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbEventReward7Layer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 10, true);
}
