/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-04 11:38:53
*/

#ifndef __CCBACHIEVEREWARDLAYER__H__
#define __CCBACHIEVEREWARDLAYER__H__

//CcbAchieveRewardLayer.h come from ccb/achieve_reward.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "TaskDataMgr.h"
#include "Observer.h"
#include <vector>
#include <map>

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

struct ACHIEVE_SHOW_INFO
{
    ACHIEVE_REWARD_INFO info;
    ACHIEVE_REWARD_CONFIG config;
};

class CcbAchieveRewardLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CCTableViewDelegate
,   public CObserverMsg
{
public:
	// Constructor
	CcbAchieveRewardLayer()
	{
		m_pLayerForList = NULL;
		m_pLabelTTFCount1 = NULL;
		m_pSpriteCount1 = NULL;
		m_pLabelTTFCount2 = NULL;
		m_pSpriteCount2 = NULL;
		m_pLabelTTFCount3 = NULL;
		m_pSpriteCount3 = NULL;
		m_pLabelTTFCount4 = NULL;
		m_pSpriteCount4 = NULL;
		m_pLabelTTFCount5 = NULL;
		m_pSpriteCount5 = NULL;
        m_tableView = NULL;
	}
	~CcbAchieveRewardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbAchieveRewardLayer, create);
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
	CCLayer* m_pLayerForList;
	CCLabelTTF* m_pLabelTTFCount1;
	CCSprite* m_pSpriteCount1;
	CCLabelTTF* m_pLabelTTFCount2;
	CCSprite* m_pSpriteCount2;
	CCLabelTTF* m_pLabelTTFCount3;
	CCSprite* m_pSpriteCount3;
	CCLabelTTF* m_pLabelTTFCount4;
	CCSprite* m_pSpriteCount4;
	CCLabelTTF* m_pLabelTTFCount5;
	CCSprite* m_pSpriteCount5;
    CCTableView* m_tableView;
    

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

	virtual void RefeashLayer();
public:
	// Funcitons





};

class CcbAchieveRewardLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbAchieveRewardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbAchieveRewardLayer);
};


#endif // __CCBACHIEVEREWARDLAYER__H__