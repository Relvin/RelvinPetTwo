#include "CcbAccountBindingLayer.h"
#include "CcbManager.h"
#include "MailDataMgr.h"
#include "deelx.h"
#include "GameSession.h"
#include "LoginSystem.h"
#include "md5.h"
#include "Instruments.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"

CcbAccountBindingLayer::~CcbAccountBindingLayer()
{
	//CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFErrorDesc);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteAccount);
	CC_SAFE_RELEASE_NULL(m_pScale9SpritePassword);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteMail);
	CC_SAFE_RELEASE_NULL(m_pLayerParent1);
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteMail2);
	CC_SAFE_RELEASE_NULL(m_pLayerParent2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFMail);
	CC_SAFE_RELEASE_NULL(m_pLayerParent3);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBinding);
    CC_SAFE_RELEASE_NULL(m_pEditBoxAccount);
    CC_SAFE_RELEASE_NULL(m_pEditBoxPassword);
    CC_SAFE_RELEASE_NULL(m_pEditBoxMail);
    CC_SAFE_RELEASE_NULL(m_pEditBoxMail2);
}


bool CcbAccountBindingLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbAccountBindingLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    CGameSession::Attach(this);
    CMailDataMgr::Get()->SetBindingLayerPt(this);
}

void CcbAccountBindingLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbAccountBindingLayer::onExit()
{
	CCLayer::onExit();
    CGameSession::Detach(this);
    CMailDataMgr::Get()->SetBindingLayerPt(NULL);
}

void CcbAccountBindingLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbAccountBindingLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFErrorDesc", CCLabelTTF*, this->m_pLabelTTFErrorDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteAccount", CCScale9Sprite*, this->m_pScale9SpriteAccount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpritePassword", CCScale9Sprite*, this->m_pScale9SpritePassword);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteMail", CCScale9Sprite*, this->m_pScale9SpriteMail);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent1", CCLayer*, this->m_pLayerParent1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteMail2", CCScale9Sprite*, this->m_pScale9SpriteMail2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent2", CCLayer*, this->m_pLayerParent2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFMail", CCLabelTTF*, this->m_pLabelTTFMail);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent3", CCLayer*, this->m_pLayerParent3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBinding", CCControlButton*, this->m_pControlButtonBinding);

	return false;
}

bool CcbAccountBindingLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbAccountBindingLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbAccountBindingLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbAccountBindingLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbAccountBindingLayer::onPressControlButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBinding", CcbAccountBindingLayer::onPressControlButtonBinding);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbAccountBindingLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_EditBoxAccountPos = m_pScale9SpriteAccount->getPosition();
    m_EditBoxPasswordPos = m_pScale9SpritePassword->getPosition();
    m_EditBoxMail = m_pScale9SpriteMail->getPosition();
    m_EditBoxMail2 = m_pScale9SpriteMail2->getPosition();
    
    
    m_pControlButtonBinding->setTouchPriority(-999);
    //m_pControlButtonClose->setTouchPriority(-999);
    
    m_pLabelTTFErrorDesc->setString("");
    
    if (CMailDataMgr::Get()->GetAccountBindingState())
    {
        m_pLayerParent1->setVisible(false);
        m_pLayerParent2->setVisible(false);
        m_pLayerParent3->setVisible(true);
        
        m_pControlButtonBinding->setVisible(false);
        m_pLabelTTFMail->setString(CMailDataMgr::Get()->GetBindingMail().c_str());
    }
    else
    {
        if (LoginSystem::Get()->getAuthFlag() == LoginSystem::E_AUTH_FAST)
        {
            CreateEditeWithAccountPassword();
        }
        else if (LoginSystem::Get()->getMode() == LoginSystem::E_AUTH_ACCOUNT)
        {
            CreateEditeWithOnlyMail();
        }        
    }
}


//void CcbAccountBindingLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
//{
//	// TODO:
//    CMailDataMgr::Get()->GetMainLayerPt()->addChild(CcbManager::sharedManager()->LoadCcbSettingsLayer(this), 99, 1);
//    removeFromParent();
//}

