/**
* CcbWorldBossFightLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-14 20:39:42
*/

#ifndef __CCBWORLDBOSSFIGHTLAYER__H__
#define __CCBWORLDBOSSFIGHTLAYER__H__

//CcbWorldBossFightLayer.h come from ccb/pet_battle_boss_scene.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PetBattleData.h"
#include "FightPetSprite.h"
#include "PetBattleControlDelegate.h"
#include "WorldPacket.h"
#include "CcbLianXieBgLayer.h"
#include "CCShake.h"
#include "DropItemSprite.h"

class CcbPetBattleCtrl;

class WorldBossFightScene : public cocos2d::CCLayer
{
public:
     WorldBossFightScene();
    ~ WorldBossFightScene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC( WorldBossFightScene);
    bool init();
    
    
};

class CcbWorldBossFightLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public PetBattleControlDelegate
{
public:
    
    enum
    {
        E_ZORDER_PET_MC = 480,              //宠物模型}
        E_ZORDER_SELECT_ICON = 690,         //选中光圈}
        E_ZORDER_BOSS_HP_BG = 695,          //boss血条}
        E_ZORDER_ENEMY_HP_BG = 697,         //怪的血条}
        E_ZORDER_LEADER_SKILL_EFF = 700,    //队长技能特效}
        E_ZORDER_PASS_TEXT = 701,          //被动技能文字}
        E_ZORDER_PASSIVE_EFF_LAYER = 702,   //被动技能触发时遮罩}
        E_ZORDER_PASSIVE_SKILL_PET = 703,   //被动技能宠物}
        E_ZORDER_PASSIVE_SKILL_EFF = 704,   //被动技能特效}
        E_ZORDER_ALT_SKILL_EFF = 705,       //主动技能特效}
        E_ZORDER_MY_HP_BG = 710,            //我方血条}
        E_ZORDER_WAVE_EFF = 885,            //波次动画}
        E_ZORDER_PET_CTRL = 886,            //宠物控制栏}
        E_ZORDER_PET_CTRL_BG = 887,         //宠物控制栏遮罩}
        E_ZORDER_OPEN_BOX_BG = 888,         //一键开箱子遮罩}
        E_ZORDER_TRANS = 999,               //波次过度动画（黑幕划过）}
        E_ZORDER_PAD_LAYER = 1000,          //弹板}
        
    };
    
	// Constructor
	CcbWorldBossFightLayer()
	{
		m_pSpriteFarMap = NULL;
		m_pSpriteNearMap = NULL;
		m_pSpriteBossIcon = NULL;
		m_pSpriteBossHpBar = NULL;
		m_pSpriteBossNature = NULL;
		m_pLayerBossHpBg = NULL;
		m_pLabelTTFEnemyAltName = NULL;
		m_pSpriteEnemyAltBg = NULL;
		m_pLayerAllBg = NULL;
		m_pSpritePetCtrlBg = NULL;
		m_pSpriteMyHpBg = NULL;
		m_pSpriteMyHpBar = NULL;
		m_pLabelTTFMyMaxHP = NULL;
		m_pLabelTTFMyCurHP = NULL;
		m_pLayerPetBattleCtrl_6 = NULL;
		m_pLayerPetBattleCtrl_4 = NULL;
		m_pLayerPetBattleCtrl_2 = NULL;
		m_pLayerPetBattleCtrl_5 = NULL;
		m_pLayerPetBattleCtrl_3 = NULL;
		m_pLayerPetBattleCtrl_1 = NULL;
		m_pLayerPetCtrlBg = NULL;
        
        m_skillBgLayer = NULL;
        m_skillLayer = NULL;
        m_actShake = NULL;
        
        pauseActions = NULL;
        pauseTargets = NULL;
        
        m_isPauseAll = false;
        m_isShake = false;

	}
	~CcbWorldBossFightLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbWorldBossFightLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteFarMap;
	cocos2d::CCSprite* m_pSpriteNearMap;
	cocos2d::CCSprite* m_pSpriteBossIcon;
	cocos2d::CCSprite* m_pSpriteBossHpBar;
	cocos2d::CCSprite* m_pSpriteBossNature;
	cocos2d::CCLayer* m_pLayerBossHpBg;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyAltName;
	cocos2d::CCSprite* m_pSpriteEnemyAltBg;
	cocos2d::CCLayer* m_pLayerAllBg;
	cocos2d::CCSprite* m_pSpritePetCtrlBg;
	cocos2d::CCSprite* m_pSpriteMyHpBg;
	cocos2d::CCSprite* m_pSpriteMyHpBar;
	cocos2d::CCLabelTTF* m_pLabelTTFMyMaxHP;
	cocos2d::CCLabelTTF* m_pLabelTTFMyCurHP;
    CcbPetBattleCtrl* m_pLayerPetBattleCtrl_3;
    CcbPetBattleCtrl* m_pLayerPetBattleCtrl_6;
    CcbPetBattleCtrl* m_pLayerPetBattleCtrl_2;
    CcbPetBattleCtrl* m_pLayerPetBattleCtrl_5;
    CcbPetBattleCtrl* m_pLayerPetBattleCtrl_4;
    CcbPetBattleCtrl* m_pLayerPetBattleCtrl_1;
	cocos2d::CCLayer* m_pLayerPetCtrlBg;

