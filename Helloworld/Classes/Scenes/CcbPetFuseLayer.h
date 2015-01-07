/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-21 17:15:37
*/

#ifndef __CCBPETFUSELAYER__H__
#define __CCBPETFUSELAYER__H__

//CcbPetFuseLayer.h come from ccb/pet_fuse.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbPetIcon.h"
#include "WorldPacket.h"
#include "SystemMessage.h"
#include "SystemMessageProtocol.h"
#include "EffectLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PetFuseScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    PetFuseScene();
    ~PetFuseScene();
    
    CREATE_FUNC(PetFuseScene);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    CCLabelTTF* m_pLabelTTFName;
};



class CcbPetFuseLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
,   public EffectLayerProtocol
{
public:
	// Constructor
	CcbPetFuseLayer()
	{
        m_curScene = NULL;
		m_pControlButtonAddpet = NULL;
		m_pControlButtonAddequip = NULL;
		m_pControlButtonShop = NULL;
		m_pControlButtonDes = NULL;
		m_pLayerElem1 = NULL;
		m_pLayerElem2 = NULL;
		m_pLayerElem3 = NULL;
		m_pLayerElem4 = NULL;
		m_pControlButtonFuse = NULL;
        m_pSprite_add_1 = NULL;
        m_pSprite_add_2 = NULL;
        m_pSprite_add_3 = NULL;
        m_pSprite_add_4 = NULL;
        m_pLayerElem = NULL;
	}
	~CcbPetFuseLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetFuseLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
	void addGuideLayer();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonAddpet;
	cocos2d::extension::CCControlButton* m_pControlButtonAddequip;
	cocos2d::extension::CCControlButton* m_pControlButtonShop;
	cocos2d::extension::CCControlButton* m_pControlButtonDes;
	CcbPetIcon* m_pLayerElem1;
	CcbPetIcon* m_pLayerElem2;
	CcbPetIcon* m_pLayerElem3;
	CcbPetIcon* m_pLayerElem4;
    cocos2d::CCSprite* m_pSprite_add_1;
    cocos2d::CCSprite* m_pSprite_add_2;
    cocos2d::CCSprite* m_pSprite_add_3;
    cocos2d::CCSprite* m_pSprite_add_4;
	cocos2d::extension::CCControlButton* m_pControlButtonFuse;
    CCLayer* m_pLayerElem;

    static CcbPetFuseLayer* m_curScene;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    virtual void onActionOver();
	
public:
	// Funcitons
	void onPressControlButtonAddpet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonAddEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonShop(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonDes(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonFuse(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
private:
    bool isPetFuse;
    std::vector<CcbPetIcon*> arrElem;
    uint32 m_dwNeedMoney;
    uint32 m_wGetFuse;
    std::vector<uint32> arrId;
    std::vector<CCSprite*> arrElemAdd;

    void autoAddEquip();
    void showGet( CCNode* getLayer,void *vptr);
public:
    static CcbPetFuseLayer* GetCurScene(){return m_curScene;};
    void loadData();
    void handlerPetFuseResult(WorldPacket &packet);
};

class CcbPetFuseLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetFuseLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetFuseLayer);
};


#endif // __CCBPETFUSELAYER__H__