//
//  EventDataMgr.h
//  HelloWorld
//
//  Created by jun on 14-3-11.
//
//

#ifndef __HelloWorld__EventDataMgr__
#define __HelloWorld__EventDataMgr__

#include <iostream>
#include "Singleton.h"
#include "cocos2d.h"
#include "Defines.h"
#include <map>
#include "WorldPacket.h"

USING_NS_CC;
using namespace std;

enum EVENT_SHOW_TYPE
{
    SHOW_FIRST_RECHARGE = 1,
    SHOW_GROW_PLAN      = 2,
    SHOW_RECOVER_ENERGY = 3,
//    SHOW_MY_STERY_SHOP  = 4,
    
    SHOW_TYPE_MAX = 3,
    
    SHOW_EVENT_ANNOUNCE = 99,
};

enum E_MY_SHOP_TYPE{
    E_MY_SHOP_MYSTERY = 1,
    E_MY_SHOP_MJ = 2,
};

struct STC_EVENT_CHANGEABLE
{
    uint32 dwActiveId;
    std::string strTitle;
    uint16 wIcon;
    STC_EVENT_CHANGEABLE()
    : dwActiveId(0)
    , strTitle("")
    , wIcon(0)
    {
        
    }
    
};

//#define CMD_SC_ACTIVE_DETAIL_INFO			CMD_MAKE_SERVER(0x0141)
/**	 活动具体信息 (2, 领奖类 )
 *		[uint8]  byNoticeType		(2, 领奖类 3，公告面板类)
 //		2, 领奖类
 *		[uint32] dwActiveId			活动Id
 *		[uint32] dwLeftTime			倒计时
 *		[string] strDesc
 *		[uint8]  byBloadBannerType
 *		[uint8]  byRewardBloadType
 *		[uint32] dwCompleteNum   完成数量
 *		[uint8]	 byBannerCnt  条目数量
 *			[uint32] dwRewId
 *			[string] strRewDesc
 *			[uint8]  byStatus
 *			[uint8]  byRewCnt
 *				[uint32] dwUniteId
 *				[uint32] dwUniteCnt
 // 3，公告面板类
 *		[uint8] bySize
 *			[string] strTitle
 *			[uint32] dwLeftTime			倒计时
 *			[string] strDesc
 *			[uint8]  byBloadBannerType
 *			[uint8]  byRewardBloadType
 */


struct STC_CHANGEABLE_CELL_REWARDITEM
{
    uint32 dwUniteId;
    uint32 dwuniteCnt;
};

struct STC_CHANGEABLE_CELL_INFO
{
    uint32 dwRewId;
    std::string strRewDesc;
    uint8  byStatus;
    std::vector<STC_CHANGEABLE_CELL_REWARDITEM> m_vecRewardItems;
    STC_CHANGEABLE_CELL_INFO()
    : dwRewId(0)
    , strRewDesc("")
    , byStatus(0)
    {
        m_vecRewardItems.clear();
    }
};

struct STC_EVENT_CHANGEABLE_INFO
{
    uint32 dwActiveId;
    uint32 dwLeftTime;
    std::string strDesc;
    uint8 byNoticeType;
    uint8 byBloadBannerType;
    uint8 byRewardBloadType;
    uint32 dwCompleteNum;
    std::vector<STC_CHANGEABLE_CELL_INFO> m_vecCells;
    STC_EVENT_CHANGEABLE_INFO()
    : dwActiveId(0)
    , dwLeftTime(0)
    , strDesc("")
    , byNoticeType(0)
    , byBloadBannerType(0)
    , byRewardBloadType(0)
    , dwCompleteNum(0)
    {
        m_vecCells.clear();
    }
};

struct STC_EVENT_ANNOUNCE_INFO{
    std::string titleName;
    std::string titleDes;
    uint32 leftTime;
    std::string fuliName;
    std::string fuliDes;
};

struct STC_STERY_GOODS
{
    uint8 byType; // 1:神秘商店；2:秘境商人
    uint32 dwGoodsId;
    std::string strName;
    uint32 dwBuyContentId;
    uint32 dwBuyCount;
    uint32 dwCostCnt;
    std::string strDescription;
    uint32 dwCostItemId;
    uint32 dwLimitCnt;
    uint32 dwBuyCnt;
    
