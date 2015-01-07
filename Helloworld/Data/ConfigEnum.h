#ifndef __CONFIG_ENUM_H__
#define __CONFIG_ENUM_H__

// we define column id in *.csv

//********************pet2*******************
enum
{
    E_CONFIG_COMBOID_INDEX = 101,
    E_CONFIG_COMBOID_OFF_TYPE = 401,
    E_CONFIG_COMBOID_CBTIME = 201,
    E_CONFIG_COMBOID_CBPER = 301,
};
enum
{
    E_CONFIG_LEAKER_SKILL_INDEX = 101,
    E_CONFIG_LEAKER_SKILL_NAME = 102,
    E_CONFIG_LEAKER_SKILL_TYPE = 110,
    E_CONFIG_LEAKER_SKILL_STRINKE_CONDITION = 120,
    E_CONFIG_LEAKER_SKILL_EFF_NATURE_1 = 121,
    E_CONFIG_LEAKER_SKILL_EFF_NATURE_2 = 122,
    E_CONFIG_LEAKER_SKILL_EFF_TYPE_1 = 131,
    E_CONFIG_LEAKER_SKILL_EFF_TYPE_2 = 132,
    E_CONFIG_LEAKER_SKILL_PARA = 140,
    E_CONFIG_LEAKER_SKILL_DES = 150
};

enum    //技能配置}
{
    E_CONFIG_PASSIVE_SKILL_INDEX = 101,             //技能编号}
    E_CONFIG_PASSIVE_SKILL_NAME = 102,              //技能名字}
    E_CONFIG_PASSIVE_SKILL_IS_JADE = 103,           //是否玉技能}
    E_CONFIG_PASSIVE_SKILL_IS_FOLLOW_ULIMATE = 104, //是否与主动技能同时生效}
    
    E_CONFIG_PASSIVE_SKILL_STRIKE_CONDITION_1 = 111,//触发条件1}
    E_CONFIG_PASSIVE_SKILL_STRIKE_PARA_1 = 112,     //触发参数1}
    E_CONFIG_PASSIVE_SKILL_STRIKE_CHG_1 = 113,      //触发成长1}
    E_CONFIG_PASSIVE_SKILL_STRIKE_CONDITION_2 = 114,//触发发条件2}
    E_CONFIG_PASSIVE_SKILL_STRIKE_PARA_2 = 115,     //触发参数2}
    E_CONFIG_PASSIVE_SKILL_STRIKE_CHG_2 = 116,      //触发成长2}
    
    
//    E_CONFIG_PASSIVE_SKILL_PARA = 120,
//    E_CONFIG_PASSIVE_SKILL_HURT_TYPE = 131,         //伤害类型}
//    E_CONFIG_PASSIVE_SKILL_ABI = 132,
//    E_CONFIG_PASSIVE_SKILL_LV_PARA = 141,           //技能威力}
    E_CONFIG_PASSIVE_SKILL_ATT_SCOPE = 152,         //攻击方范围}
    E_CONFIG_PASSIVE_SKILL_EFF_NATURE_1 = 161,      //作用属性1}
    E_CONFIG_PASSIVE_SKILL_EFF_NATURE_2 = 162,      //作用属性2}
    
    E_CONFIG_PASSIVE_SKILL_ATT_BUFF_HIT = 170,      //攻击方buff1命中}
    E_CONFIG_PASSIVE_SKILL_ATT_BUFF = 181,          //攻击方buff1}
    E_CONFIG_PASSIVE_SKILL_ATT_BUFF_TIME = 191,     //buff1持续时间}
    
    E_CONFIG_PASSIVE_SKILL_ATT_EFF = 201,           //攻击方effect1}
    E_CONFIG_PASSIVE_SKILL_ATT_EFF_HIT = 211,       //攻击方effect1命中}
    
    E_CONFIG_PASSIVE_SKILL_DEFF_SCOPE = 221,        //受击范围}
    E_CONFIG_PASSIVE_SKILL_DEFF_EFF_NATURE_1 = 222, //作用属性1}
    E_CONFIG_PASSIVE_SKILL_DEFF_EFF_NATURE_2 = 223, //作用属性2}
    
    E_CONFIG_PASSIVE_SKILL_DEFF_BUFF_HIT = 230,     //受击方buff1命中}
    E_CONFIG_PASSIVE_SKILL_DEFF_BUFF = 241,         //受击方buff1}
    E_CONFIG_PASSIVE_SKILL_DEFF_BUFF_TIME = 251,    //受击方buff1持续时间}
    
    E_CONFIG_PASSIVE_SKILL_DEFF_EFF = 261,          //受击方effect1}
    E_CONFIG_PASSIVE_SKILL_DEFF_EFF_HIT = 271,      //受击方effect1命中}
    
    E_CONFIG_PASSIVE_SKILL_DES = 300,               //技能描述}
    
    E_CONFIG_PASSIVE_SKILL_ICON = 301,              //技能icon}
    
    E_CONFIG_PASSIVE_SKILL_ISSHOW = 302,            //是否显示}
    
    E_CONFIG_PASSIVE_SKILL_TRIGGER_TYPE = 403,      //触发类型}
    
    E_CONFIG_PASSIVE_SKILL_LV_MAX = 400,            //等级上限}
    
    
    
};

enum
{
    E_CONFIG_ULIMATE_SKILL_INDEX = 101,
    E_CONFIG_ULIMATE_SKILL_NAME = 102,
    E_CONFIG_ULIMATE_SKILL_STRIPE_CONDITION = 103,
    E_CONFIG_ULIMATE_SKILL_COOL_CNT = 104,
    E_CONFIG_ULIMATE_SKILL_COOL_CHG = 105,
    E_CONFIG_ULIMATE_SKILL_EFF_OBJ = 106,
    E_CONFIG_ULIMATE_SKILL_TYPE = 107,
    E_CONFIG_ULIMATE_SKILL_EFF_NATURE_1 = 110,
    E_CONFIG_ULIMATE_SKILL_EFF_NATURE_2 =111,
    E_CONFIG_ULIMATE_SKILL_ATT_SCOPE = 120,
    E_CONFIG_ULIMATE_SKILL_HURT_TYPE = 121,
    E_CONFIG_ULIMATE_SKILL_ABI = 122,
    E_CONFIG_ULIMATE_SKILL_ABI_CHG = 123,
    E_CONFIG_ULIMATE_SKILL_LV_MAX = 124,
    E_CONFIG_ULIMATE_SKILL_PARA_1 = 130,
    E_CONFIG_ULIMATE_SKILL_PARA_2 = 131,
    E_CONFIG_ULIMATE_SKILL_PARA_3 = 132,
    
