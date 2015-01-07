/**
* CcbPetFuseLowQualityGetLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-08 15:03:00
*/

#ifndef __CCBPETFUSELOWQUALITYGETLAYER__H__
#define __CCBPETFUSELOWQUALITYGETLAYER__H__

//CcbPetFuseLowQualityGetLayer.h come from ccb/pet_fuse_lowquality.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbItemIconLayer;

class CcbPetFuseLowQualityGetLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetFuseLowQualityGetLayer()
	{
		m_pControlButtonCancel = NULL;
		m_pControlButtonFuse = NULL;
		m_pControlButtonClose = NULL;
		m_pLabelTTFDes = NULL;
		m_pLayerItemIcon_1 = NULL;
		m_pLayerItemIcon_2 = NULL;
		m_pLayerItemIcon_3 = NULL;
		m_pLayerItemIcon_4 = NULL;
        m_pLayerItemIcon_5 = NULL;

	}
	~CcbPetFuseLowQualityGetLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetFuseLowQualityGetLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
	cocos2d::extension::CCControlButton* m_pControlButtonFuse;
	cocos2d::extension::CCControlButton* m_pControlButtonClose;
	cocos2d::CCLabelTTF* m_pLabelTTFDes;
    CcbItemIconLayer* m_pLayerItemIcon_1;
    CcbItemIconLayer* m_pLayerItemIcon_2;
    CcbItemIconLayer* m_pLayerItemIcon_3;
    CcbItemIconLayer* m_pLayerItemIcon_4;
    CcbItemIconLayer* m_pLayerItemIcon_5;

    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void loadData();

	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonFuse(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbPetFuseLowQualityGetLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetFuseLowQualityGetLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetFuseLowQualityGetLayer);
};


#endif // __CCBPETFUSELOWQUALITYGETLAYER__H__