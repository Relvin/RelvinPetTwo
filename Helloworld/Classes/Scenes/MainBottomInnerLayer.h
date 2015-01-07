/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-02 20:45:14
*/

#ifndef __MAINBOTTOMINNERLAYER__H__
#define __MAINBOTTOMINNERLAYER__H__

//MainBottomInnerLayer.h come from ccb/bottom_btns.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainBottomInnerLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverRole
{
public:
	// Constructor
	MainBottomInnerLayer()
	{
		m_pControlButtonHome = NULL;
		m_pControlButtonTeam = NULL;
		m_pControlButtonActive = NULL;
		m_pControlButtonArena = NULL;
		m_pControlButtonGacha = NULL;
		m_pControlButtonShop = NULL;
		m_pSpriteNumHome = NULL;
		m_pSpriteNumPet = NULL;
		m_pSpriteNumActiveMap = NULL;
		m_pSpriteNumArena = NULL;
		m_pSpriteNumGacha = NULL;
		m_pSpriteNumShop = NULL;
        m_bCanTouchBtn = false;
	}
	~MainBottomInnerLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainBottomInnerLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    static MainBottomInnerLayer* GetInstance();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonHome;
	cocos2d::extension::CCControlButton* m_pControlButtonTeam;
	cocos2d::extension::CCControlButton* m_pControlButtonActive;
	cocos2d::extension::CCControlButton* m_pControlButtonArena;
	cocos2d::extension::CCControlButton* m_pControlButtonGacha;
	cocos2d::extension::CCControlButton* m_pControlButtonShop;
	cocos2d::CCSprite* m_pSpriteNumHome;
	cocos2d::CCSprite* m_pSpriteNumPet;
	cocos2d::CCSprite* m_pSpriteNumActiveMap;
	cocos2d::CCSprite* m_pSpriteNumArena;
	cocos2d::CCSprite* m_pSpriteNumGacha;
	cocos2d::CCSprite* m_pSpriteNumShop;

    CCPoint m_pStart;
    
    enum {
        kMain = 0,
        kUnit,
        kYiji,
        kArena,
        kGacha,
        kShop,
    };
    std::vector<CCSprite*> m_vecTips;
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
    virtual void byNotiUnitChanged(uint8 byNotiUnit);
    virtual void byNotiGachaChanged(uint8 byNotiGacha);
    virtual void byNotiShopChanged(uint8 byNotiShop);

    void setBtnTouchEnable(bool _flag) {
        m_bCanTouchBtn = _flag;
    }
public:
	// Funcitons
	void onPressControlButtonHome(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTeam(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonActive(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonArena(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonGacha(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonShop(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    // touch delegate
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

class MainBottomInnerLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainBottomInnerLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainBottomInnerLayer);
};


#endif // __MAINBOTTOMINNERLAYER__H__