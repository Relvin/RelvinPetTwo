#include "CcbUnitMiddleLayer.h"
#include "CcbManager.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "ResourcePic.h"
#include "GuideData.h"
#include "UISupport.h"
#include "GameSession.h"
#include "EquipDataMgr.h"
#include "ItemDataMgr.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "ResourceDefine.h"
#include "Role.h"
#include "CCScrollViewWithBar.h"
#include "CCScrollButton.h"
#include "EmblemDataMgr.h"
#include "FlyTextLayer.h"
#include "SystemMessage.h"
#include "GuideBtnPos.h"
#include "GlobalData.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "GachaDataMgr.h"
#include "CcbJumpTipLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

UnitMiddleScene::~UnitMiddleScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* UnitMiddleScene::scene()
{
    CCScene* pScene = CCScene::create();
    UnitMiddleScene* pLayer = UnitMiddleScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool UnitMiddleScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbUnitMiddleLayer(this));
    return true;
}

void UnitMiddleScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void UnitMiddleScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
//    addChild(CcbManager::sharedManager()->LoadCcbUnitMiddleLayer(this));
    m_pLabelTTFName->setString(GET_STR(Str_layer_unit));
}

void UnitMiddleScene::onExit()
{
	CCLayer::onExit();
}

void UnitMiddleScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool UnitMiddleScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	return false;
}



#pragma mark CcbUnitMiddleLayer

CcbUnitMiddleLayer::~CcbUnitMiddleLayer()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(GET_PIC(Pic_unit_plist));
    CC_SAFE_RELEASE_NULL(m_pLayerHeaderBack);
    CC_SAFE_RELEASE_NULL(m_pLayerBottom);
    
    m_vecCell.clear();
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbUnitMiddleLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbUnitMiddleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbUnitMiddleLayer", CcbUnitMiddleLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/unit_middle.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbUnitMiddleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    
	return true;
}

const float Icon_Width = 75.0f;
const float Icon_Height = 85.0f;
#define Icon_Cnt 12
#define Cell_Child 4

// 三行，不使用kCCTableViewFillTopDown来进行反向，因为kCCTableViewFillTopDown会重载CellAtIndex方法，耗时}
#define Cell_Cnt 2

void CcbUnitMiddleLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_nTableCnt = (Icon_Cnt + (Cell_Child - 1)) / Cell_Child;
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    CGameSession::GetRole()->Attach(this);
}

void CcbUnitMiddleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

    CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile(GET_PIC(Pic_unit_plist), GET_PIC(Pic_unit_pvr_ccz));
    
    m_pTableList->reloadData();
    
    if ( CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        if (m_pNode1) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNode1, GuideBtnPos::E_UNIT_TEAM);
        }
        if (m_pNodeEquip) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNodeEquip, GuideBtnPos::E_UNIT_EQUIP);
        }
        if (m_pNodeBaoshi) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNodeBaoshi, GuideBtnPos::E_UNIT_BAOSHI);
        }
        if (m_pNodeFenjie) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNodeFenjie, GuideBtnPos::E_UNIT_FENJIE);
        }
    }
    
    
    dynamic_cast<CCTableViewWithBar*>(getChildByTag(110))->checkIsShow(numberOfCellsInTableView(m_pTableList), cellSizeForTable(m_pTableList));
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbUnitMiddleLayer::setTouchRestore)),
                                       NULL
                                       )
                    );
}

void CcbUnitMiddleLayer::setTouchRestore() {
//#ifdef DEBUG
//    GuideData::GetInstance()->setStepId(GuideData::E_SYS_GUIDE_3_MYSTERY);
//#endif
    
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_1_TEAM,
                                             
                                             GuideData::E_SYS_GUIDE_1_EQUIP,
                                             GuideData::E_SYS_GUIDE_5_HERO,
                                             GuideData::E_SYS_GUIDE_5_TOWER,
                                             GuideData::E_SYS_GUIDE_6_BADGE,
                                             GuideData::E_SYS_GUIDE_3_MYSTERY,
                                             NULL
                                             );
    
}

void CcbUnitMiddleLayer::onExit()
{
    CGameSession::GetRole()->Detach(this);
	CCLayer::onExit();
}

void CcbUnitMiddleLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbUnitMiddleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHeaderBack", CCLayer*, this->m_pLayerHeaderBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
	return false;
}

bool CcbUnitMiddleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


// Inhert CCNodeLoaderListener
void CcbUnitMiddleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_sizeList = CCSizeMake(getWidth(m_pLayerBottom) + 4.0f, getBottom(m_pLayerHeaderBack) - getTop(m_pLayerBottom) - 14.0f);
    m_pointList = ccp(getLeft(m_pLayerBottom), getTop(m_pLayerBottom));
    
    m_pTableList = CCTableView::create(this, m_sizeList);
    m_pTableList->setDirection(kCCScrollViewDirectionVertical);
    m_pTableList->setBounceable(true);
    
    CCTableViewWithBar* pTable = CCTableViewWithBar::create(m_pTableList);
    pTable->setAnchorPoint(CCPointZero);
    pTable->setPosition(m_pointList);
    pTable->setTag(110);
    
    
    this->addChild(pTable);
}

#pragma mark CCTableVIew Delegate
void CcbUnitMiddleLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    
}


CCTableViewCell* CcbUnitMiddleLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();

    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CCLayer* pRootLayer = CCLayer::create();
        pRootLayer->setContentSize(CCSizeMake(320.0f, Icon_Width));
        
        /*
         position:  x = 77.5 + 75 * i
                    y = 30.0
         */
        setNodeData(Cell_Cnt - idx, pRootLayer);
        
        pRootLayer->setTag(123);
        pRootLayer->ignoreAnchorPointForPosition(false);
        pRootLayer->setAnchorPoint(ccp(0.5, 0));
        pRootLayer->setPosition(ccp(winSize.width*0.5, 0.0f));
        pCell->addChild(pRootLayer);
    } else {
        CCLayer* pRootLayer = dynamic_cast<CCLayer*>( pCell->getChildByTag(123) );
        pRootLayer->removeAllChildren();
        
        setNodeData(Cell_Cnt -idx, pRootLayer);
    }
    return pCell;
}

void CcbUnitMiddleLayer::setNodeData(int nIdx, CCLayer* pLayer) {
    char nameBuf[64] = {0};
    int btnCnt = (nIdx + 1) * Cell_Child <= Icon_Cnt ? Cell_Child : (Icon_Cnt - nIdx * Cell_Child);
    for (int i = 0; i < btnCnt; i++) {
        CCScale9Sprite* pBtnNormal = CCScale9Sprite::create(GET_PIC(Pic_unit_btn_normal));
        CCSize btnSize = pBtnNormal->getContentSize();
        CCScrollButton* pScrollBtn = CCScrollButton::create(pBtnNormal);
        
        pScrollBtn->setPreferredSize(btnSize);
        pScrollBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbUnitMiddleLayer::onPressControlButtonIcon), CCControlEventTouchUpInside);
        pScrollBtn->setAnchorPoint(ccp(0.5, 0.5));
        pScrollBtn->setPosition(ccp(47.0 + Icon_Width * i, Icon_Height - 32.0f));
        
        int nTag = nIdx * Cell_Child + i;
        pScrollBtn->setTag(nTag);
        
        sprintf(nameBuf, "unit_%d.png", nIdx * Cell_Child + i);
        CCSprite* pIcon = CCSprite::createWithSpriteFrameName(nameBuf);
        pIcon->setAnchorPoint(ccp(0.5, 0.5));
        pIcon->setPosition(ccp(getCenterX(pScrollBtn), getCenterY(pScrollBtn)));
        if (checkBtnEnable(pScrollBtn->getTag())) {
            CCSprite* pLock = CCSprite::create(GET_PIC(Pic_little_lock));
            pLock->setPosition(pIcon->getPosition());
            pLayer->addChild(pLock, 10);
            
            CCSprite* pDark = CCSprite::create(GET_PIC(Pic_unit_dark));
            pDark->setPosition(pIcon->getPosition());
            pLayer->addChild(pDark, 11);
        }
        uint32 dwStrId = Str_unit_0 + nIdx*Cell_Child + i;
        
        CCLabelTTF* lblName = CCLabelTTF::create(GET_STR(dwStrId), FONT_FZCQJW, 13);
        lblName->setAnchorPoint(ccp(0.5, 0));
        lblName->setPosition(ccp(getCenterX(pScrollBtn), getBottom(pScrollBtn)));
        
        CRole* pRole = CGameSession::GetRole();
        if (pRole->GetbyNotiNewPet() && nTag == kPetBag) { // 新宠物提示}
            addTipsUpRight(pLayer, ccp(getRight(pScrollBtn), getTop(pScrollBtn)));
        }
        if (pRole->GetbyNotiNewEquip() && nTag == kEquipBag) { // 新装备提示}
            addTipsUpRight(pLayer, ccp(getRight(pScrollBtn), getTop(pScrollBtn)));
        }
        if (pRole->GetbyNotiNewEmblem() && nTag == kEmblemBag) { // 新徽章提示}
            addTipsUpRight(pLayer, ccp(getRight(pScrollBtn), getTop(pScrollBtn)));
        }
        if (pRole->GetbyNotiChips() && nTag == kPetFragment) { //碎片合成提示
            addTipsUpRight(pLayer, ccp(getRight(pScrollBtn), getTop(pScrollBtn)));
        }
        if (pRole->GetbyNotiBox() && nTag == kPropsBag) { //宝箱开启提示
            addTipsUpRight(pLayer, ccp(getRight(pScrollBtn), getTop(pScrollBtn)));
        }
        
        if ( pRole->GetwRoleLv() < GUIDE_LV ) {
            if ( nTag == kPetTeam ) {
                m_pNode1 = pScrollBtn;
            } else if ( nTag == kEquipBag ) {
                m_pNodeEquip = pScrollBtn;
            } else if ( nTag == kGemInlay ) {
                m_pNodeBaoshi = pScrollBtn;
            } else if ( nTag == kPetFuseTag ) {
                m_pNodeFenjie = pScrollBtn;
            }
        }
        
        pLayer->addChild(pScrollBtn);
        pLayer->addChild(pIcon);
        pLayer->addChild(lblName, 12);
    }
}

