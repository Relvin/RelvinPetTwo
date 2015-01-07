#include "CcbTowerRankListLayer.h"
#include "CcbManager.h"
#include "CcbTowerRankFrameLayer.h"
#include "TowerDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "MusicCtrl.h"

CcbTowerRankListLayer::~CcbTowerRankListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFlood);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRank);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_tableView);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTowerRankListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTowerRankListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTowerRankListLayer", CcbTowerRankListLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_ranklist.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTowerRankListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbTowerRankListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbTowerRankListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_tableView->reloadData();
}

void CcbTowerRankListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTowerRankListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTowerRankListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFlood", CCLabelTTF*, this->m_pLabelTTFFlood);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRank", CCLabelTTF*, this->m_pLabelTTFRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbTowerRankListLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTowerRankListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTowerRankListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTowerRankListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbTowerRankListLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTowerRankListLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    char szTemp[32] = "";
    //玩家自己当前排名}
    sprintf(szTemp, "%d", g_TowerDataMgr->GetTowerRank().dwCurRank);
    m_pLabelTTFRank->setString(szTemp);
    //玩家自己达到的最高层数}
    sprintf(szTemp, "%d", g_TowerDataMgr->GetTowerRank().dwMaxFloor);
    m_pLabelTTFFlood->setString(szTemp);
    
    m_tableView = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->retain();
    
    m_pLayerViewSize->addChild(m_tableView);
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 1);
}

void CcbTowerRankListLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 1);
}

bool CcbTowerRankListLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbTowerRankListLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    removeFromParent();
}

CCSize CcbTowerRankListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 95);
}

CCTableViewCell* CcbTowerRankListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbTowerRankFrameLayer(this);
        pNode->setPosition(getWidth(m_pLayerViewSize)*0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbTowerRankFrameLayer *pNode = (CcbTowerRankFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->loadData(idx);
        
    }//end if (pNode)
    
    return pCell;
}

unsigned int CcbTowerRankListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return g_TowerDataMgr->GetTowerRankList().size();
}





