#include "CcbPetTujianLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "CCScrollViewWithBar.h"
#include "UISupport.h"
#include "BackCtrl.h"
#include "ResourceStringClient.h"
#include "CcbPetIcon.h"
#include "GlobalData.h"
#include "ResourceDefine.h"
#include "MusicCtrl.h"
#include "CcbTujianFrame.h"
#include "PetLoadingLayer.h"
#include "GachaDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define colCnt  4

PetTujianScene::~PetTujianScene()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene *PetTujianScene::scene()
{
    CCScene *scene = CCScene::create();
    PetTujianScene *layer = PetTujianScene::create();
    scene->addChild(layer);
    return scene;
}

bool PetTujianScene::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    addChild(CcbManager::sharedManager()->LoadCcbPetTujianLayer(this));
	return true;
}

void PetTujianScene::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_pLabelTTFName->setString(GET_STR(Str_layer_pet_tujian));
}

void PetTujianScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void PetTujianScene::onExit()
{
	CCLayer::onExit();
}

void PetTujianScene::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
    CCDirector::sharedDirector()->purgeCachedData();
}

// Inhert MemberVariableAssigner
bool PetTujianScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
	return false;
}

bool PetTujianScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


CcbPetTujianLayer::~CcbPetTujianLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerBg);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPettype);
    CC_SAFE_RELEASE_NULL(m_pSpriteJinduBar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFJindu);
    CC_SAFE_RELEASE_NULL(m_pSpriteSelected);
    CC_SAFE_RELEASE_NULL(m_pControlButtonType1);
    CC_SAFE_RELEASE_NULL(m_pControlButtonType2);
    CC_SAFE_RELEASE_NULL(m_pControlButtonType3);
    CC_SAFE_RELEASE_NULL(m_pControlButtonType4);
    CC_SAFE_RELEASE_NULL(m_pControlButtonType5);
    CC_SAFE_RELEASE_NULL(m_pControlButtonType6);
    CC_SAFE_RELEASE_NULL(m_pNodeTitle);
    CC_SAFE_RELEASE_NULL(m_pNodeTop);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetTujianLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetTujianLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetTujianLayer", CcbPetTujianLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/scrollBar.ccb]", [ccb/scrollBar.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/tujian.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetTujianLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetTujianLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_TUJIAN);
    m_off = CPetCtrl::Get()->getPetBagOffSet();
    
}

void CcbPetTujianLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    selectType(CPetCtrl::Get()->getCurTujianType());
}

void CcbPetTujianLayer::onExit()
{
    CPetCtrl::Get()->setPetBagOffSet(m_scroll->getContentOffset());
	CCLayer::onExit();
}

void CcbPetTujianLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetTujianLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPettype", CCLabelTTF*, this->m_pLabelTTFPettype);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteJinduBar", CCSprite*, this->m_pSpriteJinduBar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFJindu", CCLabelTTF*, this->m_pLabelTTFJindu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSelected", CCSprite*, this->m_pSpriteSelected);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType1", CCControlButton*, this->m_pControlButtonType1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType2", CCControlButton*, this->m_pControlButtonType2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType3", CCControlButton*, this->m_pControlButtonType3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType4", CCControlButton*, this->m_pControlButtonType4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType5", CCControlButton*, this->m_pControlButtonType5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonType6", CCControlButton*, this->m_pControlButtonType6);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTitle", CCNode*, this->m_pNodeTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTop", CCNode*, this->m_pNodeTop);
	return false;
}

bool CcbPetTujianLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetTujianLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

    
	return NULL;
}

SEL_MenuHandler CcbPetTujianLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetTujianLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonType", CcbPetTujianLayer::onPressControlButtonType);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetTujianLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_isOnEnter = true;
    loadWaitTime = 0;
    arrBtn[1] = m_pControlButtonType1;
    arrBtn[2] = m_pControlButtonType2;
    arrBtn[3] = m_pControlButtonType3;
    arrBtn[4] = m_pControlButtonType4;
    arrBtn[5] = m_pControlButtonType5;
    arrBtn[6] = m_pControlButtonType6;
    
    m_clipRect.origin = getWorldPos(m_pLayerBg);
    
    barWidth = getWidth(m_pSpriteJinduBar);
    
    m_pLayerBg->setContentSize(CCSizeMake(getWidth(m_pLayerBg), getBottom(m_pNodeTitle) - 4 - m_pLayerBg->getPositionY()));
    
    m_clipRect.size = m_pLayerBg->getContentSize();
    
    m_scroll = CCScrollView::create(m_pLayerBg->getContentSize());
    m_scroll->setDirection(kCCScrollViewDirectionVertical);
    m_pLayerBg->addChild(m_scroll);
    
    m_curType = 0;
    for ( int i = 1; i < 7; i++) {
        arrBtn[i]->setTag(i);
//        if (i == CPetCtrl::Get()->getCurTujianType()) {
//            selectType(i);
//        }
    }
    
}


