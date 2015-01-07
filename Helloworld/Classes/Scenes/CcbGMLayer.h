/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-13 15:45:08
*/

#ifndef __CCBGMLAYER__H__
#define __CCBGMLAYER__H__

//CcbGMLayer.h come from ccb/gm.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbGmUserLayer.h"
#include "CcbGmItemLayer.h"

class GMScene : public cocos2d::CCLayer
{
public:
    GMScene(){};
    ~GMScene();
    
    static CCScene * scene();
    
    CREATE_FUNC(GMScene);
    
    bool init();
};


class CcbGMLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbGMLayer()
	{
		m_pControlButtonUser = NULL;
		m_pControlButtonPet = NULL;
		m_pControlButtonItem = NULL;
		m_pControlButtonVip = NULL;
		m_pLayerBg = NULL;
		m_pControlButtonBack = NULL;
		m_pControlButtonSend = NULL;
		m_pControlButtonGem = NULL;
        m_pControlButtonEmblem = NULL;

	}
	~CcbGMLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGMLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonUser;
	cocos2d::extension::CCControlButton* m_pControlButtonPet;
	cocos2d::extension::CCControlButton* m_pControlButtonItem;
	cocos2d::extension::CCControlButton* m_pControlButtonVip;
	cocos2d::CCLayer* m_pLayerBg;
	cocos2d::extension::CCControlButton* m_pControlButtonBack;
	cocos2d::extension::CCControlButton* m_pControlButtonSend;
	cocos2d::extension::CCControlButton* m_pControlButtonGem;
    cocos2d::extension::CCControlButton* m_pControlButtonEmblem;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonUser(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonPet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonItem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonVip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonSend(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonGem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEmblem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

private:
    CcbGmItemLayer * m_ItemLayer;
    CcbGmUserLayer* m_UserLayer;
    CCTextFieldAuto *m_pTextFieldAutoInfo;
private:
    void loadData();
    void loadUser();
    void loadItem(uint8 type);
    void onSave();
};

class CcbGMLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGMLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGMLayer);
};


#endif // __CCBGMLAYER__H__