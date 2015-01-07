#include "CcbItemListLayer.h"
//#include "CcbManager.h"
#include "CcbItemFrameLayer.h"
#include "ItemDataMgr.h"
#include "BackCtrl.h"
#include "ConfigData.h"
#include "ConfigGet.h"
#include "CCScrollViewWithBar.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "GameSession.h"
#include "CcbManager.h"
#include "Role.h"
#include "EnumDefines.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "FlyTextLayer.h"
#include "StageScene.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "EventDataMgr.h"
#include "GuideData.h"
#include "PacketDataMgr.h"
#include "BuyDataMgr.h"
#include "CcbSystemLayer2.h"
#include "CcbJumpTipLayer.h"

#include <algorithm>

CcbItemListLayer::~CcbItemListLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerForView);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxCount);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurCount);
    CC_SAFE_RELEASE_NULL(m_pLayerDown);
    CC_SAFE_RELEASE_NULL(m_pControlButtonExpandBag);
    CC_SAFE_RELEASE_NULL(m_pControlButtonMaterial);
    CC_SAFE_RELEASE_NULL(m_pControlButtonNormal);
    CC_SAFE_RELEASE_NULL(m_pLayerUp);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbItemListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbItemListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbItemListLayer", CcbItemListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbItemListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	//setTouchEnabled(true);
    //m_vecShowList.clear();
    //g_ItemData->ClearItemShowList();
    return true;
}

void CcbItemListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    //CCLOG("ItemListLayer Retain Cnt:%d", this->retainCount());
    CGameSession::Attach(this);
    CGameSession::GetRole()->Attach(this);
//    m_pLayerForView->setPositionX(m_pLayerForView->getPositionX() + CCDirector::sharedDirector()->getWinSize().width);
}

void CcbItemListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    changeTab();
    
//    m_pLayerForView->runAction(CCSequence::create(CCMoveBy::create(TRANS_DUR * 0.5, ccp(-CCDirector::sharedDirector()->getWinSize().width, 0)),CCCallFunc::create(this, callfunc_selector(CcbItemListLayer::animationFinishCallBack)),NULL));
}

void CcbItemListLayer::animationFinishCallBack()
{
//    if (g_ItemData->GetItemShowMode() == MODE_SHOW_NORMAL_ITEM)
//    {
//        m_pControlButtonExpandBag->setVisible(true);
//    }
}

void CcbItemListLayer::onExit()
{
	CCLayer::onExit();
    m_pControlButtonExpandBag->setVisible(false);
    CGameSession::Detach(this);
    CGameSession::GetRole()->Detach(this);
}

void CcbItemListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbItemListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerForView", CCLayer*, this->m_pLayerForView);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxCount", CCLabelTTF*, this->m_pLabelTTFMaxCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurCount", CCLabelTTF*, this->m_pLabelTTFCurCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDown", CCLayer*, this->m_pLayerDown);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExpandBag", CCControlButton*, this->m_pControlButtonExpandBag);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMaterial", CCControlButton*, this->m_pControlButtonMaterial);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonNormal", CCControlButton*, this->m_pControlButtonNormal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);
    
	return false;
}

bool CcbItemListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbItemListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbItemListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbItemListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMaterial", CcbItemListLayer::onPressControlButtonMaterial);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonNormal", CcbItemListLayer::onPressControlButtonNormal);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressButtonExpandBagCallBack", CcbItemListLayer::onPressButtonExpandBagCallBack);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbItemListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    CreateTableViewData();
    //CreateChosenTagData();
    BuyDataMgr::Get()->setChangeToBuyScene(false);
    CGameSession::SendReqShopCnt();
//    m_pControlButtonExpandBag->setVisible(false);
    m_curItemType = E_ITEM_USE_NORMAL;
    m_offPos = ccp(0, 1);
    m_pLayerUp->getChildByTag(3)->setZOrder(3);

    //背包数量显示}
    char szTemp[64] = "";
    sprintf(szTemp, "0");
    m_vecShowList.clear();

    sprintf(szTemp, "%lu", g_ItemData->GetVecShowItemIndex().size());
    m_pLabelTTFCurCount->setString(szTemp);
    
    sprintf(szTemp, "%d", CGameSession::GetRole()->GetdwItemBagCnt());
    m_pLabelTTFMaxCount->setString(szTemp);
    
    m_clipRect.origin = getWorldPos(m_pLayerForView);
    float h = getBottom(m_pLayerUp) - m_clipRect.origin.y;
    m_pLayerForView->setContentSize(CCSizeMake(getWidth(m_pLayerForView), h));
    m_clipRect.size = m_pLayerForView->getContentSize();

    m_tableView = CCTableView::create(this, m_pLayerForView->getContentSize());
    m_tableView->setDirection(kCCScrollViewDirectionVertical);
    m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_tableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_tableView->setPosition(CCPointZero);
    m_tableView->setAnchorPoint(CCPointZero);
    m_pLayerForView->addChild(m_tableView);
        
    m_pControlButtonNormal->setEnabled(false);
    m_pControlButtonNormal->setZOrder(2);
    m_pControlButtonMaterial->setEnabled(true);
    m_pControlButtonMaterial->setZOrder(1);
}

