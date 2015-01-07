/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-29 10:11:21
*/

#ifndef __CCBCHALLENGEOVERREWARDLAYER__H__
#define __CCBCHALLENGEOVERREWARDLAYER__H__

//CcbChallengeOverRewardLayer.h come from ccb/pavilion_rewardlist.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemIconLayer;

class CcbChallengeOverRewardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbChallengeOverRewardLayer()
	{
        m_pLayerIcon_1 = NULL;
        m_pLayerIcon_3 = NULL;
        m_pLayerIcon_2 = NULL;
        m_pLayerIcon_4 = NULL;
        m_pControlButtonGetReward = NULL;
        m_pControlButtonClose = NULL;
        m_pSpriteGetYet = NULL;

	}
	~CcbChallengeOverRewardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeOverRewardLayer, create);
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
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    CcbItemIconLayer* m_pLayerIcon_1;
    CcbItemIconLayer* m_pLayerIcon_3;
    CcbItemIconLayer* m_pLayerIcon_2;
    CcbItemIconLayer* m_pLayerIcon_4;
    cocos2d::CCSprite* m_pSpriteGetYet;
    cocos2d::extension::CCControlButton* m_pControlButtonGetReward;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    
    std::vector<CcbItemIconLayer*> arrItem;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


    void onPressControlButtonGetReward(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    
    void loadData();

};

class CcbChallengeOverRewardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeOverRewardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeOverRewardLayer);
};


#endif // __CCBCHALLENGEOVERREWARDLAYER__H__