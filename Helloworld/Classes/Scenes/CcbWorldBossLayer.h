/**
* CcbWorldBossLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-13 15:46:57
*/

#ifndef __CCBWORLDBOSSLAYER__H__
#define __CCBWORLDBOSSLAYER__H__

//CcbWorldBossLayer.h come from ccb/world_boss.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "WorldPacket.h"
#include "WorldBossDataMgr.h"
#include "SystemMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;

class WorldBossScene : public cocos2d::CCLayer
{
public:
    WorldBossScene();
    ~WorldBossScene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(WorldBossScene);
    bool init();
    
    
};


class CcbWorldBossLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbWorldBossLayer()
	{
		m_pControlButtonRank = NULL;
		m_pControlButtonReward = NULL;
		m_pControlButtonBack = NULL;
		m_pLabelTTFBossName = NULL;
		m_pLabelTTFBossHpCur = NULL;
		m_pLabelTTFBossHpMax = NULL;
		m_pLabelTTFLeftTime = NULL;
		m_pSpriteBossPaint = NULL;
		m_pControlButtonCostMoney = NULL;
		m_pControlButtonCostDiamond = NULL;
		m_pLabelTTFMoneyNum = NULL;
		m_pLabelTTFDiamondNum = NULL;
		m_pLabelTTFTimes = NULL;
		m_pLabelTTFDamageNum = NULL;
		m_pLabelTTFDamagePercent = NULL;
		m_pLabelTTFDamageBuffPercent = NULL;
		m_pLabelTTFRankNum = NULL;
		m_pLabelTTFCD = NULL;
		m_pControlButtonAutoAttack = NULL;
		m_pControlButtonAtack = NULL;
		m_pControlButtonFuhuo = NULL;
        m_pSpriteHpBar = NULL;
        m_pLayerBoss = NULL;
        m_pLabelTTFBlessCDTime = NULL;
        m_pLabelTTFBossLV = NULL;
        
        m_rankLayer = NULL;
        m_rewardLayer = NULL;
        
        m_curScene = NULL;

	}
	~CcbWorldBossLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbWorldBossLayer, create);
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
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonRank;
	cocos2d::extension::CCControlButton* m_pControlButtonReward;
	cocos2d::extension::CCControlButton* m_pControlButtonBack;
	cocos2d::CCLabelTTF* m_pLabelTTFBossName;
	cocos2d::CCLabelTTF* m_pLabelTTFBossHpCur;
	cocos2d::CCLabelTTF* m_pLabelTTFBossHpMax;
	cocos2d::CCLabelTTF* m_pLabelTTFLeftTime;
	cocos2d::CCSprite* m_pSpriteBossPaint;
	cocos2d::extension::CCControlButton* m_pControlButtonCostMoney;
	cocos2d::extension::CCControlButton* m_pControlButtonCostDiamond;
	cocos2d::CCLabelTTF* m_pLabelTTFMoneyNum;
	cocos2d::CCLabelTTF* m_pLabelTTFDiamondNum;
	cocos2d::CCLabelTTF* m_pLabelTTFTimes;
	cocos2d::CCLabelTTF* m_pLabelTTFDamageNum;
	cocos2d::CCLabelTTF* m_pLabelTTFDamagePercent;
	cocos2d::CCLabelTTF* m_pLabelTTFDamageBuffPercent;
	cocos2d::CCLabelTTF* m_pLabelTTFRankNum;
	cocos2d::CCLabelTTF* m_pLabelTTFCD;
	cocos2d::extension::CCControlButton* m_pControlButtonAutoAttack;
	cocos2d::extension::CCControlButton* m_pControlButtonAtack;
	cocos2d::extension::CCControlButton* m_pControlButtonFuhuo;
    CCSprite* m_pSpriteHpBar;
    CCLayer* m_pLayerBoss;
    CCLabelTTF* m_pLabelTTFBlessCDTime;
    CCLabelTTF* m_pLabelTTFBossLV;
    
    CCNode* m_rankLayer;
    CCNode* m_rewardLayer;
    
    float fHpBarWidth;
    
    STC_WORLD_BOSS_INFO m_curBossInfo;

    uint32 m_dwBossCurHp;

    uint32 m_dwLeftTime;          //boss剩余时间

    uint32 m_dwBuffAdd;           //祝福后加成

    uint32 m_dwBlessCDTime;       //金币CD时间

    uint32 m_dwAllDamage;         //已造成伤害
    uint32 m_dwCdTime;            //攻击CD时间

    uint32 m_dwCurRank;           //当前我的排名

    int m_randOtherDamTime;       //随机时间请求其他人的伤害
    
    static CcbWorldBossLayer* m_curScene;
    
    
    uint8 m_fightType;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


public:
    static CcbWorldBossLayer* getCurScene(){return m_curScene;};
    
    void handlerBlessResult(WorldPacket& packet);
    void handlerFuhuoResult(WorldPacket& packet);
    void handlerOtherUserDam(WorldPacket& packet);
    void handlerAutoAttReward(WorldPacket& packet);
    void handlerBossDead(WorldPacket& packet);
    
    void reloadRank();
    
    void loadData();
private:
    void updateForAttCd(float time);
    void updateForBossLeftTime(float time);
    void updateForBlessCd(float time);
	
    void updateForGetOtherDam(float time);
    
    void showBlessCD();
    void hideBlessCD();
    
    void showAttCD();
    void hideAttCD();

public:
	// Funcitons


	void onPressControlButtonRank(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonReward(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonCostMoney(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonCostDiamond(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonAutoAttack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonAtack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonFuhuo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbWorldBossLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbWorldBossLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbWorldBossLayer);
};


#endif // __CCBWORLDBOSSLAYER__H__