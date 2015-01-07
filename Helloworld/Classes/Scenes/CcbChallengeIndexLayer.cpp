#include "CcbChallengeIndexLayer.h"
#include "CcbManager.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "CcbChallengeNodeLayer.h"
#include "ChallengeCtrl.h"
#include "PetLoadingLayer.h"
#include "MapScene.h"
#include "StageScene.h"
#include "FlyTextLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "GuideData.h"
#include "CcbChallengeSelectBoardLayer.h"
#include "ResourcePic.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;

ChallengeIndexScene::ChallengeIndexScene()
: m_pLabelTTFName(NULL)
, m_pChildLayer(NULL)
{
    
}

ChallengeIndexScene::~ChallengeIndexScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* ChallengeIndexScene::scene()
{
    CCScene *scene = CCScene::create();
    
    ChallengeIndexScene *layer = ChallengeIndexScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ChallengeIndexScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    m_pChildLayer = (CcbChallengeIndexLayer *)CcbManager::sharedManager()->LoadCcbChallengeIndexLayer(this);
    addChild(m_pChildLayer);
    return true;
}

bool ChallengeIndexScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    return false;
}

SEL_MenuHandler ChallengeIndexScene::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
    return NULL;
}

SEL_CCControlHandler ChallengeIndexScene::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    return NULL;
}

void ChallengeIndexScene::onEnter()
{
    CCLayer::onEnter();
    if (m_pLabelTTFName) {
        m_pLabelTTFName->setString(GET_STR(Str_relic));
    }
    
}

void ChallengeIndexScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}




#pragma mark - Constructor -
CcbChallengeIndexLayer::CcbChallengeIndexLayer()
: m_pNodeCell (NULL)
{
    m_pLayerPetChanllege = NULL;
    m_pLayerTower = NULL;
    m_pLayerYiji = NULL;
}

CcbChallengeIndexLayer::~CcbChallengeIndexLayer()
{
    CC_SAFE_RELEASE_NULL(m_pNodeCell);
    CC_SAFE_RELEASE_NULL(m_pLayerPetChanllege);
    CC_SAFE_RELEASE_NULL(m_pLayerTower);
    CC_SAFE_RELEASE_NULL(m_pLayerYiji);
}

#pragma mark - initialization -
bool CcbChallengeIndexLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeIndexLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeCell", CCNode*, this->m_pNodeCell);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPetChanllege", CCLayer*, this->m_pLayerPetChanllege);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTower", CCLayer*, this->m_pLayerTower);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerYiji", CCLayer*, this->m_pLayerYiji);
	return false;
}

bool CcbChallengeIndexLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeIndexLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeIndexLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeIndexLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeIndexLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    ChallengeCtrl::Get()->setChallengePetChoose(false);
}

#pragma mark - onEnter & onExit -
void CcbChallengeIndexLayer::onEnter()
{
    CCLayer::onEnter();
    this->setChallengeIndexInfo();
}

void CcbChallengeIndexLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    switch (ChallengeCtrl::Get()->getChallengeStage()) {
        case ChallengeCtrl::E_CHALLENGE_FIGHT:
        case ChallengeCtrl::E_CHALLENGE_TRIAL:
        {
            
            CcbChallengeNodeLayer *pChallengeNodeLayer = ((CcbChallengeNodeLayer*)m_pNodeCell->getChildByTag(ChallengeCtrl::Get()->getChallengeStage() - 1));
            pChallengeNodeLayer->onPressControlButtonClickedCallBack(NULL, CCControlEventTouchUpInside);
            break;
        }
        default:
            break;
    }
    
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerPetChanllege, GuideBtnPos::E_PET_CHANLLENGE);
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerTower, GuideBtnPos::E_TOWER);
        GuideBtnPos::Get()->addNodeWorldPos(m_pLayerYiji, GuideBtnPos::E_YIJI);
        runAction(
                  CCSequence::create(
                                     CCDelayTime::create(0.1f),
                                     CCCallFunc::create(this, callfunc_selector(CcbChallengeIndexLayer::addGuideLayer)),
                                     NULL
                                     )
                  );
    }
}

void CcbChallengeIndexLayer::addGuideLayer() {
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_SYS_GUIDE_0_CAT,
                                             GuideData::E_SYS_GUIDE_2_TOWER,
                                             GuideData::E_SYS_GUIDE_1_BADGE,
                                             GuideData::E_SYS_GUIDE_5_1_BADGE,
                                             NULL
                                             );
}

void CcbChallengeIndexLayer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeIndexLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}


#pragma mark - Self Functions -
void CcbChallengeIndexLayer::setChallengeIndexInfo()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GET_PIC(Pic_Challenge_Index_plist));
    CcbChallengeNodeLayer* pChallengeNode = NULL;
    for (int i = 0; i < 4; i++) {
        pChallengeNode = (CcbChallengeNodeLayer*)m_pNodeCell->getChildByTag(i);
        pChallengeNode->setChallengeStage(i + 1);
        pChallengeNode->setDropItemIconVisible(false);
        pChallengeNode->setAttackCntVisible(false);
        pChallengeNode->setSelectSpriteVisible(false);
        pChallengeNode->setChallengeBackground(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(GET_PIC(Pic_Challenge_Index),i + 1)->getCString()));
        pChallengeNode->setShowTitle(GET_STR(Str_ChallengeIndex_1 + i));
        
        this->setLockStatusByNode(pChallengeNode);
        
    }
}

void CcbChallengeIndexLayer::setLockStatusByNode(cocos2d::CCNode *pNode)
{
    CcbChallengeNodeLayer* pChallengeNode = (CcbChallengeNodeLayer *)pNode;
    if (!pChallengeNode) {
        return;
    }
   
    StageCtrl::VEC_SPE_MAP* pVecActs = NULL;
    pVecActs = StageCtrl::Get()->getActivitysByKey(pChallengeNode->getChallengeStage() - 1);
    uint16 wRoleLv = CGameSession::GetRole()->GetwRoleLv();
    if (pVecActs) {
        int i = 0;
        for (; i < pVecActs->size(); i++) {
            SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, (*pVecActs)[i].wMapId);
            if ((*pVecActs)[i].byIsOpen != 0 && pConfig && wRoleLv >= pConfig->wLimitLv) {
                pChallengeNode->setLockVisible(false);
                break;
            }
        }
        if (i == pVecActs->size()) {
            pChallengeNode->setLockVisible(true);
        }
    }
    else
    {
        pChallengeNode->setLockVisible(true);
    }
    
}

