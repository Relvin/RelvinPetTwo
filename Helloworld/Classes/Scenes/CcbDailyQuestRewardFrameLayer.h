/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-04 11:38:53
*/

#ifndef __CCBDAILYQUESTREWARDFRAMELAYER__H__
#define __CCBDAILYQUESTREWARDFRAMELAYER__H__

//CcbDailyQuestRewardFrameLayer.h come from ccb/dailyquest_reward_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbDailyQuestRewardFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
    typedef enum _RewardType
    {
        ENUM_NONE = 0,
        ENUM_DAILYREWARD = 1,
        ENUM_ACHIEVEREWARD = 2,
        
    } E_RewardType;
    
    enum _buttonStatus
    {
        E_NONE = 0,
        E_CANGET = 1,
        E_GOT = 2,
    };
	// Constructor
	CcbDailyQuestRewardFrameLayer()
    : m_byRewardType(ENUM_NONE)
    , m_nShowType(0)
	{
		m_pSpriteIcon = NULL;
		m_pControlButtonReward = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFReward = NULL;
        m_pSpriteFinish = NULL;
        m_pLabelTTFSchedule = NULL;
        m_pLabelTTFRewardNum = NULL;
        m_pLabelTTFScheduleValue = NULL;
        m_vecPot.clear();
        
	}
	~CcbDailyQuestRewardFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbDailyQuestRewardFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    void setSchedulerLabelState(ccColor3B color);
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
    CCLabelTTF* m_pLabelTTFSchedule;
    CCLabelTTF* m_pLabelTTFRewardNum;
    CCLabelTTF* m_pLabelTTFScheduleValue;

    CC_SYNTHESIZE(uint32, m_dwIndex, Index);
    CC_SYNTHESIZE(uint8, m_byRewardType, RewardType);
    CC_SYNTHESIZE(std::string, m_strNextSceneTag, NextSeneTag);
    CC_SYNTHESIZE(uint8, m_byStatus, Status);
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
    void CreateData(uint32 dwIndex);
    void setRewardButtonStatus(int status);
    void updateRewardButtonStatus();
private:
    uint32 m_nShowType;
    std::vector<cocos2d::CCPoint> m_vecPot;

};

class CcbDailyQuestRewardFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbDailyQuestRewardFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbDailyQuestRewardFrameLayer);
};


#endif // __CCBDAILYQUESTREWARDFRAMELAYER__H__