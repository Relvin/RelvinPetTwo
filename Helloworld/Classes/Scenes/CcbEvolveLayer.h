/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-23 15:21:31
*/

#ifndef __CCBEVOLVELAYER__H__
#define __CCBEVOLVELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "SystemMessage.h"
#include "CcbItemIconLayer.h"

class EvolveScene :
    public cocos2d::CCLayer,
    public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    EvolveScene() {
        m_pLabelTTFName = NULL;
    };
    ~EvolveScene();
    
    static cocos2d::CCScene* scene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EvolveScene, create);
    
    virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};



class CcbEvolveLayer:
	public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEvolveLayer()
	{
		m_pControlButtonEvo = NULL;
		m_pLabelTTFMoney = NULL;
		m_pSprite_no_1 = NULL;
		m_pLabelTTFNum01 = NULL;
		m_pSprite_no_2 = NULL;
		m_pLabelTTFNum02 = NULL;
		m_pSprite_no_3 = NULL;
		m_pLabelTTFNum03 = NULL;
		m_pSprite_no_4 = NULL;
		m_pLabelTTFNum04 = NULL;
		m_pSprite_no_5 = NULL;
		m_pLabelTTFNum05 = NULL;
		m_pSpriteBase_2 = NULL;
		m_pSpritePet_2 = NULL;
		m_pLabelTTFAdd2 = NULL;
		m_pLabelTTFDef_2 = NULL;
		m_pLabelTTFRev_2 = NULL;
		m_pLabelTTFAtt_2 = NULL;
		m_pLabelTTFHp_2 = NULL;
		m_pLabelTTFLv_2 = NULL;
		m_pSpriteBase_1 = NULL;
		m_pSpritePet_1 = NULL;
		m_pLabelTTFAdd1 = NULL;
		m_pLabelTTFDef_1 = NULL;
		m_pLabelTTFRev_1 = NULL;
		m_pLabelTTFAtt_1 = NULL;
		m_pLabelTTFHp_1 = NULL;
		m_pLabelTTFLv_1 = NULL;
		m_pLabelTTFMsg = NULL;
//		m_pControlButtonBack = NULL;
//		m_pLabelTTFName = NULL;
        m_pLabelTTFSpeDef_2 = NULL;
        m_pLabelTTFSpeDef_1 = NULL;
        m_pLabelTTFPassiveSkillName = NULL;
        m_pLabelTTFCurName = NULL;
        m_pLabelTTFNextName = NULL;
        
        m_pLyaerPet1Bg = NULL;
        m_pLyaerPet2Bg = NULL;
        
        m_pLayerElem1 = NULL;
        m_pLayerElem2 = NULL;
        m_pLayerElem3 = NULL;
        m_pLayerElem4 = NULL;
        m_pLayerElem5 = NULL;
        
        m_pControlButtonEvoSearch = NULL;
        m_evoInfoLayer = NULL;
	}
	~CcbEvolveLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEvolveLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonEvo;
	cocos2d::CCLabelTTF* m_pLabelTTFMoney;
	cocos2d::CCSprite* m_pSprite_no_1;
	cocos2d::CCLabelTTF* m_pLabelTTFNum01;
	cocos2d::CCSprite* m_pSprite_no_2;
	cocos2d::CCLabelTTF* m_pLabelTTFNum02;
	cocos2d::CCSprite* m_pSprite_no_3;
	cocos2d::CCLabelTTF* m_pLabelTTFNum03;
	cocos2d::CCSprite* m_pSprite_no_4;
	cocos2d::CCLabelTTF* m_pLabelTTFNum04;
	cocos2d::CCSprite* m_pSprite_no_5;
	cocos2d::CCLabelTTF* m_pLabelTTFNum05;
	cocos2d::CCSprite* m_pSpriteBase_2;
	cocos2d::CCSprite* m_pSpritePet_2;
	cocos2d::CCLabelTTF* m_pLabelTTFAdd2;
	cocos2d::CCLabelTTF* m_pLabelTTFDef_2;
	cocos2d::CCLabelTTF* m_pLabelTTFRev_2;
	cocos2d::CCLabelTTF* m_pLabelTTFAtt_2;
	cocos2d::CCLabelTTF* m_pLabelTTFHp_2;
	cocos2d::CCLabelTTF* m_pLabelTTFLv_2;
    cocos2d::CCLabelTTF* m_pLabelTTFSpeDef_2;
	cocos2d::CCSprite* m_pSpriteBase_1;
	cocos2d::CCSprite* m_pSpritePet_1;
	cocos2d::CCLabelTTF* m_pLabelTTFAdd1;
	cocos2d::CCLabelTTF* m_pLabelTTFDef_1;
	cocos2d::CCLabelTTF* m_pLabelTTFRev_1;
	cocos2d::CCLabelTTF* m_pLabelTTFAtt_1;
	cocos2d::CCLabelTTF* m_pLabelTTFHp_1;
	cocos2d::CCLabelTTF* m_pLabelTTFLv_1;
    cocos2d::CCLabelTTF* m_pLabelTTFSpeDef_1;
	cocos2d::CCLabelTTF* m_pLabelTTFMsg;
    cocos2d::CCLayer* m_pLyaerPet2Bg;
    cocos2d::CCLayer* m_pLyaerPet1Bg;
    cocos2d::CCLabelTTF* m_pLabelTTFPassiveSkillName;
    cocos2d::CCLabelTTF* m_pLabelTTFCurName;
    cocos2d::CCLabelTTF* m_pLabelTTFNextName;
//    cocos2d::extension::CCControlButton* m_pControlButtonElem1;
//    cocos2d::extension::CCControlButton* m_pControlButtonElem2;
//    cocos2d::extension::CCControlButton* m_pControlButtonElem3;
//    cocos2d::extension::CCControlButton* m_pControlButtonElem4;
//    cocos2d::extension::CCControlButton* m_pControlButtonElem5;
    CcbItemIconLayer* m_pLayerElem1;
    CcbItemIconLayer* m_pLayerElem2;
    CcbItemIconLayer* m_pLayerElem3;
    CcbItemIconLayer* m_pLayerElem4;
    CcbItemIconLayer* m_pLayerElem5;
    CcbItemIconLayer* m_pLayerElem6;
    
    cocos2d::extension::CCControlButton* m_pControlButtonEvoSearch;
    uint32 m_dwPetObId;
    
    std::vector<uint32> arrElemId;
    
    
    CCNode* m_evoInfoLayer;
private:
    void loadData();
    void addGuideLayer();
    void showEvoInfo();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonEvo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonElem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEvoSearch(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void setPetObjectId(uint32 dwObId);
    
    void onBack();

};

class CcbEvolveLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEvolveLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEvolveLayer);
};


#endif // __CCBEVOLVELAYER__H__