/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-29 10:10:43
*/

#ifndef __CCBCHALLENGEMAPLAYER__H__
#define __CCBCHALLENGEMAPLAYER__H__

//CcbChallengeMapLayer.h come from ccb/pavilion_map.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbChallengeOverRewardLayer.h"
#include "CcbChallengeLayer.h"
#include "SystemMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbChallengeMapLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
    
    static CCScene* scene();
	// Constructor
	CcbChallengeMapLayer()
	{
        m_pControlButtonReset = NULL;
        m_pControlButton_Go = NULL;
        m_pLabelTTFName = NULL;
        m_pControlButtonBack = NULL;
        m_pControlButtonReward = NULL;
        m_pNodeRule = NULL;
        m_pControlButtonRule = NULL;
        m_pControlButtonWeather = NULL;
        m_pSpriteTip = NULL;
        m_pNodeWeather = NULL;
        m_pSpriteWeather = NULL;
        m_pLabelTTFW_1 = NULL;
        m_pLabelTTFW_2 = NULL;
        m_pLabelTTFW_3 = NULL;
        m_pLabelTTFW_4 = NULL;
        m_pLabelTTFW_5 = NULL;
        m_pLabelTTFW_6 = NULL;
        
        m_pScale9SpriteWeather = NULL;
        m_curScene = NULL;
        m_chalLayer = NULL;
        m_rewardLayer = NULL;
        
	}
	~CcbChallengeMapLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeMapLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::extension::CCControlButton* m_pControlButtonReset;
    cocos2d::extension::CCControlButton* m_pControlButton_Go;
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    cocos2d::extension::CCControlButton* m_pControlButtonBack;
    cocos2d::extension::CCControlButton* m_pControlButtonReward;
    cocos2d::CCNode* m_pNodeRule;
    cocos2d::extension::CCControlButton* m_pControlButtonRule;
    cocos2d::extension::CCControlButton* m_pControlButtonWeather;
    cocos2d::CCSprite* m_pSpriteTip;
    cocos2d::CCNode* m_pNodeWeather;
    cocos2d::CCSprite* m_pSpriteWeather;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteWeather;
    cocos2d::CCLabelTTF* m_pLabelTTFW_1;
    cocos2d::CCLabelTTF* m_pLabelTTFW_2;
    cocos2d::CCLabelTTF* m_pLabelTTFW_3;
    cocos2d::CCLabelTTF* m_pLabelTTFW_4;
    cocos2d::CCLabelTTF* m_pLabelTTFW_5;
    cocos2d::CCLabelTTF* m_pLabelTTFW_6;
    
    static CcbChallengeMapLayer* m_curScene;
    CcbChallengeOverRewardLayer * m_rewardLayer;
    CcbChallengeLayer* m_chalLayer;

    std::vector<CCPoint> arrPoint;
    std::vector<CCLabelTTF*> arrWdes;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


public:
    static CcbChallengeMapLayer* getCurScene(){return m_curScene;};
    void loadData();
    
    void reflash();
    void handlerUpdateBuff();
private:
    void showEff();
    void showChalLayer();
    
    void addGuideLayer();
    void setWeatherLbl(uint8 weather);
public:

    void onPressControlButtonReset(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonLevel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonReward(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonRule(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonWeather(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    

};

class CcbChallengeMapLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeMapLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeMapLayer);
};


#endif // __CCBCHALLENGEMAPLAYER__H__