//
//  PetBattleData.h
//  HelloWorld
//
//  Created by long on 13-8-1.
//
//

#ifndef __HelloWorld__PetBattleData__
#define __HelloWorld__PetBattleData__

#include <iostream>
#include "Defines.h"
#include <vector>
#include <map>
#include "ccMacros.h"

#define PetCnt  6

#define PetSkillValue 100
#define DEADTIME 45
#define startFrames     6*2
#define delayFrame 30

//#define sparkAdd    0.2
//#define critAdd     0.5
#define ATK(_atk, _def, _damFloat, ret) \
do{\
ret = (_atk - _def );\
if (ret <= 0) \
{ret = _atk * 0.1;}\
else { ret += CCRANDOM_MINUS1_1() * ret * _damFloat;}\
}while(0)

#define REHP(recover, revFloat) recover * revFloat / 10000


#define CC_MY_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

typedef enum _E_ATTACK_STATE
{
    //普通攻击}
    E_ATTACK_STATE_NORMAL = 0,
    //暴击}
    E_ATTACK_STATE_CRIT,
    //spark
    E_ATTACK_STATE_SPARK,
    //回血}
    E_ATTACK_STATE_HP,
}E_ATTACK_STATE;

//属性压制}
typedef enum _E_ATTRIBUTE_REGULATE
{
    //无克制情况}
    E_ATTRIBUTE_REGULATE_NON = 0,
    //克制}
    E_ATTRIBUTE_REGULATE_UP,
    //被克制}
    E_ATTRIBUTE_REGULATE_DOWN,
}E_ATTRIBUTE_REGULATE;

typedef enum _E_PET_STATE
{
    //普通情况}
    E_PET_STATE_NORMAL = 0,
    //技能满时}
    E_PET_STATE_SKILL_FULL = 1,
    //死亡}
    E_PET_STATE_DEAD = 2,
    //没有宠物}
    E_PET_STATE_NOTHING = 3,
}E_PET_STATE;

typedef enum _E_PET_SKILL
{
    //普通攻击}
    E_PET_SKILL_NON = 0,
    //技能1}
    E_PET_SKILL_1,
    //技能2}
    E_PET_SKILL_2,
}E_PET_SKILL;

//display到control的回执类型}
typedef enum _E_DTOC
{
    //攻击结束}
    E_DTOC_ATTACK_OVER,
    //心珠回血}
    E_DTOC_RECOVER,
    
}E_DTOC;
typedef enum _E_DROP_ITEM_TYPE
{
    //金币}
    E_DROP_ITEM_TYPE_COIN,
    //心珠}
    E_DROP_ITEM_TYPE_HP,
    //魂}
    E_DROP_ITEM_TYPE_SPRITE,
    //材料}
    E_DROP_ITEM_TYPE_STUFF,
    //能量珠}
    E_DROP_ITEM_TYPE_POWER,
    //蛋}
    E_DROP_ITEM_TYPE_EGG,
    
    
}E_DROP_ITEM_TYPE;

typedef enum _E_WORD_TYPE
{
    //普通}
    E_WORD_TYPE_NORMAL = 0,
    //克制}
    E_WORD_TYPE_REGULATE_UP,
    //被克制}
    E_WORD_TYPE_REGULATE_DOWN,
    //暴击文字}
    E_WORD_TYPE_CRIT_TEXT,
    //加血}
    E_WORD_TYPE_HP,
    //合击文字}
    E_WORD_TYPE_SPARK_TEXT,
    //被动技能}
    E_WORD_TYPE_PASSIVE,
    //闪避}
    E_WORD_TYPE_MISS_TEXT,
    //连携}
    E_WORD_TYPE_LIANXIE,
    
    //赢}
    E_WORD_TYPE_WIN,
    //输}
    E_WORD_TYPE_LOSE,
    //战斗开始}
    E_WORD_TYPE_FIGHT_START,
    //warning
    E_WORD_TYPE_BOSS_WARNING,
    //战斗结束}
    E_WORD_TYPE_FIGHT_FINISH,
    
}E_WORD_TYPE;
//作用对象}
typedef enum _E_EFFECT_OBJECT
{
    E_EFFECT_OBJECT_MY = 0,
    E_EFFECT_OBJECT_ENEMY = 1,
    E_EFFECT_OBJECT_ALL = 2,
}E_EFFECT_OBJECT;

