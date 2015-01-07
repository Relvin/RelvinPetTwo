/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-03 20:36:23
*/

#ifndef __CCBPETEVOLVESUCCESSLAYER__H__
#define __CCBPETEVOLVESUCCESSLAYER__H__

//CcbPetEvolveSuccessLayer.h come from ccb/pet_evo_result.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PetEvolveSuccessScene :
public cocos2d::CCLayer
{
public:
    PetEvolveSuccessScene() {
    };
    ~PetEvolveSuccessScene(){};
    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(PetEvolveSuccessScene);
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};


class CcbPetEvolveSuccessLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetEvolveSuccessLayer()
	{
        m_pSpritePet = NULL;
        m_pSpriteCenter = NULL;
        m_pLabelTTFPetName = NULL;
        m_pLabelTTFCurUp = NULL;
        m_pLabelTTFCurHp = NULL;
        m_pLabelTTFCurAtt = NULL;
        m_pLabelTTFCurCover = NULL;
        m_pLabelTTFCurDef = NULL;
        m_pLabelTTFNextUp = NULL;
        m_pLabelTTFNextHp = NULL;
        m_pLabelTTFNextAtt = NULL;
        m_pLabelTTFNextDef = NULL;
        m_pLabelTTFNextCover = NULL;
        m_pLabelTTFCurSpeDef = NULL;
        m_pLabelTTFNextSpeDef = NULL;
        m_pLabelTTFPassiveSkillName = NULL;
        m_pLabelTTFPassiveSkillDes = NULL;
        m_pLayerInfoBg = NULL;

	}
	~CcbPetEvolveSuccessLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetEvolveSuccessLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCSprite* m_pSpritePet;
    cocos2d::CCSprite* m_pSpriteCenter;
    cocos2d::CCLabelTTF* m_pLabelTTFPetName;
    cocos2d::CCLabelTTF* m_pLabelTTFCurUp;
    cocos2d::CCLabelTTF* m_pLabelTTFCurHp;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAtt;
    cocos2d::CCLabelTTF* m_pLabelTTFCurCover;
    cocos2d::CCLabelTTF* m_pLabelTTFCurDef;
    cocos2d::CCLabelTTF* m_pLabelTTFNextUp;
    cocos2d::CCLabelTTF* m_pLabelTTFNextHp;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAtt;
    cocos2d::CCLabelTTF* m_pLabelTTFNextDef;
    cocos2d::CCLabelTTF* m_pLabelTTFNextCover;
    cocos2d::CCLabelTTF* m_pLabelTTFCurSpeDef;
    cocos2d::CCLabelTTF* m_pLabelTTFNextSpeDef;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillDes;
    cocos2d::CCLayer* m_pLayerInfoBg;


    bool bTouchEnable;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void loadData();


private:
    void showEff1();
    void showEff2();
    void showEff3();
    void openTouch();

};

class CcbPetEvolveSuccessLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetEvolveSuccessLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetEvolveSuccessLayer);
};


#endif // __CCBPETEVOLVESUCCESSLAYER__H__