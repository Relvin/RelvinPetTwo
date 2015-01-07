/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-17 18:03:55
*/

#ifndef __CCBEQUIPSTRENGTHENLAYER__H__
#define __CCBEQUIPSTRENGTHENLAYER__H__

//CcbEquipStrengthenLayer.h come from ccb/equip_strengthen.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "EffectLayer.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipStrengthenLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEquipStrengthenLayer()
	{
        m_pControlButtonEvolve = NULL;
        m_pLabelTTFEvoMoney = NULL;
        m_pLabelTTFCoin = NULL;
        m_pLayerElem_1 = NULL;
        m_pLayerEvoIcon = NULL;
        m_pLayer_no_1 = NULL;
        m_pSprite_no_1 = NULL;
        m_pLabelTTFItemHaveNum1 = NULL;
        m_pLabelTTFItemNeedNum1 = NULL;
        m_pNodeParent1 = NULL;
        m_pLayerElem_2 = NULL;
        m_pLayer_no_2 = NULL;
        m_pSprite_no_2 = NULL;
        m_pLabelTTFItemHaveNum2 = NULL;
        m_pLabelTTFItemNeedNum2 = NULL;
        m_pNodeParent2 = NULL;
        m_pNodeEvo = NULL;
        m_pNodeUnevo = NULL;
        m_pLayerNextIcon = NULL;
        m_pLabelTTFNextName = NULL;
        m_pLabelTTFCurAttriType1 = NULL;
        m_pLabelTTFEvoCurAttri1 = NULL;
        m_pLabelTTFEvoNextAttri1 = NULL;
        m_pLabelTTFNextAttriType1 = NULL;
        m_pLabelTTFCurAttriType2 = NULL;
        m_pLabelTTFEvoCurAttri2 = NULL;
        m_pLabelTTFEvoNextAttri2 = NULL;
        m_pLabelTTFNextAttriType2 = NULL;
        m_pLayerCurIcon = NULL;
        m_pLabelTTFCurName = NULL;
        m_pLayerEvo = NULL;
        m_pLayerSuit = NULL;
        m_pLabelTTFSuit_1 = NULL;
        m_pLabelTTFSuitDes_1 = NULL;
        m_pLabelTTFSuit_2 = NULL;
        m_pLabelTTFSuitDes_2 = NULL;
        m_pLabelTTFSuit_3 = NULL;
        m_pLabelTTFSuitDes_3 = NULL;
        m_pLayerIcon = NULL;
        m_pLabelTTFName = NULL;
        m_pLabelTTFAttriType1 = NULL;
        m_pLabelTTFCurAttri1 = NULL;
        m_pLabelTTFNextAttri1 = NULL;
        m_pLabelTTFAttriType2 = NULL;
        m_pLabelTTFCurAttri2 = NULL;
        m_pLabelTTFNextAttri2 = NULL;
        m_pControlButtonStrengthen = NULL;
        m_pControlButtonStrengthenMAX = NULL;
        m_pLabelTTFCostMoney = NULL;
        m_pLabelTTFCoin_2 = NULL;
        m_pLabelTTFCurStrength = NULL;
        m_pLabelTTFCurLevel = NULL;
        m_pLabelTTFNextLevel = NULL;
        m_pLayerStrengthen = NULL;
        m_pLabelEvoCurName = NULL;
        
        m_pLabelEnhCurAttriType1 = NULL;
        m_pLabelEnhCurAttri1 = NULL;
        m_pLabelEnhCurAttriType2 = NULL;
        m_pLabelEnhCurAttri2 = NULL;
        m_pLabelEnhNextAttri1 = NULL;
        m_pLabelEnhNextAttri2 = NULL;
        m_pLabelTTFCurAttriType1_2 = NULL;
        m_pLabelTTFCurAttriType2_2 = NULL;
        m_pLabelTTFEvoCoin = NULL;
        
        m_bCanTouchBtn = false;
        byShowLayerType = 0;
	}
	~CcbEquipStrengthenLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipStrengthenLayer, create);
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
	CcbItemIconLayer* m_pLayerElem_1;
	CcbItemIconLayer* m_pLayerElem_2;
    CcbItemIconLayer* m_pLayerCurIcon;
    CcbItemIconLayer* m_pLayerEvoIcon;
	CcbItemIconLayer* m_pLayerNextIcon;
    CcbItemIconLayer* m_pLayerIcon;

    cocos2d::extension::CCControlButton* m_pControlButtonEvolve;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoMoney;
    cocos2d::CCLabelTTF* m_pLabelTTFCoin;
    cocos2d::CCLayer* m_pLayer_no_1;
    cocos2d::CCSprite* m_pSprite_no_1;
    cocos2d::CCLabelTTF* m_pLabelTTFItemHaveNum1;
    cocos2d::CCLabelTTF* m_pLabelTTFItemNeedNum1;
    cocos2d::CCNode* m_pNodeParent1;
    cocos2d::CCLayer* m_pLayer_no_2;
    cocos2d::CCSprite* m_pSprite_no_2;
    cocos2d::CCLabelTTF* m_pLabelTTFItemHaveNum2;
    cocos2d::CCLabelTTF* m_pLabelTTFItemNeedNum2;
    cocos2d::CCNode* m_pNodeParent2;
    cocos2d::CCNode* m_pNodeEvo;
    cocos2d::CCNode* m_pNodeUnevo;
    cocos2d::CCLabelTTF* m_pLabelTTFNextName;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttriType1;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoCurAttri1;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoNextAttri1;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttriType1;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttriType2;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoCurAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoNextAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttriType2;
    cocos2d::CCLabelTTF* m_pLabelTTFCurName;
    cocos2d::CCLayer* m_pLayerEvo;
    cocos2d::CCLayer* m_pLayerSuit;
    cocos2d::CCLabelTTF* m_pLabelTTFSuit_1;
    cocos2d::CCLabelTTF* m_pLabelTTFSuitDes_1;
    cocos2d::CCLabelTTF* m_pLabelTTFSuit_2;
    cocos2d::CCLabelTTF* m_pLabelTTFSuitDes_2;
    cocos2d::CCLabelTTF* m_pLabelTTFSuit_3;
    cocos2d::CCLabelTTF* m_pLabelTTFSuitDes_3;
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    cocos2d::CCLabelTTF* m_pLabelTTFAttriType1;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttri1;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttri1;
    cocos2d::CCLabelTTF* m_pLabelTTFAttriType2;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttri2;
    cocos2d::extension::CCControlButton* m_pControlButtonStrengthen;
    cocos2d::extension::CCControlButton* m_pControlButtonStrengthenMAX;
    cocos2d::CCLabelTTF* m_pLabelTTFCostMoney;
    cocos2d::CCLabelTTF* m_pLabelTTFCoin_2;
    cocos2d::CCLabelTTF* m_pLabelTTFCurStrength;
    cocos2d::CCLabelTTF* m_pLabelTTFCurLevel;
    cocos2d::CCLabelTTF* m_pLabelTTFNextLevel;
    cocos2d::CCLayer* m_pLayerStrengthen;
    cocos2d::CCLabelTTF* m_pLabelEvoCurName;
    
    cocos2d::CCLabelTTF* m_pLabelEnhCurAttriType1;
    cocos2d::CCLabelTTF* m_pLabelEnhCurAttri1;
    cocos2d::CCLabelTTF* m_pLabelEnhCurAttriType2;
    cocos2d::CCLabelTTF* m_pLabelEnhCurAttri2;
    cocos2d::CCLabelTTF* m_pLabelEnhNextAttri1;
    cocos2d::CCLabelTTF* m_pLabelEnhNextAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttriType1_2;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttriType2_2;
    cocos2d::CCLabelTTF* m_pLabelTTFEvoCoin;
    
    
    void addGuideLayer();
    
    uint32 arrPerValue[2];
    
    static CcbEquipStrengthenLayer* m_curScene;
    
    uint8 byEnhCnt; //强化的数量（1：单次强化，大于1：最大强化）}
    
    bool m_isNeedFly;
    
    bool m_bCanTouchBtn;
    void restoreTouch();
    
    uint8 byShowLayerType;  // 0 = enhLayer /1= evoLayer
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

	void handlerEnh();
    void handlerEvo();
    
    void loadEnhData();
    void loadEvoData();
    
private:
    

public:
	// Funcitons
    void CreateEquipData();
    static CcbEquipStrengthenLayer* getCurScene(){return m_curScene;};
    
	void onPressControlButtonStrengthen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonStrengthenMAX(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonEvolve(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


};

class CcbEquipStrengthenLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipStrengthenLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipStrengthenLayer);
};


#endif // __CCBEQUIPSTRENGTHENLAYER__H__