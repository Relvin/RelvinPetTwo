#include "CcbFriendGetAllEnergyLayer.h"
//#include "CcbManager.h"
#include "FriendUnitDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendGetAllEnergyLayer::~CcbFriendGetAllEnergyLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLeftCnt);
	CC_SAFE_RELEASE_NULL(m_pControlButtonGetAll);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendGetAllEnergyLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendGetAllEnergyLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendGetAllEnergyLayer", CcbFriendGetAllEnergyLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_send_energy.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendGetAllEnergyLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFriendGetAllEnergyLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendGetAllEnergyLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendGetAllEnergyLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendGetAllEnergyLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendGetAllEnergyLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLeftCnt", CCLabelTTF*, this->m_pLabelTTFLeftCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGetAll", CCControlButton*, this->m_pControlButtonGetAll);

	return false;
}

bool CcbFriendGetAllEnergyLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendGetAllEnergyLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendGetAllEnergyLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendGetAllEnergyLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGetAll", CcbFriendGetAllEnergyLayer::onPressControlButtonGetAll);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendGetAllEnergyLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFWord->noStroke();
    m_pLabelTTFLeftCnt->noStroke();
    
    leftEnergyCntUpdate();
}

void CcbFriendGetAllEnergyLayer::onPressControlButtonGetAll(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CGameSession::SendGetFriendEnergy(true, 0);
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
}

void CcbFriendGetAllEnergyLayer::leftEnergyCntUpdate() {
    CCString* pString = CCString::createWithFormat("%d", FriendUnitDataMgr::Get()->leftEnergyCnt());
    m_pLabelTTFLeftCnt->setString(pString->getCString());
}





