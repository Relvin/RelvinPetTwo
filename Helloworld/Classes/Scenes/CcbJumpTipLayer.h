/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-11 15:49:48
*/

#ifndef __CCBJUMPTIPLAYER__H__
#define __CCBJUMPTIPLAYER__H__

//CcbJumpTipLayer.h come from ccb/jump.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum SHOW_JUMP_TIP
{
    E_SHOW_JUMP_NULL = 0,
    E_ITEM_NOT_ENOUGH       = 1,
    E_VIP_NOT_ENOUGH        = 2,
    E_PET_PACKAGE_FULL      = 1202,
    E_ITEM_PACKAGE_FULL     = 1504,
    E_POWER_NOT_ENOUGH      = 1000,
    E_MONEY_NOT_ENOUGH      = 1001,
    E_REPUTATION_NOT_ENOUGH = 1006,
    E_FUSE_STONE_NOT_ENOUGH = 1508,
    E_DOLLAR_NOT_ENOUGH     = 1003,
    
};

class CShowJumpTip : public Singleton<CShowJumpTip>
{
public:
    CShowJumpTip()
    {
        m_jumtType = E_SHOW_JUMP_NULL;
        m_itemId = 0;
    };
    void Show(SHOW_JUMP_TIP emType, uint32 itemId = 0);
    void Close();
    
    uint32 getNeedItemId(){return m_itemId;};
    void setNeedItemId(uint32 itemId){m_itemId = itemId;};
    
    SHOW_JUMP_TIP getJumpType(){return m_jumtType;};
    void setJumpType(SHOW_JUMP_TIP jumpType){m_jumtType = jumpType;};
private:
    uint32 m_itemId;
    SHOW_JUMP_TIP m_jumtType;
};

class CcbJumpTipLayer:
	public CCLayer
,	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbJumpTipLayer()
	{
        m_pControlButtonCancel = NULL;
		m_pLabelTTFContent = NULL;
		m_pLabelTTFTipTitle = NULL;
		m_pControlButtonGo = NULL;

	}
	~CcbJumpTipLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbJumpTipLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCControlButton* m_pControlButtonCancel;
	CCLabelTTF* m_pLabelTTFContent;
	CCLabelTTF* m_pLabelTTFTipTitle;
    CCControlButton* m_pControlButtonGo;

    CCPoint m_posButton1;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void SetShowJumpTip(SHOW_JUMP_TIP emType, uint32 itemId);
    SHOW_JUMP_TIP m_emShowJumpTipType;
public:
	// Funcitons


	void onPressControlButtonCancel(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonGo(CCObject* pSender, CCControlEvent event);



};

class CcbJumpTipLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbJumpTipLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbJumpTipLayer);
};


#endif // __CCBJUMPTIPLAYER__H__