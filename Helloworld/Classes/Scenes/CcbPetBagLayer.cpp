#include "CcbPetBagLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "MaskLayer.h"
#include "PropertyList.h"
#include "Pet.h"
#include "CcbPetShowLayer.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "CCScrollButton.h"
#include "BackCtrl.h"
#include "UISupport.h"
#include "CCScrollViewWithBar.h"
#include "GameSession.h"
#include "Role.h"
#include "ResourceStringClient.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "GlobalData.h"
#include "EmblemDataMgr.h"
#include "PetLoadingLayer.h"
#include "GuideData.h"
#include "GuideBtnPos.h"
#include "BuyDataMgr.h"
#include "CcbSystemLayer2.h"

USING_NS_CC;
USING_NS_CC_EXT;

PetBagScene::~PetBagScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* PetBagScene::scene()
{
    CCScene* pScene = CCScene::create();
    PetBagScene* pLayer = PetBagScene::create();
    pLayer->setTag(1);
    pScene->addChild(pLayer);
    return pScene;
}

bool PetBagScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CcbPetBagLayer *layer = (CcbPetBagLayer *)CcbManager::sharedManager()->LoadPetBagLayer(this);
    layer->setTag(1);
    addChild(layer);
    return true;
}

void PetBagScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
    m_pLabelTTFName->setString(GET_STR(Str_layer_petBag));
}

void PetBagScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void PetBagScene::onExit()
{
	CCLayer::onExit();
}
void PetBagScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool PetBagScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool PetBagScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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



CcbPetBagLayer::~CcbPetBagLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerBg);
    CC_SAFE_RELEASE_NULL(m_pControlButtonSort);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurCount);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxCount);
    CC_SAFE_RELEASE_NULL(m_pLayerPetBg);
    CC_SAFE_RELEASE_NULL(m_pSpriteSort);
    CC_SAFE_RELEASE_NULL(m_pLayerBack);
    CC_SAFE_RELEASE_NULL(m_pControlButtonExpandBag);
    m_sortLayer = NULL;
    m_curScene = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetBagLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetBagLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader("CcbPetBagLayer", CcbPetBagLayerLoader::loader());
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/bag_pet.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

bool CcbPetBagLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_sortLayer != NULL && m_sortLayer->isVisible()) {
        return true;
    }
    return false;
}
void CcbPetBagLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

CcbPetBagLayer* CcbPetBagLayer::m_curScene = NULL;
bool CcbPetBagLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    this->setTouchEnabled(true);
    m_curScene = this;
    
	return true;
}

void CcbPetBagLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::GetRole()->Attach(this);
    winSzie = CCDirector::sharedDirector()->getWinSize();
//    m_pLayerPetBg->setPositionX(m_pLayerPetBg->getPositionX() + winSzie.width);
    m_pControlButtonSort->setPositionX(m_pControlButtonSort->getPositionX() + winSzie.width);
}
void CcbPetBagLayer::onEnterTransitionDidFinish()
{
    m_scrollOff = CPetCtrl::Get()->getPetBagOffSet();
    loadPet();
//    m_table->reloadData();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        if (m_pNode1) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNode1, GuideBtnPos::E_PET_BAG_ONE);
        }
    }
    
//    CGameSession::Attach(this);
    CcbPetShowLayer::m_bIsChangePetEnable = true;

    CCLayer::onEnterTransitionDidFinish();
//    m_pLayerPetBg->runAction( CCSequence::create(CCMoveBy::create(TRANS_DUR * 0.5, ccp(-winSzie.width, 0)), CCCallFunc::create(this, callfunc_selector(CcbPetBagLayer::addGuideLayer)), NULL) );
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbPetBagLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
    
    m_pControlButtonSort->runAction( CCMoveBy::create(TRANS_DUR * 0.5, ccp(-winSzie.width, 0)));
    
    CRole* pRole = CGameSession::GetRole();
    pRole->SetbyNotiNewPet(false);
//    pRole->SetbyNotiUnit(pRole->GetbyNotiNewEquip() | pRole->GetbyNotiNewEmblem());
}

