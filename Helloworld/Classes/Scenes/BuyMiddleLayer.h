/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-09-07 16:14:57
*/

#ifndef __BUYMIDDLELAYER__H__
#define __BUYMIDDLELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SystemMessage.h"
#include "WorldPacket.h"

class BuyMiddleLayer:
    public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	BuyMiddleLayer()
	{
        m_pControlButtonZero = NULL;
        m_pControlButtonOne = NULL;
		//m_pControlButtonTwo = NULL;
//		m_pControlButtonEnlageBag = NULL;
//		m_pControlButtonEnlagePet = NULL;
		m_pControlButtonRecEnergy = NULL;
		m_pControlButtonBuyCoin = NULL;
        
        m_pLayerHead = NULL;
        m_pLayerBottom = NULL;
        m_pLayerBack = NULL;
        m_pSpriteBg = NULL;
        m_pNodeBtn = NULL;
        
        m_pLabelTTFLeftCoinCnt = NULL;
        m_pLabelTTFLeftBagCnt = NULL;
        m_pLabelTTFLeftPetCnt = NULL;
        m_pLabelTTFLeftRecCnt = NULL;
        
        m_pSpriteLeftCoin = NULL;
        m_pSpriteLeftBag = NULL;
        m_pSpriteLeftPet = NULL;
        m_pSpriteLeftRec = NULL;
        
        m_pLabelTTFWord = NULL;
	}
	~BuyMiddleLayer();

	// must have
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BuyMiddleLayer, create);
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );

	// option
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::extension::CCControlButton* m_pControlButtonZero;
    cocos2d::extension::CCControlButton* m_pControlButtonOne;
	//cocos2d::extension::CCControlButton* m_pControlButtonTwo;
//	cocos2d::extension::CCControlButton* m_pControlButtonEnlageBag;
//	cocos2d::extension::CCControlButton* m_pControlButtonEnlagePet;
	cocos2d::extension::CCControlButton* m_pControlButtonRecEnergy;
	cocos2d::extension::CCControlButton* m_pControlButtonBuyCoin;
    cocos2d::CCLabelTTF* m_pLabelTTFWord;
    
    cocos2d::CCSprite* m_pSpriteLeftCoin;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftCoinCnt;    // 剩余金币购买次数}
    cocos2d::CCSprite* m_pSpriteLeftRec;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftRecCnt;     // 剩余恢复体力购买次数}
    cocos2d::CCSprite* m_pSpriteLeftPet;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftPetCnt;     // 剩余宠物栏扩展次数}
    cocos2d::CCSprite* m_pSpriteLeftBag;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftBagCnt;     // 剩余背包扩展次数}
    
    cocos2d::CCLayer* m_pLayerHead;
    cocos2d::CCLayer* m_pLayerBottom;
    cocos2d::CCLayer* m_pLayerBack;
    cocos2d::CCNode* m_pNodeBtn;
    cocos2d::CCSprite* m_pSpriteBg;

    CCPoint m_posNodeAction;
    
    static BuyMiddleLayer* m_currentScene;
    
    
    void showTips();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
	virtual void systemMessageCancelTapped(SystemMessage *systemMessage);
	
    static BuyMiddleLayer * GetCurrScene() { return m_currentScene;}
    
    void updateLeftCnt();
public:
	// Funcitons
    void onPressControlButton(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//    void onPressControlButtonEnlagePet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//    void onPressControlButtonEnlageBag(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonRecEnergy(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonBuyCoin(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonChest(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonFace(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonDown(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class BuyMiddleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuyMiddleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BuyMiddleLayer);
};


#endif // __BUYMIDDLELAYER__H__