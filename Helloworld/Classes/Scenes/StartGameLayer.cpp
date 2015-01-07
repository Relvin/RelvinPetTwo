
#include "StartGameLayer.h"
#include "CcbManager.h"
#include "CCTextFieldAuto.h"
#include "UISupport.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "NetClient.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "ServerListCtrl.h"
#include "GlobalData.h"
#include "CcbServerListLayer.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "LoginSystem.h"
#include "VersionCtrl.h"
#include "Version.h"
#include "GameStateManager.h"
#include "Role.h"
#include "Instruments.h"
#include "Support.h"
#include "EffectLayer.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "ResourceDefine.h"
#include "sound_system_fmod.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "CcbUpdateResourceLayer.h"
#include "AnalysicsManager.h"
#include "Account.h"
#endif


USING_NS_CC;
USING_NS_CC_EXT;

StartGameLayer* StartGameLayer::m_shared = NULL;

StartGameLayer::~StartGameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonFast);
	CC_SAFE_RELEASE_NULL(m_pControlButtonAccount);
	CC_SAFE_RELEASE_NULL(m_pControlButtonThird);
    CC_SAFE_RELEASE_NULL(m_pControlButtonServer);
    CC_SAFE_RELEASE_NULL(m_pControlButtonLogoff);
    CC_SAFE_RELEASE_NULL(m_pSpriteStart);
    
    m_shared = NULL;
    CGameSession::Detach(this);
}

bool StartGameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    m_shared = this;
#ifdef VERSION_D9
    Account::shareInstance()->switchAccount();
#endif
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_nAuthFlag = 0;
    CGameSession::Attach(this);
    
    CMusicCtrl::Init();

    m_strGameServerIp = "";
    m_nGameServerPort = 0;

    LoginSystem::Get()->setConnectStatus( LoginSystem::E_UNCONNECTED );
    
    lblConnectStatus = CCLabelTTF::create("connecting...", T_Font, 12);
    lblServerName = CCLabelTTF::create("", FONT_FZCQJW, 18);
    lblServerName->noStroke();
    lblServerName->setAnchorPoint(ccp(0.5f, 0.5f));
    lblServerName->setColor(ccc3(19, 15, 15));
    lblServerName->setPosition(ccp(winSize.width * 0.5, getCenterY(lblServerName)));
    addChild(lblServerName, 2);
    
    lblAreaId = CCLabelTTF::create("", T_Font, 16);
    lblAreaId->setAnchorPoint(ccp(1, 0.5));
    lblAreaId->setPosition(ccp(getLeft(lblServerName) - 50, getCenterY(lblServerName)));
    addChild(lblAreaId, 2);
    
    // place the connect status label on the bottom of the screen
    lblConnectStatus->setPosition(ccp(winSize.width * 0.5, 20.0));
    addChild(lblConnectStatus, 1);
    

    VersionCtrl vCtr;
    snprintf(strBuf64, BUFFER_SIZE_64, "%s.%s", Support::sharedInstance()->appVersion(), vCtr.versionCode());
    m_pLabelTTFVersion = CCLabelTTF::create(strBuf64, T_Font, 12);
    m_pLabelTTFVersion->setAnchorPoint(ccp(0.5, 0));
    m_pLabelTTFVersion->setColor(ccBLACK);
    m_pLabelTTFVersion->setPosition(ccp(winSize.width*0.5, 5));
    addChild(m_pLabelTTFVersion, 1);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    m_strLoginServerIp = DEBUG_IP;
    m_nLoginServerPort = DEFAULT_PORT;
#else
    
#ifndef NDEBUG
    m_strLoginServerIp = DEBUG_IP;
    m_nLoginServerPort = DEFAULT_PORT;
#elif defined VERSION_I4
    m_strLoginServerIp = I4_IP;
    m_nLoginServerPort = I4_PORT;
#else
    m_strLoginServerIp = RELEASE_IP;
    m_nLoginServerPort = OUTER_PORT;
#endif
    
