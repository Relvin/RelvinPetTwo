#include "CcbChallengeType1Layer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "StageScene.h"
#include "CcbItemIconLayer.h"
#include "ReRichText.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "CcbTeamMemberLayer.h"
#include "CcbChallengeNodeLayer.h"
#include "FlyTextLayer.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "Role.h"
#include "AnalysicsManager.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "MusicCtrl.h"


USING_NS_CC;
USING_NS_CC_EXT;


ChallengeType1Scene::ChallengeType1Scene()
: m_pLabelTTFName(NULL)
, m_pChallengeType1Layer(NULL)

{
    
}

ChallengeType1Scene::~ChallengeType1Scene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* ChallengeType1Scene::scene()
{
    CCScene *scene = CCScene::create();
    
    ChallengeType1Scene *layer = ChallengeType1Scene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ChallengeType1Scene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    m_pChallengeType1Layer = (CcbChallengeType1Layer *)CcbManager::sharedManager()->LoadCcbChallengeType1Layer(this);
    addChild(m_pChallengeType1Layer);
    return true;
}

bool ChallengeType1Scene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    return false;
}

SEL_MenuHandler ChallengeType1Scene::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    
    return NULL;
}

SEL_CCControlHandler ChallengeType1Scene::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    return NULL;
}

void ChallengeType1Scene::onEnter()
{
    CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_ChallengeType1_Title));
    }
}


#pragma mark - Constructor -
CcbChallengeType1Layer::CcbChallengeType1Layer()
: m_pNodeTeam (NULL)
, m_pLabelTTFDescribe (NULL)
, m_pNodeReward (NULL)
, m_pMissionStageLayer (NULL)
, m_pLabelTTFEnergy(NULL)
, m_pLabelTTFLeftCnt(NULL)
, m_pLabelTTFLeaderSkillName(NULL)
, m_pLabelTTFLeaderSkillDes(NULL)
, m_pRerichText(NULL)
, m_nCurIndex(0)
{
    
    
}

CcbChallengeType1Layer::~CcbChallengeType1Layer()
{
	CC_SAFE_RELEASE_NULL(m_pNodeTeam);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFDescribe);
	CC_SAFE_RELEASE_NULL(m_pNodeReward);
    CC_SAFE_RELEASE_NULL(m_pMissionStageLayer);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergy);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillDes);

}

#pragma mark - Initialization -
bool CcbChallengeType1Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeType1Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTeam", CCNode*, this->m_pNodeTeam);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFDescribe", CCLabelTTF*, this->m_pLabelTTFDescribe);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeReward", CCNode*, this->m_pNodeReward);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMissionStageLayer", CcbChallengeMissionStageLayer*, this->m_pMissionStageLayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCnt", CCLabelTTF*, this->m_pLabelTTFLeftCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillName", CCLabelTTF*, this->m_pLabelTTFLeaderSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillDes", CCLabelTTF*, this->m_pLabelTTFLeaderSkillDes);

	return false;
}

bool CcbChallengeType1Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeType1Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeType1Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeType1Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBattle", CcbChallengeType1Layer::onPressControlButtonBattle);
	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeType1Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pMissionStageLayer->setDelegage(this);
    
    ChallengeCtrl::Get()->setChallengePetChoose(true);
    m_pRerichText = ReRichText::create("", m_pLabelTTFDescribe->getFontName(), m_pLabelTTFDescribe->getFontSize(),ccp(m_pLabelTTFDescribe->getDimensions().width,0));
    m_pLabelTTFDescribe->getParent()->addChild(m_pRerichText);
    m_pRerichText->setPosition(m_pLabelTTFDescribe->getPosition());
    m_pRerichText->setAnchorPoint(ccp(0, 1));
    m_pRerichText->setVisible(m_pLabelTTFDescribe->isVisible());
    m_pLabelTTFDescribe->setVisible(false);
    
    CCNode* pBattlePetNode = NULL;
    CcbItemIconLayer* pPetIcon = NULL;
    CCSprite* pBattleTypeSprite = NULL;
    for (int i = 0; i < 6; i++) {
        pBattlePetNode = m_pNodeTeam->getChildByTag(i);
        pPetIcon = (CcbItemIconLayer *)pBattlePetNode->getChildByTag(0);
        pBattleTypeSprite = (CCSprite *)pBattlePetNode->getChildByTag(1);
        m_pItemIcon[i] = pPetIcon;
        m_pBattleType[i] = pBattleTypeSprite;
        m_pSpriteTip[i] = (CCSprite *)pBattlePetNode->getChildByTag(2);
        m_pSpriteTip[i]->setVisible(false);
    }
    
    LeaderSkillConfig::STC_LEADER_SKILL_CONFIG* pConfig = CTeamCtrl::GetTeamLeaderSkill(CTeamCtrl::GetCurTeamId());
    if (!pConfig) {
        m_pLabelTTFLeaderSkillName->setString(GET_STR(Str_wu));
        m_pLabelTTFLeaderSkillDes->setString("");
    }
    else
    {
        m_pLabelTTFLeaderSkillName->setString(pConfig->strName.c_str());
        m_pLabelTTFLeaderSkillDes->setString(pConfig->strDes.c_str());
    }
    
}

