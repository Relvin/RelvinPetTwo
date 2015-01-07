/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-29 17:39:11
*/

#ifndef __CCBEVENTGROWPLANFRAMELAYER__H__
#define __CCBEVENTGROWPLANFRAMELAYER__H__

//CcbEventGrowPlanFrameLayer.h come from ccb/event_grow_plan_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollButton.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class STC_CHANGEABLE_CELL_INFO;

class CcbEventGrowPlanFrameLayer
: public CCLayer
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCNodeLoaderListener
, public CCTableViewDataSource
{
public:
	// Constructor
	CcbEventGrowPlanFrameLayer()
    : m_index(0)
    , m_ClipRect(0,0,0,0)
    , m_pTableView(NULL)
    , m_pChangeableCellInfo(NULL)
	{
		m_pLabelTTFTitle = NULL;
		m_pControlButtonGet = NULL;
		m_pSpriteGetYet = NULL;
        m_pLayerRewardIcon = NULL;
	}
	~CcbEventGrowPlanFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventGrowPlanFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table) ;
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx) ;
    
private:
	
	// Attributes for CCB
	CCLabelTTF* m_pLabelTTFTitle;
	CCScrollButton* m_pControlButtonGet;
	CCSprite* m_pSpriteGetYet;
    CCLayer* m_pLayerRewardIcon;

    int m_index;
    bool m_touchFlag;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
//    CC_SYNTHESIZE(int, m_nLocalTag, LocalTag);

	void onPressControlButtonGet(CCObject* pSender, CCControlEvent event);

    void loadData(int index);
    void setClipRect(CCRect rect);
    
    
private:
    CCRect  m_ClipRect;
    CCTableView* m_pTableView;
    STC_CHANGEABLE_CELL_INFO* m_pChangeableCellInfo;
};

class CcbEventGrowPlanFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventGrowPlanFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventGrowPlanFrameLayer);
};


#endif // __CCBEVENTGROWPLANFRAMELAYER__H__