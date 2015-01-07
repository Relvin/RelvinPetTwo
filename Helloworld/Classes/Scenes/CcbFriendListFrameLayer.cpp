#include "CcbFriendListFrameLayer.h"
#include "CcbManager.h"
#include "CcbPetIcon.h"
#include "Defines.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "CcbFriendSocialBoardLayer.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbFriendListFrameLayer::~CcbFriendListFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSocial);
	CC_SAFE_RELEASE_NULL(m_pControlButtonSendEnergy);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFFightPower);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFWord);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbFriendListFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbFriendListFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbFriendListFrameLayer", CcbFriendListFrameLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/pet_icon.ccb]", [ccb/pet_icon.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendListFrameLayer.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbFriendListFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbFriendListFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbFriendListFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbFriendListFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbFriendListFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbFriendListFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbPetIcon*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSocial", CCControlButton*, this->m_pControlButtonSocial);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSendEnergy", CCControlButton*, this->m_pControlButtonSendEnergy);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFFightPower", CCLabelTTF*, this->m_pLabelTTFFightPower);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFWord", CCLabelTTF*, this->m_pLabelTTFWord);
	return false;
}

bool CcbFriendListFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbFriendListFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbFriendListFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbFriendListFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSocial", CcbFriendListFrameLayer::onPressControlButtonSocial);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSendEnergy", CcbFriendListFrameLayer::onPressControlButtonSendEnergy);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbFriendListFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pLabelTTFName->noStroke();
    m_pLabelTTFFightPower->noStroke();
    m_pLabelTTFWord->noStroke();
    m_pLabelTTFLv->noStroke();
}



void CcbFriendListFrameLayer::onPressControlButtonSocial(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CcbFriendSocialBoardLayer* pSocialBoard = dynamic_cast<CcbFriendSocialBoardLayer*>(CcbManager::sharedManager()->LoadCcbFriendSocialBoardLayer(this));
    pSocialBoard->setTargetIdAndName(m_dwTargetId, m_strTargetName);
    pSocialBoard->ignoreAnchorPointForPosition(false);
    pSocialBoard->setAnchorPoint(ccp(0.5, 0.5));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pSocialBoard->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    CCDirector::sharedDirector()->getRunningScene()->addChild(pSocialBoard, 10, 5021);
}

void CcbFriendListFrameLayer::onPressControlButtonSendEnergy(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendFriendEnergyGive(m_dwTargetId);
}

void CcbFriendListFrameLayer::setFrameData(const FriendUnitDataMgr::STC_LIST_INFO &_info)
{
    m_dwTargetId = _info.dwRoleId;
    m_strTargetName = _info.strName;
    
    m_pLayerIcon->setPetId(_info.wLeaderId);
    CCString* pString;
    pString = CCString::createWithFormat("%d", _info.dwFightPower);
    m_pLabelTTFFightPower->setString(pString->getCString());
    
    pString = CCString::createWithFormat("%s%d", SB_Lv, _info.wRoleLv);
    m_pLabelTTFLv->setString(pString->getCString());
    m_pLabelTTFName->setString(m_strTargetName.c_str());

    if (_info.byHaveSendEnergy) {
        m_pControlButtonSendEnergy->setEnabled(false);
    } else {
        m_pControlButtonSendEnergy->setEnabled(true);
    }
}





