#include "CcbFriendFindFrameLayer.h"
//#include "CcbManager.h"
#include "CcbPetIcon.h"
#include "Defines.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendFindFrameLayer::~CcbFriendFindFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerHead);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAddFriend);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFightPower);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendFindFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendFindFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendFindFrameLayer", CcbFriendFindFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendFindFrameLayer.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendFindFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFriendFindFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendFindFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendFindFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendFindFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendFindFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CcbPetIcon*, this->m_pLayerHead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAddFriend", CCControlButton*, this->m_pControlButtonAddFriend);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFightPower", CCLabelTTF*, this->m_pLabelTTFFightPower);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);

	return false;
}

bool CcbFriendFindFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendFindFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendFindFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendFindFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAddFriend", CcbFriendFindFrameLayer::onPressControlButtonAddFriend);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendFindFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFName->noStroke();
    m_pLabelTTFLv->noStroke();
    m_pLabelTTFFightPower->noStroke();
    m_pLabelTTFWord->noStroke();
}

void CcbFriendFindFrameLayer::onPressControlButtonAddFriend(CCObject* pSender, CCControlEvent event)
{
    if (m_dwTargetId == 0) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendReqApplyFriend(m_dwTargetId);
}

void CcbFriendFindFrameLayer::setFrameData(const FriendUnitDataMgr::STC_LIST_INFO &_info) {
    m_pLayerHead->setPetId(_info.wLeaderId);
    CCString* pString;
    pString = CCString::createWithFormat("%d", _info.dwFightPower);
    m_pLabelTTFFightPower->setString(pString->getCString());
    
    pString = CCString::createWithFormat("%s%d", SB_Lv, _info.wRoleLv);
    m_pLabelTTFLv->setString(pString->getCString());
    m_pLabelTTFName->setString(_info.strName.c_str());
    m_dwTargetId = _info.dwRoleId;
}





