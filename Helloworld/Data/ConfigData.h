//
//  ConfigData.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-7-15.}
//
//

#ifndef __HelloWorld__ConfigData__
#define __HelloWorld__ConfigData__

#include "Defines.h"
#include <string>
#include "ConfigBase.h"
#include "Log.h"
#include "ConfigEnum.h"

#define GET_CONFIG_STC( _T, _ID )   \
((_T*)Client::g_ConfigMap[ _T::GetName() ])->GetById( _ID )

#define GET_CONFIG_MAP( _T )        \
((_T*)Client::g_ConfigMap[ _T::GetName() ])->GetMap()



//1
class ComboIdConfig : public ConfigBase
{
public:
    typedef struct STC_COMBOID_CONFIG
    {
        uint16 wComboId;
        uint16 wComboOffId;
        uint32 dwComboTime[15];
        uint32 dwComboPer[15];
    } STC_COMBOID_CONFIG;
    
    CONFIG_GET_BY_ID( STC_COMBOID_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_COMBOID_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ComboIdConfig"; };
};

//2
class LeaderSkillConfig : public ConfigBase
{
public:
    typedef struct STC_LEADER_SKILL_CONFIG
    {
        uint32 wIndex;
        std::string strName;
        uint8 wSkillType[5];
        uint16 wStrikeCondition;
        
        uint8 byEffectNature1;
        uint8 byEffectNature2;
        
        uint8 byEffectType1;
        uint8 byEffectType2;
        uint32 szSkillPara[8];
        
        std::string strDes;
        
    } STC_LEADER_SKILL_CONFIG;
    
    CONFIG_GET_BY_ID( STC_LEADER_SKILL_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_LEADER_SKILL_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "LeaderSkillConfig"; };
};

//3
class PassiveSkillConfig : public ConfigBase
{
public:
    typedef struct STC_PASSIVE_SKILL_CONFIG
    {
        uint32 dwIndex;             //技能编号]}
        std::string strName;        //技能名字]}
        
        uint8 byIsJade;             //是否玉技能]}
        uint8 byIsFlollowUlimate;   //是否与主动技能同时生效]}
        
        uint8 byTriggerType;        //触发类型]}
        
        uint16 wStrikeCondition1;   //触发条件1]}
        uint16 wStrikePara1;        //触发参数1]}
        uint16 wStrikeChg1;         //触发成长1]}
        uint16 wStrikeCondition2;   //触发发条件2]}
        uint16 wStrikePara2;        //触发参数2]}
        uint16 wStrikeChg2;         //触发成长2]}
        
//        uint32 szSkillPara[5];
        
//        uint8 byHurtType;           //伤害类型}
//        uint32 dwSkillAbi;
        
//        uint32 szLevelPara[5];      //技能威力}
        
//        uint16 wAttackerEffectId;
        uint8  byAttackerScope;     //攻击方范围}
        
        uint8  byEffectNature1;     //作用属性1}
        uint8  byEffectNature2;     //作用属性2}
        
        uint32 wAttackBuff[3];      //攻击方buff1~buff3}
        uint16 wAttackBuffHit;      //攻击方buff1命中}
        uint16 wAttackBuffTime[3];  //攻击方buff1~buff3持续时间}
        
        uint32 wAttackEff[3];       //攻击方effect1~effect3}
        uint16 wAttackEffHit[3];    //攻击方effect1~effect3命中}
        

        uint8  byDeffenseScope;         //受击范围}
        uint8  byDeffenseEffectNature1; //作用属性1}
        uint8  byDeffenseEffectNature2; //作用属性2}
        
        uint32 wDeffenseBuff[3];        //受击方buff1}
        uint16 wDeffenseBuffHit;        //受击方buff1命中}
        uint16 wDeffenseBuffTime[3];    //受击方buff1~buff3}
        
        uint32 wDeffenseEff[3];         //受击方effect1}
        uint16 wDeffenseEffHit[3];      //受击方effect1命中}
        
        std::string strDes;             //技能描述}
        
        uint32 wIcon;                   //技能icon}
        uint16 wMaxLv;                 //等级上限}
        
        uint8 byIsShow;                 //是否显示此被动技能}
        
    } STC_PASSIVE_SKILL_CONFIG;
    
    CONFIG_GET_BY_ID( STC_PASSIVE_SKILL_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_PASSIVE_SKILL_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "PassiveSkillConfig"; };
};


class UltimateSkillConfig : public ConfigBase
{
public:
    typedef struct STC_ULIMATE_SKILL_CONFIG
    {
        uint32 wIndex;
        uint8 byType;
        std::string strName;
        
        uint16 wStripeCondition;
        
        uint8 bySkillCoolCnt;
        uint8 bySkillCoolChg;
        
        uint8 byEffectObj;
        uint8 byEffectNature1;
        uint8 byEffectNature2;
        
        uint8 byAttackScope;
        uint8 byHurtType;
        uint32 dwSkillAbi;
        uint32 dwSkillAbiChg;
        uint8 bySkillLvMax;
        
        uint32 dwSkillPara1;
        uint32 dwSkillPara2;
        uint32 dwSkillPara3;
        
        uint32 wAttackBuff[3];
        uint16 wAttackBuffHit;
        uint8 byAttackBuffScope;
        uint16 wAttackBuffTime[3];
        
        uint32 wAttackEff[3];
        uint16 wAttackEffHit[3];
        
        uint32 wDeffenseBuff[3];
        uint16 wDeffenseBuffHit;
        uint16 wDeffenseBuffTime[3];
        
        uint32 wDeffenseEff[3];
        uint16 wDeffenseEffHit[3];
        
        uint32 wComboid;
        
        uint32 wShowEffectId;
        
        std::string strDes;
    } STC_ULIMATE_SKILL_CONFIG;
    
