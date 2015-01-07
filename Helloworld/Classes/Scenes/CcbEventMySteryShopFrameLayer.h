/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-22 15:45:10
*/

#ifndef __CCBEVENTMYSTERYSHOPFRAMELAYER__H__
#define __CCBEVENTMYSTERYSHOPFRAMELAYER__H__

//CcbEventMySteryShopFrameLayer.h come from ccb/event_mysteryshop_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbItemIconLayer.h"
#include "EventDataMgr.h"
class CCScrollButton;

class CcbEventMySteryShopFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener

{
public:
	// Constructor
	CcbEventMySteryShopFrameLayer()
	{
		m_pLayerIcon = NULL;
		m_pControlButtonExchange = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFExchange = NULL;
		m_pLabelTTFExchangeCount = NULL;
        m_pSpriteCostType = NULL;
	}
	~CcbEventMySteryShopFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventMySteryShopFrameLayer, create);
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
	CCScrollButton* m_pControlButtonExchange;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFExchange;
	cocos2d::CCLabelTTF* m_pLabelTTFExchangeCount;
    CcbItemIconLayer* m_pLayerIcon;
    cocos2d::CCSprite* m_pSpriteCostType;

    STC_STERY_GOODS m_stcGoods;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    void loadData(STC_STERY_GOODS stcGoods);

	void onPressControlButtonExchange(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void setClipRect(CCRect rect);

};

class CcbEventMySteryShopFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventMySteryShopFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventMySteryShopFrameLayer);
};


#endif // __CCBEVENTMYSTERYSHOPFRAMELAYER__H__