/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-20 15:04:46
*/

#ifndef __CCBARENAFIGHTLAYER__H__
#define __CCBARENAFIGHTLAYER__H__

//CcbArenaFightLayer.h come from ccb/pet_arena_battle_scene.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "WorldPacket.h"
#include "PetBattleData.h"
#include "PetBattleControlDelegate.h"
#include "DropItemSprite.h"
#include "CCShake.h"


class FightPetSprite;
class CcbArenaPetCtrl;

class AreanFightSecne : public cocos2d::CCLayer
{
public:
    AreanFightSecne();
    ~AreanFightSecne();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(AreanFightSecne);
    bool init();
};


class CcbArenaFightLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public PetBattleControlDelegate
{
public:
	// Constructor
	CcbArenaFightLayer()
	{
		m_pSpriteEnemyIcon = NULL;
		m_pSpriteMyIcon = NULL;
		m_pLabelTTFEnemyName = NULL;
		m_pLabelTTFEnemyOrder = NULL;
		m_pLabelTTFMyName = NULL;
		m_pLabelTTFMyOrder = NULL;
		m_pSpriteEnemyHpBar = NULL;
		m_pLabelTTFEnemyMaxHp = NULL;
		m_pLabelTTFEnemyCurHp = NULL;
		m_pSpriteMyHpBar = NULL;
		m_pLabelTTFMyCurHp = NULL;
		m_pLabelTTFMyMaxHp = NULL;
		m_pLayerEnemyMember_4 = NULL;
		m_pLayerEnemyMember_1 = NULL;
		m_pLayerEnemyMember_2 = NULL;
		m_pLayerEnemyMember_3 = NULL;
		m_pLayerEnemyMember_6 = NULL;
		m_pLayerEnemyMember_5 = NULL;
		m_pLayerMyMember_1 = NULL;
		m_pLayerMyMember_4 = NULL;
		m_pLayerMyMember_2 = NULL;
		m_pLayerMyMember_5 = NULL;
		m_pLayerMyMember_3 = NULL;
		m_pLayerMyMember_6 = NULL;
        m_pSpriteCloudFar_1 = NULL;
		m_pSpriteCloudFar_2 = NULL;
		m_pLayerFireBg = NULL;
		m_pSpriteCloudNear_1 = NULL;
		m_pSpriteCloudNear_2 = NULL;
        m_pLabelTTFTime = NULL;
        m_pSpriteNearMap = NULL;
        m_pControlButtonGo = NULL;
        
//        cPassEffLayer = NULL;
        m_isShake = false;
        m_actShake = NULL;
        m_skillBgLayer = NULL;
        m_skillLayer = NULL;
        m_isPauseAll = false;
        pauseActions = NULL;
        pauseTargets = NULL;
        
	}
	~CcbArenaFightLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaFightLayer, create);
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
	cocos2d::CCSprite* m_pSpriteEnemyIcon;
	cocos2d::CCSprite* m_pSpriteMyIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyName;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyOrder;
	cocos2d::CCLabelTTF* m_pLabelTTFMyName;
	cocos2d::CCLabelTTF* m_pLabelTTFMyOrder;
	cocos2d::CCSprite* m_pSpriteEnemyHpBar;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyMaxHp;
	cocos2d::CCLabelTTF* m_pLabelTTFEnemyCurHp;
	cocos2d::CCSprite* m_pSpriteMyHpBar;
	cocos2d::CCLabelTTF* m_pLabelTTFMyCurHp;
	cocos2d::CCLabelTTF* m_pLabelTTFMyMaxHp;
	CcbArenaPetCtrl* m_pLayerEnemyMember_4;
	CcbArenaPetCtrl* m_pLayerEnemyMember_1;
	CcbArenaPetCtrl* m_pLayerEnemyMember_2;
	CcbArenaPetCtrl* m_pLayerEnemyMember_3;
	CcbArenaPetCtrl* m_pLayerEnemyMember_6;
	CcbArenaPetCtrl* m_pLayerEnemyMember_5;
	CcbArenaPetCtrl* m_pLayerMyMember_1;
	CcbArenaPetCtrl* m_pLayerMyMember_4;
	CcbArenaPetCtrl* m_pLayerMyMember_2;
	CcbArenaPetCtrl* m_pLayerMyMember_5;
	CcbArenaPetCtrl* m_pLayerMyMember_3;
	CcbArenaPetCtrl* m_pLayerMyMember_6;
    cocos2d::CCSprite* m_pSpriteCloudFar_1;
	cocos2d::CCSprite* m_pSpriteCloudFar_2;
	cocos2d::CCLayer* m_pLayerFireBg;
	cocos2d::CCSprite* m_pSpriteCloudNear_1;
	cocos2d::CCSprite* m_pSpriteCloudNear_2;
    cocos2d::CCLabelTTF* m_pLabelTTFTime;
    cocos2d::CCSprite* m_pSpriteNearMap;
    cocos2d::extension::CCControlButton* m_pControlButtonGo;
    
    cocos2d::CCNode* m_skillBgLayer;
//    cocos2d::CCLayerColor* cPassEffLayer;
    cocos2d::CCNode* m_skillLayer;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

