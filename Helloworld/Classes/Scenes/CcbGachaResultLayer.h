/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-17 16:40:35
*/

#ifndef __CCBGACHARESULTLAYER__H__
#define __CCBGACHARESULTLAYER__H__

//CcbGachaResultLayer.h come from ccb/gacha_result_3.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Pet.h"

USING_NS_CC;
USING_NS_CC_EXT;


class CcbGachaOpenEgg;

class GachaResultScene:
public cocos2d::CCLayer
{
public:
    GachaResultScene();
    ~GachaResultScene();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GachaResultScene);
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
};


class CcbGachaResultLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbGachaResultLayer()
	{
		m_pSpriteGlyph2 = NULL;
		m_pLayerGlyph2 = NULL;
		m_pSpriteGlyph1 = NULL;
		m_pLayerGlyph1 = NULL;
		m_pLayerTenBg = NULL;
		m_pSpritePetIcon = NULL;
		m_pLayerOpenEgg = NULL;
		m_pLayerAll = NULL;
        m_pLayerFinger = NULL;

	}
	~CcbGachaResultLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGachaResultLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteGlyph2;
	cocos2d::CCLayer* m_pLayerGlyph2;
	cocos2d::CCSprite* m_pSpriteGlyph1;
	cocos2d::CCLayer* m_pLayerGlyph1;
	cocos2d::CCLayer* m_pLayerTenBg;
	cocos2d::CCSprite* m_pSpritePetIcon;
	CcbGachaOpenEgg* m_pLayerOpenEgg;
	cocos2d::CCLayer* m_pLayerAll;
    cocos2d::CCLayer* m_pLayerFinger;

    CCLayer *m_pLayerStarBg;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void showLight();
    void showPet();
    void showOnePet();
    void showTenPet();
    
    void showEgg();
private:
//    uint8 curPetCount;
    uint8 curStarCnt;
    uint8 maxStarCnt;
    uint8 quality;
    bool isCanBack;
    int m_curPetCnt; //初始为-1}

private:
    void onStart();

    void addStar(float time);
    void showText(uint8 type, uint8 star);
    void setCanBack();
    
    void addPet(float time);
    void showPetEff(CCNode *node, void *vptr);
    void jumpToPetshow();
};

class CcbGachaResultLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGachaResultLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGachaResultLayer);
};


#endif // __CCBGACHARESULTLAYER__H__