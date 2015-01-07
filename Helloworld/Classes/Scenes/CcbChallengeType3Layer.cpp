#include "CcbChallengeType3Layer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "ConfigData.h"
#include "MusicCtrl.h"
#include "ChallengeCtrl.h"
#include "CcbChallengetype3ScrollLayer.h"
#include "CcbChallengeNodeLayer.h"
#include "StageScene.h"
#include "FlyTextLayer.h"
#include "PetLoadingLayer.h"
#include "AnalysicsManager.h"
#include "GameSession.h"
#include "Role.h"
#include "Instruments.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "BackCtrl.h"


USING_NS_CC;
USING_NS_CC_EXT;

ChallengeType3Scene::ChallengeType3Scene()
: m_pLabelTTFName(NULL)
{
    
}

ChallengeType3Scene::~ChallengeType3Scene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* ChallengeType3Scene::scene()
{
    CCScene *scene = CCScene::create();
    
    ChallengeType3Scene *layer = ChallengeType3Scene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ChallengeType3Scene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbChallengeType3Layer(this));
    return true;
}

bool ChallengeType3Scene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    return false;
}

void ChallengeType3Scene::onEnter()
{
    CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_ChallengeType3_Title));
    }
    
}


#pragma mark - Constructor -
CcbChallengeType3Layer::CcbChallengeType3Layer()
: m_pLayerUp (NULL)
, m_pControlButtonLeft (NULL)
, m_pControlButtonRight (NULL)
, m_pLayerScroll (NULL)
, m_pLabelTTFMissionLevel (NULL)
, m_pTableView(NULL)
, m_pNodeTeam(NULL)
, m_pLabelTTFEnergy(NULL)
, m_pLabelTTFLeftCnt(NULL)
, m_pLabelTTFLeaderSkillName(NULL)
, m_pLabelTTFLeaderSkillDes(NULL)
, m_bTouchMoved(false)
, m_TouchBeginPos(0,0)
, m_TouchRect(0,0,0,0)
, m_nCurPage(0)
, m_nTotalPage(0)
, m_nCurIndex(0)
, m_pCurNode(NULL)
, m_nSelectPage(0)
, m_bFirstSelect(true)
{
    
    
}

CcbChallengeType3Layer::~CcbChallengeType3Layer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerUp);
	CC_SAFE_RELEASE_NULL(m_pControlButtonLeft);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRight);
	CC_SAFE_RELEASE_NULL(m_pLayerScroll);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFMissionLevel);
    CC_SAFE_RELEASE_NULL(m_pNodeTeam);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEnergy);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCnt);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLeaderSkillDes);

}

#pragma mark - Initialization -
bool CcbChallengeType3Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    this->setTouchEnabled(true);
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeType3Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLeft", CCControlButton*, this->m_pControlButtonLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRight", CCControlButton*, this->m_pControlButtonRight);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerScroll", CCLayer*, this->m_pLayerScroll);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMissionLevel", CCLabelTTF*, this->m_pLabelTTFMissionLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeTeam", CCNode*, this->m_pNodeTeam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEnergy", CCLabelTTF*, this->m_pLabelTTFEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCnt", CCLabelTTF*, this->m_pLabelTTFLeftCnt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillName", CCLabelTTF*, this->m_pLabelTTFLeaderSkillName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeaderSkillDes", CCLabelTTF*, this->m_pLabelTTFLeaderSkillDes);
	return false;
}

bool CcbChallengeType3Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeType3Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeType3Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeType3Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbChallengeType3Layer::onPressControlButtonLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbChallengeType3Layer::onPressControlButtonRight);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClickedCallBack", CcbChallengeType3Layer::onPressControlButtonClickedCallBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBattle", CcbChallengeType3Layer::onPressControlButtonBattle);

	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeType3Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pTableView = CCTableView::create(this, m_pLayerScroll->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pTableView->setBounceable(false);
    m_pLayerScroll->addChild(m_pTableView);
    
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
    
    m_nTotalPage = ChallengeCtrl::Get()->getChallengeStageInfoCountByMapId(ChallengeCtrl::Get()->getChallengeType());
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
void CcbChallengeType3Layer::onEnter()
{
    CCLayer::onEnter();
    CCPoint validPos = m_pLayerScroll->convertToWorldSpace(CCPointZero);
    m_TouchRect = CCRectMake(validPos.x, validPos.y, m_pLayerScroll->getContentSize().width, m_pLayerScroll->getContentSize().height);
    m_pTableView->reloadData();
    m_pLabelTTFMissionLevel->setString(CCString::createWithFormat("%s %s",GET_STR(Str_ChallengeDifficultLevel),covert2Roman(m_nCurPage + 1).c_str())->getCString());
    m_pControlButtonLeft->setVisible(false);
    m_pControlButtonRight->setVisible(false);
    this->loadBattleTeamInfo();
}

void CcbChallengeType3Layer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if (ChallengeCtrl::Get()->getCellIndex() != -1) {
        this->updateTableViewPos(ChallengeCtrl::Get()->getCellIndex());
    }
    else
    {
        this->updateTableViewPos(0);
    }
}

void CcbChallengeType3Layer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeType3Layer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functinos -
void CcbChallengeType3Layer::onPressControlButtonLeft(CCObject* pSender, CCControlEvent event)
{
    if (!m_bTouchMoved) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
        this->updateTableViewPos(-1);
    }
}

