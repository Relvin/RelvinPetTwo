#include "CcbChallengeType2Layer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "CcbItemIconLayer.h"
#include "StageScene.h"
#include "CcbChallengeNodeLayer.h"
#include "GameSession.h"
#include "FlyTextLayer.h"
#include "Role.h"
#include "AnalysicsManager.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "Team.h"
#include "TeamCtrl.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "BackCtrl.h"


USING_NS_CC;
USING_NS_CC_EXT;
ChallengeType2Scene::ChallengeType2Scene()
: m_pLabelTTFName(NULL)
{
    
}

ChallengeType2Scene::~ChallengeType2Scene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* ChallengeType2Scene::scene()
{
    CCScene *scene = CCScene::create();
    
    ChallengeType2Scene *layer = ChallengeType2Scene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ChallengeType2Scene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    m_pChallengeType2Layer = (CcbChallengeType2Layer *)CcbManager::sharedManager()->LoadCcbChallengeType2Layer(this);
    addChild(m_pChallengeType2Layer);
    return true;
}

bool ChallengeType2Scene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    return false;
}

SEL_MenuHandler ChallengeType2Scene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler ChallengeType2Scene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

void ChallengeType2Scene::onEnter()
{
    CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_ChallengeType2_Title));
    }
    
}



#pragma mark - Constructor -
CcbChallengeType2Layer::CcbChallengeType2Layer()
: m_pNodeReward(NULL)
, m_pMissionStageLayer(NULL)
, m_pNodeTeam(NULL)
, m_pLabelTTFEnergy(NULL)
, m_pLabelTTFLeftCnt(NULL)
, m_pLabelTTFLeaderSkillName(NULL)
, m_pLabelTTFLeaderSkillDes(NULL)
, m_nCurIndex(0)
{
    
}

CcbChallengeType2Layer::~CcbChallengeType2Layer()
{
	CC_SAFE_RELEASE_NULL(m_pNodeReward);
    CC_SAFE_RELEASE_NULL(m_pMissionStageLayer);
    CC_SAFE_RELEASE_NULL(m_pNodeTeam);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergy);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillDes);

}

#pragma mark - Initialization -
bool CcbChallengeType2Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeType2Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeReward", CCNode*, this->m_pNodeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMissionStageLayer", CcbChallengeMissionStageLayer*, this->m_pMissionStageLayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTeam", CCNode*, this->m_pNodeTeam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCnt", CCLabelTTF*, this->m_pLabelTTFLeftCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillName", CCLabelTTF*, this->m_pLabelTTFLeaderSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillDes", CCLabelTTF*, this->m_pLabelTTFLeaderSkillDes);
	return false;
}

bool CcbChallengeType2Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeType2Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeType2Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeType2Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBattle", CcbChallengeType2Layer::onPressControlButtonBattle);
	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeType2Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pMissionStageLayer->setDelegage(this);
    m_pMissionStageLayer->setButtonVisible(false);
    
    CCNode* pBattlePetNode = NULL;
    CcbItemIconLayer* pPetIcon = NULL;
    CCSprite* pBattleTypeSprite = NULL;
    for (int i = 0; i < 6; i++) {
        pBattlePetNode = m_pNodeTeam->getChildByTag(i);
        pPetIcon = (CcbItemIconLayer *)pBattlePetNode->getChildByTag(0);
        pBattleTypeSprite = (CCSprite *)pBattlePetNode->getChildByTag(1);
        m_pItemIcon[i] = pPetIcon;
        m_pBattleType[i] = pBattleTypeSprite;
        
    }
    
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG* pConfig = CTeamCtrl::GetTeamLeaderSkill(CTeamCtrl::GetCurTeamId());
    if (pConfig) {
        m_pLabelTTFLeaderSkillName->setString(pConfig->strName.c_str());
        m_pLabelTTFLeaderSkillDes->setString(pConfig->strDes.c_str());
    }
    else
    {
        m_pLabelTTFLeaderSkillName->setString(GET_STR(Str_wu));
        m_pLabelTTFLeaderSkillDes->setString("");
    }

}

#pragma mark - onEnter & onExit -
void CcbChallengeType2Layer::onEnter()
{
    CCLayer::onEnter();
    this->loadBattleTeamInfo();
}

void CcbChallengeType2Layer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
}

