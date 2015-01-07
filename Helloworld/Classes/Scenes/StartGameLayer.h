/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-29 16:00:32
*/

#ifndef __STARTGAMELAYER__H__
#define __STARTGAMELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "WorldPacket.h"
#include "Observer.h"
#include "SystemMessage.h"

class CCTextFieldAuto;
class StartGameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverMsg
,   public SystemMessageProtocol
{
public:
    // enum
	enum {
		E_SYSTEMMSG_REGOK,
		E_SYSTEMMSG_EXIT,
	};
    
    enum {
        E_ACCOUNT_TAG = 465,
        E_REGIST_TAG = 179,
        E_SERVER_TAG = 369,
    };
    
	// Constructor
	StartGameLayer()
	{
		m_pControlButtonFast = NULL;
		m_pControlButtonAccount = NULL;
		m_pControlButtonThird = NULL;
        m_pControlButtonServer = NULL;
        m_pControlButtonLogoff = NULL;

        m_pControlButtonExit = NULL;
        m_pControlButtonExServer = NULL;
        m_pControlButtonInServer = NULL;
        m_pControlButtonI4Server = NULL;
        m_pSpriteStart = NULL;
        
        lblConnectStatus = NULL;
        lblServerName = NULL;
        lblAreaId = NULL;
        m_shared = NULL;
        
        m_strUsername = "";
        m_strPassword = "";
	}
	~StartGameLayer();

    static StartGameLayer* GetCurLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StartGameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonFast;
	cocos2d::extension::CCControlButton* m_pControlButtonAccount;
	cocos2d::extension::CCControlButton* m_pControlButtonThird;
    cocos2d::extension::CCControlButton* m_pControlButtonServer;
    cocos2d::extension::CCControlButton* m_pControlButtonLogoff;
    
    cocos2d::extension::CCControlButton* m_pControlButtonExit;
    cocos2d::extension::CCControlButton* m_pControlButtonExServer;
    cocos2d::extension::CCControlButton* m_pControlButtonInServer;
    cocos2d::extension::CCControlButton* m_pControlButtonI4Server;
    
    cocos2d::CCSprite* m_pSpriteStart;
    
    cocos2d::CCLabelTTF* lblConnectStatus;
    cocos2d::CCLabelTTF* lblServerName;
    cocos2d::CCLabelTTF* lblAreaId;
    std::string m_strUsername, m_strPassword, m_strLoginServerIp;
    int m_nLoginServerPort;
    std::string m_strRegAccount, m_strRegPwd, m_strRegMail;
    
    
    cocos2d::CCTextFieldTTF* m_ttfLoginServerIp;
    cocos2d::CCTextFieldTTF* m_ttfLoginServerPort;
    cocos2d::CCTextFieldTTF* m_ttfGmAccount;
    cocos2d::CCTextFieldTTF* m_ttfUserAccount;
    
    CCTextFieldAuto* m_ptfaLoginServerIp;
    CCTextFieldAuto* m_ptfaLoginServerPort;
    CCTextFieldAuto* m_ptfaGmAccount;
    CCTextFieldAuto* m_ptfaUserAccount;
    
    static StartGameLayer* m_shared;
    
    cocos2d::CCSize winSize;

    CCLabelTTF* m_pLabelTTFVersion;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    virtual void RefeashLayer();

    void update(float delta);
    
	void onBack(CCObject* pObject , CCControlEvent event);
    
    void setRegResult(WorldPacket& packet);
    
    /*!
     账号登录传入strUname和strPwd的值}
     第三方登录前两个参数传空，最后一个传入第三方ID
     
     登出调用CGameSession::BackToLogin();
     */
    void login(const char *strUname, const char * strPwd, const char *userId);
    void onStartLogin(std::string& strUname, std::string& strPwd, std::string _strGm = "");
    void sendRegInfo(std::string strAcnt, std::string strPwd, std::string strMail);
    
    void updateFinish();
#pragma mark Prvate Method Declare
private:
	void ConnectToLoginServer();
    void onNewestFileVersion();
    
    void addCurAreaIdToUserDefault();
    
    std::string getUid();
    
	void onExServer(CCObject* pObject, CCControlEvent event);
	void onInServer(CCObject* pObject, CCControlEvent event);
	void onI4Server(CCObject* pObject, CCControlEvent event);
    
    bool checkNeedUpdate();
    
    std::string m_strDevice;
    std::string m_strUname;
    std::string m_strVersion;
public:
	// Funcitons}

	void onPressControlButtonFast(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonAccount(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonThird(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonServer(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonLogoff(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    // return by server!
    uint8 m_nAuthFlag;
    std::string m_strGameServerIp;
    int m_nGameServerPort;

    void setCurAreaId(int idx);
};

class StartGameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StartGameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StartGameLayer);
};


#endif // __STARTGAMELAYER__H__