#include "CcbChallengeNodeLayer.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "PetLoadingLayer.h"
#include "ChallengeCtrl.h"
#include "MapScene.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "CcbManager.h"
#include "CcbChallengeSelectBoardLayer.h"
#include "ResourcePic.h"
#include "StageScene.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"
#include "AnalysicsManager.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "EnumDefines.h"
#include "CcbActivityTipLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark - Constructor -
CcbChallengeNodeLayer::CcbChallengeNodeLayer()
: m_pSpriteMissioonbg (NULL)
, m_pSpriteLock (NULL)
, m_pLabelTTFMissionName (NULL)
, m_pLabelTTFTimes (NULL)
, m_pNodeName1 (NULL)
, m_pSpriteDropicon (NULL)
, m_pControlButton (NULL)
, m_pSpriteSelected (NULL)
, m_byChallengeStage (ChallengeCtrl::E_CHALLENGE_NONE)
, m_dwIndex(0)
, m_pDelegate(NULL)
, m_bCntVisible(true)
, m_bLockVisible(true)
, m_bDropItemVisible(true)
{
    
    
}

CcbChallengeNodeLayer::~CcbChallengeNodeLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteMissioonbg);
	CC_SAFE_RELEASE_NULL(m_pSpriteLock);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMissionName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTimes);
	CC_SAFE_RELEASE_NULL(m_pNodeName1);
	CC_SAFE_RELEASE_NULL(m_pSpriteDropicon);
    CC_SAFE_RELEASE_NULL(m_pControlButton);
    CC_SAFE_RELEASE_NULL(m_pSpriteSelected);

}

#pragma mark - Initialization -
bool CcbChallengeNodeLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeNodeLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteMissioonbg", CCSprite*, this->m_pSpriteMissioonbg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLock", CCSprite*, this->m_pSpriteLock);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMissionName", CCLabelTTF*, this->m_pLabelTTFMissionName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTimes", CCLabelTTF*, this->m_pLabelTTFTimes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeName1", CCNode*, this->m_pNodeName1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDropicon", CCSprite*, this->m_pSpriteDropicon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButton", CCControlButton*, this->m_pControlButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteSelected", CCSprite*, this->m_pSpriteSelected);
    
	return false;
}

bool CcbChallengeNodeLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeNodeLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeNodeLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeNodeLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClickedCallBack", CcbChallengeNodeLayer::onPressControlButtonClickedCallBack);
	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeNodeLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    this->m_pSpriteSelected->setVisible(false);
}

#pragma mark - onEnter & onExit -
void CcbChallengeNodeLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void CcbChallengeNodeLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengeNodeLayer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeNodeLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}


#pragma mark - Self Functions -
void CcbChallengeNodeLayer::setChallengeNodeInfoByIndex(uint32 dwIndex)
{
    ActiveStageConfig::STC_ACTIVE_STAGE_CONFIG* pConfig = GET_CONFIG_STC(ActiveStageConfig, dwIndex);
    if (!pConfig) {
        this->setVisible(false);
        return;
    }
    m_dwIndex = dwIndex;
    m_byChallengeStage = ChallengeCtrl::E_CHALLENGE_NONE;
    this->setVisible(true);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CCString::createWithFormat(GET_PIC(Pic_Challenge_Type_Node_plist),dwIndex / 1000)->getCString());
    
    CCSpriteFrame* pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(GET_PIC(Pic_Challenge_Type_Node),dwIndex / 1000,pConfig->byPicId)->getCString());
    if (pSpriteFrame) {
        m_pSpriteMissioonbg->setDisplayFrame(pSpriteFrame);
    }
    
    CRole* pRole = CGameSession::GetRole();
    if (pRole->GetwRoleLv() >= pConfig->byLvLimit) {
        m_pSpriteLock->setVisible(false);
    }
    else
    {
        if (m_bLockVisible) {
            m_pSpriteLock->setVisible(true);
        }
    }
    m_pLabelTTFMissionName->setString(pConfig->strName.c_str());
    
    StageCtrl::STC_STAGE* pConfigStage = StageCtrl::Get()->getStageByStageId(dwIndex);
    if (pConfigStage) {
        if (m_bCntVisible) {
            this->setAttackCntVisible(true);
            m_pLabelTTFTimes->setString(CCString::createWithFormat("%d/%d",pConfigStage->byAttackCnt,pConfigStage->byMaxAttCnt)->getCString());
        }
        
        if (pConfigStage->m_vecItemId.size() == 0) {
            this->setDropItemIconVisible(false);
        }
        else
        {
            if (m_bDropItemVisible) {
                this->setDropItemIconVisible(true);
                m_pSpriteDropicon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(pConfigStage->m_vecItemId[0]).c_str()));
            }
        }
        
    }
    else
    {
        this->setAttackCntVisible(false);
    }
    
    
}

