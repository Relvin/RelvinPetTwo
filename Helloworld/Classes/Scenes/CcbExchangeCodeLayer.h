/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-22 14:05:54
*/

#ifndef __CCBEXCHANGECODELAYER__H__
#define __CCBEXCHANGECODELAYER__H__

//CcbExchangeCodeLayer.h come from ccb/exchange_code.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbExchangeCodeLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCEditBoxDelegate
,   public CObserverMsg
{
public:
	// Constructor
	CcbExchangeCodeLayer()
	{
		m_pControlButtonExchangeCode = NULL;
        m_pSpriteEditParent = NULL;
        m_pScale9SpriteEnterCode = NULL;
        m_pEditBoxEnterCode = NULL;
        
	}
	~CcbExchangeCodeLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbExchangeCodeLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual void RefeashLayer();

    //Edit Box
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCControlButton* m_pControlButtonExchangeCode;
    CCSprite* m_pSpriteEditParent;
    CCScale9Sprite* m_pScale9SpriteEnterCode;
    CCEditBox* m_pEditBoxEnterCode;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonExchangeCode(CCObject* pSender, CCControlEvent event);



};

class CcbExchangeCodeLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbExchangeCodeLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbExchangeCodeLayer);
};


#endif // __CCBEXCHANGECODELAYER__H__