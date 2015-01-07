/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-24 18:36:26
*/

#ifndef __CCBFRIENDMAILLAYER__H__
#define __CCBFRIENDMAILLAYER__H__

//CcbFriendMailLayer.h come from ccb/friend_mail.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCTextFieldAuto.h"
#include "SystemMessage.h"

class CcbFriendMailLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
,   public CCIMEDelegate
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbFriendMailLayer()
	{
		m_pScale9SpriteTitle = NULL;
//		m_pScale9SpriteContent = NULL;
        m_pNodeContent = NULL;
        m_pControlButtonSend = NULL;
        m_pLabelTTFId = NULL;
        m_pEditTitle = NULL;
        m_pTTFContent = NULL;
        m_pTTAContent = NULL;
        m_strTile = "";
        m_strContent = "";
        m_dwUserId = 0;
        m_pLayerContent = NULL;
	}
	~CcbFriendMailLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendMailLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB

    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteTitle;
//    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteContent;
    cocos2d::CCNode* m_pNodeContent;
    cocos2d::extension::CCControlButton* m_pControlButtonSend;
    cocos2d::CCLabelTTF* m_pLabelTTFId;
    cocos2d::CCLayer* m_pLayerContent;
    
    std::string m_strTile;
    std::string m_strContent;
    uint32 m_dwUserId;
    cocos2d::extension::CCEditBox* m_pEditTitle;

    // 为了能输入多行，利用TextFieldAuto}
    cocos2d::CCTextFieldTTF* m_pTTFContent;
    CCTextFieldAuto* m_pTTAContent;
    
    // 说来话长~哎。看界面吧，能回忆多少回忆多少，回忆不起来也没关系。}
    cocos2d::CCPoint m_posBegin;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
	virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
    
    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
public:
	// Funcitons
    void onPressControlButtonSend(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbFriendMailLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendMailLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendMailLayer);
};


#endif // __CCBFRIENDMAILLAYER__H__