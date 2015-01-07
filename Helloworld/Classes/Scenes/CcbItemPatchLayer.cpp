#include "CcbItemPatchLayer.h"
#include "CcbManager.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"
#include "GuideData.h"
#include "StageScene.h"
#include "PetLoadingLayer.h"
#include "EventDataMgr.h"
#include "BackCtrl.h"
#include "UISupport.h"
#include "PacketDataMgr.h"
#include "Item.h"
#include "ItemDataMgr.h"
#include "EnumDefines.h"
#include "CcbPatchFrameLayer.h"

#include <algorithm>

USING_NS_CC;
USING_NS_CC_EXT;


ItemPatchScene::ItemPatchScene()
: m_pLabelTTFName(NULL)
{
    
}

ItemPatchScene::~ItemPatchScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* ItemPatchScene::scene()
{
    CCScene *scene = CCScene::create();
    
    ItemPatchScene *layer = ItemPatchScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ItemPatchScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbItemPatchLayer(this));
    return true;
}

bool ItemPatchScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    return false;
}

SEL_MenuHandler ItemPatchScene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

SEL_CCControlHandler ItemPatchScene::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    return NULL;
}


void ItemPatchScene::onEnter()
{
    CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_unit_7));
    }
}



#pragma mark - Constructor -
CcbItemPatchLayer::CcbItemPatchLayer()
: m_pLayerForView (NULL)
, m_pLayerDown (NULL)
, m_pControlButtonJingYing (NULL)
, m_pControlButtonMySteryShop (NULL)
, m_pLayerUp (NULL)
, m_pSpriteLine(NULL)
, m_pCurButton(NULL)
, m_clipRect(0,0,0,0)
, m_pTableView(NULL)
, m_pSpriteTip_Pet(NULL)
, m_pSpriteTip_Equip(NULL)
, m_pSpriteTip_Emblem(NULL)
, m_offPos(0,0)
{
    
    m_vecShowList.clear();
}

CcbItemPatchLayer::~CcbItemPatchLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerForView);
	CC_SAFE_RELEASE_NULL(m_pLayerDown);
	CC_SAFE_RELEASE_NULL(m_pControlButtonJingYing);
	CC_SAFE_RELEASE_NULL(m_pControlButtonMySteryShop);
	CC_SAFE_RELEASE_NULL(m_pLayerUp);
    CC_SAFE_RELEASE_NULL(m_pSpriteLine);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip_Pet);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip_Equip);
    CC_SAFE_RELEASE_NULL(m_pSpriteTip_Emblem);
    m_vecShowList.clear();

}

#pragma mark - Initialization -
bool CcbItemPatchLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbItemPatchLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerForView", CCLayer*, this->m_pLayerForView);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDown", CCLayer*, this->m_pLayerDown);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonJingYing", CCControlButton*, this->m_pControlButtonJingYing);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMySteryShop", CCControlButton*, this->m_pControlButtonMySteryShop);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLine", CCSprite*, this->m_pSpriteLine);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip_Pet", CCSprite*, this->m_pSpriteTip_Pet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip_Equip", CCSprite*, this->m_pSpriteTip_Equip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTip_Emblem", CCSprite*, this->m_pSpriteTip_Emblem);

	return false;
}

bool CcbItemPatchLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbItemPatchLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbItemPatchLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbItemPatchLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonJingYing", CcbItemPatchLayer::onPressControlButtonJingYing);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMySteryShop", CcbItemPatchLayer::onPressControlButtonMySteryShop);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTab", CcbItemPatchLayer::onPressControlButtonTab);

	return NULL;
}

#pragma mark - NodeLoaded -
// Inhert CCNodeLoaderListener
void CcbItemPatchLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pSpriteLine->setZOrder(2);
    m_pControlButtonJingYing->getParent()->setVisible(false);
    m_clipRect.origin = getWorldPos(m_pLayerForView);
    m_pLayerForView->setContentSize(CCSizeMake(getWidth(m_pLayerForView), getBottom(m_pLayerUp) - m_clipRect.origin.y));
    m_clipRect.size = m_pLayerForView->getContentSize();
    
    m_pTableView = CCTableView::create(this, m_pLayerForView->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 21);
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pLayerForView->addChild(m_pTableView);
    
    
    m_pSpriteTip_Pet->setZOrder(4);
    m_pSpriteTip_Equip->setZOrder(4);
    m_pSpriteTip_Emblem->setZOrder(4);
    
    checkTip();
}

#pragma mark - onEnter & onExit -
void CcbItemPatchLayer::onEnter()
{
    CCLayer::onEnter();
    CGameSession::Attach(this);
}

void CcbItemPatchLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    this->onPressControlButtonTab(m_pLayerUp->getChildByTag(0), CCControlEventTouchUpInside);
}

void CcbItemPatchLayer::onExit()
{
    CGameSession::Detach(this);
    CCLayer::onExit();
}

void CcbItemPatchLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functions -
void CcbItemPatchLayer::onPressControlButtonJingYing(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_SPECIAL);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    StageCtrl::Get()->setKind(StageCtrl::kSpecialStage);
    
    CGameSession::SendNormalMap();
}

void CcbItemPatchLayer::onPressControlButtonMySteryShop(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_MY_STERY_SHOP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    g_EventData->setMyShopType(E_MY_SHOP_MYSTERY);
    CGameSession::SendReqMJShopList();
    CGameSession::SendReqMySteryShopList();
}

