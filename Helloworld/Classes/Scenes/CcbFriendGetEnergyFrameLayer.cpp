#include "CcbFriendGetEnergyFrameLayer.h"
//#include "CcbManager.h"
#include "CcbPetIcon.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendGetEnergyFrameLayer::~CcbFriendGetEnergyFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerHead);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGetEnergy);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFightPower);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendGetEnergyFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendGetEnergyFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendGetEnergyFrameLayer", CcbFriendGetEnergyFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendGetEnergyFrame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendGetEnergyFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFriendGetEnergyFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendGetEnergyFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendGetEnergyFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendGetEnergyFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendGetEnergyFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerHead", CcbPetIcon*, this->m_pLayerHead);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGetEnergy", CCControlButton*, this->m_pControlButtonGetEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFightPower", CCLabelTTF*, this->m_pLabelTTFFightPower);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);

	return false;
}

bool CcbFriendGetEnergyFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendGetEnergyFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendGetEnergyFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendGetEnergyFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGetEnergy", CcbFriendGetEnergyFrameLayer::onPressControlButtonGetEnergy);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendGetEnergyFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFLv->noStroke();
    m_pLabelTTFFightPower->noStroke();
    m_pLabelTTFName->noStroke();
    m_pLabelTTFWord->noStroke();
}

void CcbFriendGetEnergyFrameLayer::onPressControlButtonGetEnergy(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CGameSession::SendGetFriendEnergy(false, m_dwTargetId);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
}

void CcbFriendGetEnergyFrameLayer::setFrameData(const FriendUnitDataMgr::STC_LIST_INFO &_info) {
    m_dwTargetId = _info.dwRoleId;
    
    m_pLayerHead->setPetId(_info.wLeaderId);
    CCString* pString;
    pString = CCString::createWithFormat("%d", _info.dwFightPower);
    m_pLabelTTFFightPower->setString(pString->getCString());
    
    pString = CCString::createWithFormat("%s%d", SB_Lv, _info.wRoleLv);
    m_pLabelTTFLv->setString(pString->getCString());
    m_pLabelTTFName->setString(_info.strName.c_str());
}





