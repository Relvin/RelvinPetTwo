#include "CcbEventMySteryShopLayer.h"
#include "CcbManager.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "CCScrollViewWithBar.h"
#include "ItemDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EnumDefines.h"
#include "PacketDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "Instruments.h"
#include "Role.h"
#include "MusicCtrl.h"
#include "WorldInfoDataMgr.h"
#include "AnalysicsManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMySteryShopScene::CcbMySteryShopScene()
{
    
}

CcbMySteryShopScene::~CcbMySteryShopScene()
{
    
}

CCScene* CcbMySteryShopScene::scene()
{
    CCScene* pScene = CCScene::create();
    CcbMySteryShopScene* pLayer = CcbMySteryShopScene::create();
    if (!pLayer)
    {
        return NULL;
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool CcbMySteryShopScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbEventMySteryShopLayer(this));
    return true;
}

void CcbMySteryShopScene::onEnter()
{
    CCLayer::onEnter();
}

void CcbMySteryShopScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbMySteryShopScene::onExit()
{
    CCLayer::onExit();
}

void CcbMySteryShopScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}



CcbEventMySteryShopLayer::~CcbEventMySteryShopLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerEventViewSize);
    CC_SAFE_RELEASE_NULL(m_pControlButtonRefresh);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFRefCnt);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNum);
    CC_SAFE_RELEASE_NULL(m_pControlButtonFuse);
    CC_SAFE_RELEASE_NULL(m_pNodeShoperMystery);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftTime);
    CC_SAFE_RELEASE_NULL(m_pNodeShoperMJ);
    CC_SAFE_RELEASE_NULL(m_pControlButtonMysteryShop);
    CC_SAFE_RELEASE_NULL(m_pControlButtonMJShop);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMJLeftTime);
    CC_SAFE_RELEASE_NULL(m_pLayerTop);

    m_curScene = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEventMySteryShopLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEventMySteryShopLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEventMySteryShopLayer", CcbEventMySteryShopLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_mysteryshop.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
CcbEventMySteryShopLayer* CcbEventMySteryShopLayer::m_curScene = NULL;

bool CcbEventMySteryShopLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    m_curScene = this;
	// code here
	return true;
}

void CcbEventMySteryShopLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbEventMySteryShopLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

}

void CcbEventMySteryShopLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEventMySteryShopLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEventMySteryShopLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEventViewSize", CCLayer*, this->m_pLayerEventViewSize);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRefresh", CCControlButton*, this->m_pControlButtonRefresh);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRefCnt", CCLabelTTF*, this->m_pLabelTTFRefCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom2", CCLayer*, this->m_pLayerBottom2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum", CCLabelTTF*, this->m_pLabelTTFNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFuse", CCControlButton*, this->m_pControlButtonFuse);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeShoperMystery", CCNode*, this->m_pNodeShoperMystery);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftTime", CCLabelTTF*, this->m_pLabelTTFLeftTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeShoperMJ", CCNode*, this->m_pNodeShoperMJ);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMysteryShop", CCControlButton*, this->m_pControlButtonMysteryShop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMJShop", CCControlButton*, this->m_pControlButtonMJShop);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMJLeftTime", CCLabelTTF*, this->m_pLabelTTFMJLeftTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTop", CCLayer*, this->m_pLayerTop);
	return false;
}

bool CcbEventMySteryShopLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEventMySteryShopLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEventMySteryShopLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEventMySteryShopLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRefresh", CcbEventMySteryShopLayer::onPressControlButtonRefresh);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFuse", CcbEventMySteryShopLayer::onPressControlButtonFuse);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMysteryShop", CcbEventMySteryShopLayer::onPressControlButtonMysteryShop);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMJShop", CcbEventMySteryShopLayer::onPressControlButtonMJShop);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEventMySteryShopLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}

    m_clipRect.origin = getWorldPos(m_pLayerEventViewSize);
