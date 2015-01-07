#include "CcbFuseListLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "EquipDataMgr.h"
#include "CFuseDadaMgr.h"
#include "UISupport.h"
#include "CCScrollViewWithBar.h"
#include "BackCtrl.h"
#include "GuideData.h"
#include "PacketDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark FuseLise  Scene
FuseListScene::~FuseListScene()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    
}

CCScene *FuseListScene::scene()
{
    CCScene *scene = CCScene::create();
    
    FuseListScene *layer = FuseListScene::create();
    layer->setTag(1);
    scene->addChild(layer);
    
    return scene;
}

bool FuseListScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CCNode * node = CcbManager::sharedManager()->LoadCcbFuseListLayer(this);
    node->setTag(1);
    addChild(node);
	return true;
}

void FuseListScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_pLabelTTFName->setString(GET_STR(Str_equip_pet));
}

void FuseListScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void FuseListScene::onExit()
{
	CCLayer::onExit();
}

void FuseListScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool FuseListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	return false;
}

bool FuseListScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


#pragma mark FuseLise  Layer
CcbFuseListLayer::~CcbFuseListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonEquip);
	CC_SAFE_RELEASE_NULL(m_pControlButtonPet);
	CC_SAFE_RELEASE_NULL(m_pLayerShow);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAccept);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCnt);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFuseListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFuseListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFuseListLayer", CcbFuseListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fuse_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFuseListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFuseListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbFuseListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction( CCSequence::create(CCDelayTime::create(TRANS_DUR*0.5), CCCallFunc::create(this, callfunc_selector(CcbFuseListLayer::addGuideLayer)), NULL));
}

void CcbFuseListLayer::addGuideLayer()
{
//    GuideData::GetInstance()->addGuideofEnum(GuideData::E_SYS_GUIDE_FUSE_3, NULL);
}

void CcbFuseListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFuseListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFuseListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip", CCControlButton*, this->m_pControlButtonEquip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonPet", CCControlButton*, this->m_pControlButtonPet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerShow", CCLayer*, this->m_pLayerShow);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAccept", CCControlButton*, this->m_pControlButtonAccept);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCnt", CCLabelTTF*, this->m_pLabelTTFCnt);

	return false;
}

bool CcbFuseListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFuseListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFuseListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFuseListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEquip", CcbFuseListLayer::onPressControlButtonEquip);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonPet", CcbFuseListLayer::onPressControlButtonPet);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAccept", CcbFuseListLayer::onPressControlButtonAccept);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFuseListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    cellNum = 0;
    curCellSize = CCSizeMake(getWidth(m_pLayerShow), 65);
    m_clipRect.origin = getWorldPos(m_pLayerShow);
    
    m_pLayerShow->setContentSize(CCSizeMake(getWidth(m_pLayerShow), getHeight(m_pLayerShow->getParent()) - getBottom(m_pLayerShow) - 10));
    
    m_clipRect.size = m_pLayerShow->getContentSize();
    
    m_table = CCTableView::create(this, m_pLayerShow->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    CCTableViewWithBar *layerWithBar = CCTableViewWithBar::create(m_table);
    layerWithBar->setPosition(CCPointZero);
    layerWithBar->setAnchorPoint(CCPointZero);
    layerWithBar->setTag(111);
    m_pLayerShow->addChild(layerWithBar);
    
    
    
    m_mapPetIcon.clear();
    m_mapEquipIcon.clear();
    m_arrPetObjId = CPetCtrl::Get()->GetBagPets();
    
    vector<uint32> arrEquipKeyId = g_EquipData->GetVecShowEquipKeyID();
    for (int i = 0; i < arrEquipKeyId.size(); i++)
    {
        const CEquip *equip = g_PacketDataMgr->GetEquipInfoByKeyID(arrEquipKeyId[i]);
        if (!equip
            || equip->GetWearPetID()
            || equip->GetRune1()
            || equip->GetRune2())
        {
            continue;
        }
       
        PetFuseConfig::STC_PET_FUSE_CONFIG* fCfg = GET_CONFIG_STC(PetFuseConfig, equip->GetIndex());
        if (!fCfg)
        {
            continue;
        }
       
        m_arrEquipObjId.push_back(equip->GetKeyID());
    }
    
//    g_FuseDada->setFuseTab(E_FUSE_TAB_PET);
    uint32 cnt = m_arrPetObjId.size();
    if (g_FuseDada->getFuseTab() == E_FUSE_TAB_EQUIP) {
        cnt = m_arrEquipObjId.size();
    }
    if (cnt % 5 > 0) {
        cellNum = cnt / 5 + 1;
    }
    else {
        cellNum = cnt / 5;
    }
    
}