    CONFIG_GET_BY_ID( STC_ULIMATE_SKILL_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_ULIMATE_SKILL_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "UltimateSkillConfig"; };
};

//4
class PetConfig : public ConfigBase
{
public:
    typedef struct STC_PET_CONFIG
    {
        uint16 wGroupId;
        uint16 wIndex;
        std::string strName;
        uint8 byNature1;
        uint8 byNature2;
        uint8 byType1;
        uint8 byType2;
        uint8 byStarLv;
        uint8 byLvMax;
        uint32 dwExpFatio;
        
        uint32  dwHpValue;
        uint32  dwAttackValue;
        uint32  dwDeffenseValue;
        uint32  dwSAttackValue;
        uint32  dwSDeffenseValue;
        uint32  dwRecoverValue;
        uint32  dwLuckValue;
        uint32  dwHitValue;
        uint32  dwDodgeValue;
        uint32  dwSpeedValue;
        
        
        uint32  dwHpChg;
        uint32  dwAttackChg;
        uint32  dwDeffenseChg;
        uint32  dwSAttackChg;
        uint32  dwSDeffenseChg;
        uint32  dwRecoverChg;
        uint32  dwLuckChg;
        uint32  dwSpeedChg;
        
        uint16  wComboId;
        uint16  wEffectId;
        
        uint32  wLeaderSkillId;
        
        uint32	wPassiveSkillId1;
        uint32	wPassiveSkillId2;
        uint32  wPassiveSkillId3;
        uint32  dwTalentId;
        uint32  wInitialSkillId;
        uint32  dwNomaleAttId;
        
        uint32  dwMergeExpFatio;
        uint32  dwMergeCoinFatio;
        std::string strDes;
        
        uint32 dwModelIndex;
        
        uint8 byAttackType;
        
        uint16 wStandFrame;
        uint16 wAtkFrame;
        std::string strKeyFrames;
        std::string strAltKeyFrames;
        uint16 wMusicId;
        
        std::string strStandSize;
        std::string strAtkSize;
        
        uint16 wSoundLeader;
        uint16 wSoundAlt;
        
        uint16 wAltEffSound;
        uint8 byIsTujian;
        uint8 byIsGachaShow;
        
        uint32 arrQyIndex[4];
        
    } STC_PET_CONFIG;
    
    CONFIG_GET_BY_ID( STC_PET_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_PET_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "PetConfig"; };
};

//5
class PetExpConfig : public ConfigBase
{
public:
    typedef struct STC_PETEXP_CONFIG
    {
        uint16 wPetLv;
        uint32 dwNeedExp;
    } STC_PETEXP_CONFIG;
    
    CONFIG_GET_BY_ID( STC_PETEXP_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_PETEXP_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "PetExpConfig"; };
};

class PetModel : public ConfigBase
{
public:
    typedef struct STC_PET_MODEL_CONFIG
    {
        uint32 wIndex;
        uint16 wSkeletonIndex;
        uint16 wActIndex;
        uint16 wStartTime1;
        uint16 wEffIndex1;
        uint16 wStartTime2;
        uint16 wEffIndex2;
        uint16 wEffStandIndex;
        std::string strKeyFrame;
        uint8 byMusicId;
        
        std::map<uint8, uint8> mapPart;
    } STC_PET_MODEL_CONFIG;
    
    CONFIG_GET_BY_ID( STC_PET_MODEL_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_PET_MODEL_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "PetModel"; };
};

//6
class SkillEffectConfig : public ConfigBase
{
public:
    typedef struct STC_SKILL_EFFECT_CONFIG
    {
        uint32 wIndex;
        std::string strName;
        uint8 byType;
        
        uint32 szSkillPara[3];

        std::string strDes;
    } STC_SKILL_EFFECT_CONFIG;
    
    CONFIG_GET_BY_ID( STC_SKILL_EFFECT_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_SKILL_EFFECT_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "SkillEffectConfig"; };
};

class SkillBuffConfig : public ConfigBase
{
public:
    typedef struct STC_SKILL_BUFF_CONFIG
    {
        uint32 wIndex;
        std::string strName;
        uint16 wBuffEff;
        uint16 wType;
        uint16 wHurtType;
        uint8 byStartTime;
        
        uint32 buffPara[3];
        uint32 wIcon;
        std::string strDes;
        std::string strFlyText;
    } STC_SKILL_BUFF_CONFIG;
    
    CONFIG_GET_BY_ID( STC_SKILL_BUFF_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_SKILL_BUFF_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "SkillBuffConfig"; };
};

class TriggerConfig : public ConfigBase
{
public:
    typedef struct STC_TRIGGER_CONFIG
    {
        uint16 wIndex;
        std::string strName;
    
    } STC_TRIGGER_CONFIG;
    
    CONFIG_GET_BY_ID( STC_TRIGGER_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_TRIGGER_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "TriggerConfig"; };
};

//7
class ResourcePicConfig : public ConfigBase
{
public:
    typedef struct STC_CONFIG_RESOURCE_PIC
    {
        uint32 dwPicId;
        std::string strPicName;
        
    }STC_CONFIG_RESOURCE_PIC;
    
    CONFIG_GET_BY_ID( STC_CONFIG_RESOURCE_PIC, uint32 );
    CONFIG_GET_MAP( STC_CONFIG_RESOURCE_PIC, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ResourcePicConfig"; };
};

class ResourceStringClientConfig : public ConfigBase {
    
public:
    typedef struct STC_CONFIG_RESOURCE_STRING_CLIENT
    {
        uint32 dwId;
        std::string strText;
    } STC_CONFIG_RESOURCE_STRING_CLIENT;
    
    CONFIG_GET_BY_ID( STC_CONFIG_RESOURCE_STRING_CLIENT, uint32 );
    CONFIG_GET_MAP( STC_CONFIG_RESOURCE_STRING_CLIENT, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ResourceStringClientConfig"; };
};

class EffectGroupConfig : public ConfigBase
{
public:
    typedef struct STC_EFFECT_GROUP_CONFIG
    {
        uint32 wIndex;
        uint8 byType;
        uint8 byAltEffType;
        std::vector<std::string> effParts;
        std::string strArmEff;
        
    } STC_EFFECT_GROUP_CONFIG;
    
    CONFIG_GET_BY_ID( STC_EFFECT_GROUP_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EFFECT_GROUP_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EffectGroupConfig"; };
};

class InterPlayConfig : public ConfigBase
{
public:
    typedef struct STC_INTER_PLAY_CONFIG
    {
        uint16 wIndex;
        
        //std::vector<uint16> arrNature;
        uint16 arrNature[6];
    } STC_INTER_PLAY_CONFIG;
    
