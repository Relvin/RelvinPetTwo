/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-25 15:05:40
*/

#ifndef __CCBEVOINFOLISTLAYER__H__
#define __CCBEVOINFOLISTLAYER__H__

//CcbEvoInfoListLayer.h come from ccb/evo_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


class CcbEvoInfoListLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbEvoInfoListLayer()
    : m_pTableView(NULL)
	{
		m_pLayerList = NULL;
		m_pControlButtonBack = NULL;
		m_pLabelTTFEvoLv = NULL;

	}
	~CcbEvoInfoListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEvoInfoListLayer, create);
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
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerList;
	cocos2d::extension::CCControlButton* m_pControlButtonBack;
	cocos2d::CCLabelTTF* m_pLabelTTFEvoLv;


    std::vector<uint16> arrEvolveId;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


    void loadData();
    
private:
    cocos2d::extension::CCTableView* m_pTableView;

};

class CcbEvoInfoListLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEvoInfoListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEvoInfoListLayer);
};


#endif // __CCBEVOINFOLISTLAYER__H__