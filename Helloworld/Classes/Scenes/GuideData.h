//
//  GuideData.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-13.}
//
//

#ifndef __HelloWorld__GuideData__
#define __HelloWorld__GuideData__

#include <iostream>
#include <map>
#include <vector>
#include "cocos2d.h"
#include "Defines.h"
#include "GameSession.h"
#include "Role.h"
#include "ConfigGet.h"

USING_NS_CC;

using namespace std;

#define GUIDE_LV 30

class GuideData {
    
public:
    static GuideData* GetInstance();
    static void DestoryInstace();
    
    void Initialize();
    
    GuideData();
    virtual ~GuideData() {};
    
    typedef struct _STC_DIALOG {
        uint16 wRefButtonId;
        string strName;
        string strText;
        ccColor3B colorName;
        ccColor3B colorText;
        int nPosY;
        uint16 wLadyPath;
        uint8 byLadyOffset;
        uint16 wOpenLv;
    }STC_DIALOG;
    
    enum kStepEnum {
        E_GUIDE_TRIGGER_START = 0,
        E_GUIDE_TRIGGER_INTRO = 100,                    //开场三张漫画}
        
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_1 = 200,       //-/ 第一场战斗，敌我双方进场后，暂停加入第一句话弹版}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_2 = 201,       //-/ 第二句话弹版}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_3 = 202,       //-/ 第三句话弹版 // -- 解除暂停 -- 敌方攻击完毕，继续暂停}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_4 = 203,       //-/ 第四句话弹版}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_5 = 204,       //-/ 第五句话弹版 (命令战斗) -- 解除暂停 -- 敌方攻击完毕，继续暂停}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_6 = 205,       // 那我们就大发慈悲的告诉你
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_7 = 206,       //
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_8 = 207,
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_9 = 208,
        E_GUIDE_TRIGGER_FAKE_ATTACK_TALK_10 = 209,
        
        E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_1 = 210,      //-/ 点击站位1的宠物}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_2 = 211,      //-/ 点击站位2的宠物 -- 解除暂停 -- 敌方攻击完毕，继续暂停}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_3 = 212,      //-/ 点击站位3的宠物}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_4 = 213,      //-/ 点击站位4的宠物 -- 解除暂停 -- 敌方攻击完毕，继续暂停}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_5 = 214,      //-/ 点击站位5的宠物}
        E_GUIDE_TRIGGER_FAKE_ATTACK_TOUCH_6 = 215,      //-/ 点击站位6的宠物 -- 解除暂停 -- 敌方攻击完毕，继续暂停}
        
        E_GUIDE_TRIGGER_END_FAKE_ATTACK = 199,
        
        E_GUIDE_TRIGGER_BOSS_1_TALK = 216,      // 变身之前的说话
        E_GUIDE_TRIGGER_BOSS_2_TALK = 217,
        E_GUIDE_TRIGGER_BOSS_3_TALK = 218,
        E_GUIDE_TRIGGER_BOSS_4_TALK = 219,
        E_GUIDE_TRIGGER_BOSS_5_TALK = 220,
        E_GUIDE_TRIGGER_BOSS_6_TALK = 221,
        E_GUIDE_TRIGGER_BOSS_7_TALK = 222,      // 变身之后的说话
        
        
        E_GUIDE_TRIGGER_FAKE_ATTACK_END_1_TALK = 223,   // 战斗结束的说话1}
        
        E_GUIDE_TRIGGER_WAKE_1_TALK = 224,      // 苏醒说话
        E_GUIDE_TRIGGER_WAKE_2_TALK = 225,
        E_GUIDE_TRIGGER_WAKE_3_TALK = 226,
        
        
        E_GUIDE_TRIGGER_NAME = 300,                     // 起名字}
        
        
        E_GUIDE_TRIGGER_CHOOSE_TALK_1 = 400,                   // 选宠物 说话1}
        E_GUIDE_TRIGGER_CHOOSE_TALK_2 = 401,                    // 选宠物，说话2}
        