    E_CONFIG_ULIMATE_SKILL_ATT_BUFF_HIT = 140,
    E_CONFIG_ULIMATE_SKILL_ATT_BUFF_SCOPE = 141,
    E_CONFIG_ULIMATE_SKILL_ATT_BUFF = 151,
    E_CONFIG_ULIMATE_SKILL_ATT_BUFF_TIME = 161,
    
    E_CONFIG_ULIMATE_SKILL_ATT_EFF = 171,
    E_CONFIG_ULIMATE_SKILL_ATT_EFF_HIT = 181,
    
    E_CONFIG_ULIMATE_SKILL_DEFF_BUFF_HIT = 210,
    E_CONFIG_ULIMATE_SKILL_DEFF_BUFF = 221,
    E_CONFIG_ULIMATE_SKILL_DEFF_BUFF_TIME = 231,
    
    E_CONFIG_ULIMATE_SKILL_DEFF_EFF = 251,
    E_CONFIG_ULIMATE_SKILL_DEFF_EFF_HIT = 261,
    
    E_CONFIG_ULIMATE_SKILL_COMBOID = 300,
    E_CONFIG_ULIMATE_SKILL_EFF_ID = 301,
    E_CONFIG_ULIMATE_SKILL_DES = 302,
};

enum
{
    E_CONFIG_PET_GROUP = 100,
    E_CONFIG_PET_INDEX = 101,
    E_CONFIG_PET_NAME = 102,
    E_CONFIG_PET_NATURE_1 = 110,
    E_CONFIG_PET_NATURE_2 = 111,
    E_CONFIG_PET_TYPE_1 = 120,
    E_CONFIG_PET_TYPE_2 = 121,
    E_CONFIG_PET_STAR_LV = 130,
    E_CONFIG_PET_LV_MAX = 131,
    E_CONFIG_PET_EXP_FATIO = 132,
    
    E_CONFIG_PET_HP_VALUE = 140,
    E_CONFIG_PET_ATTACK_VALUE = 141,
    E_CONFIG_PET_DEFFENSE_VALUE = 142,
    E_CONFIG_PET_RECOVER_VALUE = 143,
    E_CONFIG_PET_LUCK_VALUE = 144,
    E_CONFIG_PET_SATTACK_VALUE = 145,
	E_CONFIG_PET_SDEFFENSE_VALUE = 146,

    E_CONFIG_PET_HP_CHG = 150,
    E_CONFIG_PET_ATTACK_CHG = 151,
    E_CONFIG_PET_DEFFENSE_CHG = 152,
    E_CONFIG_PET_RECOVER_CHG = 153,
    E_CONFIG_PET_LUCK_CHG = 154,
    E_CONFIG_PET_HIT_VALUE = 155,
    E_CONFIG_PET_DODGE_VALUE = 156,
    E_CONFIG_PET_SATTACK_CHG = 157,
    E_CONFIG_PET_SDEFFENSE_CHG =158,
    
    E_CONFIG_PET_COMBO_ID = 160,
    E_CONFIG_PET_EFFECT_ID = 161,
    E_CONFIG_PET_LEADER_SKILL_ID = 162,
    
    E_CONFIG_PET_PASSIVE_SKILL_ID_1 = 170,
    E_CONFIG_PET_PASSIVE_SKILL_ID_2 = 171,
    E_CONFIG_PET_PASSIVE_SKILL_ID_3 = 172,
    E_CONFIG_PET_TALENT_SKILL_ID    = 173,
    
    E_CONFIG_PET_INITIALSKILL_ID = 180,
    E_CONFIG_PET_NOMALE_ATT_ID = 181,
    E_CONFIG_PET_MERGE_EXP_FATIO = 190,
    E_CONFIG_PET_MERGE_COIN_FATIO = 191,
    E_CONFIG_PET_DES = 192,
    
    E_CONFIG_PET_MODEL = 193,
    E_CONFIG_PET_ATTACK_TYPE = 194,
    E_CONFIG_PET_STAND_FRAME = 195,
    E_CONFIG_PET_ATK_FRAME = 196,
    E_CONFIG_PET_KEY_FRAMES = 197,
    E_CONFIG_PET_ALT_KEY_FRAMES = 203,
    E_CONFIG_PET_MUSIC_ID = 198,
    E_CONFIG_PET_STAND_SIZE = 200,
    E_CONFIG_PET_ATK_SIZE = 199,
    E_CONFIG_PET_SOUND_LEADER = 201,
    E_CONFIG_PET_SOUND_ALT = 202,
    E_CONFIG_PET_SPEED_VALUE = 301,
    E_CONFIG_PET_SPEED_CHG = 302,
    E_CONFIG_PET_ALT_SOUND = 204,
    E_CONFIG_PET_IS_TUJIAN = 205,
    E_CONFIG_PET_IS_GACHASHOW = 206,
    E_CONFIG_PET_QY_INDEX = 401,
};

enum
{
    E_CONFIG_PETEXP_LV = 101,
    E_CONFIG_PETEXP_NEED_EXP = 102,
};

enum
{
    E_CONFIG_PET_MODEL_INDEX = 101,
    E_CONFIG_PET_MODEL_SKELETON_INDEX = 102,
    E_CONFIG_PET_MODEL_ACT_INDEX = 103,
    E_CONFIG_PET_MODEL_START_TIME_1 = 104,
    E_CONFIG_PET_MODEL_EFF_INDEX_1 = 105,
    E_CONFIG_PET_MODEL_START_TIME_2 = 106,
    E_CONFIG_PET_MODEL_EFF_INDEX_2 = 107,
    E_CONFIG_PET_MODEL_EFF_STAND = 108,
    E_CONFIG_PET_MODEL_KEY_FRAME = 109,
    E_CONFIG_PET_MODEL_MUSIC = 110,
    E_CONFIG_PET_MODEL_PART = 201,
};

enum
{
    E_CONFIG_SKILL_EFFECT_INDEX = 101,
    E_CONFIG_SKILL_EFFECT_NAME = 102,
    E_CONFIG_SKILL_EFFECT_TYPE = 103,
    
    E_CONFIG_SKILL_EFFECT_PARA = 110,
  
    E_CONFIG_SKILL_EFFECT_DES = 141,
};

enum
{
    E_CONFIG_SKILL_BUFF_INDEX = 100,
    E_CONFIG_SKILL_BUFF_NAME = 101,
    E_CONFIG_SKILL_BUFF_EFF = 102,
    E_CONFIG_SKILL_BUFF_TYPE = 103,
    E_CONFIG_SKILL_BUFF_HURT_TYPE = 104,
    E_CONFIG_SKILL_BUFF_START_TIME = 105,
    E_CONFIG_SKILL_BUFF_PARA = 110,
    E_CONFIG_SKILL_BUFF_ICON = 120,
    E_CONFIG_SKILL_BUFF_DES = 121,
    E_CONFIG_SKILL_BUFF_FLYTEXT = 122,
};