    cocos2d::CCNode* m_skillLayer;
    cocos2d::CCNode* m_skillBgLayer;
private:
    // 战斗完发验证
    void failVerified();
    void menuCloseCallback(cocos2d::CCObject *pObject);
    void menuJiaSu(cocos2d::CCObject *pObject);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


    uint8 m_wFightType;
    bool m_isPauseAll;
    //屏幕抖动标记}
    bool m_isShake;
    CCShake* m_actShake;
    
    cocos2d::CCSet *pauseActions;
    cocos2d::CCSet *pauseTargets;
    
    //掉落物品}
    std::map<uint32, std::vector<DropItemSprite*> > mapDropSprite;
    struct STC_EAT_HEART
    {
        uint8 cnt;
        uint32 dwValue;
    };
    
    //站位}
    cocos2d::CCPoint arrPetPos[PetCnt];
    cocos2d::CCPoint arrEnemyPos[PetCnt];
    //人物flcc}
    std::map<uint16, FightPetSprite*> mapPetSprite;
    //人物头像Ctrl}
    std::map<uint16, CcbPetBattleCtrl*> mapPetCtrl;
    
    int m_dwMyTeamHP;
    int m_dwCurMyTeamHP;

    float fRealHeight;
//    float barWidth;
    float bosshpBarWidth;
    
    float myhpBarWidth;
    
    uint16 m_CurRound;
    
    uint16 m_wBossIndex;
    
    //当前攻击完成的数量}
    int m_AttCnt;
    //当前开始攻击的数量}
    int m_CurAttCnt;
    int waitTime;
    uint8 m_WaitAttCnt;

    //攻击包}
    struct STC_WAIT_BATTLE
    {
        //在技能等待序列里，该值代表 -1：攻击结束，0：正在攻击，大于0：即将攻击}
        int wcurFrame;
        uint16 wStartFrame;
        STC_BATTLE_DATA bData;
        uint32 dwPetHP;
        uint32 dwTeamHP;
        std::vector<uint32> arrLianxieId;
        uint16 wLianxieAdd;
    };
    
    //回合包}
    struct STC_BATTLE_ROUND
    {
        //攻击者 1：我方；2：敌方}
        uint8 byAttacker;
        //回合开始时buff}
        std::map<uint16, std::vector<STC_BUFF> > mapBeforeBuff;
        //回合开始时被动技能}
        std::map<uint16, std::vector<STC_TRIGGERED_PSKILL> >mapBeforePass;

        //本回合攻击顺序、攻击包}
        std::vector<STC_WAIT_BATTLE> arrWaitBattle;
        //buff生效}
        std::map<uint16, std::vector<STC_BUFF_VALUE> > mapAfterBuffValue;
        //回合结束时buff}
        std::map<uint16, std::vector<STC_BUFF> > mapAfterBuff;
        //回合后吃到的心珠}
        std::map<uint16, STC_EAT_HEART> mapEatHeart;
        //回合后各宠物的必杀值}
        std::map<uint16, uint16> mapAfterPower;
        //回合后各宠物的必杀值}
        std::map<uint16, uint32> mapAfterHp;
        
        uint32 dwAllHeartCnt;
        uint32 dwHeartValue;
        uint32 dwOneHeartValue;
        
        uint32 dwMyAllHp;
        uint32 dwEnemyAllHp;
    };
    
