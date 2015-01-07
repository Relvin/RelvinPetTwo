/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-08 11:38:39
*/

#ifndef __CCBEMBLEMENHANCELAYER__H__
#define __CCBEMBLEMENHANCELAYER__H__

//CcbEmblemEnhanceLayer.h come from ccb/badge_strengthen.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "WorldPacket.h"
#include "CcbItemIconLayer.h"


class EmblemEnhanceScene :
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    EmblemEnhanceScene() {
        m_pLabelTTFName = NULL;
    };
    ~EmblemEnhanceScene();
    
    static cocos2d::CCScene* scene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EmblemEnhanceScene, create);
    
    virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

class CcbEmblemEnhanceLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEmblemEnhanceLayer()
	{
        m_pLayerIcon = NULL;
        m_pSpriteStar = NULL;
        m_pLabelTTFName = NULL;
        m_pSpriteBar = NULL;
        m_pLabelTTFNextLevel = NULL;
        m_pSpriteArrow1 = NULL;
        m_pLabelTTFCurLevel = NULL;
        m_pLabelTTFCurAttri1 = NULL;
        m_pSpriteArrow2 = NULL;
        m_pLabelTTFNextAttri1 = NULL;
        m_pLabelTTFCurAttri2 = NULL;
        m_pSpriteArrow3 = NULL;
        m_pLabelTTFNextAttri2 = NULL;
        m_pLabelTTFCurAttri3 = NULL;
        m_pSpriteArrow4 = NULL;
        m_pLabelTTFNextAttri3 = NULL;
        m_pLabelTTFAttr_1 = NULL;
        m_pLabelTTFAttr_2 = NULL;
        m_pLabelTTFAttr_3 = NULL;
        m_pSpriteEmBg = NULL;
        m_pLayerElem5 = NULL;
        m_pControlButtonElem5 = NULL;
        m_pSprite_plus_5 = NULL;
        m_pLayerElem4 = NULL;
        m_pControlButtonElem4 = NULL;
        m_pSprite_plus_4 = NULL;
        m_pLayerElem3 = NULL;
        m_pControlButtonElem3 = NULL;

        m_pSprite_plus_3 = NULL;
        m_pLayerElem2 = NULL;
        m_pControlButtonElem2 = NULL;

        m_pSprite_plus_2 = NULL;
        m_pLayerElem1 = NULL;
        m_pControlButtonElem1 = NULL;

        m_pSprite_plus_1 = NULL;
        m_pLabelTTFGetExp = NULL;
        m_pLabelTTFNeedExp = NULL;
        m_pControlButtonAutoAdd = NULL;
        m_pControlButtonStrengthen = NULL;

	}
	~CcbEmblemEnhanceLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEmblemEnhanceLayer, create);
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
    cocos2d::CCSprite* m_pSpriteStar;
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    cocos2d::CCSprite* m_pSpriteBar;
    cocos2d::CCLabelTTF* m_pLabelTTFNextLevel;
    cocos2d::CCSprite* m_pSpriteArrow1;
    cocos2d::CCLabelTTF* m_pLabelTTFCurLevel;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttri1;
    cocos2d::CCSprite* m_pSpriteArrow2;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttri1;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttri2;
    cocos2d::CCSprite* m_pSpriteArrow3;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFCurAttri3;
    cocos2d::CCSprite* m_pSpriteArrow4;
    cocos2d::CCLabelTTF* m_pLabelTTFNextAttri3;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_1;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_2;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_3;
    cocos2d::CCSprite* m_pSpriteEmBg;
    CcbItemIconLayer* m_pLayerElem5;
    cocos2d::extension::CCControlButton* m_pControlButtonElem5;
    cocos2d::CCSprite* m_pSprite_plus_5;
    CcbItemIconLayer* m_pLayerElem4;
    cocos2d::extension::CCControlButton* m_pControlButtonElem4;
    cocos2d::CCSprite* m_pSprite_plus_4;
    CcbItemIconLayer* m_pLayerElem3;
    cocos2d::extension::CCControlButton* m_pControlButtonElem3;
//    cocos2d::CCLabelTTF* m_pLabelTTFElemLv3;
    cocos2d::CCSprite* m_pSprite_plus_3;
    CcbItemIconLayer* m_pLayerElem2;
    cocos2d::extension::CCControlButton* m_pControlButtonElem2;
//    cocos2d::CCLabelTTF* m_pLabelTTFElemLv2;
    cocos2d::CCSprite* m_pSprite_plus_2;
    CcbItemIconLayer* m_pLayerElem1;
    cocos2d::extension::CCControlButton* m_pControlButtonElem1;
//    cocos2d::CCLabelTTF* m_pLabelTTFElemLv1;
    cocos2d::CCSprite* m_pSprite_plus_1;
    cocos2d::CCLabelTTF* m_pLabelTTFGetExp;
    cocos2d::CCLabelTTF* m_pLabelTTFNeedExp;
    cocos2d::extension::CCControlButton* m_pControlButtonAutoAdd;
    cocos2d::extension::CCControlButton* m_pControlButtonStrengthen;
    
    
private:
    
    float expBarWidth;
    
    float fEmStarW;
    static CcbEmblemEnhanceLayer* m_curScene;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void onPressControlButtonElem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAutoAdd(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonStrengthen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadData();
    void loadElem();
    
    
    static CcbEmblemEnhanceLayer* getCurScene(){return m_curScene;};
    void handlerEnhanceResult(WorldPacket& packet);
private:
    
    
    void updateForCheckSelected(float time);
};

class CcbEmblemEnhanceLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEmblemEnhanceLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEmblemEnhanceLayer);
};


#endif // __CCBEMBLEMENHANCELAYER__H__