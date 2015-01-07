/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 14:37:42
*/

#ifndef __CCBARENAINDEXLAYER__H__
#define __CCBARENAINDEXLAYER__H__

//CcbArenaIndexLayer.h come from ccb/arena_index.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaIndexLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverMsg
{
public:
	// Constructor
	CcbArenaIndexLayer()
	{
        m_pControlButtonRank = NULL;
		m_pControlButtonTeam = NULL;
		m_pControlButtonReportBack = NULL;
		m_pControlButtonReport = NULL;
		m_pControlButtonBattle = NULL;
		m_pControlButtonExchange = NULL;
        m_pControlButtonBack = NULL;
		m_pLayerArenaReward = NULL;
        m_pLayerMyInfo = NULL;
        m_pLayerMyInfoParent = NULL;
        
        m_curScene = NULL;
        m_dwLeftTime = 0;
	}
	~CcbArenaIndexLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaIndexLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void RefeashLayer();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    CCControlButton* m_pControlButtonRank;
	CCControlButton* m_pControlButtonTeam;
	CCControlButton* m_pControlButtonReportBack;
	CCControlButton* m_pControlButtonReport;
	CCControlButton* m_pControlButtonBattle;
	CCControlButton* m_pControlButtonExchange;
    CCControlButton* m_pControlButtonBack;
	CCLayer* m_pLayerArenaReward;
    CCLayer* m_pLayerMyInfo;
    CCLayer* m_pLayerMyInfoParent;
    
    void addGuideLayer();
    
    static CcbArenaIndexLayer* m_curScene;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    static CcbArenaIndexLayer* getCurScene(){
        return m_curScene;
    };
    void onUpdate(float delta);
    bool InitData();
    bool NotifyErrorMsg(uint16 wErrorNo);
	
    uint32 m_dwLeftTime;
public:
	// Funcitons
	void onPressControlButtonRank(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonTeam(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonReportBack(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonReport(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonBattle(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonExchange(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonBack(CCObject* pSender, CCControlEvent event);
};

class CcbArenaIndexLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaIndexLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaIndexLayer);
};


#endif // __CCBARENAINDEXLAYER__H__