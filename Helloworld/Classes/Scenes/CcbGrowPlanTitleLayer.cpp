#include "CcbGrowPlanTitleLayer.h"
//#include "CcbManager.h"
#include "EventDataMgr.h"
#include "Instruments.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "ResourcePic.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark - Constructor -
CcbGrowPlanTitleLayer::CcbGrowPlanTitleLayer()
: m_pSpriteTopType (NULL)
, m_pLabelTTFInfo (NULL)
, m_pLabelTTFTime (NULL)
, m_pNodeRewardType (NULL)
, m_pControlButtonBuy (NULL)
, m_pNodeGrowPlan (NULL)
, m_pCountDown (NULL)
{
    
    
}

CcbGrowPlanTitleLayer::~CcbGrowPlanTitleLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteTopType);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFInfo);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
	CC_SAFE_RELEASE_NULL(m_pNodeRewardType);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBuy);
	CC_SAFE_RELEASE_NULL(m_pNodeGrowPlan);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGrowPlanTitleLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGrowPlanTitleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGrowPlanTitleLayer", CcbGrowPlanTitleLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_reward_type.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

#pragma mark - Initialization -
bool CcbGrowPlanTitleLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbGrowPlanTitleLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTopType", CCSprite*, this->m_pSpriteTopType);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFInfo", CCLabelTTF*, this->m_pLabelTTFInfo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeRewardType", CCNode*, this->m_pNodeRewardType);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBuy", CCControlButton*, this->m_pControlButtonBuy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeGrowPlan", CCNode*, this->m_pNodeGrowPlan);

	return false;
}

bool CcbGrowPlanTitleLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbGrowPlanTitleLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGrowPlanTitleLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGrowPlanTitleLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBuy", CcbGrowPlanTitleLayer::onPressControlButtonBuy);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGrowPlanTitleLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pNodeRewardType->setVisible(false);
    m_pNodeGrowPlan->setVisible(false);
    
    m_pCountDown = ReCountDown::create();
    m_pCountDown->setDelegate(this);
    this->addChild(m_pCountDown);
}

#pragma mark - onEnter & onExit -
void CcbGrowPlanTitleLayer::onEnter()
{
    CCLayer::onEnter();
    this->setShowInfo();
    
}

void CcbGrowPlanTitleLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbGrowPlanTitleLayer::onExit()
{
    CCLayer::onExit();
}

void CcbGrowPlanTitleLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functions -
void CcbGrowPlanTitleLayer::onPressControlButtonBuy(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendBuyGrowUp();
}

void CcbGrowPlanTitleLayer::setShowInfo()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GET_PIC(Pic_event_packer));
    if (g_EventData->GetCurShowEventType() == SHOW_GROW_PLAN) {
        m_pNodeGrowPlan->setVisible(true);
        m_pSpriteTopType->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("event_top_grow.png"));
    }
    else
    {
        m_pNodeRewardType->setVisible(true);
        STC_EVENT_CHANGEABLE_INFO* pChangeableInfo = g_EventData->getEventChangeableInfoByActiveId(g_EventData->GetCurShowEventType());
        if (!pChangeableInfo) {
            return;
        }
        m_pLabelTTFInfo->setString(pChangeableInfo->strDesc.c_str());
        m_pCountDown->setTime(pChangeableInfo->dwLeftTime);
        m_pCountDown->startUpdateCountDown();
        if (pChangeableInfo) {
            CCSpriteFrame* pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(GET_PIC(Pic_event_Event_Top),pChangeableInfo->byRewardBloadType)->getCString());
            if (pSpriteFrame) {
                m_pSpriteTopType->setDisplayFrame(pSpriteFrame);
            }
        }
    }
    
}

void CcbGrowPlanTitleLayer::countDownScheduleCallBack(float cTime, CountType type)
{
    if (type == ENUM_UPDATE) {
        m_pLabelTTFTime->setString(getLeftDayTimeChFormatFromInt(cTime)->getCString());
    }
    else if (type == ENUM_COMPLETE)
    {
        CGameSession::SendRequestActiveList();
        this->removeFromParent();
    }
}




