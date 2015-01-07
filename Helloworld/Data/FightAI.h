//
//  FigthAI.h
//  HelloWorld
//
//  Created by long on 13-8-26.
//
//

#ifndef __HelloWorld__FightAI__
#define __HelloWorld__FightAI__

#include <iostream>
#include "FightPet.h"
#include "PetBattleData.h"
#include "WorldPacket.h"
#include "FightPet.h"
#include "FightTeam.h"
#include "Singleton.h"

class FightAI : public Singleton<FightAI>
{
public:
    FightAI();
    ~FightAI();
    
    
    typedef std::map<uint16, STC_BATTLE_DATA> MAP_BATTLE_DATAS;
    
    //接收PVP数据}
    void handlerPVPInfo(WorldPacket &packet);//{m_pvpData = packet;};
    WorldPacket* getPVPData(){return &m_pvpData;};
    //设置PVP队伍}
    void setPVPTeam(FightTeam* myTeam, FightTeam* enemyTeam)
    {
        m_myTeam = myTeam;
        m_enemyTeam = enemyTeam;
        m_arrEnemyTeams.clear();
        m_arrEnemyTeams.push_back(m_enemyTeam);
    };
    //获取竞技场中角色信息
    STC_ARENA_ROLE_DATA getArenaRoleData(){return m_stcArenaRoleData;};
    
    //接收PVE数据，初始化队伍信息}
    void handlerPVEInfo(WorldPacket &packet);
    //接收PVE结算信息}
    void handlerPVEReward(WorldPacket &packet);
    std::vector<STC_FIGHT_REWARD_ITEM> getPveReward(){return m_arrPveReward;};
    void setPveReward(std::vector<STC_FIGHT_REWARD_ITEM> arrItem){m_arrPveReward = arrItem;};
    
    void setWorldLoot(std::vector<STC_ITEM_DROP> arrItem){m_arrWorldLoot.clear(); m_arrWorldLoot = arrItem;};
    std::vector<STC_ITEM_DROP> getWorldLoot(){return m_arrWorldLoot;};
    
    void setPerData(STC_BATTLE_PRE_DATA data){m_stcPerData = data;};
    STC_BATTLE_PRE_DATA getPerData(){return m_stcPerData;};
    
    //获取战斗类型}
    uint8 getFightType(){return m_byFightType;};
    void setFightType(uint8 type){m_byFightType = type;};
    
    //获取当前我方队伍}
    FightTeam *getMyTeam(){return m_myTeam;};
    //获取当前敌方队伍}
    FightTeam *getEnemyTeam(){return m_enemyTeam;};
    
    //根据battleIndex获取fightPet}
    FightPet *getFightPetByBIndex(uint16 wBattleIndex);
    
    //选怪（自动战斗）}
    int RandFactor(std::vector<int>& value);
    
    //获取boss}
    FightPet* getBoss();
    
    //设置选中怪}
    void setSelectedEnemy(uint16 wEnemyIndex);
    //获取选中怪}
    uint16 getSelectedEnemy(){return m_wCurSelectedEnemy;};
    //取当前回合数}
    uint16 getCurRound(){return m_curRound;};
    //取当前波次数}
    uint8 getCurWave(){return m_curWave;};
    //取最大波次数}
    uint8 getAllWaveCnt(){return m_allWaveCnt;};
    //生成预战斗包}
    STC_START_BATTLE_DATA getStartBattleData(uint16 wBattleIndex, uint32 skillId);
    //生成战斗包}
    uint16 getBattleData(STC_START_BATTLE_DATA startData);
    //根据key获取战斗包}
    STC_BATTLE_DATA getBattleDataByKey(uint16 key);
    
    //波次开始(刷状态)}
    void waveStart();
    //波次结束}
    void waveEnd();
    //回合开始}
    void roundStart();
    //回合结束}
    void roundEnd();
    
    //buff结算}
    void buffActive();
    //获取可攻击人的数量}
    uint8 getCanFightPetCnt();
    
    //是否战斗结束}
    bool isGameOver(){return m_curWave > m_allWaveCnt || m_myTeam->getLivePetCount() == 0;};
    
    //当前是否主攻}
    bool isMyAttack(){return m_bIsMyAtt;};
    
    //设置用于计算Spark的战斗包帧组}
    void setWaitFrame(std::vector<STC_WAIT_BATTLE_DATA> arrWaitBattleData)
    {
        m_arrWaitBattleData = arrWaitBattleData;
    };
    //真正攻击前，结算伤害}
    void doBattle(uint16 key);
    
