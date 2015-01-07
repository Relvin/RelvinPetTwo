#include "CcbPetBagSaleLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "GameSession.h"
#include "CCScrollViewWithBar.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "PetLoadingLayer.h"
#include "Role.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark PetBagSale  Scene
PetBagSaleScene::~PetBagSaleScene()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    
}

CCScene *PetBagSaleScene::scene()
{
    CCScene *scene = CCScene::create();
    
    PetBagSaleScene *layer = PetBagSaleScene::create();
    layer->setTag(1);
    scene->addChild(layer);
    
    return scene;
}

bool PetBagSaleScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CCNode * node = CcbManager::sharedManager()->LoadCcbPetBagSaleLayer(this);
    node->setTag(1);
    addChild(node);
	return true;
}

void PetBagSaleScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_pLabelTTFName->setString(GET_STR(Str_layer_petBag));
}

void PetBagSaleScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void PetBagSaleScene::onExit()
{
	CCLayer::onExit();
}

void PetBagSaleScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool PetBagSaleScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	return false;
}

bool PetBagSaleScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


#pragma mark PetBagSale  Layer
CcbPetBagSaleLayer* CcbPetBagSaleLayer::m_shareLayer = NULL;
CcbPetBagSaleLayer::~CcbPetBagSaleLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerPetBg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSort);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMoney);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExp);
	CC_SAFE_RELEASE_NULL(m_pLayerBack);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurCount);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMaxCount);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMoneyText);
    m_shareLayer = NULL;
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbPetBagSaleLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbPetBagSaleLayer( CCObject* owner ) {
 CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
 pLoaderLib->registerCCNodeLoader( "CcbPetBagSaleLayer", CcbPetBagSaleLayerLoader::loader() );
 pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );
 pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
 pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
 
 
 CCBReader* pCCBReader = new CCBReader(pLoaderLib);
 CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/bag_pet_mix.ccbi", owner);
 pCCBReader->release();
 
 return pNode;
 }
 */


bool CcbPetBagSaleLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}
void CcbPetBagSaleLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}


bool CcbPetBagSaleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_sortLayer = NULL;
    this->setTouchEnabled(true);
    m_shareLayer = this;
    
    bFlag = true;
    
	return true;
}


void CcbPetBagSaleLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}

    m_pLayerPetBg->setPositionX(m_pLayerPetBg->getPositionX() + CCDirector::sharedDirector()->getWinSize().width);
    m_pControlButtonSort->setPositionX(m_pControlButtonSort->getPositionX() + CCDirector::sharedDirector()->getWinSize().width);
    m_scrollOff = CPetCtrl::Get()->getPetBagOffSet();
    
}

void CcbPetBagSaleLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
//    m_table->reloadData();
    loadPet();
    CCSize winSzie = CCDirector::sharedDirector()->getWinSize();
    m_pLayerPetBg->runAction(CCMoveBy::create(TRANS_DUR * 0.5, ccp(-winSzie.width, 0)));
    m_pControlButtonSort->runAction( CCMoveBy::create(TRANS_DUR * 0.5, ccp(-winSzie.width, 0)));
}

void CcbPetBagSaleLayer::onExit()
{
	CCLayer::onExit();
    m_scrollOff = m_table->getContentOffset();
    CPetCtrl::Get()->setPetBagOffSet(m_scrollOff);
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_SALE) {
        CPetCtrl::Get()->ClearSelectedPet();
    }
}

void CcbPetBagSaleLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    
    m_pLayerPetBg->runAction(CCMoveBy::create(TRANS_DUR * 0.5, ccp(CCDirector::sharedDirector()->getWinSize().width, 0)));
    m_pControlButtonSort->runAction(CCMoveBy::create(TRANS_DUR * 0.5, ccp(CCDirector::sharedDirector()->getWinSize().width, 0)));
}

// Inhert MemberVariableAssigner
bool CcbPetBagSaleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetBg", CCLayer*, this->m_pLayerPetBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSort", CCControlButton*, this->m_pControlButtonSort);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoney", CCLabelTTF*, this->m_pLabelTTFMoney);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExp", CCLabelTTF*, this->m_pLabelTTFExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CCLayer*, this->m_pLayerBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurCount", CCLabelTTF*, this->m_pLabelTTFCurCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMaxCount", CCLabelTTF*, this->m_pLabelTTFMaxCount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMoneyText", CCLabelTTF*, this->m_pLabelTTFMoneyText);
	return false;
}

