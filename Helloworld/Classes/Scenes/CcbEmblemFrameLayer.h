/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-07 16:01:47
*/

#ifndef __CCBEMBLEMFRAMELAYER__H__
#define __CCBEMBLEMFRAMELAYER__H__

//CcbEmblemFrameLayer.h come from ccb/badge_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"
#include "CcbPetIcon.h"
#include "CcbItemIconLayer.h"

class CcbEmblemFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEmblemFrameLayer()
	{
		m_pLabelTTFName = NULL;
		m_pSpriteStar = NULL;
		m_pSpriteArrow1 = NULL;
		m_pLayerPet = NULL;
		m_pLabelTTFPetName = NULL;
		m_pSpritePetStar = NULL;
		m_pLabelTTFLevel = NULL;
		m_pLabelTTFAttri1 = NULL;
		m_pLabelTTFAttri2 = NULL;
		m_pLabelTTFAttri3 = NULL;
		m_pControlButtonStrengthen = NULL;
        m_pLabelTTFAttr_1 = NULL;
        m_pLabelTTFAttr_2 = NULL;
        m_pLabelTTFAttr_3 = NULL;
        m_pLayerIcon = NULL;
	}
	~CcbEmblemFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEmblemFrameLayer, create);
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

	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCSprite* m_pSpriteStar;
	cocos2d::CCSprite* m_pSpriteArrow1;
	CcbPetIcon* m_pLayerPet;
	cocos2d::CCLabelTTF* m_pLabelTTFPetName;
	cocos2d::CCSprite* m_pSpritePetStar;
	cocos2d::CCLabelTTF* m_pLabelTTFLevel;
	cocos2d::CCLabelTTF* m_pLabelTTFAttri1;
    cocos2d::CCLabelTTF* m_pLabelTTFAttri2;
    cocos2d::CCLabelTTF* m_pLabelTTFAttri3;
	CCScrollButton* m_pControlButtonStrengthen;
    CcbItemIconLayer* m_pLayerIcon;
    
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_1;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_2;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_3;

    uint32 m_dwEmblemObjId;
    float fEmStarW;
    float fPetStarW;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
	void onPressControlButtonStrengthen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEmbInfo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void setEmblemObjId(uint32 dwEmbObjId);
    void loadData();
    
    void setRect(CCRect rect);
private:

};

class CcbEmblemFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEmblemFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEmblemFrameLayer);
};


#endif // __CCBEMBLEMFRAMELAYER__H__