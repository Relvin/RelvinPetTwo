//
//  BuyDataMgr.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-6-13.}
//
//

#include "BuyDataMgr.h"
#include "BackCtrl.h"
#include "BuyMiddleLayer.h"

void BuyDataMgr::handleBuyShopInfo(WorldPacket& packet) {
    uint8 bySize;
    packet >> bySize;
    m_vecBuyInfo.clear();
    for (int i = 0; i < bySize; i++) {
        STC_BUY sBuy;
        packet >> sBuy.byType >> sBuy.dwCostDollar >> sBuy.dwLeftCnt >> sBuy.dwEarnCnt;
        m_vecBuyInfo.push_back(sBuy);
    }
    if (m_bChangeToBuyScene) {
        BackCtrl::ChangeRootScene(kBuyScene);
    }
    m_bChangeToBuyScene = true;
}

void BuyDataMgr::handleBuyShopUpdateInfo(WorldPacket& packet) {
    STC_BUY sBuy;
    packet >> sBuy.byType >> sBuy.dwCostDollar >> sBuy.dwLeftCnt >> sBuy.dwEarnCnt;
    
    ITR_VEC_BUY pIter;
    for (pIter = m_vecBuyInfo.begin(); pIter != m_vecBuyInfo.end(); pIter++) {
        if (pIter->byType == sBuy.byType) {
            pIter->dwCostDollar = sBuy.dwCostDollar;
            pIter->dwLeftCnt = sBuy.dwLeftCnt;
            pIter->dwEarnCnt = sBuy.dwEarnCnt;
            break;
        }
    }
    if (BuyMiddleLayer::GetCurrScene()) {
        BuyMiddleLayer::GetCurrScene()->updateLeftCnt();
    }
    
}

BuyDataMgr::STC_BUY BuyDataMgr::buyInfoByType(uint8 byTType) {
    ITR_VEC_BUY pIter;
    for (pIter = m_vecBuyInfo.begin(); pIter != m_vecBuyInfo.end(); pIter++) {
        if (pIter->byType == byTType) {
            return *pIter;
        }
    }
    CCAssert(1, "error type");
    return *pIter;
}