bool CcbPetBagSaleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetBagSaleLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbPetBagSaleLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler CcbPetBagSaleLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSort", CcbPetBagSaleLayer::onPressControlButtonSort);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUnSelete", CcbPetBagSaleLayer::onPressControlButtonUnSelete);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbPetBagSaleLayer::onPressControlButtonOk);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetBagSaleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    //    m_pControlButtonSort->setTouchPriority(kCCMenuHandlerPriority - 10);
    m_clipRect.origin = getWorldPos(m_pLayerPetBg);
    m_pLayerPetBg->setContentSize(CCSizeMake(getWidth(m_pLayerPetBg), getBottom(m_pLayerBack) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerPetBg->getContentSize();
    
    m_table = CCTableView::create(this, m_pLayerPetBg->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    CCTableViewWithBar *layerWithBar = CCTableViewWithBar::create(m_table);
    layerWithBar->setPosition(CCPointZero);
    layerWithBar->setAnchorPoint(CCPointZero);
    layerWithBar->setTag(111);
    m_pLayerPetBg->addChild(layerWithBar);
    
    
    m_scrollOff = CCPointZero;
    
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_SALE) {
        m_pLabelTTFMoneyText->setString("出售获得:");
        m_pLabelTTFExp->getParent()->setVisible(false);
    }
    else if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB){
        m_pLabelTTFMoneyText->setString("强化花费:");
        m_pLabelTTFExp->getParent()->setVisible(true);
    }
        
    
}



void CcbPetBagSaleLayer::onPressControlButtonSort(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    //    if (!m_sortLayer) {
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_scrollOff = m_table->getContentOffset();
    if (!m_sortLayer) {
        initSortLayer();
    }
    else
    {
        m_sortLayer->setVisible(true);
    }
    
    //    }
    //    else
    //    {
    //        m_sortLayer->setVisible(true);
    //    }
}

void CcbPetBagSaleLayer::onPressControlButtonUnSelete(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    clearSelected();
}

void CcbPetBagSaleLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_scrollOff = m_table->getContentOffset();
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB
        || CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_FUSE) {
        BackCtrl::BacktoUpperScene();
        return;
    }
    else
    {
        checkSale();
        //        bFlag = true;
    }
}

CCTableViewCell* CcbPetBagSaleLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *cell  = table->dequeueCell();
    int cnt = m_arrPetObjId.size() - idx * 5;
    if (cnt > 5) {
        cnt  = 5;
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
        
        CPet *pet = CPetCtrl::Get()->GetPetByObjId(m_arrPetObjId[idx * 5 + i]);
        if (!pet) {
            petIcon->removeFromParent();
            CCLog("~~~~~~pet ObjId %d in petBag not found~~~~", m_arrPetObjId[idx * 5 + i]);
            continue;
        }
        petIcon->setVisible(true);
        petIcon->setPet(pet);
        petIcon->setPosition(ccp(8 + i*60, 0));
        petIcon->setAnchorPoint(ccp(0, 0));
        petIcon->setClipRect(m_clipRect);
        petIcon->setTag(i+1);
        petIcon->setEnable(CPetCtrl::Get()->IsPetIconEnable(pet->GetObjId()));
        m_mapPetIcon[pet->GetObjId()] = petIcon;
    }
    for (int i = cnt; i < 5; i++) {
        CcbPetIconCtrl *petIcon = dynamic_cast<CcbPetIconCtrl*>(node->getChildByTag(i+1));
        if (petIcon) {
            m_mapPetIcon[petIcon->getPetObjId()] = NULL;
            petIcon->setVisible(false);
        }
    }
    
    return cell;
    
}
unsigned int CcbPetBagSaleLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    if (m_arrPetObjId.size() % 5 > 0) {
        return m_arrPetObjId.size() / 5 + 1;
    }
    return m_arrPetObjId.size() / 5;
}
CCSize CcbPetBagSaleLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerPetBg), 64);
}

void CcbPetBagSaleLayer::initSortLayer()
{
    m_sortLayer = (CcbSortLayer*)CcbManager::sharedManager()->LoadCcbSortLayer(this);
    m_sortLayer->setOwner(this);
    m_sortLayer->setTouchPriority(kCCMenuHandlerPriority - 5);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_sortLayer->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    m_sortLayer->setAnchorPoint(ccp(0.5, 0.5));
    m_sortLayer->ignoreAnchorPointForPosition(false);
    addChild(m_sortLayer, 20);
}

void CcbPetBagSaleLayer::loadPet()
{
    RefeashLayer();
    //    m_scrollOff = m_table->getContentOffset();
}

