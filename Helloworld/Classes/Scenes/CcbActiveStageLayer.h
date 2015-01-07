/**
* CcbActiveStageLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: 
* Date: 2014-09-13 18:01:14
*/

#ifndef __CCBACTIVESTAGELAYER__H__
#define __CCBACTIVESTAGELAYER__H__

//CcbActiveStageLayer.h come from ccb/missionframe_active.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Observer.h"
#include "SystemMessageProtocol.h"

class CCScrollButton;
class CcbActiveStageLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverMsg
,   public cocos2d::extension::CCTableViewDataSource
,   public cocos2d::extension::CCTableViewDelegate
,   public SystemMessageProtocol
{
public:
	// Constructor
    CcbActiveStageLayer() {
        m_pLayerDrop = NULL;
        m_pControlButtonFight = NULL;
        m_pLabelTTFLeftCnt = NULL;
        m_pLabelTTFEnergy = NULL;
        m_pLabelTTFName = NULL;
        m_pSpriteAttribute = NULL;
        m_pTableDrop = NULL;
        m_pLabelOpenLv = NULL;
        m_vecDropId.clear();
        m_nPetCnt = m_nItemCnt = 0;
        m_byCostEnergy = 255;
        m_byAttactCnt = m_byMaxAttCnt = 255;
        m_wLimitLv = 65535;
        m_byLeftCnt = 255;
        m_byBuyCnt = 0;
        m_byLeftBuyCnt = 0;
    }
    
	~CcbActiveStageLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbActiveStageLayer, create);
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
	cocos2d::CCLayer* m_pLayerDrop;
	CCScrollButton* m_pControlButtonFight;
	cocos2d::CCLabelTTF* m_pLabelTTFLeftCnt;
	cocos2d::CCLabelTTF* m_pLabelTTFEnergy;
	cocos2d::CCLabelTTF* m_pLabelTTFName;   // 关卡名称}
	cocos2d::CCSprite* m_pSpriteAttribute;
    cocos2d::CCLabelTTF* m_pLabelOpenLv;    // 关卡开启等级}
    cocos2d::extension::CCTableView* m_pTableDrop;

    int m_nSelActiveIdx;
    uint16 m_wStageId;
    uint16 m_wLimitLv;
    uint8 m_byCostEnergy;
    uint8 m_byAttactCnt;
    uint8 m_byMaxAttCnt;
    uint8 m_byLeftCnt;
    uint16 m_wIconId;
    int m_nPetCnt, m_nItemCnt;
    std::vector<uint32> m_vecDropId;
    uint8 m_byBuyCnt;       // 已经购买次数}
    uint8 m_byLeftBuyCnt;   // 剩余购买次数}
    
    void setInfo();         // 设置Stage的信息}
    void showBuyMessage();
    
    cocos2d::CCRect m_rect;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void SetNodeData(int _idx);
    void setClipRect(cocos2d::CCRect rect);
public:
	// Funcitons
	void onPressControlButtonFight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    // ObserverDelegate
    virtual void RefeashLayer();
    
    // CCTableViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
};

class CcbActiveStageLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbActiveStageLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbActiveStageLayer);
};


#endif // __CCBACTIVESTAGELAYER__H__