void CcbPetBagLayer::addGuideLayer()
{
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_GUIDE_TRIGGER_3_TEAM,
                                             GuideData::E_SYS_GUIDE_3_BADGE,
                                             GuideData::E_GUIDE_TRIGGER_1_MAIN_TEAM,
                                             NULL
                                             );
}

void CcbPetBagLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::GetRole()->Detach(this);
    uint16 wTrigger = CGameSession::GetRole()->GetwGuideTrigger();
    if (
        wTrigger == GuideData::E_GUIDE_TRIGGER_4_TEAM ||
        wTrigger == GuideData::E_GUIDE_TRIGGER_THI_TALK_1
        ) {
        // 上阵后的通信
        GuideData::GetInstance()->connectToServer();
    }
    
    m_scrollOff = m_table->getContentOffset();
    CPetCtrl::Get()->setPetBagOffSet(m_scrollOff);
}
void CcbPetBagLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
//    m_pLayerPetBg->runAction(CCMoveBy::create(TRANS_DUR * 0.5, ccp(CCDirector::sharedDirector()->getWinSize().width, 0)));
    m_pControlButtonSort->runAction(CCMoveBy::create(TRANS_DUR * 0.5, ccp(CCDirector::sharedDirector()->getWinSize().width, 0)));
}

SEL_CallFuncN CcbPetBagLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetBagLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

bool CcbPetBagLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBg", CCLayer*, this->m_pLayerPetBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSort", CCControlButton*, this->m_pControlButtonSort);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurCount", CCLabelTTF*, this->m_pLabelTTFCurCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxCount", CCLabelTTF*, this->m_pLabelTTFMaxCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CCLayer*, this->m_pLayerBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSort", CCSprite*, this->m_pSpriteSort);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExpandBag", CCControlButton*, this->m_pControlButtonExpandBag);
	return false;
}

bool CcbPetBagLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


SEL_CCControlHandler CcbPetBagLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSort", CcbPetBagLayer::onPressControlButtonSort);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExpandBag", CcbPetBagLayer::onPressControlButtonExpandBag);
	return NULL;
}

void CcbPetBagLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_clipRect.origin = getWorldPos(m_pLayerPetBg);
    m_pLayerPetBg->setContentSize(CCSizeMake(getWidth(m_pLayerPetBg), getBottom(m_pLayerBack) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerPetBg->getContentSize();
    
    BuyDataMgr::Get()->setChangeToBuyScene(false);
    CGameSession::SendReqShopCnt();
    
    m_pControlButtonExpandBag->setTouchAreaScale(2.0);
    m_pControlButtonExpandBag->setTouchPriority(2*kCCMenuHandlerPriority);
    m_table = CCTableView::create(this, m_pLayerPetBg->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    CCTableViewWithBar *layer = CCTableViewWithBar::create(m_table);
    layer->setAnchorPoint(ccp(0, 0));
    layer->setPosition(ccp(0, 0));
    layer->setTag(111);
    m_pLayerPetBg->addChild(layer);
    bFlag = true;
    m_scrollOff = CCPointZero;

    m_sortLayer = NULL;
}



void CcbPetBagLayer::onPressControlButtonSort(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_scrollOff = m_table->getContentOffset();
    if (!m_sortLayer) {
        initSortLayer();
    }
    else
    {
        m_sortLayer->setVisible(true);
    }
}

void CcbPetBagLayer::onPressControlButtonExpandBag(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BuyDataMgr::STC_BUY sPet;
    sPet = BuyDataMgr::Get()->buyInfoByType(E_ROLE_OPERATE_TYPE_PET_BAG);
    BuyDataMgr::Get()->setCurBuyType(E_ROLE_OPERATE_TYPE_PET_BAG);
    CSystemMessage2::Get()->Show(E_TYPE_PET_BAG, sPet.dwCostDollar, sPet.dwEarnCnt);
}

void CcbPetBagLayer::initSortLayer()
{
    m_sortLayer = (CcbSortLayer*)CcbManager::sharedManager()->LoadCcbSortLayer(this);
//    m_sortLayer->setOwner(this);
    m_sortLayer->setTouchPriority(kCCMenuHandlerPriority - 5);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_sortLayer->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    m_sortLayer->setAnchorPoint(ccp(0.5, 0.5));
    m_sortLayer->ignoreAnchorPointForPosition(false);
    addChild(m_sortLayer, 20);
}

CCTableViewCell* CcbPetBagLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell  = table->dequeueCell();
    int cnt = m_arrPetObjId.size() - idx * cellCnt;
    if (cnt > cellCnt) {
        cnt  = cellCnt;
    }
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCNode *node = CCNode::create();
        node->setContentSize(CCSizeMake(table->getContentSize().width, 60));
        node->setTag(1);
        cell->addChild(node);
    }
    CCNode *node = dynamic_cast<CCNode*>(cell->getChildByTag(1));
    
    for (int i = 0; i < cnt; i++) {
        
        if ( idx == 0 && i == 0 ) {
            if (teamFlag || emblemFlag) {
                CCNode* remove= node->getChildByTag(i+1);
                if (remove) {
                    remove->removeFromParent();
                    remove = NULL;
                }
                CCScale9Sprite* btnNormal = CCScale9Sprite::create("ccbresources/12monthdate/universal/button_putdown_1.png");
                CCSize spriteSize = btnNormal->getContentSize();
                CCScale9Sprite* btnSelect = CCScale9Sprite::create("ccbresources/12monthdate/universal/button_putdown_2.png");
                
                CCScrollButton *menu = CCScrollButton::create(btnNormal);
                menu->setBackgroundSpriteForState(btnSelect, CCControlStateHighlighted);
                menu->setZoomOnTouchDown(false);
                menu->setPreferredSize(spriteSize);
                if (teamFlag) {
                    menu->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbPetBagLayer::onRemoveMember), CCControlEventTouchUpInside);
                }
                else if(emblemFlag){
                    menu->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbPetBagLayer::onRemoveEmblem), CCControlEventTouchUpInside);
                }
                menu->setAnchorPoint(CCPointZero);
                menu->setPosition(ccp(8 , 3));
                menu->setClipRect(m_clipRect);
                menu->setTouchPriority(kCCMenuHandlerPriority - 2);
                menu->setTag(1);
                node->addChild(menu);
                continue;
            }
        }
        
        if(i == 0)
        {
            CCScrollButton *menu = dynamic_cast<CCScrollButton*>(node->getChildByTag(i+1));
            if (menu) {
                menu->removeFromParent();
                menu = NULL;
            }
        }
        CcbPetIconCtrl *petIcon = dynamic_cast<CcbPetIconCtrl*>(node->getChildByTag(i+1));
        if (!petIcon) {
            petIcon =  dynamic_cast<CcbPetIconCtrl*>(CcbManager::sharedManager()->LoadCcbPetIconCtrl(this));
            petIcon->setTag(i+1);
            node->addChild(petIcon);
        }
        else
        {
            m_mapPetIcon[petIcon->getPetObjId()] = NULL;
        }
        CCLog("~~~~~~pet ObjId %d in petBag ~~~~", m_arrPetObjId[idx * cellCnt + i]);
        CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_arrPetObjId[idx * cellCnt + i]);
        if (!pet) {
            petIcon->removeFromParent();
            CCLog("~~~~~~pet ObjId %d in petBag not found~~~~", m_arrPetObjId[idx * cellCnt + i]);
            continue;
        }
        petIcon->setVisible(true);
        petIcon->setPet(pet);
        petIcon->loadData();
        petIcon->setPosition(ccp(8 + i*60, 3));
        petIcon->setAnchorPoint(ccp(0, 0));
        petIcon->setClipRect(m_clipRect);
        petIcon->setTag(i+1);
        petIcon->setEnable(CPetCtrl::Get()->IsPetIconEnable(pet->GetObjId()));
        m_mapPetIcon[pet->GetObjId()] = petIcon;
    }
    for (int i = cnt; i < cellCnt; i++) {
        CcbPetIconCtrl *petIcon = dynamic_cast<CcbPetIconCtrl*>(node->getChildByTag(i+1));
        if (petIcon) {
            m_mapPetIcon[petIcon->getPetObjId()] = NULL;
            petIcon->setVisible(false);
        }
    }
    
    if (idx == 0) {
        m_pNode1 = node->getChildByTag(1);
    }
    
    return cell;

}
unsigned int CcbPetBagLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    uint32  cnt = m_arrPetObjId.size();

    if (cnt % cellCnt > 0) {
        return cnt / cellCnt + 1;
    }
    return cnt / cellCnt;
}
CCSize CcbPetBagLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerPetBg), 64);
}