#endif

    m_ttfLoginServerIp = CCTextFieldTTF::textFieldWithPlaceHolder(m_strLoginServerIp.c_str(), T_Font, 25);
    m_ttfLoginServerIp->setColor(ccGREEN);
    m_ttfLoginServerIp->setAnchorPoint(ccp(0.5, 1.0));
    m_ttfLoginServerIp->setPosition(ccp(winSize.width * 0.5, winSize.height - 35));
    
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", m_nLoginServerPort);
    m_ttfLoginServerPort = CCTextFieldTTF::textFieldWithPlaceHolder(strBuf64, T_Font, 25);
    m_ttfLoginServerPort->setColor(ccGREEN);
    m_ttfLoginServerPort->setAnchorPoint(ccp(0.5, 1.0));
    m_ttfLoginServerPort->setPosition(ccp(winSize.width * 0.5, getBottom(m_ttfLoginServerIp) - 4));
    
    m_ttfGmAccount = CCTextFieldTTF::textFieldWithPlaceHolder("GM Account", T_Font, 25);
    m_ttfGmAccount->setColor(ccBLUE);
    m_ttfGmAccount->setAnchorPoint(ccp(0.5, 1.0));
    m_ttfGmAccount->setPosition(ccp(winSize.width * 0.5, getBottom(m_ttfLoginServerPort) - 4));
    
    m_ttfUserAccount = CCTextFieldTTF::textFieldWithPlaceHolder("User Account", T_Font, 25);
    m_ttfUserAccount->setColor(ccGREEN);
    m_ttfUserAccount->setAnchorPoint(ccp(0.5, 1.0));
    m_ttfUserAccount->setPosition(ccp(winSize.width*0.5, getBottom(m_ttfGmAccount) - 4));
    
    m_ptfaLoginServerIp = CCTextFieldAuto::create(m_ttfLoginServerIp);
    m_ttfLoginServerIp->setDelegate(m_ptfaLoginServerIp);
    
    m_ptfaLoginServerPort = CCTextFieldAuto::create(m_ttfLoginServerPort);
    m_ttfLoginServerPort->setDelegate(m_ptfaLoginServerPort);
    
    m_ptfaGmAccount = CCTextFieldAuto::create(m_ttfGmAccount);
    m_ttfGmAccount->setDelegate(m_ptfaGmAccount);
    
    m_ptfaUserAccount = CCTextFieldAuto::create(m_ttfUserAccount);
    m_ttfUserAccount->setDelegate(m_ptfaUserAccount);
    
    m_pControlButtonExit = CCControlButton::create("exit", T_Font, 20);
    m_pControlButtonExit->setAnchorPoint(ccp(1.0, 1.0));
    m_pControlButtonExit->setPosition(ccp(winSize.width, winSize.height - 44));
    m_pControlButtonExit->addTargetWithActionForControlEvents(this, cccontrol_selector(StartGameLayer::onBack), CCControlEventTouchUpInside);
    
    m_pControlButtonExServer = CCControlButton::create("OuterServer", T_Font, 18);
    m_pControlButtonExServer->setAnchorPoint(ccp(1.0, 1.0));
    m_pControlButtonExServer->setPosition(ccp(winSize.width, getBottom(m_pControlButtonExit)-10));
    m_pControlButtonExServer->addTargetWithActionForControlEvents(this, cccontrol_selector(StartGameLayer::onExServer), CCControlEventTouchUpInside);
    
    m_pControlButtonInServer = CCControlButton::create("InnerServer", T_Font, 18);
    m_pControlButtonInServer->setAnchorPoint(ccp(1.0, 1.0));
    m_pControlButtonInServer->setPosition(ccp(winSize.width, getBottom(m_pControlButtonExServer)-2));
    m_pControlButtonInServer->addTargetWithActionForControlEvents(this, cccontrol_selector(StartGameLayer::onInServer), CCControlEventTouchUpInside);
    
    m_pControlButtonI4Server = CCControlButton::create("I4Server", T_Font, 18);
    m_pControlButtonI4Server->setAnchorPoint(ccp(1.0, 1.0));
    m_pControlButtonI4Server->setPosition(ccp(winSize.width, getBottom(m_pControlButtonInServer)-2));
    m_pControlButtonI4Server->addTargetWithActionForControlEvents(this, cccontrol_selector(StartGameLayer::onI4Server), CCControlEventTouchUpInside);

    addChild(m_ptfaLoginServerIp, 10);
    addChild(m_ptfaLoginServerPort, 10);
    addChild(m_ptfaGmAccount, 10);
    addChild(m_ptfaUserAccount, 10);
    addChild(m_pControlButtonExit, 5);
    addChild(m_pControlButtonExServer,5);
    addChild(m_pControlButtonInServer, 5);
    addChild(m_pControlButtonI4Server, 5);
