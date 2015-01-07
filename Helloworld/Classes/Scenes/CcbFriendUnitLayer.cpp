#include "CcbFriendUnitLayer.h"
//#include "CcbManager.h"
#include "FriendMiddleBaseLayer.h"
#include "UISupport.h"
#include "FriendUnitDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

//#define Middle_Tag 31199

CcbFriendUnitLayer::~CcbFriendUnitLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonMyFriend);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSuggest);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGetEnergy);
	CC_SAFE_RELEASE_NULL(m_pControlButtonInvite);
	CC_SAFE_RELEASE_NULL(m_pControlButtonMail);
	CC_SAFE_RELEASE_NULL(m_pLayerUp);
	CC_SAFE_RELEASE_NULL(m_pLayerDown);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendUnitLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendUnitLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendUnitLayer", CcbFriendUnitLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_uint.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendUnitLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFriendUnitLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendUnitLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendUnitLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendUnitLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendUnitLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMyFriend", CCControlButton*, this->m_pControlButtonMyFriend);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSuggest", CCControlButton*, this->m_pControlButtonSuggest);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGetEnergy", CCControlButton*, this->m_pControlButtonGetEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonInvite", CCControlButton*, this->m_pControlButtonInvite);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonMail", CCControlButton*, this->m_pControlButtonMail);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerUp", CCLayer*, this->m_pLayerUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDown", CCLayer*, this->m_pLayerDown);

	return false;
}

bool CcbFriendUnitLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendUnitLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendUnitLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendUnitLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMyFriend", CcbFriendUnitLayer::onPressControlButtonMyFriend);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSuggest", CcbFriendUnitLayer::onPressControlButtonSuggest);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGetEnergy", CcbFriendUnitLayer::onPressControlButtonGetEnergy);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonInvite", CcbFriendUnitLayer::onPressControlButtonInvite);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonMail", CcbFriendUnitLayer::onPressControlButtonMail);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendUnitLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    
    m_pSizeMiddle = CCSizeMake(m_pLayerDown->getContentSize().width, getBottom(m_pLayerUp) - getTop(m_pLayerDown));
    m_pPointMiddle = ccp(0, getTop(m_pLayerDown));
    
    m_pControlButtonType[0] = m_pControlButtonMyFriend;
    m_pControlButtonType[1] = m_pControlButtonSuggest;
    m_pControlButtonType[2] = m_pControlButtonGetEnergy;
    m_pControlButtonType[3] = m_pControlButtonMail;
    m_pControlButtonType[4] = m_pControlButtonInvite;
    
    FriendUnitDataMgr::Get()->resetMiddles();
    
    onPressControlButtonMyFriend(m_pControlButtonType[0], CCControlEventTouchUpInside);
}

void CcbFriendUnitLayer::pressControlButton(int _type) {
    if (_type < 0 || _type >= Btn_Cnt) {
        CCMessageBox("Button Idx error", "Error");
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    for (int i = 0; i < Btn_Cnt; i++) {
        if (i == _type) {
            m_pControlButtonType[i]->setEnabled(false);
        } else {
            m_pControlButtonType[i]->setEnabled(true);
        }
    }
}

void CcbFriendUnitLayer::onPressControlButtonMyFriend(CCObject* pSender, CCControlEvent event)
{
    pressControlButton(FriendUnitDataMgr::kFriendListType);
    FriendUnitDataMgr::Get()->setMiddleNode(FriendUnitDataMgr::kFriendListType, m_pSizeMiddle, m_pPointMiddle, m_pLayerDown);
}

void CcbFriendUnitLayer::onPressControlButtonSuggest(CCObject* pSender, CCControlEvent event)
{
    pressControlButton(FriendUnitDataMgr::kFriendSuggestType);
    FriendUnitDataMgr::Get()->setMiddleNode(FriendUnitDataMgr::kFriendSuggestType, m_pSizeMiddle, m_pPointMiddle, m_pLayerDown);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendReqRecommendFriendList();
}

void CcbFriendUnitLayer::onPressControlButtonGetEnergy(CCObject* pSender, CCControlEvent event)
{
    pressControlButton(FriendUnitDataMgr::kEnergyGetType);
    FriendUnitDataMgr::Get()->setMiddleNode(FriendUnitDataMgr::kEnergyGetType, m_pSizeMiddle, m_pPointMiddle, m_pLayerDown);
}

void CcbFriendUnitLayer::onPressControlButtonInvite(CCObject* pSender, CCControlEvent event)
{
	// TODO:
}

void CcbFriendUnitLayer::onPressControlButtonMail(CCObject* pSender, CCControlEvent event)
{
    pressControlButton(FriendUnitDataMgr::kFriendMailType);
    FriendUnitDataMgr::Get()->setMiddleNode(FriendUnitDataMgr::kFriendMailType, m_pSizeMiddle, m_pPointMiddle, m_pLayerDown);
}







