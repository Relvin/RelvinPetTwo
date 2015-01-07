/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-29 15:46:04
*/

#ifndef __CCBSHOWGETLAYER__H__
#define __CCBSHOWGETLAYER__H__

//CcbShowGetLayer.h come from ccb/reward_tip.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;

class CcbShowGetLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbShowGetLayer()
    : m_bShowItemInfo(false)
    , m_nPriority(0)
    , m_bJustShow(false)
	{
		m_pLayerIconList = NULL;
		m_pControlButtonConfirm = NULL;
        m_pControlButtonClose = NULL;
        m_pTableViewIcons = NULL;
        m_pLabelTitle = NULL;
        m_vecIndex.clear();
        m_vecCnt.clear();
	}
	~CcbShowGetLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShowGetLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    // 增加物品}
    void addGetItem(uint32 dwIndex, int nCnt);
    // 重刷物品}
    void reloadItems();
    
    void setShowGetLayerTitle(const char * title);
    
    void setNeedShowItemInfo(bool isShow);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerIconList;
	cocos2d::extension::CCControlButton* m_pControlButtonConfirm;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::CCLabelTTF* m_pLabelTitle;

    std::vector<uint32> m_vecIndex;
    std::vector<int> m_vecCnt;
    
    CCTableView* m_pTableViewIcons;
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    // CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
	
public:
	// Funcitons
	void onPressControlButtonConfirm(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
    bool    m_bShowItemInfo;
    int     m_nPriority;
    bool    m_bJustShow;
    
};

class CcbShowGetLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShowGetLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShowGetLayer);
};


#endif // __CCBSHOWGETLAYER__H__