void CcbUnitMiddleLayer::addTipsUpRight(cocos2d::CCLayer *pLayer, cocos2d::CCPoint pos) {
    CCSprite* pTips = CCSprite::create(GET_PIC(Pic_red_tip));
    pTips->setAnchorPoint(ccp(1.0f, 1.0f));
    pTips->setPosition(pos);
    pLayer->addChild(pTips, 20);
}

void CcbUnitMiddleLayer::onPressControlButtonIcon(cocos2d::CCObject *pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CCScrollButton* pButton = dynamic_cast<CCScrollButton*>(pSender);
    /*
     enum kUnitTag {
     kPetBag = 0,    // 精灵一览}
     kPetTeam,       // 编辑队伍}
     kPetEnhance,    // 精灵强化}
     kPetEvolve,     // 精灵进阶}
     kGemInlay,      // 宝石镶嵌}
     kPropsBag,      // 道具一览}
     kEquipBag,      // 装备一览}
     kEmblemBag,     // 徽章一览}
     kPetFragment,   // 宠物碎片}
     kPetFuseTag,    // 宠物融合}
     kPropsCompose,  // 道具合成}
     kSellPet,       // 精灵出售}
     };
     */
    if (m_bEnableBtn) {
        m_bEnableBtn = false;
    } else {
        return;
    }
    uint16 syslockId = 0;
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    switch (pButton->getTag()) {
        case kPetBag: {
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::E_BAG_ENTER_TYPE_ALL);
            g_EquipData->setIsEquipShow(false);
            BackCtrl::InsertNextScene(kPetBagScene);
            break;
        }
        case kPetTeam:
            BackCtrl::InsertNextScene(kTeamScene);
            break;
        case kPetEnhance:
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY);
            BackCtrl::InsertNextScene(kPetBagScene);
            break;
        case kPetEvolve:
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::E_BAG_ENTER_TYPE_EVOLVE);
            BackCtrl::InsertNextScene(kPetBagScene);
            break;
        case kGemInlay:
        {
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_INLAY);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                m_bEnableBtn = true;
                PetLoadingLayer::sharedLayer()->End();
                return;
            }
        }
            g_EquipData->SetEquipListShowMode(E_SHOW_LIST_INPLAY);
            g_EquipData->SetChosenEquipKeyID(0);
            BackCtrl::InsertNextScene(kEquipInlayScene);
            break;
        case kPropsBag:
            g_ItemData->SetItemShowMode(MODE_SHOW_NORMAL_ITEM);
            CShowJumpTip::Get()->setNeedItemId(0);
            CShowJumpTip::Get()->setJumpType(E_SHOW_JUMP_NULL);
            BackCtrl::InsertNextScene(kItemListScene);
            break;
        case kEquipBag:
        {
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_UNIT_EQUIP);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                m_bEnableBtn = true;
                PetLoadingLayer::sharedLayer()->End();
                return;
            }
        }
            g_EquipData->SetDressEquipPart(0);
            g_EquipData->setIsEquipShow(false);
            BackCtrl::InsertNextScene(kEquipIntegrationScene);
            break;
        case kEmblemBag:
        {
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                m_bEnableBtn = true;
                PetLoadingLayer::sharedLayer()->End();
                return;
            }
        }
            g_EmblemData->setEmbInType(E_EMB_IN_TYPE_ALL);
            BackCtrl::InsertNextScene(kEmblemListSenec);
            break;
        case kPetFragment:
            g_ItemData->SetItemShowMode(MODE_SHOW_PET_CHIP);
            BackCtrl::InsertNextScene(kItemPatchScene);

            break;
        case kPetFuseTag:
        {
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_FUSE);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                m_bEnableBtn = true;
                PetLoadingLayer::sharedLayer()->End();
                return;
            }
        }
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::E_BAG_ENTER_TYPE_FUSE);
            BackCtrl::InsertNextScene(kPetFuse);
            break;
