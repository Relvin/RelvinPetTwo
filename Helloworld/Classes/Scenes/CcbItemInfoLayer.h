/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-12 17:55:10
*/

#ifndef __CCBITEMINFOLAYER__H__
#define __CCBITEMINFOLAYER__H__

//CcbItemInfoLayer.h come from ccb/item_info.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton.h"
#include "Defines.h"


USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemIconLayer;


class CShowItemInfo : public Singleton<CShowItemInfo>
{
public:
    void Show(uint32 dwItemID);
    void Close();
    

};

class CcbItemInfoLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbItemInfoLayer()
	{
		m_pLabelTTFItemName = NULL;
		m_pLabelTTFItemText = NULL;
		m_pControlButtonOk = NULL;
		m_pLayerIcon = NULL;
		m_pLabelTTFPro_2 = NULL;
//		m_pSpritePro_2 = NULL;
		m_pLayerPro_2 = NULL;
		m_pLabelTTFPro_1 = NULL;
//		m_pSpritePro_1 = NULL;
		m_pLayerPro_1 = NULL;
		m_pControlButtonClose = NULL;
        m_pLabelTTFProText_1 = NULL;
        m_pLabelTTFProText_2 = NULL;
	}
	~CcbItemInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemInfoLayer, create);
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
//	CCSprite* m_pSpriteIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFItemName;
	cocos2d::CCLabelTTF* m_pLabelTTFItemText;
	cocos2d::extension::CCControlButton* m_pControlButtonOk;
//	cocos2d::CCLayer* m_pLayerIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFPro_2;
//	cocos2d::CCSprite* m_pSpritePro_2;
	cocos2d::CCLayer* m_pLayerPro_2;
	cocos2d::CCLabelTTF* m_pLabelTTFPro_1;
//	cocos2d::CCSprite* m_pSpritePro_1;
	cocos2d::CCLayer* m_pLayerPro_1;
	cocos2d::extension::CCControlButton* m_pControlButtonClose;
    CcbItemIconLayer* m_pLayerIcon;
    cocos2d::CCLabelTTF* m_pLabelTTFProText_1;
    cocos2d::CCLabelTTF* m_pLabelTTFProText_2;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    
public:
	// Funcitons
    void setItemID(uint32 dwItemID);

	void onPressControlButtonOk(CCObject* pSender, CCControlEvent event);



};

class CcbItemInfoLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbItemInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbItemInfoLayer);
};


#endif // __CCBITEMINFOLAYER__H__