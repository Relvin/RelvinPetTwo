#include "CcbCountryLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "EnumDefines.h"
#include "GameSession.h"
#include "DropItemSprite.h"
#include "EquipDataMgr.h"
#include "GuideData.h"
#include "SystemMessage.h"
#include "FlyTextLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark CountryCtrl

bool CountryCtrl::bCoinBuildOn = false;
bool CountryCtrl::bFarmersBuildOn = false;

void CountryCtrl::HanderCountryBaseInfo(WorldPacket& packet)
{
    uint8 bySize;
    packet >> bySize;
    uint8 byType, byIsRew;
    
    for (int i = 0; i < bySize; i++) {
        packet >> byType >> byIsRew;
        if (byType == E_RES_BUILD_TYPE_COIN) {
            bCoinBuildOn = byIsRew;
        } else if (byType == E_RES_BUILD_TYPE_FARMRES)
        {
            bFarmersBuildOn = byIsRew;
        }
    }
    BackCtrl::ChangeRootScene(kCountryScene);
}

void CountryCtrl::HandlerFarmUpdate(WorldPacket &packet)
{
    uint8 byType, byIsRew;
    packet >> byType >> byIsRew;
    
    if (byType == E_RES_BUILD_TYPE_COIN) {
        bCoinBuildOn = byIsRew;
    } else if (byType == E_RES_BUILD_TYPE_FARMRES) {
        bFarmersBuildOn = byIsRew;
    }
}

#pragma mark CountryScene

CCScene* CountryScene::scene()
{
    CCScene* scene = CCScene::create();
    CountryScene* pLayer = CountryScene::create();
    scene->addChild(pLayer);
    return scene;
}

bool CountryScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbCountryLayer(this));
    return true;
}

bool CountryScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode) {
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    return false;
}

void CountryScene::onEnter()
{
    CCLayer::onEnter();
//    m_pLabelTTFName->setStrokeForLabelTTF(ccBLACK, 1.0);
//    m_pLabelTTFName->setString("乡村");
}

void CountryScene::onExit()
{
    CCLayer::onExit();
}

void CountryScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CountryScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark CountryLayer


CcbCountryLayer::~CcbCountryLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonMine);
	CC_SAFE_RELEASE_NULL(m_pControlButtonFarm);
	CC_SAFE_RELEASE_NULL(m_pControlButtonTree);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRiver);
    CC_SAFE_RELEASE_NULL(m_pControlButtonUpgrad);
//    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pControlButtonCompound);
    CC_SAFE_RELEASE_NULL(m_pControlButtonShowEquip);
    CC_SAFE_RELEASE_NULL(m_pControlButtonFuse);
    CGameSession::Detach(this);
}

//-- copy this to CcbManager
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbCountryLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    CGameSession::Attach(this);
	return true;
}

void CcbCountryLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbCountryLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    this->runAction( CCSequence::create(CCDelayTime::create(TRANS_DUR*0.5), CCCallFunc::create(this, callfunc_selector(CcbCountryLayer::addGuideLayer)), NULL) );
}

void CcbCountryLayer::addGuideLayer()
{
//    GuideData::GetInstance()->addGuideofEnum(GuideData::E_SYS_GUIDE_COUNTRY_1, GuideData::E_SYS_GUIDE_FUSE_1, GuideData::E_SYS_GUIDE_HERO_6, NULL);
}

void CcbCountryLayer::onExit()
{
	CCLayer::onExit();
}

void CcbCountryLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbCountryLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMine", CCControlButton*, this->m_pControlButtonMine);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFarm", CCControlButton*, this->m_pControlButtonFarm);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTree", CCControlButton*, this->m_pControlButtonTree);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRiver", CCControlButton*, this->m_pControlButtonRiver);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonUpgrad", CCControlButton*, this->m_pControlButtonUpgrad);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
     CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCompound", CCControlButton*, this->m_pControlButtonCompound);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowEquip", CCControlButton*, this->m_pControlButtonShowEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFuse", CCControlButton*, this->m_pControlButtonFuse);
	return false;
}

bool CcbCountryLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbCountryLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbCountryLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbCountryLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMine", CcbCountryLayer::onPressControlButtonMine);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFarm", CcbCountryLayer::onPressControlButtonFarm);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTree", CcbCountryLayer::onPressControlButtonTree);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRiver", CcbCountryLayer::onPressControlButtonRiver);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUpgrad", CcbCountryLayer::onPressControlButtonUpgrad);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbCountryLayer::onPressControlButtonBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCompound", CcbCountryLayer::onPressControlButtonCompound);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonShowEquip", CcbCountryLayer::onPressControlButtonShowEquip);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFuse", CcbCountryLayer::onPressControlButtonFuse);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbCountryLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    if (CountryCtrl::bCoinBuildOn) {
        m_pControlButtonTree->setEnabled(true);
    } else {
        m_pControlButtonTree->setEnabled(false);
    }
    
    if (CountryCtrl::bFarmersBuildOn) {
        m_pControlButtonRiver->setEnabled(true);
    } else {
        m_pControlButtonRiver->setEnabled(false);
    }
}

