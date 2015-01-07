/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-10 15:05:09
*/

#ifndef __CCBTOWERMAINLAYER__H__
#define __CCBTOWERMAINLAYER__H__

//CcbTowerMainLayer.h come from ccb/climbtower_main.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
//#include "SystemMessageProtocol.h"

class CcbTowerMainLayer:
    public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
//,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbTowerMainLayer()
	{
		m_pSpriteBg = NULL;
		m_pSpritePet_1 = NULL;
		m_pSpritePet_2 = NULL;
		m_pControlButtonGo = NULL;
		m_pControlButtonReset = NULL;
		m_pControlButtonSweep = NULL;
		m_pControlButtonBack = NULL;
		m_pLabelTTFTime = NULL;
		m_pLayerTime = NULL;
		m_pLabelTTFFlood = NULL;
		m_pLabelTTFMissionDesc = NULL;
		m_pSpriteHeart = NULL;
		m_pControlButtonBox = NULL;
		m_pControlButtonRank = NULL;
        m_curScene = NULL;
        mAnimationManager = NULL;
        
        m_bCanTouchBtn = true;  // 默认均可以点击，只在前进的时候不让点击
	}
	~CcbTowerMainLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTowerMainLayer, create);
	// Inhert MemberVariableAssigner
    virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
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
    
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
	cocos2d::CCSprite* m_pSpriteBg;
	cocos2d::CCSprite* m_pSpritePet_1;
	cocos2d::CCSprite* m_pSpritePet_2;
	cocos2d::extension::CCControlButton* m_pControlButtonGo;
	cocos2d::extension::CCControlButton* m_pControlButtonReset;
	cocos2d::extension::CCControlButton* m_pControlButtonSweep;
	cocos2d::extension::CCControlButton* m_pControlButtonBack;
	cocos2d::CCLabelTTF* m_pLabelTTFTime;
	cocos2d::CCLayer* m_pLayerTime;
	cocos2d::CCLabelTTF* m_pLabelTTFFlood;
	cocos2d::CCLabelTTF* m_pLabelTTFMissionDesc;
	cocos2d::CCSprite* m_pSpriteHeart;
	cocos2d::extension::CCControlButton* m_pControlButtonBox;
	cocos2d::extension::CCControlButton* m_pControlButtonRank;
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void CreateData();
	void RefreshData();
    static CcbTowerMainLayer* m_curScene;
    static CcbTowerMainLayer* getCurScene() { return m_curScene; };
    
    void onUpdate(float delta);
    uint32 m_dwLeftTime;
    
    void showRank();
private:
    void onRoad();
    void onShowPet();
    void onBattle();
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Funcitons
	void onPressControlButtonGo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonReset(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonSweep(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonBox(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRank(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

//    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
};

class CcbTowerMainLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTowerMainLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTowerMainLayer);
};


#endif // __CCBTOWERMAINLAYER__H__