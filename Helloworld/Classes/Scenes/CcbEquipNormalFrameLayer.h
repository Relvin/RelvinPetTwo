/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-18 18:15:51
*/

#ifndef __CCBEQUIPNORMALFRAMELAYER__H__
#define __CCBEQUIPNORMALFRAMELAYER__H__

//CcbEquipNormalFrameLayer.h come from ccb/equip_normal_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbItemIconLayer.h"
#include "CCScrollButton.h"

class CcbEquipNormalFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEquipNormalFrameLayer()
	{
		m_pSpriteRune1 = NULL;
		m_pSpriteRune2 = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFState = NULL;
		m_pLabelTTFEquipAttri1 = NULL;
		m_pLabelTTFEquipAttri2 = NULL;
		m_pLabelTTFRuneAttri1 = NULL;
		m_pLabelTTFRuneAttri2 = NULL;
        m_pLabelTTFEquipAttriText1 = NULL;
        m_pLabelTTFEquipAttriText2 = NULL;
        m_pLabelTTFRuneAttriText1 = NULL;
        m_pLabelTTFRuneAttriText2 = NULL;
		m_pControlButtonEvo = NULL;
		m_pControlButtonStrengthen = NULL;
		m_pLayerIcon = NULL;

	}
	~CcbEquipNormalFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipNormalFrameLayer, create);
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
	cocos2d::CCSprite* m_pSpriteRune1;
	cocos2d::CCSprite* m_pSpriteRune2;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFState;
	cocos2d::CCLabelTTF* m_pLabelTTFEquipAttri1;
	cocos2d::CCLabelTTF* m_pLabelTTFEquipAttri2;
	cocos2d::CCLabelTTF* m_pLabelTTFRuneAttri1;
	cocos2d::CCLabelTTF* m_pLabelTTFRuneAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFEquipAttriText1;
    cocos2d::CCLabelTTF* m_pLabelTTFEquipAttriText2;
    cocos2d::CCLabelTTF* m_pLabelTTFRuneAttriText1;
    cocos2d::CCLabelTTF* m_pLabelTTFRuneAttriText2;
	CCScrollButton* m_pControlButtonEvo;
	CCScrollButton* m_pControlButtonStrengthen;
	CcbItemIconLayer* m_pLayerIcon;


    uint32 m_dwEquipObjId;
    uint8 m_byType;
    uint8 m_bySite;
    bool m_bTouchFlag;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonEvo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonStrengthen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadData(uint32 dwEquipObjId);
    void setFrameType(uint8 type);
    void setTeamSite(uint8 site){m_bySite = site;};
    void setClipRect(CCRect rect);
private:
    
    void onWear();
    void onDown();
    void onEnhance();
    void onRune();
    void onEvo();
};

class CcbEquipNormalFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipNormalFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipNormalFrameLayer);
};


#endif // __CCBEQUIPNORMALFRAMELAYER__H__