enum
{
    E_CONFIG_TRIGGER_INDEX = 101,
    E_CONFIG_TRIGGER_NAME = 102,
};

/////////////////////////////////////
//////// ResourcePic.csv ////////////
/////////////////////////////////////
enum
{
    E_CONFIG_PIC_ID = 101,
    E_CONFIG_PIC_NAME = 102,
};

/////////////////////////////////////
///// ResourceStringClient.csv //////
/////////////////////////////////////
enum {
    E_CONFIG_RESOURCE_STRING_CLIENT_ID = 101,
    E_CONFIG_RESOURCE_STRING_CLIENT_TEXT = 102,
};

enum
{
    E_CONFIG_EFFECT_GROUP_INDEX = 101,
    E_CONFIG_EFFECT_GROUP_TYPE = 102,
    E_CONFIG_EFFECT_GROUP_IS_FULL_SCREEN = 103,
    E_CONFIG_EFFECT_GROUP_PARTS = 110,
    E_CONFIG_EFFECT_GROUP_ARM_EFF = 115,
};

enum
{
    E_CONFIG_INTER_PLAY_INDEX = 100,
    E_CONFIG_INTER_PLAY_NATURE = 101,
};


#pragma mark Scene Setting Type
enum
{
    E_MAIN_HOME_LAYER = 1,
    E_MAIN_BATTLE_LAYER = 2,
    E_MAIN_CITY_LAYER = 3,
    E_MAIN_SHOP_LAYER = 4,
    E_MAIN_GACHA_LAYER = 5,
    E_MAIN_FRIEND_LAYER = 6,
};

#pragma mark Map Config
enum {
    E_MAP_CONFIG_ID = 101,
    E_MAP_CONFIG_NAME = 102,
    E_MAP_CONFIG_NEED_PASS_ID = 103,
    E_MAP_CONFIG_AREA_ID = 104,
    E_MAP_CONFIG_POS_X = 105,
    E_MAP_CONFIG_POS_Y = 106,
};

#pragma mark Stage Config
enum {
    E_STAGE_CONFIG_MAP_ID = 101,
    E_STAGE_CONFIG_STAGE_ID = 102,
    E_STAGE_CONFIG_STAGE_NAME = 103,
    E_STAGE_CONFIG_COST_ENERGY = 201,
    E_STAGE_CONFIG_FIGHT_CNT = 202,
    E_STAGE_CONFIG_INFO = 401,
    E_STAGE_CONFIG_ICON = 402,
};

#pragma mark Evlove Config
enum
{
    E_EVOLVE_CONFIG_INDEX = 100,
    E_EVOLVE_CONFIG_NEXT_ID = 101,
    E_EVOLVE_CONFIG_LV = 102,
    E_EVOLVE_CONFIG_PET_LV = 103,
    E_EVOLVE_CONFIG_ADD_HP = 104,
    E_EVOLVE_CONFIG_ADD_CATK = 105,
    E_EVOLVE_CONFIG_ADD_CDEF = 106,
    E_EVOLVE_CONFIG_ADD_REV = 107,
    E_EVOLVE_CONFIG_ADD_SATK = 110,
    E_EVOLVE_CONFIG_ADD_SDEF = 111,
    E_EVOLVE_CONFIG_ADD_CRIT = 108,
    E_EVOLVE_CONFIG_ADD_SPEED = 109,
    
    E_EVOLVE_CONFIG_EVO_ITEM_ID = 201,
    E_EVOLVE_CONFIG_EVO_ITEM_CNT = 221,
    E_EVOLVE_CONFIG_BASE_PET_ID = 300,
    E_EVOLVE_CONFIG_NEED_MONEY = 400,
    E_EVOLVE_CONFIG_NEXT_PET_ID = 401,
    
    E_EVOLVE_CONFIG_ADD_SKILL_1 = 402,
    E_EVOLVE_CONFIG_ADD_SKILL_2 = 403,
    E_EVOLVE_CONFIG_ICON = 501,
};

#pragma mark EvloveInfo Config
enum
{
    E_EVOLVE_INFO_CONFIG_INDEX = 101,
    E_EVOLVE_INFO_CONFIG_TYPE = 201,
    E_EVOLVE_INFO_CONFIG_STAGEID = 202,
    E_EVOLVE_INFO_CONFIG_DROP_PROB = 301,
    E_EVOLVE_INFO_CONFIG_DES = 102,

};

#pragma mark Item Config
enum
{
    E_ITEM_CONFIG_INDEX = 101,          //物品编号}
    E_ITEM_CONFIG_NAME = 102,           //物品名字}
    E_ITEM_CONFIG_TYPE = 103,           //物品类型}
    E_ITEM_CONFIG_DES = 104,            //物品描述}
    E_ITEM_CONFIG_QUALITY = 105,        //物品品质}
    E_ITEM_CONFIG_IS_CAN_SALE = 106,    //物品是否主动使用}
    E_ITEM_CONFIG_USE_LV = 107,         //物品使用等级}
    E_ITEM_CONFIG_GROUP_CNT = 108,      //堆叠上限}
    E_ITEM_CONFIG_MAX_HAS_CNT = 109,    //最大拥有数}
    E_ITEM_CONFIG_PRICE = 110,          //出售价格}
    E_ITEM_CONFIG_PARA = 300,           //参数1-5}
    E_ITEM_CONFIG_ICON_ID = 400,        //iconID
};

enum
{
    E_GEM_CONFIG_INDEX = 101,   //宝石物品编号}
    E_GEM_CONFIG_NAME = 102,    //宝石名字}
    E_GEM_CONFIG_TYPE = 201,    //宝石使用的技能类型，天赋技能，被动技能}
    E_GEM_CONFIG_PARAM = 202,   //宝石使用的技能ID}
    E_GEM_CONFIG_QUALITY = 203, //宝石的品质}
    E_GEM_CONFIG_ICON = 204,    //宝石icon}
    E_GEM_CONFIG_DESC = 205,    //宝石说明}
};

#pragma mark RankReward Config
enum
{
    E_RANKREWARD_CONFIG_INDEX = 101,        //组别索引}
    E_RANKREWARD_CONFIG_GROUP_NAME = 606,   //组别名字}
    E_RANKREWARD_CONFIG_MONEY = 607,        //获得金钱}
    E_RANKREWARD_CONFIG_REPUTATION = 608,   //获得声望}
    E_RANKREWARD_CONFIG_ICON = 700,         //奖励宝箱ICON}
    E_RANKREWARD_CONFIG_BADGE = 701,        //奖励徽章ICON}
    E_RANKREWARD_CONFIG_COLOR = 702,        //组别显示的颜色}
    E_RANKREWARD_CONFIG_SHOW_ITEMS = 801,   //奖励展示}
};