        // 第一次战斗}
        E_GUIDE_TRIGGER_FIR_ATTACK = 500,               //-/ 点击精灵之森 《-- MainScene -- 锁定滑动操作}
        E_GUIDE_TRIGGER_FIR_1_ATTACK = 501,             //-/ 点击冒险起始按钮 《-- MapLayer -- 屏蔽返回精英按钮}
        E_GUIDE_TRIGGER_FIR_2_ATTACK = 502,             //-/ 点击说话版 《-- MapLayer}
        E_GUIDE_TRIGGER_FIR_3_ATTACK = 503,             //-/ 点击Stage第一个关卡   《-- StageLayer}
        E_GUIDE_TRIGGER_FRI_4_ATTACK = 504,             // 点击说话版
        E_GUIDE_TRIGGER_FIR_END_ATTACK = 505,           // [new]结束第一次战斗，防止战斗中网络断开[不占ID][表明是在战斗中，而不是战斗结束，下一个ID表明战斗成功]
        
        // 上阵精灵}
        E_GUIDE_TRIGGER_TEAM = 600,                     //-/ 下方精灵按钮 《-- [StageLayer || MainScene]}
        E_GUIDE_TRIGGER_1_TEAM = 601,                   //-/ 布置阵型    《-- UnitLayer}
        E_GUIDE_TRIGGER_2_TEAM = 602,                   //-/ 点击第一号站位 《-- TeamLayer}
        E_GUIDE_TRIGGER_3_TEAM = 603,                   //-/ 背包内第一个宠物 《-- PetBagLayer}
        E_GUIDE_TRIGGER_4_TEAM = 604,                   //说话
        E_GUIDE_TRIGGER_5_TEAM = 605,
        E_GUIDE_TRIGGER_END_TEAM = 606,                 // 点击下方主页按钮 《-- TeamLayer}
        
        // 第二次战斗 }
        E_GUIDE_TRIGGER_SEC_ATTACK = 700,               // 点击精灵之森  《-- MainScene -- 锁定滑动操作}
        E_GUIDE_TRIGGER_SEC_1_ATTACK = 701,             // 点击冒险起始按钮 《-- MapLayer -- 屏蔽返回精英按钮}
        E_GUIDE_TRIGGER_SEC_2_ATTACK = 702,             // 点击Stage第二个关卡《-- StageLayer -- 进入战斗后暂停，加入属性相克Layer}
        E_GUIDE_TRIGGER_SEC_END_ATTACK = 703,           // [new]结束第二次战斗，防止战斗中网络断开[不占ID]
        
        // 召唤}
        E_GUIDE_TRIGGER_GACHA = 800,                   // 点击下方扭蛋按钮 [StageLayer || MainScene]
        E_GUIDE_TRIGGER_1_GACHA = 801,                 // 点击传说召唤
        E_GUIDE_TRIGGER_ONCE_GACHA = 802,               // 点击召唤一次(免费)
//        E_GUIDE_TRIGGER_2_GACHA = 802,                 // |！！这步不走！！|点击任意地方《-- 活动界面 <== 服务器通信（断线后直接进入精灵第二次上阵Group）}
        E_GUIDE_TRIGGER_3_GACHA = 803,                 // 点击下方宠物详细板 <== CcbTujianShowLayer
        E_GUIDE_TRIGGER_4_GACHA = 804,                 // 点击宠物版返回按钮 <== PetInfoLayer
        E_GUIDE_TRIGGER_5_GACHA = 805,                  // 点击通用返回按钮
//        E_GUIDE_TRIGGER_6_GACHA = 806,                  // 关闭召唤板
        E_GUIDE_TRIGGER_END_GACHA = 807,                // 点击主页按钮
        
        // 精灵上阵}
        E_GUIDE_TRIGGER_MAIN_TEAM = 900,                   // 点击主页第三个空位 《== MainScene)}
        E_GUIDE_TRIGGER_1_MAIN_TEAM = 901,                 // 点击背包里第一个宠物 《-- PetBagLayer}
        
        // 第三次战斗}
        E_GUIDE_TRIGGER_THI_TALK_1 = 1000,              // 说话1
        E_GUIDE_TRIGGER_THI_TALK_2 = 1001,
        E_GUIDE_TRIGGER_THI_ATTACK = 1002,              // 精灵之森点击 《-- MainScene}
        E_GUIDE_TRIGGER_THI_1_ATTACK = 1003,            // 冒险起始按钮 《-- MapLayer}
        E_GUIDE_TRIGGER_THI_2_ATTACK = 1004,            // 第三个Stage 《-- StageLayer}
        E_GUIDE_TRIGGER_THI_3_ATTACK = 1005,            // 第三关说话版 《-- StageLayer}
        E_GUIDE_TRIGGER_THI_END_ATTACK = 1006,          // [new]结束第三次战斗，防止战斗中网络断开[不占ID]
        
