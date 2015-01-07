/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-21 22:20:29
*/

#ifndef __CCBFIGHTREWARDLAYER__H__
#define __CCBFIGHTREWARDLAYER__H__

//CcbFightRewardLayer.h come from ccb/fight_reward.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "PetBattleData.h"

class FightRewardScene : public cocos2d::CCLayer
{
public:
    FightRewardScene();
    ~FightRewardScene();
    static cocos2d::CCScene *scene();
    CREATE_FUNC(FightRewardScene);
    bool init();
};

class CcbFightRewardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFightRewardLayer()
	{
		m_pSpriteStar_1 = NULL;
		m_pSpriteStar_2 = NULL;
		m_pSpriteStar_3 = NULL;
		m_pLabelTTFGetMoney = NULL;
		m_pLabelTTFGetExp = NULL;
		m_pLabelTTFLv = NULL;
		m_pSpriteExpBar = NULL;
		m_pSpriteItemIcon = NULL;
		m_pLayerRward = NULL;
		m_pControlButtonContinue = NULL;
		m_pControlButtonShare = NULL;
        m_pLabelTTFStageName = NULL;
        mAnimationManager = NULL;
        m_pSpriteZhuanlun = NULL;
        m_pLabelTTFDropDes = NULL;
        m_pLabelTTFDropType = NULL;
        
	}
	~CcbFightRewardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFightRewardLayer, create);
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
	cocos2d::CCSprite* m_pSpriteStar_1;
	cocos2d::CCSprite* m_pSpriteStar_2;
	cocos2d::CCSprite* m_pSpriteStar_3;
	cocos2d::CCLabelTTF* m_pLabelTTFGetMoney;
	cocos2d::CCLabelTTF* m_pLabelTTFGetExp;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCSprite* m_pSpriteExpBar;
	cocos2d::CCSprite* m_pSpriteItemIcon;
	cocos2d::CCLayer* m_pLayerRward;
	cocos2d::extension::CCControlButton* m_pControlButtonContinue;
	cocos2d::extension::CCControlButton* m_pControlButtonShare;
    cocos2d::CCLabelTTF* m_pLabelTTFStageName;
    cocos2d::CCSprite*m_pSpriteZhuanlun;
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    cocos2d::CCLabelTTF* m_pLabelTTFDropDes;
    cocos2d::CCLabelTTF* m_pLabelTTFDropType;
    
    uint8 m_byStar;
    
    float expBarW;
    uint16 m_wUserLv;//结算前等级}
    uint32 m_dwUserExp;//结算前经验}
    
    bool isLvUpRunning;
    bool isExpUpStop;
    int curFrame;
    int perExp;
    int moleExp;
    int perMoney;
    int moleMoney;
    uint32 m_dwCurLvExp;//当前等级总经验}
    uint32 m_dwGetExp;//总共获得的经验}
    uint32 m_dwCurGetExp;//已读取的经验}
    uint32 m_dwCurLvGetExp;//当前等级读取到的经验}
    uint32 m_dwGetCoin;
    uint32 m_dwCurGetCoin;
    bool isLvMax;
    
    int m_curItemCnt;
    bool m_bIsShowEnd;
    bool m_bIsFast;
    
    bool m_backFlag;
//    uint8 m_fightType;
    
    std::vector<STC_FIGHT_REWARD_ITEM> arrFirst;
    std::vector<STC_FIGHT_REWARD_ITEM> arrItem;
    std::vector<STC_FIGHT_REWARD_ITEM> arrPet;
    
    std::vector<cocos2d::CCSprite*> m_arrItemNothing;
    std::vector<cocos2d::CCNode*>m_arrItem;
    std::vector<cocos2d::CCSprite*>m_arrLight;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);
    
    static void showReward();
    
public:
    void onPressControlButtonContinue(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonShare(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	// Funcitons

    void onLvUpEnd();
    
//    void setFightType(uint8 fightType){m_fightType = fightType;};
private:
    void loadData();
    void onNext();
    void stopRunning();
	void onStartExp1(CCNode* pNode);
	void onStartExp2(CCNode* pNode);
	void onStartExp3(CCNode* pNode);
    void onShowWorldLoot(CCNode* pNode);
    
	void onEndExpUp();
    void updateForExp(float time);
    void onLvUp();
    
    void onShowItem();
    void onFastShow();
};

class CcbFightRewardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFightRewardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFightRewardLayer);
};


#endif // __CCBFIGHTREWARDLAYER__H__