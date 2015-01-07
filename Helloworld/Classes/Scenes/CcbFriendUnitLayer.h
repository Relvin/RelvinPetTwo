/**
* CcbFriendUnitLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-20 21:01:48
*/

#ifndef __CCBFRIENDUNITLAYER__H__
#define __CCBFRIENDUNITLAYER__H__

//CcbFriendUnitLayer.h come from ccb/friend_uint.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

#define Btn_Cnt 5

class CcbFriendUnitLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFriendUnitLayer()
	{
		m_pControlButtonMyFriend = NULL;
		m_pControlButtonSuggest = NULL;
		m_pControlButtonGetEnergy = NULL;
		m_pControlButtonInvite = NULL;
		m_pControlButtonMail = NULL;
		m_pLayerUp = NULL;
		m_pLayerDown = NULL;

	}
	~CcbFriendUnitLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendUnitLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonMyFriend;
	cocos2d::extension::CCControlButton* m_pControlButtonSuggest;
	cocos2d::extension::CCControlButton* m_pControlButtonGetEnergy;
	cocos2d::extension::CCControlButton* m_pControlButtonInvite;
	cocos2d::extension::CCControlButton* m_pControlButtonMail;
	cocos2d::CCLayer* m_pLayerUp;
	cocos2d::CCLayer* m_pLayerDown;

    cocos2d::CCSize m_pSizeMiddle;
    cocos2d::CCPoint m_pPointMiddle;
    
    /*!
     enum {
     kFriendListType = 0,
     kFriendSuggestType,
     kEnergyGetType,
     kFriendMailType,
     };
     */
    cocos2d::extension::CCControlButton* m_pControlButtonType[Btn_Cnt];
    
    void pressControlButton(int _type);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
	void onPressControlButtonMyFriend(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonSuggest(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonGetEnergy(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonInvite(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonMail(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbFriendUnitLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendUnitLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendUnitLayer);
};


#endif // __CCBFRIENDUNITLAYER__H__