//被动技能类型}
typedef enum _E_PASSIVE_TYPE
{
    E_PASSIVE_TYPE_IN_FIGHT = 1,
    E_PASSIVE_TYPE_AUTO = 2,
}E_PASSIVE_TYPE;

//战斗时机}
typedef enum _E_BATTLE_TIME
{
    E_BATTLE_TIME_WAVE_START,
    E_BATTLE_TIME_ROUND_START,
    E_BATTLE_TIME_ROUND_END,
    E_BATTLE_TIME_WAVE_END,
    
}E_BATTLE_TIME;

typedef enum _E_ATTACK_TYPE
{
    //近战}
    E_ATTACK_TYPE_MELEE = 0,
    //远程}
    E_ATTACK_TYPE_MAGIC = 1,
}E_ATTACK_TYPE;

typedef enum _E_BUFF_RECOVE_TYPE
{
    E_BUFF_RECOVE_TYPE_ADD = 0,
    E_BUFF_RECOVE_TYPE_SUB = 1,
}E_BUFF_RECOVE_TYPE;

typedef enum _E_PASSIVE_SHOW_TIME
{
    E_PASSIVE_SHOW_TIME_BIGEN = 0,
    E_PASSIVE_SHOW_TIME_BATTLE = 1,
    E_PASSIVE_SHOW_TIME_DEAD = 2,
}E_PASSIVE_SHOW_TIME;

typedef enum _E_LIANXIE_STATE
{
    E_LIANXIE_STATE_NON = 0,
    E_LIANXIE_STATE_OK,
    E_LIANXIE_STATE_LOSE,
    E_LIANXIE_STATE_LAST,
}E_LIANXIE_STATE;


//掉落物品}
typedef struct _STC_ITEM_DROP
{
    //物品Id}
    uint32 wItemType;
    //掉落个数}
    uint32 wCount;
    //单个获得数值}
    uint16 wValue;
    //剩余个数}
    uint32 wHasCount;
    
    _STC_ITEM_DROP()
    {
        wItemType = 0;
        wCount = 0;
        wHasCount = 0;
        wValue = 0;
    };
}STC_ITEM_DROP;

typedef struct _STC_BUFF
{
    //BuffId}
    uint32 wBuffId;
    //已用回合}
    uint16 wStartRound;
    //持续回合}
    uint16 wLastRound;
    //是否是新增buff
    bool isNew;
    //计算参数
    uint32 dwValuePara;
    _STC_BUFF()
    {
        wBuffId = 0;
        wStartRound = 0;
        wLastRound = 0;
        isNew = true;
        dwValuePara = 0;
    };
}STC_BUFF;

typedef struct _STC_BUFF_VALUE
{
    uint8 byBuffType;
    int dwValue;
    _STC_BUFF_VALUE()
    {
        byBuffType = 0;
        dwValue = 0;
    };
}STC_BUFF_VALUE;

typedef struct _STC_EFFECT
{
    //EffId
    uint32 wEffId;
    //附加值（吸血、回复用）}
    int dwValue;
    //技能等级}
    uint16 wLv;
    _STC_EFFECT()
    {
        wEffId = 0;
        dwValue = 0;
        wLv = 1;
    };
}STC_EFFECT;

typedef struct _STC_PASSIVE_SKILL
{
    uint32 wIndex;
    uint16 wLv;
    uint32 dwValue;
    uint16 wLastTime;
    //是否已经触发过}
    bool isTrigged;
    _STC_PASSIVE_SKILL()
    {
        isTrigged = false;
        wLastTime = 0;
    };
}STC_PASSIVE_SKILL;

typedef struct _STC_PET_EFF_BY_PSKILL
{
    uint16 fightId;
    std::vector<STC_EFFECT> arrEff;
    std::map<uint8, std::vector<STC_BUFF> > arrBuff;
}STC_PET_EFF_BY_PSKILL;

typedef struct _STC_TRIGGERED_PSKILL
{
    uint32 wSkillIndex;
    uint16 fightId; //触发者的fightId}
    std::vector<STC_PET_EFF_BY_PSKILL> arrMyEffsAndBuff;
    
    std::vector<STC_PET_EFF_BY_PSKILL> arrEnemyEffsAndBuff;
    
    _STC_TRIGGERED_PSKILL()
    {
        wSkillIndex = 0;
        fightId = 0;
    };
}STC_TRIGGERED_PSKILL;

