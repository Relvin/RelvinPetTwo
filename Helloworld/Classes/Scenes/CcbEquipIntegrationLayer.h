/**
* CcbEquipIntegrationLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-09-22 17:27:31
*/

#ifndef __CCBEQUIPINTEGRATIONLAYER__H__
#define __CCBEQUIPINTEGRATIONLAYER__H__

//CcbEquipIntegrationLayer.h come from ccb/equip_integration.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "CcbEquipStrengthenLayer.h"
#include "CcbItemIconLayer.h"
#include "CcbPetIcon.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipIntegrationScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbEquipIntegrationScene();
    ~CcbEquipIntegrationScene();
    
    CREATE_FUNC(CcbEquipIntegrationScene);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    CCLabelTTF* m_pLabelTTFName;
};

class CcbEquipIntegrationLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbEquipIntegrationLayer()
    : m_pLayerEquipEnhLayer(NULL)
    , m_pCurEquipTabBtn(NULL)
	{
        m_pControlButtonPet_1 = NULL;
        m_pLayerPet1 = NULL;
        m_pSpriteCanChange_1 = NULL;
        m_pControlButtonPet_2 = NULL;
        m_pLayerPet2 = NULL;
        m_pSpriteCanChange_2 = NULL;
        m_pControlButtonPet_3 = NULL;
        m_pLayerPet3 = NULL;
        m_pSpriteCanChange_3 = NULL;
        m_pControlButtonPet_4 = NULL;
        m_pLayerPet4 = NULL;
        m_pSpriteCanChange_4 = NULL;
        m_pControlButtonPet_5 = NULL;
        m_pLayerPet5 = NULL;
        m_pSpriteCanChange_5 = NULL;
        m_pControlButtonPet_6 = NULL;
        m_pLayerPet6 = NULL;
        m_pSpriteCanChange_6 = NULL;
        m_pNodePetSelect = NULL;
        m_pControlButtonEquipStrengthen = NULL;
        m_pControlButtonEquipEvo = NULL;
        m_pLayerList = NULL;
        m_pLabelTTFNothing_go = NULL;
        m_pControlButtonQuest = NULL;
        m_pSpriteQuest = NULL;
        m_pControlButtonEquip_1 = NULL;
        m_pSpritePlus_1 = NULL;
        m_pLayerEquipIcon_1 = NULL;
        m_pControlButtonEquip_2 = NULL;
        m_pSpritePlus_2 = NULL;
        m_pLayerEquipIcon_2 = NULL;
        m_pControlButtonEquip_3 = NULL;
        m_pSpritePlus_3 = NULL;
        m_pLayerEquipIcon_3 = NULL;
        m_pControlButtonEquip_4 = NULL;
        m_pSpritePlus_4 = NULL;
        m_pLayerEquipIcon_4 = NULL;
        m_pNodeEquipSelect = NULL;
        m_pControlButtonChange = NULL;
        m_pSpriteCanChange = NULL;
        m_pNodeEquipEnh = NULL;
        
        m_table = NULL;
        
	}
	~CcbEquipIntegrationLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipIntegrationLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    
    void showEquipInfoLayerByIndex(int index);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::extension::CCControlButton* m_pControlButtonPet_1;
    CcbPetIcon* m_pLayerPet1;
    cocos2d::CCSprite* m_pSpriteCanChange_1;
    cocos2d::extension::CCControlButton* m_pControlButtonPet_2;
    CcbPetIcon* m_pLayerPet2;
    cocos2d::CCSprite* m_pSpriteCanChange_2;
    cocos2d::extension::CCControlButton* m_pControlButtonPet_3;
    CcbPetIcon* m_pLayerPet3;
    cocos2d::CCSprite* m_pSpriteCanChange_3;
    cocos2d::extension::CCControlButton* m_pControlButtonPet_4;
    CcbPetIcon* m_pLayerPet4;
    cocos2d::CCSprite* m_pSpriteCanChange_4;
    cocos2d::extension::CCControlButton* m_pControlButtonPet_5;
    CcbPetIcon* m_pLayerPet5;
    cocos2d::CCSprite* m_pSpriteCanChange_5;
    cocos2d::extension::CCControlButton* m_pControlButtonPet_6;
    CcbPetIcon* m_pLayerPet6;
    cocos2d::CCSprite* m_pSpriteCanChange_6;
    cocos2d::CCNode* m_pNodePetSelect;
    cocos2d::extension::CCControlButton* m_pControlButtonEquipStrengthen;
    cocos2d::extension::CCControlButton* m_pControlButtonEquipEvo;
    cocos2d::CCLayer* m_pLayerList;
    cocos2d::CCLabelTTF* m_pLabelTTFNothing_go;
    cocos2d::extension::CCControlButton* m_pControlButtonQuest;
    cocos2d::CCSprite* m_pSpriteQuest;
    cocos2d::extension::CCControlButton* m_pControlButtonEquip_1;
    cocos2d::CCSprite* m_pSpritePlus_1;
    CcbItemIconLayer* m_pLayerEquipIcon_1;
    cocos2d::extension::CCControlButton* m_pControlButtonEquip_2;
    cocos2d::CCSprite* m_pSpritePlus_2;
    CcbItemIconLayer* m_pLayerEquipIcon_2;
    cocos2d::extension::CCControlButton* m_pControlButtonEquip_3;
    cocos2d::CCSprite* m_pSpritePlus_3;
    CcbItemIconLayer* m_pLayerEquipIcon_3;
    cocos2d::extension::CCControlButton* m_pControlButtonEquip_4;
    cocos2d::CCSprite* m_pSpritePlus_4;
    CcbItemIconLayer* m_pLayerEquipIcon_4;
    cocos2d::CCNode* m_pNodeEquipSelect;
    cocos2d::extension::CCControlButton* m_pControlButtonChange;
    cocos2d::CCSprite* m_pSpriteCanChange;
    cocos2d::CCNode* m_pNodeEquipEnh;

    CcbEquipStrengthenLayer* m_pLayerEquipEnhLayer;
    CCTableView* m_table;
    std::vector<uint32> m_vecEquipListId;
    CCRect clipRect;
    
    int m_selectPet;
    int m_selectEquip;
//    int flashCnt;
    bool m_bChange;
    
    std::vector<uint32> arrPetObjId;
    std::vector<uint8> arrTeamSite;
    std::vector<uint32> arrCurEquipObjId;
    std::vector<CcbPetIcon*> arrPetIcon;
    std::vector<CCSprite*> arrPlus;
    std::vector<CCSprite*> arrCanChange;
    std::vector<CCControlButton*> arrEquipBtn;
    std::vector<CcbItemIconLayer*> arrEquipIcon;
    
    cocos2d::extension::CCControlButton* m_pCurEquipTabBtn;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void RefeashLayer();
private:
    void loadData();
    void loadWearEquip();
    void onSelectPet();
    void onSelectEquip();
    void loadEquipList();
    void showEquipEnhLayer();
    void hideEquipEnhLayer();
    
    void initBtnChange();
    void addGuideLayer();
    void ShowFlyLayer();

    void checkPetCanChangeEquip();
public:
	// Funcitons
	void onPressControlButtonPet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonChange(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonQuest(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEquipTab(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbEquipIntegrationLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipIntegrationLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipIntegrationLayer);
};


#endif // __CCBEQUIPINTEGRATIONLAYER__H__
