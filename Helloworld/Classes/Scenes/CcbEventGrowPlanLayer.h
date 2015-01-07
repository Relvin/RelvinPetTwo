/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-29 17:39:11
*/

#ifndef __CCBEVENTGROWPLANLAYER__H__
#define __CCBEVENTGROWPLANLAYER__H__

//CcbEventGrowPlanLayer.h come from ccb/event_grow_plan.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class STC_EVENT_CHANGEABLE_INFO;
class CcbGrowPlanTitleLayer;
class CcbEventGrowPlanLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbEventGrowPlanLayer()
    : m_pChangeableInfo(NULL)
    , m_pGrowPlanTitleLayer(NULL)
    , m_pSpriteBgType(NULL)
	{
		m_pControlButtonBuy = NULL;
		m_pControlButtonRecharge = NULL;
		m_pLayerViewSize = NULL;
        m_tableView = NULL;
        m_pLabelTTFText = NULL;
        m_pLayerTop = NULL;
        m_pLayerBottom = NULL;
        m_pLayerTopType = NULL;
        m_bFirstLoad = true;
	}
	~CcbEventGrowPlanLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventGrowPlanLayer, create);
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
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
	// Attributes for CCB
	CCControlButton* m_pControlButtonBuy;
	CCControlButton* m_pControlButtonRecharge;
	CCLayer* m_pLayerViewSize;
    CCTableView* m_tableView;
    CCLabelTTF* m_pLabelTTFText;
    CCLayer* m_pLayerTop;
    CCLayer* m_pLayerBottom;
    CCLayer* m_pLayerTopType;
    CcbGrowPlanTitleLayer* m_pGrowPlanTitleLayer;
    CCSprite* m_pSpriteBgType;
    
    CCRect m_clipRect;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons


	void onPressControlButtonBuy(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonRecharge(CCObject* pSender, CCControlEvent event);

private:
    STC_EVENT_CHANGEABLE_INFO* m_pChangeableInfo;
    bool m_bFirstLoad;
};

class CcbEventGrowPlanLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventGrowPlanLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventGrowPlanLayer);
};


#endif // __CCBEVENTGROWPLANLAYER__H__