typedef struct _STC_PET_EFF_BY_USKILL
{
    uint16 fightId; //buff与eff的受众}
    std::vector<STC_EFFECT> arrEff;
    std::map<uint8, std::vector<STC_BUFF> > arrBuff;
    
    _STC_PET_EFF_BY_USKILL()
    {
        fightId = 0;
    };

}STC_PET_EFF_BY_USKILL;



typedef struct _STC_PET_INFO
{
    //精灵ID}
    uint16 wPetIndexId;
    //精灵站位}
    uint8 wBattleIndex;
    //等级}
    uint8 petLv;
    //进阶等级}
    uint8 byEvoLv;
    //技能id}
    uint32 wSkillId;
    //技能等级}
    uint16 wSkillLv;
    uint32 dwSkillValue;//主动技能技能威力}					// new add}
    uint8  wAllPower;//主动技能冷却值}					// new add}
    
    //uint8 被动技能} size					// new del}
    //	uint16 被动技能}Id					// new del}
    //	uint8  被动技能等级}				// new del}
    
//    uint32 dwPassSkillId;//被动技能Id						// new add}
//    uint8  byPassSkillLv;//被动技能等级						// new add}
//    uint32 dwPassSkillValue;//被动技能威力						// new add}
    
//    uint32 dwTalentId;//天赋技能Id						// new add}
//    uint8  byTalenLv;//天赋技能等级						// new add}
//    uint32 dwTalenValue;//天赋技能威力						// new add}
    //普通攻击Id
    uint32 wNormalAttId;
    //队长技能Id}
    uint32 wLeaderSkillId;

    //玉技能ID}
    uint32 wGemSkillId;
    //玉技能等级}
    uint16 wGemSkillLv;
    //被动技能}
    std::map<uint32, STC_PASSIVE_SKILL> arrPassiveSkill;
    //天赋技能}
    
    
    //攻击力（基础值）}
    uint32 wBaseAttack;
    //防御（基础值）}
    uint32 wBaseDefense;
    //特攻（基础值）}
    uint32 wBaseSAttack;
    //特御（基础值）}
    uint32 wBaseSDefense;
    //回复力（基础值）}
    uint32 wBaseRestore;
    
//    uint32 dwMaxHeart;
    //暴击率（基础值）}
    uint32 wBaseLucky;
    //暴伤
    uint32 wBaseCritHurt;
    //抗暴
    uint32 wBaseCritFree;
    //速度（基础值）}
    uint32 wBaseSpeed;
    //命中}
    uint32 wBaseHit;
    //回避}
    uint32 wBaseDodge;
    
    //攻击力（服务器加成后）}
    uint32 wAttack;
    //防御（服务器加成后）}
    uint32 wDefense;
    //特攻（服务器加成后）}
    uint32 wSAttack;
    //特御（服务器加成后）}
    uint32 wSDefense;
    //回复力（服务器加成后）}
    uint32 wRestore;
    
    //    uint32 dwMaxHeart;
    //幸运（服务器加成后）}
    uint32 wLucky;
    //暴伤
    uint32 wCritHurt;
    //抗暴
    uint32 wCritFree;
    //速度（服务器加成后）}
    uint32 wSpeed;
    //命中}
    uint32 wHit;
    //回避}
    uint32 wDodge;
    
    //属性}
    uint8 petNature;
    
    uint8 petType;
    //血量}
    int wHP;
    //攻击时气增量}
    uint16 wPowerAdd;
    //受伤时气增量}
    uint16 wPowerHurtAdd;
    //初始怒气}
    uint16 wPowerCur;
    //气总量}
//    uint16 wAllPower;
    
    //是否掉箱子}
    bool isBox;
    //箱子中物品}
    std::vector<STC_ITEM_DROP> boxItem;
    
    //是否是Boss}
    bool isBoss;
    //蛋}
    bool isEgg;
    uint16 wDropPetIndexId;
    
    //当前血量}
    uint32 wCurHP;
    _STC_PET_INFO()
    {
        wCurHP = 0;
        wPowerCur = 0;
    };
    
//    //当前气量}
//    uint16 wCurPower;
//    //身上的buff序列}
//    std::vector<STC_BUFF> arrCurBuff;

    
}STC_PET_INFO;

struct STC_PET_DISINFO
{
    //精灵编号}
    uint16 wIndex;
    //精灵站位}
    uint16 wBattleIndex;
    
