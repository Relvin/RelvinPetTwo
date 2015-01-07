/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-24 17:49:26
*/

#ifndef __CCBSHOPNORMALLISTLAYER__H__
#define __CCBSHOPNORMALLISTLAYER__H__

//CcbShopNormalListLayer.h come from ccb/shop_normal_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ShopDataMgr.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbShopNormalListLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbShopNormalListLayer()
	{
		m_pControlButtonReduced = NULL;
		m_pControlButtonNormal = NULL;
		m_pLayerNormalList = NULL;
        m_pTableViewTabNormal = NULL;
        
        m_pLayerParent = NULL;
        
	}
	~CcbShopNormalListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShopNormalListLayer, create);
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
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCControlButton* m_pControlButtonNormal;
	CCControlButton* m_pControlButtonReduced;
    
	CCLayer* m_pLayerNormalList;
    CCLayer* m_pLayerParent;
    
    CCTableView* m_pTableViewTabNormal;

    CCRect m_clipRect;
    int m_nCurShowTab;
    VEC_SHOP_ITEM_INFO m_vecShowList[2];
    void CreateShowList();
    
    void jumpToNeedItem();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

   
    //重新刷界面}
	virtual void RefeashLayer();
public:
	// Funcitons
	void onPressControlButtonNormal(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonReduced(CCObject* pSender, CCControlEvent event);
    


};

class CcbShopNormalListLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShopNormalListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShopNormalListLayer);
};


#endif // __CCBSHOPNORMALLISTLAYER__H__