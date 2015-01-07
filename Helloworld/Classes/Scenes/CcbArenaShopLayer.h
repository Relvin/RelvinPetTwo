/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-14 14:32:45
*/

#ifndef __CCBARENASHOPLAYER__H__
#define __CCBARENASHOPLAYER__H__

//CcbArenaShopLayer.h come from ccb/arena_shop.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaShopLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbArenaShopLayer()
	{
		m_pLayerViewSize = NULL;
		m_pLabelTTF1 = NULL;
		m_pLabelTTFReputation = NULL;
        m_pLayerReputation = NULL;
        m_pLayerTop = NULL;
        m_pLayerBottom = NULL;
        m_tableView = NULL;
	}
	~CcbArenaShopLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaShopLayer, create);
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
    
    virtual void RefeashLayer();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCLayer* m_pLayerViewSize;
	CCLabelTTF* m_pLabelTTF1;
	CCLabelTTF* m_pLabelTTFReputation;
    CCLayer* m_pLayerReputation;
    CCLayer* m_pLayerTop;
    CCLayer* m_pLayerBottom;

    CCTableView *m_tableView;
    CCRect m_clipRect;
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
};

class CcbArenaShopLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaShopLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaShopLayer);
};


#endif // __CCBARENASHOPLAYER__H__