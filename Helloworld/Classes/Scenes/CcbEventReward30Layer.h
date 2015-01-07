/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-12 13:58:44
*/

#ifndef __CCBEVENTREWARD30LAYER__H__
#define __CCBEVENTREWARD30LAYER__H__

//CcbEventReward30Layer.h come from ccb/event_reward_30.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEventReward30Layer:
	public cocos2d::CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbEventReward30Layer()
	{
        m_pLayerEventViewSize = NULL;
        m_pControlButtonClose = NULL;
        m_tableView = NULL;
	}
	~CcbEventReward30Layer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventReward30Layer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void RefeashLayer();
    
    //tableView相关}
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerEventViewSize;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    
    CCTableView* m_tableView;

    CCRect m_clitRect;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

private:
    void loadData();
	
public:
	// Funcitons
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbEventReward30LayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventReward30LayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventReward30Layer);
};


#endif // __CCBEVENTREWARD30LAYER__H__