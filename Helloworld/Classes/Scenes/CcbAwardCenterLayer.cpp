#include "CcbAwardCenterLayer.h"
//#include "CcbManager.h"
#include "MailDataMgr.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "TaskDataMgr.h"
#include "MainLayer.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "Role.h"

CcbAwardCenterLayer::~CcbAwardCenterLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonSystemAward);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAchieve);
	CC_SAFE_RELEASE_NULL(m_pControlButtonDailyQuest);
    CC_SAFE_RELEASE_NULL(m_pControlButtonExchangeCode);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount1);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount2);
	CC_SAFE_RELEASE_NULL(m_pSpriteCount3);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbAwardCenterLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbAwardCenterLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbAwardCenterLayer", CcbAwardCenterLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/award_center.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbAwardCenterLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbAwardCenterLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbAwardCenterLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAwardCenterLayer::onExit()
{
	CCLayer::onExit();
}

void CcbAwardCenterLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbAwardCenterLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSystemAward", CCControlButton*, this->m_pControlButtonSystemAward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAchieve", CCControlButton*, this->m_pControlButtonAchieve);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDailyQuest", CCControlButton*, this->m_pControlButtonDailyQuest);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonExchangeCode", CCControlButton*, this->m_pControlButtonExchangeCode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount1", CCSprite*, this->m_pSpriteCount1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount2", CCSprite*, this->m_pSpriteCount2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCount3", CCSprite*, this->m_pSpriteCount3);

	return false;
}

bool CcbAwardCenterLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAwardCenterLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbAwardCenterLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAwardCenterLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbAwardCenterLayer::onPressControlButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSystemAward", CcbAwardCenterLayer::onPressControlButtonSystemAward);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAchieve", CcbAwardCenterLayer::onPressControlButtonAchieve);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDailyQuest", CcbAwardCenterLayer::onPressControlButtonDailyQuest);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonExchangeCode", CcbAwardCenterLayer::onPressControlButtonExchangeCode);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAwardCenterLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}

    //TODO: Change to Observer will be better
    if (CMailDataMgr::Get()->GetSysRewardNum() > 0)
    {
        m_pSpriteCount1->setVisible(true);
    }
    else
    {
        m_pSpriteCount1->setVisible(false);
    }
    
    //成就可领奖励个数}
    if (g_TaskData->GetAchieveAwardCount() > 0)
    {
        m_pSpriteCount2->setVisible(true);
    }
    else
    {
        m_pSpriteCount2->setVisible(false);
    }
    //每日任务可领个数}
    if (g_TaskData->GetDailyAwardCount() > 0)
    {
        m_pSpriteCount3->setVisible(true);
    }
    else
    {
        m_pSpriteCount3->setVisible(false);
    }
    
    if (CMailDataMgr::Get()->GetSysRewardNum() + g_TaskData->GetAchieveAwardCount() + g_TaskData->GetDailyAwardCount() <= 0) {
        CGameSession::GetRole()->SetbyNotiAward(false);
    }
}

void CcbAwardCenterLayer::onPressControlButtonSystemAward(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kMailListScene);
}

void CcbAwardCenterLayer::onPressControlButtonAchieve(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kAchieveRewardScene);
}

void CcbAwardCenterLayer::onPressControlButtonDailyQuest(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kDailyQuestRewardScene);
}

void CcbAwardCenterLayer::onPressControlButtonExchangeCode(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kExchangeCodeScene);
}
