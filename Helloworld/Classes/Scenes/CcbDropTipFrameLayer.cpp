#include "CcbDropTipFrameLayer.h"
//#include "CcbManager.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "Role.h"
#include "GameSession.h"
#include "StageScene.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "ResourceStringClient.h"
#include "MapScene.h"
#include "EventDataMgr.h"
#include "BackCtrl.h"
#include "GlobalData.h"
#include "PetLoadingLayer.h"
#include "CCScrollButton.h"
#include "ShopDataMgr.h"
#include "ActivityScene.h"
#include "ChallengeCtrl.h"
#include "UISupport.h"
#include "PetCtrl.h"
#include "PacketDataMgr.h"
#include "GachaDataMgr.h"
#include "CcbJumpTipLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbDropTipFrameLayer::~CcbDropTipFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDropplace);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWeikaiqi);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGo);
    CC_SAFE_RELEASE_NULL(m_pSpriteDropRate);
}

//-- copy this to CcbManager
/*
//CcbManager.h
CCNode* LoadCcbDropTipFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbDropTipFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbDropTipFrameLayer", CcbDropTipFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_droptip_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbDropTipFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    
	return true;
}

void CcbDropTipFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbDropTipFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbDropTipFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbDropTipFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbDropTipFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDropplace", CCLabelTTF*, this->m_pLabelTTFDropplace);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWeikaiqi", CCLabelTTF*, this->m_pLabelTTFWeikaiqi);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGo", CCScrollButton*, this->m_pControlButtonGo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDropRate", CCSprite*, this->m_pSpriteDropRate);

	return false;
}

bool CcbDropTipFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbDropTipFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbDropTipFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbDropTipFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGo", CcbDropTipFrameLayer::onPressControlButtonGo);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbDropTipFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonGo->setTouchPriority(kCCMenuHandlerPriority*2 - 2);
}



void CcbDropTipFrameLayer::onPressControlButtonGo(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    switch (m_stageType) {
        case E_ITEM_DROP_STAGE_MAP: {
            requestMap(StageCtrl::kNormalStage);
            break;
        }
        case E_ITEM_DROP_STAGE_SPECIAL: {
            requestMap(StageCtrl::kSpecialStage);
            break;
        }
        case E_ITEM_DROP_STAGE_ACTIVE: {
            GlobalData::kBottomTag = GlobalData::kActiveMapBottom;
            PetLoadingLayer::sharedLayer()->WaitForPacket(true);
            
            StageCtrl::Get()->setFromJump(false);
            ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
            CGameSession::SendSpecialMapList();
            break;
        }
        case E_ITEM_DROP_STAGE_MY_STERY_SHOP: {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            g_EventData->setMyShopType(E_MY_SHOP_MYSTERY);
            CGameSession::SendReqMJShopList();
            CGameSession::SendReqMySteryShopList();
            break;
        }
        case E_ITEM_DROP_STAGE_ARENA: {
//            if (GlobalData::kBottomTag == GlobalData::kAreanBottom) {
//                return;
//            }
//            PetLoadingLayer::sharedLayer()->WaitForPacket();
//            GlobalData::kBottomTag = GlobalData::kAreanBottom;
            BackCtrl::InsertNextScene(kArenaIndexScene);
//            CGameSession::SendEnterArenaSceneRequest();
            break;
        }
        case E_ITEM_DROP_STAGE_SHOP: {
            if (GlobalData::kBottomTag == GlobalData::kShopBottom) {
                return;
            }
//            PetLoadingLayer::sharedLayer()->WaitForPacket();
            GlobalData::kBottomTag = GlobalData::kShopBottom;
            CGameSession::SendReqShopCnt();
            break;
        }
        case E_ITEM_DROP_STAGE_TOWER: {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendRequestTowerInfo();
            break;
        }
        case E_ITEM_DROP_STAGE_CHALLENGE: {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendReqChallengeInfo();
            break;
        }
        case E_ITEM_DROP_STAGE_GACHA: {
            CPetCtrl::Get()->setPetTujianShowId(0);
            g_GachaData->setIsBoardOpen(false);
            PetLoadingLayer::sharedLayer()->WaitForPacket(true);
            BackCtrl::InsertNextScene(kGachaScene);
            break;
        }
        case E_ITEM_DROP_STAGE_VIP: {
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            g_ShopData->SetCurShopShowType(1);
            CGameSession::SendRequestStorePayList();
            break;
        }
        case E_ITEM_DROP_STAGE_BOX:{
            int cnt = g_PacketDataMgr->GetItemCountByIndex(m_stageId);
            
            CShowJumpTip::Get()->setJumpType(E_ITEM_NOT_ENOUGH);
            CShowJumpTip::Get()->setNeedItemId(m_stageId);
            
            if (cnt > 0) {
                BackCtrl::InsertNextScene(kItemListScene);
            }
            else{
                PetLoadingLayer::sharedLayer()->WaitForPacket();
                g_ShopData->SetCurShopShowType(E_SHOP_TYPE_NORMAL);
                CGameSession::SendOpenShopRequest();
            }
            break;
        }
        default:
            break;
    }
}

void CcbDropTipFrameLayer::loadData(uint32 stageId, uint8 stageType, uint8 byDorpProb)
{
    //TODO: 代码重构}
    m_pSpriteDropRate->removeAllChildren();
    m_pSpriteDropRate->setContentSize(CCSizeMake(m_pSpriteDropRate->getTexture()->getContentSize().width, getHeight(m_pSpriteDropRate)));
    for (int i = 1; i < byDorpProb; i++) {
        CCSprite *star = CCSprite::createWithTexture(m_pSpriteDropRate->getTexture());// ("ccbresources/12monthdate/pet/pic_lvstar.png");
        m_pSpriteDropRate->setContentSize(star->getContentSize());
        star->setAnchorPoint(ccp(0, 0));
        star->setPosition(ccp(i*(getWidth(star) + 1), 0));
        m_pSpriteDropRate->addChild(star);
    }
    m_pSpriteDropRate->setContentSize(CCSizeMake((getWidth(m_pSpriteDropRate)+1)*byDorpProb, getHeight(m_pSpriteDropRate)));

    
    m_stageId = stageId;
    m_stageType = stageType;
    /*
     E_ITEM_DROP_STAGE_MAP = 1,              //普通关卡类型	1}
     E_ITEM_DROP_STAGE_SPECIAL = 2,          //精英关卡类型	2}
     E_ITEM_DROP_STAGE_ACTIVE = 3,           //活动关卡类型	3}
     E_ITEM_DROP_STAGE_MY_STERY_SHOP = 4,    //神秘商店	4}
     E_ITEM_DROP_STAGE_ARENA = 5,            //竞技场	5}
     E_ITEM_DROP_STAGE_SHOP = 6,             //商城	6}
     E_ITEM_DROP_STAGE_TOWER = 7,            //爬塔	7}
     E_ITEM_DROP_STAGE_CHALLENGE = 8,        //道馆挑战	8}
     E_ITEM_DROP_STAGE_GACHA = 9,              //宠物 9}
     */
    
    switch (stageType) {
        case E_ITEM_DROP_STAGE_MAP:
        {
            StageConfig::STC_STAGE_CONFIG* cfg = GET_CONFIG_STC(StageConfig, m_stageId);
            if (cfg) {
                m_pLabelTTFDropplace->setString(cfg->strName.c_str());
            }
            //关卡开通判断}
            checkMapOpen(StageCtrl::kNormalStage);
            
        }
            break;
        case E_ITEM_DROP_STAGE_SPECIAL:
        {
            StageHConfig::STC_STAGE_H_CONFIG* cfg = GET_CONFIG_STC(StageHConfig, m_stageId);
            if (cfg) {
                m_pLabelTTFDropplace->setString(cfg->strName.c_str());
            }
            //关卡开通判断}
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_SPECIAL);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* pDebLock = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (pDebLock) {
                hideBtn();
            } else {
                checkMapOpen(StageCtrl::kSpecialStage);
            }
            break;
        }
            
        case E_ITEM_DROP_STAGE_ACTIVE: {

            uint16 wMapId = m_stageId / 1000;
            
            SpecialMapConfig::STC_SPECIAL_MAP_CONFIG* pConfig = GET_CONFIG_STC(SpecialMapConfig, wMapId);
            if (pConfig){
                m_pLabelTTFDropplace->setString(pConfig->strMapName.c_str());
            }
            
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ACTIVITY);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                hideBtn();
            } else {
                showBtn();
            }
            
            break;
        }
        case E_ITEM_DROP_STAGE_MY_STERY_SHOP:
        {
            m_pLabelTTFDropplace->setString(GET_STR(Str_mystery_shop));//291
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_MY_STERY_SHOP);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                hideBtn();
            }
            else{
                showBtn();
            }
        }
            break;
        case E_ITEM_DROP_STAGE_ARENA:
        {
			m_pLabelTTFDropplace->setString(GET_STR(Str_arena));//51
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ARENA);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                hideBtn();
            }
            else{
                showBtn();
            }
        }
            break;
        case E_ITEM_DROP_STAGE_SHOP:
            m_pLabelTTFDropplace->setString(GET_STR(Str_shop));//160
            showBtn();
            break;
        case E_ITEM_DROP_STAGE_TOWER:
        {
            m_pLabelTTFDropplace->setString(GET_STR(Str_pet_tower));//295
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_PATA);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                hideBtn();
            }
            else{
                showBtn();
            }
        }
            break;
        case E_ITEM_DROP_STAGE_CHALLENGE:
        {
            m_pLabelTTFDropplace->setString(GET_STR(Str_badge_challenge));
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                hideBtn();
            }
            else{
                showBtn();
            }
        }
            break;
        case E_ITEM_DROP_STAGE_GACHA: {
            m_pLabelTTFDropplace->setString(GET_STR(Str_gacha_text));
            showBtn();
            break;
        }
        case E_ITEM_DROP_STAGE_VIP: {
            m_pLabelTTFDropplace->setString(GET_STR(Str_send_vip));
            showBtn();
            break;
        }
        case E_ITEM_DROP_STAGE_BOX:{
            ItemConfig::STC_ITEM_CONFIG* itemCfg = GET_CONFIG_STC(ItemConfig, m_stageId);
            if (itemCfg) {
                m_pLabelTTFDropplace->setString(itemCfg->strName.c_str());
            }
            showBtn();
            break;
        }
            
        default:
            break;
    }
}

