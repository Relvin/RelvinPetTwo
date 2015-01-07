/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-26 18:22:28
*/

#ifndef __CCBSHOPITEMFRAMELAYER__H__
#define __CCBSHOPITEMFRAMELAYER__H__

//CcbShopItemFrameLayer.h come from ccb/shop_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbItemIconLayer.h"
#include "CCScrollButton.h"
#include "ShopDataMgr.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CcbShopItemFrameLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public ItemIconTouchDelegate
{
public:
	// Constructor
	CcbShopItemFrameLayer()
    : m_nCellIndex(-1)
	{
		m_pControlButtonBuy = NULL;
		m_pLayerIcon = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFText = NULL;
		m_pSpriteState = NULL;
        m_pLabelTTFCanBuyCnt = NULL;
        m_pNodeName1 = NULL;
        m_pNodeName2 = NULL;
        
	}
	~CcbShopItemFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShopItemFrameLayer, create);
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
	CCScrollButton* m_pControlButtonBuy;
	CcbItemIconLayer* m_pLayerIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFText;
	cocos2d::CCSprite* m_pSpriteState;
    cocos2d::CCLabelTTF* m_pLabelTTFCanBuyCnt;
    SHOP_ITEM_INFO m_showInfo;
    cocos2d::CCNode* m_pNodeName1;
    cocos2d::CCNode* m_pNodeName2;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId) ;
public:
	// Funcitons
	void onPressControlButtonBuy(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    CC_SYNTHESIZE(int, m_nCellIndex, CellIndex);

public:
    void loadData(SHOP_ITEM_INFO showInfo);
    
    void setClipRect(CCRect rect);
    
};

class CcbShopItemFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShopItemFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShopItemFrameLayer);
};


#endif // __CCBSHOPITEMFRAMELAYER__H__