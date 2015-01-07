//
//  Item.cpp
//  HelloWorld
//
//  Created by jun on 14-1-23.
//
//

#include "Item.h"


CItem::CItem()
{
    
}

CItem::~CItem()
{
    
}

void CItem::AddConfigData()
{
    if (m_dwIndex > 0)
    {
        LP_ITEM_CONFIG pConfig = GET_CONFIG_STC(ItemConfig, m_dwIndex);
        if (pConfig)
        {
            m_ConfigData.strName = pConfig->strName;
            m_ConfigData.byType = pConfig->byType;
            m_ConfigData.strDesc = pConfig->strDesc;
            m_ConfigData.byQuality = pConfig->byQuality;
            m_ConfigData.byIsCanSale = pConfig->byIsCanSale;
            m_ConfigData.wUseLv = pConfig->wUseLv;
            m_ConfigData.wGroupCnt = pConfig->wGroupCnt;
            m_ConfigData.wMaxHasCnt = pConfig->wMaxHasCnt;
            m_ConfigData.dwPrice = pConfig->dwPrice;
            m_ConfigData.dwIconId = pConfig->dwIconId;
            
            for (int i = 0; i < 5; i++)
            {
                m_ConfigData.wParas[i] = pConfig->wParas[i];
            }
        }
        else
        {
            CCLOG("Item:%u config error", m_dwIndex);
        }
    }
    else
    {
        CCLOG("Item index is wrong.");
    }
}

ITEM_CONFIG_DATA CItem::GetConfigData() const
{
    return m_ConfigData;
}

