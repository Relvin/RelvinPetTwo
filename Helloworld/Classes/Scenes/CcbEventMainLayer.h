/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-11 19:09:02
*/

#ifndef __CCBEVENTMAINLAYER__H__
#define __CCBEVENTMAINLAYER__H__

//CcbEventMainLayer.h come from ccb/event_main.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollViewWithBar.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEventMainLayer:
	public cocos2d::CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CCTableViewDelegate
,   public CObserverMsg
{
public:
	// Constructor
	CcbEventMainLayer()
    : _firstRechargeLayer(NULL)
    , _growPlanLayer(NULL)
    , _reward30Layer(NULL)
    , _reward7Layer(NULL)
    , _recoverEngeryLayer(NULL)
    , _mySteryShopLayer(NULL)
	{
		m_pLayerEventPos = NULL;
		m_pLayerTitleViewSize = NULL;
        m_pLayerTitleParent = NULL;
        m_pTableView = NULL;
	}
	~CcbEventMainLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventMainLayer, create);
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
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCLayer* m_pLayerEventPos;
	CCLayer* m_pLayerTitleViewSize;
	CCLayer* m_pLayerTitleParent;
    CCTableView* m_pTableView;

    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    virtual void RefeashLayer();

    void ChangeEvent();
    CCRect m_clipRect;

private:
   
    CCNode*     _firstRechargeLayer;
    CCNode*     _growPlanLayer;
    CCNode*     _reward30Layer;
    CCNode*     _reward7Layer;
    CCNode*     _recoverEngeryLayer;
    CCNode*     _mySteryShopLayer;

    void removeLoading();
};

class CcbEventMainLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventMainLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventMainLayer);
};


#endif // __CCBEVENTMAINLAYER__H__