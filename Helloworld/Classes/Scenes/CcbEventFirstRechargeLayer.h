/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-29 17:39:11
*/

#ifndef __CCBEVENTFIRSTRECHARGELAYER__H__
#define __CCBEVENTFIRSTRECHARGELAYER__H__

//CcbEventFirstRechargeLayer.h come from ccb/event_first_recharge.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEventFirstRechargeLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbEventFirstRechargeLayer()
	{
		m_pLayerIcon1 = NULL;
        m_pLayerIcon2 = NULL;
        m_pLayerIcon3 = NULL;
        m_pLayerIcon4 = NULL;
		m_pControlButtonGet = NULL;
		m_pControlButtonGoRecharge = NULL;

	}
	~CcbEventFirstRechargeLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventFirstRechargeLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CcbItemIconLayer* m_pLayerIcon1;
    CcbItemIconLayer* m_pLayerIcon2;
    CcbItemIconLayer* m_pLayerIcon3;
    CcbItemIconLayer* m_pLayerIcon4;
	CCControlButton* m_pControlButtonGet;
	CCControlButton* m_pControlButtonGoRecharge;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonGet(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonGoCharge(CCObject* pSender, CCControlEvent event);


private:
    void loadData();
};

class CcbEventFirstRechargeLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventFirstRechargeLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventFirstRechargeLayer);
};


#endif // __CCBEVENTFIRSTRECHARGELAYER__H__