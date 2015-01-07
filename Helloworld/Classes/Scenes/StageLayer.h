/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-18 22:26:26
*/

#ifndef __STAGELAYER__H__
#define __STAGELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "CcbPadLayer.h"
#include "SystemMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemIconLayer;
class StageLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
,   public CObserverMsg
,   public PadLayerDelegate
,   public SystemMessageProtocol
{
public:
	// Constructor
	StageLayer()
    : m_pControlButtonFightBot(NULL)
	{
		m_pLayerHeaderBack = NULL;
		m_pControlButtonEditTeam = NULL;
		m_pLabelTTFGetCnt = NULL;
		m_pLayerUp = NULL;
		m_pLayerDown = NULL;
        m_pSpriteReward = NULL;
        m_pControlButtonStarGet = NULL;
        
        m_newTag = 0;
        m_fDelta = 0.04f;
//        m_vecCell.clear();
        m_bRestored = false;
        m_fCellHeight = 120.0f;
        m_pTableList = NULL;
        m_pLayerView = NULL;
        
        m_nTalkIdx = 0;
        m_bShowMapTalk = false;
	}
	~StageLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StageLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    static StageLayer* getCurLayer();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerHeaderBack;
	cocos2d::extension::CCControlButton* m_pControlButtonEditTeam;
	cocos2d::CCLabelTTF* m_pLabelTTFGetCnt;
	cocos2d::CCLayer* m_pLayerUp;
	cocos2d::CCLayer* m_pLayerDown;
    cocos2d::CCSprite* m_pSpriteReward;
    cocos2d::CCLayer* m_pLayerView;
    cocos2d::extension::CCControlButton* m_pControlButtonStarGet;
    cocos2d::extension::CCControlButton* m_pControlButtonStarGet_2;
    cocos2d::extension::CCControlButton* m_pControlButtonStarGet_3;
    cocos2d::extension::CCControlButton* m_pControlButtonFightBot;

    std::vector<CcbItemIconLayer*> m_vecRewardIcon;     // 奖励Icon}
    std::vector<cocos2d::CCNode*> m_vecNodeStars;       // 奖励Node}
    std::vector<cocos2d::CCLabelTTF*> m_vecStarCnt;     // 奖励所需星数}
    std::vector<cocos2d::extension::CCControlButton*> m_vecButtonGet;   // 奖励点击按钮}
    std::vector<cocos2d::CCSprite*> m_vecSpriteGet;     // 奖励已获得图标}
    
    int m_newTag;   // 在全部通关的关卡里面，newTag = -1，在其他关卡里面等于对应的最大的index数量}
    int m_nTableCnt;   // 列表数量}
    
    float m_fDelta;
    float m_fDelay;
    
    float m_fUpOffset;
    
    bool m_bRestored;
    void setTouchRestore();
    void addFullStarPos();
    
//    std::vector<CCLayer*> m_vecCell;
    
    CCSize winSize;
    float m_fCellWidth;
    float m_fCellHeight;
    float m_fUpBound, m_fDownBound;
    
    float m_fLeftGap;
    cocos2d::extension::CCTableView* m_pTableList;
    
    uint8 m_byStarRew;      // 星星获得数，偏移}
    cocos2d::CCRect m_rect;
    
    void tableCnt();
    
    int m_nTalkIdx;
    bool m_bShowMapTalk;
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    // CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(CCTableView *table);
    
    // ObserverDelegate
    virtual void RefeashLayer();
    // PadLayerDelegate
    virtual void showStep();
    // System Message Protocol
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
public:
	// Funcitons
	void onPressControlButtonEditTeam(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonGet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonFightBot(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class StageLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StageLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StageLayer);
};


#endif // __STAGELAYER__H__