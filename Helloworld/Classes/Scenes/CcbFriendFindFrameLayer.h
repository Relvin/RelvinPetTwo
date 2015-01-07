/**
* CcbFriendFindFrameLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-21 23:51:50
*/

#ifndef __CCBFRIENDFINDFRAMELAYER__H__
#define __CCBFRIENDFINDFRAMELAYER__H__

//CcbFriendFindFrameLayer.h come from ccb/CcbFriendFindFrameLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FriendUnitDataMgr.h"
#include "Defines.h"

class CcbPetIcon;
class CcbFriendFindFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFriendFindFrameLayer()
	{
		m_pLayerHead = NULL;
		m_pControlButtonAddFriend = NULL;
		m_pLabelTTFFightPower = NULL;
		m_pLabelTTFWord = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFLv = NULL;
        m_dwTargetId = 0;
	}
	~CcbFriendFindFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendFindFrameLayer, create);
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
	CcbPetIcon* m_pLayerHead;
	cocos2d::extension::CCControlButton* m_pControlButtonAddFriend;
	cocos2d::CCLabelTTF* m_pLabelTTFFightPower;
	cocos2d::CCLabelTTF* m_pLabelTTFWord;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;

    uint32 m_dwTargetId;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setFrameData(const FriendUnitDataMgr::STC_LIST_INFO& _info);
public:
	// Funcitons
	void onPressControlButtonAddFriend(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbFriendFindFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendFindFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendFindFrameLayer);
};


#endif // __CCBFRIENDFINDFRAMELAYER__H__