    CONFIG_GET_BY_ID( STC_INTER_PLAY_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_INTER_PLAY_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "InterPlayConfig"; };
};

class MapConfig : public ConfigBase {
    
public:
    typedef struct STC_MAP_CONFIG {
        uint16 wMapId;
        std::string strName;
        uint16 wNeedPassId;
        uint8 byAreaId;
        uint16 posX;
        uint16 posY;
    } STC_MAP_CONFIG;
    
    CONFIG_GET_BY_ID( STC_MAP_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_MAP_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "MapConfig"; };
};

class EvolveConfig : public ConfigBase {
    
public:
    typedef struct STC_EVOLVE_CONFIG {
        uint32 wIndex;
        uint32 wNextId;
        uint8 byLv;
        uint16 wPetLv;
        uint32 dwAddHP;
        uint32 dwAddSATK;
        uint32 dwAddSDEF;
        uint32 dwAddREV;
        uint32 dwAddCATK;
        uint32 dwAddCDEF;
        uint32 dwAddCRIT;
        uint32 dwAddSPEED;
        
        uint32 wEvoItemId[5];
        uint32 byEvoItemCnt[5];
        uint16 wBasePetId;
        uint16 wNextPetId;
        uint32 dwNeedMoney;
        uint32 dwAddSkillId1;
//        uint32 dwAddSkillId2;
        uint8 byIcon;
        
    } STC_EVOLVE_CONFIG;
    
    CONFIG_GET_BY_ID( STC_EVOLVE_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EVOLVE_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EvolveConfig"; };
};

class EvolveInfoConfig : public ConfigBase {
    
public:
    typedef struct STC_EVOLVE_INFO_CONFIG {
        uint32 wIndex;
        std::string strDes;
        uint8 arrStageType[12];
        uint32 arrStageId[12];
        uint8 arrDropProb[12];
        
    } STC_EVOLVE_INFO_CONFIG;
    
    CONFIG_GET_BY_ID( STC_EVOLVE_INFO_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EVOLVE_INFO_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EvolveInfoConfig"; };
};

class ItemConfig : public ConfigBase {
    
public:
    struct STC_ITEM_CONFIG {
        uint32 wIndex;          //物品编号}
        std::string strName;    //物品名字}
        uint8 byType;           //物品类型，区分不同道具类型，如普通物品，碎片，礼包，技能书， 不能区分宝石和装备}
        std::string strDesc;    //物品描述}
        uint8 byQuality;        //物品品质}
        uint8 byIsCanSale;       //是否能出售}
        uint16 wUseLv;          //物品使用等级}
        uint16 wGroupCnt;       //物品堆叠上限}
        uint16 wMaxHasCnt;      //物品持有数最大值]}
        uint32 dwPrice;         //物品出售时的价格]}
        uint32 wParas[5];       //参数，具体参数意义根据道具功能来定}
        uint32 dwIconId;         //物品icon索引}
        
    } ;
    
    CONFIG_GET_BY_ID( STC_ITEM_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_ITEM_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ItemConfig"; };
};
typedef  ItemConfig::STC_ITEM_CONFIG ITEM_CONFIG_DATA;
typedef  ItemConfig::STC_ITEM_CONFIG* LP_ITEM_CONFIG;

class GemConfig : public ConfigBase{
public:
    struct STC_GEM_CONFIG
    {
        uint32 dwIndex;
        std::string strName;
        uint8 byType;
        uint16 wParam;
        uint8 byQuality;
        std::string strDesc;
        uint32 wIcon;
    };
    
    CONFIG_GET_BY_ID( STC_GEM_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_GEM_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "GemConfig"; };
};

//排行榜宝箱奖励}
class RankRewardConfig : public ConfigBase{
    
public:
    struct STC_RANKREWARD_CONFIG
    {
        uint16 wIndex;
        std::string strGroupName;   //组名}
        uint32 dwGetMoney;          //获得金钱}
        uint32 dwGetReputation;      //获得声望}
        uint16 wIcon;               //宝箱Icon}
        uint16 wBadge;              //徽章}
        uint32 dwcolor;             //颜色}
        uint32 dwShowItems[10];     //奖励展示}
    };
    
    CONFIG_GET_BY_ID( STC_RANKREWARD_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_RANKREWARD_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "RankRewardBattleInfo"; };
};

class UserLvConfig : public ConfigBase{
    
public:
    struct STC_USERLV_CONFIG
    {
        uint16 wIndex;
        uint32 dwExp;
        uint16 wEnergy;
    };
    
    CONFIG_GET_BY_ID( STC_USERLV_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_USERLV_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "UserLvConfig"; };
};

#if 0
//装备--不用}
class EquipConfig : public ConfigBase
{
    
public:
    struct STC_EQUIP_CONFIG
    {
        uint32 dwIndex;//装备编号}
        
        std::string strName;    //装备名字}
        uint32 dwGroupId;           //装备类型}
        //uint16 wUseLV;          //使用等级]}
        //uint16 wStrengthenLv;   //强化等级上限}
        uint8 byPos;            //装备位置}
        
        uint8 byEffectType1;    //作用属性1}
        uint16 wEffectValue1;   //基础数值1}
        uint16 wGrowthRate1;    //成长数值1}
        
        uint8 byEffectType2;
        uint16 wEffectValue2;
        uint16 wGrowthRate2;
        
        uint32 dwCostBaseValue; //强化消耗基准值}
        uint32 dwPrice;         //出售价格}
        std::string strDesc;    //描述说明}
        uint32 dwIcon;          //Icon}
        uint8 byStar;           //星}
        uint8 byQuality;        //品质}
        
        uint32 dwEvoID;         //进阶后ID}
        uint16 wEvoLV;          //进阶等级}
        uint16 wEvoCoef;        //进阶系数}
        uint32 dwEvoMaterial1;  //进阶材料1}
        uint32 dwEvoMaterialAttri1;//进阶材料属性1}
        
        uint32 dwEvoMaterial2;
        uint32 dwEvoMaterialAttri2;
        
        uint32 dwEvoCostMoney;  //进阶消耗金钱}
    };
    
