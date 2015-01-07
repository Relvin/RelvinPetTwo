/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-18 18:14:04
*/

#ifndef __CCBEQUIPLISTLAYER__H__
#define __CCBEQUIPLISTLAYER__H__

//CcbEquipListLayer.h come from ccb/equip_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "Defines.h"
#include "CcbEquipNormalFrameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipListLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CObserverMsg
{
public:
	// Constructor
	CcbEquipListLayer()
	{
		m_pSpriteLine = NULL;
		m_pLayerEquipBg = NULL;
		m_pLayerEquipFrame = NULL;
		m_pLayerParent = NULL;
		m_pLayerBack = NULL;
		m_pLayerHead = NULL;
	}
	~CcbEquipListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipListLayer, create);
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
    CCSprite* m_pSpriteLine;
	cocos2d::CCLayer* m_pLayerEquipBg;
	CcbEquipNormalFrameLayer* m_pLayerEquipFrame;
	cocos2d::CCLayer* m_pLayerParent;
	cocos2d::CCLayer* m_pLayerBack;
	cocos2d::CCLayer* m_pLayerHead;

    CCTableView* m_table;
    CCPoint m_offset;
    std::vector<uint32> m_vecId;
    CCRect clipRect;
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
public:
	// Funcitons
    void addGuideLayer();
private:
    void loadData();
    
};

class CcbEquipListLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipListLayer);
};


#endif // __CCBEQUIPLISTLAYER__H__