//    m_pLayerEventViewSize->setContentSize(CCSizeMake(getWidth(m_pLayerEventViewSize), getBottom(m_pLayerTop) - m_clipRect.origin.y));
    m_clipRect.size = m_pLayerEventViewSize->getContentSize();
    
    m_dwCostDollar = 0;
    m_dwCostRock = 0;
    arrGoods.clear();
    curOff = ccp(0, 1);
    
    refTime = g_EventData->getMySteryLeftTime();
    refMjTime = g_EventData->getMJShopLeftTime();
    
    schedule(schedule_selector(CcbEventMySteryShopLayer::updateForTime), 1.0);
    schedule(schedule_selector(CcbEventMySteryShopLayer::updateForMJTime), 1.0);
    m_pLabelTTFTime->setString(getLeftTimeFromInt(refTime)->getCString());
    m_pLabelTTFMJLeftTime->setString(getLeftTimeFromInt(refMjTime)->getCString());
    m_pLabelTTFMJLeftTime->setZOrder(3);
    m_pLabelTTFLeftTime->setString(getLeftTimeFromInt(refMjTime)->getCString());
    
    //秘境商人没开启时不显示
    if (!WorldInfoDataMgr::Get()->getMJShopOpen()) {
        g_EventData->setMyShopType(E_MY_SHOP_MYSTERY);
        m_pControlButtonMJShop->getParent()->setVisible(false);
    }
    
    m_table = CCTableView::create(this, m_pLayerEventViewSize->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    m_table->setTouchPriority(kCCMenuHandlerPriority - 21);
    CCTableViewWithBar *layer = CCTableViewWithBar::create(m_table);
    layer->setAnchorPoint(ccp(0, 0));
    layer->setPosition(ccp(0, 0));
    layer->setTag(111);
    m_pLayerEventViewSize->addChild(layer);
}

void CcbEventMySteryShopLayer::onPressControlButtonMysteryShop(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    g_EventData->setMyShopType(E_MY_SHOP_MYSTERY);
    loadData();
}

void CcbEventMySteryShopLayer::onPressControlButtonMJShop(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    g_EventData->setMyShopType(E_MY_SHOP_MJ);
    loadData();
}

void CcbEventMySteryShopLayer::onPressControlButtonRefresh(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	
    if (m_table) {
        curOff = m_table->getContentOffset();
    }
    //刷新石}
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("mystery_flush");
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendMySteryShopUpdate();
//    uint32 fuseCnt = g_PacketDataMgr->GetItemCountByIndex(E_MYSTERY_SHOP_UPDATE_ROCK);
//    CCString *str = CCString::create("");
//    if (fuseCnt >= m_dwCostRock) {
//        str->initWithFormat(GET_STR(Str_sure_reflash_mystery_rock), m_dwCostRock);
//    }
//    else
//    {
//        str->initWithFormat(GET_STR(Str_sure_reflash_mystery_dollar), m_dwCostDollar);
//    }
//    SystemMessage::showSystemMessage(1, CCDirector::sharedDirector()->getRunningScene(), str->getCString(), this);
}

void CcbEventMySteryShopLayer::onPressControlButtonFuse(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::ReplaceCurScene(kPetFuse);
}

