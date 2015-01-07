/**
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Junie Chu
 * Date: 2014-05-28 15:23:25
 */

#ifndef __CCBGEMLISTFRAMELAYER__H__
#define __CCBGEMLISTFRAMELAYER__H__

//CcbGemListFrameLayer.h come from ccb/gem_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollButton.h"
#include "ShopDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbGemListFrameLayer:
public CCLayer,
public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
    // Constructor
    CcbGemListFrameLayer()
    : m_pPayItemInfo(NULL)
    , _animationManager(NULL)
    {
        m_pControlButtonRecharge = NULL;
        m_pLabelTTFRmb = NULL;
        m_pLabelTTFBuy = NULL;
        m_pNodeBuyCard = NULL;
        m_pNodeBuyDiamond = NULL;
        m_pLabelTTFExternGet = NULL;
        m_pLabelTTFDayNum = NULL;
        m_pLabelTTFOnlyOnce = NULL;
    }
    ~CcbGemListFrameLayer();
    
    // Create Method
    static CcbGemListFrameLayer* createCCNode(cocos2d::CCNode *pParent, cocos2d::extension::CCBReader *pCCBReader);
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGemListFrameLayer, create);
    // Inhert MemberVariableAssigner
    virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
    virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
    // Inhert CCBSelectorResolver
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
    // Inhert CCNodeLoaderListener
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    void setAnimationManager(cocos2d::extension::CCBAnimationManager *animationMgr);
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    // Attributes for CCB
public:
    CCScrollButton* m_pControlButtonRecharge;
    CCLabelTTF* m_pLabelTTFRmb;
    CCLabelTTF* m_pLabelTTFBuy;
    CCNode* m_pNodeBuyCard;
    CCNode* m_pNodeBuyDiamond;
    CCLabelTTF* m_pLabelTTFExternGet;
    CCLabelTTF* m_pLabelTTFDayNum;
    CCLabelTTF* m_pLabelTTFOnlyOnce;
public:
    // Virtual Functions
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
public:
    // Funcitons
    void setChargeInfo(uint32 dwGoodsId);
    void setChargeNodeInfo();
    void setClipRect(CCRect rect);
    void onPressControlButtonRecharge(CCObject* pSender, CCControlEvent event);
    
private:
    cocos2d::extension::CCBAnimationManager *_animationManager;
    STORE_PAY_LIST_INFO *m_pPayItemInfo;
    
};

class CcbGemListFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGemListFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
//    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGemListFrameLayer);
    virtual CcbGemListFrameLayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        return CcbGemListFrameLayer::createCCNode(pParent, pCCBReader);
    }
};


#endif // __CCBGEMLISTFRAMELAYER__H__