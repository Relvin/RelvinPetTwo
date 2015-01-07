#include "CcbAccountLayer.h"
#include "CcbManager.h"
#include "Defines.h"
#include "StartGameLayer.h"
#include "md5.h"
#include "Instruments.h"
#include "Defines.h"
#include "PetLoadingLayer.h"
#include "SystemMessage.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"

const static int kAccountTouchPriority = kCCMenuHandlerPriority-1;
//const static float fAnimationTime = 0.5f;

CcbAccountLayer* CcbAccountLayer::m_shared = NULL;

CcbAccountLayer::~CcbAccountLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
	CC_SAFE_RELEASE_NULL(m_pControlButtonReg);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteAccount);
    CC_SAFE_RELEASE_NULL(m_pScale9SpritePassword);
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    CC_SAFE_RELEASE_NULL(m_pLayerParent);
    m_shared = NULL;
}


bool CcbAccountLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    winSize = CCDirector::sharedDirector()->getWinSize();
    m_shared = this;
	return true;
}

CcbAccountLayer* CcbAccountLayer::GetCurLayer()
{
    return m_shared;
}

void CcbAccountLayer::onEnter()
{
	CCLayer::onEnter();
    
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
    
    std::string strAccount(d9_decode_get(D9_ACCOUNT));
    std::string strPassword(CCUserDefault::sharedUserDefault()->getStringForKey(D9_PASSWORD));
    
    
    if (!strAccount.empty()) {
        m_pEditAccount->setText(strAccount.c_str());
    }
    if (!strPassword.empty()) {
        m_pEditPassword->setText(strPassword.c_str());
    }
}

void CcbAccountLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAccountLayer::onExit()
{
	CCLayer::onExit();
}

void CcbAccountLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbAccountLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kAccountTouchPriority, true);
}

bool CcbAccountLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}


// Inhert MemberVariableAssigner
bool CcbAccountLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonReg", CCControlButton*, this->m_pControlButtonReg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteAccount", CCScale9Sprite*, this->m_pScale9SpriteAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpritePassword", CCScale9Sprite*, this->m_pScale9SpritePassword);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
	return false;
}

bool CcbAccountLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAccountLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbAccountLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAccountLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbAccountLayer::onPressControlButtonOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbAccountLayer::onPressControlButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonReg", CcbAccountLayer::onPressControlButtonReg);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAccountLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{

    m_strAccount = d9_decode_get(D9_ACCOUNT);
    
    CCSize accountSize, passwordSize;
    CCPoint accountPos, passwordPos;
    accountSize = m_pScale9SpriteAccount->getContentSize();
    accountPos = m_pScale9SpriteAccount->getPosition();
    passwordSize = m_pScale9SpritePassword->getContentSize();
    passwordPos = m_pScale9SpritePassword->getPosition();
    
    m_pScale9SpriteAccount->removeFromParent();
    m_pScale9SpritePassword->removeFromParent();
    
    // account
    m_pEditAccount = CCEditBox::create(accountSize, m_pScale9SpriteAccount);
    //m_pEditAccount->setAnchorPoint(CCPointZero);
    m_pEditAccount->setPosition(accountPos);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditAccount->setFontName("Paint Boy");
#else
	m_pEditAccount->setFontName("fonts/Paint Boy.ttf");
#endif
    m_pEditAccount->setFontSize(14.0f);
    m_pEditAccount->setFontColor(ccRED);
    m_pEditAccount->setPlaceHolder("Name:");
    //m_pEditAccount->setPlaceholderFontColor(ccWHITE);
    m_pEditAccount->setMaxLength(Max_Account);
    m_pEditAccount->setReturnType(kKeyboardReturnTypeDone);
    m_pEditAccount->setDelegate(this);
    m_pEditAccount->setTouchPriority(kAccountTouchPriority-1);
    m_pLayerParent->addChild(m_pEditAccount);
    
    // password
    m_pEditPassword = CCEditBox::create(passwordSize, m_pScale9SpritePassword);
    //m_pEditPassword->setAnchorPoint(CCPointZero);
    m_pEditPassword->setPosition(passwordPos);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	m_pEditPassword->setFont("Paint Boy", 14);
#else
	m_pEditPassword->setFont("fonts/Paint Boy.ttf", 14);