    uint16 wPetNature;
    //
    std::string strName;
    uint32 dwHP;
    uint32 dwCurHP;
    //死亡判定时间(30帧)}
    uint16 wDeadTime;
    
    bool isDead;
//    std::vector<STC_EFFECT> arrEff;
    std::vector<STC_BUFF> arrBuff;
    STC_PET_DISINFO()
    {
        wIndex = 0;
        wBattleIndex = 0;
        dwHP = 0;
        dwCurHP = 0;
        wDeadTime = DEADTIME;
        isDead = false;
    };
};

//帧伤害值}
typedef struct _STC_FRAME_DAMAGE
{
    uint16 wFrame;
    uint32 dwDamege;
    bool isSpark;
    //E_ATTACK_STATE attState;
    _STC_FRAME_DAMAGE()
    {
        wFrame = 0;
        dwDamege = 0;
        isSpark = false;
    }
}STC_FRAME_DAMAGE;

typedef struct _STC_ATTACK_DATA
{
    //攻击对象位置}
    uint16 wEnemyIndex;
    //总伤害}
    int dwAllDamage;
    //敌方总血量}
    uint32 dwEnemyAllHp;
    //是否命中}
    bool isHit;
    //是否已经有spark加成了}
    bool isSpark;
    //是否暴击}
    bool isCrit;
    //帧伤害值}
    std::map<uint16, STC_FRAME_DAMAGE> arrDamage;
    //属性克制}
    uint8 regulateState;
    //掉落}
    std::vector<STC_ITEM_DROP> arrItems;
    //已掉落数量}
    uint32 dwDropCnt;
    //我身上的buff序列}
    std::map<uint8, std::vector<STC_BUFF> > arrMyBuff;
    //我Eff序列}
    std::vector<STC_EFFECT> arrMyEff;
    
    //敌人身上的buff序列}
    std::map<uint8, std::vector<STC_BUFF> > arrEnemyBuff;
    //敌人的Eff序列}
    std::vector<STC_EFFECT> arrEnemyEff;
    
    //必杀值}
    uint8 curPower;
    
    //触发的被动技能}
    std::map<uint8, std::vector<STC_TRIGGERED_PSKILL> > mapPassiveSkill;
    
    std::map<uint16, STC_PET_EFF_BY_PSKILL> mapPassEffAndBuff;
    
    _STC_ATTACK_DATA()
    {
        wEnemyIndex = 0;
        dwAllDamage = 0;
        isHit = true;
        isSpark = false;
        isCrit = false;
        arrDamage.clear();
        regulateState = E_ATTRIBUTE_REGULATE_NON;
        arrItems.clear();
        dwDropCnt = 0;
        arrMyBuff.clear();
        arrMyEff.clear();
        arrEnemyBuff.clear();
        arrEnemyEff.clear();
        curPower = 0;
        mapPassiveSkill.clear();
        mapPassEffAndBuff.clear();
    };
    
}STC_ATTACK_DATA;

typedef struct _STC_BATTLE_DATA
{
    //精灵位置}
    uint16 wBattleIndex;
    //攻击技能}
    uint32 wSkillId;
    //作用对象（自己/敌人）}
    uint8 eEffObj;
    //攻击对象位置}
    std::map<uint16, STC_ATTACK_DATA> arrAttData;
    //攻击敌人的同时，对己方施加的eff(Buff会自动刷上)
    std::map<uint16, std::vector<STC_EFFECT> > mapEffToMy;
    //是否主攻 true:攻击, false:被攻击}
    bool isAttack;
    //是否回合结束}
//    bool isOverRound;
    //必杀值}
    uint8 curPower;
    
}STC_BATTLE_DATA;

typedef struct _STC_START_BATTLE_DATA
{
    //精灵位置}
    uint16 wBattleIndex;
    //攻击技能}
    uint32 dwSkillId;
    //攻击的位置}
    uint16 wAttIndex;
    //作用对象（自己/敌人）}
    uint8 eEffObj;
    //攻击对象位置}
    std::vector<uint16> arrEnemyIndexs;
    //是否主攻 true:攻击, false:被攻击}
    bool isAttack;
    
    _STC_START_BATTLE_DATA()
    {
        wBattleIndex = 0;
        dwSkillId = 0;
        wAttIndex = 1;
        eEffObj = 1;
    }
    
}STC_START_BATTLE_DATA;