    STC_STERY_GOODS()
    {
        byType = E_MY_SHOP_MYSTERY;
        dwGoodsId = 0;
        dwBuyContentId = 0;
    };
};

class CEventDataMgr : public Singleton<CEventDataMgr>
{
public:
    CEventDataMgr();
    virtual ~CEventDataMgr();
    
public:
    void SetCurShowEventType(uint32 dwType ) { m_dwCurShowEventType = dwType; };
    uint32 GetCurShowEventType() { return m_dwCurShowEventType; };
    uint32 m_dwCurShowEventType;
    
    void SetEventMainLayer(CCNode* node) { m_pEventMainLayer = node; };
    CCNode* GetEventMainLayer() { return m_pEventMainLayer; };
    CCNode* m_pEventMainLayer;
    
    void SetGrowPlanState(uint32 dwIndex, uint8 byState);
    uint8 GetGrowPlanState(uint32 dwIndex);
    map<uint32, uint8> m_mapPlanState;
    
    void SetGrowPlanBuyState( uint8 state ) { m_byGrowPlanBuyState = state; };
    uint8 GetGrowPlanBuyState() { return m_byGrowPlanBuyState; };
    uint8 m_byGrowPlanBuyState;
    
    void SetFirstRechargeState( uint8 state ) { m_byFirstRechargeState = state; };
    uint8 GetFirstRechargeState() { return m_byFirstRechargeState; };
    uint8 m_byFirstRechargeState;
    
    const std::vector<int>& getEventType();
    void loadEventType();
    
    //活动公告
    void handlerEventAnnounce();
    std::vector<STC_EVENT_ANNOUNCE_INFO> getEventAnnounce(){return m_vecEventAnnounce;};
    
    //不定期活动
    void handlerEventsChangeable(WorldPacket& packet);
    std::vector<STC_EVENT_CHANGEABLE> getEventsChangeable() {return m_vecEventsChangeable;};
    STC_EVENT_CHANGEABLE* getEventChangeableByActiveId(uint32 dwActiveId);
    
    //不定期活动内容
    void handlerEventsChangeableInfo(WorldPacket& packet);
    STC_EVENT_CHANGEABLE_INFO* getEventChangeableInfoByActiveId(uint32 dwActiveId);
    
    void handlerActiveGetRewardResult(WorldPacket& packet);
    
    
    void handlerMySteryGoods(WorldPacket& packet);
    void handlerMySteryUpdate(WorldPacket& packet);
    std::vector<STC_STERY_GOODS> getMySteryGoods(){return m_vecMySteryGoods;};
    void setMySteryLeftTime(uint32 leftTime){m_dwMySteryLeftTime = leftTime;};
    uint32 getMySteryLeftTime(){return m_dwMySteryLeftTime;};
    
    void handlerMJShopGoods(WorldPacket& packet);
    void handlerMJShopUpdate(WorldPacket& packet);
    std::vector<STC_STERY_GOODS> getMJShopGoods(){return m_vecMJShopGoods;};
    void setMJShopLeftTime(uint32 leftTime){m_dwMJShopLeftTime = leftTime;};
    uint32 getMJShopLeftTime(){return m_dwMJShopLeftTime;};
    
    void setMyShopType(uint8 byType){m_byMyShopType = byType;};
    uint8 getMyShopType(){return m_byMyShopType;};
private:
    std::vector<int> m_vecEventType;
    std::vector<STC_EVENT_ANNOUNCE_INFO> m_vecEventAnnounce;
    std::vector<STC_EVENT_CHANGEABLE> m_vecEventsChangeable;
    std::map<uint32, STC_EVENT_CHANGEABLE_INFO> m_mapEvnetChangeableInfo;
    
    std::vector<STC_STERY_GOODS> m_vecMySteryGoods; //神秘商店商品
    std::vector<STC_STERY_GOODS> m_vecMJShopGoods;  //秘境商店商品
    uint32 m_dwMySteryLeftTime;
    uint32 m_dwMJShopLeftTime;
    uint8 m_byMyShopType;     //1：神秘商店，2：秘境商人
    
};

#define g_EventData CEventDataMgr::Get()

#endif /* defined(__HelloWorld__EventDataMgr__) */
