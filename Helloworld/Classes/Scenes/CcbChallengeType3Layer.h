/**
* CcbChallengeType3Layer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-15 19:49:34
*/

#ifndef __CCBCHALLENGETYPE3LAYER__H__
#define __CCBCHALLENGETYPE3LAYER__H__

//CcbChallengeType3Layer.h come from ccb/CcbChallengeType3Layer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"
#include "CcbChallengeNodeLayer.h"


class ChallengeType3Scene
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    ChallengeType3Scene();
    ~ChallengeType3Scene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(ChallengeType3Scene);
    bool init();
    
    
    bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
    virtual void onEnter();
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
};

class CcbChallengeType3Layer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public ItemIconTouchDelegate
, public ChallengeNodeClickedDelegate
{
public:
	// Constructor
    CcbChallengeType3Layer();
	~CcbChallengeType3Layer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeType3Layer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
private:
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerUp;
	cocos2d::extension::CCControlButton* m_pControlButtonLeft;
	cocos2d::extension::CCControlButton* m_pControlButtonRight;
	cocos2d::CCLayer* m_pLayerScroll;
    cocos2d::CCLabelTTF* m_pLabelTTFMissionLevel;
    cocos2d::CCNode* m_pNodeTeam;
    cocos2d::CCLabelTTF* m_pLabelTTFEnergy;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftCnt;
    cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillName;
    cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillDes;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    // TableView Functions
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) ;
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table) ;
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx) ;
	
    // Touch Functions
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    //
    virtual void itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId) ;
    
    //
    virtual void challengeNodeClicked(CcbChallengeNodeLayer* pNode) ;
public:
	// Funcitons
	void onPressControlButtonLeft(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClickedCallBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonBattle(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    // Self Functions
    void updateTableViewPos(int moveDir);
    void loadBattleTeamInfo();
private:
    cocos2d::extension::CCTableView* m_pTableView;
    bool    m_bTouchMoved;
    cocos2d::CCPoint m_TouchBeginPos;
    cocos2d::CCRect m_TouchRect;
    int m_nCurPage;
    int m_nTotalPage;
    int m_nSelectPage;
    CcbItemIconLayer* m_pItemIcon[6];
    cocos2d::CCSprite* m_pBattleType[6];
    int m_nCurIndex;
    CcbChallengeNodeLayer* m_pCurNode;
    bool m_bFirstSelect;
    

};

class CcbChallengeType3LayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeType3LayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeType3Layer);
};


#endif // __CCBCHALLENGETYPE3LAYER__H__