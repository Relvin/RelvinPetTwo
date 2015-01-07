/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-14 14:32:45
*/

#ifndef __CCBARENASHOPFRAMELAYER__H__
#define __CCBARENASHOPFRAMELAYER__H__

//CcbArenaShopFrameLayer.h come from ccb/arena_shop_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaShopFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbArenaShopFrameLayer()
	{
//		m_pSpriteIcon = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFDesc = NULL;
		m_pLabelTTFExchangeCount = NULL;
		m_pControlButtonExchange = NULL;
        m_pControlButtonExchange1 = NULL;
        m_pLayerIcon = NULL;
        m_dwIndex = 0;
	}
	~CcbArenaShopFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaShopFrameLayer, create);
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
	CcbItemIconLayer* m_pLayerIcon;
	CCLabelTTF* m_pLabelTTFName;
	CCLabelTTF* m_pLabelTTFDesc;
	CCLabelTTF* m_pLabelTTFExchangeCount;
	CCScrollButton* m_pControlButtonExchange;
    CCScrollButton* m_pControlButtonExchange1;
//    CCLayer* m_pLayerItemButton;

    uint32 m_dwIndex;
//    bool m_touchFlag;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonExchange(CCObject* pSender, CCControlEvent event);

    void loadData(uint32 index);
    void setClipRect(CCRect rect);
};

class CcbArenaShopFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaShopFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaShopFrameLayer);
};


#endif // __CCBARENASHOPFRAMELAYER__H__