    //根据参数随即命中与否}
    bool RandEither(uint16 value, uint16 valueMax);
    
    //取伤害浮动系数}
    STC_BATTLE_DAMAGE_FLOAT getDamFloat(){return m_stcDamFloat;};
    
    //取一场战斗的最大回合数}
    uint8 getAllRound(){return m_byAllRound;};
    
    //取战斗星级}
    uint8 getFightStar(){return m_fightStar;};
    void setFightStar(uint8 star){m_fightStar = star;};
    
    //秘境商人开启
    bool getIsMJShopOpen(){return m_bIsMJShopOpen;};
    void setIsMJShopOpen(bool isOpen){m_bIsMJShopOpen = isOpen;};
#pragma mark Drop Item
    //eff心珠掉落}
    void addEffHeart(uint32 heartCnt){m_dwEffHeartCnt += heartCnt;};
    //team心珠掉落}
    void addTeamHeart(uint32 heartCnt){m_dwTeamHeartCnt += heartCnt;};
    //获取此次攻击的物品掉落（不包括心珠）}
    std::vector<STC_ITEM_DROP> getDropItemByDamage(int damage, FightPet *enemy);
    //获取当前回合掉落物品（包括心珠）}
    std::vector<STC_ITEM_DROP> getCurRoundDropItems(){return m_arrCurRoundDropItems;};
    
    //设置当前回合掉落}
    void setCurRoundDropItem(bool isWaveEnd);
    //设置宝箱掉落
    void setBoxDrop();
    //招财猫副本的伤害和金钱}
    void setCoinCatDamage(uint32 damage){m_dwCoinCatDamage = damage;};
    void setCoinCatMoney(uint32 money){m_dwCoinCatMoney = money;};
    uint32 getCoinCatDamage(){return m_dwCoinCatDamage;};
    uint32 getCoinCatMoney(){return m_dwCoinCatMoney;};
    //清除所有数据}
    void uninit();
    
    //敌方队伍列表}
    std::vector<FightTeam*> getAllEnemyTeam(){return  m_arrEnemyTeams;};
private:
    //验证Spark}
    void checkSpark(uint16 key);
   
    //我方攻击时 选怪}
    std::vector<uint16> chooseMy(uint16 wBattleIndex, uint32 skillId);
    //敌方攻击时 选怪}
    std::vector<uint16> chooseEnemy(uint16 wBattleIndex, uint32 skillId);
    //纯随即选择}
    std::vector<uint16> chooseInRandom(uint16 wNoChoose, FightTeam *team, uint8 count);
    //顺序选择}
    std::vector<uint16> chooseInOrder(uint16 wNoChoose, FightTeam *team, uint8 count);
    /*
     E_ATTACK_SCOPE_BF_SINLGE		= 1, //前排单体}
     E_ATTACK_SCOPE_AF_SINGLE		= 2, //后排单体}
     E_ATTACK_SCOPE_BF_ALL			= 3, //前排全体}
     E_ATTACK_SCOPE_AF_ALL			= 4, //后排全体}
     E_ATTACK_SCOPE_ALL				= 5, //全体}
     E_ATTACK_SCOPE_RAND_TWO		= 6, //随机2目标}
     E_ATTACK_SCOPE_RAND_THREE		= 7, //随机3目标}
     
     E_ATTACK_SCOPE_ATK_MAX			= 8, //敌方攻击最高的}
     E_ATTACK_SCOPE_HP_MIN			= 9, //敌方血量最少的}
     E_ATTACK_SCOPE_DEF_MIN			= 10, //敌方防御最低的}
     E_ATTACK_SCOPE_NATURE_SELECT	= 11, //选择固定属性的}
     E_ATTACK_SCOPE_COLUMN			= 12, // 当前纵列}
     
     E_ATTACK_SCOPE_ATK_MAX_2		= 13, // 敌方攻击最高的}
     E_ATTACK_SCOPE_HP_MIN_2		= 14, // 敌方血量最少的}
     E_ATTACK_SCOPE_DEF_MIN_2		= 15, // 敌方防御最低的}
     E_ATTACK_SCOPE_NATURE_SELECT_2	= 16, // 选择固定属性的}
     */
    //前排单体}
    std::vector<uint16> chooseByTypeBFSingle(uint16 battleId, FightTeam* team);
    //后排单体}
    std::vector<uint16> chooseByTypeAFSingle(uint16 battleId, FightTeam* team);
    //前排全体}
    std::vector<uint16> chooseByTypeBFAll(uint16 battleId, FightTeam* team);
    //后排全体}
    std::vector<uint16> chooseByTypeAFAll(uint16 battleId, FightTeam* team);
    //全体}
    std::vector<uint16> chooseByTypeAll(uint16 battleId, FightTeam* team);
    //随机2目标}
    std::vector<uint16> chooseByTypeRandTow(uint16 battleId, FightTeam* team);
    //随机3目标}
    std::vector<uint16> chooseByTypeRandThree(uint16 battleId, FightTeam* team);
    //敌方攻击最高的}
    std::vector<uint16> chooseByTypeAtkMax(uint16 battleId, FightTeam* team);
    //敌方血量最少的}
    std::vector<uint16> chooseByTypeHpMin(uint16 battleId, FightTeam* team);
    //敌方防御最低的}
    std::vector<uint16> chooseByTypeDefMin(uint16 battleId, FightTeam* team);
    //选择固定属性的}
    std::vector<uint16> chooseByTypeNautre(uint16 battleId, FightTeam* team);
    // 当前纵列}
    std::vector<uint16> chooseByTypeColumn(uint16 battleId, FightTeam* team);
    //敌方攻击最高的(2个目标)}
    std::vector<uint16> chooseByTypeAtkMax_2(uint16 battleId, FightTeam* team);
    //敌方血量最少的(2个目标)}
    std::vector<uint16> chooseByTypeHpMin_2(uint16 battleId, FightTeam* team);
    //敌方防御最低的(2个目标)}
    std::vector<uint16> chooseByTypeDefMin_2(uint16 battleId, FightTeam* team);
    //选择固定属性的(2个目标)}
    std::vector<uint16> chooseByTypeNautre_2(uint16 battleId, FightTeam* team);
    
