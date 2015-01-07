/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 21:03:55
*/

#ifndef __CCBPETBATTLELAYER__H__
#define __CCBPETBATTLELAYER__H__

//CcbPetBattleLayer.h come from ccb/pet_battle_scene.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PetBattleData.h"
#include "FightPetSprite.h"
#include "DropItemSprite.h"
#include "PetBattleControlDelegate.h"
#include "WorldPacket.h"
#include "CcbDropBoxLayer.h"
#include "CcbFightWaveLayer.h"
#include "CcbLianXieBgLayer.h"
#include "CcbPadLayer.h"
#include "CCShake.h"

USING_NS_CC;
USING_NS_CC_EXT;
class CcbPetBattleCtrl;

class PetBattleScene : public cocos2d::CCLayer
{
public:
    PetBattleScene();
    ~PetBattleScene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(PetBattleScene);
    bool init();
    
    
};


class CcbPetBattleLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public PetBattleControlDelegate
,   public PadLayerDelegate
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
	CcbPetBattleLayer()
	{
		m_pSpriteFarMap = NULL;
		m_pSpriteNearMap = NULL;
		m_pLayerPetBattleCtrl_6 = NULL;
		m_pLayerPetBattleCtrl_3 = NULL;
		m_pLayerPetBattleCtrl_5 = NULL;
		m_pLayerPetBattleCtrl_2 = NULL;
		m_pLayerPetBattleCtrl_4 = NULL;
		m_pLayerPetBattleCtrl_1 = NULL;
		m_pLayerPetCtrlBg = NULL;
		m_pSpriteMyHpBar = NULL;
		m_pLabelTTFMyMaxHP = NULL;
		m_pLabelTTFMyCurHP = NULL;
		m_pSpriteMyHpBg = NULL;
		m_pControlButtonAutoFight = NULL;
		m_pControlButtonAutoFightOff = NULL;
		m_pSpriteEggBg = NULL;
		m_pLabelTTFEgg = NULL;
		m_pSpriteSoulBg = NULL;
		m_pLabelTTFSoul = NULL;
		m_pSpriteCoinBg = NULL;
		m_pLabelTTFCoin = NULL;
		m_pNodeNormalReward = NULL;
		m_pSpriteBossIcon = NULL;
		m_pSpriteBossNature = NULL;
		m_pSpriteBossHpBar = NULL;
		m_pLayerBossHpBg = NULL;
		m_pLabelTTFCurWave = NULL;
		m_pLabelTTFMaxWave = NULL;
		m_pLayerWaveBg = NULL;
		m_pLabelTTFCurRound = NULL;
		m_pLabelTTFRoundGang = NULL;
		m_pLabelTTFMaxRound = NULL;
		m_pSpriteCoinCat_RoundBg = NULL;
		m_pLabelTTFCoinCat_CurRound = NULL;
		m_pSpriteCoinCat_CoinBg = NULL;
		m_pLabelTTFCoinCat_Coin = NULL;
		m_pSpriteCoinCat_DamBg = NULL;
		m_pLabelTTFCoinCat_Damage = NULL;
		m_pNodeCoinCatReward = NULL;
        m_pLayerAllBg = NULL;
        m_pLayerWave = NULL;
        m_pLabelTTFEnemyAltName = NULL;
        m_pSpriteEnemyAltBg = NULL;
        m_pSpritePetCtrlBg = NULL;
        
        pauseActions = NULL;
        pauseTargets = NULL;
        m_bWaveFlag = false;

        m_bBossFlag = false;
        m_isShake = false;
        m_actShake = NULL;
        m_skillBgLayer = NULL;
        m_skillLayer = NULL;
        m_isPauseAll = false;
        bSecond = false;
        m_nRes = 0;
	}
	~CcbPetBattleLayer();
    static CcbPetBattleLayer * GetCurrScene() { return m_currentScene;};
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetBattleLayer, create);
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
    static CcbPetBattleLayer* m_currentScene;
    
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteFarMap;
	cocos2d::CCSprite* m_pSpriteNearMap;
	CcbPetBattleCtrl* m_pLayerPetBattleCtrl_3;
	CcbPetBattleCtrl* m_pLayerPetBattleCtrl_6;
	CcbPetBattleCtrl* m_pLayerPetBattleCtrl_2;
	CcbPetBattleCtrl* m_pLayerPetBattleCtrl_5;
	CcbPetBattleCtrl* m_pLayerPetBattleCtrl_4;
	CcbPetBattleCtrl* m_pLayerPetBattleCtrl_1;
	cocos2d::CCLayer* m_pLayerPetCtrlBg;
	cocos2d::CCSprite* m_pSpriteMyHpBar;
	cocos2d::CCLabelTTF* m_pLabelTTFMyMaxHP;
	cocos2d::CCLabelTTF* m_pLabelTTFMyCurHP;
	cocos2d::CCSprite* m_pSpriteMyHpBg;
	cocos2d::extension::CCControlButton* m_pControlButtonAutoFight;
	cocos2d::extension::CCControlButton* m_pControlButtonAutoFightOff;
	cocos2d::CCSprite* m_pSpriteEggBg;
	cocos2d::CCLabelTTF* m_pLabelTTFEgg;
	cocos2d::CCSprite* m_pSpriteSoulBg;
	cocos2d::CCLabelTTF* m_pLabelTTFSoul;
	cocos2d::CCSprite* m_pSpriteCoinBg;
	cocos2d::CCLabelTTF* m_pLabelTTFCoin;
	cocos2d::CCNode* m_pNodeNormalReward;
	cocos2d::CCSprite* m_pSpriteBossIcon;
	cocos2d::CCSprite* m_pSpriteBossNature;
	cocos2d::CCSprite* m_pSpriteBossHpBar;
	cocos2d::CCLayer* m_pLayerBossHpBg;
	cocos2d::CCLabelTTF* m_pLabelTTFCurWave;
	cocos2d::CCLabelTTF* m_pLabelTTFMaxWave;
	cocos2d::CCLayer* m_pLayerWaveBg;
	cocos2d::CCLabelTTF* m_pLabelTTFCurRound;
	cocos2d::CCLabelTTF* m_pLabelTTFRoundGang;
	cocos2d::CCLabelTTF* m_pLabelTTFMaxRound;
	cocos2d::CCSprite* m_pSpriteCoinCat_RoundBg;
	cocos2d::CCLabelTTF* m_pLabelTTFCoinCat_CurRound;
	cocos2d::CCSprite* m_pSpriteCoinCat_CoinBg;
	cocos2d::CCLabelTTF* m_pLabelTTFCoinCat_Coin;
	cocos2d::CCSprite* m_pSpriteCoinCat_DamBg;
	cocos2d::CCLabelTTF* m_pLabelTTFCoinCat_Damage;
	cocos2d::CCNode* m_pNodeCoinCatReward;
    cocos2d::CCLayer* m_pLayerAllBg;
    cocos2d::CCLabelTTF* m_pLabelTTFEnemyAltName;
    cocos2d::CCSprite* m_pSpriteEnemyAltBg;
    cocos2d::CCSprite* m_pSpritePetCtrlBg;
    
    CcbFightWaveLayer *m_pLayerWave;
    cocos2d::CCSprite *imgTrans;
    
    cocos2d::CCLayerColor* cPassEffLayer;

    cocos2d::CCNode* m_skillBgLayer;
    cocos2d::CCNode* m_skillLayer;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
	
