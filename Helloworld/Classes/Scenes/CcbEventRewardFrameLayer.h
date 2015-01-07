/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-11 19:09:02
*/

#ifndef __CCBEVENTREWARDFRAMELAYER__H__
#define __CCBEVENTREWARDFRAMELAYER__H__

//CcbEventRewardFrameLayer.h come from ccb/event_reward_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"
#include "CCScrollButton.h"
USING_NS_CC;
USING_NS_CC_EXT;



class CcbEventRewardFrameLayer:
	public cocos2d::CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbEventRewardFrameLayer()
	{
		m_pSpriteGetYet = NULL;
		m_pControlButtonGet = NULL;
		m_pLayerIcon1 = NULL;
		m_pLayerIcon2 = NULL;
		m_pLayerIcon3 = NULL;
		m_pLayerIcon4 = NULL;
		m_pLabelTTFLoginBg = NULL;
		m_pLabelTTFLoginDay = NULL;

        m_LocalTag = 0;
	}
	~CcbEventRewardFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventRewardFrameLayer, create);
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
	CCSprite* m_pSpriteGetYet;
	CCScrollButton* m_pControlButtonGet;
	CCLabelTTF* m_pLabelTTFLoginBg;
	CCLabelTTF* m_pLabelTTFLoginDay;
    CcbItemIconLayer* m_pLayerIcon1;
    CcbItemIconLayer* m_pLayerIcon2;
    CcbItemIconLayer* m_pLayerIcon3;
    CcbItemIconLayer* m_pLayerIcon4;


    vector<CcbItemIconLayer*> arrIcon;
    uint8 m_byType;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    CC_SYNTHESIZE(int, m_LocalTag, LocalTag);

	void onPressControlButtonGet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


    void loadData(uint32 index, uint8 byType);
    void setClipRect(CCRect rect);
};

class CcbEventRewardFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventRewardFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventRewardFrameLayer);
};


#endif // __CCBEVENTREWARDFRAMELAYER__H__