#endif
    m_pEditPassword->setFontColor(ccGREEN);
    m_pEditPassword->setPlaceHolder("Password:");
    m_pEditPassword->setMaxLength(Max_Password);
    m_pEditPassword->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPassword->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPassword->setReturnType(kKeyboardReturnTypeSend);
    m_pEditPassword->setDelegate(this);
    m_pEditPassword->setTouchPriority(kAccountTouchPriority-1);
    m_pLayerParent->addChild(m_pEditPassword);
    
    m_pControlButtonOk->setTouchPriority(kAccountTouchPriority-1);
    m_pControlButtonCancel->setTouchPriority(kAccountTouchPriority-1);
    m_pControlButtonReg->setTouchPriority(kAccountTouchPriority-1);
    //增加描边}
//    m_pControlButtonOk->setStrokeForTitle(ccBLACK, 1);
//    m_pControlButtonCancel->setStrokeForTitle(ccBLACK, 1);
//    m_pControlButtonReg->setStrokeForTitle(ccBLACK, 1);
}



void CcbAccountLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    m_strAccount = m_pEditAccount->getText();
    m_strPassword = m_pEditPassword->getText();
    
    if (m_strAccount.empty() || m_strAccount == "") {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_plz_input_np));
        return;
    }
    if (!checkAccountOk(m_strAccount)) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_reg_error_format));
        return;
    }
    if (m_strPassword.length() != 32 && !checkPasswordOk(m_strPassword)) {
        SystemMessage::showSystemMessage(0, NULL, GET_STR(Str_pwd_error));
        return;
    }
    
    std::string strMd5;
    if (m_strPassword.length() != 32) {
        m_strPassword += m_strAccount;
        strMd5 = MD5(m_strPassword).toString();
    } else {
        strMd5 = m_strPassword;
    }
    
    if (StartGameLayer::GetCurLayer()) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        StartGameLayer::GetCurLayer()->onStartLogin(m_strAccount, strMd5);
    }
}

void CcbAccountLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
//    mAnimationManager->runAnimationsForSequenceNamed("move_out");
//
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbAccountLayer::onCancel));
    onCancel();
}

void CcbAccountLayer::onPressControlButtonReg(CCObject* pSender, CCControlEvent event)
{
//    mAnimationManager->runAnimationsForSequenceNamed("move_out");
//
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbAccountLayer::onRegist));
    onRegist();
}

#pragma mark Private Method
void CcbAccountLayer::onCancel()
{
    removeFromParentAndCleanup(true);
    PetLoadingLayer::sharedLayer()->End();
}

void CcbAccountLayer::onRegist()
{
    removeFromParentAndCleanup(true);
    if (StartGameLayer::GetCurLayer()) {
        CCNode* pNode = CcbManager::sharedManager()->LoadCcbRegistLayer( );
        StartGameLayer::GetCurLayer()->addChild(pNode, 101, StartGameLayer::E_REGIST_TAG);
    }
}

#pragma mark EditBox
void CcbAccountLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
//    CCLog("editBox %p DidBegin !", editBox);
    if (editBox == m_pEditAccount) {
        m_pEditAccount->runAction(CCMoveBy::create(0.1f, ccp(0, 1)));
    } else if (editBox == m_pEditPassword) {
        m_pEditPassword->runAction(CCMoveBy::create(0.1f, ccp(0, 1)));
    }
}

void CcbAccountLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
//    CCLog("editBox %p DidEnd !", editBox);
    if (editBox == m_pEditAccount) {
        m_pEditAccount->runAction(CCMoveBy::create(0.1f, ccp(0, -1)));
    } else if (editBox == m_pEditPassword) {
        m_pEditPassword->runAction(CCMoveBy::create(0.1f, ccp(0, -1)));
    }
}

void CcbAccountLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    if (editBox == m_pEditAccount) {
        m_pEditPassword->setText("");
    }
//    CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void CcbAccountLayer::editBoxReturn(CCEditBox* editBox)
{
//    CCLog("editBox %p was returned !", editBox);
//    if (editBox == m_pEditPassword) {
//        onPressControlButtonOk(NULL, NULL);
//    }
}

#pragma mark IMEDelegate

//static CCRect getRect(CCNode * pNode)
//{
//	CCSize contentSize = pNode->getContentSize();
//	CCRect rect = CCRectMake(0, 0, contentSize.width, contentSize.height);
//	return CCRectApplyAffineTransform(rect, pNode->nodeToWorldTransform());
//}
//
//void CcbAccountLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
//{
//    CCRect rectTracked = getRect(this);
//    
//}

#pragma mark Public Method
void CcbAccountLayer::HideAccountLayer()
{
    PetLoadingLayer::sharedLayer()->End();
//    mAnimationManager->runAnimationsForSequenceNamed("move_out");
//    
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbAccountLayer::onCancel));
    onCancel();
}






