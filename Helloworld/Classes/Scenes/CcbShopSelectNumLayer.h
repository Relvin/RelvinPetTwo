/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-26 18:22:28
*/

#ifndef __CCBSHOPSELECTNUMLAYER__H__
#define __CCBSHOPSELECTNUMLAYER__H__

//CcbShopSelectNumLayer.h come from ccb/shop_select_num.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbItemIconLayer;
class CcbShopSelectNumLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
{
public:
	// Constructor
	CcbShopSelectNumLayer()
    : m_pControlButtonMax(NULL)
	{
		m_pScale9SpriteNum = NULL;
		m_pControlButtonPlus = NULL;
		m_pControlButtonMinus = NULL;
		m_pControlButtonConfirm = NULL;
		m_pControlButtonCancel = NULL;
        m_pEditBoxNum = NULL;
        m_pControlButtonClose = NULL;
        m_pLabelTTFCost = NULL;
        m_pLabelTTFItemNum = NULL;
        m_pLabelTTFItem = NULL;
        m_pNodeItemicon = NULL;
        m_pLabelTTFCanBuyCnt = NULL;
        
	}
	~CcbShopSelectNumLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShopSelectNumLayer, create);
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
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteNum;
	cocos2d::extension::CCControlButton* m_pControlButtonPlus;
	cocos2d::extension::CCControlButton* m_pControlButtonMinus;
	cocos2d::extension::CCControlButton* m_pControlButtonConfirm;
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::CCLabelTTF* m_pLabelTTFCost;
    cocos2d::CCLabelTTF* m_pLabelTTFItemNum;
    cocos2d::CCLabelTTF* m_pLabelTTFItem;
    cocos2d::extension::CCEditBox* m_pEditBoxNum;
    CcbItemIconLayer* m_pNodeItemicon;
    cocos2d::CCLabelTTF* m_pLabelTTFCanBuyCnt;
    cocos2d::extension::CCControlButton* m_pControlButtonMax;
    
    uint16 m_maxCnt;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
    void setMaxCnt(uint16 maxCnt);
    
private:
    int checkNum(int num);
public:
	// Funcitons
	void onPressControlButtonPlus(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonMinus(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonConfirm(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonMax(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
};

class CcbShopSelectNumLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShopSelectNumLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShopSelectNumLayer);
};


#endif // __CCBSHOPSELECTNUMLAYER__H__