/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-18 15:54:03
*/

#ifndef __CCBEQUIPCOMPOUNDFRAME1LAYER__H__
#define __CCBEQUIPCOMPOUNDFRAME1LAYER__H__

//CcbEquipCompoundFrame1Layer.h come from ccb/equip_compound_frame1.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollButton.h"
#include "CcbItemIconLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipCompoundFrame1Layer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEquipCompoundFrame1Layer()
	{
		m_pLayerIcon = NULL;
		m_pControlButtonShowInfo = NULL;
		m_pLabelTTFName = NULL;
//		m_pLabelTTFEquipAttri1 = NULL;
//		m_pLabelTTFEquipAttri2 = NULL;
//		m_pSpriteStar = NULL;
        m_pLabelTTFDesc = NULL;
//        m_localTag = 0;
	}
	~CcbEquipCompoundFrame1Layer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipCompoundFrame1Layer, create);
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
	CcbItemIconLayer* m_pLayerIcon;
	CCScrollButton* m_pControlButtonShowInfo;
	CCLabelTTF* m_pLabelTTFName;
//	CCLabelTTF* m_pLabelTTFEquipAttri1;
//	CCLabelTTF* m_pLabelTTFEquipAttri2;
    CCLabelTTF* m_pLabelTTFDesc;
//	CCSprite* m_pSpriteStar;
    
    uint32 m_index;
    bool m_touchFlag;
//    void CreateRuneInfo();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
public:
	// Funcitons

	void onPressControlButtonShowInfo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


    void loadData(uint32 index);
    void setClipRect(CCRect rect);
    void setBtnEnable(bool enable);
};

class CcbEquipCompoundFrame1LayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipCompoundFrame1LayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipCompoundFrame1Layer);
};


#endif // __CCBEQUIPCOMPOUNDFRAME1LAYER__H__