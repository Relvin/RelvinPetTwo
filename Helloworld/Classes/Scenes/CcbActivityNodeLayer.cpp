#include "CcbActivityNodeLayer.h"
#include "CcbManager.h"
#include "StageScene.h"
#include "GameSession.h"
#include "StageScene.h"
#include "ConfigData.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "CcbActivityTipLayer.h"
#include "Role.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"
#include "ResourcePic.h"
#include "PetLoadingLayer.h"
#include "GuideData.h"
#include "MusicCtrl.h"
#include "MapScene.h"
#include "ActivityScene.h"
#include "PacketDataMgr.h"
#include "WorldInfoDataMgr.h"
#include "GuideBtnPos.h"
#include "ChallengeCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbActivityNodeLayer::~CcbActivityNodeLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteActive);
    CC_SAFE_RELEASE_NULL(m_pSpriteLock);
    CC_SAFE_RELEASE_NULL(m_pSpriteWeather);
}


bool CcbActivityNodeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbActivityNodeLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbActivityNodeLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        if (m_wMapId == ChallengeCtrl::kMoneyCat) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNode, GuideBtnPos::E_MONEY_CAT);
        }
        if (m_wMapId == ChallengeCtrl::kTowerTag) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNode, GuideBtnPos::E_TOWER);
        }
        if (m_wMapId == ChallengeCtrl::kDaoGuanTag) {
            GuideBtnPos::Get()->addNodeWorldPos(m_pNode, GuideBtnPos::E_YIJI);
        }
    }
}

void CcbActivityNodeLayer::onExit()
{
	CCLayer::onExit();
}

void CcbActivityNodeLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbActivityNodeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteActive", CCSprite*, this->m_pSpriteActive);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLock", CCSprite*, this->m_pSpriteLock);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteWeather", CCSprite*, this->m_pSpriteWeather);
	return false;
}

bool CcbActivityNodeLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbActivityNodeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbActivityNodeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbActivityNodeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbActivityNodeLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pScrollButtonNode = CCScrollButton::create();
    m_pScrollButtonNode->setZoomOnTouchDown(false);
    m_pScrollButtonNode->setPreferredSize(m_pSpriteLock->getContentSize());
//    m_pScrollButtonNode->setClipRect(CCRectMake(0, 0, 320, 440));
    m_pScrollButtonNode->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbActivityNodeLayer::onPressControlButtonNode), CCControlEventTouchUpInside);
    m_pScrollButtonNode->setPosition(ccp(getWidth(m_pSpriteLock)*0.5, getHeight(m_pSpriteLock)*0.5));
    addChild(m_pScrollButtonNode);
    
    m_pSpriteWeather->setVisible(false);
    m_pSpriteWeather->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.5, 0.95),
                                                                           CCScaleTo::create(1.5, 1.0),
                                                                           NULL)));
    
    
}


void CcbActivityNodeLayer::onPressControlButtonNode(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    //增加锁定提示框}
    SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, m_wMapId);
    if (m_pSpriteLock->isVisible()) {
        
        if (pConfig) {
            std::string strTip;
            StageCtrl::STC_SPE_MAP stcMap = StageCtrl::Get()->activityMapAtIdx(m_wMapId);
            if (stcMap.byIsOpen == 0) {
                strTip = pConfig->wLimitDes;
            }
            else
            {
                strTip = GET_STR(Str_ChallengeRoleLvLimit);
            }
            CcbActivityTipLayer* tip = dynamic_cast<CcbActivityTipLayer*>(CcbManager::sharedManager()->LoadCcbActivityTipLayer());
            tip->loadData(strTip);
            tip->setPosition(ccp(0,0));
            CCDirector::sharedDirector()->getRunningScene()->addChild(tip, 999);
        }
        return;
    }
    
    if (m_wRoleLvLimit > CGameSession::GetRole()->GetwRoleLv()) {
        CCString* pLimitStr = CCString::createWithFormat(GET_STR(Str_will_open_at_level), m_wRoleLvLimit);
        FlyTextLayer::showTips(pLimitStr->getCString());
        return;
    }
    MapCtrl::nSelectedMapId = m_wMapId;
    CCScrollButton* pBtn = dynamic_cast<CCScrollButton*>(pSender);
    if (pBtn != NULL) {
        StageCtrl::Get()->setSelectedActivityMapIdx(pBtn->getTag());
        StageCtrl::Get()->setCurMapPointName(m_strMapName);
        if (pBtn->getTag() == ChallengeCtrl::kDaoGuanTag) {  // 6固定是道馆挑战}
            
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendReqChallengeInfo();
        } else if (pBtn->getTag() == ChallengeCtrl::kTowerTag) {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_PATA);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendRequestTowerInfo();
        } else {
            ChallengeCtrl::Get()->setChallengeType(pBtn->getTag());
            CGameSession::SendSpecialStageInfo(pBtn->getTag());
        }
    }
}


#pragma mark Public Method
void CcbActivityNodeLayer::setNode(int mapIdx)
{
    SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, m_wMapId);
    if (!pConfig) {
        CCLog("Cannot get Special Map config.");
        return;
    }
    StageCtrl::STC_SPE_MAP stcMap = StageCtrl::Get()->activityMapAtIdx(mapIdx);
    
    m_pScrollButtonNode->setTag(stcMap.wMapId);
    m_wMapId = stcMap.wMapId;
    
    if (m_wMapId == ChallengeCtrl::kDaoGuanTag) {
        m_pSpriteWeather->setVisible(true);
        m_pSpriteWeather->setDisplayFrame(g_PacketDataMgr->getWeatherSF(WorldInfoDataMgr::Get()->getWeather()));
    }
    else{
        m_pSpriteWeather->setVisible(false);
    }
    
    m_strMapName = pConfig->strMapName;
    m_wRoleLvLimit = pConfig->wLimitLv;
    if (stcMap.byIsOpen && CGameSession::GetRole()->GetwRoleLv() >= m_wRoleLvLimit) {
        m_pSpriteLock->setVisible(false);
    } else {
        m_pSpriteLock->setVisible(true);
    }
    
    // 换图}
    CCString* picPath = CCString::createWithFormat(GET_PIC(Pic_activity_map), pConfig->wPicId);
    CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage(picPath->getCString());
    if (pTex) {
        m_pSpriteActive->setTexture(pTex);
    } else {
        CCMessageBox("Activity Map Id", "Error");
    }
    
    if (
        m_wMapId == ChallengeCtrl::kMoneyCat ||
        m_wMapId == ChallengeCtrl::kDaoGuanTag ||
        m_wMapId == ChallengeCtrl::kTowerTag
        ) {
        m_pNode = this;
    }
}

void CcbActivityNodeLayer::setClipRect(CCRect rect)
{
    m_pScrollButtonNode->setClipRect(rect);
}


