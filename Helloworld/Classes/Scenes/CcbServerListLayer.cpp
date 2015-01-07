#include "CcbServerListLayer.h"
#include "CcbManager.h"
#include "CcbServerNode.h"
#include "ServerListCtrl.h"
#include "PetLoadingLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

const static int kServerTouchPriority = kCCMenuHandlerPriority;

CcbServerListLayer::~CcbServerListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerRecent1);
	CC_SAFE_RELEASE_NULL(m_pLayerRecent2);
	CC_SAFE_RELEASE_NULL(m_pLayerRecent3);
	CC_SAFE_RELEASE_NULL(m_pLayerAllScroll);
    CC_SAFE_RELEASE_NULL(mAnimationManager);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbServerListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbServerListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbServerListLayer", CcbServerListLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/server_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbServerListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbServerListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
}

void CcbServerListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    PetLoadingLayer::sharedLayer()->End();
}

void CcbServerListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbServerListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbServerListLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kServerTouchPriority, true);
}

bool CcbServerListLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

// Inhert MemberVariableAssigner
bool CcbServerListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRecent1", CcbServerNode*, this->m_pLayerRecent1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRecent2", CcbServerNode*, this->m_pLayerRecent2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerRecent3", CcbServerNode*, this->m_pLayerRecent3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerAllScroll", CCLayer*, this->m_pLayerAllScroll);
	return false;
}

bool CcbServerListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbServerListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbServerListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbServerListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbServerListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CCSize viewSize = m_pLayerAllScroll->getContentSize();
    CCPoint pos = m_pLayerAllScroll->getPosition();
    
    m_pTableList = CCTableView::create(this, viewSize);
    m_pTableList->setPosition(CCPointZero);
    m_pTableList->setDirection(kCCScrollViewDirectionVertical);
    m_pTableList->setVerticalFillOrder( kCCTableViewFillBottomUp );
    m_pTableList->setTouchPriority(kServerTouchPriority-2);
    m_pLayerAllScroll->addChild(m_pTableList, 105);
    m_pTableList->reloadData();
    
    m_pServerNode[0] = m_pLayerRecent1;
    m_pServerNode[1] = m_pLayerRecent2;
    m_pServerNode[2] = m_pLayerRecent3;
    
    int nRecnt[3];
    nRecnt[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_1);
    nRecnt[1] = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_2);
    nRecnt[2] = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_3);
    for (int i = 0; i < Recent_Cnt; i++) {
        if (nRecnt[i] == 0) {
            m_pServerNode[i]->setVisible(false);
        } else {
            m_pServerNode[i]->setTouchPriority(kServerTouchPriority-1);
            m_pServerNode[i]->setNodeData(nRecnt[i]);
        }
    }
}

void CcbServerListLayer::onSlideUp()
{
//    mAnimationManager->runAnimationsForSequenceNamed("move_out");
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbServerListLayer::removeSelfFromParent));
    removeSelfFromParent();
}

void CcbServerListLayer::removeSelfFromParent()
{
    removeFromParentAndCleanup(true);
}

#pragma mark CCTableView Delegate
void CcbServerListLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell) {
    if (cell) {
        CCLog("cell touched at index:%i", cell->getIdx());
    }
}

CCTableViewCell* CcbServerListLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) {
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbServerNode* pNode = dynamic_cast<CcbServerNode*>(CcbManager::sharedManager()->LoadCcbServerNode(this));
        pNode->setNodeData(idx);
        pNode->setPosition(ccp(107.0f, 14.0f));
        pNode->setTag(123);
        pCell->addChild(pNode);
    } else {
        CcbServerNode* pNode = dynamic_cast<CcbServerNode*>(pCell->getChildByTag(123));
        pNode->setNodeData(idx);
    }
    return pCell;
}

unsigned int CcbServerListLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return ServerListCtrl::Get()->getAreaNum();
}

CCSize CcbServerListLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(214.0f, 28.0f);
}


