#include "CcbChallengeBossLayer.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "WorldBossDataMgr.h"
#include "ChallengeCtrl.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark - Constructor -
CcbChallengeBossLayer::CcbChallengeBossLayer()
: m_pSpriteBossIcon(NULL)
, m_pLabelName(NULL)
{
    
}

CcbChallengeBossLayer::~CcbChallengeBossLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteBossIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelName);

}

#pragma mark - Initialication -
bool CcbChallengeBossLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeBossLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBossIcon", CCSprite*, this->m_pSpriteBossIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelName", CCLabelTTF*, this->m_pLabelName);

	return false;
}

bool CcbChallengeBossLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeBossLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeBossLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeBossLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClickedCallBack", CcbChallengeBossLayer::onPressControlButtonClickedCallBack);
	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeBossLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}


#pragma mark - onEnter & onExit -
void CcbChallengeBossLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void CcbChallengeBossLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengeBossLayer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeBossLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functions -
void CcbChallengeBossLayer::onPressControlButtonClickedCallBack(CCObject* pObject, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
//    FlyTextLayer::showTips(GET_STR(Str_func_not_open));
//    return;
    ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendWorldBossInfo();
    if (g_WorldBossData->getLastRank().size() == 0) {
        CGameSession::SendReqWorldBossList();
    }
}




