/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-18 22:25:47
*/

#ifndef __STAGENODE__H__
#define __STAGENODE__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Observer.h"
#include "SystemMessageProtocol.h"
#include "StageScene.h"

class CCScrollButton;
class CcbItemIconLayer;
class StageNode:
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
	StageNode() {
		m_pControlButtonStage = NULL;
		m_pLayerIcon = NULL;
		m_pLayerDrop = NULL;
		m_pControlButtonSaoDang = NULL;
		m_pControlButtonFight = NULL;
		m_pSpriteNew = NULL;
		m_pLabelTTFLeftCnt = NULL;
		m_pLabelTTFEnergy = NULL;
		m_pLabelTTFName = NULL;
		m_pSpriteAttribute = NULL;
		m_pSpriteClear = NULL;
        m_pNodeBoss = NULL;
        m_pSpriteSweep = NULL;
        m_pLabelTTFTicketNum = NULL;
        
        m_wStageId = 0;
        m_nSelectedStage = 0;
        m_byCostEnergy = 255;
        m_byAttackCnt = 255;
        m_byMaxAttCnt = 255;
        m_wIconId = 0;
        m_byStarCnt = 255;
        m_wLimiteLv = 0;
        m_vecDropId.clear();
        m_pTableView = NULL;
        m_nPetCnt = m_nItemCnt = 0;
        m_wLeftCnt = 0;
        m_wBuyCnt = 0;
        m_wLeftBuyCnt = 0;
        m_bNew = false;
        m_bCanTouchBtn = false;
	}
	~StageNode();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StageNode, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
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
	CCScrollButton* m_pControlButtonStage;     // 自身Button，可点击}
	CcbItemIconLayer* m_pLayerIcon;             // 关卡头像Icon}

    cocos2d::CCLayer* m_pLayerDrop;

	CCScrollButton* m_pControlButtonSaoDang;   // 扫荡按钮}
	CCScrollButton* m_pControlButtonFight;     // 战斗按钮}
	cocos2d::CCSprite* m_pSpriteNew;            // 新关卡动画}
	cocos2d::CCLabelTTF* m_pLabelTTFLeftCnt;    // 剩余次数}
	cocos2d::CCLabelTTF* m_pLabelTTFEnergy;     // 消耗活力}
	cocos2d::CCLabelTTF* m_pLabelTTFName;       // 关卡名称}
	cocos2d::CCSprite* m_pSpriteAttribute;      // 关卡属性}
	cocos2d::CCSprite* m_pSpriteClear;          // 关卡通关标示}
    cocos2d::CCNode* m_pNodeBoss;
    cocos2d::CCSprite* m_pSpriteSweep;
    cocos2d::CCLabelTTF* m_pLabelTTFTicketNum;
    
    uint16 m_wStageId;          // 选中的StageId}
    int m_nSelectedStage;       // 选中的Stage的Idx，不是选中的StageId}

    std::vector<cocos2d::CCSprite*> m_vecStarts;
    
    void setInfo();
    
    uint8 m_byCostEnergy;       // 记录原先的消耗体力，如果不变则不改变labelTTF的值}
    uint8 m_byAttackCnt;        // 记录原先已经攻击次数}
    uint8 m_byMaxAttCnt;        // 记录原先最大攻击次数}
    uint16 m_wIconId;           // 记录头像IconId}
    uint8 m_byStarCnt;          // 记录星数}
    uint16 m_wLimiteLv;     // 限制进入等级，只在活动中使用]}
    uint16 m_wLeftCnt;      // 剩余次数}
    int m_nPetCnt, m_nItemCnt;  // 宠物和物品数量}
    uint16 m_wLeftBuyCnt;       // 剩余购买次数
    uint16 m_wBuyCnt;           // 已经购买次数
    bool m_bNew;            // 是否是新关卡
    
    std::vector<uint32> m_vecDropId;
    
    cocos2d::extension::CCTableView* m_pTableView;
    
    cocos2d::CCRect m_rect;
    
    void showBuyMessage(int _param);
    void updateLeftCnt(StageCtrl::STC_STAGE stc);
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void SetNodeData(int idx);
    virtual void RefeashLayer();
    void setClipRect(cocos2d::CCRect rect);
public:
    void onPressControlButtonSaoDang(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonFight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    // CCTableViewDelegate
    // CCTableViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell) {}
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
};

class StageNodeLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StageNodeLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StageNode);
};


#endif // __STAGENODE__H__