void CcbChallengeType3Layer::onPressControlButtonRight(CCObject* pSender, CCControlEvent event)
{
    if (!m_bTouchMoved) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
        this->updateTableViewPos(1);
    }
}

void CcbChallengeType3Layer::onPressControlButtonClickedCallBack(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
   
}

#pragma mark - TableView Functions -
CCTableViewCell *CcbChallengeType3Layer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbChallengetype3ScrollLayer(this, m_pLayerScroll->getContentSize());
        pCell->addChild(pNode);
        pNode->setTag(0);
    }
    CcbChallengetype3ScrollLayer* pTypeCellLayer = (CcbChallengetype3ScrollLayer*)pCell->getChildByTag(0);
    if (pTypeCellLayer) {
        pTypeCellLayer->setDelegate(this);
        pTypeCellLayer->setScrollLayerInfoByDiffiValue(idx + 1);
        if (idx == 0 && m_bFirstSelect) {
            m_bFirstSelect = false;
            pTypeCellLayer->setFirstButtonSelected();
        }
    }
    return pCell;
}

unsigned int CcbChallengeType3Layer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return m_nTotalPage;
}

CCSize CcbChallengeType3Layer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return m_pLayerScroll->getContentSize();
}

#pragma mark - Touch Functions -
bool CcbChallengeType3Layer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchMoved = false;
    m_TouchBeginPos = pTouch->getLocation();
    
    if (!m_TouchRect.containsPoint(m_TouchBeginPos)) {
        return false;
    }
    return true;
}

void CcbChallengeType3Layer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchMoved = true;
}

void CcbChallengeType3Layer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!m_bTouchMoved) {
        return;
    }
    CCPoint endPos = pTouch->getLocation();
    if (endPos.x < m_TouchRect.origin.x) {
        endPos.x = m_TouchRect.origin.x;
    }
    int movDir = 0;
    if (fabs(endPos.x - m_TouchBeginPos.x) > 50) {
        movDir = (m_TouchBeginPos.x - endPos.x) > 0 ? 1 : -1;
    }
    this->updateTableViewPos(movDir);
}

void CcbChallengeType3Layer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbChallengeType3Layer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

#pragma mark - Self Functions -

void CcbChallengeType3Layer::updateTableViewPos(int moveDir)
{
    if (m_nCurPage + moveDir < 0 || m_nCurPage + moveDir >= m_nTotalPage) {
        return;
    }
    m_pTableView->unscheduleAllSelectors();
    m_pTableView->getContainer()->stopAllActions();
    m_nCurPage += moveDir;
    
    float during = 0.0f;
    float offset = - this->tableCellSizeForIndex(m_pTableView, 0).width * m_nCurPage;
    if (ChallengeCtrl::Get()->getCellIndex() != -1) {
        during = this->tableCellSizeForIndex(m_pTableView, 0).width / 800.f;
        ChallengeCtrl::Get()->setCellIndex(-1);
    }
    else
    {
        during = fabsf((offset - m_pTableView->getContentOffset().x) / 800.0f);
    }
    
    
    m_pTableView->setContentOffsetInDuration(ccp(offset, 0), during);
    m_pLabelTTFMissionLevel->setString(CCString::createWithFormat("%s %s",GET_STR(Str_ChallengeDifficultLevel),covert2Roman(m_nCurPage + 1).c_str())->getCString());
    m_pControlButtonRight->setVisible(true);
    m_pControlButtonLeft->setVisible(true);
    if (m_nCurPage >= m_nTotalPage - 1) {
        m_pControlButtonRight->setVisible(false);
    }
    if (m_nCurPage <= 0)
    {
        m_pControlButtonLeft->setVisible(false);
    }
    
    if (m_nCurPage == m_nSelectPage) {
        if (m_pCurNode) {
            m_pCurNode->setSelectSpriteVisible(true);
        }
    }
    else
    {
        if (m_pCurNode) {
            m_pCurNode->setSelectSpriteVisible(false);
        }
    }
    
//    this->setTitleShowInfo(m_nCurPage);
}


#pragma mark - Button Functions -
void CcbChallengeType3Layer::onPressControlButtonBattle(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event)
{
    ChallengeCtrl::Get()->setCellIndex(m_nCurPage);
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_bTouchMoved) {
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
void CcbChallengeType3Layer::loadBattleTeamInfo()
{
    CTeam *team = CTeamCtrl::GetCurTeam();
    if (!team) {
        return;
    }
    int nCount = 0,nNoneCount = CTeamCtrl::getCurrentTeamPetNums();
    CPet* pPet = NULL;
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

void CcbChallengeType3Layer::itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId)
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

void CcbChallengeType3Layer::challengeNodeClicked(CcbChallengeNodeLayer *pNode)
{
    if (!pNode) {
        return;
    }
    if (m_pCurNode) {
        m_pCurNode->setSelectSpriteVisible(false);
    }
    m_pCurNode = pNode;
    if (m_pCurNode) {
        m_pCurNode->setSelectSpriteVisible(true);
        m_nCurIndex = pNode->getChallengeStageIndex();
        
        StageCtrl::STC_STAGE* pConfigStage = StageCtrl::Get()->getStageByStageId(m_nCurIndex);
        if (!pConfigStage) {
            return;
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
    m_nSelectPage = m_nCurPage;
    
}