#pragma mark - onEnter & onExit -
void CcbChallengeType1Layer::onEnter()
{
    CCLayer::onEnter();
    
    m_pRerichText->setString(GET_STR(Str_Challenge_Type1_Text));
    this->loadBattleTeamInfo();
}

void CcbChallengeType1Layer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengeType1Layer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeType1Layer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Stage Change CallBack -
void CcbChallengeType1Layer::updateCurrentLayerInfoByIndex(uint32 dwIndex)
{
    m_nCurIndex = dwIndex;
    StageCtrl::STC_STAGE* pConfigStage = StageCtrl::Get()->getStageByStageId(dwIndex);
    if (!pConfigStage) {
        return;
    }
    CcbItemIconLayer* pItemIconLayer = NULL;
    for (int i = 0; i < 5; i++) {
        pItemIconLayer = (CcbItemIconLayer*)m_pNodeReward->getChildByTag(i);
        if (pConfigStage->m_vecItemId.size() <= i) {
            pItemIconLayer->setVisible(false);
            continue;
        }
        pItemIconLayer->setVisible(true);
        pItemIconLayer->loadIndexData(pConfigStage->m_vecItemId[i]);
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
void CcbChallengeType1Layer::onPressControlButtonBattle(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event)
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
    
    CTeam *team = CTeamCtrl::GetCurTeam();
    if (!team) {
        return;
    }
    
    int cnt = team->getarrPetObId().size();
    
    for (int i = 1; i < cnt; i++) {
        if (team->getarrPetObId()[i]) {
            CPet *pet = CPetCtrl::Get()->GetPetByObjId(team->getarrPetObId()[i]);
            if (pet && (pet->GetbyStarLv() == 4 || (pet->GetbyType2() == E_PET_FORM_DRAGRON && pet->GetbyStarLv() > 4))) {
                
            }
            else
            {
                FlyTextLayer::showTips(GET_STR(Str_Challenge_Pet_Illegal));
                return;
            }
        }
    }
    
    CGameSession::SendSpecialBattle(StageCtrl::Get()->selectedActivityMapIdx(), m_nCurIndex, false);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("active_battle_enter");
#endif

}

#pragma mark - Self Functions -
void CcbChallengeType1Layer::loadBattleTeamInfo()
{
    CTeam *team = CTeamCtrl::GetCurTeam();
    if (!team) {
        return;
    }
    
    CPet* pPet = NULL;
    int nCount = 0,nNoneCount = CTeamCtrl::getCurrentTeamPetNums();
    
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
            m_pBattleType[nCount]->setDisplayFrame(CPetCtrl::Get()->getPetType2SF(pPet->GetwIndex()));
            if (pPet->GetbyStarLv() == 4 || (pPet->GetbyType2() == E_PET_FORM_DRAGRON && pPet->GetbyStarLv() > 4)) {
                
            }
            else
            {
                m_pSpriteTip[nCount]->setVisible(true);
            }
        }
        else
        {
            m_pSpriteTip[nCount]->setVisible(true);
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

void CcbChallengeType1Layer::itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId)
{
    ChallengeCtrl::Get()->setChallengePetChoose(true);
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