enum
{
    E_USERLV_CONFIG_INDEX = 101,        //等级}
    E_USERLV_CONFIG_EXP = 102,          //升级需要经验}
    E_USERLV_CONFIG_ENERGY = 103,       //体力上限}
};

enum
{
    E_TALENT_CONFIG_INDEX = 101,        //ID
    E_TALENT_CONFIG_NAME = 102,         //名称}
    E_TALENT_CONFIG_MAX_LV = 201,       //最高等级}
    E_TALENT_CONFIG_TANLENT_TYPE = 202, //天赋加成类型}
    E_TALENT_CONFIG_EFF_TYPE = 203,     //作用效果类型}
    E_TALENT_CONFIG_VALUE = 204,        //加成基础值}
    E_TALENT_CONFIG_CHG_VALUE = 205,    //等级成长值}
    E_TALENT_CONFIG_DES = 206,      //描述}
    E_TALENT_CONFIG_ICON = 207,
};


enum
{
    E_EQUIP_CONFIG_INDEX = 101,         //装备编号}
    E_EQUIP_CONFIG_EVOITEM_ID = 111,    //进阶材料编号}
    E_EQUIP_CONFIG_NAME = 102,          //装备名字}
    E_EQUIP_CONFIG_GROUP_ID = 103,          //装备类型}
    //E_EQUIP_CONFIG_USE_LV = 104,        //使用等级}
    //E_EQUIP_CONFIG_STRENGTHEN_LV = 105, //强化等级上限}
    E_EQUIP_CONFIG_POS = 106,           //装备位置}
    
    E_EQUIP_CONFIG_EFFECT_TYPE_1 = 201, //作用属性1}
    E_EQUIP_CONFIG_BASE_VAL_1 = 202,    //基础数值1}
    E_EQUIP_CONFIG_GROWTH_RATE_1 = 203, //成长数值1}
    
    E_EQUIP_CONFIG_EFFECT_TYPE_2 = 301, //作用属性2}
    E_EQUIP_CONFIG_BASE_VAL_2 = 302,    //基础数值2}
    E_EQUIP_CONFIG_GROWTH_RATE_2 = 303, //成长数值2}
    
    E_EQUIP_CONFIG_EVO_TYPE_1 = 211,    //进阶属性1
    E_EQUIP_CONFIG_EVO_DATA_TYPE_1 = 212,   //数值类型1
    E_EQUIP_CONFIG_EVO_DATA_1 = 213,    //进阶数值1
    
    E_EQUIP_CONFIG_EVO_TYPE_2 = 221,    //进阶属性2
    E_EQUIP_CONFIG_EVO_DATA_TYPE_2 = 222,   //数值类型2
    E_EQUIP_CONFIG_EVO_DATA_2 = 223,    //进阶数值2
    
    E_EQUIP_CONFIG_COST_BASE_VAL = 401, //强化消耗基准值}
    E_EQUIP_CONFIG_PRICE = 402,         //出售价格}
    E_EQUIP_CONFIG_DESC = 501,          //描述说明}
    E_EQUIP_CONFIG_ICON = 502,          //ICON}
    E_EQUIP_CONFIG_STAR = 503,          //星}
    E_EQUIP_CONFIG_QUALITY = 504,       //品质}
    
    E_EQUIP_CONFIG_EVO_ID = 600,        //进阶ID}
    E_EQUIP_CONFIG_EVO_LV = 601,        //进阶等级}
    E_EQUIP_CONFIG_EVO_COEF = 602,      //进阶系数}
    E_EQUIP_CONFIG_EVO_MATERIAL = 603,      //进阶材料1}
    E_EQUIP_CONFIG_EVO_MATERIAL_ATTRI = 604,//进阶材料属性1}
    E_EQUIP_CONFIG_EVO_MATERIAL2 = 605,     //进阶材料2}
    E_EQUIP_CONFIG_EVO_MATERIAL_ATTRI2 = 606,//进阶材料属性2}
    E_EQUIP_CONFIG_EVO_COST_MONEY = 607,    //进阶消耗金钱}
    
};

enum
{
    E_EQUIP_EVO_CONFIG_EVOITEMID = 101,
    E_EQUIP_EVO_CONFIG_EVOLV    = 102,
    E_EQUIP_EVO_CONFIG_EVOMATERIAL1 = 201,
    E_EQUIP_EVO_CONFIG_EVOMATERIAL1NUM = 202,
    E_EQUIP_EVO_CONFIG_EVOMATERIAL2 = 301,
    E_EQUIP_EVO_CONFIG_EVOMATERIAL2NUM = 302,
    E_EQUIP_EVO_CONFIG_EVOCOSTMONEY = 401,
    E_EQUIP_EVO_CONFIG_EVONEEDSTRENGTHENLV = 402,
};

enum
{
    E_RUNE_CONFIG_INDEX = 101,          //符文编号}
    E_RUNE_CONFIG_NAME = 102,           //符文名字}
    E_RUNE_CONFIG_EFFECT_TYPE_1 = 201,  //作用属性1}
    E_RUNE_CONFIG_BASE_VAL_1 = 202,     //作用数值1}
    E_RUNE_CONFIG_EFFECT_TYPE_2 = 301,  //作用属性2}
    E_RUNE_CONFIG_BASE_VAL_2 = 302,     //作用数值2}
    E_RUNE_CONFIG_COST_MONEY = 401,     //消耗金钱}
    E_RUNE_CONFIG_COST_SOUL = 402,      //消耗魂}
    E_RUNE_CONFIG_PRICE = 403,          //出售价格}
    E_RUNE_CONFIG_COMPOUND_RATE = 404,  //合成成功率}
    E_RUNE_CONFIG_COST_DOLLAR = 406,    //合成消耗的钻}
    E_RUNE_CONFIG_DESC = 501,           //描述说明}
    E_RUNE_CONFIG_ICON = 502,           //ICON}
};

enum
{
    E_EQUIP_STRENGTHEN_LEVEL = 101,     //强化等级}
    E_EQUIP_STRENGTHEN_COST = 102,      //强化消耗金钱}
};

