#include "CcbArenaRankLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "CcbArenaRankListLayer.h"
#include "ArenaDataMgr.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "ResourceStringConverter.h"
#include "GameSession.h"
#include "Role.h"
#include "CcbArenaBattleListLayer.h"
#include "UISupport.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

CcbArenaRankLayer::~CcbArenaRankLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerViewSize);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbArenaRankLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbArenaRankLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbArenaRankLayer", CcbArenaRankLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbArenaRankLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

bool CcbArenaRankLayer::InitData()
{
    CCTableView* tableView = CCTableView::create(this, m_pLayerViewSize->getContentSize());
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(CCPointZero);
    tableView->setAnchorPoint(CCPointZero);
    m_pLayerViewSize->addChild(tableView);
    tableView->reloadData();
    tableView->setTouchPriority(kCCMenuHandlerPriority - 22);

    return true;
}

void CcbArenaRankLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbArenaRankLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
}

void CcbArenaRankLayer::onExit()
{
	CCLayer::onExit();
}

void CcbArenaRankLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbArenaRankLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerViewSize", CCLayer*, this->m_pLayerViewSize);

	return false;
}

bool CcbArenaRankLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbArenaRankLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbArenaRankLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbArenaRankLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
//    void onPressControlButtonTeam(CCObject* pSender, CCControlEvent event);
//	void onPressControlButtonRank(CCObject* pSender, CCControlEvent event);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbArenaRankLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_clipRect.origin = getWorldPos(m_pLayerViewSize);
    m_pLayerViewSize->setContentSize(CCSizeMake(getWidth(m_pLayerViewSize), getBottom(getChildByTag(333)) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerViewSize->getContentSize();
    
    cellNum = CArenaDataMgr::Get()->GetRankList().size();
    if (cellNum > 20)
    {
        cellNum = 20;
    }
    InitData();
}

//void CcbArenaRankLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
//{
//	// TODO:
//    BackCtrl::BacktoUpperScene();
//}

CCSize CcbArenaRankLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerViewSize), 85 + 5);
}

CCTableViewCell* CcbArenaRankLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
   
    if (!pCell)
    {
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

        VEC_RANK_LIST tempList = CArenaDataMgr::Get()->GetRankList();
        pNode->loadData(idx, E_ARENA_RANK);
    }
    
    return pCell;
}

unsigned int CcbArenaRankLayer::numberOfCellsInTableView(CCTableView *table)
{
    return cellNum;
}


