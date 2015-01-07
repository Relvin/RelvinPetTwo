/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-20 15:05:21
*/

#ifndef __CCBARENAPETCTRL__H__
#define __CCBARENAPETCTRL__H__

//CcbArenaPetCtrl.h come from ccb/arena_pet_ctrl.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbArenaFightLayer;
class CcbPetIcon;

class CcbArenaPetCtrl:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbArenaPetCtrl()
	{
		m_pSpriteIcon = NULL;
		m_pSpriteSkillBar = NULL;
		m_pSpriteHpBar = NULL;
//        m_pSpriteSkillBarBg = NULL;
//        m_pLayerPetIcon = NULL;
//        m_skillBar = NULL;
        
        m_pSpriteNormal = NULL;
		m_pSpriteDead = NULL;
		m_pSpriteNature = NULL;
		m_pSpriteNothing = NULL;
        
        m_delegate = NULL;
	}
	~CcbArenaPetCtrl();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaPetCtrl, create);
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
	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::CCSprite* m_pSpriteSkillBar;
	cocos2d::CCSprite* m_pSpriteHpBar;
//	cocos2d::CCSprite* m_pSpriteSkillBarBg;
    cocos2d::CCSprite* m_pSpriteNormal;
	cocos2d::CCSprite* m_pSpriteDead;
	cocos2d::CCSprite* m_pSpriteNature;
	cocos2d::CCSprite* m_pSpriteNothing;
    
    
//    CcbPetIcon* m_pLayerPetIcon;
//    cocos2d::CCNode* m_skillBar;
private:
    CcbArenaFightLayer* m_delegate;
    float barHpW;
    float barPowerW;
    uint16 m_wBattleIndex;
    uint32 m_dwMaxHp;
    uint8 m_byMaxPower;
    
    
    float scaleYofSkillBar;
    float offYofSkillBar;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setBattleIndex(uint16 wBattleIndex);
    void setDelegate(CcbArenaFightLayer* delegate){m_delegate = delegate;};
	
public:
	// Funcitons
    void beHit(int curHp);
    void setHp(int curHp);
    void setPower(int curPower);
private:
    void loadData();



};

class CcbArenaPetCtrlLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaPetCtrlLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaPetCtrl);
};


#endif // __CCBARENAPETCTRL__H__