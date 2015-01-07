#include "CcbMailDetailLayer.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "Instruments.h"
#include "BackCtrl.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "FriendUnitDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMailDetailLayer::~CcbMailDetailLayer()
{
//	CC_SAFE_RELEASE_NULL(m_pSpriteMailIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFTime);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMailContent);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pControlButtonDelete);
    CC_SAFE_RELEASE_NULL(m_pControlButtonReply);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMailDetailLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMailDetailLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMailDetailLayer", CcbMailDetailLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/mail_text.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMailDetailLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    this->setTouchEnabled(true);
	return true;
}

void CcbMailDetailLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbMailDetailLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbMailDetailLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMailDetailLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbMailDetailLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTitle", CCLabelTTF*, this->m_pLabelTTFTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTime", CCLabelTTF*, this->m_pLabelTTFTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMailContent", CCLabelTTF*, this->m_pLabelTTFMailContent);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDelete", CCControlButton*, this->m_pControlButtonDelete);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReply", CCControlButton*, this->m_pControlButtonReply);
	return false;
}

bool CcbMailDetailLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbMailDetailLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMailDetailLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMailDetailLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbMailDetailLayer::onPressControlButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDelete", CcbMailDetailLayer::onPressControlButtonDelete);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReply", CcbMailDetailLayer::onPressControlButtonReply);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMailDetailLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pControlButtonDelete->setTouchPriority(kCCMenuHandlerPriority - 1);
    m_pControlButtonReply->setTouchPriority(kCCMenuHandlerPriority - 1);
    
    m_pLabelTTFName->noStroke();
    m_pLabelTTFTitle->noStroke();
//    m_pLabelTTFMailContent->noStroke();
}

void CcbMailDetailLayer::setMailDetailContent(FriendUnitDataMgr::STC_MAIL_CONTENT &mailContent, std::string strSenderName, std::string strTitle) {
    m_dwMailId = mailContent.dwMailId;
    m_dwSenderId = mailContent.dwSendId;
    m_strSenderName = strSenderName;
    m_strTitle = strTitle;
    m_strSendTime = getFullTimeFromInt(mailContent.dwSendTime);
    
    m_pLabelTTFName->setString(m_strSenderName.c_str());
    m_pLabelTTFTitle->setString(m_strTitle.c_str());
    m_pLabelTTFMailContent->setString(mailContent.strContent.c_str());
    m_pLabelTTFTime->setString(m_strSendTime->getCString());
}

bool CcbMailDetailLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void CcbMailDetailLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void CcbMailDetailLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->removeFromParent();
}

void CcbMailDetailLayer::onPressControlButtonDelete(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    CGameSession::SendDelMail(m_dwMailId);
    this->removeFromParent();
}

void CcbMailDetailLayer::onPressControlButtonReply(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    FriendUnitDataMgr::Get()->setMailTarget(m_dwSenderId, m_strSenderName);
    BackCtrl::InsertNextScene(kFriendMailScene);
}