#ifdef NDEBUG
    m_ptfaLoginServerIp->setVisible(false);
    m_ptfaLoginServerPort->setVisible(false);
    m_ptfaGmAccount->setVisible(false);
    m_ptfaUserAccount->setVisible(false);
    m_pControlButtonExit->setVisible(false);
    m_pControlButtonExServer->setVisible(false);
    m_pControlButtonInServer->setVisible(false);
    m_pControlButtonI4Server->setVisible(false);
    lblConnectStatus->setVisible(false);
    lblAreaId->setVisible(false);
#endif
    
    schedule(schedule_selector(StartGameLayer::update), 1.0f);
	return true;
}

StartGameLayer* StartGameLayer::GetCurLayer()
{
    return m_shared;
}

void StartGameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    
    AnalysicsManager::sharedAnalyticsMgr()->updateUmengOnlineParams();
    
    m_strDevice = LoginSystem::Get()->getUid();
    m_strVersion = cvtInt2String((int)CUR_GAME_VERSION);
    
    CMusicCtrl::PlayBackgroundMusic(GET_MUSIC(Bgm_start));
    
    lblServerName->setPositionY(m_pControlButtonServer->getPositionY() - 2.0f);
    lblAreaId->setPositionY(getCenterY(lblServerName));
    lblAreaId->setPositionX(getLeft(lblServerName) - 150.0f);
    
    LoginSystem::Get()->setAreaId(-1);
    
    // 如果输入错误IP，则会一直loading不停，注释掉下面代码}
    std::string strIp(d9_decode_get(D9_LOGIN_IP));
    int nPort = d9_decode_get_int(D9_LOGIN_PORT);
    if (!strIp.empty()) {
        if (m_ptfaLoginServerIp) {
            m_ptfaLoginServerIp->getTextField()->setString(strIp.c_str());
        }
        
    }
    if (nPort != 0) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", nPort);
        if (m_ptfaLoginServerPort) {
            m_ptfaLoginServerPort->getTextField()->setString(strBuf64);
        }
        
    }
}

static bool bFirstLogin = true;

void StartGameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    if (bFirstLogin) {
        bFirstLogin = false;
        runAction(
                  CCSequence::create(
                                     CCDelayTime::create(0.2f),
                                     CCCallFunc::create(this, callfunc_selector(StartGameLayer::onNewestFileVersion)),
                                     NULL
                                     )
                  );
    } else {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        onNewestFileVersion();
    }
}

void StartGameLayer::onExit()
{
	CCLayer::onExit();
    unschedule(schedule_selector(StartGameLayer::update));
}

void StartGameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void StartGameLayer::RefeashLayer()
{
    int nCurIdx = 0;
    if (ServerListCtrl::Get()) {
        nCurIdx = ServerListCtrl::Get()->getAreaNum();
    }
    // get from ccdefault!!
    int k = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_1);
    if (k >= 100 && ((k-100) < nCurIdx)) {
        nCurIdx = k-100;
    } else {
        // 取最新的区}
        nCurIdx -= 1;
    }

    // 默认没有选择的时候会自动选取最后一个或者上次选择的，此时应该给selected赋值，为了后续资源更新取到该服务器的资源版本号做准备}
    ServerListCtrl::Get()->setSelected(nCurIdx);
    uint16 wAreaId = ServerListCtrl::Get()->getAreaId(nCurIdx);
    
    LoginSystem::Get()->setAreaId(wAreaId);
    
    lblServerName->setString(ServerListCtrl::Get()->getAreaName(nCurIdx));

    snprintf(strBuf64, BUFFER_SIZE_64, "%d", wAreaId);
    lblAreaId->setString(strBuf64);
    
    
    // 增加用户名的刷新}
    if (m_nAuthFlag == LoginSystem::E_AUTH_ACCOUNT) {
        if (m_pControlButtonAccount) {
            CCString* strName = CCString::create(m_strUsername);
            m_pControlButtonAccount->setTitleForState(strName, CCControlStateNormal);
        }
        if (m_pControlButtonLogoff && m_strUsername.length() > 0) {
            m_pControlButtonLogoff->setVisible(true);
        }
    }
    if (m_nAuthFlag == LoginSystem::E_AUTH_THIRD) {
        if (m_pControlButtonThird) {
            //TODO: 我TM该显示什么内容？}
            CCString* strName = CCString::create(m_strUsername);
            m_pControlButtonThird->setTitleForState(strName, CCControlStateNormal);
        }
//        if (m_pControlButtonAccount) {
//            CCString* strName = CCString::create(m_strUsername);
//            m_pControlButtonAccount->setTitleForState(strName, CCControlStateNormal);
//        }
    }
}

