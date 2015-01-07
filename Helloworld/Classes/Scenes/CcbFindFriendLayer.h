/**
* CcbFindFriendLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-21 23:48:51
*/

#ifndef __CCBFINDFRIENDLAYER__H__
#define __CCBFINDFRIENDLAYER__H__

//CcbFindFriendLayer.h come from ccb/find_friend.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbFindFriendLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
{
public:
	// Constructor
	CcbFindFriendLayer()
	{
		m_pLabelTTFWord = NULL;
		m_pLabelTTFMyId = NULL;
		m_pScale9SpriteInput = NULL;
		m_pControlButtonFind = NULL;
        m_pEditBoxInput = NULL;
	}
	~CcbFindFriendLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFindFriendLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFWord;
	cocos2d::CCLabelTTF* m_pLabelTTFMyId;
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteInput;
	cocos2d::extension::CCControlButton* m_pControlButtonFind;

    cocos2d::extension::CCEditBox* m_pEditBoxInput;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
	void onPressControlButtonFind(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    // CCEditBoxDelegate
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
};

class CcbFindFriendLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFindFriendLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFindFriendLayer);
};


#endif // __CCBFINDFRIENDLAYER__H__