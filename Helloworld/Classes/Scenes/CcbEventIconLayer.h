/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-11 19:09:02
*/

#ifndef __CCBEVENTICONLAYER__H__
#define __CCBEVENTICONLAYER__H__

//CcbEventIconLayer.h come from ccb/event_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EventDataMgr.h"
#include "CCScrollButton.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEventIconLayer:
	public cocos2d::CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CObserverRole
{
public:
	// Constructor
	CcbEventIconLayer()
	{
		m_pControlButtonEvent = NULL;
        m_pSpriteTip = NULL;
        m_pSpriteSelectframe = NULL;
	}
	~CcbEventIconLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventIconLayer, create);
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
public:
	CCScrollButton* m_pControlButtonEvent;
    CCSprite* m_pSpriteTip;
    CCSprite* m_pSpriteSelectframe;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
public:
	// Funcitons
    void ChangeIconState();
    //CC_SYNTHESIZE(int, m_showType, ShowType);
    void SetShowData(int type);
    int m_showType;
    
    void isSelected(bool flag);
    
	void onPressControlButtonEvent(CCObject* pSender, CCControlEvent event);
    virtual void byEnergyRewStatusChanged(uint8 byEnergyRewStatus);
    virtual void bySevenRewStatusChanged(uint8 bySevenRewStatus);
    virtual void byThirtyRewStatusChanged(uint8 byThirtyRewStatus);
};

class CcbEventIconLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventIconLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventIconLayer);
};


#endif // __CCBEVENTICONLAYER__H__