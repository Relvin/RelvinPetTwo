/**
* CcbGrowPlanTitleLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-12-09 10:24:33
*/

#ifndef __CCBGROWPLANTITLELAYER__H__
#define __CCBGROWPLANTITLELAYER__H__

//CcbGrowPlanTitleLayer.h come from ccb/event_reward_type.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ReCountDown.h"


class CcbGrowPlanTitleLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public ReCountDownDelegate
{
public:
	// Constructor
    CcbGrowPlanTitleLayer();
	
	~CcbGrowPlanTitleLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGrowPlanTitleLayer, create);
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
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteTopType;
	cocos2d::CCLabelTTF* m_pLabelTTFInfo;
	cocos2d::CCLabelTTF* m_pLabelTTFTime;
	cocos2d::CCNode* m_pNodeRewardType;
	cocos2d::extension::CCControlButton* m_pControlButtonBuy;
	cocos2d::CCNode* m_pNodeGrowPlan;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    virtual void countDownScheduleCallBack(float cTime,CountType type);

	
public:
	// Funcitons
	void onPressControlButtonBuy(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    //self Functions
    void setShowInfo();

private:
    ReCountDown* m_pCountDown;
    
};

class CcbGrowPlanTitleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGrowPlanTitleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGrowPlanTitleLayer);
};


#endif // __CCBGROWPLANTITLELAYER__H__