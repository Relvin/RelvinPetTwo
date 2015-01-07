//
//  WorldBossDataMgr.cpp
//  MyGame
//
//  Created by long on 14/11/13.
//
//

#include "WorldBossDataMgr.h"
#include "ConfigGet.h"

//接收boss信息
/**  世界BOSS面板信息
 uint16 wError
 uint16 wBossIndex		Boss 宠物原型
 uint32 dwMaxHP
 uint32 dwCurHP
 uint32 dwLeftTime		倒计时
 uint32 dwRank			排名
 uint32 dwKillNum			击杀量
 uint32 dwBattleCnt		攻击次数
 uint32 dwCDTime			CD时间
 uint32 dwBlessEffect		鼓励效果
 uint32 dwBlessCDTime		金币CD时间
 */
void WorldBossDataMgr::handlerBossInfo(WorldPacket& packet)
{
    uint16 wBossIndex;//		Boss 宠物原型
    uint16 wBossLv;
    uint32 dwMaxHP;
    uint32 dwCurHP;
    uint32 dwLeftTime;//		倒计时
    uint32 dwRank;	  //		排名
    uint32 dwKillNum;	//		击杀量
    uint32 dwBattleCnt;//		攻击次数
    uint32 dwCDTime	;	//	CD时间
    uint32 dwBlessEffect;//		鼓励效果
    uint32 dwBlessCDTime;//		金币CD时间

    packet >> wBossIndex;//		Boss 宠物原型
    packet >> wBossLv;
    packet >> dwMaxHP;
    packet >> dwCurHP;
    packet >> dwLeftTime;//		倒计时
    packet >> dwRank;	  //		排名
    packet >> dwKillNum;	//		击杀量
    packet >> dwBattleCnt;//		攻击次数
    packet >> dwCDTime	;	//	CD时间
    packet >> dwBlessEffect;//		鼓励效果
    packet >> dwBlessCDTime;//		金币CD时间
    
//    m_curBossInfo = *new STC_WORLD_BOSS_INFO();
    
    m_curBossInfo.wBossIndex =  wBossIndex;//		Boss 宠物原型
    m_curBossInfo.wBossLv = wBossLv;
    m_curBossInfo.dwBossMaxHp =  dwMaxHP;
    m_curBossInfo.dwBossCurHp =  dwCurHP;
    m_curBossInfo.dwLeftTime =  dwLeftTime;//		倒计时
    m_curBossInfo.dwCurRank =  dwRank;	  //		排名
    m_curBossInfo.dwAllDamage =  dwKillNum;	//		击杀量
    m_curBossInfo.dwBattleCnt =  dwBattleCnt;//		攻击次数
    m_curBossInfo.dwCdTime =  dwCDTime	;	//	CD时间
    m_curBossInfo.dwBuffAdd =  dwBlessEffect;//		鼓励效果
    m_curBossInfo.dwBlessCDTime =  dwBlessCDTime;//		金币CD时间
    
    WorldBossInfoConfig::STC_CONFIG_WORLD_BOSS_INFO* infoCfg = GET_CONFIG_STC(WorldBossInfoConfig, wBossIndex);
    if (infoCfg) {
        m_curBossInfo.dwBuffDollorAddMax = infoCfg->dwBlessDollorAddMax;
        m_curBossInfo.dwBuffMoneyAddMax = infoCfg->dwBlessMoneyAddMax;
        m_curBossInfo.dwCdMaxTime = infoCfg->dwAttCDTime;
        m_curBossInfo.dwCostDollor = infoCfg->dwBlessDollor;
        m_curBossInfo.dwCostMoney = infoCfg->dwBlessMoney;
        m_curBossInfo.dwFuhuoCost = infoCfg->dwAttFuhuoDollor;
    }
}

void WorldBossDataMgr::clearBossInfo()
{
    m_curBossInfo.wBossIndex = 0;
}

/**  世界BOSS上期排行榜
 uint16 wSize
 *			[uint32 dwRoleId
 *			[uint32 dwKillNum
 *			[string strName
 */
//接收上届boss排行榜
void WorldBossDataMgr::handlerLastRank(WorldPacket& packet)
{
    uint16 wSize;
    packet >> wSize;
    
    m_arrLastRank.clear();
    for (int i = 0; i < wSize; i++) {
        uint32 dwRoleId;
        uint32 dwKillNum;
        std::string strName;
        packet >> dwRoleId;
        packet >> dwKillNum;
        packet >> strName;
        
        STC_BOSS_RANK_INFO rankInfo;
        rankInfo.dwRoleId = dwRoleId;
        rankInfo.dwAllDamage = dwKillNum;
        rankInfo.strName = strName;
        
        m_arrLastRank.push_back(rankInfo);
    }
    
}