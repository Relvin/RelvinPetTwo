//
//  WorldBossDataMgr.h
//  MyGame
//
//  Created by long on 14/11/13.
//
//

#ifndef __MyGame__WorldBossDataMgr__
#define __MyGame__WorldBossDataMgr__

#include <stdio.h>
#include "Singleton.h"
#include "Defines.h"
#include <vector>
#include "WorldPacket.h"

#define g_WorldBossData WorldBossDataMgr::Get()

struct STC_WORLD_BOSS_INFO
{
    /**  世界BOSS面板信息
     *		[uint16]  wBossIndex
     *		[uint16]  wBossIndex		Boss 宠物原型
     *		[uint32]  dwMaxHP
     *		[uint32]  dwCurHP
     *		[uint32]  dwLeftTime		倒计时
     *		[uint32]  dwRank			排名
     *		[uint32]  dwKillNum			击杀量
     *		[uint32]  dwBattleCnt		攻击次数
     *		[uint32]  dwCDTime			CD时间
     *		[uint32]  dwBlessEffect		鼓励效果
     *		[uint32]  dwBlessCDTime		金币CD时间
     */
    uint16 wBossIndex;
    uint16 wBossLv;
    uint32 dwBossCurHp;
    uint32 dwBossMaxHp;
    uint32 dwLeftTime;          //boss剩余时间
    uint32 dwBattleCnt;         //攻击次数
    uint32 dwBuffAdd;           //祝福后加成
    uint32 dwBuffMoneyAddMax;   //金币祝福上限
    uint32 dwBuffDollorAddMax;  //钻石祝福上限
    uint32 dwCostMoney;         //祝福花费金币
    uint32 dwBlessCDTime;       //金币CD时间
    uint32 dwCostDollor;        //祝福花费钻石
    uint32 dwAllDamage;         //已造成伤害
    uint32 dwCdTime;            //攻击CD时间
    uint32 dwCdMaxTime;         //攻击CD时间总时长(自动攻击循环用)
    uint32 dwCurRank;           //当前我的排名
    uint32 dwFuhuoCost;         //复活花费
    
    
    STC_WORLD_BOSS_INFO(){
        wBossIndex = 0;
    };
    
};

struct STC_BOSS_RANK_INFO
{
    /**  世界BOSS上期排行榜
     *		[uint16]  wSize
     *			[uint32]  dwRoleId
     *			[uint32]  dwKillNum
     *			[string]  strName
     */
    uint32 dwRoleId;        //角色Id
    uint32 dwAllDamage;     //总伤害
    std::string strName;    //玩家名
    
    STC_BOSS_RANK_INFO(){
        dwRoleId = 0;
        dwAllDamage = 0;
        strName = "";
    };
};

class WorldBossDataMgr : public Singleton<WorldBossDataMgr>
{
public:
    //接收boss信息
    void handlerBossInfo(WorldPacket& packet);
    
    //获取当前boss信息
    STC_WORLD_BOSS_INFO getBossInfo(){return m_curBossInfo;};
    
    //接收上届boss排行榜
    void handlerLastRank(WorldPacket& packet);
    std::vector<STC_BOSS_RANK_INFO> getLastRank(){return m_arrLastRank;};
    
    //
    void clearBossInfo();
private:
    STC_WORLD_BOSS_INFO m_curBossInfo;
    
    std::vector<STC_BOSS_RANK_INFO> m_arrLastRank;
};


#endif /* defined(__MyGame__WorldBossDataMgr__) */
