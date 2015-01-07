#include "CcbShopNormalListLayer.h"
#include "CcbManager.h"
#include "CcbShopItemFrameLayer.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "CcbItemInfoButtonLayer.h"
#include "UISupport.h"
#include "GameSession.h"
#include "MusicCtrl.h"
#include "GlobalData.h"
#include "CcbJumpTipLayer.h"

CcbShopNormalListLayer::~CcbShopNormalListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonReduced);
	CC_SAFE_RELEASE_NULL(m_pControlButtonNormal);
	CC_SAFE_RELEASE_NULL(m_pLayerNormalList);
    CC_SAFE_RELEASE_NULL(m_pLayerParent);
    CC_SAFE_RELEASE_NULL(m_pTableViewTabNormal);
    
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbShopNormalListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbShopNormalListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbShopNormalListLayer", CcbShopNormalListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_normal_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbShopNormalListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    g_ShopData->SetDlgOpenNode(this);
    CGameSession::Attach(this);
	return true;
}

void CcbShopNormalListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbShopNormalListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_pTableViewTabNormal->reloadData();
    if (CShopDataMgr::Get()->getCellIndex() != -1) {
        this->onPressControlButtonReduced(NULL, CCControlEventTouchUpInside);
    }
    jumpToNeedItem();
}

void CcbShopNormalListLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
    CShowJumpTip::Get()->setJumpType(E_SHOW_JUMP_NULL);
    CShowJumpTip::Get()->setNeedItemId(0);
}

void CcbShopNormalListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbShopNormalListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReduced", CCControlButton*, this->m_pControlButtonReduced);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonNormal", CCControlButton*, this->m_pControlButtonNormal);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerNormalList", CCLayer*, this->m_pLayerNormalList);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
	return false;
}

bool CcbShopNormalListLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbShopNormalListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbShopNormalListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbShopNormalListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReduced", CcbShopNormalListLayer::onPressControlButtonReduced);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonNormal", CcbShopNormalListLayer::onPressControlButtonNormal);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbShopNormalListLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    float fHight = getBottom(m_pControlButtonReduced->getParent()) - getTop(m_pLayerParent);
    m_pLayerNormalList->setContentSize(CCSizeMake(m_pLayerNormalList->getContentSize().width, fHight));
    m_clipRect.origin = getWorldPos(m_pLayerNormalList);
    m_clipRect.size = m_pLayerNormalList->getContentSize();
    CreateShowList();

    m_nCurShowTab = 1;
    m_pControlButtonNormal->setEnabled(false);
    m_pControlButtonReduced->setEnabled(true);
    
    m_pTableViewTabNormal = CCTableView::create(this, m_pLayerNormalList->getContentSize());
    m_pTableViewTabNormal->setDirection(kCCScrollViewDirectionVertical);
    m_pTableViewTabNormal->setPosition(CCPointZero);
    m_pTableViewTabNormal->setAnchorPoint(CCPointZero);
    m_pTableViewTabNormal->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableViewTabNormal->retain();
    m_pTableViewTabNormal->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pLayerNormalList->addChild(m_pTableViewTabNormal, 1);
    
    if (GlobalData::shared()->getVipSwitch()) {
        m_pControlButtonReduced->setVisible(false);
        m_pControlButtonNormal->setVisible(false);
    }
    
}

void CcbShopNormalListLayer::CreateShowList()
{
    m_vecShowList[0].clear();
    m_vecShowList[1].clear();
    
    ITER_MAP_SHOP_ITEM_INFO iter;
    MAP_SHOP_ITEM_INFO mapTemp = CShopDataMgr::Get()->GetShopListByType(E_SHOP_TYPE_NORMAL);
    for (iter = mapTemp.begin(); iter != mapTemp.end(); iter++)
    {
        m_vecShowList[0].push_back(iter->second);
    }
    mapTemp = CShopDataMgr::Get()->GetShopListByType(E_SHOP_TYPE_REDUCED);
    for (iter = mapTemp.begin(); iter != mapTemp.end(); iter++)
    {
        m_vecShowList[1].push_back(iter->second);
    }
}