    CONFIG_GET_BY_ID( STC_EQUIP_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EQUIP_CONFIG, uint32) ;
    virtual bool Load( const char* );
    static const char* GetName() { return "Equip"; };
};
typedef  EquipConfig::STC_EQUIP_CONFIG EQUIP_CONFIG_DATA;
typedef  EquipConfig::STC_EQUIP_CONFIG* LP_EQUIP_CONFIG;
#endif

//装备}
class EquipNewConfig
: public ConfigBase
{
public:
    struct STC_EQUIP_CONFIG
    {
        uint32 dwIndex;//装备编号}
        uint32 dwEvoItemID; //进阶材料ID
        std::string strName;    //装备名字}
        
        uint8 byPos;            //装备位置}
        
        uint8 byEffectType1;    //作用属性1}
        uint16 wEffectValue1;   //基础数值1}
        uint16 wGrowthRate1;    //成长数值1}
        
        uint8 byEffectType2;
        uint16 wEffectValue2;
        uint16 wGrowthRate2;
        
        uint8 byEvoType1;   //进阶属性1
        uint8 byEvoDataType1;   //数值类型1
        uint32  dwEvoData1;     //进阶数值1
        
        uint8 byEvoType2;   //进阶属性2
        uint8 byEvoDataType2;   //数值类型2
        uint32  dwEvoData2;     //进阶数值2
        
        uint32 dwCostBaseValue; //强化消耗基准值}
        uint32 dwPrice;         //出售价格}
        std::string strDesc;    //描述说明}
        uint32 dwIcon;          //Icon}
        uint8 byStar;           //星}
        uint8 byQuality;        //品质}
        
    };
    
    CONFIG_GET_BY_ID( STC_EQUIP_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EQUIP_CONFIG, uint32) ;
    virtual bool Load( const char* );
    static const char* GetName() { return "EquipNew"; };
};
typedef  EquipNewConfig::STC_EQUIP_CONFIG EQUIPNEW_CONFIG_DATA;
typedef  EquipNewConfig::STC_EQUIP_CONFIG* LP_EQUIPNEW_CONFIG;

class EquipEvoConfig
: public ConfigBase
{
public:
    struct STC_EQUIP_EVO_CONFIG
    {
        uint32 dwEvoItemId;     //进阶材料编号
        uint16 wEvoLv;
        
        uint32 dwEvoMaterial1;  //进阶材料1}
        uint32 dwEvoMaterial1Num;//进阶材料属性1}
        
        uint32 dwEvoMaterial2;
        uint32 dwEvoMaterial2Num;
        uint32 dwEvoCostMoney;  //进阶消耗金钱}
        uint32 dwEvoNeedStrengthenLv;   //进阶需要强化等级
    };
    
    CONFIG_GET_BY_ID( STC_EQUIP_EVO_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EQUIP_EVO_CONFIG, uint32) ;
    virtual bool Load( const char* );
    static const char* GetName() { return "EquipEvoConfig"; };
    
};

typedef  EquipEvoConfig::STC_EQUIP_EVO_CONFIG EQUIPEVO_CONFIG_DATA;
typedef  EquipEvoConfig::STC_EQUIP_EVO_CONFIG* LP_EQUIPEVO_CONFIG;

//符文}
class RuneConfig : public ConfigBase{
    
public:
    struct STC_RUNE_CONFIG
    {
        uint32 dwIndex;         //符文编号}
        std::string strName;    //符文名字}
        uint8 byEffectType1;    //作用属性1}
        uint16 wEffectValue1;   //作用数值1}
        uint8 byEffectType2;    //作用属性2}
        uint16 wEffectValue2;   //作用数值2}
        uint32 dwCostMoney;     //消耗金钱}}
        uint32 dwCostSoul;      //消耗魂}
        uint32 dwPrice;         //出售价格}
        uint16 wCompoundRate;   //合成成功率}
        uint32 dwCostDollor;    //合成消耗钻石}
        std::string strDesc;    //描述说明}
        uint32 dwIcon;           //ICON}
    };
    
    CONFIG_GET_BY_ID( STC_RUNE_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_RUNE_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "Rune"; };
};
typedef  RuneConfig::STC_RUNE_CONFIG RUNE_CONFIG_DATA;
typedef  RuneConfig::STC_RUNE_CONFIG* LP_RUNE_CONFIG;

//装备强化金钱消耗}
class EquipStrengthenConfig : public ConfigBase{
    
public:
    struct STC_EQUIP_STRENGTHEN_CONFIG
    {
        uint8 byLevel;
        uint32 dwCostMoney;
    };
    CONFIG_GET_BY_ID( STC_EQUIP_STRENGTHEN_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EQUIP_STRENGTHEN_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EquipStrengthen"; };
};

//
class EquipCompoundConfig : public ConfigBase{
    
public:
    struct STC_EQUIP_COMPOUND_CONFIG
    {
        uint16 wIndex;          //索引}
        uint8 byShowTabType;    //标签页}
        
        uint32 dwMakeObjID;     //合成后的ID}
        uint16 wMakeCount;      //合成后的数量}
        
        uint32 dwCostObjID[5];  //合成需要的素材}
        uint16 wCostCount[5];   //合成需要的素材数量}
        uint32 dwCostSoul;      //需要消耗的魂}
        uint32 dwCostMonye;     //需要消耗的金钱}
        std::string strDesc;    //描述}
    };
    CONFIG_GET_BY_ID( STC_EQUIP_COMPOUND_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_EQUIP_COMPOUND_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EquipCompound"; };
};

//天赋技能}
class TalentConfig : public ConfigBase{
    
public:
    struct STC_TALENT_CONFIG
    {
        uint32 wIndex;
        std::string strName;
        uint16 wMaxLv;
        uint8 byTalentType;
        uint8 byEffType; //1、通常；2、万分比；3、固定值}
        uint32 dwValue;
        uint32 dwChgValue;
        std::string strDes;
        uint32 dwIcon;
    };
    
    CONFIG_GET_BY_ID( STC_TALENT_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_TALENT_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "TalentConfig"; };
};

//被动技能经验}
class PassiveSkillExpConfig : public ConfigBase{
    
public:
    struct STC_PASSIVE_SKILL_EXP_CONFIG
    {
        uint16 wIndex;
        uint32 dwTValue;
        uint32 dwPValue;
    };
    
    CONFIG_GET_BY_ID( STC_PASSIVE_SKILL_EXP_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_PASSIVE_SKILL_EXP_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "PassiveSkillExpConfig"; };
};

//主动技能经验}
class UltimateSkillExpConfig : public ConfigBase{
    
public:
    struct STC_ULTIMATE_SKILL_EXP_CONFIG
    {
        uint16 wIndex;
        uint32 dwValue;
    };
    
