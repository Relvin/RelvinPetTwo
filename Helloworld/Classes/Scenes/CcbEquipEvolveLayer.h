/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-03 14:54:49
*/

#ifndef __CCBEQUIPEVOLVELAYER__H__
#define __CCBEQUIPEVOLVELAYER__H__

//CcbEquipEvolveLayer.h come from ccb/equip_evo.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipEvolveLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbEquipEvolveLayer()
	{
		m_pLayerIcon = NULL;
		m_pSpriteStar = NULL;
		m_pLabelTTFLevel = NULL;
		m_pLabelTTFAttriType1 = NULL;
		m_pSpriteAttr1 = NULL;
		m_pLabelTTFAttri1 = NULL;
		m_pLabelTTFAttriType2 = NULL;
		m_pSpriteAttr2 = NULL;
		m_pLabelTTFAttri2 = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFEvoLv = NULL;
		m_pLayerParent2 = NULL;
		m_pLayerNextIcon = NULL;
		m_pSpriteNextStar = NULL;
		m_pLabelTTFNextName = NULL;
		m_pLabelTTFNextEvoLv = NULL;
		m_pLabelTTFNeedLevelText = NULL;
		m_pLabelTTFNeedLevel = NULL;
		m_pLabelTTFNextAttriType1 = NULL;
		m_pSpriteNextAttr1 = NULL;
		m_pLabelTTFNextAttri1 = NULL;
		m_pLabelTTFNextAttriType2 = NULL;
		m_pSpriteNextAttr2 = NULL;
		m_pLabelTTFNextAttri2 = NULL;
		m_pSpriteCurStar = NULL;
		m_pLayerCurIcon = NULL;
		m_pLabelTTFCurName = NULL;
		m_pLabelTTFCurEvoLv = NULL;
		m_pLabelTTFCurLevel = NULL;
		m_pLabelTTFCurAttriType1 = NULL;
		m_pSpriteCurAttr1 = NULL;
		m_pLabelTTFCurAttri1 = NULL;
		m_pLabelTTFCurAttriType2 = NULL;
		m_pSpriteCurAttr2 = NULL;
		m_pLabelTTFCurAttri2 = NULL;
		m_pLayerElem_1 = NULL;
		m_pLabelTTFItemHaveNum1 = NULL;
		m_pLabelTTFItemNeedNum1 = NULL;
		m_pNodeParent1 = NULL;
		m_pLayerElem_2 = NULL;
		m_pLabelTTFItemHaveNum2 = NULL;
		m_pLabelTTFItemNeedNum2 = NULL;
		m_pNodeParent2 = NULL;
		m_pControlButtonEvolve = NULL;
		m_pLayerParent1 = NULL;

	}
	~CcbEquipEvolveLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipEvolveLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CcbItemIconLayer* m_pLayerIcon;
	CCSprite* m_pSpriteStar;
	CCLabelTTF* m_pLabelTTFLevel;
	CCLabelTTF* m_pLabelTTFAttriType1;
	CCSprite* m_pSpriteAttr1;
	CCLabelTTF* m_pLabelTTFAttri1;
	CCLabelTTF* m_pLabelTTFAttriType2;
	CCSprite* m_pSpriteAttr2;
	CCLabelTTF* m_pLabelTTFAttri2;
	CCLabelTTF* m_pLabelTTFName;
	CCLabelTTF* m_pLabelTTFEvoLv;
	CCLayer* m_pLayerParent2;
	CcbItemIconLayer* m_pLayerNextIcon;
	CCSprite* m_pSpriteNextStar;
	CCLabelTTF* m_pLabelTTFNextName;
	CCLabelTTF* m_pLabelTTFNextEvoLv;
	CCLabelTTF* m_pLabelTTFNeedLevelText;
	CCLabelTTF* m_pLabelTTFNeedLevel;
	CCLabelTTF* m_pLabelTTFNextAttriType1;
	CCSprite* m_pSpriteNextAttr1;
	CCLabelTTF* m_pLabelTTFNextAttri1;
	CCLabelTTF* m_pLabelTTFNextAttriType2;
	CCSprite* m_pSpriteNextAttr2;
	CCLabelTTF* m_pLabelTTFNextAttri2;
	CCSprite* m_pSpriteCurStar;
	CcbItemIconLayer* m_pLayerCurIcon;
	CCLabelTTF* m_pLabelTTFCurName;
	CCLabelTTF* m_pLabelTTFCurEvoLv;
	CCLabelTTF* m_pLabelTTFCurLevel;
	CCLabelTTF* m_pLabelTTFCurAttriType1;
	CCSprite* m_pSpriteCurAttr1;
	CCLabelTTF* m_pLabelTTFCurAttri1;
	CCLabelTTF* m_pLabelTTFCurAttriType2;
	CCSprite* m_pSpriteCurAttr2;
	CCLabelTTF* m_pLabelTTFCurAttri2;
	CcbItemIconLayer* m_pLayerElem_1;
	CCLabelTTF* m_pLabelTTFItemHaveNum1;
	CCLabelTTF* m_pLabelTTFItemNeedNum1;
	CCNode* m_pNodeParent1;
	CcbItemIconLayer* m_pLayerElem_2;
	CCLabelTTF* m_pLabelTTFItemHaveNum2;
	CCLabelTTF* m_pLabelTTFItemNeedNum2;
	CCNode* m_pNodeParent2;
	extension::CCControlButton* m_pControlButtonEvolve;
	CCLayer* m_pLayerParent1;


    struct STC_EQUIP_EVO_SHOW_INFO
    {
        uint32 wIndex;
        uint8 byEvoLv;
        uint8 byLv;
        std::string strName;
        uint8 byStar;
        uint8 byType1;
        uint8 byType2;
        uint32 dwValue1;
        uint32 dwValue2;
        STC_EQUIP_EVO_SHOW_INFO()
        {
            byType1 = 0;
            byType2 = 0;
        };
    };
    
    std::map<uint8, std::vector<CCNode*> >mapAllNode;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    static CcbEquipEvolveLayer* getCurScene(){return m_curScene;};
    static CcbEquipEvolveLayer* m_curScene;
    
	void CreateEquipData();
    void ResetData();
    bool m_isConditionsEnough;
public:
	// Funcitons


	void onPressControlButtonEvolve(CCObject* pSender, CCControlEvent event);



};

class CcbEquipEvolveLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipEvolveLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipEvolveLayer);
};


#endif // __CCBEQUIPEVOLVELAYER__H__