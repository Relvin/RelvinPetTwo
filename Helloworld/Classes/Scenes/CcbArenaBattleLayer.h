/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-12 15:26:04
*/

#ifndef __CCBARENABATTLELAYER__H__
#define __CCBARENABATTLELAYER__H__

//CcbArenaBattleLayer.h come from ccb/arena_battle.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaBattleLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbArenaBattleLayer()
    : m_pLabelTTFMaxRank(NULL)
    , m_pLabelTTFRank(NULL)
    , m_pLabelTTFRankText(NULL)
    , m_pLabelTTFRankText2(NULL)
    , m_pLabelTTFRankReward(NULL)
	{
        m_pControlButtonTeam = NULL;
		m_pControlButtonRank = NULL;
		m_pLayerViewSize = NULL;
        m_pLabelTTFBuyCnt = NULL;
        m_curScene = NULL;
	}
	~CcbArenaBattleLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaBattleLayer, create);
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

private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    CCControlButton* m_pControlButtonTeam;
	CCControlButton* m_pControlButtonRank;
	cocos2d::CCLayer* m_pLayerViewSize;
    cocos2d::CCLabelTTF* m_pLabelTTFBuyCnt;
    cocos2d::CCLabelTTF* m_pLabelTTFMaxRank;
    cocos2d::CCLabelTTF* m_pLabelTTFRank;
    cocos2d::CCLabelTTF* m_pLabelTTFRankText;
    cocos2d::CCLabelTTF* m_pLabelTTFRankText2;
    cocos2d::CCLabelTTF* m_pLabelTTFRankReward;
    CCRect m_clipRect;
    
    cocos2d::extension::CCTableView* m_table;
    void addGuideLayer();
    int cellNum;
    bool m_touchFlag;
    
    static CcbArenaBattleLayer* m_curScene;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    static CcbArenaBattleLayer* getCurScene(){
        return m_curScene;
    };
    
    bool InitData();
	
    void handlerBuyPointResult();
public:
	// Funcitons

	void onPressControlButtonTeam(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonRank(CCObject* pSender, CCControlEvent event);



};

class CcbArenaBattleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaBattleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaBattleLayer);
};


#endif // __CCBARENABATTLELAYER__H__