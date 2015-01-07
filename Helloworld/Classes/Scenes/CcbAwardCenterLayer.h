/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-04 11:38:53
*/

#ifndef __CCBAWARDCENTERLAYER__H__
#define __CCBAWARDCENTERLAYER__H__

//CcbAwardCenterLayer.h come from ccb/award_center.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

class CcbAwardCenterLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbAwardCenterLayer()
	{
        //m_pControlButtonClose = NULL;
		m_pControlButtonSystemAward = NULL;
		m_pControlButtonAchieve = NULL;
		m_pControlButtonDailyQuest = NULL;
        m_pControlButtonExchangeCode = NULL;
		m_pSpriteCount1 = NULL;
		m_pSpriteCount2 = NULL;
		m_pSpriteCount3 = NULL;

	}
	~CcbAwardCenterLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbAwardCenterLayer, create);
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
	CCControlButton* m_pControlButtonSystemAward;
	CCControlButton* m_pControlButtonAchieve;
	CCControlButton* m_pControlButtonDailyQuest;
    CCControlButton* m_pControlButtonExchangeCode;
	CCSprite* m_pSpriteCount1;
	CCSprite* m_pSpriteCount2;
	CCSprite* m_pSpriteCount3;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
	void onPressControlButtonSystemAward(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonAchieve(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonDailyQuest(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonExchangeCode(CCObject* pSender, CCControlEvent event);
};

class CcbAwardCenterLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbAwardCenterLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbAwardCenterLayer);
};


#endif // __CCBAWARDCENTERLAYER__H__