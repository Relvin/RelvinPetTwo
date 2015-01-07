/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-26 21:39:25
*/

#ifndef __CCBTUJIANSHOWLAYER__H__
#define __CCBTUJIANSHOWLAYER__H__

//CcbTujianShowLayer.h come from ccb/tujian_show.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbPetShowTitle.h"
#include "CcbPetSkillLayer.h"
#include "CcbPetShowBackLayer.h"
#include "CcbHaloLightLayer.h"
//#include "CcbPetSkillIcon.h"

class PetTujianShowScene : cocos2d::CCLayer
{
public:
    PetTujianShowScene();
    ~PetTujianShowScene();
    static cocos2d::CCScene * scene();
    CREATE_FUNC(PetTujianShowScene);
    bool init();
    
    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
};

class CcbTujianShowLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbTujianShowLayer()
	{
        m_pSpriteBg = NULL;
        m_pLayerHaloLight = NULL;
        m_pSpritePaint = NULL;
        m_pSpriteStar = NULL;
        m_pLabelTTFName = NULL;
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
        m_pLayerBottom = NULL;
        m_pLayerTitle = NULL;
        m_pLayerBack = NULL;
        
        m_pLabelTTFJiPan1 = NULL;
        m_pLabelTTFJiPan2 = NULL;
        m_pLabelTTFJiPan3 = NULL;
        m_pLabelTTFJiPan4 = NULL;
        m_pLabelTTFBadage1 = NULL;
        m_pLabelTTFBadage2 = NULL;
        
	}
	~CcbTujianShowLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTujianShowLayer, create);
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
	CcbPetShowBackLayer* m_pLayerBack;
    CcbHaloLightLayer* m_pLayerHaloLight;
    cocos2d::CCSprite* m_pSpritePaint;
    cocos2d::CCSprite* m_pSpriteStar;
    cocos2d::CCLabelTTF* m_pLabelTTFName;
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
    cocos2d::extension::CCControlButton* m_pControlButtonShowSkill;
    cocos2d::CCLayer* m_pLayerBottom;
    cocos2d::CCLayer* m_pLayerTitle;
    CCLayer* m_pLayerStarBg;
    
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan1;
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan2;
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan3;
    cocos2d::CCLabelTTF* m_pLabelTTFJiPan4;
    cocos2d::CCLabelTTF* m_pLabelTTFBadage1;
    cocos2d::CCLabelTTF* m_pLabelTTFBadage2;
    
    
    bool m_bLock3s;
    void addGuideLayer();
    bool m_canTouch;
    bool m_bStep1End;
    bool m_bStep2End;
    
    cocos2d::CCLabelTTF* arrQyName[6];
    CCLabelTTF* arrEmName[2];
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
	
public:
	// Funcitons
    void onPressControlButtonShowSkill(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

//    void showSkillAwave(uint32 dwSkillId);
    
    static bool m_bTouchThenBack;
private:
    uint16 m_petIndex;
    uint32 m_soundId;
    
    uint8 curStarCnt;
    uint8 maxStarCnt;
    void showOnePet();
    void addStar(float time);
    void showText(uint8 type, uint8 star);
    void showTitleABottom();
    void step1End();
    void step2End();
    
    void showGuide();

    void loadData();


};

class CcbTujianShowLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTujianShowLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTujianShowLayer);
};


#endif // __CCBTUJIANSHOWLAYER__H__
