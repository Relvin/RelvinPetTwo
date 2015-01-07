/**
* CcbSystemMailBoardLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-10-11 17:05:04
*/

#ifndef __CCBSYSTEMMAILBOARDLAYER__H__
#define __CCBSYSTEMMAILBOARDLAYER__H__

//CcbSystemMailBoardLayer.h come from ccb/system_reward_board.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MailDataMgr.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CcbSystemMailBoardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CCTableViewDataSource
{
public:
	// Constructor
	CcbSystemMailBoardLayer()
    : m_pTableView(NULL)
	{
		m_pControlButtonGet = NULL;
		m_pLayerIconList = NULL;
		m_pLayerContent = NULL;
        m_pControlButtonClose = NULL;

	}
	~CcbSystemMailBoardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSystemMailBoardLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    //tableView相关}
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonGet;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
	cocos2d::CCLayer* m_pLayerIconList;
	cocos2d::CCLayer* m_pLayerContent;
    CCRect m_rect;
    int m_mailId;
    MAIL_INFO tempInfo;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    static void showMail(int wIndex);

	void onPressControlButtonGet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadData(int wIndex);
    
private:
    CCTableView* m_pTableView;

};

class CcbSystemMailBoardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSystemMailBoardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSystemMailBoardLayer);
};


#endif // __CCBSYSTEMMAILBOARDLAYER__H__