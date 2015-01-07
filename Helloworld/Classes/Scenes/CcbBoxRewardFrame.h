/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-18 10:33:18
*/

#ifndef __CCBBOXREWARDFRAME__H__
#define __CCBBOXREWARDFRAME__H__

//CcbBoxRewardFrame.h come from ccb/box_reward_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"
#include "CCScrollButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbBoxRewardFrame:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbBoxRewardFrame()
	{
		m_pLabelTTFTitle = NULL;
		m_pLabelTTFTime = NULL;
		m_pLabelTTFContent = NULL;
        m_pControlbuttonReward = NULL;
        m_pLayerIcon = NULL;
	}
	~CcbBoxRewardFrame();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbBoxRewardFrame, create);
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
public:
	// Attributes for CCB
	cocos2d::CCLabelTTF* m_pLabelTTFTitle;
	cocos2d::CCLabelTTF* m_pLabelTTFTime;
	cocos2d::CCLabelTTF* m_pLabelTTFContent;
    CCScrollButton* m_pControlbuttonReward;
    CcbItemIconLayer* m_pLayerIcon;
    
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

//    CC_SYNTHESIZE(int, m_localTag, LocalTag);
	int m_indexId;
public:
	// Funcitons
    void loadData(int wIndex);
    void setClipRect(CCRect rect);
	void onPressControlButtonReward(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbBoxRewardFrameLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbBoxRewardFrameLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbBoxRewardFrame);
};


#endif // __CCBBOXREWARDFRAME__H__