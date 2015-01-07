//
//  ArenaDataMgr.h
//  HelloWorld
//
//  Created by jun on 13-11-13.
//
//

#ifndef __HelloWorld__CArenaDataMgr__
#define __HelloWorld__CArenaDataMgr__

#include "cocos2d.h"
#include "Defines.h"
#include "Singleton.h"
#include <vector>

using namespace std;
USING_NS_CC;

enum {
    E_ARENA_RANK = 1,
    E_ARENA_NOMALE = 2,
    };

//竞技场主界面的玩家信息}
struct ARENA_PLAYER_INFO
{
    uint32 dwUserId;    //玩家ID}
    uint32 dwRank;      //排行榜上的位置}
    uint8 byGroupId;    //组别，显示字符串取配置表rankreward.csv中401字段}
    uint32 dwDoubleWin; //连胜次数}
    uint32 dwWinCnt;    //总胜利次数}
    uint32 dwLostCnt;   //总失败次数}
    uint32 dwLastRank;  //上次排行榜上的排名}
    uint8 byIsReward;   //奖励，空着代表无奖励}
    uint32 dwLeftTime;  //奖励剩余时间}
    uint32 dwMaxRank;   //历史最好成绩}
    
    ARENA_PLAYER_INFO()
    {
        dwUserId = 0;
        dwRank = 0;
        byGroupId = 0;
        dwDoubleWin = 0;
        dwWinCnt = 0;
        dwLostCnt = 0;
        dwLastRank = 0;
        byIsReward = 0;
        dwLeftTime = 0;
        dwMaxRank = 0;
    };
};

//排行榜上每个玩家的信息}
//struct ARENA_RANK_LIST_INFO
//{
//    uint32 dwUserId;        //玩家ID}
//    uint16 wPhoto;          //玩家宠物的Index，用于显示icon}
//    string strName;         //玩家名字}
//    uint32 dwReputation;    //声望}
//    uint32 dwRank;          //排行榜上的位置}
//    uint32 dwWinCnt;        //胜利次数}
//    uint32 dwLostCnt;       //失败次数}
//    
//    ARENA_RANK_LIST_INFO()
//    {
//        dwUserId = 0;
//        wPhoto = 0;
//        strName = "";
//        dwReputation = 0;
//        dwRank = 0;
//        dwWinCnt = 0;
//        dwLostCnt = 0;
//    };
//};

/**  发送 挑战列表
 uint8 bySize
 uint32	dwUserId
 string	strName
 uint8	byGroupId
 uint32	dwRank
 uint32  dwFightScore	[new add]
 string  strBattleTeam   [new Add] ( xx|xx1|xx2|xx3|xx4|xx5|xx6)
 
 uint16	wPhoto			[delete]
 uint32	dwWinCnt		[delete]
 uint32	dwLostCnt		[delete]
 
 */


struct ARENA_OPP_PET_INFO
{
    uint8 byEvolv;
    uint8 byPetLv;
    uint32 dwPetIndex;
    ARENA_OPP_PET_INFO()
    {
        byEvolv = 0;
        byPetLv = 0;
        dwPetIndex = 0;
    }
};

//挑战列表里每个玩家的信息}
struct ARENA_BATTLE_LIST_INFO
{
    uint32 dwUserId;        //玩家ID}
    uint16	wRoleLv;
    string strName;         //玩家名字}
    uint32 dwGetMoney;      //获得金钱}
    uint32 dwRank;          //在排行榜上的位置}
    uint8 byGroupId;         //当前组别}
    int nCaptainPetPos;
    uint32  dwFightScore;
    std::vector<ARENA_OPP_PET_INFO> m_VecTeam;
    
    ARENA_BATTLE_LIST_INFO()
    {
        dwUserId = 0;
        wRoleLv = 0;
        strName = "";
        dwGetMoney = 0;
        dwRank = 0;
        byGroupId = 0;
        nCaptainPetPos = 0;
        m_VecTeam.clear();
    };
};

//结算画面个人信息}
struct RESULT_INFO_PERSONAL
{
    uint32 dwUserId;
    uint16 wLeaderId;
    string strName;
    uint32 dwWinCnt;
    uint32 dwLoseCnt;
    uint32 dwRank;
    uint8 byGroupId;
    
    RESULT_INFO_PERSONAL()
    {
        dwUserId = 0;
        wLeaderId = 0;
        strName = "";
        dwWinCnt = 0;
        dwLoseCnt = 0;
        dwRank = 0;
        byGroupId = 0;
    };
};

//结算画面中的物品信息}
struct RESULT_INFO_ALL
{
    RESULT_INFO_PERSONAL infoPersonal[2];
    
