#include "CcbEmblemListLayer.h"
#include "CcbManager.h"
#include "EmblemDataMgr.h"
#include "CcbEmblemFrameLayer.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "FlyTextLayer.h"
#include "StageScene.h"
#include "PetLoadingLayer.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "ChallengeCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

EmblemListScene::~EmblemListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* EmblemListScene::scene()
{
    CCScene* pScene = CCScene::create();
    EmblemListScene* pLayer = EmblemListScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool EmblemListScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbEmblemListLayer(this));
    return true;
}

void EmblemListScene::onEnter()
{
    CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_unit_6));
}

void EmblemListScene::onExit()
{
    CCLayer::onExit();
}

void EmblemListScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void EmblemListScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool EmblemListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName );
	return false;
}

bool EmblemListScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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



CcbEmblemListLayer::~CcbEmblemListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerBadgeBg);
    CC_SAFE_RELEASE_NULL(m_pControlButtonYiji);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemListLayer", CcbEmblemListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEmblemListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEmblemListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEmblemListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_scrollOff = g_EmblemData->getBagOffSet();
    loadData();
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEmblemListLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
    CRole* pRole = CGameSession::GetRole();
    pRole->SetbyNotiNewEmblem(false);
//    pRole->SetbyNotiUnit(pRole->GetbyNotiNewPet() | pRole->GetbyNotiNewEquip());
}

void CcbEmblemListLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_9_BADGE,
                                                 NULL
                                                 );
    }
}

void CcbEmblemListLayer::onExit()
{
    g_EmblemData->setBagOffSet(m_table->getContentOffset());
	CCLayer::onExit();
}

void CcbEmblemListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBadgeBg", CCLayer*, this->m_pLayerBadgeBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonYiji", CCControlButton*, this->m_pControlButtonYiji);

	return false;
}

bool CcbEmblemListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonYiji", CcbEmblemListLayer::onPressControlButtonYiji);
	return NULL;
}

void CcbEmblemListLayer::onPressControlButtonYiji(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
//    PetLoadingLayer::sharedLayer()->WaitForPacket();
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ACTIVITY);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }

    StageCtrl::Get()->setFromJump(false);
    ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
    CGameSession::SendSpecialMapList();
}

// Inhert CCNodeLoaderListener
void CcbEmblemListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonYiji->getParent()->setVisible(false);
    arrEmblem.clear();
    CPet* pet = NULL;
    if(g_EmblemData->getEmbInType() == E_EMB_IN_TYPE_WEAR)
    {
        pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetShowPetObjId());
    }
    
    MAP_EMBLEM mapEmb = g_EmblemData->getAllEmblem();
    MAP_EMBLEM::iterator it = mapEmb.begin();
    for (; it != mapEmb.end(); it++) {
        if (pet &&
            (it->first == pet->GetdwEmblemId1() || it->first == pet->GetdwEmblemId2())) {
            continue;
        }
        if (it->second) {
            arrEmblem.push_back(it->first);
        }
    }
    if (pet){
        if (pet->GetdwEmblemId1()) {
            arrEmblem.push_back(pet->GetdwEmblemId1());
        }
        if (pet->GetdwEmblemId2()) {
            arrEmblem.push_back(pet->GetdwEmblemId2());
        }
    }
    
    m_clipRect.origin = getWorldPos(m_pLayerBadgeBg);
    m_pLayerBadgeBg->setContentSize(CCSizeMake(getWidth(m_pLayerBadgeBg), getBottom(getChildByTag(333)) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerBadgeBg->getContentSize();
    if (arrEmblem.size() == 0) {
        m_pControlButtonYiji->getParent()->setVisible(true);
    }
    
    m_table = CCTableView::create(this, m_pLayerBadgeBg->getContentSize());
    m_table->setPosition(CCPointZero);
    m_table->setAnchorPoint(CCPointZero);
    //    table->setTouchPriority(kCCMenuHandlerPriority - 10);
    m_table->setDirection(kCCScrollViewDirectionVertical);
//    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    m_pLayerBadgeBg->addChild(m_table);
    
}

void CcbEmblemListLayer::loadData()
{
    m_table->reloadData();
    
    float contentH = numberOfCellsInTableView(m_table)*cellSizeForTable(m_table).height;
    if (m_scrollOff.y > 0 || m_scrollOff.y < m_table->getViewSize().height - contentH) {
        m_scrollOff = ccp(0, m_table->getViewSize().height - contentH);
    }
    m_table->setContentOffset(m_scrollOff);
}

//tableView相关}
CCTableViewCell* CcbEmblemListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    if (!cell) {
        cell = cell = new CCTableViewCell();
        cell->autorelease();
        CCNode* node = CcbManager::sharedManager()->LoadCcbEmblemFrameLayer(this);
        node->setPosition(getWidth(m_pLayerBadgeBg)* 0.5, 0);
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(ccp(0.5, 0));
        node->setTag(1);
        cell->addChild(node);
    }
    CcbEmblemFrameLayer* node = dynamic_cast<CcbEmblemFrameLayer*>(cell->getChildByTag(1));
    node->setEmblemObjId(arrEmblem[idx]);
    node->setRect(m_clipRect);
    
    return cell;
}
unsigned int CcbEmblemListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return arrEmblem.size();
}
CCSize CcbEmblemListLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerBadgeBg), 90 + 5);
}






