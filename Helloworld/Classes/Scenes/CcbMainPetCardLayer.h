/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-15 14:14:59
*/

#ifndef __CCBMAINPETCARDLAYER__H__
#define __CCBMAINPETCARDLAYER__H__

//CcbMainPetCardLayer.h come from ccb/main_petcard.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbMainPetCardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbMainPetCardLayer()
	{
		m_pSpritePet = NULL;
		m_pControlButtonPetcard = NULL;
		m_pSpriteLeader = NULL;
		m_pSpriteNature = NULL;
		m_pSpriteLvstar = NULL;
		m_pSpriteLock = NULL;
        m_pSpriteHasEquip = NULL;
        m_pSpriteHasAllEquip = NULL;
        m_pLabelTTFLv = NULL;
        m_pSpriteNormal = NULL;
        m_pSpritePlus = NULL;
        m_pSpriteLvStar = NULL;
        m_pSpriteCanEvo = NULL;
        m_pSpritePetType = NULL;

	}
	~CcbMainPetCardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbMainPetCardLayer, create);
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
	cocos2d::CCSprite* m_pSpritePet;
	cocos2d::extension::CCControlButton* m_pControlButtonPetcard;
	cocos2d::CCSprite* m_pSpriteLeader;
	cocos2d::CCSprite* m_pSpriteNature;
	cocos2d::CCSprite* m_pSpriteLvstar;
	cocos2d::CCSprite* m_pSpriteLock;
    cocos2d::CCSprite* m_pSpriteHasEquip;
    cocos2d::CCSprite* m_pSpriteHasAllEquip;
    cocos2d::CCLabelTTF* m_pLabelTTFLv;
    cocos2d::CCSprite* m_pSpriteNormal;
    cocos2d::CCSprite* m_pSpritePlus;
    cocos2d::CCSprite* m_pSpriteCanEvo;
    cocos2d::CCSprite* m_pSpriteLvStar;
    cocos2d::CCSprite* m_pSpritePetType;
    uint32 m_dwPetObjId;
    uint8 m_bySite;
    bool m_TouchFlag;
    bool m_isLock;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonPetcard(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void setPetObjIdAndSite(uint32 dwPetObjId, uint8 bySite);
    void setIsLeader(bool isLeader);
    void setIsLock(bool isLock);
    void hideAll();
};

class CcbMainPetCardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbMainPetCardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbMainPetCardLayer);
};


#endif // __CCBMAINPETCARDLAYER__H__