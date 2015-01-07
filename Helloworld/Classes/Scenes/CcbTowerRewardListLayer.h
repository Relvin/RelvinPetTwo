/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-16 10:53:35
*/

#ifndef __CCBTOWERREWARDLISTLAYER__H__
#define __CCBTOWERREWARDLISTLAYER__H__

//CcbTowerRewardListLayer.h come from ccb/climbtower_boxlist.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class CcbTowerRewardListLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
{
public:
	// Constructor
	CcbTowerRewardListLayer()
	{
		m_pLayerViewSize = NULL;
		m_pControlButtonClose = NULL;
        m_tableView = NULL;
	}
	~CcbTowerRewardListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTowerRewardListLayer, create);
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
	CCLayer* m_pLayerViewSize;
	CCControlButton* m_pControlButtonClose;

    CCTableView* m_tableView;
    
    void CreateShowList();
    
    struct STC_SHOW_LIST
    {
        uint16 wIndex;
        uint32 dwRewardID[4];
        uint32 dwRewardCount[4];
    };
    vector<STC_SHOW_LIST> m_vecShowList;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();



public:
	// Funcitons


	void onPressControlButtonClose(CCObject* pSender, CCControlEvent event);



};

class CcbTowerRewardListLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTowerRewardListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTowerRewardListLayer);
};


#endif // __CCBTOWERREWARDLISTLAYER__H__