void CcbEventMySteryShopLayer::loadData()
{
    //刷新描述}
    CCString* str = CCString::create("");
//    m_pLabelTTFText->setString(str->getCString());
    //刷新石}
    CRole* role = CGameSession::GetRole();
    uint32 fuseCnt = g_PacketDataMgr->GetItemCountByIndex(E_MYSTERY_SHOP_UPDATE_ROCK);
    str->initWithFormat("%d%s", fuseCnt, GET_STR(Str_ge));
    m_pLabelTTFRefCnt->setString(str->getCString());
    //当前融合石数量}
    str->initWithFormat("%d", role->GetdwResFarmNum());
    m_pLabelTTFNum->setString(str->getCString());
    
    //刷新列表}
    arrGoods.clear();
    if (g_EventData->getMyShopType() == E_MY_SHOP_MYSTERY) {
        arrGoods = g_EventData->getMySteryGoods();
        
        m_pNodeShoperMystery->setVisible(true);
        m_pControlButtonMysteryShop->setEnabled(false);
        m_pControlButtonMysteryShop->setZOrder(2);
        m_pLayerBottom2->setVisible(true);
        
        m_pControlButtonMJShop->setEnabled(true);
        m_pControlButtonMJShop->setZOrder(1);
        m_pNodeShoperMJ->setVisible(false);
    }
    else if (g_EventData->getMyShopType() == E_MY_SHOP_MJ){
        arrGoods = g_EventData->getMJShopGoods();
        
        m_pNodeShoperMystery->setVisible(false);
        m_pControlButtonMysteryShop->setEnabled(true);
        m_pControlButtonMysteryShop->setZOrder(1);
        m_pLayerBottom2->setVisible(false);
        
        m_pNodeShoperMJ->setVisible(true);
        m_pControlButtonMJShop->setEnabled(false);
        m_pControlButtonMJShop->setZOrder(2);
    }
    m_table->reloadData();
    
//    float contentH = m_table->getContentSize().height;// numberOfCellsInTableView(m_table)*cellSizeForTable(m_table).height;
//
//    if (curOff.y > 0 || curOff.y < m_table->getViewSize().height - contentH) {
//        curOff = ccp(0, m_table->getViewSize().height - contentH);
//    }
//    m_table->setContentOffset(curOff);
    
    dynamic_cast<CCTableViewWithBar*>(m_pLayerEventViewSize->getChildByTag(111))->checkIsShow(numberOfCellsInTableView(m_table), cellSizeForTable(m_table));
    
    schedule(schedule_selector(CcbEventMySteryShopLayer::updateForTime), 1.0);
}

CCTableViewCell* CcbEventMySteryShopLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        for (int i = 0; i < 2; i++) {
            CcbEventMySteryShopFrameLayer* node = dynamic_cast<CcbEventMySteryShopFrameLayer*>(CcbManager::sharedManager()->LoadCcbEventMySteryShopFrameLayer(this));
            if (i == 0) {
                node->setPosition(ccp(getWidth(m_pLayerEventViewSize) * 0.5f - 3, 1));
                node->setAnchorPoint(ccp(1, 0));
            }
            else
            {
                node->setPosition(ccp(getWidth(m_pLayerEventViewSize) * 0.5f + 3, 1));
                node->setAnchorPoint(ccp(0, 0));
            }
            
            node->setTag(i);
            cell->addChild(node);
            node->setClipRect(m_clipRect);
        }
        
    }
    for (int i = 0; i < 2; i++) {
        CcbEventMySteryShopFrameLayer *node = dynamic_cast<CcbEventMySteryShopFrameLayer*>(cell->getChildByTag(i));
        if (idx * 2 + i >= arrGoods.size()) {
            node->setVisible(false);
            continue;
        }
        if (node) {
            node->setVisible(true);
            node->loadData(arrGoods[idx * 2 + i]);
        }
    }
    
    return cell;
}
unsigned int CcbEventMySteryShopLayer::numberOfCellsInTableView(CCTableView *table)
{
    return ceil(arrGoods.size() / 2.0f);
}

CCSize CcbEventMySteryShopLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerEventViewSize), 68);
}

void CcbEventMySteryShopLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("mystery_flush");
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendMySteryShopUpdate();
}

void CcbEventMySteryShopLayer::updateForTime(float time)
{
    refTime --;
    if (refTime < 0) {
        unschedule(schedule_selector(CcbEventMySteryShopLayer::updateForTime));
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        CGameSession::SendMySteryShopUpdate();
    }
    m_pLabelTTFTime->setString(getLeftTimeFromInt(refTime)->getCString());
}

void CcbEventMySteryShopLayer::updateForMJTime(float time)
{
    refMjTime--;
    if (refMjTime < 0) {
        unschedule(schedule_selector(CcbEventMySteryShopLayer::updateForMJTime));
        m_pControlButtonMJShop->getParent()->setVisible(false);
        g_EventData->setMyShopType(E_MY_SHOP_MYSTERY);
        loadData();
    }
    m_pLabelTTFMJLeftTime->setString(getLeftTimeFromInt(refMjTime)->getCString());
    m_pLabelTTFLeftTime->setString(getLeftTimeFromInt(refMjTime)->getCString());
}

