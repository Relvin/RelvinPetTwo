//
//  CArenaDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 13-11-13.
//
//

#include "ArenaDataMgr.h"
#include <math.h>

void CArenaDataMgr::SetPlayerInfo(const ARENA_PLAYER_INFO &info)
{
    m_PlayerInfo.dwUserId = info.dwUserId;
    m_PlayerInfo.dwRank = info.dwRank;
    m_PlayerInfo.byGroupId = info.byGroupId;
    m_PlayerInfo.dwDoubleWin = info.dwDoubleWin;
    m_PlayerInfo.dwWinCnt = info.dwWinCnt;
    m_PlayerInfo.dwLostCnt = info.dwLostCnt;
    m_PlayerInfo.dwLastRank = info.dwLastRank;
    m_PlayerInfo.byIsReward = info.byIsReward;
    m_PlayerInfo.dwLeftTime = info.dwLeftTime;
    m_PlayerInfo.dwMaxRank = info.dwMaxRank;
}

ARENA_PLAYER_INFO CArenaDataMgr:: GetPlayerInfo()
{
    return m_PlayerInfo;
}

void CArenaDataMgr::ClearPlayerInfo()
{
    m_PlayerInfo.dwUserId = 0;
    m_PlayerInfo.dwRank = 0;
    m_PlayerInfo.byGroupId = 0;
    m_PlayerInfo.dwDoubleWin = 0;
    m_PlayerInfo.dwWinCnt = 0;
    m_PlayerInfo.dwLostCnt = 0;
    m_PlayerInfo.dwLastRank = 0;
    m_PlayerInfo.byIsReward = 0;
    m_PlayerInfo.dwLeftTime = 0;
}

void CArenaDataMgr::AddNewRecord(const string &strMsg)
{
    //该容器只存放6条信息，大于6条就删掉第一条}
    if (m_vecRecords.size() >= 3)//改为3条}
    {
        m_vecRecords.erase(m_vecRecords.begin());
    }
    m_vecRecords.push_back(strMsg);
}

VEC_STR CArenaDataMgr::GetRecords()
{
    return m_vecRecords;
}

void CArenaDataMgr::ClearRedords()
{
    m_vecRecords.clear();
}

void CArenaDataMgr::AddNewRankListInfo(const ARENA_BATTLE_LIST_INFO &info)
{
    m_vecRankListInfo.push_back(info);
}

VEC_RANK_LIST CArenaDataMgr::GetRankList()
{
    return m_vecRankListInfo;
}

void CArenaDataMgr::ClearRankList()
{
    m_vecRankListInfo.clear();
}

void CArenaDataMgr::AddNewBattleList(const ARENA_BATTLE_LIST_INFO &info)
{
    m_vecBattleListInfo.push_back(info);
}

VEC_BATTLE_LIST CArenaDataMgr::GetBattleList()
{
    return m_vecBattleListInfo;
}

void CArenaDataMgr::ClearBattleList()
{
    m_vecBattleListInfo.clear();
}

void CArenaDataMgr::setStartClock()
{
    m_dwStartClock = clock();
}

double CArenaDataMgr::getLostTime()
{
    return floor((clock() - m_dwStartClock) / CLOCKS_PER_SEC);
}

void CArenaDataMgr::ResetResultInfo()
{
    for (int i = 0; i < 2; i++)
    {
        m_ResultInfoAll.infoPersonal[i].dwUserId = 0;
        m_ResultInfoAll.infoPersonal[i].wLeaderId = 0;
        m_ResultInfoAll.infoPersonal[i].strName = "";
        m_ResultInfoAll.infoPersonal[i].dwWinCnt = 0;
        m_ResultInfoAll.infoPersonal[i].dwLoseCnt = 0;
        m_ResultInfoAll.infoPersonal[i].dwRank = 0;
        m_ResultInfoAll.infoPersonal[i].byGroupId = 0;
    }
    m_ResultInfoAll.byIsWin = 0;
    m_ResultInfoAll.dwCoin = 0;
    m_ResultInfoAll.dwReputation = 0;
    
    m_ResultInfoAll.bySize = 0;
    for (int i = 0; i < 3; i++)
    {
        m_ResultInfoAll.dwItemId[i] = 0;
        m_ResultInfoAll.dwItemCnt[i] = 0;
    }
}

