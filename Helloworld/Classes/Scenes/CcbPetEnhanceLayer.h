/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-28 15:06:49
*/

#ifndef __CCBPETENHANCELAYER__H__
#define __CCBPETENHANCELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "SystemMessage.h"

class CcbTeamMemberLayer;

class PetEnhanceScene :
    public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner {
    
public:
    PetEnhanceScene() {
        m_pLabelTTFName = NULL;
    };
    
    ~PetEnhanceScene();
    
    static cocos2d::CCScene* scene();
    // Create Method
    CREATE_FUNC(PetEnhanceScene);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
};

class CcbPetEnhanceLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbPetEnhanceLayer()
	{
		m_pControlButtonEnhance = NULL;
		m_pLayerElem1 = NULL;
		m_pControlButtonElem1 = NULL;
		m_pLabelTTFElemLv1 = NULL;
		m_pLayerElem2 = NULL;
		m_pControlButtonElem2 = NULL;
		m_pLabelTTFElemLv2 = NULL;
		m_pLayerElem3 = NULL;
		m_pControlButtonElem3 = NULL;
		m_pLabelTTFElemLv3 = NULL;
		m_pLayerElem4 = NULL;
		m_pControlButtonElem4 = NULL;
		m_pLabelTTFElemLv4 = NULL;
		m_pLayerElem5 = NULL;
		m_pControlButtonElem5 = NULL;
		m_pLabelTTFElemLv5 = NULL;
		m_pLabelTTFHp = NULL;
		m_pLabelTTFAtt = NULL;
		m_pLabelTTFRev = NULL;
		m_pLabelTTFDef = NULL;
		m_pSpriteBase = NULL;
		m_pSpritePet = NULL;
		m_pLabelTTFLv = NULL;
		m_pLabelTTFMoney = NULL;
		m_pLabelTTFGetExp = NULL;
		m_pLabelTTFNeedExp = NULL;
		m_pSpriteExpBar2 = NULL;
		m_pSpriteExpBar = NULL;
		m_pLabelTTFNoMoney = NULL;
		m_pSprite_plus_1 = NULL;
		m_pSprite_plus_2 = NULL;
        m_pSprite_plus_3 = NULL;
        m_pSprite_plus_4 = NULL;
        m_pSprite_plus_5 = NULL;
        m_pLabelTTFEvoLv = NULL;
        m_pNodeFood1 = NULL;
        m_pNodeFood2 = NULL;
        m_pNodeFood3 = NULL;
        m_pNodeFood4 = NULL;
        m_pNodeFood5 = NULL;
        m_pLabelTTFSpeDef = NULL;
        m_pLabelTTFPetName = NULL;
        m_pControlButtonAutoAdd = NULL;
        
        m_pLabelTTFAddHp = NULL;
        m_pLabelTTFAddAtt = NULL;
        m_pLabelTTFAddRev = NULL;
        m_pLabelTTFAddDef = NULL;
        m_pLabelTTFAddSpeDef = NULL;
        m_pLabelTTFAddLv = NULL;
	}
	~CcbPetEnhanceLayer();

    static CcbPetEnhanceLayer* GetSharedLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetEnhanceLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonEnhance;
	cocos2d::CCLayer* m_pLayerElem1;
	cocos2d::extension::CCControlButton* m_pControlButtonElem1;
	cocos2d::CCLabelTTF* m_pLabelTTFElemLv1;
	cocos2d::CCLayer* m_pLayerElem2;
	cocos2d::extension::CCControlButton* m_pControlButtonElem2;
	cocos2d::CCLabelTTF* m_pLabelTTFElemLv2;
	cocos2d::CCLayer* m_pLayerElem3;
	cocos2d::extension::CCControlButton* m_pControlButtonElem3;
	cocos2d::CCLabelTTF* m_pLabelTTFElemLv3;
	cocos2d::CCLayer* m_pLayerElem4;
	cocos2d::extension::CCControlButton* m_pControlButtonElem4;
	cocos2d::CCLabelTTF* m_pLabelTTFElemLv4;
	cocos2d::CCLayer* m_pLayerElem5;
	cocos2d::extension::CCControlButton* m_pControlButtonElem5;
	cocos2d::CCLabelTTF* m_pLabelTTFElemLv5;
	cocos2d::CCLabelTTF* m_pLabelTTFHp;
	cocos2d::CCLabelTTF* m_pLabelTTFAtt;
	cocos2d::CCLabelTTF* m_pLabelTTFRev;
	cocos2d::CCLabelTTF* m_pLabelTTFDef;
	cocos2d::CCSprite* m_pSpriteBase;
	cocos2d::CCSprite* m_pSpritePet;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCLabelTTF* m_pLabelTTFMoney;
	cocos2d::CCLabelTTF* m_pLabelTTFGetExp;
	cocos2d::CCLabelTTF* m_pLabelTTFNeedExp;
	cocos2d::CCSprite* m_pSpriteExpBar2;
	cocos2d::CCSprite* m_pSpriteExpBar;
	cocos2d::CCLabelTTF* m_pLabelTTFNoMoney;
    cocos2d::CCSprite* m_pSprite_plus_1;
    cocos2d::CCSprite* m_pSprite_plus_2;
    cocos2d::CCSprite* m_pSprite_plus_3;
    cocos2d::CCSprite* m_pSprite_plus_4;
    cocos2d::CCSprite* m_pSprite_plus_5;
    cocos2d::CCNode* m_pNodeFood1;
    cocos2d::CCNode* m_pNodeFood2;
    cocos2d::CCNode* m_pNodeFood3;
    cocos2d::CCNode* m_pNodeFood4;
    cocos2d::CCNode* m_pNodeFood5;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoLv;
    cocos2d::CCLabelTTF* m_pLabelTTFSpeDef;
    cocos2d::CCLabelTTF* m_pLabelTTFPetName;
    cocos2d::extension::CCControlButton* m_pControlButtonAutoAdd;
    
    cocos2d::CCLabelTTF* m_pLabelTTFAddHp;
    cocos2d::CCLabelTTF* m_pLabelTTFAddAtt;
    cocos2d::CCLabelTTF* m_pLabelTTFAddRev;
    cocos2d::CCLabelTTF* m_pLabelTTFAddDef;
    cocos2d::CCLabelTTF* m_pLabelTTFAddSpeDef;
    cocos2d::CCLabelTTF* m_pLabelTTFAddLv;
    
    uint32 m_dwPetObjId;
    std::vector<cocos2d::CCLayer*> arrElems;
//    std::vector<cocos2d::CCLabelTTF*> arrElemLvs;
    std::vector<cocos2d::extension::CCControlButton*> arrElemButtons;
    std::vector<cocos2d::CCSprite*> arrElemsPlus;
    std::vector<cocos2d::CCNode*> m_vecNode;
    float expBarWidth;
    
    uint32 m_costCoin;
    bool m_bAutoSelect;
    void addPetEnhanceEff();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    
    /*!
     强化成功后的回调动画}
     */
    void playEnhanceEffect();
public:
	// Funcitons
    void onPressControlButtonAutoAdd(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonEnhance(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonElem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
private:
    void loadData();
    void checkIntensify();
    void addGuideLayer();
    void loadElem();
    
    bool checkExpFull(uint32 addexp);
    void showNextLvValue(uint32 addExp);
    void showAddTextEff(CCLabelTTF* lbl);
    void hideAddTextEff(CCLabelTTF* lbl);
    void showEnhTextEff(CCLabelTTF* lbl);
};

class CcbPetEnhanceLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetEnhanceLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetEnhanceLayer);
};


#endif // __CCBPETENHANCELAYER__H__