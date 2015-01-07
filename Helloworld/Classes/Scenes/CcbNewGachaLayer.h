/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-27 19:56:52
*/

#ifndef __CCBNEWGACHALAYER__H__
#define __CCBNEWGACHALAYER__H__

//CcbNewGachaLayer.h come from ccb/gacha_new.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SystemMessage.h"
#include "Defines.h"

class CcbGachaBoardLayer;

class CcbNewGachaLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbNewGachaLayer()
	{
        m_pControlButtonGoCharge = NULL;
        m_pControlButtonTicket = NULL;
        m_pSpriteTicket = NULL;
        m_pLabelTTFTicket = NULL;
        m_pLabelTTFFreeTimes = NULL;
        m_pNodeFree = NULL;
        m_pSpriteTip1 = NULL;
        m_pControlButtonDiamond = NULL;
        m_pLabelTTFTime = NULL;
        m_pSpriteTip2 = NULL;
        
        m_GachaBoardLayer = NULL;
	}
	~CcbNewGachaLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbNewGachaLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    static CcbNewGachaLayer* GetCurScene();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::extension::CCControlButton* m_pControlButtonGoCharge;
    cocos2d::extension::CCControlButton* m_pControlButtonTicket;
    cocos2d::CCSprite* m_pSpriteTicket;
    cocos2d::CCLabelTTF* m_pLabelTTFTicket;
    cocos2d::CCLabelTTF* m_pLabelTTFFreeTimes;
    cocos2d::CCNode* m_pNodeFree;
    cocos2d::CCSprite* m_pSpriteTip1;
    cocos2d::extension::CCControlButton* m_pControlButtonDiamond;
    cocos2d::CCLabelTTF* m_pLabelTTFTime;
    cocos2d::CCSprite* m_pSpriteTip2;

    CcbGachaBoardLayer* m_GachaBoardLayer;
    
    int m_nTicketCnt;
    int m_nCurDollar;
    int m_dwLeftTime;
    int m_dwFreeLeftTime;
    
    void addGuideLayer();
    void changeToFree();
    void updateTime(float cTime);
    void showGachaBoard();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
    // System Message Protocol
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    
    void handlerDollarShow(uint32 dwDollar);
    void setLeftTime();
    void setFreeLeftTime();
public:
	// Funcitons
    void loadData();
    
	void onPressControlButtonGoCharge(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonTicket(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonDiamond(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbNewGachaLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbNewGachaLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbNewGachaLayer);
};


#endif // __CCBNEWGACHALAYER__H__