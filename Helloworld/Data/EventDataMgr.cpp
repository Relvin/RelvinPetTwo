//
//  EventDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 14-3-11.
//
//

#include "EventDataMgr.h"
#include "GlobalData.h"
#include "Instruments.h"
#include "GameSession.h"
#include "EnumDefines.h"
#include "FlyTextLayer.h"
#include "CcbEventMySteryShopLayer.h"
#include "PacketDataMgr.h"

CEventDataMgr::CEventDataMgr()
: m_byGrowPlanBuyState(0)
, m_byMyShopType(1)
{
    m_vecEventType.clear();
    m_vecEventAnnounce.clear();
    m_vecEventsChangeable.clear();
    m_mapEvnetChangeableInfo.clear();
}

CEventDataMgr::~CEventDataMgr()
{
    m_vecEventType.clear();
    m_vecEventAnnounce.clear();
    m_vecEventsChangeable.clear();
    m_mapEvnetChangeableInfo.clear();
}

void CEventDataMgr::SetGrowPlanState(uint32 dwIndex, uint8 byState)
{
    map<uint32, uint8>::iterator iter = m_mapPlanState.find(dwIndex);
    if (iter != m_mapPlanState.end())
    {
        iter->second = byState;
    }
    else
    {
        m_mapPlanState.insert(make_pair(dwIndex, byState));
    }
}

uint8 CEventDataMgr::GetGrowPlanState(uint32 dwIndex)
{
    map<uint32, uint8>::iterator iter = m_mapPlanState.find(dwIndex);
    if (iter != m_mapPlanState.end())
    {
        return iter->second;
    }
    return 0;
}

const std::vector<int>& CEventDataMgr::getEventType()
{
    return m_vecEventType;
}

void CEventDataMgr::loadEventType()
{
    m_vecEventType.clear();
    for (int i = 1; i <= SHOW_TYPE_MAX; i++) {
        if (!GlobalData::shared()->getVipSwitch() || i != SHOW_GROW_PLAN) {
            if (m_byFirstRechargeState == 2 && i == SHOW_FIRST_RECHARGE) {
                continue;
            }
            m_vecEventType.push_back(i);
        }
    }
}

//活动公告
void CEventDataMgr::handlerEventAnnounce()
{
    m_vecEventAnnounce.clear();
    
    for (int i = 0; i < 4; i++) {
        STC_EVENT_ANNOUNCE_INFO info;
        info.titleDes = "你瞅啥？？你瞅啥？？你瞅啥？？你瞅啥？？你瞅啥？？你瞅啥？？";
        info.fuliDes = "瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？瞅你咋滴？？？";
        m_vecEventAnnounce.push_back(info);
    }
    
}

void CEventDataMgr::handlerEventsChangeable(WorldPacket &packet)
{
    m_vecEventsChangeable.clear();
    STC_EVENT_CHANGEABLE eventInfo;
    uint8 bySize= 0;
    packet >> bySize;
    
    for (int i = 0; i < bySize; i++) {
        packet >> eventInfo.dwActiveId;
        packet >> eventInfo.strTitle;
        packet >> eventInfo.wIcon;
        m_vecEventsChangeable.push_back(eventInfo);
    }
    CGameSession::NotifyRefeashLayer();
}

STC_EVENT_CHANGEABLE* CEventDataMgr::getEventChangeableByActiveId(uint32 dwActiveId)
{
    for (int i = 0; i < m_vecEventsChangeable.size(); i++) {
        if (dwActiveId == m_vecEventsChangeable[i].dwActiveId) {
            return &m_vecEventsChangeable[i];
        }
    }
    return NULL;
}