void CcbItemPatchLayer::onPressControlButtonTab(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    CCControlButton* pButton = (CCControlButton*)pSender;
    if (!pButton) {
        return;
    }
    if (m_pCurButton) {
        m_pCurButton->setEnabled(true);
    }
    pButton->setEnabled(false);
    pButton->setZOrder(1);
    m_pCurButton = pButton;
    CCNode* pNode = NULL;
    for (int i = 0; i < 3; i++) {
        pNode = m_pLayerUp->getChildByTag(i);
        pNode->setZOrder(0 - abs(pNode->getTag() - pButton->getTag()));
    }
    m_offPos = ccp(0, 1);
    this->changeShowInfoByTab(pButton->getTag());
}


#pragma mark - TableView Functions -
CCSize CcbItemPatchLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSize(getWidth(m_pLayerForView), 91 + 5);
}

CCTableViewCell* CcbItemPatchLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    if (!pCell)
    {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbPatchFrameLayer();
        pNode->setPosition(getWidth(m_pLayerForView) *0.5, 0);
        pNode->setAnchorPoint(ccp(0.5, 0));
        pNode->ignoreAnchorPointForPosition(false);
        pCell->addChild(pNode, 1, 123);
    }
    
    CcbPatchFrameLayer* pNode = (CcbPatchFrameLayer*)pCell->getChildByTag(123);
    if (pNode)
    {
        pNode->setItemShowIndex(m_vecShowList[idx]);
        pNode->setClipRect(m_clipRect);
    }
    
    return pCell;
}

unsigned int CcbItemPatchLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_vecShowList.size();
}

#pragma mark - Self Functions -
void CcbItemPatchLayer::changeShowInfoByTab(int tab)
{
    m_vecShowList.clear();
    std::vector<uint32> arrItem = g_ItemData->GetVecPetChip();

    int nCuritemType = 0;
    switch (tab) {
        case 0:
        {
            nCuritemType = E_ITEM_USE_PET_PATCH;
            break;
        }
        case 1:
        {
            nCuritemType = E_ITEM_USE_EQUIP_PATCH;
            break;
        }
        case 2:
        {
            nCuritemType = E_ITEM_USE_EMBLEM_PATCH;
            break;
        }
        default:
            break;
    }
    
    

    for (int i = 0; i < arrItem.size(); i++) {
        const CItem* item = g_PacketDataMgr->GetItemInfoByIndex(arrItem[i]);
        if (!item) {
            continue;
        }
        if(item->GetConfigData().byType == nCuritemType) {
            m_vecShowList.push_back(arrItem[i]);
        }
    }
    if (m_vecShowList.size() > 0) {
        m_pControlButtonJingYing->getParent()->setVisible(false);
        sort(m_vecShowList.begin(), m_vecShowList.end(), cmpItem);
        int viewHeight = m_pTableView->getViewSize().height;
        
        m_pTableView->reloadData();
        
        int curHeight = m_pTableView->getContentSize().height;
        if (m_offPos.y > 0 || m_offPos.y < viewHeight - curHeight)
        {
            m_offPos.y = (viewHeight - curHeight);
        }
        m_pTableView->setVisible(true);
        m_pTableView->setContentOffset(m_offPos);
    }
    else
    {
        m_pTableView->setVisible(false);
        m_pControlButtonJingYing->getParent()->setVisible(true);
    }

}

bool CcbItemPatchLayer::cmpItem(uint32 index1,uint32 index2)
{
    const CItem* pItem1 = g_PacketDataMgr->GetItemInfoByIndex(index1);
    const CItem* pItem2 = g_PacketDataMgr->GetItemInfoByIndex(index2);
    if (!pItem1 || !pItem2)
    {
        return false;
    }
    if ((pItem1->GetCount() >= pItem1->GetConfigData().wParas[0] && pItem2->GetCount() >= pItem2->GetConfigData().wParas[0]) || (pItem1->GetCount() < pItem1->GetConfigData().wParas[0] && pItem2->GetCount() < pItem2->GetConfigData().wParas[0])) {
        if(pItem1->GetConfigData().byQuality > pItem2->GetConfigData().byQuality)
        {
            return true;
        }
        else if (pItem1->GetConfigData().byQuality == pItem2->GetConfigData().byQuality)
        {
            if (pItem1->GetCount() /(float) pItem1->GetConfigData().wParas[0] > pItem2->GetCount() / (float)pItem2->GetConfigData().wParas[0]) {
                return true;
            }
        }
    }
    else
    {
        if (pItem1->GetCount() >= pItem1->GetConfigData().wParas[0] ) {
            return true;
        }
    }
    return false;
}

void CcbItemPatchLayer::RefeashLayer()
{
    if (m_pCurButton) {
        this->changeShowInfoByTab(m_pCurButton->getTag());
    }
    checkTip();
}

void CcbItemPatchLayer::checkTip()
{
    vector<uint32> vecPetChipIndex = g_ItemData->GetVecPetChip();
    m_pSpriteTip_Pet->setVisible(false);
    m_pSpriteTip_Equip->setVisible(false);
    m_pSpriteTip_Emblem->setVisible(false);

    for (int i = 0; i < vecPetChipIndex.size(); i++) {
        uint32 itemId = vecPetChipIndex[i];
        if (!itemId) {
            continue;
        }
        const CItem* item = g_PacketDataMgr->GetItemInfoByIndex(itemId);
        if (item->GetCount() >= item->GetConfigData().wParas[0]) {
            
            switch (item->GetConfigData().byType) {
                case E_ITEM_USE_PET_PATCH:
                    m_pSpriteTip_Pet->setVisible(true);
                    break;
                case E_ITEM_USE_EQUIP_PATCH:
                    m_pSpriteTip_Equip->setVisible(true);
                    break;
                case E_ITEM_USE_EMBLEM_PATCH:
                    m_pSpriteTip_Emblem->setVisible(true);
                    break;
                default:
                    break;
            }
        }
    }
}