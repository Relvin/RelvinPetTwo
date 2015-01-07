/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-20 16:43:17
*/

#ifndef __CCBDROPBOXLAYER__H__
#define __CCBDROPBOXLAYER__H__

//CcbDropBoxLayer.h come from ccb/box.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PetBattleControlDelegate.h"


class CcbDropBoxLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbDropBoxLayer()
	{
        mAnimationManager = NULL;
        m_pSpriteBoxClose = NULL;
		m_pSpriteBoxOpen_1 = NULL;
		m_pSpriteBoxOpen_2 = NULL;
        m_pControlButtonOpen = NULL;
        m_pLayerFinger = NULL;
        
        m_delegate = NULL;
        isOpen = false;
        
	}
	~CcbDropBoxLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbDropBoxLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
//	virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    cocos2d::CCSprite* m_pSpriteBoxClose;
	cocos2d::CCSprite* m_pSpriteBoxOpen_1;
	cocos2d::CCSprite* m_pSpriteBoxOpen_2;
    cocos2d::extension::CCControlButton *m_pControlButtonOpen;
    cocos2d::CCLayer* m_pLayerFinger;
    
    bool isOpen;
    PetBattleControlDelegate *m_delegate;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    void onPressControlButtonOpen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	
public:
	// Funcitons
    void runDrop();
    void runOpen();
    void runCheck();
    void setDelegate(PetBattleControlDelegate *delegate){m_delegate = delegate;};
private:
    void hideSalf();
};

class CcbDropBoxLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbDropBoxLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbDropBoxLayer);
};


#endif // __CCBDROPBOXLAYER__H__