void CcbItemListLayer::onPressControlButtonMaterial(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    m_curItemType = E_ITEM_USE_EVO_MATERIAL;
    m_offPos = ccp(0, 1);
    m_pControlButtonNormal->setEnabled(true);
    m_pControlButtonNormal->setZOrder(1);
    m_pControlButtonMaterial->setEnabled(false);
    m_pControlButtonMaterial->setZOrder(2);
    
    changeTab();
}

void CcbItemListLayer::onPressControlButtonNormal(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    m_curItemType = E_ITEM_USE_NORMAL;
    m_offPos = ccp(0, 1);
    m_pControlButtonNormal->setEnabled(false);
    m_pControlButtonNormal->setZOrder(2);
    m_pControlButtonMaterial->setEnabled(true);
    m_pControlButtonMaterial->setZOrder(1);
    
    changeTab();
}

void CcbItemListLayer::onPressButtonExpandBagCallBack(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BuyDataMgr::STC_BUY sBag;
    sBag = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_ITEM_BAG);
    BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_ITEM_BAG);
    CSystemMessage2::Get()->Show(E_TYPE_ITEM_BAG, sBag.dwCostDollar, sBag.dwEarnCnt);
}

void CcbItemListLayer::changeTab()
{
    m_vecShowList.clear();
    std::vector<uint32> arrItem = g_ItemData->GetVecShowItemIndex();
    
    for (int i = 0; i < arrItem.size(); i++) {
        const CItem* item = g_PacketDataMgr->GetItemInfoByIndex(arrItem[i]);
        if (!item) {
            continue;
        }
        //进阶材料 和 非进阶材料
        if (m_curItemType == E_ITEM_USE_EVO_MATERIAL ){
            if(item->GetConfigData().byType == E_ITEM_USE_EVO_MATERIAL) {
                m_vecShowList.push_back(arrItem[i]);
            }
        }
        else{
            if (item->GetConfigData().byType != E_ITEM_USE_EVO_MATERIAL) {
                m_vecShowList.push_back(arrItem[i]);
            }
        }
    }
    
    sort(m_vecShowList.begin(), m_vecShowList.end(), cmpItem);
    int viewHeight = m_tableView->getViewSize().height;

    m_tableView->reloadData();
    
    int curHeight = m_tableView->getContentSize().height;
    if (m_offPos.y > 0 || m_offPos.y < viewHeight - curHeight)
    {
        m_offPos.y = (viewHeight - curHeight);
    }
    
    m_tableView->setContentOffset(m_offPos);
}


void CcbItemListLayer::RefeashLayer()
{
    m_offPos = m_tableView->getContentOffset();
    changeTab();
    //背包数量显示}
    char szTemp[64] = "";
    sprintf(szTemp, "%lu", g_ItemData->GetVecShowItemIndex().size());
    m_pLabelTTFCurCount->setString(szTemp);
    
    sprintf(szTemp, "%d", CGameSession::GetRole()->GetdwItemBagCnt());
    m_pLabelTTFMaxCount->setString(szTemp);
}

bool CcbItemListLayer::cmpItem(uint32 p, uint32 q)
{
    const CItem* pItem_1 = g_PacketDataMgr->GetItemInfoByIndex(p);
    const CItem* pItem_2 = g_PacketDataMgr->GetItemInfoByIndex(q);
    
    int flag1 = 0;
    int flag2 = 0;
    
    if (!pItem_1 || !pItem_2) {
        return false;
    }
    
    switch (pItem_1->GetConfigData().byType)
    {
        case E_ITEM_USE_BOX:
            flag1 = 2;
            break;
        case E_ITEM_USE_ENERGY:
            //可以使用}
            flag1 = 1;
            break;
        default:
            
            break;
    }
    
    flag1 = flag1 * 10000 + pItem_1->GetConfigData().byQuality;
    
    switch (pItem_2->GetConfigData().byType)
    {
        case E_ITEM_USE_BOX:
            flag2 = 2;
            break;
        case E_ITEM_USE_ENERGY:
            //可以使用}
            flag2 = 1;
            break;
        default:
            
            break;
    }
    
    flag2 = flag2 * 10000 + pItem_2->GetConfigData().byQuality;
    
    return flag1 > flag2;
    
}

CCSize CcbItemListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerForView), 91 + 5);
}

CCTableViewCell* CcbItemListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbItemFrameLayer(this);
        pNode->setPosition(getWidth(m_pLayerForView) *0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbItemFrameLayer* pNode = (CcbItemFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->setItemShowIndex(m_vecShowList[idx]);
        pNode->CreateShowData();
        pNode->setClipRect(m_clipRect);
    }
    
    return pCell;
}

unsigned int CcbItemListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecShowList.size();
}

void CcbItemListLayer::dwItemBagCntChanged(uint32 cnt)
{
    m_pLabelTTFMaxCount->setString(CCString::createWithFormat("%d", cnt)->getCString());
}



void CcbItemListLayer::jumpToNeedItem()
{
    if (CShowJumpTip::Get()->getJumpType() == E_ITEM_NOT_ENOUGH) {
        uint32 itemId = CShowJumpTip::Get()->getNeedItemId();
        if (!itemId) {
            return;
        }
        
        for (int i = 0; i < m_vecShowList.size(); i++) {
            if (m_vecShowList[i] == itemId) {
                m_tableView->scrollToIndex(i);
                break;
            }
            
        }
    }
}