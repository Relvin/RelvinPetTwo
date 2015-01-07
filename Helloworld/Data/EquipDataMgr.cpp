//
//  EquipDataMgr.cpp
//  HelloWorld
//
//  Created by jun on 14-2-11.
//
//

#include "EquipDataMgr.h"
#include "ResourceDefine.h"
#include "ConfigGet.h"
#include "TeamCtrl.h"
#include "Team.h"

//========装备==========}
void CEquipDataMgr::AddShowEquipKeyID(uint32 dwKeyID)
{
    vector<uint32>::iterator iter = m_vecShowEquipKeyID.begin();
    for (; iter != m_vecShowEquipKeyID.end(); iter++)
    {
        if (*iter == dwKeyID)
        {
            CCLOG("Error: have been excit this equip, KeyID_%u", dwKeyID);
            return;
        }
    }
    m_vecShowEquipKeyID.push_back(dwKeyID);
}

vector<uint32> CEquipDataMgr::GetVecShowEquipKeyID()
{
    return m_vecShowEquipKeyID;
}

void CEquipDataMgr::ClearShowEquipKeyID()
{
    m_vecShowEquipKeyID.clear();
}

void CEquipDataMgr::DelKeyIDFormEquipShowVector(uint32 dwKeyID)
{
    vector<uint32>::iterator iter = m_vecShowEquipKeyID.begin();
    for (; iter != m_vecShowEquipKeyID.end(); iter++)
    {
        if (*iter == dwKeyID)
        {
            m_vecShowEquipKeyID.erase(iter);
            return;
        }
    }
    CCLOG("Error: can't find this equip, KeyID_%u", dwKeyID);
}

//========符文==========}
void CEquipDataMgr::AddShowRuneKeyID(uint32 dwKeyID)
{
    vector<uint32>::iterator iter = m_vecShowRuneKeyID.begin();
    for (; iter != m_vecShowRuneKeyID.end(); iter++)
    {
        if (*iter == dwKeyID)
        {
            CCLOG("Error: have been excit this rune, KeyID_%u", dwKeyID);
            return;
        }
    }
    m_vecShowRuneKeyID.push_back(dwKeyID);
}

vector<uint32> CEquipDataMgr::GetVecShowRuneKeyID()
{
    return m_vecShowRuneKeyID;
}

void CEquipDataMgr::ClearShowRuneKeyID()
{
    m_vecShowRuneKeyID.clear();
}

void CEquipDataMgr::DelKeyIDFormRuneShowVector(uint32 dwKeyID)
{
    vector<uint32>::iterator iter = m_vecShowRuneKeyID.begin();
    for (; iter != m_vecShowRuneKeyID.end(); iter++)
    {
        if (*iter == dwKeyID)
        {
            m_vecShowRuneKeyID.erase(iter);
            return;
        }
    }
    CCLOG("Error: can't find this rune, KeyID_%u", dwKeyID);
}

void CEquipDataMgr::SetStartClock()
{
    m_dwStartClock = clock();
}

double CEquipDataMgr::GetLostTime()
{
    return floor((clock() - m_dwStartClock) / CLOCKS_PER_SEC);
}

#pragma mark EquipTeam

void CEquipTeamDataMgr::initEquipTeam(std::map<uint8, std::map<uint8, uint32> > mapEquipTeam)
{
    m_mapEquipTeam = mapEquipTeam;
}

//更新}
void CEquipTeamDataMgr::updateEquipTeam(uint8 site, uint8 part, uint32 equipId)
{
    std::map<uint8, uint32>mapEquip;
    mapEquip.clear();
    if (m_mapEquipTeam.find(site) != m_mapEquipTeam.end()) {
        mapEquip = m_mapEquipTeam[site];
    }
    
    mapEquip[part] = equipId;
    m_mapEquipTeam[site] = mapEquip;
}

//装备}
void CEquipTeamDataMgr::wearEquip(uint8 site, uint8 part, uint32 equipId)
{
    std::map<uint8, uint32>mapEquip;
    mapEquip.clear();
    if (m_mapEquipTeam.find(site) != m_mapEquipTeam.end()) {
        mapEquip = m_mapEquipTeam[site];
    }

    mapEquip[part] = equipId;
    m_mapEquipTeam[site] = mapEquip;
}

//卸下}
void CEquipTeamDataMgr::downEquip(uint8 site, uint8 part)
{
    std::map<uint8, uint32>mapEquip;
    mapEquip.clear();
    if (m_mapEquipTeam.find(site) != m_mapEquipTeam.end()) {
        mapEquip = m_mapEquipTeam[site];
    }
    
    mapEquip[part] = 0;
    m_mapEquipTeam[site] = mapEquip;

    uint32 equipId = 0;
    if (mapEquip.size() > 0 && mapEquip.find(part) != mapEquip.end()) {
        equipId = mapEquip[part];
    }

}

//获取战位上的装备}
std::map<uint8, uint32> CEquipTeamDataMgr::getEquipsBySite(uint8 site)
{
    std::map<uint8, uint32>mapEquip;
    mapEquip.clear();
    if (m_mapEquipTeam.find(site) != m_mapEquipTeam.end()) {
        mapEquip = m_mapEquipTeam[site];
    }
    return mapEquip;
}

//根据战位和部位获取装备id}
uint32 CEquipTeamDataMgr::getEquipIdBySiteAPart(uint8 site, uint8 part)
{
    uint32 equipId = 0;
    std::map<uint8, uint32>mapEquip;
    mapEquip.clear();
    if (m_mapEquipTeam.find(site) != m_mapEquipTeam.end()) {
        mapEquip = m_mapEquipTeam[site];
    }
    
    if (mapEquip.size() > 0 && mapEquip.find(part) != mapEquip.end()) {
        equipId = mapEquip[part];
    }
    
    return equipId;
}

//验证装备是否被穿戴
bool CEquipTeamDataMgr::checkEquipIsWear(uint32 equipId)
{
    for (int s = 1; s <= 6; s++) {
        if (m_mapEquipTeam.find(s) != m_mapEquipTeam.end()) {
            
            std::map<uint8, uint32>mapEquip = m_mapEquipTeam[s];;
            
            for (int part = 0; part < 4; part++) {
                if (mapEquip.find(part) != mapEquip.end()) {
                    if (equipId != mapEquip.find(part)->second) {
                        continue;
                    }
                    //找出装备在装备队伍中的位置，如果该位置有宠物，说明装备被用了
                    CTeam* team = CTeamCtrl::GetCurTeam();
                    if (team->getarrPetObId()[s]) {
                        return true;
                    }
                    return false;
                }
            }
        }
    }
    
    return false;
}