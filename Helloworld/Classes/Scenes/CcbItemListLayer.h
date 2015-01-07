/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-26 11:26:05
*/

#ifndef __CCBITEMLISTLAYER__H__
#define __CCBITEMLISTLAYER__H__

//CcbItemListLayer.h come from ccb/item_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ItemDataMgr.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemListLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
,   public CObserverMsg
,   public CObserverRole
{
public:
	// Constructor
	CcbItemListLayer()
	{
        m_pLayerForView = NULL;
        m_pLabelTTFMaxCount = NULL;
        m_pLabelTTFCurCount = NULL;
        m_pLayerDown = NULL;
        m_pControlButtonExpandBag = NULL;
        m_pControlButtonMaterial = NULL;
        m_pControlButtonNormal = NULL;
        m_pLayerUp = NULL;
        m_tableView = NULL;
    
	}
	~CcbItemListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemListLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    //tableView相关}
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void RefeashLayer();
    virtual void dwItemBagCntChanged(uint32 cnt);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerForView;
    cocos2d::CCLabelTTF* m_pLabelTTFMaxCount;
    cocos2d::CCLabelTTF* m_pLabelTTFCurCount;
    cocos2d::CCLayer* m_pLayerDown;
    cocos2d::extension::CCControlButton* m_pControlButtonExpandBag;
    cocos2d::extension::CCControlButton* m_pControlButtonMaterial;
    cocos2d::extension::CCControlButton* m_pControlButtonNormal;
    cocos2d::CCLayer* m_pLayerUp;
    
    cocos2d::extension::CCTableView* m_tableView;
    
    CCRect m_clipRect;
    CCPoint m_offPos;
    //void CreateShowList();
    void CreateTableViewData();
    std::vector<uint32> m_vecShowList;
    uint8 m_curItemType;
    
private:
    static bool cmpItem(uint32 p, uint32 q);
    
private:
    void changeTab();
    void jumpToNeedItem();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


    void onPressControlButtonMaterial(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonNormal(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressButtonExpandBagCallBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void animationFinishCallBack();
public:
	// Funcitons

};

class CcbItemListLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbItemListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbItemListLayer);
};


#endif // __CCBITEMLISTLAYER__H__