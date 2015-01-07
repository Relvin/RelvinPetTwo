//
//  TowerDataMgr.cpp
//  MyGame
//
//  Created by jun on 14-7-10.
//
//

#include "TowerDataMgr.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "Role.h"
#include "GameSession.h"

void CTowerDataMgr::SetTowerInfo( const TOWER_INFO &info)
{
    m_TowerInfo.dwCurFloor = info.dwCurFloor;
    m_TowerInfo.byHasResetCnt = info.byHasResetCnt;
    m_TowerInfo.byLeftFightCnt = info.byLeftFightCnt;
    m_TowerInfo.dwLeftTime = info.dwLeftTime;
    VipShowConfig::STC_VIP_SHOW_CONFIG* pVipShowCfg = GET_CONFIG_STC(VipShowConfig, CGameSession::GetRole()->GetbyVipLv());
    if (pVipShowCfg) {
        m_TowerInfo.byMaxResetCnt = pVipShowCfg->wTowerResetMax + 1;
    }
}

//设置玩家自己的排行榜信息}
void CTowerDataMgr::SetTowerRank( const TOWER_RANK &rank)
{
    m_TowerRank.dwCurFloor = rank.dwCurFloor;
    m_TowerRank.dwMaxFloor = rank.dwMaxFloor;
    m_TowerRank.dwCurRank = rank.dwCurRank;
}

//添加排行榜上每个玩家的信息}
void CTowerDataMgr::AddTowerRankList(const TOWER_RANK_INFO &info)
{
    vector<TOWER_RANK_INFO>::iterator iter;
    for ( iter = m_vecRankInfoList.begin(); iter != m_vecRankInfoList.end(); iter++)
    {
        if (iter->dwRoleId == info.dwRoleId)
        {
            return;
        }
    }
    m_vecRankInfoList.push_back(info);
}

const TOWER_RANK_INFO CTowerDataMgr::GetTowerRankListInfo(uint32 dwRoleID)
{
    vector<TOWER_RANK_INFO>::iterator iter;
    for ( iter = m_vecRankInfoList.begin(); iter != m_vecRankInfoList.end(); iter++)
    {
        if (iter->dwRoleId == dwRoleID)
        {
            return *iter;
        }
    }
    return TOWER_RANK_INFO();
}

void CTowerDataMgr::ClearTowerRankList()
{
    m_vecRankInfoList.clear();
}

string CTowerDataMgr::GetDescByIndex(uint16 wIndex)
{
    TowerConfig::STC_TOWER_CONFIG *pConfig = GET_CONFIG_STC(TowerConfig, wIndex);
    if (pConfig)
    {
        return pConfig->strDesc;
    }
	CCLOG("tower csv read describe error");
    return "";
}

string CTowerDataMgr::GetPetBodyPicName(uint16 wIndex)
{
    TowerConfig::STC_TOWER_CONFIG *pConfig = GET_CONFIG_STC(TowerConfig, wIndex);
    if (pConfig)
    {
        return CPetCtrl::Get()->GetPetBodyPicName(pConfig->dwPetIcon);
    }
	CCLog("tower csv read pet concept error");
    return "";
}