    CONFIG_GET_BY_ID( STC_ULTIMATE_SKILL_EXP_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_ULTIMATE_SKILL_EXP_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "UltimateSkillExpConfig"; };
};


// 动画效果配表}
class AnimationEffectConfig : public ConfigBase {

public:
    struct STC_ANIMATION_EFFECT_CONFIG
    {
        uint16 wIndex;
        std::string strPath;
        std::string strName;
        uint16  wCnt;
    };
    CONFIG_GET_BY_ID( STC_ANIMATION_EFFECT_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_ANIMATION_EFFECT_CONFIG, uint16 );
    virtual bool Load( const char * );
    static const char* GetName() { return "AnimationEffectConfig"; };
};

class SpecialMapConfig : public ConfigBase {
    
public:
    struct STC_SPECIAL_MAP_CONFIG {
        uint16 wMapId;
        std::string strMapName;
        uint16 wPicId;
        uint16 wLimitLv;         // 等级参数}
        std::string wLimitDes;    // 未开启描述}
    };
    CONFIG_GET_BY_ID( STC_SPECIAL_MAP_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_SPECIAL_MAP_CONFIG, uint16 );
    virtual bool Load( const char * );
    static const char* GetName() { return "SpecialMapConfig"; };
};

class EventReward7Config : public ConfigBase{

public:
    struct STC_EVENT_REWARD_7_CONFIG {
        uint16 wIndex;
        uint32 dwItemID[4];
        uint32 dwItemCount[4];
    };
    CONFIG_GET_BY_ID( STC_EVENT_REWARD_7_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_EVENT_REWARD_7_CONFIG, uint16 );
    virtual bool Load( const char * );
    static const char* GetName() { return "EventReward7Config"; };
};

class EventReward30Config : public ConfigBase{
    
public:
    struct STC_EVENT_REWARD_30_CONFIG {
        uint16 wIndex;
        uint32 dwItemID[4];
        uint32 dwItemCount[4];
    };
    CONFIG_GET_BY_ID( STC_EVENT_REWARD_30_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_EVENT_REWARD_30_CONFIG, uint16 );
    virtual bool Load( const char * );
    static const char* GetName() { return "EventReward30Config"; };
};

class GuideConfig : public ConfigBase {
    
public:
    struct STC_GUIDE_CONFIG {
        uint16 wId;
        uint16 wGroupId;
        uint16 wDialogId;
        uint16 wButtonId;
        std::string strName;
        std::string strText;
        uint16 wNameColor;
        uint16 wTextColor;
        int nPosY;
        uint16 wLadyPath;
        uint8 byLadyOffset;
        uint16 wOpenLv;
    };
    CONFIG_GET_BY_ID( STC_GUIDE_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_GUIDE_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "GuideConfig"; };
};

class GuideButtonConfig : public ConfigBase {
    
public:
    struct STC_GUIDE_BUTTON_CONFIG {
        uint16 wId;
        uint8 byLock;
        uint8 byDirection;
        uint8 byDark;
    };
    CONFIG_GET_BY_ID( STC_GUIDE_BUTTON_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_GUIDE_BUTTON_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "GuideButtonConfig"; };
};

class AchieveRewardConfig : public ConfigBase {
    
public:
    struct STC_ACHIEVE_REWARD_CONFIG {
        uint32 dwIndex;
        uint8 byType;
        uint32 dwParam[2];
        uint32 dwRewardID[2];
        uint32 dwRewardCnt[2];
        std::string strTitle;
        std::string strDesc;
        std::string strNextScene;
    };
    CONFIG_GET_BY_ID( STC_ACHIEVE_REWARD_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_ACHIEVE_REWARD_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "AchieveRewardConfig"; };
};
#define ACHIEVE_REWARD_CONFIG AchieveRewardConfig::STC_ACHIEVE_REWARD_CONFIG

class DailyQuestConfig : public ConfigBase {
    
public:
    struct STC_DAILY_QUEST_CONFIG {
        uint32 dwIndex;
        uint8 byType;
        uint32 dwParam[2];
        uint32 dwRewardID[2];
        uint32 dwRewardCnt[2];
        std::string strTitle;
        std::string strDesc;
        uint32 dwScore;
        std::string strNextScene;
    };
    CONFIG_GET_BY_ID( STC_DAILY_QUEST_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_DAILY_QUEST_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "DailyQuestConfig"; };
};
#define DAILY_QUEST_CONFIG DailyQuestConfig::STC_DAILY_QUEST_CONFIG

class RandomNameConfig : public ConfigBase {
    
public:
    struct STC_RANDOM_NAME {
        uint32 dwIndex;
        std::string strFistName;
        std::string strSecondName;
        std::string strThirdName;
    };
    CONFIG_GET_BY_ID( STC_RANDOM_NAME, uint32 );
    CONFIG_GET_MAP( STC_RANDOM_NAME, uint32 );
    virtual bool Load(const char* );
    static const char* GetName() { return "RandomNameConfig"; };
};


class PetFuseConfig : public ConfigBase {
    
public:
    struct STC_PET_FUSE_CONFIG {
        uint32 wIndex;
        uint32 dwNeedMoney;
        uint32 wGetItemId;
        uint32 wGetCnt;
    };
    CONFIG_GET_BY_ID( STC_PET_FUSE_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_PET_FUSE_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "PetFuseConfig"; };
};

class InviteConfig : public ConfigBase
{
public:
    struct STC_INVITE_CONFIG
    {
        uint32 dwIndex;
        uint32 dwRewardID[5];
        uint32 dwRewardCount[5];
        std::string strDesc;
    };
    CONFIG_GET_BY_ID( STC_INVITE_CONFIG, uint32);
    CONFIG_GET_MAP( STC_INVITE_CONFIG, uint32);
    virtual bool Load( const char* );
    static const char* GetName() { return "InviteConfig"; };
};
#define INVITE_CONFIG InviteConfig::STC_INVITE_CONFIG

class InviteeConfig : public ConfigBase
{
public:
    struct STC_INVITEE_CONFIG
    {
        uint32 dwIndex;
        uint8 byLevel;
        uint32 dwRewardID[5];
        uint32 dwRewardCount[5];
        std::string strDesc;
    };
    CONFIG_GET_BY_ID( STC_INVITEE_CONFIG, uint32);
    CONFIG_GET_MAP( STC_INVITEE_CONFIG, uint32);
    virtual bool Load( const char* );
    static const char* GetName() { return "InviteeConfig"; };
};
#define INVITEE_CONFIG InviteeConfig::STC_INVITEE_CONFIG

class EpitasisConfig : public ConfigBase {
    
public:
    struct STC_EPITASIS_CONFIG {
        uint32 dwIndex;
        std::string strContent;
        std::string strName;
        uint16 wPicIndex;
        uint8 byPicPos;
        uint16 wMapId;
        uint8 byContentColor;
        uint8 byNameColor;
        uint16 wStageId;
        int nOffX;
        int nOffY;
        uint16 wScale;
        uint8 byInsertBefore;
    };
    CONFIG_GET_BY_ID( STC_EPITASIS_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EPITASIS_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EpitasisConfig"; };
};

class GrowPlanConfig : public ConfigBase {
    
public:
    struct STC_GROW_PLAN_CONFIG {
        uint32 dwIndex;
        uint8 byLevel;
        uint32 dwRewardID;
        uint32 dwCount;
        std::string strTitle;
        std::string strDesc;
    };
    CONFIG_GET_BY_ID( STC_GROW_PLAN_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_GROW_PLAN_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "GrowPlanConfig"; };
    
};

class SystemDebLockingConfig : public ConfigBase {
    
public:
    struct STC_SYSTEM_DEB_LOCKING_CONFIHG {
        uint16 dwIndex;
        uint8 byType;
        uint16 wPara;
        std::string strUnLock;
        uint32 dwGuideId;
        std::string strDesc;
        std::string strDescShow;
        uint16 wIcon[3];
        std::string strIconName[3];
    };
    CONFIG_GET_BY_ID( STC_SYSTEM_DEB_LOCKING_CONFIHG, uint16 );
    CONFIG_GET_MAP( STC_SYSTEM_DEB_LOCKING_CONFIHG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "SystemDebLockingConfig"; };
    
};


class StageConfig : public ConfigBase {
    
public:
    struct STC_STAGE_CONFIG {
        uint32 dwMapId;
        uint32 dwStageId;
        std::string strName;
        uint16 wAttCnt; //可攻击次数，0为不限制}
        uint16 wCostEnergy;
        uint16 wWaveCnt;
        uint32 dwFirstRewItemId1;   // 首次通关获得的第一个物品ID}
        uint32 dwFirstRewItemCnt1;  // 首次通关获得的第一个物品的数量}
        uint32 dwFirstRewItemId2;   // 首次通关获得的第二个物品ID}
        uint32 dwFirstRewItemCnt2;  // 首次通关获得的第二个物品的数量}
        std::string strDesc;
        uint32 dwStageIcon;
        std::vector<int> vectNormalBgm;
        std::vector<int> vectBossBgm;
        uint8 byFlag;       // 是否需要加红标
        uint16 wShowMapId;
    };
    CONFIG_GET_BY_ID( STC_STAGE_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_STAGE_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "StageConfig"; };
    
};

class StageHConfig : public ConfigBase {
    
public:
    struct STC_STAGE_H_CONFIG {
        uint32 dwMapId;
        uint32 dwStageId;
        std::string strName;
        uint16 wAttCnt; //可攻击次数，0为不限制}
        uint16 wCostEnergy;
        uint16 wWaveCnt;
        uint32 dwFirstRewItemId1;
        uint32 dwFirstRewItemCnt1;
        uint32 dwFirstRewItemId2;
        uint32 dwFirstRewItemCnt2;
        std::string strDesc;
        uint32 dwStageIcon;
        uint16 wBattleMapId;
        std::vector<int> vectNormalBgm;
        std::vector<int> vectBossBgm;
        uint8 byFlag;       // 是否需要加红标
        uint16 wShowMapId;
    };
    CONFIG_GET_BY_ID( STC_STAGE_H_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_STAGE_H_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "StageHConfig"; };
    
};

class StageShowConfig : public ConfigBase {
    
public:
    struct STC_STAGE_SHOW_CONFIG {
        uint32 dwIndex;
        uint8 byType;   //1、普通关卡，2、精英关卡}
        uint32 dwStageId;
        uint32 arrPetId[6];
        uint32 arrItemId[6];
    };
    CONFIG_GET_BY_ID( STC_STAGE_SHOW_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_STAGE_SHOW_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "StageShowConfig"; };
    
};

class VipShowConfig : public ConfigBase {
    
public:
    struct STC_VIP_SHOW_CONFIG {
        uint16  wIndex;
        uint32  dwRechargeVal;
        uint8   bySweepOpen;
        uint16  wFreeSweepCnt;
        uint8   bySweepCanClear;
        uint16  wFriendMax;
        uint16  wStageBuyMax;
        uint16  wHStageBuyMax;
        uint16  wActivityBuyMax;
        uint16  wMoneyCatBuyMax;
        uint16  wTowerResetMax;
        uint16  wCoinBuyMax;
        uint16  wPetBagMax;
        uint16  wItemBagMax;
        uint16  wEnergyBuyMax;
        uint16  wArenaBuyMax;
        std::string strDes;
    };
    CONFIG_GET_BY_ID( STC_VIP_SHOW_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_VIP_SHOW_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "VipShowConfig"; };
    
};
#define VIP_SHOW_CONFIG VipShowConfig::STC_VIP_SHOW_CONFIG

class ActiveStageConfig : public ConfigBase {
public:
    struct STC_ACTIVE_STAGE_CONFIG {
        uint16 wIndex;
        uint8 byLvLimit;
        
