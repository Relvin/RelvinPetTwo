#include "CcbChallengetype3ScrollLayer.h"

#include "ChallengeCtrl.h"
#include "ConfigData.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark - Constructor -
CcbChallengetype3ScrollLayer::CcbChallengetype3ScrollLayer()
:m_pDelegate(NULL)
{
    
}

CcbChallengetype3ScrollLayer::~CcbChallengetype3ScrollLayer()
{

}

#pragma mark - Initialzation -
bool CcbChallengetype3ScrollLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengetype3ScrollLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

	return false;
}

bool CcbChallengetype3ScrollLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengetype3ScrollLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengetype3ScrollLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengetype3ScrollLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengetype3ScrollLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

#pragma mark - onEnter & onExit -
void CcbChallengetype3ScrollLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void CcbChallengetype3ScrollLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengetype3ScrollLayer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengetype3ScrollLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Self Functions -
void CcbChallengetype3ScrollLayer::setScrollLayerInfoByDiffiValue(uint8 byDiffiValue)
{
    ChallengeCtrl::VECSTAGE* pVecStage = ChallengeCtrl::Get()->getChallengeStageInfoByDiffiValue(byDiffiValue);
    if (!pVecStage) {
        return;
    }
    
    CcbChallengeNodeLayer* pNodeLayer = NULL;
    for (int i = 0; i < 6; i++) {
        pNodeLayer = (CcbChallengeNodeLayer *)this->getChildByTag(i);
        if (pVecStage->size() <= i) {
            pNodeLayer->setVisible(false);
            continue;
        }
        pNodeLayer->setVisible(true);
        pNodeLayer->setChallengeNodeInfoByIndex((*pVecStage)[i]);
        pNodeLayer->setDelegate(m_pDelegate);
        
        
    }
}

void CcbChallengetype3ScrollLayer::setFirstButtonSelected()
{
    CcbChallengeNodeLayer* pNodeLayer = (CcbChallengeNodeLayer *)this->getChildByTag(0);
    pNodeLayer->onPressControlButtonClickedCallBack(NULL, CCControlEventTouchUpInside);
}





