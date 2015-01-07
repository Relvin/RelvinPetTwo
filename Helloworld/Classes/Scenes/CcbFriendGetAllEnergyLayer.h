/**
* CcbFriendGetAllEnergyLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-22 15:54:19
*/

#ifndef __CCBFRIENDGETALLENERGYLAYER__H__
#define __CCBFRIENDGETALLENERGYLAYER__H__

//CcbFriendGetAllEnergyLayer.h come from ccb/friend_send_energy.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbFriendGetAllEnergyLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFriendGetAllEnergyLayer()
	{
		m_pLabelTTFWord = NULL;
		m_pLabelTTFLeftCnt = NULL;
		m_pControlButtonGetAll = NULL;

	}
	~CcbFriendGetAllEnergyLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendGetAllEnergyLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFLeftCnt;
	cocos2d::extension::CCControlButton* m_pControlButtonGetAll;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void leftEnergyCntUpdate();
public:
	// Funcitons
	void onPressControlButtonGetAll(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbFriendGetAllEnergyLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendGetAllEnergyLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendGetAllEnergyLayer);
};


#endif // __CCBFRIENDGETALLENERGYLAYER__H__