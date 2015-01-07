/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-04 11:38:53
*/

#ifndef __CCBACHIEVEREWARDFRAMELAYER__H__
#define __CCBACHIEVEREWARDFRAMELAYER__H__

//CcbAchieveRewardFrameLayer.h come from ccb/achieve_reward_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbAchieveRewardFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbAchieveRewardFrameLayer()
	{
		m_pSpriteIcon = NULL;
		m_pControlButtonReward = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFReward = NULL;
        m_pSpriteFinish = NULL;
        
	}
	~CcbAchieveRewardFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbAchieveRewardFrameLayer, create);
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
public:
	// Attributes for CCB
	CCSprite* m_pSpriteIcon;
	CCControlButton* m_pControlButtonReward;
	CCLabelTTF* m_pLabelTTFName;
	CCLabelTTF* m_pLabelTTFReward;
    CCSprite* m_pSpriteFinish;
    
    CC_SYNTHESIZE(int, m_nShowType, ShowType);
    CC_SYNTHESIZE(uint32, m_dwIndex, Index);
    void CreateData(uint32 dwIndex);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
public:
	// Funcitons


	void onPressControlButtonReward(CCObject* pSender, CCControlEvent event);



};

class CcbAchieveRewardFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbAchieveRewardFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbAchieveRewardFrameLayer);
};


#endif // __CCBACHIEVEREWARDFRAMELAYER__H__