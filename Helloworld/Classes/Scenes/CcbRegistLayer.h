/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-04 18:06:47
*/

#ifndef __CCBREGISTLAYER__H__
#define __CCBREGISTLAYER__H__

//CcbRegistLayer.h come from ccb/regist.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbRegistLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
{
public:
	// Constructor
	CcbRegistLayer()
	{
		m_pControlButtonOk = NULL;
		m_pControlButtonCancel = NULL;
        m_pScale9SpriteAccount = NULL;
        //m_pScale9SpriteCPassword = NULL;
        m_pScale9SpritePassword = NULL;
        //m_pScale9SpriteMail = NULL;
        m_strAccount = "";
        m_strPassword = "";
        //m_strCPassword = "";
        //m_strMail = "";
        mAnimationManager = NULL;
        m_pLayerParent = NULL;
	}
	~CcbRegistLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbRegistLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonOk;
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
    CCScale9Sprite* m_pScale9SpriteAccount;
    CCScale9Sprite* m_pScale9SpritePassword;
    //CCScale9Sprite* m_pScale9SpriteCPassword;
    //CCScale9Sprite* m_pScale9SpriteMail;
    CCLayer* m_pLayerParent;
    
    CCEditBox* m_pEditAccount;
    CCEditBox* m_pEditPwd;
    //CCEditBox* m_pEditCPwd;
    //CCEditBox* m_pEditMail;

    std::string m_strAccount, m_strPassword, m_strCPassword;//, m_strMail;
    
    void onCancel();
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
	
public:
	// Funcitons
	void onPressControlButtonOk(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbRegistLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbRegistLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbRegistLayer);
};


#endif // __CCBREGISTLAYER__H__