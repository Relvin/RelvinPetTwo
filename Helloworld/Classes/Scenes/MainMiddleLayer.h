/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-15 14:14:03
*/

#ifndef __MAINMIDDLELAYER__H__
#define __MAINMIDDLELAYER__H__

//MainMiddleLayer.h come from ccb/mainmiddle.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


USING_NS_CC;
USING_NS_CC_EXT;

class MainMiddleLayer:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	MainMiddleLayer()
	{
		m_pControlButtonBackLogin = NULL;
		m_pControlButtonArrowleft = NULL;
		m_pControlButtonArrowright = NULL;
		m_pControlButtonQuest = NULL;
		m_pLayerQuest = NULL;
		m_pControlButtonArena = NULL;
		m_pLayerArena = NULL;
		m_pControlButtonActive = NULL;
		m_pLayerActive = NULL;
		m_pControlButtonTower = NULL;
		m_pLayerTower = NULL;
        m_pSpriteQuest = NULL;
        m_pSpriteArena = NULL;
        m_pSpriteActive = NULL;
        m_pSpriteTower = NULL;
	}
	~MainMiddleLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainMiddleLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void setOpacity(GLubyte opacity);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCControlButton* m_pControlButtonBackLogin;
	cocos2d::extension::CCControlButton* m_pControlButtonArrowleft;
	cocos2d::extension::CCControlButton* m_pControlButtonArrowright;
	cocos2d::extension::CCControlButton* m_pControlButtonQuest;
    
	CCLayer* m_pLayerQuest;
	cocos2d::extension::CCControlButton* m_pControlButtonArena;
    
	CCLayer* m_pLayerArena;
	cocos2d::extension::CCControlButton* m_pControlButtonActive;
    
	CCLayer* m_pLayerActive;
	cocos2d::extension::CCControlButton* m_pControlButtonTower;
    
	CCLayer* m_pLayerTower;
    
    CCSprite* m_pSpriteQuest;
    CCSprite* m_pSpriteArena;
    CCSprite* m_pSpriteActive;
    CCSprite* m_pSpriteTower;


    std::vector<CCLayer*> arrLayer;
    int m_curPage;
    CCPoint m_tTouchPoint;
    float m_fTouchLength;
    
    bool m_changeFlag;
    bool m_btnFlag;
    
    void addEffect();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	// Funcitons
    void onGM(CCObject *sender);
public:
	// Funcitons
	void onPressControlButtonBackLogin(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonArrowleft(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonArrowright(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonQuest(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonArena(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonActive(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTower(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


private:
    void relocateContainer();
    void changePage(int off);
    
    void canChange();
    
    
};

class MainMiddleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainMiddleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainMiddleLayer);
};


#endif // __MAINMIDDLELAYER__H__