        std::string strName;
        std::string strDes;
        uint8 byDiffiValue;
        uint8 byPicId;
        uint16 wBattleMapId;
        std::vector<int> vectNormalBgm;
        std::vector<int> vectBossBgm;
    };
    CONFIG_GET_BY_ID( STC_ACTIVE_STAGE_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_ACTIVE_STAGE_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ActiveStageConfig"; };

};

class ArenaRewardConfig : public ConfigBase {
public:
    struct STC_ARENA_REWARD_CONFIG {
        uint16 wIndex;
        uint16 wRankBegin;
        uint16 wRankEnd;
        uint32 dwMoneyMax;
        uint32 dwMoneyMin;
        uint32 dwReputationMax;
        uint32 dwReputationMin;
        uint32 dwItemID[5];
        uint32 dwItemCount[5];
    };
    CONFIG_GET_BY_ID( STC_ARENA_REWARD_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_ARENA_REWARD_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ArenaRewardConfig"; };
};

class FirstRechargeConfig : public ConfigBase {
public:
    struct STC_FIRST_RECHARGE_CONFIG {
        uint16 wIndex;
        uint32 dwItemID[5];
        uint32 dwItemCount[5];
    };
    CONFIG_GET_BY_ID( STC_FIRST_RECHARGE_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_FIRST_RECHARGE_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "FirstRechargeConfig"; };
};

class ComboOffConfig : public ConfigBase
{
public:
    typedef struct STC_COMBO_OFF_CONFIG
    {
        uint16 wIndex;
        int arrComboOffX[15];
        int arrComboOffY[15];
        
    } STC_COMBO_OFF_CONFIG;
    