// Inhert MemberVariableAssigner
bool StartGameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonFast", CCControlButton*, this->m_pControlButtonFast);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAccount", CCControlButton*, this->m_pControlButtonAccount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonThird", CCControlButton*, this->m_pControlButtonThird);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonServer", CCControlButton*, this->m_pControlButtonServer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLogoff", CCControlButton*, this->m_pControlButtonLogoff);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStart", CCSprite*, this->m_pSpriteStart);
	return false;
}

bool StartGameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN StartGameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler StartGameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler StartGameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonFast", StartGameLayer::onPressControlButtonFast);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAccount", StartGameLayer::onPressControlButtonAccount);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonThird", StartGameLayer::onPressControlButtonThird);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonServer", StartGameLayer::onPressControlButtonServer);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLogoff", StartGameLayer::onPressControlButtonLogoff);
	return NULL;
}

// Inhert CCNodeLoaderListener
void StartGameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonThird->setVisible(false);
    m_pSpriteStart->runAction(CCRepeatForever::create(CCSequence::create(CCHide::create(),
                                                                         CCDelayTime::create(0.6),
                                                                         CCShow::create(),
                                                                         CCDelayTime::create(1.0),
                                                                         NULL)));
    // [2014-01-26] 是否有账号被保存，有则账号登陆，否则快速登陆}
    m_strUsername = d9_decode_get(D9_ACCOUNT);
    m_strPassword = CCUserDefault::sharedUserDefault()->getStringForKey(D9_PASSWORD);
    
    m_nAuthFlag = LoginSystem::E_AUTH_FAST;
    
    if (!m_strUsername.empty() && m_strUsername != "") {
        CCString* strName = CCString::create(m_strUsername);
        m_pControlButtonAccount->setTitleForState(strName, CCControlStateNormal);
        m_nAuthFlag = LoginSystem::E_AUTH_ACCOUNT;
    } else {
        m_pControlButtonLogoff->setVisible(false);
    }
    
#if (defined VERSION_I4) || (defined VERSION_D9)||(defined VERSION_91)
    m_pControlButtonAccount->setVisible(false);
#endif
    
#ifndef NDEBUG
    m_pControlButtonFast->setPreferredSize(CCSizeMake(winSize.width, winSize.height*0.5));
#endif
}


void StartGameLayer::onPressControlButtonLogoff(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    d9_encode_save(D9_ACCOUNT, "");
    CCUserDefault::sharedUserDefault()->setStringForKey(D9_PASSWORD, "");
    CCString* strName = CCString::create(GET_STR(Str_account_login));
    m_pControlButtonAccount->setTitleForState(strName, CCControlStateNormal);
    
    m_nAuthFlag = LoginSystem::E_AUTH_FAST;
    m_pControlButtonLogoff->setVisible(false);
}

void StartGameLayer::onPressControlButtonFast(CCObject* pSender, CCControlEvent event)
{
	// get user input Ip
    // [2014-01-26] 点击登陆游戏，要看之前是否有账号登陆，如果没有，则默认快速登陆，否则账号登陆}
//    m_nAuthFlag = LoginSystem::E_AUTH_FAST;
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    LoginSystem::Get()->setMode(LoginSystem::E_FUCKING_LOWER);
#if defined VERSION_I4||VERSION_91
    Account::shareInstance()->init();
#elif defined VERSION_D9 ||VERSION_PP
    Account::shareInstance()->init();
    Account::shareInstance()->login();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Account::shareInstance()->login();
#else
    onStartLogin(m_strUsername, m_strPassword);
#endif
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("start_game");
#endif
}

