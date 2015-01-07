/**
* CcbEventAnnounceFrame.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-12-04 17:16:04
*/

#ifndef __CCBEVENTANNOUNCEFRAME__H__
#define __CCBEVENTANNOUNCEFRAME__H__

//CcbEventAnnounceFrame.h come from ccb/event_announce_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EventDataMgr.h"
#include "ReCountDown.h"

class CcbEventAnnounceFrame:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public ReCountDownDelegate
{
public:
	// Constructor
	CcbEventAnnounceFrame()
	{
        m_pLabelTTFDesText = NULL;
        m_pLabelTTFDesTitle = NULL;
        m_pLabelTTFTime = NULL;
        m_pNodeTitle = NULL;
        m_pLayerDes = NULL;
        m_pLabelTTFFuliTitle = NULL;
        m_pLabelTTFFuliText = NULL;
        m_pLayerFuli = NULL;
        m_pScale9Sprite_bg = NULL;
        m_pCountDown = NULL;

	}
	~CcbEventAnnounceFrame();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventAnnounceFrame, create);
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
    cocos2d::CCLabelTTF* m_pLabelTTFDesText;
    cocos2d::CCLabelTTF* m_pLabelTTFDesTitle;
    cocos2d::CCLabelTTF* m_pLabelTTFTime;
    cocos2d::CCNode* m_pNodeTitle;
    cocos2d::CCLayer* m_pLayerDes;
    cocos2d::CCLabelTTF* m_pLabelTTFFuliTitle;
    cocos2d::CCLabelTTF* m_pLabelTTFFuliText;
    cocos2d::CCLayer* m_pLayerFuli;
    cocos2d::extension::CCScale9Sprite* m_pScale9Sprite_bg;

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

    float loadData(STC_EVENT_ANNOUNCE_INFO annInfo);

private:
    ReCountDown* m_pCountDown;


};

class CcbEventAnnounceFrameLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventAnnounceFrameLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventAnnounceFrame);
};


#endif // __CCBEVENTANNOUNCEFRAME__H__