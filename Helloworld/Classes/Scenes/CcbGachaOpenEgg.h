/**
* CcbGachaOpenEgg.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-09-25 20:55:09
*/

#ifndef __CCBGACHAOPENEGG__H__
#define __CCBGACHAOPENEGG__H__

//CcbGachaOpenEgg.h come from ccb/gacha_result_2.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbGachaResultLayer;

class CcbGachaOpenEgg:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbGachaOpenEgg()
	{
		m_pSpriteEgg1 = NULL;
		m_pSpriteEgg2 = NULL;
		m_pControlButtonOpen = NULL;
        m_delegate = NULL;
	}
	~CcbGachaOpenEgg();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGachaOpenEgg, create);
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
	cocos2d::CCSprite* m_pSpriteEgg1;
	cocos2d::CCSprite* m_pSpriteEgg2;
	cocos2d::extension::CCControlButton* m_pControlButtonOpen;

    CcbGachaResultLayer* m_delegate;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void loadData(uint8 quality);
    void setDelegate(CcbGachaResultLayer* delegate){
        m_delegate = delegate;
    };

    void hideEgg();
    
	void onPressControlButtonOpen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbGachaOpenEggLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGachaOpenEggLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGachaOpenEgg);
};


#endif // __CCBGACHAOPENEGG__H__