void CcbPetBagSaleLayer::RefeashLayer()
{
    PetLoadingLayer::sharedLayer()->End();
    sortPetBag(CPetCtrl::Get()->GetBagPets());
}

void CcbPetBagSaleLayer::sortPetBag(std::vector<uint32> arrPetObjId)
{
    //    if (m_sortLayer) {
    //        m_sortLayer->setVisible(false);
    //    }
    //    listNormal.clear();
    //    listProtected.clear();
    
    m_pLabelTTFMoney->setString("0");
    m_pLabelTTFExp->setString("0");
    
    //    CCNode *node = pScrollViewBag->getContainer();
    m_mapPetIcon.clear();
    //    node->removeAllChildrenWithCleanup(true);
    
    uint32 petCount = CPetCtrl::Get()->GetTotalPetNum();
    uint32 size = CGameSession::GetRole()->GetdwPetBagCnt();//CPetCtrl::Get()->GetBagTotalSize();
    
    CCString *str = CCString::createWithFormat("%d",petCount);
    m_pLabelTTFCurCount->setString(str->getCString());
    str->initWithFormat("%d", size);
    m_pLabelTTFMaxCount->setString(str->getCString());
    
    m_arrPetObjId = arrPetObjId;
    m_table->reloadData();
    dynamic_cast<CCTableViewWithBar*>(m_pLayerPetBg->getChildByTag(111))->checkIsShow(numberOfCellsInTableView(m_table), cellSizeForTable(m_table));
    
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB
        || CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_SALE
        || CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_FUSE) {
        ReflashPetBagNum();
    }
    
    float contentH = numberOfCellsInTableView(m_table)*cellSizeForTable(m_table).height;

    if (m_scrollOff.y > 0 || m_scrollOff.y < m_table->getViewSize().height - contentH) {
        m_scrollOff = ccp(0, m_table->getViewSize().height - contentH);
    }
    //    }
    m_table->setContentOffset(m_scrollOff);
    
}

void CcbPetBagSaleLayer::ReflashPetBagNum()
{
    m_pLabelTTFMoney->setString("0");
    m_pLabelTTFExp->setString("0");
    std::vector<uint32> arrSelectedPet = CPetCtrl::Get()->GetSelectedPet();
    //    if (arrSelectedPet.size() == 0) {
    //        return;
    //    }
    
    bool unEnable = CPetCtrl::Get()->IsSeletedFull();
    
    int size = arrSelectedPet.size();
//    int money = 0;
    
    std::map<uint32, uint32> mapSelectedPet;
    mapSelectedPet.clear();
    for (int i = 0; i < size; i++) {
        uint32 objId = arrSelectedPet[i];
        
        mapSelectedPet[objId] = i + 1;
    }
    if (!m_table || !m_table->getContainer() || !m_table->getContainer()->getChildren()) {
        return;
    }
    
//    CPet* pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetIntensifyPet());
    uint32 costCoin = 0;
    uint32 getExp = 0;
    for (int i = 0; i < m_table->getContainer()->getChildren()->count(); i++) {
        CCTableViewCell *cell = dynamic_cast<CCTableViewCell*>(m_table->getContainer()->getChildren()->objectAtIndex(i));
        if (!cell) {
            continue;
        }
        CCNode *node = cell->getChildByTag(1);
        if (!node) {
            continue;
        }
        for (int tag = 1; tag <= 5; tag++) {
            CcbPetIconCtrl *petIcon = dynamic_cast<CcbPetIconCtrl*>(node->getChildByTag(tag));
            if (!petIcon) {
                continue;
            }
            if (!petIcon->getPetObjId()) {
                continue;
            }
            petIcon->setNum(0);
            if (mapSelectedPet.find(petIcon->getPetObjId()) != mapSelectedPet.end())
            {
                petIcon->setNum(mapSelectedPet[petIcon->getPetObjId()]);
            }
            //设置过编号的不置灰}
            petIcon->setEnable(!unEnable);
        }
    }
    
    for (int i = 0; i < arrSelectedPet.size(); i++) {
        CPet *p = CPetCtrl::Get()->GetPetByObjId(arrSelectedPet[i]);
        if (p) {
            if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB) {
                PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, p->GetwIndex());
                //钱}
                costCoin += ENHANCE_MONEY(pCfg->dwMergeExpFatio, p->GetbyLv(), pCfg->dwMergeCoinFatio);
                //经验}
                //                        bool same = false;
                //                        if (p->GetbyNature1() == pet->GetbyNature1()) {
                //                            //            exp *= 1.5;
                //                            same = true;
                //                        }
                getExp += ENHANCE_EXP(pCfg->dwMergeExpFatio, p->GetbyLv());
            }
            else
            {
                costCoin += p->GetbyStarLv() * 1000;
                getExp ++;
            }
        }
    }
    CCString *str = CCString::create("");
    //金币}
    str->initWithFormat("%d", costCoin);
    m_pLabelTTFMoney->setString(str->getCString());
    
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB
        && costCoin > CGameSession::GetRole()->GetdwCoin()) {
        m_pLabelTTFMoney->setColor(ccRED);
    }
    else
    {
        m_pLabelTTFMoney->setColor(ccWHITE);
    }
    
    if (CPetCtrl::Get()->GetPetBagType() == CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_SUB) {
        //获得经验}
        str->initWithFormat("%d", getExp);
        m_pLabelTTFExp->setString(str->getCString());
    }
}

