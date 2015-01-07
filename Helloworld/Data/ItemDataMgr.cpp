//
//  ItemDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 13-11-26.
//
//

#include "ItemDataMgr.h"
#include "EnumDefines.h"
#include "ResourceDefine.h"
#include "Role.h"
#include "GameSession.h"
#include "PacketDataMgr.h"

void CItemDataMgr::AddShowItemIndex(uint32 dwIndex)
{
    vector<uint32>::iterator iter = m_vecShowItemIndex.begin();
    for (; iter != m_vecShowItemIndex.end(); iter++)
    {
        if (*iter == dwIndex)
        {
            CCLOG("Error: have been excit this index_%u in normal items", dwIndex);
            return;
        }
    }
    m_vecShowItemIndex.push_back(dwIndex);
}

vector<uint32> CItemDataMgr::GetVecShowItemIndex()
{
    return m_vecShowItemIndex;
}

void CItemDataMgr::ClearShowItemIndex()
{
    m_vecShowItemIndex.clear();
}

void CItemDataMgr::DelIndexFromShowVector(uint32 dwIndex)
{
    vector<uint32>::iterator iter = m_vecShowItemIndex.begin();
    for (; iter != m_vecShowItemIndex.end(); iter++)
    {
        if (*iter == dwIndex)
        {
            m_vecShowItemIndex.erase(iter);
            return;
        }
    }
    CCLOG("Error: can't find this index_%u in normal items", dwIndex);
}

void CItemDataMgr::AddPetChipIndex(uint32 dwIndex)
{
    vector<uint32>::iterator iter = m_vecPetChipIndex.begin();
    for (; iter != m_vecPetChipIndex.end(); iter++)
    {
        if (*iter == dwIndex)
        {
            CCLOG("Error: have been excit this index_%u in pet chip", dwIndex);
            return;
        }
    }
    m_vecPetChipIndex.push_back(dwIndex);
}

vector<uint32> CItemDataMgr::GetVecPetChip()
{
    return m_vecPetChipIndex;
}

void CItemDataMgr::ClearPetChipIndex()
{
    m_vecPetChipIndex.clear();
}

void CItemDataMgr::DelPetChipIndex(uint32 dwIndex)
{
    vector<uint32>::iterator iter = m_vecPetChipIndex.begin();
    for (; iter != m_vecPetChipIndex.end(); iter++)
    {
        if (*iter == dwIndex)
        {
            m_vecPetChipIndex.erase(iter);
            return;
        }
    }
    CCLOG("Error: can't find this index_%u in pet chip", dwIndex);
}

void CItemDataMgr::checkAllItem()
{
    //箱子
    CGameSession::GetRole()->SetbyNotiBox(0);
    for (int i = 0; i < m_vecShowItemIndex.size(); i++) {
        uint32 itemId = m_vecShowItemIndex[i];
        if (!itemId) {
            continue;
        }
        const CItem* item = g_PacketDataMgr->GetItemInfoByIndex(itemId);
        if (item->GetConfigData().byType != E_ITEM_USE_BOX) {
            continue;
        }
        if (item->GetConfigData().wParas[1] && !g_PacketDataMgr->GetItemCountByIndex(item->GetConfigData().wParas[1])) {
            continue;
        }
        CGameSession::GetRole()->SetbyNotiBox(1);
        break;
    }
    //碎片
    CGameSession::GetRole()->SetbyNotiChips(0);
    for (int i = 0; i < m_vecPetChipIndex.size(); i++) {
        uint32 itemId = m_vecPetChipIndex[i];
        if (!itemId) {
            continue;
        }
        const CItem* item = g_PacketDataMgr->GetItemInfoByIndex(itemId);
        if (item->GetCount() >= item->GetConfigData().wParas[0]) {
            CGameSession::GetRole()->SetbyNotiChips(1);
            break;
        }
    }
    
}