void CcbShopNormalListLayer::onPressControlButtonNormal(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_nCurShowTab = 1;
    m_pControlButtonNormal->setEnabled(false);
    m_pControlButtonReduced->setEnabled(true);
    m_pControlButtonNormal->setZOrder(2);
    m_pControlButtonReduced->setZOrder(1);
    m_pTableViewTabNormal->reloadData();
    CShopDataMgr::Get()->setItemId(0);
    CShopDataMgr::Get()->setCellIndex(-1);
}

void CcbShopNormalListLayer::onPressControlButtonReduced(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    m_nCurShowTab = 2;
    m_pControlButtonNormal->setEnabled(true);
    m_pControlButtonReduced->setEnabled(false);
    m_pControlButtonNormal->setZOrder(1);
    m_pControlButtonReduced->setZOrder(2);
    m_pTableViewTabNormal->reloadData();
    if (CShopDataMgr::Get()->getCellIndex() != -1) {
        m_pTableViewTabNormal->scrollToIndex(CShopDataMgr::Get()->getCellIndex());
        
    }
    
}



CCSize CcbShopNormalListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerNormalList), 79);
}

CCTableViewCell* CcbShopNormalListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CcbShopItemFrameLayer* pLayer = (CcbShopItemFrameLayer*)CcbManager::sharedManager()->LoadCcbShopItemFrameLayer(this);
        pLayer->setAnchorPoint(ccp(0.5, 0));
        pLayer->setPosition(ccp(getWidth(m_pLayerNormalList)*0.5, 0));
        pLayer->ignoreAnchorPointForPosition(false);
        pLayer->setClipRect(m_clipRect);
        pCell->addChild(pLayer, 1, 123);
    }

    CcbShopItemFrameLayer* pNode = (CcbShopItemFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        SHOP_ITEM_INFO showInfo = m_vecShowList[m_nCurShowTab-1][idx];
        pNode->loadData(showInfo);
        pNode->setCellIndex(idx);
        if (idx == CShopDataMgr::Get()->getCellIndex()) {
            pNode->itemIconTouchedCallBack(NULL, CShopDataMgr::Get()->getItemId());
            CShopDataMgr::Get()->setItemId(0);
            CShopDataMgr::Get()->setCellIndex(-1);
        }
    }
    
    return pCell;
}

unsigned int CcbShopNormalListLayer::numberOfCellsInTableView(CCTableView *table)
{
    if (m_nCurShowTab <= SHOP_TYPE_MAX)
    {
        return m_vecShowList[m_nCurShowTab-1].size();
    }
    return 0;
}

//重新刷界面}
void CcbShopNormalListLayer::RefeashLayer()
{
    CCPoint off = m_pTableViewTabNormal->getContentOffset();
    CreateShowList();
    m_pTableViewTabNormal->reloadData();
    float h = m_pTableViewTabNormal->getViewSize().height - m_pTableViewTabNormal->getContentSize().height;
    if (off.y < h) {
        off.y = h;
    }
    m_pTableViewTabNormal->setContentOffset(off);
}

void CcbShopNormalListLayer::jumpToNeedItem()
{
    if (CShowJumpTip::Get()->getJumpType() == E_ITEM_NOT_ENOUGH) {
        uint32 itemId = CShowJumpTip::Get()->getNeedItemId();
        if (!itemId) {
            return;
        }
        
        for (int i = 0; i < m_vecShowList[0].size(); i++) {
            SHOP_ITEM_INFO info = m_vecShowList[0][i];
            if (info.dwBuyContentId == itemId) {
                
                m_pTableViewTabNormal->scrollToIndex(i);
                break;
            }
            
        }
    }
}