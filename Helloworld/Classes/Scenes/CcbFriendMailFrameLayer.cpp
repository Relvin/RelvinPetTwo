#include "CcbFriendMailFrameLayer.h"
//#include "CcbManager.h"
#include "CcbPetIcon.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendMailFrameLayer::~CcbFriendMailFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerHead);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAccept);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRefuse);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFightPower);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendMailFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendMailFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendMailFrameLayer", CcbFriendMailFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendMailFrameLayer.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendMailFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFriendMailFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendMailFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendMailFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendMailFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendMailFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CcbPetIcon*, this->m_pLayerHead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAccept", CCControlButton*, this->m_pControlButtonAccept);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRefuse", CCControlButton*, this->m_pControlButtonRefuse);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFightPower", CCLabelTTF*, this->m_pLabelTTFFightPower);

	return false;
}

bool CcbFriendMailFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendMailFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendMailFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendMailFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAccept", CcbFriendMailFrameLayer::onPressControlButtonAccept);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRefuse", CcbFriendMailFrameLayer::onPressControlButtonRefuse);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendMailFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFFightPower->noStroke();
    m_pLabelTTFLv->noStroke();
    m_pLabelTTFName->noStroke();
    m_pLabelTTFTitle->noStroke();
    m_pLabelTTFWord->noStroke();
}



void CcbFriendMailFrameLayer::onPressControlButtonAccept(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    if (m_nFrameType == FriendUnitDataMgr::kMailTypeApply) {
        // 同意好友申请
        CGameSession::SendAgreeFriendApply(m_dwTargetId);
    } else if (m_nFrameType == FriendUnitDataMgr::kMailTypeMsg) {
        // 读取邮件
        FriendUnitDataMgr::Get()->openMailWithNameAndTitle(m_pLabelTTFName->getString(), m_pLabelTTFTitle->getString());
        CGameSession::SendReadMailInfo(m_dwTargetId);
    }
}

void CcbFriendMailFrameLayer::onPressControlButtonRefuse(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_nFrameType == FriendUnitDataMgr::kMailTypeApply) {
        // 拒绝好友申请
        CGameSession::SendDisagreeFriendApply(m_dwTargetId);
        FriendUnitDataMgr::Get()->delTargetIdInType(m_dwTargetId, FriendUnitDataMgr::kFriendMailType);
    } else if (m_nFrameType == FriendUnitDataMgr::kMailTypeMsg) {
        // 删除邮件
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        CGameSession::SendDelMail(m_dwTargetId);
    }
}


void CcbFriendMailFrameLayer::setFrameData(const FriendUnitDataMgr::STC_FRIEND_MAIL &_info) {
    m_pLayerHead->setPetId(_info.wLeaderPetId);
    m_nFrameType = _info.byType;
    m_dwTargetId = _info.dwIndex;
    
    CCString* pString = NULL;
    if (m_nFrameType == FriendUnitDataMgr::kMailTypeMsg) {
        pString = CCString::createWithFormat("%s", "读取");
        m_pControlButtonAccept->setTitleForState(pString, CCControlStateNormal);
        pString = CCString::createWithFormat("%s", "删除");
        m_pControlButtonRefuse->setTitleForState(pString, CCControlStateNormal);
        m_pLabelTTFTitle->setString(_info.strTitle.c_str());
    } else if (m_nFrameType == FriendUnitDataMgr::kMailTypeApply) {
        pString = CCString::createWithFormat("%s", "接受");
        m_pControlButtonAccept->setTitleForState(pString, CCControlStateNormal);
        pString = CCString::createWithFormat("%s", "拒绝");
        m_pControlButtonRefuse->setTitleForState(pString, CCControlStateNormal);
        m_pLabelTTFTitle->setString("好友申请");
    }
    
    pString = CCString::createWithFormat("%d", _info.dwFightPower);
    m_pLabelTTFFightPower->setString(pString->getCString());
    
    pString = CCString::createWithFormat("%s%d", SB_Lv, _info.wRoleLv);
    m_pLabelTTFLv->setString(pString->getCString());
    m_pLabelTTFName->setString(_info.strSendName.c_str());
    
}