    //战斗包}
    struct STC_ARENA_BATTLE_DATA
    {
        uint8 isWin;
        uint8 byRoundCnt;
        
        //回合包}
        std::vector<STC_BATTLE_ROUND> arrRound;
    };
    STC_BATTLE_ROUND m_curBattleRound;
    STC_ARENA_BATTLE_DATA m_ArenaData;
    int getEnemyIndex(STC_BATTLE_DATA bData);
    
    std::map<uint16, STC_FRAME_DAMAGE> makeCombo(int& allDamage, uint16 fightId, uint32 skillId );
    
    std::vector<STC_WAIT_BATTLE> arrLianxieWait;
    std::vector<STC_WAIT_BATTLE> arrSkillWait;//技能攻击等待序列}
    std::set<uint16> arrCurFightPet;//当前正在攻击的宠物(目前的机制下，同时攻击的宠物肯定都是在一个阵营中)}
    //死亡时触发的被动技能}
    std::map<uint16, std::vector<STC_TRIGGERED_PSKILL> > mapPetDeadTRSkill;
    
    std::vector<CCSprite*> arrNowShowPassTextSprite;
    std::vector<std::string> arrWaitPassiveText;
    std::vector<std::string> arrWaveStartMyPassiveText;
    std::vector<std::string> arrWaveStartEnemyPassiveText;
    
public:
    // Funcitons
    void handlerPVPInfo(WorldPacket &packet);
    std::vector<STC_TRIGGERED_PSKILL> getTrSkillInSpecial(uint16 wBattleId, WorldPacket &packet);
    
    
    //掉物品}
//    virtual void dropItem(uint16 wBattleIndex, STC_ITEM_DROP item);
    //吃掉落}
    void eatDropThing();
    
    //物品飞动}
    void callBackItemFly(cocos2d::CCNode* node);
    //等待吃物品结束}
    void waitToEatDrop(float time);
    
    //    void loseHP(uint16 wIndex, uint32 dwLoseHp);
    virtual void loseHp(uint16 wBattleIndex, int loseHealth);
    //回血}
    virtual void addHp(uint16 wIndex, int wValue);

    //获取精灵的petSprite}
    virtual FightPetSprite* getFightPetSprite(uint16 wBattleIndex){return mapPetSprite[wBattleIndex];};
    
    virtual void endBattle(uint16 wBattleIndex, uint32 skillId);
    
    //获取我方宠物中间位置}
    virtual cocos2d::CCPoint getMyMiddlePos();
    //获取敌方宠物中间位置}
    virtual cocos2d::CCPoint getEnemyMiddlePos();
    
    //精灵死亡}
    virtual void showDeadEff(uint16 wBattleId);

    //调整主动技能冷却}
    virtual void setPower(uint16 wBattleId, int wValue);
    
    virtual void setPetCtrlSpecial(uint16 wBattleIndex);
    //屏幕抖动}
    virtual void doShake();
    
    //屏幕抖动回调}
    void callBackShake();

private:

    void loadData();
    void showBossHp();
    void initPos();
    
    void fightStart();
    void fightEnd();
    void roundStart();
    void roundEnd();
    
    void pauseAll();
    void remuseAll();
    
    void updateWaitForFight(float time);
    //技能等待中的战斗包计时}
    void updateForSkillWaitBattle(float time);
    void startBattle(STC_WAIT_BATTLE data);
    
    void doBattle(STC_BATTLE_DATA data);

    //用于判断死亡}
    void updateForChkDead(float time);
    //等待所有死亡怪消失}
    void updateForChange(float time);
    
    //我方进场动画}
    void petInEff();
    //显示队长技能动画}
    void showLeaderSkillLayer();
    //显示战斗开始动画}
    float showFightStartEff();
    //显示主动技能动画}
    void showSkillLayer(uint16 wPetId, uint32 dwSkillId);
    //显示怪的主动技能}
    void showEnemyUltSkill(std::string strPassName);
    //怪进入场景}
    void enemyRunIn();
    
    void afterInEff();
    
    //验证连携}
    bool checkLianXie(STC_WAIT_BATTLE wdata);
    
    void gotoReward();
    
    void removeDeadEff(CCNode* node);

};

class CcbWorldBossFightLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbWorldBossFightLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbWorldBossFightLayer);
};


#endif // __CCBWORLDBOSSFIGHTLAYER__H__