    CONFIG_GET_BY_ID( STC_COMBO_OFF_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_COMBO_OFF_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ComboOffConfig"; };
};

class EmblemConfig : public ConfigBase
{
public:
    typedef struct STC_EMBLEM_CONFIG
    {
        uint32 dwIndex;
        std::string strName;
        uint8 byStarLv;
        uint16 wMaxLv;
        uint32 dwExpFatio;
        uint32 dwEatExp;
        uint8 byAttribute[3];
        uint8 byAttrType[3];
        uint32 dwAttrValue[3];
        uint32 dwAttrChg[3];
        
        uint16 wExcPetIndex[5];
        uint8 byExcAttr[5];
        uint32 dwExcAttrValue[5];
        
        std::string strDes;
        uint32 wIcon;
        
    } STC_EMBLEM_CONFIG;
    
    CONFIG_GET_BY_ID( STC_EMBLEM_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EMBLEM_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EmblemConfig"; };
};


class ExpConfig : public ConfigBase
{
public:
    typedef struct STC_EXP_CONFIG
    {
        uint16 wLv;
        uint32 dwUserExp;
        uint32 dwEnergyMax;
        uint32 dwEquipCost;
        uint32 dwPetExp;
        uint32 dwTalentExp;
        uint32 dwPassiveExp;
        uint32 dwEmblemExp;
        uint32 dwGetEquipFuseMoney;
        
        uint32 dwGetPetFusePetId;
        uint32 dwGetPetFusePetCnt;
        uint32 dwGetPetFuseMoney;
        uint32 dwGetPetFuseItemId;
        uint32 dwGetPetFuseItemCnt;
        
    } STC_EXP_CONFIG;
    
    CONFIG_GET_BY_ID( STC_EXP_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_EXP_CONFIG, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "ExpConfig"; };
};

class TowerConfig : public ConfigBase
{
public:
    struct STC_TOWER_CONFIG
    {
        uint16 wIndex;
        uint8  byIsSpecial;
        uint16 wBattleMapId;
        uint32 dwRewardID[4];
        uint32 dwRewardCount[4];
        uint32 dwPetLevel;
        std::string strDesc;
        uint32 dwPetIcon;
    };
    
    CONFIG_GET_BY_ID( STC_TOWER_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_TOWER_CONFIG, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "TowerConfig"; };
};
#define TOWER_CONFIG TowerConfig::STC_TOWER_CONFIG

class SupportSkillConfig : public ConfigBase
{
public:
    struct STC_SUPPORT_SKILL_CONFIG
    {
        uint16 wPetIndex;
        uint8 byNature[4];
        uint32 dwPassSkillId[4];
    };
    
    CONFIG_GET_BY_ID( STC_SUPPORT_SKILL_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_SUPPORT_SKILL_CONFIG, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "SupportSkillConfig"; };
};

class ChallengeConfig : public ConfigBase
{
public:
    struct STC_CHALLENGE_CONFIG
    {
        uint16 wIndex;
        std::string strName;
        
        uint32 dwRewardItem[4];
        uint32 dwRewardItemCnt[4];
        uint32 dwShowMapId;
    };
    
    CONFIG_GET_BY_ID( STC_CHALLENGE_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_CHALLENGE_CONFIG, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "ChallengeConfig"; };
};

class ChallengeBuffConfig : public ConfigBase
{
public:
    struct STC_CHALLENGE_BUFF_CONFIG
    {
        uint16 wIndex;
        uint8 byBuffType1;
        uint32 dwPara1;
        uint8 byBuffType2;
        uint32 dwPara2;
        std::string strDesc;
    };
    
    CONFIG_GET_BY_ID( STC_CHALLENGE_BUFF_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_CHALLENGE_BUFF_CONFIG, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "ChallengeBuffConfig"; };
};

class StageBonusConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_BONUS {
        uint16  wIndex;
        uint8   byStageType;
        uint16  wMapId;
        uint16  wMaxGetCnt;

        uint16 wRewardNeed[3];
        uint32 dwRewardId[3];
        uint32 dwRewardCnt[3];
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_BONUS, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_BONUS, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "StageBonusConfig"; };
};

class MusicConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_MUSIC {
        uint16 wIndex;
        std::string strPath;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_MUSIC, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_MUSIC, uint16 );
    virtual bool Load( const char * );
    
    static const char* GetName() { return "MusicConfig"; };
};

class ArmatureConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_ARMATURE {
        uint16 wIndex;
        std::string strPath;
        std::string strName;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_ARMATURE, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_ARMATURE, uint16 );
    virtual bool Load( const char * );
    
    static const char* GetName() { return "ArmatureConfig"; }
};

class TipsConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_TIPS {
        uint16 wIndex;
        std::string strText;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_TIPS, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_TIPS, uint16 );
    virtual bool Load( const char * );
    