enum
{
    E_EQUIP_COMPOUND_INDEX = 101,       //索引}
    E_EQUIP_COMPOUND_SHOWTABTYPE = 102, //标签页}
    E_EQUIP_COMPOUND_MAKEOBJID = 103,   //合成道具ID}
    E_EQUIP_COMPOUND_MAKECOUNT = 104,   //合成道具数量}
    E_EQUIP_COMPOUND_COSTOBJID = 201,   //需要的素材1的ID}
    E_EQUIP_COMPOUND_COSTCOUNT = 202,   //需要的素材1数量}
    E_EQUIP_COMPOUND_COSTSOUL = 701,    //需要消耗的魂}
    E_EQUIP_COMPOUND_COSTMONEY = 702,   //需要消耗金钱}
    E_EQUIP_COMPOUND_DESC      = 703,   //合成描述}
};

enum
{
    E_CONFIG_PASSIVE_SKILL_LV = 101,
    E_CONFIG_PASSIVE_SKILL_T_EXP = 102,
    E_CONFIG_PASSIVE_SKILL_P_EXP = 103,
};

enum
{
    E_CONFIG_ULTIMATE_SKILL_LV = 101,
    E_CONFIG_ULTIMATE_SKILL_EXP = 102,
};

// 动画序列帧}
enum {
    E_CONFIG_ANI_EFFECT_ID = 101,
    E_CONFIG_ANI_EFFECT_PATH = 102,
    E_CONFIG_ANI_EFFECT_NAME = 103,
    E_CONFIG_ANI_EFFECT_CNT = 104,
    };

// 特殊活动关卡}
enum {
    E_CONFIG_SPEMAP_ID = 101,
    E_CONFIG_SPEMAP_NAME = 102,
    E_CONFIG_SPEMAP_PIC_ID = 103,   // 图片地址}
    E_CONFIG_SPEMAP_LIMIT0 = 201,   // 限制条件[unused]}
    E_CONFIG_SPEMAP_LIMIT1 = 202,   // 限制参数[unused]}
    E_CONFIG_SPEMAP_LIMIT_LV = 203,   // 等级参数}
    E_CONFIG_SPEMAP_LIMIT_DES = 204,   // 未开启描述}
};

//7天奖励}
enum {
    E_CONFIG_REWARD_7_INDEX = 101,
    E_CONFIG_REWARD_7_ITEMID1 = 201,
    E_CONFIG_REWARD_7_ITEMCOUNT1 = 202,
    };
//30天奖励}
enum {
    E_CONFIG_REWARD_30_INDEX = 101,
    E_CONFIG_REWARD_30_ITEMID1 = 201,
    E_CONFIG_REWARD_30_ITEMCOUNT1 = 202,
};

enum {
    E_CONFIG_GUIDE_ID = 101,
    E_CONFIG_GUIDE_GROUP_ID = 102,
    E_CONFIG_GUIDE_DIALOG_ID = 103,
    E_CONFIG_GUIDE_BUTTON_ID = 104,
    E_CONFIG_GUIDE_NAME = 201,
    E_CONFIG_GUIDE_TEXT = 202,
    E_CONFIG_GUIDE_NAME_COLOR = 203,
    E_CONFIG_GUIDE_TEXT_COLOR = 204,
    E_CONFIG_GUIDE_POSY = 301,
    E_CONFIG_GUIDE_LADY_PATH = 401,
    E_CONFIG_GUIDE_LADY_OFFSET = 402,
    E_CONFIG_GUIDE_OPEN_LV = 501,
};

enum {
    E_CONFIG_GUIDE_BUTTON_KEY_ID = 101,
    E_CONFIG_GUIDE_BUTTON_POSX = 102,
    E_CONFIG_GUIDE_BUTTON_POSY = 103,
    E_CONFIG_GUIDE_BUTTON_WIDTH = 104,
    E_CONFIG_GUIDE_BUTTON_HEIGHT = 105,
    E_CONFIG_GUIDE_BUTTON_LOCK = 201,
    E_CONFIG_GUIDE_BUTTON_DIRECTION = 202,
    E_CONFIG_GUIDE_BUTTON_DARK = 203,
    E_CONFIG_GUIDE_BUTTON_SCALE = 204,
};

//成就}
enum {
    E_CONFIG_ACHIEVE_INDEX = 101,
    E_CONFIG_ACHIEVE_TYPE  = 201,
    E_CONFIG_ACHIEVE_PARAM_1 = 202,
    E_CONFIG_ACHIEVE_PARAM_2 = 203,
    E_CONFIG_ACHIEVE_REWARD_ID_1 = 301,
    E_CONFIG_ACHIEVE_REWARD_CNT_1 = 302,
    E_CONFIG_ACHIEVE_REWARD_ID_2 = 401,
    E_CONFIG_ACHIEVE_REWARD_CNT_2 = 402,
    E_CONFIG_ACHIEVE_TITLE = 501,
    E_CONFIG_ACHIEVE_DESC = 502,
    E_CONFIG_ACHIEVE_NEXT_SCENE = 503,
};

//每日任务}
enum {
    E_CONFIG_DAILY_QUEST_INDEX = 101,
    E_CONFIG_DAILY_QUEST_TYPE = 201,
    E_CONFIG_DAILY_QUEST_PARAM_1 = 202,
    E_CONFIG_DAILY_QUEST_PARAM_2 = 203,
    E_CONFIG_DAILY_QUEST_REWARD_ID_1 = 301,
    E_CONFIG_DAILY_QUEST_REWARD_CNT_1 = 302,
    E_CONFIG_DAILY_QUEST_REWARD_ID_2 = 401,
    E_CONFIG_DAILY_QUEST_REWARD_CNT_2 = 402,
    E_CONFIG_DAILY_QUEST_TITLE = 501,
    E_CONFIG_DAILY_QUEST_DESC = 502,
    E_CONFIG_DAILY_QUEST_SCORE = 503,
    E_CONFIG_DAILY_QUEST_NEXT_SCENE = 504,
};

// 随机姓名}
enum {
    E_CONFIG_RANDOM_NAME_ID = 101,
    E_CONFIG_RANDOM_FIRST_NAME = 102,
    E_CONFIG_RANDOM_SECOND_NAME = 103,
    E_CONFIG_RANDOM_THIRD_NAME = 104,
};

//宠物融合}
enum {
    E_CONFIG_PET_FUSE_INDEX = 101,
    E_CONFIG_PET_FUSE_NEED_MONEY = 102,
    E_CONFIG_PET_FUSE_GET_FUSE = 103,
    E_CONFIG_PET_FUSE_GET_FUSE_CNT = 104,
};

//邀请人奖励}
enum {
    E_CONFIG_INVITE_INDEX = 101,
    E_CONFIG_INVITE_REWARDID1 = 106,
    E_CONFIG_INVITE_REWARDCOUNT1 = 107,
    E_CONFIG_INVITE_DESC = 508,
};