void CcbAccountBindingLayer::onPressControlButtonBinding(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if (CheckAccountPasswordMail())
    {
        string strAccount = m_pEditBoxAccount->getText();
        string strPassword = m_pEditBoxPassword->getText();
        strPassword += strAccount;
        std::string strMd5 = MD5(strPassword).toString();
        
//        CCUserDefault::sharedUserDefault()->setStringForKey(D9_ACCOUNT, strAccount);
        d9_encode_save(D9_ACCOUNT, strAccount);
        CCUserDefault::sharedUserDefault()->setStringForKey(D9_PASSWORD, strMd5);
        CGameSession::SendBindingAccount(m_pEditBoxMail->getText(), strAccount, strMd5);
        return;
    }
    else if (CheckMail2())
    {
        CGameSession::SendBindingAccount(m_pEditBoxMail2->getText(), "", "");
    }
}

void CcbAccountBindingLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox * editbox)
{
    //
}

void CcbAccountBindingLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox * editbox)
{
    //
}

void CcbAccountBindingLayer::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    //
}

void CcbAccountBindingLayer::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
    
}

void CcbAccountBindingLayer::RefeashLayer()
{
    //m_pLabelTTFErrorDesc->setString("");
    
    if (CMailDataMgr::Get()->GetAccountBindingState())
    {
        m_pLayerParent1->setVisible(false);
        m_pLayerParent2->setVisible(false);
        m_pLayerParent3->setVisible(true);
        
        m_pControlButtonBinding->setVisible(false);
        m_pLabelTTFMail->setString(CMailDataMgr::Get()->GetBindingMail().c_str());
    }
    else
    {
        if (LoginSystem::Get()->getAuthFlag() == LoginSystem::E_AUTH_FAST)
        {
            CreateEditeWithAccountPassword();
        }
        else if (LoginSystem::Get()->getMode() == LoginSystem::E_AUTH_ACCOUNT)
        {
            CreateEditeWithOnlyMail();
        }
    }
}

void CcbAccountBindingLayer::CreateEditeWithAccountPassword()
{
    m_pLayerParent1->setVisible(true);
    m_pLayerParent2->setVisible(false);
    m_pLayerParent3->setVisible(false);
    //账号}
    CCSize EditBoxSize = m_pScale9SpriteAccount->getContentSize();
    m_pScale9SpriteAccount->removeFromParent();
    
    m_pEditBoxAccount = CCEditBox::create(EditBoxSize, m_pScale9SpriteAccount);

    m_pEditBoxAccount->setInputMode(kEditBoxInputModeAny);
    m_pEditBoxAccount->setInputFlag(kEditBoxInputFlagSensitive);
    m_pEditBoxAccount->setPosition(m_EditBoxAccountPos);
    m_pEditBoxAccount->setMaxLength(Max_Account);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditBoxAccount->setFontName("Paint Boy");
#else
	m_pEditBoxAccount->setFontName("fonts/Paint Boy.ttf");
#endif
    
    m_pEditBoxAccount->setFontSize(14);
    m_pEditBoxAccount->setPlaceHolder("USER ACCOUNT");
    m_pEditBoxAccount->setText("");
    
    m_pEditBoxAccount->retain();
    m_pLayerParent1->addChild(m_pEditBoxAccount);
    m_pEditBoxAccount->setDelegate(this);
    
    //密码}
    EditBoxSize = m_pScale9SpritePassword->getContentSize();
    m_pScale9SpritePassword->removeFromParent();
    
    m_pEditBoxPassword = CCEditBox::create(EditBoxSize, m_pScale9SpritePassword);
    m_pEditBoxPassword->setInputMode(kEditBoxInputModeSingleLine);
    m_pEditBoxPassword->setPosition(m_EditBoxPasswordPos);
    m_pEditBoxPassword->setMaxLength(Max_Password);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditBoxPassword->setFontName("Paint Boy");
#else
	m_pEditBoxPassword->setFontName("fonts/Paint Boy.ttf");
#endif
    
    m_pEditBoxPassword->setFontSize(14);
    m_pEditBoxPassword->setPlaceHolder("PASSWORD");

    m_pEditBoxPassword->setText("");
    
    m_pEditBoxPassword->retain();
    m_pLayerParent1->addChild(m_pEditBoxPassword);
    m_pEditBoxPassword->setDelegate(this);
    
    //邮箱}
    EditBoxSize = m_pScale9SpriteMail->getContentSize();
    m_pScale9SpriteMail->removeFromParent();
    
    m_pEditBoxMail = CCEditBox::create(EditBoxSize, m_pScale9SpriteMail);
    m_pEditBoxMail->setInputMode(kEditBoxInputModeEmailAddr);
    m_pEditBoxMail->setPosition(m_EditBoxMail);
    m_pEditBoxMail->setMaxLength(Max_Mail);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditBoxMail->setFontName("Paint Boy");
#else
	m_pEditBoxMail->setFontName("fonts/Paint Boy.ttf");
#endif
    
    m_pEditBoxMail->setFontSize(14);
    m_pEditBoxMail->setPlaceHolder("USER@MAIL.COM");
    m_pEditBoxMail->setText("");
    
    m_pEditBoxMail->retain();
    m_pLayerParent1->addChild(m_pEditBoxMail);
    m_pEditBoxMail->setDelegate(this);
    
    m_pEditBoxAccount->setTouchPriority(-99);
    m_pEditBoxPassword->setTouchPriority(-99);
    m_pEditBoxMail->setTouchPriority(-99);
}