void CcbChallengeType2Layer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeType2Layer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Stage Change CallBack -
void CcbChallengeType2Layer::updateCurrentLayerInfoByIndex(uint32 dwIndex)
{
    m_nCurIndex = dwIndex;
    StageCtrl::STC_STAGE* pConfigStage = StageCtrl::Get()->getStageByStageId(dwIndex);
    if (!pConfigStage) {
        return;
    }
    CcbItemIconLayer* pItemIconLayer = NULL;
    for (int i = 0; i < 10; i++) {
        pItemIconLayer = (CcbItemIconLayer*)m_pNodeReward->getChildByTag(i);
        if (pConfigStage->m_vecItemId.size() + pConfigStage->m_vecPetId.size() <= i) {
            pItemIconLayer->setVisible(false);
            continue;
        }
        pItemIconLayer->setVisible(true);
        if (pConfigStage->m_vecPetId.size() <= i) {
            pItemIconLayer->loadIndexData(pConfigStage->m_vecItemId[i - pConfigStage->m_vecPetId.size()]);
        }
        else
        {
            pItemIconLayer->loadIndexData(pConfigStage->m_vecPetId[i]);
        }
        pItemIconLayer->setLabelNameColor(ccWHITE);
        
    }
    
    
    CCString* pCostEnergy = CCString::createWithFormat(GET_STR(Str_energy_cost), pConfigStage->byCostEnergy);
    m_pLabelTTFEnergy->setString(pCostEnergy->getCString());
    
    int leftCnt = 0;
    if (pConfigStage->byMaxAttCnt + pConfigStage->byBuyCnt > pConfigStage->byAttackCnt) {
        leftCnt = pConfigStage->byMaxAttCnt + pConfigStage->byBuyCnt - pConfigStage->byAttackCnt;
    } else {
        leftCnt = 0;
    }
    CCString* pLeftCnt = CCString::createWithFormat(GET_STR(Str_cnt_last), leftCnt);
    m_pLabelTTFLeftCnt->setString(pLeftCnt->getCString());
}

#pragma mark - Button Functions -
void CcbChallengeType2Layer::onPressControlButtonBattle(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (this->getTouchMoved()) {
        return;
    }
    CCControlButton* pButton = (CCControlButton *)pObject;
    if (!pButton) {
        return;
    }
    StageCtrl::Get()->setSelectStageId(m_nCurIndex);
    StageCtrl::STC_STAGE* pConfigStage = StageCtrl::Get()->getStageByStageId(m_nCurIndex);
    if (!pConfigStage) {
        return;
    }
    CRole* pRole = CGameSession::GetRole();
    if (pConfigStage->wRoleLvLimit > pRole->GetwRoleLv()) {
        CCString* pLimitStr = CCString::createWithFormat(GET_STR(Str_will_open_at_level), pConfigStage->wRoleLvLimit);
        FlyTextLayer::showTips(pLimitStr->getCString());
        return;
    }
    
    CGameSession::SendSpecialBattle(StageCtrl::Get()->selectedActivityMapIdx(), m_nCurIndex, false);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("active_battle_enter");
#endif
    
}

#pragma mark - Self Functions -
void CcbChallengeType2Layer::loadBattleTeamInfo()
{
    CTeam *team = CTeamCtrl::GetCurTeam();
    if (!team) {
        return;
    }
    
    int nCount = 0,nNoneCount = CTeamCtrl::getCurrentTeamPetNums();
    CPet *pPet = NULL;
    
    for (int i = 0; i <= 6; i++) {
        
        if (i != 0) {
            if (!team->getarrPetObId()[i]) {
                m_pItemIcon[nNoneCount]->setTag(i);
                nNoneCount++;
                continue;
            }
            if (i == team->getbyLeaderSite()) {
                continue;
            }
            m_pItemIcon[nCount]->loadObjData(team->getarrPetObId()[i], E_UNITE_TYPE_PET);
            m_pItemIcon[nCount]->setTag(i);
            pPet = CPetCtrl::Get()->GetPetByObjId(team->getarrPetObId()[i]);
        }
        else
        {
            m_pItemIcon[nCount]->loadObjData(team->getarrPetObId()[team->getbyLeaderSite()], E_UNITE_TYPE_PET);
            m_pItemIcon[nCount]->setTag(team->getbyLeaderSite());
            pPet = CPetCtrl::Get()->GetPetByObjId(team->getarrPetObId()[team->getbyLeaderSite()]);
        }
        
        
        m_pItemIcon[nCount]->setVisible(true);
        m_pItemIcon[nCount]->setDelegate(this);
        m_pItemIcon[nCount]->hideName();
        
        if (pPet) {
            m_pBattleType[nCount]->setVisible(true);
            m_pBattleType[nCount]->setDisplayFrame(CPetCtrl::Get()->GetPetTypeSF(pPet->GetwIndex()));
        }
        ++nCount;
    }
    
    for(;nCount < 6;nCount++)
    {
        m_pBattleType[nCount]->setVisible(false);
        if (nCount >= CGameSession::GetRole()->GetdwBattleBagCnt()) {
            m_pItemIcon[nCount]->setVisible(false);
            continue;
        }
        m_pItemIcon[nCount]->setDelegate(this);
        m_pItemIcon[nCount]->loadObjData(0, E_UNITE_TYPE_PET);
    }
    
}

void CcbChallengeType2Layer::itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId)
{
    CTeam* team = CTeamCtrl::GetCurTeam();
    int site = pItemIcon->getTag();
    if (team->getbyLeaderSite() == site) {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_LEADER);
    }
    else
    {
        CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_PARTY_NORMAL);
    }
    CTeamCtrl::SetSelectedMemberSite(site);
    BackCtrl::InsertNextScene(kPetBagScene, kNormalTrans);
}


