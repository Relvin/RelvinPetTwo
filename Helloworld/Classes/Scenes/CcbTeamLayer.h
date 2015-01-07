/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-24 22:01:34
*/

#ifndef __CCBTEAMLAYER__H__
#define __CCBTEAMLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbTeamFrameLayer;

class TeamScene:
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	// Constructor
	TeamScene()
	{
        m_pLabelTTFName = NULL;
	}
	~TeamScene();
    
    static cocos2d::CCScene *scene();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TeamScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLabelTTF *m_pLabelTTFName;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
};



class CcbTeamLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbTeamLayer()
	{
        m_pLayerBack = NULL;
		m_pControlButtonShowValue = NULL;
		m_pLayerTeam_1 = NULL;
		m_pLayerTeamBg = NULL;
		m_pLayerArrowLeft = NULL;
		m_pControlButtonLeft = NULL;
		m_pLayerArrowRight = NULL;
		m_pControlButtonRight = NULL;
        m_pControlButtonChgLeader = NULL;
        m_bCanTouchBtn = false;
	}
	~CcbTeamLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTeamLayer, create);
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
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerBack;
	cocos2d::extension::CCControlButton* m_pControlButtonShowValue;
	CcbTeamFrameLayer* m_pLayerTeam_1;

	cocos2d::CCLayer* m_pLayerTeamBg;
	cocos2d::CCLayer* m_pLayerArrowLeft;
	cocos2d::extension::CCControlButton* m_pControlButtonLeft;
	cocos2d::CCLayer* m_pLayerArrowRight;
	cocos2d::extension::CCControlButton* m_pControlButtonRight;
    
    cocos2d::extension::CCControlButton* m_pControlButtonChgLeader;
    
    void loadData();
    
    CcbTeamFrameLayer *arrTeams[6];
    
    cocos2d::CCPoint m_tTouchPoint;
    bool m_bTouchMoved;
    bool m_bDragging;
    cocos2d::CCPoint m_tScrollDistance;
    float m_fTouchLength;
    
    bool m_isCanTouch;
    float convertDistanceFromPointToInch(float pointDis);
    void relocateContainer();
    int curPage;
    bool m_bShowValue;

    void moveTeamLayer(cocos2d::CCPoint moveDis);
    void changePage(int off);
    int getPageInitOff(int page);
    void afterChgPage();
    
    bool m_bLockSlide;
    void addGuide();
    
    bool m_bCanTouchBtn;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);

	void endLeaderChg();
public:
	// Funcitons
//    void onPressMenuItemChgBack(cocos2d::CCObject* pSender);

	void onPressControlButtonShowValue(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonLeft(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonChgLeader(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


};

class CcbTeamLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTeamLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTeamLayer);
};


#endif // __CCBTEAMLAYER__H__