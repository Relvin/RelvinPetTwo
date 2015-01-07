/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-22 15:44:52
*/

#ifndef __CCBEVENTMYSTERYSHOPLAYER__H__
#define __CCBEVENTMYSTERYSHOPLAYER__H__

//CcbEventMySteryShopLayer.h come from ccb/event_mysteryshop.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbEventMySteryShopFrameLayer.h"
#include "Defines.h"
#include "SystemMessageProtocol.h"


class CcbMySteryShopScene:public CCLayer
{
public:
    CcbMySteryShopScene();
    ~CcbMySteryShopScene();
    
    CREATE_FUNC(CcbMySteryShopScene);
    //virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    
};

class CcbEventMySteryShopLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbEventMySteryShopLayer()
	{
        m_curScene = NULL;
        
        m_pLayerEventViewSize = NULL;
        m_pControlButtonRefresh = NULL;
        m_pLabelTTFTime = NULL;
        m_pLabelTTFRefCnt = NULL;
        m_pLayerBottom2 = NULL;
        m_pLabelTTFNum = NULL;
        m_pControlButtonFuse = NULL;
        m_pNodeShoperMystery = NULL;
        m_pLabelTTFLeftTime = NULL;
        m_pNodeShoperMJ = NULL;
        m_pControlButtonMysteryShop = NULL;
        m_pControlButtonMJShop = NULL;
        m_pLabelTTFMJLeftTime = NULL;
        m_pLayerTop = NULL;
	}
	~CcbEventMySteryShopLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEventMySteryShopLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    //tableView相关}
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerEventViewSize;
    cocos2d::extension::CCControlButton* m_pControlButtonRefresh;
    cocos2d::CCLabelTTF* m_pLabelTTFTime;
    cocos2d::CCLabelTTF* m_pLabelTTFRefCnt;
    cocos2d::CCLayer* m_pLayerBottom2;
    cocos2d::CCLabelTTF* m_pLabelTTFNum;
    cocos2d::extension::CCControlButton* m_pControlButtonFuse;
    cocos2d::CCNode* m_pNodeShoperMystery;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftTime;
    cocos2d::CCNode* m_pNodeShoperMJ;
    cocos2d::extension::CCControlButton* m_pControlButtonMysteryShop;
    cocos2d::extension::CCControlButton* m_pControlButtonMJShop;
    cocos2d::CCLabelTTF* m_pLabelTTFMJLeftTime;
    cocos2d::CCLayer* m_pLayerTop;
    

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

private:
    static CcbEventMySteryShopLayer* m_curScene;
    
    uint32 m_dwCostRock;
    uint32 m_dwCostDollar;
    std::vector<STC_STERY_GOODS> arrGoods;
    cocos2d::extension::CCTableView *m_table;
    cocos2d::CCPoint curOff;
    cocos2d::CCSprite* m_pSpriteRole;
	
    CCRect m_clipRect;
    
    int refTime;
    int refMjTime;
private:
    void updateForTime(float time);
    void updateForMJTime(float time);
public:
	// Funcitons
    static CcbEventMySteryShopLayer* getCurScene(){return m_curScene;};
    
    void loadData();
    
    void onPressControlButtonRefresh(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonFuse(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonMysteryShop(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonMJShop(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


};

class CcbEventMySteryShopLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEventMySteryShopLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEventMySteryShopLayer);
};


#endif // __CCBEVENTMYSTERYSHOPLAYER__H__