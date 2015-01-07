/**
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Junie Chu
 * Date: 2014-03-24 17:49:26
 */

#ifndef __CCBSHOPGEMLISTLAYER__H__
#define __CCBSHOPGEMLISTLAYER__H__

//CcbShopGemListLayer.h come from ccb/shop_gem_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ShopDataMgr.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbVipListLayer;

class CcbShopGemListLayer
: public CCLayer
, public CCBMemberVariableAssigner
, public CCBSelectorResolver
, public CCNodeLoaderListener
, public CCTableViewDataSource
, public CObserverMsg
, public CObserverRole
{
public:
    // Constructor
    CcbShopGemListLayer();
    
    ~CcbShopGemListLayer();
    
    static CcbShopGemListLayer* shareInstance();
    
    // Create Method
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShopGemListLayer, create);
    // Inhert MemberVariableAssigner
    virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
    virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
    // Inhert CCBSelectorResolver
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
    // Inhert CCNodeLoaderListener
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    //tableView相关}
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    void refreshLayer();
    virtual void byVipLvChanged(uint8 byVipLv);
    virtual void dwVipExpChanged(uint32 dwVipExp);
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    // Attributes for CCB
    CCLayer* m_pLayerGemList;
    CCLayer* m_pLayerParent;
    CCControlButton* m_pControlButtonGotoVIP;
    CCControlButton* m_pControlButtonBackShopgem;
    CCLabelTTF* m_pLabelTTFCurVip;
    CCLabelTTF* m_pLabelTTFNextVip;
    CCLabelTTF* m_pLabelTTFText1;
    CCLabelTTF* m_pLabelTTFDollarToNext;
    CCLabelTTF* m_pLabelTTFText2;
    CCSprite* m_pSpriteVipProcess;
    CCNode* m_pTiplessVip2;
    CCScale9Sprite* m_pScale9VipBg;
    
    CCTableView* m_pTableViewTabGem;
    VEC_PAY_LIST_INFO m_vecShowList;
    
    CCRect m_clipRect;
    
    void SetVipData();
public:
    // Virtual Functions
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
    
    
public:
    // Funcitons
    
    void onPressControlButtonGotoVIP(CCObject* pSender, CCControlEvent event);
    
private:
    CcbVipListLayer* m_pVipListLayer;
    float m_fVipProcessWidth;
    
};

class CcbShopGemListLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShopGemListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShopGemListLayer);
};


#endif // __CCBSHOPGEMLISTLAYER__H__