private:

    uint8 m_wFightType;
    bool m_isPauseAll;
    //屏幕抖动标记}
    bool m_isShake;
    CCShake* m_actShake;
    
    cocos2d::CCSet *pauseActions;
    cocos2d::CCSet *pauseTargets;
    
    //站位}
    cocos2d::CCPoint arrPetPos[PetCnt];
    cocos2d::CCPoint arrEnemyPos[PetCnt];
    //人物flcc}
    std::map<uint16, FightPetSprite*> mapPetSprite;
    //人物头像Ctrl}
    std::map<uint16, CcbArenaPetCtrl*> mapPetCtrl;
    
    //是否主攻}
    bool m_bIsAttcte;
    
    int m_dwMyTeamHP;
    int m_dwCurMyTeamHP;
    int m_dwEnemyTeamHP;
    int m_dwCurEnemyTeamHP;
    
    bool isFightEnd;
    
    float barWidth;
    uint16 m_CurRound;
    
    int curHeartCount;
    //当前攻击完成的数量}
    int m_AttCnt;
    //当前开始攻击的数量}
    int m_CurAttCnt;
    int waitTime;
    uint8 m_WaitAttCnt;
    
    int countDownTime;
    //掉落物品}
    std::map<uint32, std::vector<DropItemSprite*> > mapDropSprite;
    
    struct STC_EAT_HEART
    {
        uint8 cnt;
        uint32 dwValue;
    };
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
        
        //回合开始时buff}
//        std::map<uint16, std::vector<STC_BUFF> > mapEnemyBeforeBuff;
//        //回合开始时被动技能}
//        std::map<uint16, std::vector<STC_TRIGGERED_PSKILL> >mapEnemyBeforePass;
        
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
	
//    struct STC_WAIT_FIGHT_DATA
//    {
//        uint32 curFrame;
//        uint32 maxFrame;
//        STC_BATTLE_DATA bData;
//    };
//    std::vector<STC_WAIT_BATTLE> arrWaitBattleData;
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
    void onPressControlButtonGo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void handlerPVPInfo(WorldPacket &packet);

    //    void loseHP(uint16 wIndex, uint32 dwLoseHp);
    virtual void loseHp(uint16 wBattleIndex, int loseHealth);
    //回血}
    virtual void addHp(uint16 wIndex, int wValue);
    //掉物品}
    virtual void dropItem(uint16 wBattleIndex, STC_ITEM_DROP item);
    //获取精灵的petSprite}
    virtual FightPetSprite* getFightPetSprite(uint16 wBattleIndex){return mapPetSprite[wBattleIndex];};
    
    virtual void endBattle(uint16 wBattleIndex, uint32 skillId);
    
    //获取我方宠物中间位置}
    virtual cocos2d::CCPoint getMyMiddlePos();
    //获取敌方宠物中间位置}
    virtual cocos2d::CCPoint getEnemyMiddlePos();
    
    //精灵死亡}
    virtual void showDeadEff(uint16 wBattleId);
//    virtual void showPassive(std::vector<STC_TRIGGERED_PSKILL> arrTPSkill);
    
    //显示死亡时触发的被动技能}
//    virtual void showDeadPassive(uint16 wBattleIndex);
    //调整主动技能冷却}
    virtual void setPower(uint16 wBattleId, int wValue);
    
    //屏幕抖动}
    virtual void doShake();
    
    //屏幕抖动回调}
    void callBackShake();
public:
    //显示自动触发的被动技能}
//    void showPassive();
//    void showPassive(std::string strPassName);
//    void showWaveAction();
private:
    void menuCloseCallback(cocos2d::CCObject *pObject);
    
    void loadData();
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
    
    //吃掉落}
    void eatDropThing();
    
    //物品飞动}
    void callBackItemFly(cocos2d::CCNode* node);
    //等待吃物品结束}
    void waitToEatDrop(float time);
    
    //控制云飘动}
    void updateCloudyFly(float time);
    
    void showSkillLayer(uint16 wPetId, uint32 dwSkillId);
    
    //显示被动技能动画}
//    void showPassSkillLayer(uint16 wBattleId);
//    void endShowPassSkillLayer(CCNode *node);
    //显示一个被动技能}
//    void addPassText(std::string strPassName);
    //被动技能等待计时}
//    void updataWaitForShowPass(float time);
//    //被动技能消失}
//    void hidePassText(CCNode *node);
    
    std::vector<STC_TRIGGERED_PSKILL> getTrSkillInSpecial(uint16 wBattleId, WorldPacket &packet);
    
    //用于判断死亡}
    void updateForChkDead(float time);
    //等待所有死亡怪消失}
    void updateForChange(float time);
    //倒计时}
    void updateTime(float time);
    
    void petInEff();
    
    void afterInEff();
    
    //验证连携}
    bool checkLianXie(STC_WAIT_BATTLE wdata);
    
    void gotoReward();
    
    void removeDeadEff(CCNode* node);
};

class CcbArenaFightLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaFightLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaFightLayer);
};


#endif // __CCBARENAFIGHTLAYER__H__