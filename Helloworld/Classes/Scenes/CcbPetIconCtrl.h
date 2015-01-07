/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-23 16:50:57
*/

#ifndef __CCBPETICONCTRL__H__
#define __CCBPETICONCTRL__H__

//CcbPetIconCtrl.h come from ccb/pet_icon_ctrl.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Pet.h"
#include "CCScrollButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbPetIconCtrl:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetIconCtrl()
    : m_pNodeStar(NULL)
	{
		m_pSpritePetBg = NULL;
		m_pControlButtonSelect = NULL;
		m_pLabelTTFLv = NULL;
		m_pSpriteE = NULL;
		m_pNodeNumBg = NULL;
		m_pLabelTTFNum = NULL;
		m_pSpriteNumBg = NULL;
		m_pSpriteTeam = NULL;
        m_pSpriteLocked = NULL;
        m_pSpritePetFrame = NULL;
        m_pSpriteAttribute = NULL;
        m_pSpriteStar = NULL;
        m_pSpritePet = NULL;
	}
	~CcbPetIconCtrl();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetIconCtrl, create);
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
	cocos2d::CCSprite* m_pSpritePetBg;
    cocos2d::CCSprite* m_pSpritePet;
	CCScrollButton* m_pControlButtonSelect;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCSprite* m_pSpriteE;
	cocos2d::CCNode* m_pNodeNumBg;
	cocos2d::CCLabelTTF* m_pLabelTTFNum;
	cocos2d::CCSprite* m_pSpriteNumBg;
	cocos2d::CCSprite* m_pSpriteTeam;
    CCSprite *m_pSpriteLocked;
    CCLayerColor *layerUnEnable;
    CCSprite* m_pSpritePetFrame;
    CCSprite* m_pSpriteAttribute;
    CCSprite* m_pSpriteStar;
    CCNode* m_pNodeStar;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
	void onPressControlButtonSelect(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void setPet(CPet *pet);
    void setNum(uint8 byNum);
    
    void setEnable(bool isEnable);
    
    void setTouchEnable(bool isTouch);
    
    uint16 getPetObjId()
    {
        if (!m_pet) {
            return 0;
        }
        return m_pet->GetObjId();
    };
    
    void setClipRect(CCRect rect);
//    void showLock();
//    void showLocked();
//    void setLock();
    void loadData();
private:
    
private:
    CPet *m_pet;
    bool m_bIsEnable;
    
    bool m_bCanTouch;
};

class CcbPetIconCtrlLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetIconCtrlLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetIconCtrl);
};


#endif // __CCBPETICONCTRL__H__