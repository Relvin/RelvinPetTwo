/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-29 17:52:09
*/

#ifndef __CCBARENARESULTWINLAYER__H__
#define __CCBARENARESULTWINLAYER__H__

//CcbArenaResultWinLayer.h come from ccb/arena_result_win.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaResultWinLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CObserverRole
{
public:
	// Constructor
	CcbArenaResultWinLayer()
    : m_pLabelTTFMaxRank(NULL)
    , m_pLabelTTFNums(NULL)
    , m_pNodeShareReward(NULL)
	{
		m_pLayerIcon = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFRank = NULL;
		m_pLabelTTFReputation = NULL;
		m_pLabelTTFCoin = NULL;
		m_pControlButtonExtraReward = NULL;
		m_pLayerScroll_1 = NULL;
		m_pLayerScroll_2 = NULL;
		m_pLayerScroll_3 = NULL;
        m_pLayerRewardParent = NULL;
        m_pControlButtonShare = NULL;

	}
	~CcbArenaResultWinLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaResultWinLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void dwShareCntChanged(uint32 dwShareCnt);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CcbItemIconLayer* m_pLayerIcon;
	CCLabelTTF* m_pLabelTTFName;
	CCLabelTTF* m_pLabelTTFRank;
	CCLabelTTF* m_pLabelTTFReputation;
	CCLabelTTF* m_pLabelTTFCoin;
	CCControlButton* m_pControlButtonExtraReward;
    CCControlButton* m_pControlButtonShare;
	CCLayer* m_pLayerScroll_1;
	CCLayer* m_pLayerScroll_2;
	CCLayer* m_pLayerScroll_3;
    CCLayer* m_pLayerRewardParent;
    CCLabelTTF* m_pLabelTTFMaxRank;
    CCLabelTTF* m_pLabelTTFNums;
    CCNode* m_pNodeShareReward;

    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void onUpdate(float delta);
    void scheduleStopRoll(float cTime);
    void StartRoll();
    void StopRoll();
    void EndRoll();
    void StopScrollView1();
    void StopScrollView2();
    void StopScrollView3();
    void listenToBackFromNotification(CCObject *pObject);
    
    
    struct SHOW_ITEM_INFO
    {
        uint32 dwIndex;
        int sort;
        
        bool operator < (const SHOW_ITEM_INFO &info) const
        {
            return sort < info.sort;
        }
    };
    void RandShowItem();
    vector<SHOW_ITEM_INFO> m_ShowItem[3];
    
    bool m_isStartRoll[3];
    bool m_isEndRoll;
	CCScrollView* m_pScrollView[3];
    CCNode* m_pNodeRewardItem[3];
    
public:
	// Funcitons
    void addGuideLayer();
    
    void onPressControlButtonExtraReward(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonShare(CCObject* pSender, CCControlEvent event);


};

class CcbArenaResultWinLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaResultWinLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaResultWinLayer);
};


#endif // __CCBARENARESULTWINLAYER__H__