//        case kPropsCompose:
//        {
//            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_COMPOUND);
//            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
//            if (cfg) {
//                FlyTextLayer::showTips(cfg->strDescShow.c_str());
//                m_bEnableBtn = true;
//                PetLoadingLayer::sharedLayer()->End();
//                return;
//            }
//        }
//            g_EquipData->SetCompoundTabType(SHOW_TAB_ATTRI_HP);
//            BackCtrl::InsertNextScene(kEquipCompoundListScene);
//            break;
        case kTujian:
            g_GachaData->setGachaFlag(false);
            BackCtrl::InsertNextScene(kPetTujian);
            break;
        case kSellPet:
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::E_BAG_ENTER_TYPE_SALE);
            CPetCtrl::Get()->ClearSelectedPet();
            BackCtrl::InsertNextScene(kPetBagSaleScene);
            break;
        default:
            break;
    }
}

unsigned int CcbUnitMiddleLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return m_nTableCnt;
}

CCSize CcbUnitMiddleLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerBottom), Icon_Height);
}

bool CcbUnitMiddleLayer::checkBtnEnable(int tag){
    /*
     enum kUnitTag {
     kPetBag = 0,    // 精灵一览}
     kPetTeam,       // 编辑队伍}
     kPetEnhance,    // 精灵强化}
     kPetEvolve,     // 精灵进阶}
     kGemInlay,      // 宝石镶嵌}
     kPropsBag,      // 道具一览}
     kEquipBag,      // 装备一览}
     kEmblemBag,     // 徽章一览}
     kPetFragment,   // 宠物碎片}
     kPetFuseTag,    // 宠物融合}
     kPropsCompose,  // 道具合成}
     kSellPet,       // 精灵出售}
     };
     */
    uint16 syslockId = 0;
    switch (tag) {
        case kGemInlay:
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_INLAY);
            break;
        case kEquipBag:
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_UNIT_EQUIP);
            break;
        case kEmblemBag:
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
            break;
        case kPetFuseTag:
            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_FUSE);
            break;
//        case kPropsCompose:
//            syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_COMPOUND);
//            break;
        default:
            break;
    }
    
    return syslockId;
}


#pragma mark Observer Role Delegate
void CcbUnitMiddleLayer::byNotiNewPetChanged(uint8 byNotiNewPet) {
    if (m_pTableList) {
        m_pTableList->reloadData();
    }
}

void CcbUnitMiddleLayer::byNotiNewEquipChanged(uint8 byNotiNewEquip) {
    if (m_pTableList) {
        m_pTableList->reloadData();
    }
}

void CcbUnitMiddleLayer::byNotiNewEmblemChanged(uint8 byNotiNewEmblem) {
    if (m_pTableList) {
        m_pTableList->reloadData();
    }
}