//被邀请人奖励}
enum {
    E_CONFIG_INVITEE_INDEX = 101,
    E_CONFIG_INVITEE_LEVEL = 102,
    E_CONFIG_INVITEE_REWARDID1 = 103,
    E_CONFIG_INVITEE_REWARDCOUNT1 = 104,
    E_CONFIG_INVITEE_DESC = 505,
};

enum {
    E_CONFIG_EPITASIS_ID = 101,
    E_CONFIG_EPITASIS_CONTENT = 102,
    E_CONFIG_EPITASIS_NAME = 103,
    E_CONFIG_EPITASIS_PIC_ID = 104,
    E_CONFIG_EPITASIS_PIC_POS = 105,
    E_CONFIG_EPITASIS_MAP_ID = 106,
    E_CONFIG_EPITASIS_COLOR_CONTENT = 201,
    E_CONFIG_EPITASIS_COLOR_NAME = 202,
    E_CONFIG_EPITASIS_STAGE = 203,
    E_CONFIG_EPITASIS_OFF_X = 204,
    E_CONFIG_EPITASIS_OFF_Y = 205,
    E_CONFIG_EPITASIS_SCALE = 206,
    E_CONFIG_EPITASIS_INSERT_BEFORE = 207,
};

enum {
    E_CONFIG_GROW_PLAN_INDEX = 101,
    E_CONFIG_GROW_PLAN_LEVEL = 102,
    E_CONFIG_GROW_PLAN_REWARDID = 103,
    E_CONFIG_GROW_PLAN_COUNT = 104,
    E_CONFIG_GROW_PLAN_TITLE = 105,
    E_CONFIG_GROW_PLAN_DESC = 106,
};

enum {
    E_CONFIG_SYSTEM_DEB_LOCKING_INDEX = 101,
    E_CONFIG_SYSTEM_DEB_LOCKING_TYPE = 102,
    E_CONFIG_SYSTEM_DEB_LOCKING_PARA = 103,
    E_CONFIG_SYSTEM_DEB_LOCKING_GUIDEID = 105,
    E_CONFIG_SYSTEM_DEB_LOCKING_UNLOCK = 104,
    E_CONFIG_SYSTEM_DEB_LOCKING_DES = 200,
    E_CONFIG_SYSTEM_DEB_LOCKING_DES_SHOW = 201,
    E_CONFIG_SYSTEM_DEB_LOCKING_ICON = 301,
    E_CONFIG_SYSTEM_DEB_LOCKING_ICON_NAME = 302,
};

enum {
    E_CONFIG_STAGE_MAPID = 101,
    E_CONFIG_STAGE_STAGEID = 102,
    E_CONFIG_STAGE_NAME = 103,
    E_CONFIG_STAGE_ATT_CNT = 104,
    E_CONFIG_STAGE_COST_ENERGY = 201,
    E_CONFIG_STAGE_WAVE_CNT = 202,
    E_CONFIG_STAGE_FIRST_REW_ITEM_ID_1 = 501,
    E_CONFIG_STAGE_FIRST_REW_ITEM_CNT_1 = 502,
    E_CONFIG_STAGE_FIRST_REW_ITEM_ID_2 = 503,
    E_CONFIG_STAGE_FIRST_REW_ITEM_CNT_2 = 504,
    E_CONFIG_STAGE_DES = 401,
    E_CONFIG_STAGE_ICON = 402,
    E_CONFIG_STAGE_NORMAL_BGM = 601,
    E_CONFIG_STAGE_BOSS_BGM = 602,
    E_CONFIG_STAGE_FLAG = 701,
    E_CONFIG_STAGE_SHOW_MAPID = 702,
};

enum {
    E_CONFIG_STAGE_SHOW_INDEX = 401,
    E_CONFIG_STAGE_SHOW_TYPE = 100,
    E_CONFIG_STAGE_SHOW_STAGEID = 101,
    E_CONFIG_STAGE_SHOW_PETID = 201,
    E_CONFIG_STAGE_SHOW_ITEMID = 301,
};

enum {
    E_CONFIG_VIP_SHOW_INDEX = 101,
    E_CONFIG_VIP_SHOW_RECHARGE_VAL = 102,
    E_CONFIG_VIP_SHOW_SWEEP_OPEN = 103,
    E_CONFIG_VIP_SHOW_SWEEP_CNT = 104,
    E_CONFIG_VIP_SHOW_SWEEP_CLEAR = 105,
    E_CONFIG_VIP_SHOW_FRIEND_MAX = 201,
    E_CONFIG_VIP_SHOW_STAGE_BUY_MAX = 301,
    E_CONFIG_VIP_SHOW_H_STAGE_BUY_MAX = 302,
    E_CONFIG_VIP_SHOW_ACTIVITY_BUY_MAX = 303,
    E_CONFIG_VIP_SHOW_MONEY_CAT_BUY_MAX = 304,
    E_CONFIG_VIP_SHOW_TOWER_RESET_MAX = 305,
    E_CONFIG_VIP_SHOW_COIN_BUY_MAX = 306,
    E_CONFIG_VIP_SHOW_PET_BAG_MAX = 307,
    E_CONFIG_VIP_SHOW_ITEM_BAG_MAX = 309,
    E_CONFIG_VIP_SHOW_ENERGY_BUY_MAX = 310,
    E_CONFIG_VIP_SHOW_ARENA_BUY_MAX = 311,
    E_CONFIG_VIP_SHOW_DES = 600,
};

enum {
    E_ACTIVE_STAGE_CONFIG_INDEX = 102,
    E_ACTIVE_STAGE_CONFIG_NAME = 103,
    E_ACTIVE_STAGE_CONFIG_LVLIMIT = 302,
    E_ACTIVE_STAGE_CONFIG_DIFFVALUE = 303,
    E_ACTIVE_STAGE_CONFIG_PICID = 304,
    E_ACTIVE_STAGE_CONFIG_DES = 402,
    E_ACTIVE_STAGE_CONFIG_MAP_ID = 403,
    E_ACTIVE_STAGE_CONFIG_NORMAL_BGM = 601,
    E_ACTIVE_STAGE_CONFIG_BOSS_BGM = 602,
};

enum {
    E_ARENA_REWARD_CONFIG_INDEX = 101,
    E_ARENA_REWARD_CONFIG_RANK_BEGIN = 102,
    E_ARENA_REWARD_CONFIG_RANK_END = 103,
    E_ARENA_REWARD_CONFIG_MONEY_MAX = 104,
    E_ARENA_REWARD_CONFIG_MONEY_MIN = 105,
    E_ARENA_REWARD_CONFIG_REPUTATION_MAX = 106,
    E_ARENA_REWARD_CONFIG_REPUTATION_MIN = 107,
    E_ARENA_REWARD_CONFIG_ITEM_ID = 108,
    E_ARENA_REWARD_CONFIG_ITEM_COUNT = 109,
};

