/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-28 21:22:53
*/

#ifndef __CCBTEAMMEMBERLAYER__H__
#define __CCBTEAMMEMBERLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
USING_NS_CC;
USING_NS_CC_EXT;


class CCScrollButton;

class CcbTeamMemberLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbTeamMemberLayer()
	{
		m_pSpritePet = NULL;
		m_pLayerValue = NULL;
		m_pSpritePetType = NULL;
		m_pSpriteAttribute = NULL;
		m_pSpriteLeaderMark = NULL;
		m_pLabelTTFLv = NULL;
		m_pLayerNormal = NULL;
		m_pControlButtonPetcard = NULL;
		m_pSpriteLock = NULL;
        m_pLabelTTFFightValue = NULL;
        m_pSpriteLvStar = NULL;
        m_pSpriteNormal = NULL;
        m_pSpritePlus = NULL;
        m_isButtonTouchEnable = false;
        m_pNodeTip = NULL;
        m_bCanTouchBtn = false;
	}
	~CcbTeamMemberLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTeamMemberLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFFightValue;
	cocos2d::CCLayer* m_pLayerValue;
	cocos2d::CCSprite* m_pSpritePetType;
	cocos2d::CCSprite* m_pSpriteAttribute;
	cocos2d::CCSprite* m_pSpriteLeaderMark;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCLayer* m_pLayerNormal;
	CCScrollButton* m_pControlButtonPetcard;
	cocos2d::CCSprite* m_pSpriteLock;
    cocos2d::CCSprite* m_pSpriteLvStar;
    cocos2d::CCSprite* m_pSpriteNormal;
    cocos2d::CCSprite* m_pSpritePlus;
    cocos2d::CCNode* m_pNodeTip;
    
    uint16 m_wPetObjId;
    uint8 m_bySite;
    bool m_isTouchEnable;
    bool m_isLock;
    bool m_isButtonTouchEnable;
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setPetObjIdAndSite(uint16 wPetObjId, uint8 bySite);
    uint16 getPetObjId();
    void setSite(uint8 site){m_bySite = site;};
    uint8 getSite(){return m_bySite;};
    void ShowBaseValue(bool bIsShow);
    void setIsLeader(bool bIsLeader);
    
    void setButtonTouchEnable(bool enable){ m_isButtonTouchEnable = enable;};
    void setTouchEnable(bool enable){ m_isTouchEnable = enable;};
    void setIsLock(bool lock);
    bool isLock(){return m_isLock;};
    
    void onSetMember();
private:
    void loadData();
    
public:
	// Funcitons
    

    void onPressControlButtonPetcard(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbTeamMemberLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTeamMemberLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTeamMemberLayer);
};


#endif // __CCBTEAMMEMBERLAYER__H__