/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 23:00:41
*/

#ifndef __CCBCOUNTRYLAYER__H__
#define __CCBCOUNTRYLAYER__H__

//CcbCountryLayer.h come from ccb/country.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "WorldPacket.h"

#pragma mark CountryCtrl

class CountryCtrl {
    
public:
    static void HanderCountryBaseInfo(WorldPacket& packet);
    static void HandlerFarmUpdate(WorldPacket& packet);

    static bool bCoinBuildOn;
    static bool bFarmersBuildOn;
};

#pragma mark CountryScene

class CountryScene : public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner {
    
public:
    CountryScene() {
//        m_pLabelTTFName = NULL;
    };
    ~CountryScene() {
//        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    };
    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(CountryScene);
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
private:
//    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#pragma mark CountryLayer
#include "Observer.h"

class CcbCountryLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverMsg
{
public:
	// Constructor
	CcbCountryLayer()
	{
		m_pControlButtonMine = NULL;
		m_pControlButtonFarm = NULL;
		m_pControlButtonTree = NULL;
		m_pControlButtonRiver = NULL;
        m_pControlButtonUpgrad = NULL;
//        m_pControlButtonBack = NULL;
        m_pControlButtonCompound = NULL;
        m_pControlButtonShowEquip = NULL;
        m_pControlButtonFuse = NULL;
	}
	~CcbCountryLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbCountryLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonMine;
	cocos2d::extension::CCControlButton* m_pControlButtonFarm;
	cocos2d::extension::CCControlButton* m_pControlButtonTree;
	cocos2d::extension::CCControlButton* m_pControlButtonRiver;
    cocos2d::extension::CCControlButton* m_pControlButtonUpgrad;
//    cocos2d::extension::CCControlButton* m_pControlButtonBack;
    cocos2d::extension::CCControlButton* m_pControlButtonCompound;
    cocos2d::extension::CCControlButton* m_pControlButtonShowEquip;
    cocos2d::extension::CCControlButton* m_pControlButtonFuse;
    void flyToHome(cocos2d::CCNode* pNode);
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void RefeashLayer();
	
public:
	// Funcitons


	void onPressControlButtonMine(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonFarm(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTree(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRiver(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonUpgrad(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//    void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void  onPressControlButtonCompound(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void  onPressControlButtonShowEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void  onPressControlButtonFuse(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbCountryLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbCountryLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbCountryLayer);
};


#endif // __CCBCOUNTRYLAYER__H__