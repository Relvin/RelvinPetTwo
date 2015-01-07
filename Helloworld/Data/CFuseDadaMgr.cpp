//
//  CFuseDadaMgr.cpp
//  HelloWorld
//
//  Created by long on 14-6-4.
//
//

#include "CFuseDadaMgr.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "EquipDataMgr.h"
#include "PacketDataMgr.h"
#include "CcbFuseListLayer.h"

#include <algorithm>


bool CFuseDadaMgr::addSelected(uint32 dwId)
{
    if (m_arrSelected.size() < fuseCnt) {
        std::vector<uint32>::iterator it = std::find(m_arrSelected.begin(), m_arrSelected.end(), dwId);
        
        if( it == m_arrSelected.end()) {
            m_arrSelected.push_back(dwId);
            ReflashPetBagNum();
            return true;
        }
    }
    
    return false;
}

bool CFuseDadaMgr::delSelected(uint32 dwId)
{
    if (m_arrSelected.size() == 0)
    {
        return false;
    }
    
    std::vector<uint32>::iterator it = std::find(m_arrSelected.begin(), m_arrSelected.end(), dwId);
    
    if( it != m_arrSelected.end()) {
        m_arrSelected.erase(it);
        ReflashPetBagNum();
        return true;
    }
    return false;
}

bool CFuseDadaMgr::checkSelected(uint32 dwId)
{
    std::vector<uint32>::iterator it = std::find(m_arrSelected.begin(), m_arrSelected.end(), dwId);
    
    if( it != m_arrSelected.end()) {
        return true;
    }
    return false;
}

void CFuseDadaMgr::setFuseTab(uint8 tab)
{
    clearSelected();
    m_curTab = tab;
}

void CFuseDadaMgr::atuoSelecte()
{
    clearSelected();
    switch (m_curTab) {
        case E_FUSE_TAB_PET:
            autoSelectePet();
            break;
        case E_FUSE_TAB_EQUIP:
            autoSelecteEquip();
            break;
        default:
            break;
    }
}

//自动选择可融合宠（大于等于3星的）}
void CFuseDadaMgr::autoSelectePet()
{
//    int count = 0;//m_arrSelectedPet.size();
    m_arrSelected.clear();
//    std::map<uint32, CPet*> m_mapPets = CPetCtrl::getAllPet();
//    std::map<uint32, CPet*>::iterator it = m_mapPets.begin();
//    for (; it != m_mapPets.end(); ++it) {
//        if (!it->second || CPetCtrl::IsProtected(it->first)) {
//            continue;
//        }
//        PetFuseConfig::STC_PET_FUSE_CONFIG *fuCfg = GET_CONFIG_STC(PetFuseConfig, it->second->GetwIndex());
//        if (!fuCfg) {
//            continue;
//        }
//        if (count >= fuseCnt) {
//            break;
//        }
//        m_arrSelected.push_back(it->first);
//        count++;
//    }
    CPetCtrl::Get()->selectFuseElemAuto();
    m_arrSelected = CPetCtrl::Get()->GetSelectedPet();
}

void CFuseDadaMgr::autoSelecteEquip()
{
    int count = 0;
    //添加融合用装备，星级大于等于4}
    vector<uint32> arrEquipKeyId = g_EquipData->GetVecShowEquipKeyID();
    for (int i = 0; i < arrEquipKeyId.size(); i++)
    {
        const CEquip *equip = g_PacketDataMgr->GetEquipInfoByKeyID(arrEquipKeyId[i]);
        if (!equip || equip->GetWearPetID() || equip->GetRune1() || equip->GetRune2())
        {
            continue;
        }
        PetFuseConfig::STC_PET_FUSE_CONFIG* fCfg = GET_CONFIG_STC(PetFuseConfig, equip->GetIndex());
        //        EquipConfig::STC_EQUIP_CONFIG* eCfg = GET_CONFIG_STC(EquipConfig, equip->GetIndex());
        if (!fCfg) {
            continue;
        }
        if (count >= fuseCnt) {
            break;
        }
        m_arrSelected.push_back(equip->GetKeyID());
        count++;
    }
}

//刷新所选宠物的编号}
void CFuseDadaMgr::ReflashPetBagNum()
{
//    if (m_curTab == E_FUSE_TAB_PET)
//    {
        CcbFuseListLayer* fuseList = (CcbFuseListLayer*)CCDirector::sharedDirector()->getNowScene()->getChildByTag(1)->getChildByTag(1);
        if (fuseList) {
            fuseList->ReflashPetBagNum();
        }
//    }
}