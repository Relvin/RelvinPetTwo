#include "CcbEmblemChooseListLayer.h"
#include "CcbManager.h"
#include "CcbEmblemIconLayer.h"
#include "UISupport.h"
#include "EmblemDataMgr.h"
#include "CCScrollViewWithBar.h"
#include "BackCtrl.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "GuideData.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "StageScene.h"
#include "ChallengeCtrl.h"

#define clmCnt 5


EmblemChooseListScene::~EmblemChooseListScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* EmblemChooseListScene::scene()
{
    CCScene* pScene = CCScene::create();
    EmblemChooseListScene* pLayer = EmblemChooseListScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool EmblemChooseListScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbEmblemChooseListLayer(this));
    return true;
}

void EmblemChooseListScene::onEnter()
{
    CCLayer::onEnter();
    m_pLabelTTFName->setString(GET_STR(Str_unit_6));
}

void EmblemChooseListScene::onExit()
{
    CCLayer::onExit();
}

void EmblemChooseListScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void EmblemChooseListScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool EmblemChooseListScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName );
    return false;
}

bool EmblemChooseListScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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




CcbEmblemChooseListLayer::~CcbEmblemChooseListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerBadgeBg);
	CC_SAFE_RELEASE_NULL(m_pControlButtonUnSelect);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFExp);
	CC_SAFE_RELEASE_NULL(m_pLayerBack);
    CC_SAFE_RELEASE_NULL(m_pControlButtonYiji);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemChooseListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemChooseListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemChooseListLayer", CcbEmblemChooseListLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_choose.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEmblemChooseListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEmblemChooseListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbEmblemChooseListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    getArrEmbObjId();
    reflashSelected();
}

void CcbEmblemChooseListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEmblemChooseListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemChooseListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBadgeBg", CCLayer*, this->m_pLayerBadgeBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUnSelect", CCControlButton*, this->m_pControlButtonUnSelect);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFExp", CCLabelTTF*, this->m_pLabelTTFExp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBack", CCLayer*, this->m_pLayerBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonYiji", CCControlButton*, this->m_pControlButtonYiji);

	return false;
}

bool CcbEmblemChooseListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemChooseListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemChooseListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemChooseListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUnSelect", CcbEmblemChooseListLayer::onPressControlButtonUnSelect);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbEmblemChooseListLayer::onPressControlButtonOk);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonYiji", CcbEmblemChooseListLayer::onPressControlButtonYiji);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEmblemChooseListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_tableOff = ccp(0, 1);
    m_clipRect.origin = getWorldPos(m_pLayerBadgeBg);
    
    m_pLayerBadgeBg->setContentSize(CCSizeMake(getWidth(m_pLayerBadgeBg), getBottom(m_pLayerBack) - m_clipRect.origin.y + 5));
    m_clipRect.size = m_pLayerBadgeBg->getContentSize();
    
    m_table = CCTableView::create(this, m_pLayerBadgeBg->getContentSize());
    m_table->setPosition(CCPointZero);
    m_table->setAnchorPoint(CCPointZero);
    m_table->setTouchPriority(kCCMenuHandlerPriority - 30);
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    m_table->setContentOffset(ccp(0, 1));
    CCTableViewWithBar *layerWithBar = CCTableViewWithBar::create(m_table);
    layerWithBar->setPosition(CCPointZero);
    layerWithBar->setAnchorPoint(CCPointZero);
    layerWithBar->setTag(111);
    m_pLayerBadgeBg->addChild(layerWithBar);
//    layerWithBar->checkIsShow(numberOfCellsInTableView(m_table), cellSizeForTable(m_table));
    
    m_pControlButtonYiji->getParent()->setVisible(false);
}

void CcbEmblemChooseListLayer::getArrEmbObjId()
{
    m_arrEmbObjId.clear();
    MAP_EMBLEM mapEmb = g_EmblemData->getAllEmblem();
    MAP_EMBLEM::iterator it = mapEmb.begin();
    for (; it != mapEmb.end(); it++) {
        if (!it->second || it->second->getdwPetObjId()
            || it->first == g_EmblemData->getEnhEmbObjId()) {
            continue;
        }
        m_arrEmbObjId.push_back(it->first);
    }
    
    if (m_arrEmbObjId.size() == 0) {
        m_pControlButtonYiji->getParent()->setVisible(true);
    }
}