void CEventDataMgr::handlerEventsChangeableInfo(WorldPacket &packet)
{
    STC_EVENT_CHANGEABLE_INFO eventInfo;
    eventInfo.m_vecCells.clear();
    packet >> eventInfo.byNoticeType;
    packet >> eventInfo.dwActiveId;
    
    if (eventInfo.byNoticeType == E_ACTIVE_BLOAD_TYPE_HANDLE) {
        
        packet >> eventInfo.dwLeftTime;
        eventInfo.dwLeftTime += getLocalCurTimeSec();
        
        packet >> eventInfo.strDesc;
        packet >> eventInfo.byBloadBannerType;
        packet >> eventInfo.byRewardBloadType;
        packet >> eventInfo.dwCompleteNum;
        uint8 byCellNum = 0;
        packet >> byCellNum;
        STC_CHANGEABLE_CELL_INFO cellInfo;
        
        for (int i = 0; i < byCellNum; i++) {
            packet >> cellInfo.dwRewId;
            packet >> cellInfo.strRewDesc;
            packet >> cellInfo.byStatus;
            
            uint8 byRewardNum = 0;
            packet >> byRewardNum;
            cellInfo.m_vecRewardItems.clear();
            STC_CHANGEABLE_CELL_REWARDITEM rewardItem;
            for (int j = 0; j < byRewardNum; j++) {
                packet >> rewardItem.dwUniteId;
                packet >> rewardItem.dwuniteCnt;
                cellInfo.m_vecRewardItems.push_back(rewardItem);
            }
            eventInfo.m_vecCells.push_back(cellInfo);
        }
    }
    else if(eventInfo.byNoticeType == E_ACTIVE_BLOAD_TYPE_NOTICE)
    {
        m_vecEventAnnounce.clear();
        uint8 bySize;
        packet >> bySize;
        for (int i = 0; i < bySize; i++) {
            STC_EVENT_ANNOUNCE_INFO anInfo;
            string strTitle;
            uint32 dwLeftTime;//	;		倒计时
            string strDesc;
            uint8 byBloadBannerType;
            uint8 byRewardBloadType;
            
            packet >> strTitle;
            packet >> dwLeftTime;
            packet >> strDesc;
            packet >> byBloadBannerType;
            packet >> byRewardBloadType;
            
            anInfo.titleName = strTitle;
            anInfo.leftTime = dwLeftTime + getLocalCurTimeSec();
            CCArray * arr = ccs(strDesc)->componentsSeparatedByString("|");
            anInfo.titleDes = ((CCString*)arr->objectAtIndex(0))->getCString();
            if (arr->count() > 1) {
                anInfo.fuliDes = ((CCString*)arr->objectAtIndex(1))->getCString();
            }
            
            m_vecEventAnnounce.push_back(anInfo);
        }
    }
    
    std::map<uint32, STC_EVENT_CHANGEABLE_INFO>::iterator mapIter = m_mapEvnetChangeableInfo.find(eventInfo.dwActiveId);
    if (mapIter != m_mapEvnetChangeableInfo.end()) {
        m_mapEvnetChangeableInfo.erase(mapIter);
    }
    m_mapEvnetChangeableInfo[eventInfo.dwActiveId] = eventInfo;
    
    CGameSession::NotifyRefeashLayer();
}

//#define CMD_SC_ACTIVE_REW_RESULT			CMD_MAKE_SERVER(0x0143)
/**	 活动奖励结果
 *		[uint16] wError
 *		[uint32] dwActiveId
 *		[uint32] dwClickId
 */
void CEventDataMgr::handlerActiveGetRewardResult(WorldPacket &packet)
{
    uint16 wError = 0;
    packet >> wError;
    if (!wError) {

    }
    uint32 dwActiveId = 0,dwRewardId = 0;
    packet >> dwActiveId >> dwRewardId;
    
    std::map<uint32, STC_EVENT_CHANGEABLE_INFO>::iterator mapIter = m_mapEvnetChangeableInfo.find(dwActiveId);
    if (mapIter != m_mapEvnetChangeableInfo.end()) {
        for (int i = 0; i < mapIter->second.m_vecCells.size(); i++) {
            if (mapIter->second.m_vecCells[i].dwRewId == dwRewardId) {
                mapIter->second.m_vecCells[i].byStatus = E_REW_STATUS_DONE;
            }
        }
    }
    CGameSession::NotifyRefeashLayer();
}

STC_EVENT_CHANGEABLE_INFO* CEventDataMgr::getEventChangeableInfoByActiveId(uint32 dwActiveId)
{
    std::map<uint32, STC_EVENT_CHANGEABLE_INFO>::iterator mapIter = m_mapEvnetChangeableInfo.find(dwActiveId);
    if (mapIter != m_mapEvnetChangeableInfo.end()) {
        return &mapIter->second;
    }
    return NULL;
}


/** 神秘商店列表
 * 	[uint32] LeftUpdateTime
 * 	[uint32] UpdateCostRock
 * 	[uint32] UpdateCostDollar
 * 	[uint8] count
 * 		[uint32] dwGoodsId
 *		[uint32] dwBuyCnt
 * */
void CEventDataMgr::handlerMySteryGoods(WorldPacket& packet)
{
    uint32 dwLeftTime;
    uint32 UpdateCostRock;
    uint32 UpdateCostDollar;
    packet >> dwLeftTime;
    packet >> UpdateCostRock;
    packet >> UpdateCostDollar;
    m_dwMySteryLeftTime = dwLeftTime;
    
    uint8 count;
    packet >> count;
    m_vecMySteryGoods.clear();
    for (int i = 0; i < count; ++i) {
        uint32 dwGoodsId;
        std::string strName;
        uint32 dwBuyContentId;
        uint32 dwBuyCount;
        uint32 dwCostCnt;
        std::string strDescription;
        //        uint32 dwIconId;
        uint32 dwLimitCnt;
        uint32 dwBuyCnt;
        
        packet >> dwGoodsId;
        packet >> dwBuyCnt;
        
        MysteryShopConfig::STC_CONFIG_MYSTERY_SHOP* cfg = GET_CONFIG_STC(MysteryShopConfig, dwGoodsId);
        if (cfg) {
            strName = g_PacketDataMgr->GetObjectNameByIndex(cfg->dwItemId);
            dwBuyContentId = cfg->dwItemId;
            dwBuyCount = cfg->dwItemCnt;
            dwCostCnt = cfg->dwBuyCost;
            strDescription = cfg->strDes;
            dwLimitCnt = cfg->dwCanBuyCnt;
        }
        
        STC_STERY_GOODS stcGoods;
        stcGoods.byType = E_MY_SHOP_MYSTERY;
        stcGoods.dwGoodsId = dwGoodsId;
        stcGoods.strName = strName;
        stcGoods.dwBuyContentId = dwBuyContentId;
        stcGoods.dwBuyCount = dwBuyCount;
        stcGoods.dwCostItemId = E_PET_FUSE_ROCK;
        stcGoods.dwCostCnt = dwCostCnt;
        stcGoods.strDescription = strDescription;
        stcGoods.dwLimitCnt = dwLimitCnt;
        stcGoods.dwBuyCnt = dwBuyCnt;
        
        m_vecMySteryGoods.push_back(stcGoods);
    }
}