enum {
    E_FIRST_REWARD_CONFIG_INDEX = 101,
    E_FIRST_REWARD_CONFIG_ITEMID = 102,
    E_FIRST_REWARD_CONFIG_ITEMCOUNT = 103,
};

enum
{
    E_CONFIG_COMBO_OFF_INDEX = 101,
    E_CONFIG_COMBO_OFF_POINT = 201,
};

enum
{
    E_CONFIG_EMBLEM_INDEX = 101,
    E_CONFIG_EMBLEM_NAME = 102,
    E_CONFIG_EMBLEM_STAR_LV = 103,
    E_CONFIG_EMBLEM_MAX_LV = 104,
    E_CONFIG_EMBLEM_EXPFATIO = 105,
    E_CONFIG_EMBLEM_EATEXP = 106,
    
    E_CONFIG_EMBLEM_ATTRIBUTE = 201,
    E_CONFIG_EMBLEM_ATTRTYPE = 202,
    E_CONFIG_EMBLEM_ATTRVALUE = 203,
    E_CONFIG_EMBLEM_ATTRCHG = 204,
    
    E_CONFIG_EMBLEM_EXCPET_INDEX = 501,
    E_CONFIG_EMBLEM_EXCATTR = 502,
    E_CONFIG_EMBLEM_EXCATTRVALUE = 503,
    
    E_CONFIG_EMBLEM_DES = 108,
    E_CONFIG_EMBLEM_ICON = 109,
};

enum
{
    E_CONFIG_EXP_LV = 101,
    E_CONFIG_EXP_USER_EXP = 102,
    E_CONFIG_EXP_ENERGY = 103,
    E_CONFIG_EXP_EQUIP_COST = 104,
    E_CONFIG_EXP_PET_EXP = 105,
    E_CONFIG_EXP_TALENT_EXP = 106,
    E_CONFIG_EXP_PASSIVE_EXP = 107,
    E_CONFIG_EXP_EMBLEM_EXP = 108,
    E_CONFIG_EXP_FUSE_EQUIP_GET_MONEY = 109,
    E_CONFIG_EXP_FUSE_PET_GET_PET_ID = 110,
    E_CONFIG_EXP_FUSE_PET_GET_PET_CNT = 111,
    E_CONFIG_EXP_FUSE_PET_GET_MONEY = 112,
    E_CONFIG_EXP_FUSE_PET_GET_ITEM_ID = 113,
    E_CONFIG_EXP_FUSE_PET_GET_ITEM_CNT = 114,
};

enum
{
    E_CONFIG_TOWER_INDEX = 101,
    E_CONFIG_TOWER_IS_SPECIAL = 102,
    E_CONFIG_TOWER_MAP_ID = 106,
    E_CONFIG_TOWER_REWARD_ID = 802,
    E_CONFIG_TOWER_REWARD_COUNT = 803,
    E_CONFIG_TOWER_PET_LEVEL = 901,
    E_CONFIG_TOWER_DESC = 902,
    E_CONFIG_TOWER_PET_ICON = 903,
};

enum
{
    E_CONFIG_SUPPORT_SKILL_INDEX = 101,
    E_CONFIG_SUPPORT_SKILL_NATURE = 201,
    E_CONFIG_SUPPORT_SKILL_PASSIVE_ID = 202,
};

enum
{
    E_CONFIG_CHANLLENGE_INDEX = 101,
    E_CONFIG_CHANLLENGE_NAME = 102,
    E_CONFIG_CHANLLENGE_GROUP_ID = 201,
    E_CONFIG_CHANLLENGE_LEVEL = 202,
    E_CONFIG_CHANLLENGE_ISBOSS = 203,
    E_CONFIG_CHANLLENGE_MAP_ID = 204,
    E_CONFIG_CHANLLENGE_DROP_ITEM = 1001,
//    E_CONFIG_CHANLLENGE_DROP_ITEM_CNT = 1002,
    
    E_CONFIG_CHANLLENGE_REWARD_ITEM = 601,
    E_CONFIG_CHANLLENGE_REWARD_ITEM_CNT = 602,
};

enum
{
    E_CONFIG_CHANLLENGE_BUFF_INDEX = 101,
    E_CONFIG_CHANLLENGE_BUFF_TYPE_1 = 102,
    E_CONFIG_CHANLLENGE_BUFF_PARA_1 = 201,
    E_CONFIG_CHANLLENGE_BUFF_TYPE_2 = 202,
    E_CONFIG_CHANLLENGE_BUFF_PARA_2 = 203,
    E_CONFIG_CHANLLENGE_BUFF_DES = 205,
};

enum {
    E_STAGE_BONUS_ID = 100,
    E_STAGE_BONUS_TYPE = 101,     //关卡类型（普通关卡，精英关卡）}
    E_STAGE_BONUS_MAP_ID = 102,   // 地图点ID}
    E_STAGE_BONUS_MAX_GET = 103,  // 最大获得星星数量}
    
    E_STAGE_BONUS_REWARD_NEED = 201,
    E_STAGE_BONUS_REWARD_ID = 202,
    E_STAGE_BONUS_REWARD_CNT = 203,
};

enum {
    E_CONFIG_MUSIC_ID = 100,
    E_CONFIG_MUSIC_PATH = 101,
};

enum {
    E_CONFIG_ARMATURE_ID = 100,
    E_CONFIG_ARMATURE_PATH = 101,
    E_CONFIG_ARMATURE_NAME = 102,
};

enum {
    E_CONFIG_TIPS_ID = 101,
    E_CONFIG_TIPS_TEXT = 102,
};

enum {
    E_CONFIG_ARENA_TIME_ID = 101,
    E_CONFIG_ARENA_TIME_COST = 102,
};

enum {
    E_CONFIG_VIP_BUY_CNT = 101,
    E_CONFIG_VIP_BUY_ANENA = 102,
    E_CONFIG_VIP_BUY_ENERGY = 103,
    E_CONFIG_VIP_BUY_NORMAL_STAGE = 104,
    E_CONFIG_VIP_BUY_SPECIAL_STAGE = 105,
    E_CONFIG_VIP_BUY_MONEY_CAT = 106,
    E_CONFIG_VIP_BUY_TOWER = 107,
    E_CONFIG_VIP_BUY_HERO_STAGE = 108,
};

enum {
    E_CONFIG_PET_LIUWEI_ID = 101,
    E_CONFIG_PET_LIUWEI_HP = 201,
    E_CONFIG_PET_LIUWEI_ATK = 202,
    E_CONFIG_PET_LIUWEI_CDEF = 203,
    E_CONFIG_PET_LIUWEI_SDEF = 204,
    E_CONFIG_PET_LIUWEI_SUPP = 205,
    E_CONFIG_PET_LIUWEI_CONTROL = 206,
};