        // 宠物强化}
        E_GUIDE_TRIGGER_1_PRESS_MAIN  = 1100,                 // 点击主页按钮 《-- StageLayer}
        E_GUIDE_TRIGGER_PET_ENHANCE   = 1101,                 // 点击主界面第二个宠物  《== MainScene}
        E_GUIDE_TRIGGER_1_PET_ENHANCE = 1102,                 // 点击强化按钮 <== PetShowLayer
        E_GUIDE_TRIGGER_2_PET_ENHANCE = 1103,                 // 点击自动添加 <== PetEnhanceLayer
        E_GUIDE_TRIGGER_3_PET_ENHANCE = 1104,                 // 点击强化按钮 <== PetEnhanceLayer
        E_GUIDE_TRIGGER_PET_ENHANCE_1_TALK = 1105,              // 说话
        E_GUIDE_TRIGGER_PET_ENHANCE_2_TALK = 1106,
        E_GUIDE_TRIGGER_END_PET_ENHANCE = 1107,               // 点击主页按钮 <== PetEnhanceLayer
        
        // 第四次战斗}
        E_GUIDE_TRIGGER_FOUR_ATTACK = 1200,             // 精灵之森点击 《-- MainScene}
        E_GUIDE_TRIGGER_1_FOUR_ATTACK = 1201,           // 冒险起始按钮 《-- MapLayer}
        E_GUIDE_TRIGGER_2_FOUR_ATTACK = 1202,           // 第四个Stage 《-- StageLayer}
        E_GUIDE_TRIGGER_FOUR_END_ATTACK = 1203,         // [new]结束第四次战斗，防止战斗中网络断开[不占ID]
        
        // 宠物进阶}
        E_GUIDE_TRIGGER_2_PRESS_MAIN = 1300,            //点击主页按钮 《-- StageLayer}
        E_GUIDE_TRIGGER_PET_EVOLVE = 1301,              // 点击主界面第二个宠物  《== MainScene}
        E_GUIDE_TRIGGER_0_PET_EVOLVE = 1302,            // 点击进阶按钮   <== PetShowLayer
        E_GUIDE_TRIGGER_1_PET_EVOLVE = 1303,            // 点击确认进阶按钮 <== PetEvolveLayer
        E_GUIDE_TRIGGER_PET_EVOLVE_1_TALK = 1304,       //说话 <== connect to server
        E_GUIDE_TRIGGER_PET_EVOLVE_2_TALK = 1305,
        E_GUIDE_TRIGGER_PET_EVOLVE_3_TALK = 1306,
        E_GUIDE_TRIGGER_END_PET_EVOLVE = 1307,          // 点击主页按钮 《== 进阶界面
        
        // 第五次战斗
        E_GUIDE_TRIGGER_FIVE_ATTACK = 1400,             // 精灵之森点击 《-- MainScene}
        E_GUIDE_TRIGGER_1_FIVE_ATTACK = 1401,           // 冒险起始按钮 《-- MapLayer}
        E_GUIDE_TRIGGER_2_FIVE_ATTACK = 1402,           // 第五个Stage 《-- StageLayer}
        E_GUIDE_TRIGGER_FIVE_END_ATTACK = 1499,         // [new]结束第五次战斗，防止战斗中网络断开[不占ID]
        E_GUIDE_TRIGGER_GET_STAR = 1403,           // 点击满星奖励  《-- StageLayer}
        E_GUIDE_TRIGGER_1_GET_STAR = 1404,          // 点击确定按钮   <== connect to server
        E_GUIDE_TRIGGER_JUMP_NEXT = 1405,          // 点击跳转确定按钮
//        E_GUIDE_TRIGGER_MAP_2 = 1406,               // 点击地图点2
        E_GUIDE_TRIGGER_MAP_2_TALK = 1407,          // 地图点2的说话版
        
