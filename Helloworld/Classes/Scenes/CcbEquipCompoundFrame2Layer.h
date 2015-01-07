/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-18 15:54:03
*/

#ifndef __CCBEQUIPCOMPOUNDFRAME2LAYER__H__
#define __CCBEQUIPCOMPOUNDFRAME2LAYER__H__

//CcbEquipCompoundFrame2Layer.h come from ccb/equip_compound_frame2.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipCompoundFrame2Layer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEquipCompoundFrame2Layer()
	{
		m_pSpriteIcon = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFNeedNum = NULL;
		m_pLabelTTFOwnNum = NULL;

	}
	~CcbEquipCompoundFrame2Layer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipCompoundFrame2Layer, create);
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
public:
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFNeedNum;
	cocos2d::CCLabelTTF* m_pLabelTTFOwnNum;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
public:
	// Funcitons

    CC_SYNTHESIZE(int, m_localTag, LocalTag);


};

class CcbEquipCompoundFrame2LayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipCompoundFrame2LayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipCompoundFrame2Layer);
};


#endif // __CCBEQUIPCOMPOUNDFRAME2LAYER__H__