void CArenaDataMgr::SetResultInfo(const RESULT_INFO_ALL &info)
{
    for (int i = 0; i < 2; i++)
    {
        m_ResultInfoAll.infoPersonal[i].dwUserId = info.infoPersonal[i].dwUserId;
        m_ResultInfoAll.infoPersonal[i].wLeaderId = info.infoPersonal[i].wLeaderId;
        m_ResultInfoAll.infoPersonal[i].strName = info.infoPersonal[i].strName;
        m_ResultInfoAll.infoPersonal[i].dwWinCnt = info.infoPersonal[i].dwWinCnt;
        m_ResultInfoAll.infoPersonal[i].dwLoseCnt = info.infoPersonal[i].dwLoseCnt;
        m_ResultInfoAll.infoPersonal[i].dwRank = info.infoPersonal[i].dwRank;
        m_ResultInfoAll.infoPersonal[i].byGroupId = info.infoPersonal[i].byGroupId;
    }
    m_ResultInfoAll.byIsWin = info.byIsWin;
    m_ResultInfoAll.dwCoin = info.dwCoin;
    m_ResultInfoAll.dwReputation = info.dwReputation;
    
    m_ResultInfoAll.bySize = info.bySize;
    for (int i = 0; i < info.bySize; i++)
    {
        m_ResultInfoAll.dwItemId[i] = info.dwItemId[i];
        m_ResultInfoAll.dwItemCnt[i] = info.dwItemCnt[i];
    }
    m_ResultInfoAll.dwMaxRankDollar = info.dwMaxRankDollar;
}

RESULT_INFO_ALL CArenaDataMgr::GetResultInfo()
{
    return m_ResultInfoAll;
}

void CArenaDataMgr::AddShopList(ARENA_SHOP_INFO &info)
{
    VEC_SHOP_LIST::iterator iter;
    for (iter = m_vecArenaShopList.begin(); iter != m_vecArenaShopList.end(); iter++)
    {
        if (iter->dwGoodsId == info.dwGoodsId)
        {
            return;
        }
    }
    m_vecArenaShopList.push_back(info);
}

void CArenaDataMgr::UpdateShopList(ARENA_SHOP_INFO &info)
{
    VEC_SHOP_LIST::iterator iter;
    for (iter = m_vecArenaShopList.begin(); iter != m_vecArenaShopList.end(); iter++)
    {
        if (iter->dwGoodsId == info.dwGoodsId)
        {
            iter->dwExchangeCnt = info.dwExchangeCnt;
        }
    }
}

void CArenaDataMgr::ClearShopList()
{
    m_vecArenaShopList.clear();
}

VEC_SHOP_LIST CArenaDataMgr::GetShopList()
{
    return m_vecArenaShopList;
}

void CArenaDataMgr::setOppTeamInfoByString(ARENA_BATTLE_LIST_INFO &listInfo,const char * TeamInfo)
{
    CCArray* pArrTeamInfo = ccs(TeamInfo)->componentsSeparatedByString("|");
    listInfo.m_VecTeam.clear();
    CCString *pEachInfo = NULL;
    ARENA_OPP_PET_INFO stcTeamInfo;
    
    for (int i = 0; i < pArrTeamInfo->count(); i++) {
        pEachInfo = (CCString *)pArrTeamInfo->objectAtIndex(i);
        if (i == 0) {
            listInfo.nCaptainPetPos = atoi(pEachInfo->getCString());
            continue;
        }
        int teamInfo = atoi(pEachInfo->getCString());
        
        stcTeamInfo.dwPetIndex = teamInfo % 1000;
        teamInfo /= 1000;
        stcTeamInfo.byPetLv = teamInfo % 1000;
        stcTeamInfo.byEvolv = teamInfo / 1000;
        if (stcTeamInfo.dwPetIndex != 0) {
            if (listInfo.nCaptainPetPos == i) {
                listInfo.m_VecTeam.insert(listInfo.m_VecTeam.begin(), stcTeamInfo);
            }
            else
            {
                listInfo.m_VecTeam.push_back(stcTeamInfo);
            }
        }
    }
}

