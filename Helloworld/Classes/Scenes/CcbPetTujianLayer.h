/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-25 16:37:50
*/

#ifndef __CCBPETTUJIANLAYER__H__
#define __CCBPETTUJIANLAYER__H__

//CcbPetTujianLayer.h come from ccb/tujian.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "ConfigGet.h"
class CcbPetIcon;

class PetTujianScene:
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	// Constructor
	PetTujianScene()
	{
		m_pLabelTTFName = NULL;
	}
	~PetTujianScene();
    
    static cocos2d::CCScene *scene();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PetTujianScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLabelTTF* m_pLabelTTFName;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons

};


class CcbPetTujianLayer:
    public cocos2d::CCLayer,
    public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetTujianLayer()
	{
        m_pLayerBg = NULL;
        m_pLabelTTFPettype = NULL;
        m_pSpriteJinduBar = NULL;
        m_pLabelTTFJindu = NULL;
        m_pSpriteSelected = NULL;
        m_pControlButtonType1 = NULL;
        m_pControlButtonType2 = NULL;
        m_pControlButtonType3 = NULL;
        m_pControlButtonType4 = NULL;
        m_pControlButtonType5 = NULL;
        m_pControlButtonType6 = NULL;
        m_pNodeTitle = NULL;
        m_pNodeTop = NULL;
        
	}
	~CcbPetTujianLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetTujianLayer, create);
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
    cocos2d::CCLayer* m_pLayerBg;
    cocos2d::CCLabelTTF* m_pLabelTTFPettype;
    cocos2d::CCSprite* m_pSpriteJinduBar;
    cocos2d::CCLabelTTF* m_pLabelTTFJindu;
    cocos2d::CCSprite* m_pSpriteSelected;
    cocos2d::extension::CCControlButton* m_pControlButtonType1;
    cocos2d::extension::CCControlButton* m_pControlButtonType2;
    cocos2d::extension::CCControlButton* m_pControlButtonType3;
    cocos2d::extension::CCControlButton* m_pControlButtonType4;
    cocos2d::extension::CCControlButton* m_pControlButtonType5;
    cocos2d::extension::CCControlButton* m_pControlButtonType6;
    cocos2d::CCNode* m_pNodeTitle;
    cocos2d::CCNode* m_pNodeTop;
    cocos2d::extension::CCScrollView* m_scroll;

    cocos2d::extension::CCControlButton* arrBtn[7];
    
    
    float barWidth;
    uint8 m_curType;
    cocos2d::CCPoint m_off;
    cocos2d::CCRect m_clipRect;
    
    bool m_isOnEnter;
    int loadWaitTime;
    
private:
    void updateForWaitLoad(float time);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void onPressControlButtonType(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void loadData();


private:
    void selectType(uint8 type);

};

class CcbPetTujianLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetTujianLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetTujianLayer);
};


#endif // __CCBPETTUJIANLAYER__H__