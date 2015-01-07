/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-13 15:45:31
*/

#ifndef __CCBGMITEMLAYER__H__
#define __CCBGMITEMLAYER__H__

//CcbGmItemLayer.h come from ccb/gm_item.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "ConfigGet.h"
#include "CcbGmInsertLayer.h"

enum E_GM_ITEM_TYPE
{
    E_GM_ITEM_PET = 1,
    E_GM_ITEM_ITEM,
    E_GM_ITEM_RUNE,
    E_GM_ITEM_EQUIP,
    E_GM_ITEM_EMBLEM,
};

class CcbGmItemLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbGmItemLayer()
	{
		m_pLayerItemBg = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFId = NULL;
		m_pLayerInsert_Cnt = NULL;
		m_pLayerInsert_Lv = NULL;

	}
	~CcbGmItemLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGmItemLayer, create);
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
	cocos2d::CCLayer* m_pLayerItemBg;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFId;
	CcbGmInsertLayer* m_pLayerInsert_Cnt;
	CcbGmInsertLayer* m_pLayerInsert_Lv;

    cocos2d::extension::CCTableView *m_table;
    std::map<uint16, PetConfig::STC_PET_CONFIG> mapPet;
    std::map<uint32, ItemConfig::STC_ITEM_CONFIG> mapItem;
    std::map<uint32, RuneConfig::STC_RUNE_CONFIG> mapRune;
    std::map<uint32, EquipNewConfig::STC_EQUIP_CONFIG> mapEquip;
    std::map<uint32, EmblemConfig::STC_EMBLEM_CONFIG> mapEmblem;
    std::vector<uint16> vctPet;
    std::vector<uint32> vcttem;
    std::vector<uint32> vctRune;
    std::vector<uint32> vctEquip;
    std::vector<uint32> vctEmblem;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    //tableView相关}
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
   virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	
public:
	// Funcitons
    void setType(uint8 type);
    cocos2d::CCString*  getGmString();
private:
    uint8 m_type;
    void loadData();
    void onSelected(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbGmItemLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGmItemLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGmItemLayer);
};


#endif // __CCBGMITEMLAYER__H__