/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 21:04:20
*/

#ifndef __CCBPETBATTLECTRL__H__
#define __CCBPETBATTLECTRL__H__

//CcbPetBattleCtrl.h come from ccb/pet_battle_ctrl.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "PetBattleData.h"
#include "CCFlowFire.h"
#include "PetBattleControlDelegate.h"

//class CcbPetBattleLayer;

class CcbPetBattleCtrl:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
    
    enum
    {
        E_SKILL_STATE_NUN = 1,
        E_SKILL_STATE_NORMAL = 2,
        E_SKILL_STATE_ACTIVE = 3,
    };
    
	// Constructor
	CcbPetBattleCtrl()
	{
		m_pSpriteBg = NULL;
		m_pSpriteIcon = NULL;
		m_pSpriteHpBar2 = NULL;
		m_pSpriteHpBar = NULL;
		m_pSpritePowerBar = NULL;
		m_pSpriteNature = NULL;
		m_pSpriteBgNormal = NULL;
		m_pSpriteBgDead = NULL;
		m_pSpriteBgNothing = NULL;
        m_pSpriteLvStar = NULL;
        fire1 = NULL;
        fire2 = NULL;
        m_pLayerSkillFull = NULL;
        m_pLayerEffBg = NULL;
        
        m_pSpriteFace = NULL;

	}
	~CcbPetBattleCtrl();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetBattleCtrl, create);
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
	cocos2d::CCSprite* m_pSpriteBg;
	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::CCSprite* m_pSpriteHpBar2;
	cocos2d::CCSprite* m_pSpriteHpBar;
	cocos2d::CCSprite* m_pSpritePowerBar;
	cocos2d::CCSprite* m_pSpriteNature;
	cocos2d::CCSprite* m_pSpriteBgNormal;
	cocos2d::CCSprite* m_pSpriteBgDead;
	cocos2d::CCSprite* m_pSpriteBgNothing;
    cocos2d::CCLayer* m_pLayerSkillFull;
    cocos2d::CCLayer* m_pLayerEffBg;
    cocos2d::CCSprite* m_pSpriteLvStar;
    CCSprite* m_pSpriteFace;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    virtual void registerWithTouchDispatcher(void);
	
public:
	// Funcitons
    void setBattleIndex(uint16 bIndxe, PetBattleControlDelegate *delegate);
    void loadData();
    void Reflash(STC_PET_CTRL_INFO pet);
    STC_PET_CTRL_INFO getPetCrtlInfo(){return petInfo;};
    
    void loseHP(int curHp);
    
    void setRegulateState(uint8 regulateState);
    
    void setCtrlState(uint8 ctrlState);
    
    void setPower(uint32 curPower);
    
    void setIsPalsy(bool isPalsy);
    
    void setIsConfused(bool isConfused);
    
    void setIsSeal(bool isSeal);
    
    void setIsBingDong(bool isBingDong);
    
    void setIsZhongdu(bool isZhongdu);
    
    void setIsZhuoShao(bool isZhuoShao);
    
    void setAttributeRegulate(int rate);

    void setIsEnable(bool isEnable){m_bIsEnable = isEnable;};

    void hideFlowFire(CCObject* object);
    
    void showBuffEff();
private:
    STC_PET_CTRL_INFO petInfo;
    PetBattleControlDelegate *_delegate;
    
    
    float barHpWidth;
    float barPowerWidth;
    bool isFirstFull;
    
//    bool is
    
    uint32 m_curHp;
    
    uint16 m_battleIndex;
    
    /*
     麻痹
     混乱
     封印
     冰冻
     中毒
     灼烧*/
    bool m_isPalsy;//麻痹}
    bool m_isSeal;//封印}
    bool m_isConfused;//混乱}
    bool m_isBingDong;//冰冻}
    bool m_isZhongDu;//中毒}
    bool m_isZhuoShao;//灼烧}
    
    uint8 m_regulate;
    
    bool m_bIsEnable;
    uint32 m_ObjId;
    
    CCFlowFire* fire1;
    CCFlowFire* fire2;
    
    bool m_bLockDelay;      // 新手引导手速党的福音，true锁住点击（大招好也不让点），false解锁点击}
private:
    void onUpMove();

    void setPetState();
    void doSomeThing(uint32 skillId);

    void showSkillFull();
    void showFlowFire();
    
    
    void showSPAdd(int add);
    void removeSPAdd(CCNode* object);
};

class CcbPetBattleCtrlLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetBattleCtrlLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetBattleCtrl);
};


#endif // __CCBPETBATTLECTRL__H__