void CcbFuseListLayer::onPressControlButtonEquip(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    g_FuseDada->setFuseTab(E_FUSE_TAB_EQUIP);
    uint32 cnt = m_arrEquipObjId.size();
    if (cnt % 5 > 0) {
        cellNum = cnt / 5 + 1;
    }
    else {
        cellNum = cnt / 5;
    }
    curCellSize = CCSizeMake(getWidth(m_pLayerShow), 70);
    loadData();
}

void CcbFuseListLayer::onPressControlButtonPet(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
	// TODO:
    g_FuseDada->setFuseTab(E_FUSE_TAB_PET);
    uint32 cnt = m_arrPetObjId.size();
    if (cnt % 5 > 0) {
        cellNum = cnt / 5 + 1;
    }
    else {
        cellNum = cnt / 5;
    }
    curCellSize = CCSizeMake(getWidth(m_pLayerShow), 65);
    loadData();
}

void CcbFuseListLayer::onPressControlButtonAccept(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	// TODO:
    BackCtrl::BacktoUpperScene();
}

void CcbFuseListLayer::loadData()
{
    std::map<uint32, CcbPetIconCtrl*>::iterator it = m_mapPetIcon.begin();
    for (; it != m_mapPetIcon.end(); it++) {
        CcbPetIconCtrl *icon = it->second;
        if (!icon) {
            continue;
        }
        icon->removeFromParent();
    }
    std::map<uint32, CcbPetEquipIcon*>::iterator itE = m_mapEquipIcon.begin();
    for (; itE != m_mapEquipIcon.end(); itE++) {
        CcbPetEquipIcon *icon = itE->second;
        if (!icon) {
            continue;
        }
        
        if (!icon->getParent()) {
            CC_SAFE_RELEASE_NULL(icon);
            continue;
        }
        
        icon->removeFromParent();
    }
    
    m_mapPetIcon.clear();
    m_mapEquipIcon.clear();
    
    m_pLabelTTFCnt->setString("0");
    bool isPet = g_FuseDada->getFuseTab() == E_FUSE_TAB_PET;
    m_pControlButtonPet->setEnabled(!isPet);
    m_pControlButtonEquip->setEnabled(isPet);
//    m_table->getContainer()->removeAllChildren();
    
//    if (m_pLayerShow->getChildByTag(111)) {
//        m_pLayerShow->removeChildByTag(111);
//    }
    
//    m_table = CCTableView::create(this, m_pLayerShow->getContentSize());
//    m_table->setDirection(kCCScrollViewDirectionVertical);
//    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
//    m_table->setBounceable(true);
//    CCTableViewWithBar *layerWithBar = CCTableViewWithBar::create(m_table);
//    layerWithBar->setPosition(CCPointZero);
//    layerWithBar->setAnchorPoint(CCPointZero);
//    layerWithBar->setTag(111);
//    m_pLayerShow->addChild(layerWithBar);
    
    while (true) {
       CCTableViewCell* cell = m_table->dequeueCell();
        if (!cell) {
            break;
        }
        cell->removeAllChildren();
        m_table->removeCellAtIndex(cell->getIdx());
    }
    
    m_table->reloadData();
}