void StartGameLayer::onPressControlButtonAccount(CCObject* pSender, CCControlEvent event)
{
    m_nAuthFlag = LoginSystem::E_AUTH_ACCOUNT;
    LoginSystem::Get()->setMode(LoginSystem::E_FUCKING_UPPER);
    CCNode* pAccountLayer = CcbManager::sharedManager()->LoadCcbAccountLayer( );
    addChild(pAccountLayer, 98, E_ACCOUNT_TAG);
}

void StartGameLayer::onPressControlButtonThird(CCObject* pSender, CCControlEvent event)
{
    LoginSystem::Get()->setMode(LoginSystem::E_FUCKING_UPPER);
    m_nAuthFlag = LoginSystem::E_AUTH_THIRD;
}

void StartGameLayer::onPressControlButtonServer(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    LoginSystem::Get()->setShowServerList(LoginSystem::E_FROM_SERVER);
    // 重新获取服务器列表}
    ConnectToLoginServer();
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    m_strUname = d9_decode_get(D9_ACCOUNT);
    CGameSession::SendRequestServerList(m_strUname, m_strDevice, m_strVersion, Support::sharedInstance()->appChannel());
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("select_server");
#endif
}


#pragma mark Private Method

void StartGameLayer::ConnectToLoginServer()
{
    std::string strIp;
    std::string strPort;
    
    if (m_ptfaLoginServerIp) {
        strIp = (m_ptfaLoginServerIp->getTextField()->getString());
    }
    if (m_ptfaLoginServerPort) {
        strPort = (m_ptfaLoginServerPort->getTextField()->getString());
    }

    std::string strLoginServerPort;
    
    if (!strIp.empty() && strIp != "") {
        m_strLoginServerIp = strIp;
    } else {
#ifdef DEBUG
        m_strLoginServerIp = DEBUG_IP;
#elif defined VERSION_I4
        m_strLoginServerIp = I4_IP;
#else
        m_strLoginServerIp = RELEASE_IP;
#endif
        
    }
    if (!strPort.empty() && strPort != "") {
        strLoginServerPort = strPort;
        m_nLoginServerPort = atoi(strLoginServerPort.c_str());
    } else {
#ifdef DEBUG
        m_nLoginServerPort = DEFAULT_PORT;
#else
        m_nLoginServerPort = OUTER_PORT;
#endif
    }
    
    d9_encode_save(D9_LOGIN_IP, m_strLoginServerIp);
    d9_encode_save(D9_LOGIN_PORT, m_nLoginServerPort);
    
    LoginSystem::Get()->ConnectToLoginServer(m_strLoginServerIp, m_nLoginServerPort);
}

void StartGameLayer::onNewestFileVersion()
{
    LoginSystem::Get()->setShowServerList(LoginSystem::E_FROM_STARTING);
    ConnectToLoginServer();
    
    m_strUname = d9_decode_get(D9_ACCOUNT);
    
    // [2014-10-15] 放大招啦！小于10直接重新取一遍}
    if (m_strDevice.empty() || m_strDevice == "" || m_strDevice.length() < 10) {
        m_strDevice = LoginSystem::Get()->getUid();
    }
    
    CGameSession::SendRequestServerList(m_strUname, m_strDevice, m_strVersion, Support::sharedInstance()->appChannel());
    LoginSystem::Get()->setConnectStatus( LoginSystem::E_UNCONNECTED );
}


#pragma mark Public Method
void StartGameLayer::update(float delta)
{
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    CNetClient::eConnectState connState = pNetClient->connectState();
    if ( connState == CNetClient::CONN_STATE_CONNECTED ) {
        lblConnectStatus->setString("connected!");
    } else if ( connState == CNetClient::CONN_STATE_CONNECTING ) {
        lblConnectStatus->setString("connecting...");
    } else if ( connState == CNetClient::CONN_STATE_DISCONNECT ) {
        lblConnectStatus->setString("disconnected");
    } else {
        lblConnectStatus->setString("error");
    }
}

