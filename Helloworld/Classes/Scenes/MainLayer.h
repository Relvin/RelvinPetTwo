//
//  MainSceneLayer.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-15.}
//
//

#ifndef __HelloWorld__MainLayer__
#define __HelloWorld__MainLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

class MainLayer:
public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	MainLayer()
	{
		m_pLayerTeam = NULL;
		m_pLayerBottom = NULL;
		m_pLayerHead = NULL;
        m_pLayerSocialUnit = NULL;
        m_pControlButtonExpand = NULL;
		m_pControlButtonChat = NULL;
        m_pControlButtonFriend = NULL;
        
		m_pControlButtonRecharge = NULL;
        m_pLayerQuest = NULL;
        m_pSpriteQuest = NULL;
        m_pControlButtonQuest = NULL;
        m_bCanTouchBtn = false;
	}
	~MainLayer();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainLayer, create);
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
    
	// option
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    static MainLayer* GetCurLayer();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerTeam;
	cocos2d::CCLayer* m_pLayerBottom;
	cocos2d::CCLayer* m_pLayerHead;
    cocos2d::CCLayer* m_pLayerSocialUnit;
    cocos2d::extension::CCControlButton* m_pControlButtonExpand;
    cocos2d::extension::CCControlButton* m_pControlButtonChat;
    cocos2d::extension::CCControlButton* m_pControlButtonFriend;
    
	cocos2d::extension::CCControlButton* m_pControlButtonRecharge;
    cocos2d::CCLayer* m_pLayerQuest;
    cocos2d::CCSprite* m_pSpriteQuest;
    cocos2d::extension::CCControlButton* m_pControlButtonQuest;
    
    void loadTeam();
    void onGM(CCObject* sender);
    void addEff();
    
    cocos2d::CCPoint m_pPointUnitOrg;
    cocos2d::CCPoint m_pPointUnitDes;
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
	
public:
	// Funcitons
    void onPressControlButtonChat(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonRecharge(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonQuest(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonExpand(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonFriend(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class MainLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainLayer);
};


#endif /* defined(__HelloWorld__MainLayer__) */
