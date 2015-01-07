#include "CcbChallengeSelectBoardLayer.h"
#include "CcbManager.h"
#include "ChallengeCtrl.h"
#include "CcbChallengeNode2Layer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "GuideBtnPos.h"

USING_NS_CC;
USING_NS_CC_EXT;


#pragma mark - Constructor -
CcbChallengeSelectBoardLayer::CcbChallengeSelectBoardLayer()
: m_pControlButtonClose(NULL)
, m_pLayerTable(NULL)

, m_bySelectType((ChallengeCtrl::E_CHALLENGE_NONE))
, m_pTableView(NULL)
{
    vec_ShowInfos.clear();
    m_pCatNode = NULL;
}

CcbChallengeSelectBoardLayer::~CcbChallengeSelectBoardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLayerTable);
    vec_ShowInfos.clear();
}

#pragma mark - Initialication -
bool CcbChallengeSelectBoardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    this->setTouchEnabled(true);
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeSelectBoardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTable", CCLayer*, this->m_pLayerTable);

	return false;
}

bool CcbChallengeSelectBoardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeSelectBoardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeSelectBoardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeSelectBoardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbChallengeSelectBoardLayer::onPressControlButtonClose);

	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeSelectBoardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pTableView = CCTableView::create(this, m_pLayerTable->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pLayerTable->addChild(m_pTableView);
    
}

#pragma mark - onEnter & onExit -
void CcbChallengeSelectBoardLayer::onEnter()
{
    CCLayer::onEnter();
    m_pTableView->reloadData();
    
}

void CcbChallengeSelectBoardLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV && m_pCatNode) {
        runAction(
                  CCSequence::create(
                                     CCDelayTime::create(0.6f),
                                     CCCallFunc::create(this, callfunc_selector(CcbChallengeSelectBoardLayer::addGuideLayer)),
                                     NULL
                                     )
                  );
    }
}

void CcbChallengeSelectBoardLayer::addGuideLayer() {
    GuideBtnPos::Get()->addNodeWorldPos(m_pCatNode, GuideBtnPos::E_MONEY_CAT);
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_SYS_GUIDE_1_CAT,
                                             NULL
                                             );
}

void CcbChallengeSelectBoardLayer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeSelectBoardLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Touch Functions -
bool CcbChallengeSelectBoardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbChallengeSelectBoardLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbChallengeSelectBoardLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbChallengeSelectBoardLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbChallengeSelectBoardLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}


#pragma mark - Button Functions -
void CcbChallengeSelectBoardLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->removeFromParent();
}

#pragma mark - TableView Functions -

CCTableViewCell* CcbChallengeSelectBoardLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbChallengeNode2Layer();
        pNode->setPosition(ccp(8, 0));
        pCell->addChild(pNode);
        pNode->setTag(0);
    }
    CcbChallengeNode2Layer* pChallengeNode = (CcbChallengeNode2Layer *)pCell->getChildByTag(0);
    if (pChallengeNode) {
        pChallengeNode->setChallengeNodeInfoByIndex(vec_ShowInfos[idx].wMapId);
        if (idx == 0) {
            m_pCatNode = pChallengeNode;
        }
    }
    return pCell;
}

unsigned int CcbChallengeSelectBoardLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return vec_ShowInfos.size();
}

CCSize CcbChallengeSelectBoardLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(table->getContentSize().width, 95);
}

#pragma mark - Self Functions -
void CcbChallengeSelectBoardLayer::setSelectType(uint8 byType)
{
    vec_ShowInfos.clear();
    StageCtrl::VEC_SPE_MAP* pVecActs = NULL;
    pVecActs = StageCtrl::Get()->getActivitysByKey(byType - 1);
    if (pVecActs) {
        vec_ShowInfos = *pVecActs;
    }
    
    m_pTableView->reloadData();
}