void CcbDropTipFrameLayer::setClipRect(cocos2d::CCRect rect)
{
    m_pControlButtonGo->setClipRect(rect);
}

#pragma mark Private Method
void CcbDropTipFrameLayer::requestMap(int _kind) {
    uint16 wMapId = m_stageId / 1000;
    
    StageCtrl::Get()->setKind(_kind);
    MapCtrl::nSelectedMapId = wMapId;
    
    MapConfig::STC_MAP_CONFIG* pMapConfig = GET_CONFIG_STC(MapConfig, wMapId);
    if (pMapConfig) {
        StageCtrl::Get()->setCurMapPointName(pMapConfig->strName);
        StageCtrl::Get()->setFromJump(true);
        StageCtrl::Get()->setDropStage(m_stageId);
        CGameSession::SendReqStageInfo(StageCtrl::Get()->kind(), wMapId);
    }
}

void CcbDropTipFrameLayer::checkMapOpen(int _kind) {
    
    CRole* pRole = CGameSession::GetRole();
    uint16 wMapId = 0;
    uint16 wStageId = 0;
    if (_kind == StageCtrl::kNormalStage) {
        wMapId = pRole->GetwPassMapId() + 1;
        wStageId = pRole->GetwPassStageId();
    } else if (_kind == StageCtrl::kSpecialStage) {
        wMapId = pRole->GetwHeroMap() + 1;
        wStageId = pRole->GetwHeroStage();
    }
    int mapId = m_stageId / 1000;
    int tageId = m_stageId % 1000;
    if (mapId < wMapId) {   // 地图点下的关卡全部通关 }
        showBtn();
    } else if (mapId > wMapId) {    // 未开启该地图点 }
        hideBtn();
    } else {    // 判断是否是新开启的地图点 }
        if (wStageId / 1000 < wMapId) { // 该地图点刚刚开启 }
            if (tageId == 1) {
                showBtn();
            } else {
                hideBtn();
            }
        } else {    // 该地图开启但是还没通关
            if (wStageId % 1000 + 1 >= tageId) {
                showBtn();
            } else {
                hideBtn();
            }
        }
    }
}

void CcbDropTipFrameLayer::showBtn(){
    m_pControlButtonGo->setVisible(true);
    m_pLabelTTFWeikaiqi->setVisible(false);
};
void CcbDropTipFrameLayer::hideBtn(){
    m_pControlButtonGo->setVisible(false);
    m_pLabelTTFWeikaiqi->setVisible(true);
};