enum{
    E_CONFIG_MYSTERY_SHOP_ID = 101,
    E_CONFIG_MYSTERY_SHOP_NAME = 102,
    E_CONFIG_MYSTERY_SHOP_TYPE = 103,
    E_CONFIG_MYSTERY_SHOP_ITEM_ID = 104,
    E_CONFIG_MYSTERY_SHOP_ITEM_CNT = 106,
    E_CONFIG_MYSTERY_SHOP_CAN_BUY_CNT = 107,
    E_CONFIG_MYSTERY_SHOP_BUY_COST = 108,
    E_CONFIG_MYSTERY_SHOP_REF_COST_DOLLOR = 109,
    E_CONFIG_MYSTERY_SHOP_REF_COST_STONE = 110,
    E_CONFIG_MYSTERY_SHOP_DES = 112,
};


enum{
    E_CONFIG_ARENA_SHOP_ID = 101,
    E_CONFIG_ARENA_SHOP_NAME = 102,
    E_CONFIG_ARENA_SHOP_ITEM_ID = 103,
    E_CONFIG_ARENA_SHOP_ITEM_CNT = 104,
    E_CONFIG_ARENA_SHOP_CAN_BUY_CNT = 105,
    E_CONFIG_ARENA_SHOP_BUY_COST = 106,
    E_CONFIG_ARENA_SHOP_DES = 107,
};

enum{
    E_CONFIG_DAILY_REWARD_ID = 101,
    E_CONFIG_DAILY_REWARD_NEED_SCORE = 102,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_1 = 201,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_NUM_1 = 202,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_2 = 301,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_NUM_2 = 302,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_3 = 401,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_NUM_3 = 402,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_4 = 501,
    E_CONFIG_DAILY_REWARD_REWARD_ITEM_NUM_4 = 502,
    E_CONFIG_DAILY_REWARD_REWARD_NEXT_SCENE = 503,
};

enum{
    E_CONFIG_CHEST_INDEX = 101,
    E_CONFIG_CHEST_ITEM_INDEX1 = 200,
    E_CONFIG_CHEST_ITEM_NUM1 = 201,
    E_CONFIG_CHEST_ITEM_INDEX2 = 202,
    E_CONFIG_CHEST_ITEM_NUM2 = 203,
    E_CONFIG_CHEST_ITEM_INDEX3 = 204,
    E_CONFIG_CHEST_ITEM_NUM3 = 205,
    E_CONFIG_CHEST_ITEM_INDEX4 = 206,
    E_CONFIG_CHEST_ITEM_NUM4 = 207,
    E_CONFIG_CHEST_ITEM_INDEX5 = 208,
    E_CONFIG_CHEST_ITEM_NUM5 = 209,
    E_CONFIG_CHEST_ITEM_INDEX6 = 210,
    E_CONFIG_CHEST_ITEM_NUM6 = 211,
    E_CONFIG_CHEST_ITEM_INDEX7 = 212,
    E_CONFIG_CHEST_ITEM_NUM7 = 213,
    E_CONFIG_CHEST_ITEM_INDEX8 = 214,
    E_CONFIG_CHEST_ITEM_NUM8 = 215,
    E_CONFIG_CHEST_ITEM_ICON = 300,
    E_CONFIG_CHEST_ITEM_DES = 301,
    E_CONFIG_CHEST_ITEM_NAME = 302,
};

enum{
    E_CONFIG_WORLD_INFO_BOSS_INDEX = 101,
    E_CONFIG_WORLD_INFO_ATT_CD = 203,
    E_CONFIG_WORLD_INFO_ATT_DOLLOR = 205,
    E_CONFIG_WORLD_INFO_BLESS_MONEY = 301,
    E_CONFIG_WORLD_INFO_BLESS_MONEY_MAX = 303,
    E_CONFIG_WORLD_INFO_BLESS_MONEY_CD = 304,
    E_CONFIG_WORLD_INFO_BLESS_DOLLOR = 401,
    E_CONFIG_WORLD_INFO_BLESS_DOLLOR_MAX = 403,
};

enum {
    E_WORLD_BOSS_REWARD_CONFIG_INDEX = 101,
    E_WORLD_BOSS_REWARD_CONFIG_RANK_BEGIN = 201,
    E_WORLD_BOSS_REWARD_CONFIG_RANK_END = 202,
    E_WORLD_BOSS_REWARD_CONFIG_ITEM_ID = 301,
    E_WORLD_BOSS_REWARD_CONFIG_ITEM_COUNT = 302,
};

enum {
    E_QING_YUAN_CONFIG_INDEX = 101,
    E_QING_YUAN_CONFIG_NAME = 102,
    E_QING_YUAN_CONFIG_ATT_TYPE = 201,
    E_QING_YUAN_CONFIG_ATT_VALUE = 202,
    E_QING_YUAN_CONFIG_QY_PET = 301,
    E_QING_YUAN_CONFIG_QY_PET_NAME = 401,
};

enum
{
    E_CONFIG_EMBLEM_SHOW_INDEX = 100,
    E_CONFIG_EMBLEM_SHOW_NAME = 204,
    E_CONFIG_EMBLEM_SHOW_EXCEM_INDEX = 201,
    E_CONFIG_EMBLEM_SHOW_EXCATTR = 202,
    E_CONFIG_EMBLEM_SHOW_EXCATTRVALUE = 203,
    
    E_CONFIG_EMBLEM_SHOW_EQUIP_NAME = 404,
    E_CONFIG_EMBLEM_SHOW_EQUIP_EXCEM_INDEX = 401,
    E_CONFIG_EMBLEM_SHOW_EQUIP_EXCATTR = 402,
    E_CONFIG_EMBLEM_SHOW_EQUIP_EXCATTRVALUE = 403,
};

enum
{
    E_CONFIG_SHARE_INDEX = 101,
    E_CONFIG_SHARE_ITEM_INDEX = 103,
    E_CONFIG_SHARE_ITEM_COUNT = 104,

};

enum
{
    E_CONFIG_EQUIP_GROUP_INDEX = 103,
    E_CONFIG_EQUIP_GROUP_SUIT = 102,
    E_CONFIG_EQUIP_GROUP_NAME = 104,
    
    E_CONFIG_EQUIP_GROUP_ATTR_TYPE = 201,
    E_CONFIG_EQUIP_GROUP_ATTR_ADD_TYPE = 202,
    E_CONFIG_EQUIP_GROUP_ATTR_VALUE = 203,
    
};
#endif
