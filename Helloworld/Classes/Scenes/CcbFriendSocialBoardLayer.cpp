#include "CcbFriendSocialBoardLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "BackCtrl.h"
#include "FriendUnitDataMgr.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendSocialBoardLayer::~CcbFriendSocialBoardLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
	CC_SAFE_RELEASE_NULL(m_pControlButtonMail);
	CC_SAFE_RELEASE_NULL(m_pControlButtonChallenge);
	CC_SAFE_RELEASE_NULL(m_pControlButtonDelete);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendSocialBoardLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendSocialBoardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendSocialBoardLayer", CcbFriendSocialBoardLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_social_board.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendSocialBoardLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbFriendSocialBoardLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendSocialBoardLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendSocialBoardLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendSocialBoardLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendSocialBoardLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMail", CCControlButton*, this->m_pControlButtonMail);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonChallenge", CCControlButton*, this->m_pControlButtonChallenge);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDelete", CCControlButton*, this->m_pControlButtonDelete);

	return false;
}

bool CcbFriendSocialBoardLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbFriendSocialBoardLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendSocialBoardLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendSocialBoardLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbFriendSocialBoardLayer::onPressControlButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMail", CcbFriendSocialBoardLayer::onPressControlButtonMail);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonChallenge", CcbFriendSocialBoardLayer::onPressControlButtonChallenge);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDelete", CcbFriendSocialBoardLayer::onPressControlButtonDelete);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendSocialBoardLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority-1);
    m_pControlButtonChallenge->setTouchPriority(kCCMenuHandlerPriority-1);
    m_pControlButtonDelete->setTouchPriority(kCCMenuHandlerPriority-1);
    m_pControlButtonMail->setTouchPriority(kCCMenuHandlerPriority-1);
}



void CcbFriendSocialBoardLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    removeFromParent();
}

void CcbFriendSocialBoardLayer::onPressControlButtonMail(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    FriendUnitDataMgr::Get()->setMailTarget(m_dwTargetId, m_strTargetName);
    BackCtrl::InsertNextScene(kFriendMailScene);
}

void CcbFriendSocialBoardLayer::onPressControlButtonChallenge(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendFightWithFriend(m_dwTargetId);
}

void CcbFriendSocialBoardLayer::onPressControlButtonDelete(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendDelFriend(m_dwTargetId);
}


void CcbFriendSocialBoardLayer::setTargetIdAndName(uint32 dwTargetId, std::string strTargetName) {
    m_dwTargetId = dwTargetId;
    m_strTargetName = strTargetName;
}

void CcbFriendSocialBoardLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CcbFriendSocialBoardLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    return true;
}