void CcbFuseListLayer::ReflashPetBagNum()
{
    std::vector<uint32> arrSelectedPet = g_FuseDada->getSelected();
    
    m_pLabelTTFCnt->setString(CCString::createWithFormat("%lu", arrSelectedPet.size())->getCString());
    
    if (arrSelectedPet.size() == 0) {
        return;
    }
    bool unEnable = g_FuseDada->getSelected().size() >= fuseCnt;
    
    if (g_FuseDada->getFuseTab() == E_FUSE_TAB_PET) {
        for (int i = 0; i < arrSelectedPet.size(); i++) {
            uint16 objId = arrSelectedPet[i];
            CcbPetIconCtrl *petIcon = m_mapPetIcon[objId];
            if (!petIcon) {
                continue;
            }
            petIcon->setNum(i+1);
        }
        
        std::map<uint32, CcbPetIconCtrl*>::iterator it = m_mapPetIcon.begin();
        for (; it != m_mapPetIcon.end(); it++) {
            CcbPetIconCtrl *icon = it->second;
            if (!icon) {
                continue;
            }
            //设置过编号的不置灰}
            icon->setEnable(!unEnable);
        }
    }
    else if (g_FuseDada->getFuseTab() == E_FUSE_TAB_EQUIP){
        for (int i = 0; i < arrSelectedPet.size(); i++) {
            uint16 objId = arrSelectedPet[i];
            CcbPetEquipIcon *eIcon = m_mapEquipIcon[objId];
            if (!eIcon) {
                continue;
            }
            eIcon->setNum(i+1);
        }
        std::map<uint32, CcbPetEquipIcon*>::iterator it = m_mapEquipIcon.begin();
        for (; it != m_mapEquipIcon.end(); it++) {
            CcbPetEquipIcon *icon = it->second;
            if (!icon) {
                continue;
            }
            //设置过编号的不置灰}
            icon->setEnable(!unEnable);
        }
    }
}


CCTableViewCell* CcbFuseListLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *cell = table->dequeueCell();

    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCNode *node = CCNode::create();
        node->setContentSize(curCellSize);
        node->setTag(1);
        cell->addChild(node);
    }
    CCNode *node = dynamic_cast<CCNode*>(cell->getChildByTag(1));

    //宠物}
    if (g_FuseDada->getFuseTab() == E_FUSE_TAB_PET) {
        int cnt = m_arrPetObjId.size() - idx * 5;
        if (cnt > 5) {
            cnt  = 5;
        }
        
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
            petIcon->setPosition(ccp(14 + i*60, 5));
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
//                petIcon->removeFromParent();
            }
        }
    }
    //装备}
    else if (g_FuseDada->getFuseTab() == E_FUSE_TAB_EQUIP){
        int cnt = m_arrEquipObjId.size() - idx * 5;
        if (cnt > 5) {
            cnt  = 5;
        }
        
        for (int i = 0; i < cnt; i++) {
            CcbPetEquipIcon *icon = dynamic_cast<CcbPetEquipIcon*>(node->getChildByTag(i+1));
            if (!icon) {
                icon =  dynamic_cast<CcbPetEquipIcon*>(CcbManager::sharedManager()->LoadCcbPetEquipIcon(this));
                icon->setTag(i+1);
                node->addChild(icon);
            }
            else
            {
                m_mapEquipIcon[icon->getEquipObjId()] = NULL;
            }
            
            const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(m_arrEquipObjId[idx * 5 + i]);
            if (!equip) {
                icon->removeFromParent();
                CCLog("~~~~~~pet ObjId %d in petBag not found~~~~", m_arrEquipObjId[idx * 5 + i]);
                continue;
            }
            icon->setVisible(true);
            icon->setEquipObjId(equip->GetKeyID());
//            icon->hideStarLv();
//            icon->hideLv();
//            icon->hideEvoLv();
            icon->setPosition(ccp(14 + i*60, 10));
            icon->setAnchorPoint(ccp(0, 0));
            icon->setClipRect(m_clipRect);
            icon->setTag(i+1);
            
            m_mapEquipIcon[icon->getEquipObjId()] = icon;
        }
        
        for (int i = cnt; i < 5; i++) {
            CcbPetEquipIcon *icon = dynamic_cast<CcbPetEquipIcon*>(node->getChildByTag(i+1));
            if (icon) {
                m_mapEquipIcon[icon->getEquipObjId()] = NULL;
                icon->setVisible(false);
//                icon->removeFromParent();
            }
        }
    }
    
    return cell;
}
unsigned int CcbFuseListLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return cellNum;
}
CCSize CcbFuseListLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return curCellSize;
}





