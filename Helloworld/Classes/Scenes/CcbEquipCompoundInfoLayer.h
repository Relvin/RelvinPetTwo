/**
* equip_compound_info.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Relvin
* Date: 2014-10-29 12:22:05
*/

#ifndef __EQUIP_COMPOUND_INFO__H__
#define __EQUIP_COMPOUND_INFO__H__

//equip_compound_info.h come from ccb/equip_compound_info.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "WorldPacket.h"
#include "GameSession.h"

class CcbItemIconLayer;

class CcbEquipCompoundInfoLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
    
    static CcbEquipCompoundInfoLayer* shareInstance();
	// Constructor
    CcbEquipCompoundInfoLayer();
	~CcbEquipCompoundInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipCompoundInfoLayer, create);
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
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLabelTTF* m_pLabelTTFCostName;
	cocos2d::extension::CCControlButton* m_pControlButtonCompound;
	cocos2d::extension::CCControlButton* m_pControlButtonInlay;
	cocos2d::CCLabelTTF* m_pLabelTTFCostText;
	cocos2d::CCLabelTTF* m_pLabelTTFCostDollor;
	cocos2d::extension::CCControlButton* m_pControlButtonChooseDollor;
	cocos2d::CCSprite* m_pSpriteCross;
	cocos2d::CCLabelTTF* m_pLabelTTFRate;
	CcbItemIconLayer* m_pLayerIcon_Cost;
	cocos2d::CCLabelTTF* m_pLabelAttributes_Cost;
	cocos2d::CCLabelTTF* m_pLabelAttributes_Number1;
	CcbItemIconLayer* m_pLayerIcon_Result;
	cocos2d::CCLabelTTF* m_pLabelTTFResultName;
	cocos2d::CCLabelTTF* m_pLabelAttributes_Result;
	cocos2d::CCLabelTTF* m_pLabelAttributes_Number2;
	cocos2d::CCLabelTTF* m_pLabelTTFNeedNum;
	cocos2d::CCLabelTTF* m_pLabelTTFOwnNum;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::CCLabelTTF* m_pLabelTTFCostTitle;
    cocos2d::CCLabelTTF* m_pLabelTTFCostMoney;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    //Touch Functions
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
	
    //Self Functions
    void setEquipInfoByItemIndex(uint32 dwIndex);
    void setChooseCostState();
    void playFlashAnimation(CCNode *pNode);
    
    //Receive Functions
    void handlerRunesUpgradeResult(WorldPacket &packet);
    
    //
    
public:
	// Funcitons


	void onPressControlButtonCompound(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonInlay(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonChooseDollor(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void movementEventCallback(cocos2d::extension::CCArmature *pArmature, cocos2d::extension::MovementEventType moveEventType, const char *animateName);
private:
    uint32 m_dwItemId;
    uint32 m_dwRate;
    bool m_bIsCostDollor;
};

class CcbEquipCompoundInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipCompoundInfoLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipCompoundInfoLayer);
};


#endif // __EQUIP_COMPOUND_INFO__H__