    static const char* GetName() { return "TipsConfig"; }
};

class VipBuyConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_VIP_BUY {
        uint16 wBuyCnt;
        uint16 wArena;
        uint16 wEnergy;
        uint16 wNormalStage;
        uint16 wSpecialStage;
        uint16 wMoneyCat;
        uint16 wTower;
        uint16 wHeroStage;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_VIP_BUY, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_VIP_BUY, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "VipBuyConfig"; }
};

class PetLiuWeiConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_PET_LIUWEI {
        uint16 wIndex;
        uint16 wHp;
        uint16 wAtk;
        uint16 wCDef;
        uint16 wSDef;
        uint16 wSupp;
        uint16 wControl;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_PET_LIUWEI, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_PET_LIUWEI, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "PetLiuWeiConfig"; }
};


class MysteryShopConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_MYSTERY_SHOP {
        uint16 wIndex;
        std::string strName;
        uint8 byType;
        uint32 dwItemId;
        uint32 dwItemCnt;
        uint32 dwCanBuyCnt;
        uint32 dwBuyCost;
        uint32 dwRefCostDollor;
        uint32 dwRefCostStone;
        std::string strDes;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_MYSTERY_SHOP, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_MYSTERY_SHOP, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "MysteryShopConfig"; }
};

class ArenaShopConfig : public ConfigBase {
    
public:
    struct STC_CONFIG_ARENA_SHOP {
        uint16 wIndex;
        std::string strName;
        uint32 dwItemId;
        uint32 dwItemCnt;
        uint32 dwCanBuyCnt;
        uint32 dwBuyCost;
        std::string strDes;
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_ARENA_SHOP, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_ARENA_SHOP, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "ArenaShopConfig"; }
};

class DailyRewardConfig
: public ConfigBase
{
public:
    struct STC_CONFIG_DAILYREWARD
    {
        uint16 wRewardId;
        uint32 dwNeedScore;
        uint32 dwRewardItemId[4];
        uint32 dwRewardItemNum[4];
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_DAILYREWARD, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_DAILYREWARD, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "DailyRewardConfig"; }
};


class ChestConfig
: public ConfigBase
{
public:
    struct STC_UNITE_RESOURCE
    {
        uint32 dwUniteId;
        uint32 dwUniteCnt;
        
        STC_UNITE_RESOURCE()
        : dwUniteId(0), dwUniteCnt(0)
        {
        }
        
    };
    struct STC_CONFIG_CHEST
    {
        uint32 dwIndex;
        std::vector<STC_UNITE_RESOURCE> vecInfo;
        uint16 wIcon;
        std::string strDes;
        std::string strName;
    };
    CONFIG_GET_BY_ID( STC_CONFIG_CHEST, uint32 );
    CONFIG_GET_MAP( STC_CONFIG_CHEST, uint32 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "ChestConfig"; }
};

class WorldBossInfoConfig
: public ConfigBase
{
public:
    struct STC_CONFIG_WORLD_BOSS_INFO
    {
        uint16 wBossIndex;
        uint32 dwAttCDTime;
        uint32 dwAttFuhuoDollor;
        uint32 dwBlessMoney;
        uint32 dwBlessMoneyAddMax;
        uint32 dwBlessDollor;
        uint32 dwBlessDollorAddMax;
        uint32 dwBlessMoneyCD;
        
    };
    
    CONFIG_GET_BY_ID( STC_CONFIG_WORLD_BOSS_INFO, uint16 );
    CONFIG_GET_MAP( STC_CONFIG_WORLD_BOSS_INFO, uint16 );
    virtual bool Load( const char* );
    
    static const char* GetName() { return "WorldBossInfoConfig"; }
};

class WorldBossRewardConfig : public ConfigBase {
public:
    struct STC_WORLD_BOSS_REWARD_CONFIG {
        uint16 wIndex;
        uint16 wRankBegin;
        uint16 wRankEnd;
        uint32 dwItemID[4];
        uint32 dwItemCount[4];
    };
    CONFIG_GET_BY_ID( STC_WORLD_BOSS_REWARD_CONFIG, uint16 );
    CONFIG_GET_MAP( STC_WORLD_BOSS_REWARD_CONFIG, uint16 );
    virtual bool Load( const char* );
    static const char* GetName() { return "WorldBossRewardConfig"; };
};

class QingYuanConfig : public ConfigBase {
public:
    struct STC_QING_YUAN_CONFIG {
        uint32 wIndex;
        std::string strName;
        uint32 dwAttType;
        uint32 dwAttValue;
        uint32 dwQyPetGroup[4];
        std::string strPetName[4];
    };
    CONFIG_GET_BY_ID( STC_QING_YUAN_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_QING_YUAN_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "QingYuanConfig"; };
};

class EmblemShowConfig : public ConfigBase
{
public:
    struct STC_EMBLEM_SHOW_CONFIG
    {
        uint32 dwIndex;
        std::string strName[2];
        uint32 wExcEmIndex[2];
        uint8 byExcAttr[2];
        uint32 dwExcAttrValue[2];
        
        std::string strExcEquipName;
        uint32 wExcEquipIndex;
        uint8 byExcEquipAttr;
        uint32 dwExEquipcAttrValue;
    };
    
    CONFIG_GET_BY_ID( STC_EMBLEM_SHOW_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EMBLEM_SHOW_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EmblemShowConfig"; };
};

class ShareConfig : public ConfigBase
{
public:
    struct STC_SHARE_CONFIG
    {
        uint32 dwIndex;
        uint32 dwItemIndex;
        uint32 dwItemCount;
    };
    CONFIG_GET_BY_ID( STC_SHARE_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_SHARE_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "ShareConfig"; };
};

class EquipGroupConfig : public ConfigBase
{
public:
    struct STC_EQUIP_GROUP_CONFIG
    {
        uint32 dwEquipGroupId;
        uint32 dwSuitId;
        std::string strName;
        
        uint8 byAttrType_1[2];
        uint8 byAttrAddType_1[2];
        uint32 dwAttrValue_1[2];
        
        uint8 byAttrType_2[2];
        uint8 byAttrAddType_2[2];
        uint32 dwAttrValue_2[2];
        
        uint8 byAttrType_3[2];
        uint8 byAttrAddType_3[2];
        uint32 dwAttrValue_3[2];
        
    };
    CONFIG_GET_BY_ID( STC_EQUIP_GROUP_CONFIG, uint32 );
    CONFIG_GET_MAP( STC_EQUIP_GROUP_CONFIG, uint32 );
    virtual bool Load( const char* );
    static const char* GetName() { return "EquipGroupConfig"; };
};
#endif /* defined(__HelloWorld__ConfigData__) */




