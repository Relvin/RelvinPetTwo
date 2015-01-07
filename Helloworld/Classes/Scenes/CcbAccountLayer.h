/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-04 18:07:21
*/

#ifndef __CCBACCOUNTLAYER__H__
#define __CCBACCOUNTLAYER__H__

//CcbAccountLayer.h come from ccb/account_login.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CcbAccountLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
{
public:
	// Constructor
	CcbAccountLayer()
	{
		m_pControlButtonOk = NULL;
		m_pControlButtonCancel = NULL;
		m_pControlButtonReg = NULL;
        m_pScale9SpriteAccount = NULL;
        m_pScale9SpritePassword = NULL;
        m_strAccount = "";
        m_strPassword = "";
        mAnimationManager = NULL;
        m_pLayerParent = NULL;
	}
	~CcbAccountLayer();

    static CcbAccountLayer* GetCurLayer();
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbAccountLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
//    void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonOk;
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
	cocos2d::extension::CCControlButton* m_pControlButtonReg;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteAccount;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpritePassword;
    cocos2d::CCLayer* m_pLayerParent;
    
    cocos2d::extension::CCEditBox* m_pEditAccount;
    cocos2d::extension::CCEditBox* m_pEditPassword;

    std::string m_strAccount;
    std::string m_strPassword;
    cocos2d::CCSize winSize;
    
    void onCancel();
    void onRegist();
    
    static CcbAccountLayer* m_shared;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
//    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
//	virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
    void HideAccountLayer();
public:
	// Funcitons
	void onPressControlButtonOk(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonReg(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
};

class CcbAccountLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbAccountLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbAccountLayer);
};


#endif // __CCBACCOUNTLAYER__H__