/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-17 20:58:38
*/

#ifndef __CCBPETSHOWLAYER__H__
#define __CCBPETSHOWLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "Observer.h"
#include "SystemMessageProtocol.h"
#include "CcbItemIconLayer.h"
#include "CcbPetEquipIcon.h"
#include "Equip.h"
#include "Pet.h"
#include "CcbHaloLightLayer.h"
#include "Observer.h"


class CcbPetShowTitle;
class CcbPetShowBackLayer;
class CcbPetInfoLayer;

class CcbPetShowScene:
public cocos2d::CCLayer
{
public:
	// Constructor
	CcbPetShowScene()
	{
        
	}
	~CcbPetShowScene();
    
    static cocos2d::CCScene *scene();
    CREATE_FUNC(CcbPetShowScene);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
};

class CcbPetShowLayer:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
,   public CObserverRole
{
public:
    
	// Constructor
	CcbPetShowLayer()
    : m_pNodeShareReward(NULL)
	{
        m_pSpriteBg = NULL;
        m_pLayerBack = NULL;
        m_pLayerHaloLight = NULL;
        m_pLayerLeft = NULL;
        m_pLayerRight = NULL;
        m_pSpritePaint = NULL;
        m_pLayerEquip1 = NULL;
        m_pLayerEquip3 = NULL;
        m_pLayerEmblem1 = NULL;
        m_pLayerEquip2 = NULL;
        m_pLayerEquip4 = NULL;
        m_pLayerEmblem2 = NULL;
        m_pControlButtonUp = NULL;
        m_pControlButtonStrong = NULL;
        m_pControlButtonYijian = NULL;
        m_pControlButtonChange = NULL;
        m_pSpriteExp = NULL;
        m_pLabelTTFProperty = NULL;
        m_pSpritePetType = NULL;
        m_pLabelTTF_Text_SkillInfo = NULL;
        m_pLabelTTFNormal_AtkName = NULL;
        m_pLabelTTFSkill_alkName = NULL;
        m_pLabelTTFHp = NULL;
        m_pLabelTTFRec = NULL;
        m_pLabelTTFAtt = NULL;
        m_pLabelTTFCrit = NULL;
        m_pLabelTTFCDef = NULL;
        m_pLabelTTFSDef = NULL;
        m_pControlButtonShowSkill = NULL;
        m_pLayerFlash = NULL;
        m_pControlButtonWeiBo = NULL;
        m_pControlButtonWeiXin = NULL;
        m_pLayerShare = NULL;
        m_pLayerBottom = NULL;
        m_curScene = NULL;
        m_pet = NULL;
        
        m_pControlButtonEmblem_1 = NULL;
        m_pControlButtonEmblem_2 = NULL;
        m_pSpriteEmblemHas_1 = NULL;
        m_pSpriteEmblemHas_2 = NULL;
        
        m_pLabelTTFPetLv = NULL;
        m_pSpriteCanEvo = NULL;
        
        m_pLabelTTFJiPan1 = NULL;
        m_pLabelTTFJiPan2 = NULL;
        m_pLabelTTFJiPan3 = NULL;
        m_pLabelTTFJiPan4 = NULL;
        
        m_pLabelTTFBadage1 = NULL;
        m_pLabelTTFBadage2 = NULL;
        
        m_petInfo = NULL;
        
        m_bCanTouchBtn =false;
	}
	~CcbPetShowLayer();

//    static cocos2d::CCScene *scene(uint32 wObjectId);
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetShowLayer, create);
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
	virtual void systemMessageCancelTapped(SystemMessage *systemMessage);
	
    static CcbPetShowLayer* m_curScene;
    static CcbPetShowLayer* getCurScene(){return m_curScene;};
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB

	CcbPetShowBackLayer* m_pLayerBack;
	CcbItemIconLayer* m_pLayerEmblem1;
	CcbItemIconLayer* m_pLayerEmblem2;
	CcbPetEquipIcon* m_pLayerEquip1;
	CcbPetEquipIcon* m_pLayerEquip3;
	CcbPetEquipIcon* m_pLayerEquip2;
	CcbPetEquipIcon* m_pLayerEquip4;
    CcbHaloLightLayer* m_pLayerHaloLight;
    CCLayer* m_pLayerLeft;
    CCLayer* m_pLayerRight;
    CCLayer* m_pLayerShare;
    CCLayer* m_pLayerBottom;
    cocos2d::CCSprite* m_pSpriteBg;
    cocos2d::CCSprite* m_pSpritePaint;
    cocos2d::CCSprite* m_pSpriteExp;
    cocos2d::CCLabelTTF* m_pLabelTTFProperty;
    cocos2d::CCSprite* m_pSpritePetType;
    cocos2d::CCLabelTTF* m_pLabelTTF_Text_SkillInfo;
    cocos2d::CCLabelTTF* m_pLabelTTFNormal_AtkName;
    cocos2d::CCLabelTTF* m_pLabelTTFSkill_alkName;
    cocos2d::CCLabelTTF* m_pLabelTTFHp;
    cocos2d::CCLabelTTF* m_pLabelTTFRec;
    cocos2d::CCLabelTTF* m_pLabelTTFAtt;
    cocos2d::CCLabelTTF* m_pLabelTTFCrit;
    cocos2d::CCLabelTTF* m_pLabelTTFCDef;
    cocos2d::CCLabelTTF* m_pLabelTTFSDef;
    cocos2d::CCLabelTTF* m_pLabelTTFPetLv;
    cocos2d::extension::CCControlButton* m_pControlButtonEmblem_1;
    cocos2d::extension::CCControlButton* m_pControlButtonEmblem_2;
    cocos2d::CCSprite* m_pSpriteEmblemHas_1;
    cocos2d::CCSprite* m_pSpriteEmblemHas_2;
    
    cocos2d::extension::CCControlButton* m_pControlButtonShowSkill;
    cocos2d::CCLayer* m_pLayerFlash;
    cocos2d::extension::CCControlButton* m_pControlButtonWeiBo;
    cocos2d::extension::CCControlButton* m_pControlButtonWeiXin;
    
    cocos2d::extension::CCControlButton* m_pControlButtonUp;
    cocos2d::extension::CCControlButton* m_pControlButtonStrong;
    cocos2d::extension::CCControlButton* m_pControlButtonYijian;
    cocos2d::extension::CCControlButton* m_pControlButtonChange;
    
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan1;
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan2;
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan3;
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan4;
    cocos2d::CCLabelTTF* m_pLabelTTFBadage1;
    cocos2d::CCLabelTTF* m_pLabelTTFBadage2;
    
    cocos2d::CCSprite* m_pSpriteCanEvo;
    cocos2d::CCNode* m_pNodeShareReward;
    
    uint32 m_wObjectId;
    bool isfriend;
    bool isShareChange;
    CCPoint m_tTouchPoint;
    float m_fTouchLength;
    int curPage;

    std::vector<uint32> m_arrPetObjId;
    
    CcbPetEquipIcon* arrEquip[4];
    CCSprite* arrEquipSprite[4];
    CCLabelTTF* arrQyName[6];
    CCLabelTTF* arrEmName[2];
    
    std::vector<CCNode*> arrUnTouchNode;

    CcbPetInfoLayer * m_petInfo;

    unsigned int m_soundId;
    
    CPet* m_pet;
    CCPoint m_petPos;
    float expBarW;
