/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-21 18:12:51
*/

#ifndef __CCBUNITMIDDLELAYER__H__
#define __CCBUNITMIDDLELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class UnitMiddleScene :
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    UnitMiddleScene()
	{
        m_pLabelTTFName = NULL;
	}
	~UnitMiddleScene();
    
    static cocos2d::CCScene* scene();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(UnitMiddleScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    
private:
	// Attributes for CCB
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
};


class CcbUnitMiddleLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
,   public CObserverRole
{
public:
	// Constructor
	CcbUnitMiddleLayer()
	{
        m_pLayerHeaderBack = NULL;
        m_pLayerBottom = NULL;
        m_pTableList = NULL;
        m_fDelta = 0.02f;
        m_vecCell.clear();
        m_fCellHeight = 550.0f;
        m_bEnableBtn = true;
        m_pNode1 = NULL;
        m_pNodeEquip = NULL;
        m_pNodeBaoshi = NULL;
        m_pNodeFenjie = NULL;
	}
	~CcbUnitMiddleLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbUnitMiddleLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
private:
    enum kUnitTag {
        kPetBag = 8,    // 精灵一览}
        kPetTeam = 0,       // 编辑队伍}
        kPetEnhance = 1,    // 精灵强化}
        kPetEvolve = 2,     // 精灵进阶}
        kEquipBag = 4,      // 装备一览}
        kGemInlay = 5,      // 符文镶嵌}    //宝石
//        kPropsCompose = 6,  // 符文合成}
        kTujian = 3,        // 图鉴
        kEmblemBag = 6,     // 徽章一览}
        kPropsBag = 9,      // 道具一览}
        kPetFragment = 7,   // 宠物碎片}
        kPetFuseTag = 11,    // 精灵分解}
        kSellPet = 10,       // 精灵出售}
    };
    
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerHeaderBack;
    cocos2d::CCLayer* m_pLayerBottom;
    
    cocos2d::extension::CCTableView* m_pTableList;

    float m_fCellHeight;
    float m_fCellWidth;
    
    int m_nTableCnt;
    cocos2d::CCSize winSize;
    
    std::vector<CCNode*> m_vecCell;
    float m_fDelta;
    float m_fDelay;
    void setTouchRestore();
    
    cocos2d::CCPoint m_pointList;
    cocos2d::CCSize m_sizeList;
    bool m_bEnableBtn;
    
    void setNodeData(int nIdx, CCLayer* pLayer);
    bool checkBtnEnable(int tag);
    
    void addTipsUpRight(CCLayer* pLayer, CCPoint pos);
    
    cocos2d::CCNode* m_pNode1;
    cocos2d::CCNode* m_pNodeEquip;
    cocos2d::CCNode* m_pNodeBaoshi;
    cocos2d::CCNode* m_pNodeFenjie;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    // CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize cellSizeForTable(CCTableView *table);
    
    void onPressControlButtonIcon(CCObject* pSender, CCControlEvent event);
    
    void byNotiNewPetChanged(uint8 byNotiNewPet);
    void byNotiNewEquipChanged(uint8 byNotiNewEquip);
    void byNotiNewEmblemChanged(uint8 byNotiNewEmblem);
};

class CcbUnitMiddleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbUnitMiddleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbUnitMiddleLayer);
};


#endif // __CCBUNITMIDDLELAYER__H__