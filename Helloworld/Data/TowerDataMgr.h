//
//  TowerDataMgr.h
//  MyGame
//
//  Created by jun on 14-7-10.
//
//

#ifndef __MyGame__TowerDataMgr__
#define __MyGame__TowerDataMgr__

#include "Singleton.h"
#include "Defines.h"
#include <map>
#include <vector>
#include <math.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <time.h>
#endif

using namespace std;

//爬塔主界面信息}
struct TOWER_INFO
{
    uint32  dwCurFloor;      //当前所处层数}
    uint8   byHasResetCnt;   //已经重置次数}
    uint8   byMaxResetCnt;   //最大重置次数}
    uint8   byLeftFightCnt;   //剩余战斗次数}
    uint32  dwLeftTime;  //扫荡倒计时 [0 未扫荡状态]}
    
    TOWER_INFO()
    {
        dwCurFloor = 0;
        byHasResetCnt = 0;
        byMaxResetCnt = 1;
        byLeftFightCnt = 0;
        dwLeftTime = 0;
        
    }
};

//爬塔排行榜玩家自己的信息}
struct TOWER_RANK
{
    uint32 dwCurFloor;  //当前层数}
    uint32 dwMaxFloor;  //达到过最大层数}
    uint32 dwCurRank;   //当前所处层数}
    
    TOWER_RANK()
    {
        dwCurFloor = 0;
        dwMaxFloor = 0;
        dwCurRank = 0;
    }
};

//爬塔排行榜上每个角色的详情}
struct TOWER_RANK_INFO
{
    uint32 dwRoleId;    //角色ID}
    uint32 dwMaxFloor;  //达到过的最大层数}
    string strName;     //角色名字}
    uint16 wLeader;     //角色宠物队长ID}
    
    TOWER_RANK_INFO()
    {
        dwRoleId = 0;
        dwMaxFloor = 0;
        strName = "";
        wLeader = 0;
    }
};


class CTowerDataMgr : public Singleton<CTowerDataMgr>
{
public:
    CTowerDataMgr(){
        m_isEnterTower = false;
    };
    //主界面信息}
    void SetTowerInfo( const TOWER_INFO &info);
    const TOWER_INFO GetTowerInfo() { return m_TowerInfo; };
    TOWER_INFO m_TowerInfo;
    
    //玩家自己的排行榜信息}
    void SetTowerRank( const TOWER_RANK &rank);
    const TOWER_RANK GetTowerRank(){ return m_TowerRank; };
    TOWER_RANK m_TowerRank;
    
    //排行榜上每个玩家的信息}
    void AddTowerRankList(const TOWER_RANK_INFO &info);
    const TOWER_RANK_INFO GetTowerRankListInfo(uint32 dwRoleID);
    void ClearTowerRankList();
    vector<TOWER_RANK_INFO> GetTowerRankList() { return m_vecRankInfoList; };
    vector<TOWER_RANK_INFO> m_vecRankInfoList;
    
    string GetDescByIndex(uint16 wIndex);
    string GetPetBodyPicName(uint16 wIndex);
    
    //是否是从爬塔入口进入战斗}
    void SetEnterTowerState(bool isEnter) { m_isEnterTower = isEnter; };
    bool isEnterTower() { return m_isEnterTower; };
    bool m_isEnterTower;
    
    //当前挑战层数}
    void SetCurBattleFloor(uint32 dwFloor) { m_dwCurBattleFloor = dwFloor; };
    uint32 GetCurBattleFloor() { return m_dwCurBattleFloor; };
    uint32 m_dwCurBattleFloor;
    
    void SetStartClock() { m_dwStartClock = clock(); };
    double GetLostTime() { return floor((clock() - m_dwStartClock) / CLOCKS_PER_SEC); };//单位：秒}
    double m_dwStartClock;  //记录扫荡倒计时的开始时间}

};

#define g_TowerDataMgr CTowerDataMgr::Get()

#endif /* defined(__MyGame__TowerDataMgr__) */
