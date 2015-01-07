//
//  ShopDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 13-12-26.
//
//

#include "ShopDataMgr.h"
#include "CcbManager.h"
#include "CcbShopSelectNumLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "md5.h"
#include "LoginSystem.h"
#include "Support.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform_android.h"
#endif

void CShopDataMgr::AddShopItemList(const SHOP_ITEM_INFO& info)
{
    int nIndex = info.byShopType - 1;
    if (nIndex < SHOP_TYPE_MAX)
    {
//        ITER_MAP_SHOP_ITEM_INFO iter = m_mapShopListTab[nIndex].begin();
//        for (; iter != m_mapShopListTab[nIndex].end(); iter++)
//        {
//            if (iter->second.dwGoodsId == info.dwGoodsId)
//            {
//                iter->second.byShopType = info.byShopType;
//                iter->second.dwBuyTypeId = info.dwBuyTypeId;f
//                iter->second.dwBuyContentId = info.dwBuyContentId;
//                iter->second.dwBuyCount = info.dwBuyCount;
//                iter->second.dwCostTypeId = info.dwCostTypeId;
//                iter->second.dwCostContentId = info.dwCostContentId;
//                iter->second.dwCostCount = info.dwCostCount;
//                iter->second.strName = info.strName;
//                iter->second.strDescription = info.strDescription;
//                iter->second.dwIconId = info.dwIconId;
//                iter->second.byStatus = info.byStatus;
//                iter->second.dwSortIdx = info.dwSortIdx;
//
//                iter->second.dwDisappearTime = info.dwDisappearTime;
//                return;
//            }
//        }
        if (m_mapShopListTab[nIndex].find(info.dwSortIdx) != m_mapShopListTab[nIndex].end()) {
            m_mapShopListTab[nIndex][info.dwSortIdx] = info;
        }
        else{
            m_mapShopListTab[nIndex].insert(make_pair(info.dwSortIdx, info));
        }
    }
}

MAP_SHOP_ITEM_INFO CShopDataMgr::GetShopListByType(E_SHOP_TYPE type)
{
    int nIndex = type - 1;
    if (nIndex < SHOP_TYPE_MAX)
    {
        return m_mapShopListTab[nIndex];
    }
    return MAP_SHOP_ITEM_INFO();
}

SHOP_ITEM_INFO CShopDataMgr::GetShopItemByID(uint32 dwItemId)
{
    ITER_MAP_SHOP_ITEM_INFO iter;
    for (int i = 0 ; i < SHOP_TYPE_MAX; i++)
    {
        iter = m_mapShopListTab[i].begin();
        for (; iter != m_mapShopListTab[i].end(); iter++)
        {
            if (iter->second.dwGoodsId == dwItemId)
            {
                return iter->second;
            }
        }
    }
    
    return SHOP_ITEM_INFO();
}

void CShopDataMgr::AddStorePayList(const STORE_PAY_LIST_INFO& info)
{
//    ITER_VEC_PAY_LIST_INFO iter = m_vecStorePayList.begin();
//    for (; iter != m_vecStorePayList.end(); iter++)
//    {
//        if (iter->dwGoodsId == info.dwGoodsId)
//        {
//            iter->dwDollar = info.dwDollar;
//            iter->strFirstLine = info.strFirstLine;
//            iter->strSecondLine = info.strSecondLine;
//            iter->strThirdLine = info.strThirdLine;
//            iter->dwLeftDay = info.dwLeftDay;
//            iter->byBuyType = info.byBuyType;
//            iter->dwPrice = info.dwPrice;
//            iter->byFirstPay = info.byFirstPay;
//            return;
//        }
//    }
    m_vecStorePayList.push_back(info);
}

STORE_PAY_LIST_INFO* CShopDataMgr::GetStorePayGoodsInfoById(uint32 dwGoodsId)
{
    for (int i = 0; i < m_vecStorePayList.size() ; i++) {
        if (m_vecStorePayList[i].dwGoodsId == dwGoodsId) {
            return &m_vecStorePayList[i];
        }
    }
    return NULL;
}

void CShopDataMgr::setViewLayerRect(cocos2d::CCRect rect)
{
    m_ViewLayerRect = rect;
}

cocos2d::CCRect CShopDataMgr::getViewLayerRect()
{
    return m_ViewLayerRect;
}

void CShopDataMgr::SetCurChosenGoodsId(uint32 dwGoodsId)
{
    m_dwCurChosenGoodsId = dwGoodsId;
}

uint32 CShopDataMgr::GetCurChosenGoodsId()
{
    return m_dwCurChosenGoodsId;
}

void CShopDataMgr::OpenDlgSelectNum()
{
    if (!m_isDlgOpen && m_pShopSceneListNode)
    {
        m_isDlgOpen = true;
//        CcbShopSelectNumLayer* pLayer = (CcbShopSelectNumLayer*)CcbManager::sharedManager()->LoadCcbShopSelecNumLayer(m_pShopSceneListNode);
//        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//        pLayer->ignoreAnchorPointForPosition(false);
//        pLayer->setAnchorPoint(ccp(0.5, 0.5));
//        pLayer->setPosition(ccp(winSize.width*0.5 , winSize.height *0.5));
//        m_pShopSceneListNode->addChild(pLayer, 999);
    }
}

void CShopDataMgr::SetDlgOpenNode(cocos2d::CCNode *node)
{
    m_pShopSceneListNode = node;
}

void CShopDataMgr::SetDlgOpenState(bool state)
{
    m_isDlgOpen = state;
}

bool CShopDataMgr::GetDlgOpenState()
{
    return m_isDlgOpen;
}

void CShopDataMgr::SetSelectNum(int num)
{
    m_nSelectNum = num;
}

int CShopDataMgr::GetSelectNum()
{
    return m_nSelectNum;
}

const char* CShopDataMgr::GetOrderSerialByGoodsId(uint32 dwGoodsId)
{
    CRole *pRole = CGameSession::GetRole();
    STORE_PAY_LIST_INFO* pPayInfo = this->GetStorePayGoodsInfoById(dwGoodsId);
    if (!pPayInfo) {
        return NULL;
    }
    CCString* pCStrOrder;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if defined VERSION_I4 || VERSION_PP
    pCStrOrder = CCString::createWithFormat("%d-%d-%d-%d-%d-%ld", Support::sharedInstance()->appChannel(), LoginSystem::Get()->getAreaId(), pRole->GetdwAccountId(),pPayInfo->dwGoodsId, 1, time(NULL));
#endif
#if defined VERSION_91
    pCStrOrder = CCString::createWithFormat("%d-%d-%d-%d", Support::sharedInstance()->appChannel(), LoginSystem::Get()->getAreaId(), pRole->GetdwAccountId(), 0);
#endif

#ifdef VERSION_D9
    pCStrOrder = CCString::createWithFormat("%d-%d-%d-%d-%d", Support::sharedInstance()->appChannel(), LoginSystem::Get()->getAreaId(), pRole->GetdwAccountId(),pPayInfo->dwGoodsId, 1);
#endif
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    pCStrOrder = CCString::createWithFormat("%d-%d-%d-%d-%d-%ld", PlatformGetAccountChannel(), LoginSystem::Get()->getAreaId(), pRole->GetdwAccountId(),pPayInfo->dwGoodsId, 1, time(NULL));
#else

#endif
    return pCStrOrder->getCString();
}