    uint8 byIsWin;
    uint32 dwCoin;
    uint32 dwReputation;
    uint8 bySize;
    uint32 dwItemId[3];
    uint32 dwItemCnt[3];
    uint32 dwMaxRankDollar;
    
    RESULT_INFO_ALL()
    {
        byIsWin = 0;
        dwCoin = 0;
        dwReputation = 0;
        bySize = 0;
        for (int i = 0; i < 3; i++)
        {
            dwItemId[i] = 0;
            dwItemCnt[i] = 0;
        }
        dwMaxRankDollar = 0;

    };
};

struct ARENA_SHOP_INFO
{
    uint32 dwGoodsId;
    string strName;
    uint32 dwBuyContentId;
    uint32 dwBuyCount;
    uint32 dwCostReputition;
    string strDescription;
    uint32 dwIconId;
    uint32 dwLimitCnt;
    uint32 dwExchangeCnt;
    
    ARENA_SHOP_INFO()
    {
        dwGoodsId = 0;
        strName = "";
        dwBuyContentId = 0;
        dwBuyCount = 0;
        dwCostReputition = 0;
        strDescription = "";
        dwIconId = 0;
        dwLimitCnt = 0;
        dwExchangeCnt = 0;
    }
};


typedef vector<ARENA_BATTLE_LIST_INFO> VEC_RANK_LIST;
typedef vector<ARENA_BATTLE_LIST_INFO> VEC_BATTLE_LIST;
typedef vector<string> VEC_STR;
typedef vector<ARENA_SHOP_INFO> VEC_SHOP_LIST;

class CArenaDataMgr : public Singleton<CArenaDataMgr>
{
public:
    CArenaDataMgr(){
        m_buyUseCnt = 0;
        m_myPreRank = 0;
    };
    
    void SetPlayerInfo(const ARENA_PLAYER_INFO &info);//设置面板上的人物信息}
    ARENA_PLAYER_INFO GetPlayerInfo();
    void ClearPlayerInfo();
    
    void AddNewRecord(const string &strMsg);
    VEC_STR GetRecords();
    void ClearRedords();
    
    //排行榜}
    void AddNewRankListInfo(const ARENA_BATTLE_LIST_INFO &info);
    VEC_RANK_LIST GetRankList();
    void ClearRankList();
    
    //挑战榜}
    void AddNewBattleList(const ARENA_BATTLE_LIST_INFO &info);
    VEC_BATTLE_LIST GetBattleList();
    void ClearBattleList();
    
    void ResetResultInfo();
    void SetResultInfo(const RESULT_INFO_ALL &info);
    RESULT_INFO_ALL GetResultInfo();
    
    
    void setBuyUseCnt(uint8 cnt ){m_buyUseCnt = cnt;};
    uint8 getBuyUseCnt( ){return m_buyUseCnt;};
    
    void setOppTeamInfoByString(ARENA_BATTLE_LIST_INFO &listInfo,const char * TeamInfo);
    
    void setMyPreRank(uint32 rank){m_myPreRank = rank;};
    uint32 getMyPreRank(){return m_myPreRank;};
    
private:
    ARENA_PLAYER_INFO m_PlayerInfo; //面板上的人物信息}
    
    VEC_STR m_vecRecords;    //挑战历史记录信息}
    VEC_RANK_LIST m_vecRankListInfo;//排行榜列表}
    VEC_BATTLE_LIST m_vecBattleListInfo;//挑战列表}
    
    RESULT_INFO_ALL m_ResultInfoAll;
    
    uint8 m_buyUseCnt;
    
    uint32 m_myPreRank;
public:
    
    void setStartClock();
    double getLostTime();//单位：秒}
    double m_dwStartClock;
    
    //竞技商店列表}
    void AddShopList(ARENA_SHOP_INFO &info);
    void UpdateShopList(ARENA_SHOP_INFO &info);
    void ClearShopList();
    VEC_SHOP_LIST GetShopList();
    VEC_SHOP_LIST m_vecArenaShopList;
    
    void SaveArenaMyInfoLayerPt(CCNode* node) { m_pArenaMyInfoLayerPt = node; };
    CCNode* GetArenaMyInfoLayerPt() { return m_pArenaMyInfoLayerPt; };
    CCNode* m_pArenaMyInfoLayerPt;
    
    void SetCanRequestReward(bool isCan ) { m_isCanRequestReward = isCan; };
    bool isCanRequestReward() { return m_isCanRequestReward; };
    bool m_isCanRequestReward;
};
#define g_ArenaData CArenaDataMgr::Get()

#endif /* defined(__HelloWorld__CArenaDataMgr__) */
