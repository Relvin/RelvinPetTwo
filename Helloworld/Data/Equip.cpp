//
//  Equip.cpp
//  HelloWorld
//
//  Created by jun on 14-1-23.
//
//

#include "Equip.h"
#include "EnumDefines.h"

CEquip::CEquip()
{

}

CEquip::~CEquip()
{
    
}

void CEquip::AddConfigData()
{
    if (m_dwIndex > 0)
    {
        LP_EQUIPNEW_CONFIG pConfig = GET_CONFIG_STC(EquipNewConfig, m_dwIndex);
        
        
        
        if (pConfig)
        {
            m_ConfigData = *pConfig;
            
//            m_ConfigData.dwIndex = m_dwIndex;
//            m_ConfigData.strName = pConfig->strName;
//            m_ConfigData.dwGroupId = pConfig->dwGroupId;
//            m_ConfigData.byPos = pConfig->byPos;
//
//            m_ConfigData.byEffectType1 = pConfig->byEffectType1;
//            m_ConfigData.wEffectValue1 = pConfig->wEffectValue1;
//            m_ConfigData.wGrowthRate1 = pConfig->wGrowthRate1;
//            
//            m_ConfigData.byEffectType2 = pConfig->byEffectType2;
//            m_ConfigData.wEffectValue2 = pConfig->wEffectValue2;
//            m_ConfigData.wGrowthRate2 = pConfig->wGrowthRate2;
//            
//            m_ConfigData.dwCostBaseValue= pConfig->dwCostBaseValue;
//            m_ConfigData.dwPrice = pConfig->dwPrice;
//            m_ConfigData.strDesc = pConfig->strDesc;
//            m_ConfigData.dwIcon = pConfig->dwIcon;
//            m_ConfigData.byStar = pConfig->byStar;
//            m_ConfigData.byQuality = pConfig->byQuality;
//            
//            m_ConfigData.dwEvoID = pConfig->dwEvoID;
//            m_ConfigData.wEvoLV = pConfig->wEvoLV;
//            m_ConfigData.wEvoCoef = pConfig->wEvoCoef;
//            
//            m_ConfigData.dwEvoMaterial1 = pConfig->dwEvoMaterial1;
//            m_ConfigData.dwEvoMaterialAttri1 = pConfig->dwEvoMaterialAttri1;
//            
//            m_ConfigData.dwEvoMaterial2 = pConfig->dwEvoMaterial2;
//            m_ConfigData.dwEvoMaterialAttri2 = pConfig->dwEvoMaterialAttri2;
//            
//            m_ConfigData.dwEvoCostMoney = pConfig->dwEvoCostMoney;
        }
        else
        {
            CCLOG("Equip:%u config error", m_dwIndex);
        }
    }
    else
    {
        CCLOG("Equip index is wrong!");
    }
}

EQUIPNEW_CONFIG_DATA CEquip::GetConfigData() const
{
    return m_ConfigData;
}

LP_EQUIPEVO_CONFIG CEquip::GetEvoConfigDataByLv(uint8 byEvoLv) const
{
    if (byEvoLv > 0) {
        LP_EQUIPEVO_CONFIG pConfig = GET_CONFIG_STC(EquipEvoConfig, m_ConfigData.dwEvoItemID * 100 + byEvoLv);
        if (pConfig) {
            return pConfig;
        }
    }
    
    return NULL;
}

const uint32 CEquip::GetCurStrengthenCostMoney()
{
    EquipStrengthenConfig::STC_EQUIP_STRENGTHEN_CONFIG* pConfig = GET_CONFIG_STC(EquipStrengthenConfig, m_byLv+1);
    if (pConfig)
    {
        return pConfig->dwCostMoney * m_ConfigData.dwCostBaseValue * 0.01;
    }
    return 0;
}


//获取当前进阶等级}
uint16 CEquip::getEvoLv() const
{
    return m_dwIndex % 1000 / 100;
}

uint32 CEquip::getEquipAttrInfoByType(uint8 byType) const
{
    std::string str = "";

    uint32 dwValue = 0;
    
    /*
     生命 1
     普攻 2
     普防 3
     回复 4
     特攻 5
     特防 6
     暴击 7
     速度 8
     命中 9
     闪避 10
     爆伤 11
     抗暴 12
     攻击 13
     */
    
    switch (byType) {
        case E_ATTR_HP:
            dwValue = m_dwHP;
            break;
        case E_ATTR_CATT:
            dwValue = m_dwCAtk;
            break;
        case E_ATTR_CDEF:
            dwValue = m_dwCDef;
            break;
        case E_ATTR_REV:
            dwValue = m_dwRev;
            break;
        case E_ATTR_SATT:
            dwValue = m_dwSAtk;
            break;
        case E_ATTR_SDEF:
            dwValue = m_dwSDef;
            break;
        case E_ATTR_CRIT:
            dwValue = m_dwCrit;
            break;
        case E_ATTR_HIT:
            dwValue = m_dwHit;
            break;
        case E_ATTR_SPEED:
            dwValue = m_dwSpeed;
            break;
        case E_ATTR_DODGE:
            dwValue = m_dwDodge;
            break;
        case E_ATTR_CRIT_HURT:
            dwValue = m_dwCritDamage;
            break;
        case E_ATTR_CRIT_FREE:
            dwValue = m_dwCritFree;
            break;
        case E_ATTR_ALL_ATT:
            dwValue = m_dwAllAtk;
            break;
        default:
            break;
    }
    
    
    return dwValue;
}