        E_GUIDE_END_TRIGGER = 1408,                 // 结束新手引导
        
        
        //-------------------系统引导-------------------//}
        // 装备引导}
        E_SYS_GUIDE_EQUIP = 1500,               // 装备解锁，点击下方精灵按钮   《-- Main主页}
        E_SYS_GUIDE_1_EQUIP = 1501,             // 装备解锁，点击装备按钮      《-- UnitMiddleLayer}
        E_SYS_GUIDE_2_EQUIP = 1502,             // 装备解锁，点击第二个宠物     《-- CcbEquipIntegrationLayer}
        E_SYS_GUIDE_3_EQUIP = 1503,             // 装备解锁，点击装备按钮      《-- CcbEquipIntegrationLayer}
        E_SYS_GUIDE_4_EQUIP = 1504,             // 装备解锁，点击自动强化按钮   《-- CcbEquipIntegrationLayer}
        E_SYS_GUIDE_END_EQUIP = 1505,           // 装备解锁，结束引导}

        
        
        // 招财猫引导
        E_SYS_GUIDE_CAT = 1600,             // 点击下方遗迹按钮
        E_SYS_GUIDE_0_CAT = 1601,           // 点击精灵挑战
        E_SYS_GUIDE_1_CAT = 1602,           // 点击招财猫按钮
        E_SYS_GUIDE_2_CAT = 1603,           // 点击战斗按钮
        E_SYS_GUIDE_END_CAT = 1604,         // 招财猫结束
        

        //竞技场引导}
        E_SYS_GUIDE_1_JJC = 1700,               // JJC解锁，点击竞技场图标    《-- MainLayer}
        E_SYS_GUIDE_2_JJC = 1701,               // JJC解锁，进入竞技场的说话
        E_SYS_GUIDE_3_JJC = 1702,               // 点击开始战斗按钮   《-- 竞技场界面}
        E_SYS_GUIDE_4_JJC = 1703,               // JJC解锁，点击最后一名玩家   《-- 竞技场战斗列表界面（开打）}
        E_SYS_GUIDE_5_JJC = 1704,               // JJC解锁，点击领取额外奖励   《-- 竞技场结算面板（随便点击即退出，不引导）}
        E_SYS_GUIDE_6_JJC = 1705,               // JJC解锁，点击声望商店         《-- 竞技场界面}
        E_SYS_GUIDE_END_JJC = 1706,             // JJC解锁，结束引导}
        
        
        
        // 精英关卡引导}
        E_SYS_GUIDE_HERO = 1800,                // 精英关卡，点击冒险   《-- Main主页}
        E_SYS_GUIDE_1_HERO = 1801,              // 精英关卡，点击左上角精英关卡   《-- MapLayer}
        E_SYS_GUIDE_2_HERO = 1802,              // 精英关卡，点击第一个地图      《-- MapLayer冒险起始按钮}
        E_SYS_GUIDE_3_HERO = 1803,              // 精英关卡，点击第一个Stage(开打)      《-- StageLayer界面}
        E_SYS_GUIDE_4_HERO = 1804,              // 精英关卡，点击下方精灵      《-- StageLayer界面}
        E_SYS_GUIDE_5_HERO = 1805,              // 精英关卡，点击装备一览      《-- UnitMiddleLayer}
        // 为什么要加上自动强化操作？？需要到30级才能进阶
        E_SYS_GUIDE_6_HERO = 1806,              // 点击自动强化按钮
        // 去除
        E_SYS_GUIDE_7_HERO = 1807,              // 点击装备进阶按钮
        E_SYS_GUIDE_END_HERO = 1808,              // 精英关卡，结束引导}

        
        
        // 爬塔引导}
        E_SYS_GUIDE_1_TOWER = 1900,             // 爬塔解锁，点击遗迹按钮      《-- MainLayer}
        E_SYS_GUIDE_2_TOWER = 1901,             // 爬塔解锁，点击爬塔按钮      《-- [(ActivityLayer)遗迹界面 -- ]MainLayer}
        E_SYS_GUIDE_3_TOWER = 1902,             // 爬塔解锁，点击前进按钮      《-- CcbTowerMainLayer}
        E_SYS_GUIDE_4_TOWER = 1903,             // 爬塔解锁，点击下方精灵      《-- CcbTowerMainLayer}
        E_SYS_GUIDE_5_TOWER = 1904,             // 爬塔解锁，点击符文镶嵌      《-- UnitMiddleLayer}
        