/** 神秘商店更新
 * 		[uint32] dwGoodsId
 *		[uint32] dwBuyCnt
 * */
void CEventDataMgr::handlerMySteryUpdate(WorldPacket& packet)
{
    uint32 dwGoodsId;
    uint32 dwBuyCnt;
    packet >> dwGoodsId;
    packet >> dwBuyCnt;
    for (int i = 0; i < m_vecMySteryGoods.size(); ++i) {
        STC_STERY_GOODS goods = m_vecMySteryGoods[i];
        if (goods.dwGoodsId != dwGoodsId) {
            continue;
        }
        goods.dwBuyCnt = dwBuyCnt;
        m_vecMySteryGoods[i] = goods;
        break;
    }
    if (CcbEventMySteryShopLayer::getCurScene()) {
        CcbEventMySteryShopLayer::getCurScene()->loadData();
    }
}

/**  秘境商店列表
 *		[uint16]  wError
 *		[uint32]  dwLeftTime
 *		[uint8]   bySize
 *			[uint32]  dwBuyId
 *			[uint32]  dwNumTotal
 *          [uint32]  dwLimitCnt
 *			[uint32]  dwBuyCnt
 *			[uint32]  dwPriceId
 *			[uint32]  dwPriceNum
 */
void CEventDataMgr::handlerMJShopGoods(WorldPacket& packet)
{
    uint32 dwLeftTime;
    packet >> dwLeftTime;
    m_dwMJShopLeftTime = dwLeftTime;
    
    uint8 count;
    packet >> count;
    m_vecMJShopGoods.clear();
    for (int i = 0; i < count; ++i) {
        uint32 dwGoodsId;
        std::string strName;
        uint32 dwBuyContentId;
        uint32 dwBuyCount;
        uint32 dwCostItemId;
        uint32 dwCostCnt;
        std::string strDescription;
        uint32 dwLimitCnt;
        uint32 dwBuyCnt;
        
        packet >> dwGoodsId;
        packet >> dwBuyCount;
        dwBuyContentId = dwGoodsId;
        packet >> dwLimitCnt;
        packet >> dwBuyCnt;
        packet >> dwCostItemId;
        packet >> dwCostCnt;
        strName = g_PacketDataMgr->GetObjectNameByIndex(dwGoodsId);

        
        STC_STERY_GOODS stcGoods;
        stcGoods.byType = E_MY_SHOP_MJ;
        stcGoods.dwGoodsId = dwGoodsId;
        stcGoods.strName = strName;
        stcGoods.dwBuyContentId = dwBuyContentId;
        stcGoods.dwBuyCount = dwBuyCount;
        stcGoods.dwCostCnt = dwCostCnt;
        stcGoods.dwCostItemId = dwCostItemId;
        stcGoods.strDescription = strDescription;
        stcGoods.dwLimitCnt = dwLimitCnt;
        stcGoods.dwBuyCnt = dwBuyCnt;
        
        m_vecMJShopGoods.push_back(stcGoods);
    }
}

/**  秘境商店 购买更新
 *		[uint16]  wError
 *		[uint32]  dwBuyId
 *		[uint32]  dwNumTotal
 *		[uint32]  dwBuyCnt
 */
void CEventDataMgr::handlerMJShopUpdate(WorldPacket& packet)
{
    uint32  dwBuyId;
    uint32  dwNumTotal;
    uint32  dwBuyCnt;
    packet >> dwBuyId;
    packet >> dwNumTotal;
    packet >> dwBuyCnt;
    for (int i = 0; i < m_vecMJShopGoods.size(); ++i) {
        STC_STERY_GOODS goods = m_vecMJShopGoods[i];
        if (goods.dwGoodsId != dwBuyId) {
            continue;
        }
        goods.dwBuyCnt = dwBuyCnt;
        m_vecMJShopGoods[i] = goods;
        break;
    }
    if (CcbEventMySteryShopLayer::getCurScene()) {
        CcbEventMySteryShopLayer::getCurScene()->loadData();
    }
}