void StartGameLayer::setCurAreaId(int idx)
{
    if (getChildByTag(E_SERVER_TAG)) {
        dynamic_cast<CcbServerListLayer*>(getChildByTag(E_SERVER_TAG))->onSlideUp();
    }

    uint16 wAreaId = ServerListCtrl::Get()->getAreaId(idx);
    LoginSystem::Get()->setAreaId(wAreaId);
    ServerListCtrl::Get()->setSelected(idx);
    
    lblServerName->setString(ServerListCtrl::Get()->getAreaName(idx));
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", wAreaId);
    lblAreaId->setString(strBuf64);
}

void StartGameLayer::onBack(CCObject* pObject, CCControlEvent event)
{
    CCScene* pScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void StartGameLayer::onExServer(CCObject* pObject, CCControlEvent event) {
    if (m_ptfaLoginServerIp) {
        m_ptfaLoginServerIp->getTextField()->setString(RELEASE_IP);
    }
    if (m_ptfaLoginServerPort) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", OUTER_PORT);
        m_ptfaLoginServerPort->getTextField()->setString(strBuf64);
    }
}

void StartGameLayer::onInServer(CCObject* pObject, CCControlEvent event){
    if (m_ptfaLoginServerIp) {
        m_ptfaLoginServerIp->getTextField()->setString(DEBUG_IP);
    }
    if (m_ptfaLoginServerPort) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", DEFAULT_PORT);
        m_ptfaLoginServerPort->getTextField()->setString(strBuf64);
    }
}

void StartGameLayer::onI4Server(CCObject* pObject, CCControlEvent event) {
    if (m_ptfaLoginServerIp) {
        m_ptfaLoginServerIp->getTextField()->setString(I4_IP);
    }
    if (m_ptfaLoginServerPort) {
        snprintf(strBuf64, BUFFER_SIZE_64, "%d", I4_PORT);
        m_ptfaLoginServerPort->getTextField()->setString(strBuf64);
    }
}


void StartGameLayer::setRegResult(WorldPacket &packet)
{
    uint8 byRegResult;
    std::string strAccount, strPwd;
    packet >> byRegResult >> strAccount >> strPwd;
    
    if (byRegResult == E_ERRNO_AUTH_REG_SUCCESS) {
        // 注册成功}
        FlyTextLayer::showTips(GET_STR(Str_regist_suc));
        
        d9_encode_save(D9_ACCOUNT, strAccount);
        CCUserDefault::sharedUserDefault()->setStringForKey(D9_PASSWORD, strPwd);
        if (getChildByTag(E_REGIST_TAG)) {
            getChildByTag(E_REGIST_TAG)->removeFromParent();
        }
        LoginSystem::Get()->setMode(LoginSystem::E_FUCKING_UPPER);
        CCNode* pAccountLayer = CcbManager::sharedManager()->LoadCcbAccountLayer( );
        addChild(pAccountLayer, 98, E_ACCOUNT_TAG);
        return;
    } else if (byRegResult == E_ERRNO_AUTH_ACCOUNT_HAVE) {
        FlyTextLayer::showTips(GET_STR(Str_already_have_account));
        return;
    } else {
        FlyTextLayer::showTips(GET_STR(Str_other_error));
        return;
    }
    return;
}

void StartGameLayer::addCurAreaIdToUserDefault()
{
    int nCur1 = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_1);
    int nCur2 = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_2);
    int nCur3 = CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_AREA_ID_3);
    
    uint16 wSelected = ServerListCtrl::Get()->getSelected();
    if (wSelected == 999) {
        if (nCur1) {
            wSelected = nCur1;
        } else {
            // 默认最新服务器，没有手动选区}
            wSelected = ServerListCtrl::Get()->getAreaNum()-1;
            wSelected += 100;
        }
    } else {
        wSelected += 100;
    }
    
    std::vector<int> vecServerId;
    vecServerId.clear();
    vecServerId.push_back(nCur1);
    vecServerId.push_back(nCur2);
    vecServerId.push_back(nCur3);
    vector<int>::iterator serIter = vecServerId.begin();
    for (; serIter != vecServerId.end(); ++serIter) {
        if (*serIter == wSelected) {
            vecServerId.erase(serIter);
            break;
        }
    }
    
    vecServerId.insert(vecServerId.begin(), wSelected);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(D9_AREA_ID_1, vecServerId[0]);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(D9_AREA_ID_2, vecServerId[1]);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(D9_AREA_ID_3, vecServerId[2]);
    
}