void CcbPetBagSaleLayer::clearSelected()
{
    CPetCtrl::Get()->ClearSelectedPet();
    ReflashPetBagNum();
}


void CcbPetBagSaleLayer::checkSale()
{
    //学了被动技能的出售、3星以上出售、满级的出售}
//    bool flagSkill = false;
    bool flagStar = false;
    bool flagLv = false;
    bool flagFiveStar = false;
    
    std::vector<uint32> arrMemberObjId =  CPetCtrl::Get()->GetSelectedPet();
    
    if (arrMemberObjId.size() == 0) {
        return;
    }
    
    for (int i = 0; i < arrMemberObjId.size(); i++) {
        if (!arrMemberObjId[i]) {
            continue;
        }
        CPet *p = CPetCtrl::Get()->GetPetByObjId(arrMemberObjId[i]);
        if (!p) {
            continue;
        }
        PetConfig::STC_PET_CONFIG *pCfg = GET_CONFIG_STC(PetConfig, p->GetwIndex());
        if (!pCfg) {
            continue;
        }
        //学过技能的}
//        if ((p->GetwPassiveSkillId1() && !pCfg->wPassiveSkillId1) ||
//            (p->GetwPassiveSkillId2() && !pCfg->wPassiveSkillId2) ||
//            (p->GetwPassiveSkillId3() && !pCfg->wPassiveSkillId3) //||
//            //            p->GetwPassiveSkillId4() ||
//            //            p->GetwPassiveSkillId5() ||
//            //            p->GetwPassiveSkillId6()
//            ) {
//            //SystemMessage::showSystemMessage(1, this, "出售的宠物中有学习过技能的，确定要出售吗？");
//            flagSkill = true;
//            break;
//        }
        
        if (p->GetbyStarLv() >= 3) {
            flagStar = true;
            if (p->GetbyStarLv() == 5 && p->GetwIndex() != 165) {
                flagFiveStar = true;
            }
            //            SystemMessage::showSystemMessage(1, this, "出售的宠物中有3星级以上的，确定要出售吗？");
            continue;
        }
        
        if (p->GetbyLv() == pCfg->byLvMax) {
            flagLv = true;
            continue;
        }
    }
    
//    if (flagSkill) {
//        SystemMessage::showSystemMessage(1, this, "出售的宠物中有学习过技能的，确定要出售吗？", this);
//        return;
//    }
//    else
    if (flagStar)
    {
        CCString *str = CCString::create("");
        if (flagFiveStar) {
            str->initWithFormat("%s\n%s\n%s", GET_STR(Str_sure_sale_pet_star), GET_STR(Str_five_star_pet_notice), GET_STR(Str_sure_sale));
        }
        else{
            str->initWithFormat("%s\n%s", GET_STR(Str_sure_sale_pet_star), GET_STR(Str_sure_sale));
        }
        
        SystemMessage::showSystemMessage(1, this, str->getCString(), this, false, 1, GET_STR(Str_tishi));

        return;
    }
    else if (flagLv)
    {
        SystemMessage::showSystemMessage(1, this, GET_STR(Str_sure_sale_pet_lv), this, false, 1, GET_STR(Str_tishi));
        return;
    }
    CPetCtrl::Get()->DoSalePet(CPetCtrl::Get()->GetSelectedPet());
    clearSelected();
}

void CcbPetBagSaleLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    if (CPetCtrl::Get()->GetSelectedPet().size() == 0) {
        return;
    }
    CPetCtrl::Get()->DoSalePet(CPetCtrl::Get()->GetSelectedPet());
    clearSelected();
}