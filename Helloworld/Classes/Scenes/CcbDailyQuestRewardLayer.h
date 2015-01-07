/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-04 11:38:53
*/

#ifndef __CCBDAILYQUESTREWARDLAYER__H__
#define __CCBDAILYQUESTREWARDLAYER__H__

//CcbDailyQuestRewardLayer.h come from ccb/dailyquest_reward.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "TaskDataMgr.h"
#include "Observer.h"
#include <map>
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

struct DAILY_QUEST_SHOW_INFO
{
    DAILY_QUEST_INFO info;
    DAILY_QUEST_CONFIG config;
};

class CcbDailyQuestRewardLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CCTableViewDelegate
,   public CObserverMsg
{
public:
	// Constructor
	CcbDailyQuestRewardLayer()
    : m_pCurButton(NULL)
    , m_SpriteBarSize(0,0)
	{
		m_pLabelTTFExtraAward = NULL;
		m_pLayerList = NULL;
		m_pLabelTTFProcess = NULL;
		m_pSpriteBar = NULL;
		m_pLabelTTFCompleteCount = NULL;
        m_pLayerTop = NULL;
        m_pLayerTop2 = NULL;
        m_pLayerBottom = NULL;
        m_tableView = NULL;
        m_pNodeScoreBox = NULL;
        m_pNodeScore = NULL;
        m_pConrtolButtonDailyquest = NULL;
        m_pConrtolButtonAchieve = NULL;
        m_pLabelTTFJifen = NULL;
        m_pSpriteDailyquesttip = NULL;
        m_pSpriteAchievetip = NULL;
        m_pSpriteSelectframe = NULL;
        
	}
	~CcbDailyQuestRewardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbDailyQuestRewardLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    //tableView相关}
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) {};
    
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    static bool compare(const DAILY_QUEST_SHOW_INFO &p,const DAILY_QUEST_SHOW_INFO &q);
    static bool compare1(const DAILY_QUEST_SHOW_INFO &p,const DAILY_QUEST_SHOW_INFO &q);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCLabelTTF* m_pLabelTTFExtraAward;
	CCLayer* m_pLayerList;
	CCLabelTTF* m_pLabelTTFProcess;
	CCSprite* m_pSpriteBar;
	CCLabelTTF* m_pLabelTTFCompleteCount;
    CCTableView *m_tableView;
    CCLayer* m_pLayerTop;
    CCLayer* m_pLayerTop2;
    CCLayer* m_pLayerBottom;
    CCRect m_clitRect;
    CCNode* m_pNodeScoreBox;
    CCNode* m_pNodeScore;
    CCControlButton* m_pConrtolButtonDailyquest;
    CCControlButton* m_pConrtolButtonAchieve;
    CCLabelTTF* m_pLabelTTFJifen;
    CCSprite* m_pSpriteDailyquesttip;
    CCSprite* m_pSpriteAchievetip;
    CCSprite* m_pSpriteSelectframe;
    
    
    int m_nCompleteCount;
    vector<DAILY_QUEST_SHOW_INFO> m_vecDailyQuestShowList;
    void CreateDailyQuestList();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

	virtual void RefeashLayer();
    void setLayerInfoByTab(uint8 byType);
public:
	// Funcitons
    void onPressConrtolButtonDailyCallBack(CCObject* pObject, CCControlEvent event);
    void onPressControlButtonBox(CCObject* pObject, CCControlEvent event);
private:
    CCControlButton *m_pCurButton;
    CCNode* m_pNodeParticle[3];
    CCSize  m_SpriteBarSize;
    uint8   m_byCurType;

};

class CcbDailyQuestRewardLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbDailyQuestRewardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbDailyQuestRewardLayer);
};


#endif // __CCBDAILYQUESTREWARDLAYER__H__