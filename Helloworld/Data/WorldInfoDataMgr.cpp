//
//  WorldInfoDataMgr.cpp
//  MyGame
//
//  Created by Relvin on 14/11/4.
//
//

#include "WorldInfoDataMgr.h"

WorldInfoDataMgr::WorldInfoDataMgr()
: m_byWeather(0)
, m_dwSweepCDDollar(0)
, m_byWorldBossOpen(0)
, m_byMJShopOpen(0)
{
    
}

WorldInfoDataMgr::~WorldInfoDataMgr()
{
    
}

//uint8 WorldInfoDataMgr::GetWeatherStatus()
//{
//    return m_byWeather;
//}
//
//uint32 WorldInfoDataMgr::GetSweepCDDollar()
//{
//    return m_dwSweepCDDollar;
//}
//
//uint8 WorldInfoDataMgr::GetIsWorldBossOpen()
//{
//    return m_byWorldBossOpen;
//}

#pragma mark - Receive Function -
void WorldInfoDataMgr::handlerWorldInfoUpdate(WorldPacket &packet)
{
    packet >> m_byWeather >> m_dwSweepCDDollar >> m_byWorldBossOpen >> m_wAreanJumpTime;
    packet >> m_byMJShopOpen;
}