typedef struct _STC_PET_CTRL_INFO
{
    //精灵位置id}
    uint16 petBattleIndex;
    //精灵编号}
    uint16 petIndex;
    
    //
    uint16 petNature;
    //名称}
    std::string name;
    //技能值}
    uint32 curSkillValue;
    //最大技能值}
    uint32 maxSkillValue;
    //破防值}
    uint32 curHP;
    //最大破防值}
    uint32 maxHP;
    //精灵战斗状态}
    int petState;
    //属性压制}
    uint8 regulateState;
    _STC_PET_CTRL_INFO()
    {
        petBattleIndex = 0;
        petIndex = 0;
    };
    
}STC_PET_CTRL_INFO;

typedef struct _STC_SKILL_TRIGGER
{
    uint16 wSize;
    uint32 wSkillId;
    uint8 byMyBuffHit;
    std::vector<uint8> arrMyEffHit;
    std::vector<uint8> byEnemyBuffHit;
    std::vector<std::vector<uint8> > arrEnemyEffHit;
    
}STC_SKILL_TRIGGER;

typedef struct _STC_PASSIVE_SKILL_TRIGGER
{
    uint16 wSize;
    uint32 wSkillId;
    uint8 byMyBuffHit;
    std::vector<uint8> arrMyEffHit;
    uint8 byEnemyBuffHit;
    std::vector<uint8> arrEnemyEffHit;
    _STC_PASSIVE_SKILL_TRIGGER()
    {
        wSize = 0;
        wSkillId = 0;
    };
    
}STC_PASSIVE_SKILL_TRIGGER;

typedef struct _STC_FIGHT_PET_INFO
{
    STC_PET_INFO petInfo;
    
//    std::vector<STC_ITEM_DROP> arrItem;

    std::vector<std::map<uint32, STC_PASSIVE_SKILL_TRIGGER> > arrPassiveSkillTrigger;

    std::vector<STC_SKILL_TRIGGER > arrSkillTrigger;
    
    std::vector<std::vector<int> > arrCritTrigger;
}STC_FIGHT_PET_INFO;

typedef struct _STC_WAIT_BATTLE_DATA
{
    uint16 key;
    //数据结算点}
    uint16 frameData;
    //战斗包播放点}
    int frame;
    //技能}
    uint32 skillId;
}STC_WAIT_BATTLE_DATA;

typedef struct _STC_BATTLE_DAMAGE_FLOAT
{
    uint32 dwCritFloat;
    uint32 dwSparkFloat;
    uint32 dwDamFloat;
    uint32 dwSkillFloat;
    uint32 dwCoinCatFloat;
    uint32 dwRecoverFloat; //回复计算}
    uint32 dwLvDamAdd;
    uint32 dwEvoLvDamAdd;
    
    uint16 arrLianXieRate[6]; //连携概率}
    uint16 arrLianXieValue[6]; //连携伤害加成}
    
}STC_BATTLE_DAMAGE_FLOAT;

//战斗前角色部分数据}
typedef struct _STC_BATTLE_PRE_DATA
{
    uint16 wUserLv;
    uint32 dwCurExp;
    uint32 dwCurEnergy;
    uint8 byCurFightCnt; //战斗位}
    uint32 dwPrePassStage; //关卡解锁用
    
    _STC_BATTLE_PRE_DATA()
    {
        wUserLv= 0;
        dwCurExp = 0;
        dwCurEnergy = 0;
        byCurFightCnt = 0;
        dwPrePassStage = 0;
    };
}STC_BATTLE_PRE_DATA;

typedef struct _STC_FIGHT_REWARD_ITEM
{
    uint32 dwItemId;
    uint32 dwCount;
    uint8 byType;   //1、首次通关，0、普通掉落}
    uint8 byIsNew;  //1、新宠，0、普通}
    _STC_FIGHT_REWARD_ITEM()
    {
        dwItemId = 0;
        dwCount = 0;
        byType = 0;
        byIsNew = 0;
    };
    
}STC_FIGHT_REWARD_ITEM;


typedef struct _STC_ARENA_ROLE_DATA
{
    uint16 wPetIconIndex;
    std::string strMyTeamName;
    uint32 dwMyRank;
    
    uint16 wEnemyIconIndex;
    std::string strEnemyTeamName;
    uint32 dwEnemyRank;
    
}STC_ARENA_ROLE_DATA;

#endif /* defined(__HelloWorld__PetBattleData__) */
