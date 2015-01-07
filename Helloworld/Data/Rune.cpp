//
//  Rune.cpp
//  HelloWorld
//
//  Created by jun on 14-1-23.
//
//

#include "Rune.h"

CRune::CRune()
{
    
}

CRune::~CRune()
{
    
}

void CRune::AddConfigData()
{
    if (m_dwIndex > 0)
    {
        LP_RUNE_CONFIG pConfig = GET_CONFIG_STC(RuneConfig, m_dwIndex);
        if (pConfig)
        {
            m_ConfigData.strName = pConfig->strName;
            m_ConfigData.byEffectType1 = pConfig->byEffectType1;
            m_ConfigData.wEffectValue1 = pConfig->wEffectValue1;
            m_ConfigData.byEffectType2 = pConfig->byEffectType2;
            m_ConfigData.wEffectValue2 = pConfig->wEffectValue2;
            m_ConfigData.dwCostMoney = pConfig->dwCostMoney;
            
            m_ConfigData.dwCostSoul = pConfig->dwCostSoul;
            m_ConfigData.dwPrice = pConfig->dwPrice;
            m_ConfigData.wCompoundRate = pConfig->wCompoundRate;
            m_ConfigData.strDesc = pConfig->strDesc;
            m_ConfigData.dwIcon = pConfig->dwIcon;
        }
        else
        {
            CCLOG("Rune:%u config error", m_dwIndex);
        }
    }
    else
    {
        CCLOG("Rune index is wrong!");
    }
}

RUNE_CONFIG_DATA CRune::GetConfigData() const
{
    return m_ConfigData;
}
