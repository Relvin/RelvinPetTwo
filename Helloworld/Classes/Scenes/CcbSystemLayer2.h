/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-20 11:34:35
*/

#ifndef __CCBSYSTEMLAYER2__H__
#define __CCBSYSTEMLAYER2__H__

//CcbSystemLayer2.h come from ccb/message2.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum SHOW_MSG_TYPE
{
    E_TYPE_POWER    = 1,
    E_TYPE_ITEM_BAG = 2,
    E_TYPE_PET_BAG  = 3,
    E_TYPE_GET_COIN = 4,
    E_TYPE_ITEM_BAG_FULL = 5,
    E_TYPE_PET_BAG_FULL = 6,
};

class CSystemMessage2 : public Singleton<CSystemMessage2>
{
public:
    void Show(SHOW_MSG_TYPE emType, uint32 dwCount1, uint32 dwCount2);
    void Refeash(uint32 dwCount1, uint32 dwCount2);
    void Close();
    void SetMsgType(SHOW_MSG_TYPE emType) { m_emType = emType; };
    SHOW_MSG_TYPE GetMsgType(){ return m_emType; };
    SHOW_MSG_TYPE m_emType;
};


class CcbSystemLayer2:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbSystemLayer2()
	{
		m_pLayerColor = NULL;
		m_pLabelTTFTipTitle = NULL;
		m_pLabelTTFContentTitle = NULL;
		m_pLabelTTFText1 = NULL;
		m_pLabelTTFText2 = NULL;
		m_pSpriteArrowRight = NULL;
		m_pLabelTTFText3 = NULL;
		m_pSpriteArrowUp = NULL;
		m_pLayerTextParent = NULL;
		m_pControlButtonOk = NULL;
		m_pControlButtonCancel = NULL;
		m_pControlButtonClose = NULL;

	}
	~CcbSystemLayer2();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSystemLayer2, create);
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
    
    SHOW_MSG_TYPE m_emMsgType;
    void SetShowMsg(SHOW_MSG_TYPE emType, uint32 dwCount1, uint32 dwCount2);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCLayer* m_pLayerColor;
	CCLabelTTF* m_pLabelTTFTipTitle;
	CCLabelTTF* m_pLabelTTFContentTitle;
	CCLabelTTF* m_pLabelTTFText1;
	CCLabelTTF* m_pLabelTTFText2;
	CCSprite* m_pSpriteArrowRight;
	CCLabelTTF* m_pLabelTTFText3;
	CCSprite* m_pSpriteArrowUp;
	CCLayer* m_pLayerTextParent;
	CCControlButton* m_pControlButtonOk;
	CCControlButton* m_pControlButtonCancel;
	CCControlButton* m_pControlButtonClose;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonOk(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonCancel(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonClose(CCObject* pSender, CCControlEvent event);

};

class CcbSystemLayer2Loader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSystemLayer2Loader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSystemLayer2);
};


#endif // __CCBSYSTEMLAYER2__H__