    std::vector<uint16> chooseFromVect(std::vector<uint16> arrId, uint8 count);
    
    //拆分物品}
    std::vector<STC_ITEM_DROP> partItem(STC_ITEM_DROP item);
    
    
    
public:
    //设置当前波次掉落}
    void setCurWaveDropItem();

private:
    //我方队伍}
    FightTeam *m_myTeam;
    //敌方队伍列表}
    std::vector<FightTeam*> m_arrEnemyTeams;
    //当前敌方队伍}
    FightTeam *m_enemyTeam;
    //当前波次}
    uint8 m_curWave;
    //总波次}
    uint8 m_allWaveCnt;
    //当前选中怪}
    uint16 m_wCurSelectedEnemy;
    //当前回合}
    uint16 m_curRound;
    //是否主攻}
    bool m_bIsMyAtt;
    //当前战斗包列表}
    MAP_BATTLE_DATAS m_mapBattleData;
    //当前回合掉落物品(仅钱和魂)}
    std::vector<STC_ITEM_DROP> m_arrCurRoundDropItems;
    //当前波次掉落(仅钱和魂)}
    std::vector<STC_ITEM_DROP> m_arrCurWaveDropItems;
    //全部掉落物品}
    std::vector<STC_ITEM_DROP> m_arrAllDropItems;
    //全部掉落宝箱}
    std::vector<STC_ITEM_DROP> m_arrBoxItems;
    //eff掉落心珠总数}
    uint32 m_dwEffHeartCnt;
    //team掉落心珠总数}
    uint32 m_dwTeamHeartCnt;
    //可攻击人数}
    uint8 m_curAttCnt;
    //用于计算Spark的战斗包帧组}
    std::vector<STC_WAIT_BATTLE_DATA> m_arrWaitBattleData;

    //PVE结算物品}
    std::vector<STC_FIGHT_REWARD_ITEM> m_arrPveReward;
    //天降宝箱奖励
    std::vector<STC_ITEM_DROP> m_arrWorldLoot;
    //秘境商人开启
    bool m_bIsMJShopOpen;
    //战斗星级}
    uint8 m_fightStar;
    //pvp数据}
    WorldPacket m_pvpData;
    
    STC_BATTLE_DAMAGE_FLOAT m_stcDamFloat;
    
    uint8 m_byAllRound;
    
    //结算前角色等级和经验}
    STC_BATTLE_PRE_DATA m_stcPerData;
    
    //战斗类型}
    uint8 m_byFightType;
    
    //招财猫副本的伤害和金钱}
    uint32 m_dwCoinCatDamage;
    uint32 m_dwCoinCatMoney;
    
    uint32 dwCoinValue;
    uint32 dwResValue;
    
    std::vector<uint32> getItemValue(uint8 cnt, uint32 dwAllValue);
    
    STC_ARENA_ROLE_DATA m_stcArenaRoleData;
    
};
#endif /* defined(__HelloWorld__FigthAI__) */