        /***-8-***/
        E_SYS_GUIDE_6_TOWER = 1905,             // 爬塔解锁，点击选择装备      《-- EquipListLayer}
        E_SYS_GUIDE_7_TOWER = 1906,             // 爬塔解锁，点击镶嵌     《-- EquipInlayLayer}
        E_SYS_GUIDE_8_TOWER = 1907,             // 点击第一个宝石
        E_SYS_GUIDE_9_TOWER = 1908,             // 点击弹版镶嵌按钮
        /***-8-***/
        
        E_SYS_GUIDE_END_TOWER = 1909,           // 爬塔解锁，结束引导}
        
        
        
        // 徽章引导}
        E_SYS_GUIDE_BADGE = 2000,               // 徽章解锁，点击下方遗迹按钮       《-- MainLayer}
        E_SYS_GUIDE_1_BADGE = 2001,             // 徽章解锁，点击遗迹挑战          《-- ActivityLayer}
        E_SYS_GUIDE_2_BADGE = 2002,             // 徽章解锁，点击天气         《--CcbEmblemListLayer}
        E_SYS_GUIDE_3_BADGE = 2003,             // 徽章解锁，点击遗迹点         <-- PetBagLayer}
        E_SYS_GUIDE_4_BADGE = 2004,             // 点击我要挑战按钮
        E_SYS_GUIDE_5_BADGE = 2005,             // 点击遗迹界面返回按钮
        E_SYS_GUIDE_5_1_BADGE = 2006,             // 点击下方精灵按钮
        E_SYS_GUIDE_6_BADGE = 2007,             // 点击阵容按钮
        E_SYS_GUIDE_7_BADGE = 2008,             // 点击阵容第一个宠物
        E_SYS_GUIDE_8_BADGE = 2009,             // 点击左下角的徽章位置
        E_SYS_GUIDE_9_BADGE = 2010,             // 徽章界面点击装备按钮
        E_SYS_GUIDE_10_BADGE = 2011,            // 宠物界面说话1
        E_SYS_GUIDE_11_BADGE = 2012,            // 宠物界面说话2
        E_SYS_GUIDE_12_BADGE = 2013,            // 宠物界面说话3
        E_SYS_GUIDE_END_BADGE = 2014,           // 徽章解锁，结束引导}

        
        // 神秘商店引导
        E_SYS_GUIDE_MYSTERY = 2100,             // 点击领取第一个星级奖励
        E_SYS_GUIDE_1_MYSTERY = 2101,           // 点击确定按钮
        E_SYS_GUIDE_2_MYSTERY = 2102,           // 点击精灵按钮
        E_SYS_GUIDE_3_MYSTERY = 2103,           // 点击分解
        E_SYS_GUIDE_4_MYSTERY = 2104,           // 点击添加精灵
        E_SYS_GUIDE_5_MYSTERY = 2105,           // 点击开始分解
        E_SYS_GUIDE_6_MYSTERY = 2106,           // 点击确定分解
        E_SYS_GUIDE_7_MYSTERY = 2107,           // 点击ShowGet获得的确定按钮
        E_SYS_GUIDE_8_MYSTERY = 2108,           // 跳转到神秘商店
        E_SYS_GUIDE_END_MYSTERY = 2109,         // 结束引导
        
        E_GUIDE_TRIGGER_END = 9999,
    };
    
