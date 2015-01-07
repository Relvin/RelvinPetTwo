#include "CcbSystemNoticeLayer.h"
#include "CcbManager.h"
#include "SystemNoticeDataMgr.h"
#include "CcbSystemNoticeFrameLayer.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

CcbSystemNoticeLayer::~CcbSystemNoticeLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerView);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_tableView);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSystemNoticeLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSystemNoticeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSystemNoticeLayer", CcbSystemNoticeLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_notice.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSystemNoticeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbSystemNoticeLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbSystemNoticeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_tableView->reloadData();
}

void CcbSystemNoticeLayer::onExit()
{
	CCLayer::onExit();
}

void CcbSystemNoticeLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSystemNoticeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerView", CCLayer*, this->m_pLayerView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	return false;
}

bool CcbSystemNoticeLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSystemNoticeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSystemNoticeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSystemNoticeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbSystemNoticeLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSystemNoticeLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CreateTableView();
    m_tableView->scrollToIndex(g_SystemNoticeDataMgr->GetSystemNoticeMap().size() - 1);
}

void CcbSystemNoticeLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 2*kCCMenuHandlerPriority, true);
    m_pControlButtonClose->setTouchPriority(2*kCCMenuHandlerPriority);
    
}

bool CcbSystemNoticeLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbSystemNoticeLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParent();
}

CCSize CcbSystemNoticeLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    map<unsigned int, CCSize>::iterator iter = m_mapCellSize.find(idx);
    if (iter != m_mapCellSize.end())
    {
        return iter->second;
    }
    
    return CCSize(getWidth(m_pLayerView), 100);
}

CCTableViewCell* CcbSystemNoticeLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbSystemNoticeFrameLayer(this);
        
        pCell->addChild(pNode, 1, 123);
    }
    
    
    CcbSystemNoticeFrameLayer* pNode = (CcbSystemNoticeFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->setLocalTag(idx+1);
        pNode->CreatNoticeText();
        InserCellSize(idx, pNode->getLoaclSize());
        pNode->setPosition(getWidth(m_pLayerView) * 0.5, pNode->getLoaclSize().height*0.5);
        pNode->setAnchorPoint(ccp(0.5, 0.5));
        pNode->ignoreAnchorPointForPosition(false);
    }

    return pCell;
}

unsigned int CcbSystemNoticeLayer::numberOfCellsInTableView(CCTableView *table)
{
    return g_SystemNoticeDataMgr->GetSystemNoticeMap().size();
}

void CcbSystemNoticeLayer::CreateTableView()
{
    m_tableView = CCTableView::create(this, m_pLayerView->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setDelegate(this);
    m_tableView->retain();
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_pLayerView->addChild(m_tableView);
    
    m_tableView->setTouchPriority(2*kCCMenuHandlerPriority);
    m_tableView->reloadData();
    
}

void CcbSystemNoticeLayer::InserCellSize(unsigned int idx, CCSize size)
{
    map<unsigned int, CCSize>::iterator iter = m_mapCellSize.find(idx);
    if (iter != m_mapCellSize.end())
    {
        iter->second = size;
    }
    else
    {
        m_mapCellSize.insert(make_pair(idx, size));
    }
}
