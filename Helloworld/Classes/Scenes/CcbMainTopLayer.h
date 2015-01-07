/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-25 16:36:45
*/

#ifndef __CCBMAINTOPLAYER__H__
#define __CCBMAINTOPLAYER__H__

//CcbMainTopLayer.h come from ccb/top3.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

class CcbMainTopLayer:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverRole
{
public:
	// Constructor
	CcbMainTopLayer()
	{
		m_pControlButtonActive = NULL;
		m_pSpriteActiveNum = NULL;
		m_pControlButtonReward = NULL;
		m_pSpriteSysRewardNum = NULL;
        m_pControlButtonMystery = NULL;
        m_pSpriteMysteryNum = NULL;
        m_pControlButtonAchieve = NULL;
        m_pSpriteAchieveNum = NULL;
        m_pControlButtonDailyquest = NULL;
        m_pSpriteDailyquestNum = NULL;
        m_pControlButtonEvent7 = NULL;
        m_pSpriteEvent7Num = NULL;
        m_pControlButtonEvent30 = NULL;
        m_pSpriteEvent30Num = NULL;
	}
	~CcbMainTopLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbMainTopLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonActive;
	cocos2d::CCSprite* m_pSpriteActiveNum;
	cocos2d::extension::CCControlButton* m_pControlButtonReward;
	cocos2d::CCSprite* m_pSpriteSysRewardNum;
    cocos2d::extension::CCControlButton* m_pControlButtonMystery;
    cocos2d::CCSprite* m_pSpriteMysteryNum;
    cocos2d::extension::CCControlButton* m_pControlButtonAchieve;
    cocos2d::CCSprite* m_pSpriteAchieveNum;
    cocos2d::extension::CCControlButton* m_pControlButtonDailyquest;
    cocos2d::CCSprite* m_pSpriteDailyquestNum;
    cocos2d::extension::CCControlButton* m_pControlButtonEvent7;
    cocos2d::CCSprite* m_pSpriteEvent7Num;
    cocos2d::extension::CCControlButton* m_pControlButtonEvent30;
    cocos2d::CCSprite* m_pSpriteEvent30Num;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void setOpacity(GLubyte opacity);
	
public:
	// Funcitons
	void onPressControlButtonActive(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonReward(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonMystery(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAchieve(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonDailyquest(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEvent7(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEvent30(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    virtual void byNotiActiveChanged(uint8 byNotiActive);
    virtual void byNotiAwardChanged(uint8 byNotiAward);
    virtual void byNotiMysteryChanged(uint8 byNotiMystery);
    virtual void bySevenRewStatusChanged(uint8 bySevenRewStatus);
    virtual void byThirtyRewStatusChanged(uint8 byThirtyRewStatus);
private:
    void showEff();
};

class CcbMainTopLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbMainTopLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbMainTopLayer);
};


#endif // __CCBMAINTOPLAYER__H__