void CcbEmblemChooseListLayer::onPressControlButtonYiji(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
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

void CcbEmblemChooseListLayer::onPressControlButtonUnSelect(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_EmblemData->clearSelected();
    reflashSelected();
}

void CcbEmblemChooseListLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    BackCtrl::BacktoUpperScene();
}


//tableView相关}
CCTableViewCell* CcbEmblemChooseListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell  = table->dequeueCell();
    int cnt = m_arrEmbObjId.size() - idx * clmCnt;
    if (cnt > clmCnt) {
        cnt  = clmCnt;
    }
    
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCNode *node = CCNode::create();
        node->setContentSize(CCSizeMake(table->getContentSize().width, 68));
        node->setTag(1);
        cell->addChild(node);
    }
    CCNode *node = dynamic_cast<CCNode*>(cell->getChildByTag(1));
    
    for (int i = 0; i < cnt; i++) {
        CcbEmblemIconLayer *icon = dynamic_cast<CcbEmblemIconLayer*>(node->getChildByTag(i+1));
        if (!icon) {
            icon =  dynamic_cast<CcbEmblemIconLayer*>(CcbManager::sharedManager()->LoadCcbEmblemIconLayer(this));
            icon->setTag(i+1);
            node->addChild(icon);
        }
        
        CEmblem *emb = g_EmblemData->getEmblemByObjId(m_arrEmbObjId[idx * clmCnt + i]);
        if (!emb) {
            icon->removeFromParent();
            CCLog("~~~~~~CEmblem ObjId %d in EmblemBag not found~~~~", m_arrEmbObjId[idx *clmCnt + i]);
            continue;
        }
        icon->setVisible(true);
        icon->setEmbObjId(emb->getdwEmlemObjId());
        icon->setDelegate(this);
        icon->setPosition(ccp(8 + i*(60), 13));
        icon->setAnchorPoint(ccp(0, 0));
        icon->setRect(m_clipRect);
        icon->setTag(i+1);
        //        petIcon->setEnable(CPetCtrl::IsPetIconEnable(pet->GetObjId()));
        //        m_mapPetIcon[pet->GetObjId()] = petIcon;
    }
    for (int i = cnt; i <= clmCnt; i++) {
        CcbEmblemIconLayer *icon = dynamic_cast<CcbEmblemIconLayer*>(node->getChildByTag(i+1));
        if (icon) {
            icon->setVisible(false);
        }
    }
    
    return cell;
}
unsigned int CcbEmblemChooseListLayer::numberOfCellsInTableView(CCTableView *table)
{
    if (m_arrEmbObjId.size() % clmCnt > 0) {
        return m_arrEmbObjId.size() / clmCnt + 1;
    }
    return m_arrEmbObjId.size() / clmCnt;
}
CCSize CcbEmblemChooseListLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerBadgeBg), 68);
}

void CcbEmblemChooseListLayer::reflashSelected()
{
    //计算经验
    uint32 allExp = 0;
    for (int i = 0 ; i < g_EmblemData->getSelected().size(); i++) {
        uint32 embId = g_EmblemData->getSelected()[i];
        CEmblem *emb = g_EmblemData->getEmblemByObjId(embId);
        if (!emb) {
            continue;
        }
        EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
        if (!embCfg) {
            continue;
        }
        
        //计算可获得经验}
        allExp += embCfg->dwEatExp * emb->getbyLv();
    }
    m_pLabelTTFExp->setString(CCString::createWithFormat("%d", allExp)->getCString());
    
    CCPoint off = m_table->getContentOffset();
    m_table->reloadData();
    if (off.y > 0) {
        dynamic_cast<CCTableViewWithBar*>(m_pLayerBadgeBg->getChildByTag(111))->checkIsShow(numberOfCellsInTableView(m_table), cellSizeForTable(m_table));
        m_table->scrollToIndex(0);        
    }
    else{
        m_table->setContentOffset(off);
    }
    
}