void CcbPetBagLayer::loadPet()
{
    RefeashLayer();
}

void CcbPetBagLayer::RefeashLayer()
{
    sortPetBag(CPetCtrl::Get()->GetBagPets());
}

void CcbPetBagLayer::sortPetBag(std::vector<uint32> arrPetObjId)
{
    m_mapPetIcon.clear();
    
    uint32 petCount = CPetCtrl::Get()->GetTotalPetNum();
    uint32 size = CGameSession::GetRole()->GetdwPetBagCnt();//CPetCtrl::Get()->GetBagTotalSize();
    m_pLabelTTFCurCount->setString(PARSE_STRING1("##0##",petCount));
    m_pLabelTTFMaxCount->setString(PARSE_STRING1("##0##", size));
    
    teamFlag = false;
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_NORMAL) {
        uint32 wObjId = CTeamCtrl::GetCurTeam()->getarrPetObId()[CTeamCtrl::GetSelectedMemberSite()];
        if (wObjId) {
            teamFlag = true;
        }
    }
    
    emblemFlag = false;
//    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_EMBLEM) {
//        CEmblem* emb = g_EmblemData->getEmblemByObjId(g_EmblemData->getWearEmbObjId());
//        if (emb && emb->getdwPetObjId()) {
//            emblemFlag = true;
//        }
//    }
    
    m_arrPetObjId = arrPetObjId;
    if (teamFlag || emblemFlag) {
        m_arrPetObjId.insert(m_arrPetObjId.begin(), 0);
    }
    m_table->reloadData();
    dynamic_cast<CCTableViewWithBar*>(m_pLayerPetBg->getChildByTag(111))->checkIsShow(numberOfCellsInTableView(m_table), cellSizeForTable(m_table));
    
    float contentH = numberOfCellsInTableView(m_table)*cellSizeForTable(m_table).height;
    
    if (m_scrollOff.y > 0 || m_scrollOff.y < m_table->getViewSize().height - contentH) {
        m_scrollOff = ccp(0, m_table->getViewSize().height - contentH);
    }
    
    m_table->setContentOffset(m_scrollOff);

}

void CcbPetBagLayer::ReflashPetBagNum()
{
    std::vector<uint32> arrSelectedPet = CPetCtrl::Get()->GetSelectedPet();
    if (arrSelectedPet.size() == 0) {
        return;
    }
    
    bool unEnable = CPetCtrl::Get()->IsSeletedFull();
    
    for (int i = 0; i < arrSelectedPet.size(); i++) {
        uint16 objId = arrSelectedPet[i];
        CcbPetIconCtrl *petIcon = m_mapPetIcon[objId];
        if (!petIcon) {
            continue;
        }
        petIcon->setNum(i+1);
    }
    
    std::map<uint16, CcbPetIconCtrl*>::iterator it = m_mapPetIcon.begin();
    for (; it != m_mapPetIcon.end(); it++) {
        CcbPetIconCtrl *petIcon = it->second;
        if (!petIcon) {
            continue;
        }
        //设置过编号的不置灰}
        petIcon->setEnable(!unEnable);
    }
}

void CcbPetBagLayer::onRemoveMember(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CTeamCtrl::DelTeamMamber(CTeamCtrl::GetSelectedMemberSite());
    CTeamCtrl::SaveTeamUpdate();
//    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_TEAM);
//    BackCtrl::BacktoUpperScene();
}

void CcbPetBagLayer::onRemoveEmblem(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
//    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
//    CGameSession::SendEmblemTakeOff(g_EmblemData->getWearEmbObjId());
//    PetLoadingLayer::sharedLayer()->WaitForPacket();
}

void CcbPetBagLayer::dwPetBagCntChanged(uint32 cnt)
{
    m_pLabelTTFMaxCount->setString(CCString::createWithFormat("%d", cnt)->getCString());
}

