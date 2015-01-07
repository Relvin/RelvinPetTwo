/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-18 11:23:13
*/

#ifndef __CCBPLISTSHOWLAYER__H__
#define __CCBPLISTSHOWLAYER__H__

//CcbPlistShowLayer.h come from ccb/plist_show.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "FlccMovieClip.h"
#include "SequencePet.h"

class PlistShowScene : public cocos2d::CCLayer
{
public:
    PlistShowScene();
    ~PlistShowScene();
    static cocos2d::CCScene *scene();
    CREATE_FUNC(PlistShowScene);
    bool init();
};

class CcbPlistShowLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,  public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbPlistShowLayer()
	{
		m_pLayerBg = NULL;
		m_pSpriteMyHpBar = NULL;
		m_pLabelTTFMyMaxHP = NULL;
		m_pLabelTTFMyCurHP = NULL;
		m_pSpriteCoinBg = NULL;
		m_pSpriteSoulBg = NULL;
		m_pSpriteEggBg = NULL;
		m_pLabelTTFEnemyCurHP = NULL;
		m_pLabelTTFEnemyMaxHP = NULL;
		m_pLabelTTFCoin = NULL;
		m_pLabelTTFSoul = NULL;
		m_pLabelTTFEgg = NULL;
		m_pControlButtonAutoFight = NULL;

	}
	~CcbPlistShowLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPlistShowLayer, create);
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
	cocos2d::CCSprite* m_pSpriteMyHpBar;
	cocos2d::CCLabelTTF* m_pLabelTTFMyMaxHP;
	cocos2d::CCLabelTTF* m_pLabelTTFMyCurHP;
	cocos2d::CCSprite* m_pSpriteCoinBg;
	cocos2d::CCSprite* m_pSpriteSoulBg;
	cocos2d::CCSprite* m_pSpriteEggBg;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyCurHP;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyMaxHP;
	cocos2d::CCLabelTTF* m_pLabelTTFCoin;
	cocos2d::CCLabelTTF* m_pLabelTTFSoul;
	cocos2d::CCLabelTTF* m_pLabelTTFEgg;
	cocos2d::extension::CCControlButton* m_pControlButtonAutoFight;

    
    CCPoint arrEnemyPos[6];
    CCPoint arrPetPos[6];
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table) {
        return cocos2d::CCSizeMake(320, 40);
    };
	
public:
	// Funcitons


	void onPressControlButtonAutoFight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

private:
    std::vector<uint32> arrEffIndex;
    SequencePet* mc;
    cocos2d::CCSprite* imgTest;
    std::string getEffPath(std::string idx);
	void onParticle(CCObject *pObject);
    void onTab(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void removeLabel(cocos2d::CCNode *node);
    void onBoss(CCObject* obj);
};

class CcbPlistShowLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPlistShowLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPlistShowLayer);
};


#endif // __CCBPLISTSHOWLAYER__H__