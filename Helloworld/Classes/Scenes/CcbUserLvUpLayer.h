/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-07 14:40:36
*/

#ifndef __CCBUSERLVUPLAYER__H__
#define __CCBUSERLVUPLAYER__H__

//CcbUserLvUpLayer.h come from ccb/user_levelup.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbUserLvUpLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbUserLvUpLayer()
	{
        m_pLayerFuncBg = NULL;
        m_pSpriteText_GongNengKaiFang = NULL;
        m_pControlButtonClose = NULL;
        m_pLabelTTFCurEnergy = NULL;
        m_pLabelTTFNextEnergy = NULL;
        m_pLabelTTFLv = NULL;
        m_pLabelTTFCurStage = NULL;
        m_pLabelTTFNextStage = NULL;
        m_pSpriteStageUp = NULL;
        m_pLabelTTFLv_0 = NULL;
        m_pLabelTTFEquip_Lv1 = NULL;
        m_pLabelTTFEquip_Lv0 = NULL;
        m_pLabelTTFPet_Lv1 = NULL;
        m_pLabelTTFPet_Lv0 = NULL;

	}
	~CcbUserLvUpLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbUserLvUpLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerFuncBg;
    cocos2d::CCSprite* m_pSpriteText_GongNengKaiFang;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::CCLabelTTF* m_pLabelTTFCurEnergy;
    cocos2d::CCLabelTTF* m_pLabelTTFNextEnergy;
    cocos2d::CCLabelTTF* m_pLabelTTFLv;
    cocos2d::CCLabelTTF* m_pLabelTTFCurStage;
    cocos2d::CCLabelTTF* m_pLabelTTFNextStage;
    cocos2d::CCSprite* m_pSpriteStageUp;
    cocos2d::CCLabelTTF* m_pLabelTTFLv_0;
    cocos2d::CCLabelTTF* m_pLabelTTFEquip_Lv1;
    cocos2d::CCLabelTTF* m_pLabelTTFEquip_Lv0;
    cocos2d::CCLabelTTF* m_pLabelTTFPet_Lv1;
    cocos2d::CCLabelTTF* m_pLabelTTFPet_Lv0;

    CCNode *m_delegate;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void loadData();
    void setDelegate(CCNode *delegate){m_delegate = delegate;};
};

class CcbUserLvUpLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbUserLvUpLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbUserLvUpLayer);
};


#endif // __CCBUSERLVUPLAYER__H__