//  登陆回调函数}
void StartGameLayer::login(const char *strUname, const char * strPwd, const char *userId)
{
    std::string strName(strUname);
    std::string strPassword(strPwd);
    std::string strUserId(userId);
    onStartLogin(strName, strPassword,strUserId);
}
void StartGameLayer::onStartLogin(std::string& strUname, std::string& strPwd, std::string _strGm)
{
    if (ServerListCtrl::Get()->getAreaNum() == 0) {
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        onNewestFileVersion();
        return;
    }
    
    // 资源更新判断}
    if (checkNeedUpdate()) {
        return;
    }
    
    addCurAreaIdToUserDefault();
    
    std::string strGM;
    
    if (m_ptfaGmAccount) {
        strGM = (m_ptfaGmAccount->getTextField()->getString());
    }
    if (!_strGm.empty()) {
        strGM = _strGm;
    }
    
    m_strUsername = strUname;
    m_strPassword = strPwd;
    
    // [2014-02-14] added by Juniechu, 修复点击账户后不登陆返回的bug}
    // [2014-02-21] fix bug, 移上来是因为当快速登陆的时候，如果利用gm登陆，由于username为空，则会被判断为快速登陆}
    if (m_strUsername.empty() || m_strUsername == "") {
        m_nAuthFlag = LoginSystem::E_AUTH_FAST;
        LoginSystem::Get()->setMode(LoginSystem::E_FUCKING_LOWER);
    }
    
    if (!strGM.empty()) {
        m_nAuthFlag = LoginSystem::E_AUTH_THIRD;
        m_strUsername = strGM;
    }
    
    std::string strUser;
    if (m_ptfaUserAccount) {
        strUser = (m_ptfaUserAccount->getTextField()->getString());
    }
    
    if (!strUser.empty()) {
        m_nAuthFlag = LoginSystem::E_AUTH_USER;
        LoginSystem::Get()->setUserId(atoll(strUser.c_str()));
    }
    
    LoginSystem::Get()->StartLogin(m_strLoginServerIp, m_nLoginServerPort, m_nAuthFlag, m_strUsername, m_strPassword);
    
}

void StartGameLayer::sendRegInfo(std::string strAcnt, std::string strPwd, std::string strMail)
{
    ConnectToLoginServer();
    
    m_strRegAccount = strAcnt;
    m_strRegPwd = strPwd;
    m_strRegMail = strMail;
    
    Support* application = Support::sharedInstance();
    
    CGameSession::SendGameReg(LoginSystem::Get()->getUid(), CUR_GAME_VERSION, m_strRegAccount, m_strRegPwd, m_strRegMail, application->deviceType(), application->deviceOS(), application->appChannel());
}

bool StartGameLayer::checkNeedUpdate()
{
    VersionCtrl vCtrl;
    
    vCtrl.checkUseWhichResource();
    
    if (vCtrl.needUpdate(ServerListCtrl::Get()->resourceVersion())) {
        CCLog("[%d] need to Update!", ServerListCtrl::Get()->resourceVersion());
		SystemMessage::showSystemMessage(1, this, GET_STR(Str_need_update), this, true);
        
        return true;
    }
    return false;
}

void StartGameLayer::updateFinish()
{
    CCFileUtils::sharedFileUtils()->purgeCachedEntries();
    
    VersionCtrl vCtrl;
    
    vCtrl.updateCallback(ServerListCtrl::Get()->resourceVersion());
    
    snprintf(strBuf64, BUFFER_SIZE_64, "%s.%u", Support::sharedInstance()->appVersion(), ServerListCtrl::Get()->resourceVersion());
    m_pLabelTTFVersion->setString(strBuf64);
    
    // 清除音乐缓存
    if (strcmp(Support::sharedInstance()->systemVersion(), "5.1.1") != 0) {
        SoundSystem::SoundSystemFmod::getInstance()->cleanUp();
    }
    
    // 清除图片路径缓存，在更新前预加载的
    GameStateManager::sharedManager()->Reload();
}

void StartGameLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
	// 增加下载界面}
    CCNode* pUpdateLayer = CcbManager::sharedManager()->LoadCcbUpdateResourceLayer(this);
    addChild(pUpdateLayer, 200);

AnalysicsManager::sharedAnalyticsMgr()->SendEvent("update_resource");
#endif
}