void CcbChallengeNodeLayer::setDropItemIconVisible(bool bVisible)
{
    m_bDropItemVisible = bVisible;
    m_pSpriteDropicon->getParent()->setVisible(bVisible);
}

void CcbChallengeNodeLayer::setAttackCntVisible(bool bVisible)
{
    m_bCntVisible = bVisible;
    m_pLabelTTFTimes->getParent()->setVisible(bVisible);
}

void CcbChallengeNodeLayer::setChallengeBackground(CCSpriteFrame* pSpriteFrame)
{
    if (pSpriteFrame) {
        m_pSpriteMissioonbg->setDisplayFrame(pSpriteFrame);
    }
}

void CcbChallengeNodeLayer::setLockVisible(bool isVisible)
{
    m_bLockVisible = isVisible;
    m_pSpriteLock->setVisible(isVisible);
}

void CcbChallengeNodeLayer::setShowTitle(const char *strTitle)
{
    m_pLabelTTFMissionName->setString(strTitle);
}

void CcbChallengeNodeLayer::setSelectSpriteVisible(bool isVisible)
{
    m_pSpriteSelected->setVisible(isVisible);
}

#pragma mark - Button Functions -
void CcbChallengeNodeLayer::onPressControlButtonClickedCallBack(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event)
{
    if (pObject) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    }
    
    if (m_dwIndex != 0) {
        this->onStageNodeButtonClicked();
        return;
    }
    
    ChallengeCtrl::Get()->setChallengeStage(this->getChallengeStage());
    switch (m_byChallengeStage) {
        case ChallengeCtrl::E_CHALLENGE_TOWER:
        {
            MapCtrl::nSelectedMapId = StageCtrl::Get()->activityMapAtIdx(this->getChallengeStage() - 1).wMapId;
            
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_PATA);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendRequestTowerInfo();
            break;
        }
        case ChallengeCtrl::E_CHALLENGE_PAVILION:
        {
            MapCtrl::nSelectedMapId = StageCtrl::Get()->activityMapAtIdx(this->getChallengeStage() - 1).wMapId;
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendReqChallengeInfo();
            break;
        }
        case ChallengeCtrl::E_CHALLENGE_FIGHT:
        case ChallengeCtrl::E_CHALLENGE_TRIAL:
        {
            if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
                GuideData::GetInstance()->onlyRmGuideLayer();
            }
            if (this->getLockVisible() && m_byChallengeStage != ChallengeCtrl::E_CHALLENGE_NONE) {
                StageCtrl::VEC_SPE_MAP* vec_spe = StageCtrl::Get()->getActivitysByKey(m_byChallengeStage - 1);
                if (!vec_spe || vec_spe->size() == 0) {
                    return;
                }
                bool bServerOpen = false;
                for (int i = 0; i < vec_spe->size(); i++) {
                    if ((*vec_spe)[i].byIsOpen != 0) {
                        bServerOpen = true;
                        break;
                    }
                }
                std::string strTip;
                if (!bServerOpen) {
                    SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, (*vec_spe)[0].wMapId);
                    if (pConfig) {
                        strTip = pConfig->wLimitDes;
                        CcbActivityTipLayer* tip = dynamic_cast<CcbActivityTipLayer*>(CcbManager::sharedManager()->LoadCcbActivityTipLayer());
                        tip->loadData(strTip);
                        tip->setPosition(ccp(0,0));
                        CCDirector::sharedDirector()->getRunningScene()->addChild(tip, 999);
                    }
                }
                else
                {
                    SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = NULL;
                    int lowLv = 999;
                    for (int i = 0; i < vec_spe->size(); i++)
                    {
                        pConfig = GET_CONFIG_STC(SpecialMapConfig, (*vec_spe)[0].wMapId);
                        if ((*vec_spe)[i].byIsOpen != 0 && pConfig)
                        {
                            lowLv = lowLv > pConfig->wLimitLv ? pConfig->wLimitLv : lowLv;
                        }
                    }
                    strTip = CCString::createWithFormat(GET_STR(Str_ji_lv_open), lowLv)->getCString();
                    FlyTextLayer::showTips(strTip);
                }
                
                return;
                
            }
            
            CCScene* pScene = CCDirector::sharedDirector()->getNowScene();
            if (pScene->getChildByTag(1101)) {
                pScene->removeChildByTag(1101);
            }
            CcbChallengeSelectBoardLayer* pSelectBoard = (CcbChallengeSelectBoardLayer*)CcbManager::sharedManager()->LoadCcbChallengeSelectBoardLayer();
            pSelectBoard->setSelectType(this->getChallengeStage());
            pScene->addChild(pSelectBoard, 10);
            pSelectBoard->setTag(1101);
            
            break;
        }
        default:
            
            break;
    }
}

void CcbChallengeNodeLayer::onStageNodeButtonClicked()
{
    if (m_pDelegate) {
        m_pDelegate->challengeNodeClicked(this);
    }
}