void CcbAccountBindingLayer::CreateEditeWithOnlyMail()
{
    m_pLayerParent1->setVisible(false);
    m_pLayerParent2->setVisible(true);
    m_pLayerParent3->setVisible(false);
    
    CCSize EditBoxSize = m_pScale9SpriteMail2->getContentSize();
    m_pScale9SpriteMail2->removeFromParent();
    
    m_pEditBoxMail2 = CCEditBox::create(EditBoxSize, m_pScale9SpriteMail2);
    m_pEditBoxMail2->setInputMode(kEditBoxInputModeEmailAddr);
    m_pEditBoxMail2->setPosition(m_EditBoxMail2);
    m_pEditBoxMail2->setMaxLength(Max_Mail);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pEditBoxMail2->setFontName("Paint Boy");
#else
	m_pEditBoxMail2->setFontName("fonts/Paint Boy.ttf");
#endif
    
    m_pEditBoxMail2->setFontSize(14);
    m_pEditBoxMail2->setPlaceHolder("USER@MAIL.COM");
    m_pEditBoxMail2->setText("");
    
    m_pEditBoxMail2->retain();
    m_pLayerParent2->addChild(m_pEditBoxMail2);
    m_pEditBoxMail2->setDelegate(this);
    
    m_pEditBoxMail2->setTouchPriority(-99);
}

bool CcbAccountBindingLayer::CheckAccountPasswordMail()
{
    if (!m_pEditBoxAccount || !m_pEditBoxPassword || !m_pEditBoxMail)
    {
        return false;
    }
    
//    char szAccount[64] = "";
//    char szPassword[64] = "";
//    char szMail[128] = "";
    
//    strncpy(szAccount, m_pEditBoxAccount->getText(), 16);
    std::string strAccount = m_pEditBoxAccount->getText();
//    strncpy(szPassword, m_pEditBoxPassword->getText(), 16);
    std::string strPassword = m_pEditBoxPassword->getText();
//    strncpy(szMail, m_pEditBoxMail->getText(), 64);
    std::string strMail = m_pEditBoxMail->getText();
    
    if (strAccount.length() == 0)
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_plz_input_np));
        return false;
    }
    else if (strPassword.length() == 0)
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_plz_input_np));
        return false;
    }
    else if (strMail.length() == 0)
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_reg_mail_error));
        return false;
    }
    
    //匹配账号}

    if (!checkAccountOk(strAccount))
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_account_error));
        return false;
    }
    
    //匹配密码}

    if (!checkPasswordOk(strPassword))
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_pwd_error));
        return false;
    }
    
    //匹配邮箱格式}
    if (!checkMailOk(strMail))
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_reg_mail_error));
        return false;
    }
    
    m_pLabelTTFErrorDesc->setString("");//消除错误提示}
    return true;
}

bool CcbAccountBindingLayer::CheckMail2()
{
    if (!m_pEditBoxMail2)
    {
        return false;
    }
    std::string strMail2 = m_pEditBoxMail2->getText();
    //匹配邮箱格式}
    if (!checkMailOk(strMail2))
    {
        m_pLabelTTFErrorDesc->setString(GET_STR(Str_reg_mail_error));
        return false;
    }
    
    return true;
}

void CcbAccountBindingLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    CGameSession::BackToLogin();
}