#pragma mark Public Method

void CcbCountryLayer::onPressControlButtonMine(CCObject* pSender, CCControlEvent event)
{
    CGameSession::SendCaptureReq(E_RES_FARM_ROB_TYPE_COIN);
}

void CcbCountryLayer::onPressControlButtonFarm(CCObject* pSender, CCControlEvent event)
{
    CGameSession::SendCaptureReq(E_RES_FARM_ROB_TYPE_FARMRES);
}

void CcbCountryLayer::flyToHome(CCNode* pNode)
{
    pNode->removeFromParentAndCleanup(true);
}

void CcbCountryLayer::onPressControlButtonTree(CCObject* pSender, CCControlEvent event)
{
	// 掉落素材动画}
    CCPoint m_posStart = m_pControlButtonTree->getPosition();
    CCPoint m_posCoinHome = m_pControlButtonFarm->getPosition();
    int r = rand() % 5+4;
    for (int i = 0; i < r; i++) {
        DropItemSprite* pDrop = DropItemSprite::create(E_UNITE_TYPE_SPECIAL*E_UNITE_BASE_FABIO+E_SPECIAL_ID_COIN);
        pDrop->setPosition(m_posStart);
        pDrop->runAct();
        addChild(pDrop);
        pDrop->runAction( CCSequence::create(CCDelayTime::create(1.2f), CCMoveTo::create(0.5f, m_posCoinHome), CCCallFuncN::create(this, callfuncN_selector(CcbCountryLayer::flyToHome)), NULL) );
    }

    CGameSession::SendFarmRewardClick(E_RES_BUILD_TYPE_COIN);
}

void CcbCountryLayer::onPressControlButtonRiver(CCObject* pSender, CCControlEvent event)
{
	// 掉落素材动画}
    CCPoint m_posStart = m_pControlButtonRiver->getPosition();
    CCPoint m_posCoinHome = m_pControlButtonMine->getPosition();
    int r = rand() % 5+4;
    for (int i = 0; i < r; i++) {
        DropItemSprite* pDrop = DropItemSprite::create(E_UNITE_TYPE_SPECIAL*E_UNITE_BASE_FABIO+E_SPECIAL_ID_FARM_RES);
        pDrop->setPosition(m_posStart);
        pDrop->runAct();
        addChild(pDrop);
        pDrop->runAction( CCSequence::create(CCDelayTime::create(1.2f), CCMoveTo::create(0.5f, m_posCoinHome), CCCallFuncN::create(this, callfuncN_selector(CcbCountryLayer::flyToHome)), NULL) );
    }
    CGameSession::SendFarmRewardClick(E_RES_BUILD_TYPE_FARMRES);
}

void CcbCountryLayer::onPressControlButtonUpgrad(CCObject *pSender, CCControlEvent event)
{
//    BackCtrl::InsertNextScene(kBuildUpScene);
    CGameSession::SendReqUpgradeBuildInfo();
    
}

//void CcbCountryLayer::onPressControlButtonBack(CCObject *pSender, CCControlEvent event)
//{
//    BackCtrl::BacktoUpperScene();
//}

void  CcbCountryLayer::onPressControlButtonCompound(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_COMPOUND);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    g_EquipData->SetCompoundTabType(SHOW_TAB_ATTRI_HP);
    BackCtrl::InsertNextScene(kEquipCompoundListScene);
}

void  CcbCountryLayer::onPressControlButtonShowEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_EQUIP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    //g_EquipData->SetIsShowAllEquips(true);
    g_EquipData->SetEquipListShowMode(E_SHOW_LIST_ALL);
//    g_EquipData->SetEquipStrengthenOffsetPos1(ccp(1, 1));
//    g_EquipData->SetEquipStrengthenOffsetPos2(ccp(1, 1));
    BackCtrl::InsertNextScene(kEquipListScene);
}

void  CcbCountryLayer::onPressControlButtonFuse(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_FUSE);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    //g_EquipData->SetIsShowAllEquips(true);
    BackCtrl::InsertNextScene(kPetFuse);
}

#pragma mark ObserverMsg
void CcbCountryLayer::RefeashLayer()
{
    if (CountryCtrl::bCoinBuildOn) {
        m_pControlButtonTree->setEnabled(true);
    } else {
        m_pControlButtonTree->setEnabled(false);
    }
    
    if (CountryCtrl::bFarmersBuildOn) {
        m_pControlButtonRiver->setEnabled(true);
    } else {
        m_pControlButtonRiver->setEnabled(false);
    }
}





