/**
* CcbFriendSocialBoardLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-22 21:18:48
*/

#ifndef __CCBFRIENDSOCIALBOARDLAYER__H__
#define __CCBFRIENDSOCIALBOARDLAYER__H__

//CcbFriendSocialBoardLayer.h come from ccb/friend_social_board.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbFriendSocialBoardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFriendSocialBoardLayer()
	{
		m_pControlButtonClose = NULL;
		m_pControlButtonMail = NULL;
		m_pControlButtonChallenge = NULL;
		m_pControlButtonDelete = NULL;

	}
	~CcbFriendSocialBoardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendSocialBoardLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonClose;
	cocos2d::extension::CCControlButton* m_pControlButtonMail;
	cocos2d::extension::CCControlButton* m_pControlButtonChallenge;
	cocos2d::extension::CCControlButton* m_pControlButtonDelete;

    uint32 m_dwTargetId;
    std::string m_strTargetName;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setTargetIdAndName(uint32 dwTargetId, std::string strTargetName);
public:
	// Funcitons
	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonMail(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonChallenge(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonDelete(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

class CcbFriendSocialBoardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendSocialBoardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendSocialBoardLayer);
};


#endif // __CCBFRIENDSOCIALBOARDLAYER__H__