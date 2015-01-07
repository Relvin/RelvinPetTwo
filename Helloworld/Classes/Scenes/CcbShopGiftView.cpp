#include "CcbShopGiftView.h"
#include "UISupport.h"
#include "CcbManager.h"
#include "game_config.h"
#include "ShopDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbShopGiftView::CcbShopGiftView()
: m_pLayerGiftList(NULL)
, m_pControlButtonClose(NULL)
, m_pTableView(NULL)
{
    
    
}

CcbShopGiftView::~CcbShopGiftView()
{
	CC_SAFE_RELEASE_NULL(m_pLayerGiftList);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);

}


bool CcbShopGiftView::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    this->setTouchEnabled(true);
	// code here
	return true;
}

void CcbShopGiftView::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbShopGiftView::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbShopGiftView::onExit()
{
	CCLayer::onExit();
}

void CcbShopGiftView::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShopGiftView::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerGiftList", CCLayer*, this->m_pLayerGiftList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);

	return false;
}

bool CcbShopGiftView::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbShopGiftView::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShopGiftView::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShopGiftView::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbShopGiftView::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShopGiftView::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pTableView = CCTableView::create(this, m_pLayerGiftList->getContentSize());
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pLayerGiftList->addChild(m_pTableView, 1);
}



void CcbShopGiftView::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CShopDataMgr::Get()->setItemId(0);
    CShopDataMgr::Get()->setCellIndex(-1);
    this->removeFromParent();
}

#pragma mark - Touch Functions -
bool CcbShopGiftView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbShopGiftView::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 22, true);
}

#pragma mark - TableView Functions -
CCTableViewCell* CcbShopGiftView::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbShopGiftViewFrame* pLayer = (CcbShopGiftViewFrame*)CcbManager::sharedManager()->LoadCcbShopGiftViewFrame();
        pLayer->setAnchorPoint(ccp(0, 0));
        pLayer->setPosition(ccp(0, 0));
//        pLayer->setClipRect(m_clipRect);
        pCell->addChild(pLayer, 1, 123);
    }
    
    CcbShopGiftViewFrame* pNode = (CcbShopGiftViewFrame*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->setFrameInfoByItemIndex(vec_CellItems[idx]);
    }
    
    return pCell;
}

unsigned int CcbShopGiftView::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return vec_CellItems.size();
}

CCSize CcbShopGiftView::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerGiftList), 79);
}

void CcbShopGiftView::setItemsByChestId(uint32 dwChestId)
{
    vec_CellItems.clear();
    ChestConfig::STC_CONFIG_CHEST *pChestConfig = GET_CONFIG_STC(ChestConfig,dwChestId);
    if (!pChestConfig) {
        this->removeFromParent();
        return;
    }
    std::copy(pChestConfig->vecInfo.begin(), pChestConfig->vecInfo.end(), std::back_inserter(vec_CellItems));
    
    m_pTableView->reloadData();
}

void CcbShopGiftView::setItemsByVector(std::vector<ChestConfig::STC_UNITE_RESOURCE> &vec)
{
    vec_CellItems.clear();
    std::vector<ChestConfig::STC_UNITE_RESOURCE>::iterator iter = vec.begin();
    ChestConfig::STC_UNITE_RESOURCE confInfo ;
    for (; iter != vec.end(); ++iter) {
        confInfo.dwUniteId = iter->dwUniteId;
        confInfo.dwUniteCnt = iter->dwUniteCnt;
        if (confInfo.dwUniteId != 0) {
            vec_CellItems.push_back(confInfo);
        }
    }
    
    m_pTableView->reloadData();
}

