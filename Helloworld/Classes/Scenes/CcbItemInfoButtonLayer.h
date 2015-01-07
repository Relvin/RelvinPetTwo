/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-13 13:57:58
*/

#ifndef __CCBITEMINFOBUTTONLAYER__H__
#define __CCBITEMINFOBUTTONLAYER__H__

//CcbItemInfoButtonLayer.h come from ccb/iteminfo_button.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemInfoButtonLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbItemInfoButtonLayer()
	{
		m_pControlButtonShowItemInfo = NULL;

        m_btnShow = NULL;
	}
	~CcbItemInfoButtonLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemInfoButtonLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
//    virtual void registerWithTouchDispatcher();
//    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCControlButton* m_pControlButtonShowItemInfo;

    CCScrollButton* m_btnShow;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonShowItemInfo(CCObject* pSender, CCControlEvent event);

    void setShowItemID(uint32 dwItemID) { m_dwShowItemID = dwItemID; };
    void setClipRect(CCRect rect);
    uint32 m_dwShowItemID;
};

class CcbItemInfoButtonLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbItemInfoButtonLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbItemInfoButtonLayer);
};


#endif // __CCBITEMINFOBUTTONLAYER__H__