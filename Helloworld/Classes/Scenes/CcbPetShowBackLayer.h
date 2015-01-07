/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-06 16:14:57
*/

#ifndef __CCBPETSHOWBACKLAYER__H__
#define __CCBPETSHOWBACKLAYER__H__

//CcbPetShowBackLayer.h come from ccb/petshow_back.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Pet.h"

class CcbPetShowBackLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetShowBackLayer()
	{
		m_pLabelTTFPetName = NULL;
		m_pSpriteLvStar = NULL;
        mAnimationManager = NULL;
        m_pSpriteAttribute = NULL;
        m_pControlButtonLock = NULL;
        m_pControlButtonUnLock = NULL;
        m_pLayerEvoLv = NULL;
        m_pControlButtonBack = NULL;
        m_pSpritePetTypeIcon = NULL;
        m_delegate = NULL;
        m_bCanTouchBtn = false;
	}
	~CcbPetShowBackLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetShowBackLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFPetName;
	cocos2d::CCSprite* m_pSpriteLvStar;
    cocos2d::CCSprite* m_pSpriteAttribute;
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    cocos2d::extension::CCControlButton* m_pControlButtonLock;
    cocos2d::extension::CCControlButton* m_pControlButtonUnLock;
    cocos2d::extension::CCControlButton* m_pControlButtonBack;
    cocos2d::CCLabelTTF* m_pLayerEvoLv;
    cocos2d::CCSprite* m_pSpritePetTypeIcon;
//    CcbPetShowLayer* m_delegate;
    uint32 m_dwPetObjId;
    bool m_backFlag;
    
    bool m_isHideOnly;//petinfolayer中用
    CCLayer* m_delegate;
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

	
public:
	// Funcitons
    void loadData(uint16 wPetIndex, bool isHideOnly = false);
    
    void loadObjData(CPet *pet, bool isHideOnly = false);
    void hideLock();
    void setDelegate(CCLayer* delegate){m_delegate = delegate;};
    
    void setBackTouchPr(int priority){
        m_pControlButtonBack->setTouchPriority(priority);
    };
    
    void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonLock(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonUnLock(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

private:
    void onMoveIn();
    void onMoveOut();

};

class CcbPetShowBackLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetShowBackLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetShowBackLayer);
};


#endif // __CCBPETSHOWBACKLAYER__H__