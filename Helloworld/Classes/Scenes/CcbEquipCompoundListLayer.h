/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-18 15:54:03
*/

#ifndef __CCBEQUIPCOMPOUNDLISTLAYER__H__
#define __CCBEQUIPCOMPOUNDLISTLAYER__H__

//CcbEquipCompoundListLayer.h come from ccb/equip_compound_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Equip.h"
#include "Item.h"
#include "Rune.h"
#include "EquipDataMgr.h"
#include "CCScrollViewWithBar.h"

//enum SHOW_TAB_TYPE
//{
//    SHOW_TAB_EQUIP = 0,
//    SHOW_TAB_ITEM = 1,
//    SHOW_TAB_RUNE = 2,
//};

class CcbEquipCompoundListLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CCTableViewDelegate
{
public:
	// Constructor
	CcbEquipCompoundListLayer()
	{
		m_pControlButtonType1 = NULL;
		m_pControlButtonType2 = NULL;
		m_pControlButtonType3 = NULL;
		m_pControlButtonType4 = NULL;
		m_pControlButtonType5 = NULL;
		m_pLayerEquipBg = NULL;
		m_pLayerParent = NULL;
        m_tableView = NULL;
        
	}
	~CcbEquipCompoundListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipCompoundListLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    
//    void addGuideLayer();
public:
	CCControlButton* m_pControlButtonType1;
	CCControlButton* m_pControlButtonType2;
	CCControlButton* m_pControlButtonType3;
	CCControlButton* m_pControlButtonType4;
	CCControlButton* m_pControlButtonType5;
	CCLayer* m_pLayerEquipBg;
	CCLayer* m_pLayerParent;
    CCTableView *m_tableView;
    CCRect m_clipRect;
    //tableView相关}
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) {};
    
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


public:
	// Funcitons
    vector<uint32> m_vecRuneList[5];
    
    void CreateRunesList();
    void ChangeTab();
    
    SHOW_TAB_TYPE m_emShowTabType;
    
	void onPressControlButtonType1(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonType2(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonType3(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonType4(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonType5(CCObject* pSender, CCControlEvent event);

};

class CcbEquipCompoundListLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipCompoundListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipCompoundListLayer);
};

#endif // __CCBEQUIPCOMPOUNDLISTLAYER__H__