public:
	// Funcitons
    void onPressControlButtonAutoFight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAutoFightOff(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void onPressControlButtonOpenBox(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void handlerPVEResult(WorldPacket& packet);
    
    virtual void doSomething(uint16 wBattleIndex, uint32 skillId);
    void addSkillWait(uint16 wBattleIndex, uint32 skillId);
    void startBattle(uint16 wBattleIndex, uint32 skillId);
    //显示掉血}
    virtual void loseHp(uint16 wBattleIndex, int hp);
    //加血}
    virtual void addHp(uint16 wBattleIndex, int hp);
    //获取所有pet的flcc}
    FightPetSprite* getFightPetSprite(uint16 wBattleIndex){return m_mapPet[wBattleIndex];};
    //一次攻击结束}
    virtual void endBattle(uint16 wBattleIndex, uint32 skillId);
    
    virtual void setPetCtrlSpecial(uint16 wBattleIndex);
    
    //显示掉物品}
    virtual void dropItem(uint16 wEnemyIndex, STC_ITEM_DROP item);
    
    //获取我方宠物中间位置}
    virtual cocos2d::CCPoint getMyMiddlePos();
    //获取敌方宠物中间位置}
    virtual cocos2d::CCPoint getEnemyMiddlePos();
    
    //掉落箱子}
    virtual void dropBox(uint16 wEnemyIndxe);
    
    virtual void openBox(CCLayer *box);
    
    //调整主动技能冷却}
    virtual void setPower(uint16 wBattleId, int wValue);

    //精灵死亡}
    virtual void showDeadEff(uint16 wBattleId);
    void showWaveAction();
    
    //屏幕抖动}
    virtual void doShake();
    
    //屏幕抖动回调}
    void callBackShake();
    
    virtual void pauseAll();
    virtual void remuseAll();
    
    // 大魔王变身
    void bossTransform();
    // 战斗完发验证
    void fightVerify();
    
    //显示大招点击时特效}
    virtual void showBattleCtrlTouchEff(uint16 wBattleId);
private:
    bool m_isPauseAll;
    //实际用来计算显示的地图高度
    float fRealHeight;
    
    //屏幕抖动标记}
    bool m_isShake;
    CCShake* m_actShake;
    
    int curRound;
    //是否自动战斗}
    bool m_isAutoFight;
    //是否正在战斗中}
    bool m_isFighting;
    //当前已攻击结束的人次}
    uint8 m_AttCnt;
    //等待攻击的次数（连携用）}
    uint8 m_WaitAttCnt;
    //是否回合结束}
    bool m_bIsRoundEnd;

    //当前获得的金币}
    uint32 m_curCoin;
    //当前获得的魂}
    uint32 m_curSoul;
    //当前获得的蛋}
    uint32 m_curEgg;
    
    //我队当前血量}
    uint32 m_dwMyTeamCurHP;
    
    float enemyhpBarWidth;
    float bosshpBarWidth;
    float myhpBarWidth;
    uint16 m_wBossIndex;
    bool isStop;
    
    //是否正在技能攻击}
    bool isSkillFight;
    
    int waitTime;
    
    bool isEatBox;
    
    //新手关卡用，结算等待时间
    float fRewardWait;
    
    cocos2d::CCPoint arrPetPos[PetCnt];
    cocos2d::CCPoint arrEnemyPos[PetCnt];
    std::map<uint16, FightPetSprite*> m_mapPet;
    std::vector<CcbPetBattleCtrl*> arrBattleCtrl;
    
    std::vector<DropItemSprite*> arrHeartSprite;
    
    std::vector<STC_WAIT_BATTLE_DATA> arrWaitBattleData;
    
    std::vector<STC_WAIT_BATTLE_DATA> arrEnemyBattleWait;
    std::vector<STC_WAIT_BATTLE_DATA> arrLianxieWait;
    std::vector<STC_WAIT_BATTLE_DATA> arrSkillWait;//技能攻击等待序列}
    std::set<uint16> arrCurFightPet;//当前正在攻击的宠物(目前的机制下，同时攻击的宠物肯定都是在一个阵营中)}
    
    //宝箱}
    std::map<CcbDropBoxLayer*, STC_ITEM_DROP> mapDropBox;

    //我方总输出量}
    uint32 allDamage;
    //我方当前回合输出}
    uint32 curRoundDamage;
    
    cocos2d::CCSet *pauseActions;
    cocos2d::CCSet *pauseTargets;
    
    bool m_bWaveFlag;       // 判断是wave开始后的第一个round的锁}
    bool bSecond;           // 第二次普通说话
    bool m_bBossFlag;       // 判断是boss wave开始后的第一个round锁}
    int m_nTalkIdx;         // 弹版Idx}
    int m_nRes;
public:
    // PadLayerDelegate
    virtual void showStep();
    
    
    //回合开始}
    void roundStart();
    
    //回合结束}
    void roundEnd();
    
    //波次开始}
    void waveStart();
    //波次结束}
    void waveEnd();
private:
    static bool cmpSpeed(const int &p, const int &q);
    void menuCloseCallback(cocos2d::CCObject *pObject);
    void menuJiaSu(cocos2d::CCObject *pObject);
    //初始化站位}
    void initPos();
    //加载数据}
    void loadData();
    
    //敌方攻击}
    void autoAttack();
    //开始播战斗包}
    void doBattle(uint8 key);
    //等待中的战斗包计时}
    void updateForWaitBattle(float time);
    //技能等待中的战斗包计时}
    void updateForSkillWaitBattle(float time);
    //用于判断死亡}
    void updateForChkDead(float time);
    //敌人死亡}
    void enemyDead(uint16 wEnemyIndex);
    //显示boss血条}
    void showBossHp();
    
    //切换敌人血条}
    void chgEnemyHpBar(uint16 wEnemyIndex);
    //选择敌人}
    void seleteEnemy(uint16 wEnemyIndex);
    
    void eatDropThing();
    void removeDeadEff(CCNode* node);
    void dropItemFly(DropItemSprite* imgItem, bool isHeart = false);
    void addEgg();
    void waitToEatDrop(float item);
    
    void doAfterEat();
    //更新精灵ctrl}
    void updatePetCtrl();
    
    void callBackItemFly(CCNode *node);

    //刷新队伍buff}
    void refreshBuff();
    //buff结算}
    void buffActive();

    void loadEnemyTeam();
    
    //跳转到结算面板}
    void gotoReward();
    //我方进场动画}
    void petInEff();
    //显示队长技能动画}
    void showLeaderSkillLayer();
    //显示战斗开始动画}
    float showFightStartEff();
    //显示主动技能动画}
    void showSkillLayer(uint16 wPetId, uint32 dwSkillId);
    //显示boss动画}
    void showBossEff();
    
    //开全部箱子}
    void openBox();
    
    //波次结束动画}
    void waveEndAction();
    
    //怪进入场景}
    void enemyRunIn();
    //开放整个场景的触摸}
    void openTouch(){isStop = false;};
    
    // 战斗失败回调}
    void onLoseBattle();
    // 验证失败回调}
    void failVerified();
    
    //等待所有怪消失后，切换波次}
    void updateForWaveChange(float time);
    
    //显示怪的主动技能}
    void showEnemyUltSkill(std::string strPassName);
    
    //显示自动触发被动技能}
    void showPassive();
    
    //判断连携加成}
    bool checkLianXie(uint16 wBattleIndex);
    
};

class CcbPetBattleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetBattleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetBattleLayer);
};


#endif // __CCBPETBATTLELAYER__H__