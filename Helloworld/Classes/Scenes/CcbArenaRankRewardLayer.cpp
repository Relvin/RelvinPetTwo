#include "CcbArenaRankRewardLayer.h"
#include "CcbManager.h"
#include "GameSession.h"
#include "Role.h"
#include "ConfigGet.h"
#include "CcbArenaRankRewardFrameLayer.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "PacketDataMgr.h"
#include "UISupport.h"
//#include "CcbItemInfoButtonLayer.h"

CcbArenaRankRewardLayer::~CcbArenaRankRewardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
    CC_SAFE_RELEASE_NULL(m_tableView);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaRankRewardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaRankRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaRankRewardLayer", CcbArenaRankRewardLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank_reward.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaRankRewardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbArenaRankRewardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaRankRewardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
   
    m_tableView->reloadData();
    
    CRole* role = CGameSession::GetRole();
    m_tableView->scrollToIndex(role->GetbyArenaGroup() - 1);
}

void CcbArenaRankRewardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRankRewardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaRankRewardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);

	return false;
}

bool CcbArenaRankRewardLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaRankRewardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaRankRewardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaRankRewardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaRankRewardLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    m_pLayerViewSize->setContentSize(CCSizeMake(getWidth(m_pLayerViewSize), getBottom(getChildByTag(333)) - getWorldPos(m_pLayerViewSize).y + 5));
    
    m_tableView = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->retain();
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    
    m_pLayerViewSize->addChild(m_tableView);
    
}

CCSize CcbArenaRankRewardLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 96 + 5);
}

CCTableViewCell* CcbArenaRankRewardLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbArenaRankRewardFrameLayer(this);
        pNode->setPosition(ccp(getWidth(m_pLayerViewSize)*0.5, 0));
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbArenaRankRewardFrameLayer *pNode = (CcbArenaRankRewardFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(idx+1);
    }
    
    return pCell;
}

unsigned int CcbArenaRankRewardLayer::numberOfCellsInTableView(CCTableView *table)
{
    return GET_CONFIG_MAP(ArenaRewardConfig).size();
}








