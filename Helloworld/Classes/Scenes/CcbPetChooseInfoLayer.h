/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-22 22:33:59
*/

#ifndef __CCBPETCHOOSEINFOLAYER__H__
#define __CCBPETCHOOSEINFOLAYER__H__

//CcbPetChooseInfoLayer.h come from ccb/novicepetactive.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

#pragma mark CcbPetChooseInfoScene
class CcbPetChooseInfoScene : public cocos2d::CCLayer {
public:
    CcbPetChooseInfoScene() {
        
    }
    ~CcbPetChooseInfoScene() {
        
    }
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CcbPetChooseInfoScene);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
};


#pragma mark CcbPetChooseInfoLayer

class CcbPetChooseInfoLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetChooseInfoLayer()
	{
        m_pNodePet1 = NULL;
        m_pNodePet2 = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFAdd2 = NULL;
		m_pSpriteAttribute2 = NULL;
		m_pSpriteStar2 = NULL;
		m_pSpriteAttribute1 = NULL;
		m_pSpriteStar1 = NULL;
		m_pLabelTTFDes = NULL;
		m_pControlButtonActive = NULL;
        m_pControlButtonClose = NULL;
        m_pLayerLeft = NULL;
        m_pLayerRight = NULL;
	}
	~CcbPetChooseInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetChooseInfoLayer, create);
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
    cocos2d::CCNode* m_pNodePet1;
    cocos2d::CCNode* m_pNodePet2;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFAdd2;
	cocos2d::CCSprite* m_pSpriteAttribute2;
	cocos2d::CCSprite* m_pSpriteStar2;
	cocos2d::CCSprite* m_pSpriteAttribute1;
	cocos2d::CCSprite* m_pSpriteStar1;

	cocos2d::CCLabelTTF* m_pLabelTTFDes;
	cocos2d::extension::CCControlButton* m_pControlButtonActive;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::CCLayer* m_pLayerLeft;
    cocos2d::CCLayer* m_pLayerRight;

    uint16 m_wPetIdx;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setPetIdx(uint16 wOrgPetIdx, uint16 wDesPetIdx);
public:
	// Funcitons
	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonActive(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    // Touch Method
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};

class CcbPetChooseInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetChooseInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetChooseInfoLayer);
};


#endif // __CCBPETCHOOSEINFOLAYER__H__