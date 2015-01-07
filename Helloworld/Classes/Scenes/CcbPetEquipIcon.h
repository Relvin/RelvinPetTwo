/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-03-13 21:09:00
*/

#ifndef __CCBPETEQUIPICON__H__
#define __CCBPETEQUIPICON__H__

//CcbPetEquipIcon.h come from ccb/petshow_equip_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "EquipDataMgr.h"
#include "CCScrollButton.h"

class CcbPetEquipIcon:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetEquipIcon()
	{
		m_pSpriteBg = NULL;
		m_pSpriteIcon = NULL;
		m_pControlButtonEquip = NULL;
		m_pSpriteIconFrame = NULL;
		m_pLabelTTFItemName = NULL;
		m_pLabelTTFItemEvoLv = NULL;
		m_pLabelTTFLv = NULL;
		m_pSpriteStar = NULL;
        m_pSpriteNumBg = NULL;
        m_pLabelTTFNum = NULL;
        m_pLayerColorUnEnable = NULL;
        m_pSpriteHas = NULL;

	}
	~CcbPetEquipIcon();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetEquipIcon, create);
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
	cocos2d::CCSprite* m_pSpriteBg;
	cocos2d::CCSprite* m_pSpriteIcon;
	CCScrollButton* m_pControlButtonEquip;
	cocos2d::CCSprite* m_pSpriteIconFrame;
	cocos2d::CCLabelTTF* m_pLabelTTFItemName;
	cocos2d::CCLabelTTF* m_pLabelTTFItemEvoLv;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCSprite* m_pSpriteStar;
    cocos2d::CCSprite* m_pSpriteNumBg;
    cocos2d::CCLabelTTF* m_pLabelTTFNum;
    CCLayerColor *m_pLayerColorUnEnable;
    cocos2d::CCSprite* m_pSpriteHas;

    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


    void setEquipObjId(uint32 dwObjId);
    uint32 getEquipObjId(){return m_dwEquipObjId;};
    void loadData();
    void setEnable(bool enable);
    void setEquipType(uint8 type) { m_byEquipType = type; };
    
    void setClipRect(CCRect rect);
    
    void showName(bool isShow);
    
    void setIndex(uint32 index);
    void setLv(uint8 lv);
    
    void showStarLv(uint8 lv);
    void hideStarLv();
    
    void hideEvoLv();
    void hideLv();
    
    void setNum(uint8 byNum);
    
    void checkHasCanUse(uint8 pos);
    
    bool getHasCanUse(){return m_pSpriteHas->isVisible();};
private:
    uint32 m_dwEquipObjId;
    uint8 m_byEquipType;
	bool m_isEnable;
public:
	// Funcitons


	void onPressControlButtonEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbPetEquipIconLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetEquipIconLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetEquipIcon);
};


#endif // __CCBPETEQUIPICON__H__