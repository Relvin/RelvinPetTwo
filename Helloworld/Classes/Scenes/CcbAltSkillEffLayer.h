/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-27 17:04:08
*/

#ifndef __CCBALTSKILLEFFLAYER__H__
#define __CCBALTSKILLEFFLAYER__H__

//CcbAltSkillEffLayer.h come from ccb/fight_scene.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SpccMovieClip.h"
#include "SpccMovieFPSAction.h"
#include "PetBattleControlDelegate.h"

class AltSkillEffScene : cocos2d::CCLayer
{
public:
    AltSkillEffScene(){};
    ~AltSkillEffScene(){};
    static cocos2d::CCScene *scene();
    CREATE_FUNC(AltSkillEffScene);
    bool init();
};


class CcbAltSkillEffLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener

{
public:
	// Constructor
	CcbAltSkillEffLayer()
	{
		m_pSpritePet = NULL;
        m_pSpritePet_1 = NULL;
        m_pSpritePet_2 = NULL;
        mAnimationManager = NULL;
        m_pSpriteGuangZhu = NULL;
        m_pLabelTTFSkillName = NULL;
        
        m_delegate = NULL;
	}
	~CcbAltSkillEffLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbAltSkillEffLayer, create);
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
	cocos2d::CCSprite* m_pSpritePet;
    cocos2d::CCSprite* m_pSpritePet_1;
    cocos2d::CCSprite* m_pSpritePet_2;
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
	cocos2d::CCSprite* m_pSpriteGuangZhu;
    cocos2d::CCLabelTTF *m_pLabelTTFSkillName;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
public:
	// Funcitons
    void setDelegate(PetBattleControlDelegate *delegate){m_delegate = delegate;};
    void setPetId(uint16 wPetId, uint32 dwSkillId){m_petId = wPetId;m_skillId = dwSkillId;};
private:
//    void updateForAct(float time);
    void loadData();
    
    void runStart();
    void runBg();
    void runPet();
	void onLight_1(cocos2d::CCNode* pNode);
	void onLight_2(cocos2d::CCNode* pNode);
	void onLblLight(cocos2d::CCNode* pNode);
	void onRemoveSalf(cocos2d::CCNode* pNode);
//    void removeSalf();
    
//    std::string convertStr(std::string str);
private:
    uint16 m_petId;
    uint32 m_skillId;
//    SpccMovieClip *spcc1;
//    SpccMovieClip *spcc2;
//    SpccMovieClip* lblSpcc;
    PetBattleControlDelegate* m_delegate;
    int counter;
//    cocos2d::CCSet *pauseActions;
//    cocos2d::CCSet *pauseTargets;
};

class CcbAltSkillEffLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbAltSkillEffLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbAltSkillEffLayer);
};


#endif // __CCBALTSKILLEFFLAYER__H__