    enum{
        E_GUIDE_UNLOCK_TYPE_LV = 1,
        E_GUIDE_UNLOCK_TYPE_STAGE = 2,
    };
//    enum{
//        E_GUIDE_UNLOCK_
//    };
    /*
     宠物装备ICON	1}
     村庄	2
     装备屋	3
     合成屋	4
     融合屋	5
     竞技场	6
     宠物技能Icon	7
     祭炼	8
     神秘商店	9
     精英关卡	10
     镶嵌	11
     活动关卡	12
     装备一览 13
     爬塔     14
     道馆挑战 15
     装备强化 16
     装备进阶 17
     遗迹挑战 18
     */
    enum{
        E_GUIDE_UNLOCK_BTN_EQUIP_ICON = 1,
        E_GUIDE_UNLOCK_BTN_COUNTRY = 2,
        E_GUIDE_UNLOCK_BTN_EQUIP = 3,
        E_GUIDE_UNLOCK_BTN_COMPOUND = 4,
        E_GUIDE_UNLOCK_BTN_FUSE = 5,
        E_GUIDE_UNLOCK_BTN_ARENA = 6,
        E_GUIDE_UNLOCK_BTN_PET_SKILL = 7,
        E_GUIDE_UNLOCK_BTN_REFINE = 8,
        E_GUIDE_UNLOCK_BTN_MY_STERY_SHOP = 9,
        E_GUIDE_UNLOCK_BTN_SPECIAL = 10,
        E_GUIDE_UNLOCK_BTN_INLAY = 11,
        E_GUIDE_UNLOCK_BTN_ACTIVITY = 12,
        E_GUIDE_UNLOCK_BTN_UNIT_EQUIP = 13,
        E_GUIDE_UNLOCK_BTN_PATA = 14,
        E_GUIDE_UNLOCK_BTN_DAOGUAN = 15,
        E_GUIDE_UNLOCK_BTN_EQUIP_ENHANCE = 16,
        E_GUIDE_UNLOCK_BTN_EQUIP_EVO = 17,
        E_GUIDE_UNLOCK_BTN_YIJI = 18,
    };
    
    
    /*
     装备	1
     村庄	2
     竞技场	3
     神秘商店	4
     精英关卡	5
     活动	6
     探索	7
     队伍编辑 8
     符文镶嵌 9
     爬塔 10
     徽章 11
     */
    enum{
        E_GUIDE_FUNC_ICON_FIGHT_CNT = 99,
        E_GUIDE_FUNC_ICON_EQUIP = 1,
        E_GUIDE_FUNC_ICON_COUNTRY = 2,
        E_GUIDE_FUNC_ICON_ARENA = 3,
        E_GUIDE_FUNC_ICON_MY_STERY = 4,
        E_GUIDE_FUNC_ICON_SPECIAL_STAGE = 5,
        E_GUIDE_FUNC_ICON_ACTIVITY_STAGE = 6,
        E_GUIDE_FUNC_ICON_NORMAL_STAGE = 7,
        E_GUIDE_FUNC_ICON_EDIT_TEAM = 8,
        E_GUIDE_FUNC_ICON_RUNE_INLAY = 9,
        E_GUIDE_FUNC_ICON_PATA = 10,
        E_GUIDE_FUNC_ICON_BADGE = 11,
    };
private:
    typedef std::map<uint16, STC_DIALOG> MAP_DIALOG;
    typedef std::map<uint16, MAP_DIALOG> MAP_GUIDE;
    
    typedef SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG STC_LOCK;
    typedef std::map<uint16, STC_LOCK> MAP_LOCK;
private:
    MAP_GUIDE m_mapGuide;
    MAP_DIALOG m_mapData;
    
    STC_DIALOG m_stcData;

    int m_nStepId;
    int m_nGroupId;
    
    MAP_LOCK mapLock;
    uint32 m_dwSysLockId;
    
public:
    MAP_DIALOG getCurGuideData();

    void stepOver();
    void connectToServer();
    
    bool triggerOn();
    
    /*!
     * 增加对应enum的guidelayer
     */
    void addGuideofEnum(GuideData::kStepEnum kenum, ...);
    
    void addGuideLayer(bool connect = false, bool step = true);
    void onlyRmGuideLayer();
    void setStepId(int step);
    void setGroupId(uint16 groupId);
    void setSysLockId(uint32 dwSysLockId);
    uint32 getSysLockId(){return m_dwSysLockId;};
    /*!
     * 跳过当前Group的新手引导
     */
    void skipCurGroup();
    
    void skipCurStep();
    
    //系统解锁}
    /*!
     * 格式化保存用 guideId
     */
    void formateLockGuideId();
    
    uint16 checkSystemLock(uint8 type);
    
    uint16 checkBtnLock(uint16 wBtn);
    
    /*!
     */
    void runSystemGuide(uint16 wGroupId);
};

#endif /* defined(__HelloWorld__GuideData__) */
