/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-08 14:31:10
*/

#ifndef __CCBPETICON__H__
#define __CCBPETICON__H__

//CcbPetIcon.h come from ccb/pet_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"
#include <string>

class CcbPetIcon:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetIcon()
	{
		m_pSpritePet = NULL;
		m_pSpritePetFrame = NULL;
		m_pSpriteBg = NULL;
        m_pSpriteAttribute = NULL;
        m_pLabelTTFName = NULL;
        m_pSpriteVip = NULL;
	}
	~CcbPetIcon();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetIcon, create);
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
	
	cocos2d::CCSprite* m_pSpritePetFrame;
	cocos2d::CCSprite* m_pSpriteBg;
    cocos2d::CCSprite* m_pSpriteAttribute;
    cocos2d::CCSprite* m_pSpriteVip;
    CCLabelTTF* m_pLabelTTFName;
    uint16 m_wPetId;
    CCScrollButton *btn;
    uint32 m_dwPetObjiId;
    
    uint32 m_dwAccountId;
public:
    cocos2d::CCSprite* m_pSpritePet;
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void setOpacity(GLubyte opacity);
	
public:
	// Funcitons

    void setPetId(uint16 wPetId);
    uint16 getPetId(){return m_wPetId;};
    
    void setPetObjId(uint32 petObjiId);
    uint32 getPetObjId(){return m_dwPetObjiId;};
    void loadData();
    
    void loadObjData();
    
    void showAttribute(bool isShow);
    void setBtnEnable(bool enable);
    void setRect(CCRect rect);
    
    void showName();
    void hideName();
    
    /*!
     设置Icon名字
     */
    void setName(const char* _strName);
    
    /*!
     @brief 显示和隐藏VIP图标
     */
    void showVip();
    void hideVip();
    
    void setAccountId(uint32 accoundId){m_dwAccountId = accoundId;};
    
    CC_SYNTHESIZE(uint32, m_dwEmlemObjId, dwEmlemObjId);
private:
    void onSelected(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbPetIconLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetIconLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetIcon);
};


#endif // __CCBPETICON__H__