public:
    static bool m_bIsChangePetEnable;
    static bool cmpEquip(uint32 equipKeyID1, uint32 equipKeyID2);
private:
    
    void loadPetData();
    void changePage();
    
    void relocateContainer();
    
    void putOnTheBestEquip();
    
    static bool cmpEmblem(uint32 emblemKeyID1, uint32 emblemKeyID2);
    
    void addGuideLayer();
    
    void shareChangeEnd(){
        isShareChange = false;
    };
    
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void setOpacity(GLubyte opacity);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);
    
    virtual void dwShareCntChanged(uint32 dwShareCnt);
public:
	// Funcitons
//    void onPressControlButtonLock(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonWeiBo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonWeiXin(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonUp(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonStrong(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonYijian(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonShowSkill(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonChange(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void onPressControlButtonEmblem(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void setPetObjectId(uint32 wObjectId);
    
    void setChangePetEnable(bool isEnable){m_bIsChangePetEnable = isEnable;};

    void RefeashLayer();
    
//    void showSkillAwave(uint32 skillId);
//    void showSkillInject(uint32 skillId);
//    
//    void reflashSkill(uint32 dwSkillId);
    void reflachEquip(std::vector<uint32> arrEquipId, std::vector<uint8> arrPos);
    
//    int m_isHaveDelta[5];
//    uint32 m_dwDelta[5];
    void ShowFlyLayer();
//    void DelayShowAtkFly();
//    void DelayShowDefFly();
//    void DelayShowLifeFly();
//    void DelayShowRecoverFly();
//    void DelayShowLuckFly();
    
    void handleOtherRoleInfo(WorldPacket& packet);
    
    void listenToBackFromNotification(cocos2d::CCObject *pObject);
};

class CcbPetShowLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetShowLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetShowLayer);
};


#endif // __CCBPETSHOWLAYER__H__