void CcbPetTujianLayer::onPressControlButtonType(CCObject* pSender, CCControlEvent event)
{
    if (g_GachaData->getGachaFlag()) {
        return;
    }
    
    if (loadWaitTime > 0) {
        return;
    }
    loadWaitTime = 15;
    schedule(schedule_selector(CcbPetTujianLayer::updateForWaitLoad));
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    int tag = ((CCNode*)pSender)->getTag();
    if (tag != m_curType) {
        CPetCtrl::Get()->setCurTujianType(tag);
        m_off = ccp(0, 1);
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        selectType(tag);

    }
}

void CcbPetTujianLayer::loadData()
{
    m_scroll->getContainer()->removeAllChildren();
    //获取当前属性所有宠物
    m_pLabelTTFPettype->setString(GET_STR(Str_attr_water + m_curType - 1));
    
    std::vector<std::vector<uint16> > arrAllStar;
    for (int i = 0; i < 8; i++) {
        std::vector<uint16> arrStar;
        arrAllStar.push_back(arrStar);
    }
    
//    std::set<uint16> setPet = CPetCtrl::Get()->getPetTujian();
    uint8 byStarLvF = 0;
    uint8 byStarLvT = 8;
    
    if (g_GachaData->getGachaFlag()) {
        if (g_GachaData->byType() == E_LOTTERY_TYPE_JUNIOR) {
            byStarLvF = 1;
            byStarLvT = 5;
        }
        else{
            byStarLvF = 4;
            byStarLvT = 6;
        }
        m_curType = 7;
        m_pNodeTop->setVisible(true);
    }
    else{
        m_pNodeTop->setVisible(false);
    }
    
    
    std::map<uint16, PetConfig::STC_PET_CONFIG> mapAllPet = GET_CONFIG_MAP(PetConfig);
    std::map<uint16, PetConfig::STC_PET_CONFIG>::iterator it = mapAllPet.begin();
    for (; it != mapAllPet.end(); it++) {
        PetConfig::STC_PET_CONFIG petCfg = it->second;
        if (!petCfg.wIndex || !petCfg.byIsTujian
            || (petCfg.byNature1 != m_curType && m_curType != 7)
            || (g_GachaData->getGachaFlag() && !petCfg.byIsGachaShow)) {
            continue;
        }
        if (petCfg.byStarLv < byStarLvF || petCfg.byStarLv > byStarLvT) {
            continue;
        }
        //按星级分类
        std::vector<uint16> arrStar = arrAllStar[petCfg.byStarLv - 1];
        arrStar.push_back(petCfg.wIndex);
        arrAllStar[petCfg.byStarLv - 1] = arrStar;
    }

    //加到scroll中
    float allH = 0;
    uint16 getCnt = 0;
    uint16 allCnt = 0;
    for (int i = 0; i < arrAllStar.size(); i++) {
        if (arrAllStar[i].size() == 0) {
            continue;
        }
        CcbTujianFrame* frame = dynamic_cast<CcbTujianFrame*>(CcbManager::sharedManager()->LoadCcbTujianFrame());
        frame->setPosition(ccp(0, allH));
//        frame->setAnchorPoint(ccp(0.5, 0));
        frame->ignoreAnchorPointForPosition(false);
        frame->setClipRect(m_clipRect);
        m_scroll->addChild(frame);
        
        getCnt += frame->loadData(arrAllStar[i]);
        allCnt += arrAllStar[i].size();
        allH += frame->getContentSize().height + 5;
    }
    m_scroll->setContentSize(CCSizeMake(getWidth(m_pLayerBg), allH));
    if (m_off.y > 0 || m_off.y < m_scroll->getViewSize().height - allH) {
        m_off = ccp(0, m_scroll->getViewSize().height - allH);
    }
    m_scroll->setContentOffset(m_off);
    //进度条
    m_pLabelTTFJindu->setString(CCString::createWithFormat("%d/%d", getCnt , allCnt)->getCString());
    m_pSpriteJinduBar->setTextureRect(CCRectMake(0, 0, barWidth * getCnt / allCnt, getHeight(m_pSpriteJinduBar)));
}

void CcbPetTujianLayer::selectType(uint8 type)
{
    if (m_curType != 0) {
        arrBtn[m_curType]->setScale(0.9);
        arrBtn[m_curType]->setEnabled(true);
    }
    
    m_curType = type;
    arrBtn[m_curType]->setScale(1.1);
    arrBtn[m_curType]->setEnabled(false);
    m_pSpriteSelected->setPosition(arrBtn[m_curType]->getParent()->getPosition());
    if (m_isOnEnter) {
        m_isOnEnter = false;
        loadData();
    }
    else{
        this->runAction(CCSequence::create(CCDelayTime::create(0.05),
                                           CCCallFunc::create(this, callfunc_selector(CcbPetTujianLayer::loadData)),
                                           NULL));
    }

}

void CcbPetTujianLayer::updateForWaitLoad(float time)
{
    loadWaitTime--;
    if (loadWaitTime < 0) {
        PetLoadingLayer::sharedLayer()->End();
        unschedule(schedule_selector(CcbPetTujianLayer::updateForWaitLoad));
    }
}
