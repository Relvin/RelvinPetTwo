/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-17 16:42:22
*/

#ifndef __CCBGACHARESULTEGG__H__
#define __CCBGACHARESULTEGG__H__

//CcbGachaResultEgg.h come from ccb/gacha_result_egg.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbGachaResultLayer;

class CcbGachaResultEgg:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbGachaResultEgg()
	{
		m_pSpriteEgg1 = NULL;
		m_pSpriteEgg2 = NULL;
        m_pSpriteEgg3 = NULL;
		m_pSpriteEgg4 = NULL;

        m_delegate = NULL;
	}
	~CcbGachaResultEgg();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGachaResultEgg, create);
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
    cocos2d::CCSprite* m_pSpriteEgg3;
	cocos2d::CCSprite* m_pSpriteEgg4;

    CcbGachaResultLayer* m_delegate;
    uint8 quality;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void setDelegate(CcbGachaResultLayer* delegate){
        m_delegate = delegate;
    };
    void loadData(uint8 type);

private:
	void showBall(CCNode* pNode);
//    void showLight();
	void removeSelf(CCNode* pNode);
    void showEggLight();
    void showFlashLight();
    void showPet();
};

class CcbGachaResultEggLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGachaResultEggLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGachaResultEgg);
};


#endif // __CCBGACHARESULTEGG__H__