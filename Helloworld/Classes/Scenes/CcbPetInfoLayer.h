/**
* CcbPetInfoLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-10-23 10:26:01
*/

#ifndef __CCBPETINFOLAYER__H__
#define __CCBPETINFOLAYER__H__

//CcbPetInfoLayer.h come from ccb/pet_information.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Pet.h"

class CcbPetSkillLayer;
class CcbPetShowBackLayer;


class CcbPetInfoScene: public cocos2d::CCLayer
{
public:
    // Constructor
    CcbPetInfoScene()
    {
        
    }
    ~CcbPetInfoScene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(CcbPetInfoScene);
public:
    // Virtual Functions
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    
};

class CcbPetInfoLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetInfoLayer()
	{
		m_pLayerBack = NULL;
		m_pLayerSkill = NULL;
		m_pSpriteBase = NULL;
		m_pSpritePetMc = NULL;
		m_pSprite6Wei = NULL;
		m_pControlButtonStrong = NULL;
		m_pControlButtonUp = NULL;
		m_pControlButtonChange = NULL;
        m_pControlButtonAlt = NULL;
        
        m_skillLayer = NULL;
        m_scrollView = NULL;
	}
	~CcbPetInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetInfoLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void draw();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CcbPetShowBackLayer* m_pLayerBack;
	cocos2d::CCLayer* m_pLayerSkill;
	cocos2d::CCSprite* m_pSpriteBase;
	cocos2d::CCSprite* m_pSpritePetMc;
	cocos2d::CCSprite* m_pSprite6Wei;
	cocos2d::extension::CCControlButton* m_pControlButtonStrong;
	cocos2d::extension::CCControlButton* m_pControlButtonUp;
	cocos2d::extension::CCControlButton* m_pControlButtonChange;
    cocos2d::extension::CCControlButton* m_pControlButtonAlt;
    CcbPetSkillLayer* m_skillLayer;
    cocos2d::extension::CCScrollView * m_scrollView;
    uint16 m_wPetIndexId;
    cocos2d::CCPoint arrPoint[6];
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

private:
    void showPetBgEff();
    void hidePetBgEff();
    void loadData(uint16 wPetIndexId, uint8 evoLv);
    void showSkillEff();
    
    void initFrame();
    uint32 curFrame;
    uint32 allNorFrame;
    uint32 allAltFrame;
    uint32 allFrame;
    bool isParitleStop;
    bool isRealSkill;
    std::map<uint16, uint16> m_mapKeyFrame;
    std::map<uint16, uint16> m_mapAltKeyFrame;
    std::vector<CCParticleSystemQuad*> arrCurParticle;
    void updateForEff(float time);
    void showHitEff();
    void showHitEff(uint32 effGroupId);
    std::string getEffPath(std::string idx);
    void onParticle(CCObject *pObject);
    void showArmEff();
    
    void showNor();
    void showAlk();
    void stopEff();
    
    
    
    
public:
    // Funcitons
    void loadTujianData(uint16 wPetIndexId);
    void loadPetData(CPet* pet);

	void onPressControlButtonStrong(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonUp(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonChange(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAlt(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbPetInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetInfoLayer);
};


#endif // __CCBPETINFOLAYER__H__