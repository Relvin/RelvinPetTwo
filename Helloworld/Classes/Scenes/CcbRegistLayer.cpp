#include "CcbRegistLayer.h"
//#include "CcbManager.h"
#include "Defines.h"
#include "md5.h"
#include "Instruments.h"
#include "StartGameLayer.h"
#include "SystemMessage.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "FlyTextLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

const static int kRegistTouchPriority = kCCMenuHandlerPriority-2;

CcbRegistLayer::~CcbRegistLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
	CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteAccount);
    CC_SAFE_RELEASE_NULL(m_pScale9SpritePassword);
    //CC_SAFE_RELEASE_NULL(m_pScale9SpriteCPassword);
    //CC_SAFE_RELEASE_NULL(m_pScale9SpriteMail);
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    CC_SAFE_RELEASE_NULL(m_pLayerParent);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbRegistLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbRegistLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbRegistLayer", CcbRegistLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/regist.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbRegistLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbRegistLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CC_SAFE_RELEASE_NULL(mAnimationManager);
    mAnimationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    CC_SAFE_RETAIN(mAnimationManager);
}

void CcbRegistLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbRegistLayer::onExit()
{
	CCLayer::onExit();
}

void CcbRegistLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbRegistLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kRegistTouchPriority, true);
}

bool CcbRegistLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

// Inhert MemberVariableAssigner
bool CcbRegistLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonCancel", CCControlButton*, this->m_pControlButtonCancel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteAccount", CCScale9Sprite*, this->m_pScale9SpriteAccount);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpritePassword", CCScale9Sprite*, this->m_pScale9SpritePassword);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteCPassword", CCScale9Sprite*, this->m_pScale9SpriteCPassword);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteMail", CCScale9Sprite*, this->m_pScale9SpriteMail);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent", CCLayer*, this->m_pLayerParent);
	return false;
}

bool CcbRegistLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbRegistLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbRegistLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbRegistLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbRegistLayer::onPressControlButtonOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonCancel", CcbRegistLayer::onPressControlButtonCancel);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbRegistLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    
    CCSize acntSize, pwdSize, cpwdSize, mailSize;
    CCPoint acntPos, pwdPos, cpwdPos, mailPos;
    acntSize = m_pScale9SpriteAccount->getContentSize();
    acntPos = m_pScale9SpriteAccount->getPosition();
    pwdSize = m_pScale9SpritePassword->getContentSize();
    pwdPos = m_pScale9SpritePassword->getPosition();
    //cpwdSize = m_pScale9SpriteCPassword->getContentSize();
    //cpwdPos = m_pScale9SpriteCPassword->getPosition();
    //mailSize = m_pScale9SpriteMail->getContentSize();
    //mailPos = m_pScale9SpriteMail->getPosition();
    
    m_pScale9SpriteAccount->removeFromParent();
    m_pScale9SpritePassword->removeFromParent();
    //m_pScale9SpriteCPassword->removeFromParent();
    //m_pScale9SpriteMail->removeFromParent();
    
    // acount
    m_pEditAccount = CCEditBox::create(acntSize, m_pScale9SpriteAccount);
    //m_pEditAccount->setAnchorPoint(CCPointZero);
    m_pEditAccount->setPosition(acntPos);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditAccount->setFont("Paint Boy", 14);
#else
	m_pEditAccount->setFont("fonts/Paint Boy.ttf", 14);
#endif
    m_pEditAccount->setFontColor(ccRED);
    m_pEditAccount->setPlaceHolder("Account Here");
    //m_pEditAccount->setPlaceholderFontColor(ccWHITE);
    m_pEditAccount->setMaxLength(Max_Account);
    m_pEditAccount->setReturnType(kKeyboardReturnTypeDone);
    m_pEditAccount->setDelegate(this);
    m_pEditAccount->setTouchPriority(kRegistTouchPriority - 1);
    m_pLayerParent->addChild(m_pEditAccount);
    
    // password
    m_pEditPwd = CCEditBox::create(pwdSize, m_pScale9SpritePassword);
    //m_pEditPwd->setAnchorPoint(CCPointZero);
    m_pEditPwd->setPosition(pwdPos);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditPwd->setFont("Paint Boy", 14);
#else
	m_pEditPwd->setFont("fonts/Paint Boy.ttf", 14);
#endif
    m_pEditPwd->setFontColor(ccGREEN);
    m_pEditPwd->setPlaceHolder("Password Here");
    m_pEditPwd->setMaxLength(Max_Password);
    //m_pEditPwd->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditPwd->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditPwd->setReturnType(kKeyboardReturnTypeDone);
    m_pEditPwd->setDelegate(this);
    m_pEditPwd->setTouchPriority(kRegistTouchPriority-1);
    m_pLayerParent->addChild(m_pEditPwd);
    
    // confirm password
    
    m_pControlButtonOk->setTouchPriority(kRegistTouchPriority-1);
    m_pControlButtonCancel->setTouchPriority(kRegistTouchPriority-1);
}

void CcbRegistLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    m_strAccount = m_pEditAccount->getText();
    m_strPassword = m_pEditPwd->getText();
    //m_strCPassword = m_pEditCPwd->getText();
    //m_strMail = m_pEditMail->getText();
    
    if (m_strAccount.empty() || m_strPassword.empty() || m_strAccount == "" /*|| m_strCPassword == ""*/) {
        FlyTextLayer::showTips(GET_STR(Str_plz_input_np));
        return;
    }
    if (!checkAccountOk(m_strAccount) || !checkPasswordOk(m_strPassword)) {
        FlyTextLayer::showTips(GET_STR(Str_reg_error_format));
        return;
    }

    if (StartGameLayer::GetCurLayer()) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        m_strPassword += m_strAccount;
        std::string strMd5 = MD5(m_strPassword).toString();
        StartGameLayer::GetCurLayer()->sendRegInfo(m_strAccount, strMd5, "");
    }
}

void CcbRegistLayer::onPressControlButtonCancel(CCObject* pSender, CCControlEvent event)
{
//    mAnimationManager->runAnimationsForSequenceNamed("move_out");
//    mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CcbRegistLayer::onCancel));
    onCancel();
}

#pragma mark Private
void CcbRegistLayer::onCancel()
{
    removeFromParentAndCleanup(true);
    PetLoadingLayer::sharedLayer()->End();
}


#pragma mark EditBox
void CcbRegistLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    if (editBox == m_pEditAccount) {
        m_pEditAccount->runAction(CCMoveBy::create(0.1f, ccp(0, 1)));
    } else if (editBox == m_pEditPwd) {
        m_pEditPwd->runAction(CCMoveBy::create(0.1f, ccp(0, 1)));
    }
}

void CcbRegistLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    if (editBox == m_pEditAccount) {
        m_pEditAccount->runAction(CCMoveBy::create(0.1f, ccp(0, -1)));
    } else if (editBox == m_pEditPwd) {
        m_pEditPwd->runAction(CCMoveBy::create(0.1f, ccp(0, -1)));
    }
}

void CcbRegistLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
}

void CcbRegistLayer::editBoxReturn(CCEditBox* editBox)
{
}




