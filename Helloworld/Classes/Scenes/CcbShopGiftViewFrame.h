/**
* shop_giftbag_prerviewframe.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-13 16:38:53
*/

#ifndef __SHOP_GIFTBAG_PRERVIEWFRAME__H__
#define __SHOP_GIFTBAG_PRERVIEWFRAME__H__

//shop_giftbag_prerviewframe.h come from ccb/shop_giftbag_prerviewframe.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "ConfigData.h"

class CcbItemIconLayer;
class CcbShopGiftViewFrame:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbShopGiftViewFrame();
	~CcbShopGiftViewFrame();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShopGiftViewFrame, create);
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
	CcbItemIconLayer* m_pNodeGiftIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFGiftName;
	cocos2d::CCLabelTTF* m_pLabelTTFGiftIntroduce;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void setFrameInfoByItemIndex(ChestConfig::STC_UNITE_RESOURCE &cellItem);

private:
    ChestConfig::STC_UNITE_RESOURCE  m_cellItem;

};

class CcbShopGiftViewFrameLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShopGiftViewFrameLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShopGiftViewFrame);
};


#endif // __SHOP_GIFTBAG_PRERVIEWFRAME__H__