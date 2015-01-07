/**
* CcbMapPointJumpLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-12-09 20:38:34
*/

#ifndef __CCBMAPPOINTJUMPLAYER__H__
#define __CCBMAPPOINTJUMPLAYER__H__

//CcbMapPointJumpLayer.h come from ccb/jump.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbMapPointJumpLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbMapPointJumpLayer()
	{
		m_pLayerColor = NULL;
		m_pControlButtonCancel = NULL;
		m_pLabelTTFContent = NULL;
		m_pControlButtonGoto1 = NULL;
		m_pControlButtonGoto2 = NULL;

	}
	~CcbMapPointJumpLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbMapPointJumpLayer, create);
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
	cocos2d::CCLayer* m_pLayerColor;
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
	cocos2d::CCLabelTTF* m_pLabelTTFContent;
	cocos2d::extension::CCControlButton* m_pControlButtonGoto1;
	cocos2d::extension::CCControlButton* m_pControlButtonGoto2;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonGoto1(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonGoto2(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    // Touch Delegate
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};

class CcbMapPointJumpLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbMapPointJumpLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbMapPointJumpLayer);
};


#endif // __CCBMAPPOINTJUMPLAYER__H__