/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 23:42:44
*/

#ifndef __CCBFRIENDLAYER__H__
#define __CCBFRIENDLAYER__H__

//CcbFriendLayer.h come from ccb/friend_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbFriendLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,   public cocos2d::extension::CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbFriendLayer()
	{
		m_pLayerHeadBack = NULL;
        m_pLayerBottom = NULL;
        m_pTableFriend = NULL;
        m_nTableCnt = 0;
        m_pLayerViewBg = NULL;
	}
	~CcbFriendLayer();

    static CcbFriendLayer* GetCurLayer();
    
    void onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader);
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerHeadBack;
    cocos2d::CCLayer* m_pLayerBottom;
    cocos2d::CCLayer* m_pLayerViewBg;
    cocos2d::extension::CCTableView* m_pTableFriend;

    static CcbFriendLayer* m_shared;
    float m_fCellWidth, m_fCellHeight;
    
    CCSize winSize;
    int m_nTableCnt;
    CCRect m_clipRect;
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
    void ReloadList();
    void addMailContent();
};

class CcbFriendLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendLayer);
};


#endif // __CCBFRIENDLAYER__H__