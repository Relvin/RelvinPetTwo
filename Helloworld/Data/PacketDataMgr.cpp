//
//  PacketDataMgr.cpp
//  MyGame
//
//  Created by jun on 14-8-4.
//
//

#include "PacketDataMgr.h"
#include "ItemDataMgr.h"
#include "EquipDataMgr.h"
#include "EnumDefines.h"
#include "ResourceDefine.h"
#include "ResourceStringClient.h"
#include "PetCtrl.h"
#include "TeamCtrl.h"
#include "GuideData.h"

//========物品============}

bool CPacketDataMgr::AddNewItemToMap(const CItem* pItem)
{
    map<uint32, CItem*>::iterator iter = m_mapItemPacket.find(pItem->GetIndex());
    if (iter == m_mapItemPacket.end())
    {
        m_mapItemPacket.insert(make_pair(pItem->GetIndex(), const_cast<CItem*>(pItem)));
        if (pItem->GetConfigData().byType == E_ITEM_USE_PET_PATCH ||
            pItem->GetConfigData().byType == E_ITEM_USE_EMBLEM_PATCH ||
            pItem->GetConfigData().byType == E_ITEM_USE_EQUIP_PATCH)
        {
            g_ItemData->AddPetChipIndex(pItem->GetIndex());
        }
        else
        {
            g_ItemData->AddShowItemIndex(pItem->GetIndex());
        }
        return true;
    }
    else
    {
        CCLOG("Add new item Error: item_%u have been existed.", pItem->GetIndex());
        return false;//外部获得false记得delete}
    }
}

void CPacketDataMgr::ClearItemMap()
{
    m_mapItemPacket.clear();
    g_ItemData->ClearShowItemIndex();
    g_ItemData->ClearPetChipIndex();
}

const CItem* CPacketDataMgr::GetItemInfoByIndex(uint32 dwIndex)
{
    map<uint32, CItem*>::iterator iter = m_mapItemPacket.find(dwIndex);
    if (iter != m_mapItemPacket.end())
    {
        return iter->second;
    }
    else
    {
        CCLOG("Get item info Error: can't find this item_%u.", dwIndex);
        return NULL;
    }
}

void CPacketDataMgr::UpdateItemCount(uint32 dwIndex, uint32 dwCount)
{
    map<uint32, CItem*>::iterator iter = m_mapItemPacket.find(dwIndex);
    if (iter != m_mapItemPacket.end())
    {
        if (dwCount == 0)
        {
            if (iter->second->GetConfigData().byType == E_ITEM_USE_PET_PATCH ||
                iter->second->GetConfigData().byType == E_ITEM_USE_EQUIP_PATCH||
                iter->second->GetConfigData().byType == E_ITEM_USE_EMBLEM_PATCH)
            {
                g_ItemData->DelPetChipIndex(dwIndex);
            }
            else
            {
                g_ItemData->DelIndexFromShowVector(dwIndex);
            }
            delete iter->second;
            iter->second = NULL;
            m_mapItemPacket.erase(iter);
            return;
        }
        iter->second->SetCount(dwCount);
    }
    else
    {
        CCLOG("Update item count error: can't find this item_%u.", dwIndex);
    }
}

uint32 CPacketDataMgr::GetItemCountByIndex(uint32 dwIndex)
{
    map<uint32, CItem*>::iterator iter = m_mapItemPacket.find(dwIndex);
    if (iter != m_mapItemPacket.end())
    {
        return iter->second->GetCount();
    }
    else
    {
        CCLOG("Get Item count error: can't find this item_%u.", dwIndex);
        return 0;
    }
}

string CPacketDataMgr::GetItemIconByIndex(uint32 dwIndex)
{
    string path = PIC_DEFAULT;
    ItemConfig::STC_ITEM_CONFIG* pItemConfig = GET_CONFIG_STC(ItemConfig, dwIndex);
    if (pItemConfig)
    {
        path = GET_ITEM_ICON(pItemConfig->dwIconId);
        
        CCTexture2D *t2d = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
        if (!t2d) {
            path = PIC_DEFAULT;
        }
    }

    return path;
}

//=======装备=========}

bool CPacketDataMgr::AddNewEquipToMap(const CEquip* pEquip)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(pEquip->GetKeyID());
    if (iter == m_mapEquipPacket.end())
    {
        m_mapEquipPacket.insert(make_pair(pEquip->GetKeyID(), const_cast<CEquip*>(pEquip)));
        g_EquipData->AddShowEquipKeyID(pEquip->GetKeyID());
        return true;
    }
    else
    {
        CCLOG("Add new equip error: equip KeyID_%u, Index_%u have been existed.", pEquip->GetKeyID(), pEquip->GetIndex());
        return false;//外部获得false记得delete}
    }
}

void CPacketDataMgr::ClearEquipMap()
{
    m_mapEquipPacket.clear();
    g_EquipData->ClearShowEquipKeyID();
}

const CEquip* CPacketDataMgr::GetEquipInfoByKeyID(uint32 dwKeyID)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        return iter->second;
    }
    else
    {
        CCLOG("Get equip info error: can't find this equip, KeyID_%u.", dwKeyID);
        return NULL;
    }
}

const void CPacketDataMgr::DelEquipByKeyID(uint32 dwKeyID)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        delete iter->second;
        iter->second = NULL;
        m_mapEquipPacket.erase(iter);
        g_EquipData->DelKeyIDFormEquipShowVector(dwKeyID);
    }
    else
    {
        CCLOG("Delete equip Error: Can't find this equip KeyID_%u", dwKeyID);
    }
}

string CPacketDataMgr::GetEquipIconByIndex(uint32 dwIndex)
{
    string path = PIC_DEFAULT;
    EquipNewConfig::STC_EQUIP_CONFIG* pEquipConfig = GET_CONFIG_STC(EquipNewConfig, dwIndex);
    if (pEquipConfig)
    {
//        return GET_ITEM_ICON(pEquipConfig->dwIcon);
        path = GET_ITEM_ICON(pEquipConfig->dwIcon);
        
        CCTexture2D *t2d = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
        if (!t2d) {
            path = PIC_DEFAULT;
        }
    }
    
    return path;
}

uint32 CPacketDataMgr::GetAllEquipsCountByIndex(uint32 dwIndex)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.begin();
    int nCount = 0;
    for (; iter != m_mapEquipPacket.end(); iter++)
    {
        if (iter->second->GetIndex() == dwIndex)
        {
            nCount++;
        }
    }
    return nCount;
}

void CPacketDataMgr::EquipPropertyUpdate(uint32 dwEquipKeyID, WorldPacket& packet)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwEquipKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        CEquip* equip = iter->second;
        CDynamicStruct DynamicStruct;
        DynamicStruct.loadDataLoose(packet);
        map<CDynamicStruct::key_type, AnyType> mapData;
        DynamicStruct.toMap(mapData);
        
        for (map<CDynamicStruct::key_type, AnyType>::iterator iter = mapData.begin(); iter != mapData.end(); ++iter)
        {
            switch (iter->first)
            {
                case E_EQUIP_dwIndex:
                    equip->SetIndex(DynamicStruct.getProperty(E_EQUIP_dwIndex).get<uint32>());
                    break;
                case E_EQUIP_byLv:
                    equip->SetLevel( DynamicStruct.getProperty(E_EQUIP_byLv).get<uint8>());
                    break;
                case E_EQUIP_dwWearPetId:
                    equip->SetWearPetID( DynamicStruct.getProperty(E_EQUIP_dwWearPetId).get<uint32>());
                    break;
                case E_EQUIP_dwRunes1:
                    equip->SetRune1( DynamicStruct.getProperty(E_EQUIP_dwRunes1).get<uint32>());
                    break;
                case E_EQUIP_dwRunes2:
                    equip->SetRune2( DynamicStruct.getProperty(E_EQUIP_dwRunes2).get<uint32>());
                    break;
                case E_EQUIP_dwRunesCnt:
                    equip->SetRunesCnt( DynamicStruct.getProperty(E_EQUIP_dwRunesCnt).get<uint32>());
                    break;
                case E_EQUIP_dwAddHp:
                    equip->SetHP( DynamicStruct.getProperty(E_EQUIP_dwAddHp).get<uint32>());
                    break;
                case E_EQUIP_dwAddCA:
                    equip->SetCAtk( DynamicStruct.getProperty(E_EQUIP_dwAddCA).get<uint32>());
                    break;
                case E_EQUIP_dwAddCD:
                    equip->SetCDef( DynamicStruct.getProperty(E_EQUIP_dwAddCD).get<uint32>());
                    break;
                case E_EQUIP_dwAddRev:
                    equip->SetRev( DynamicStruct.getProperty(E_EQUIP_dwAddRev).get<uint32>());
                    break;
                case E_EQUIP_dwAddSA:
                    equip->SetSAtk( DynamicStruct.getProperty(E_EQUIP_dwAddSA).get<uint32>());
                    break;
                case E_EQUIP_dwAddSD:
                    equip->SetSDef( DynamicStruct.getProperty(E_EQUIP_dwAddSD).get<uint32>());
                    break;
                    
                case E_EQUIP_dwAddCrit:
                    equip->SetCrit( DynamicStruct.getProperty(E_EQUIP_dwAddCrit).get<uint32>());
                    break;
                case E_EQUIP_dwAddSpeed:
                    equip->SetSpeed( DynamicStruct.getProperty(E_EQUIP_dwAddSpeed).get<uint32>());
                    break;
                case E_EQUIP_dwAddDodge:
                    equip->SetDodge( DynamicStruct.getProperty(E_EQUIP_dwAddDodge).get<uint32>());
                    break;
                case E_EQUIP_dwAddHit:
                    equip->SetHit( DynamicStruct.getProperty(E_EQUIP_dwAddHit).get<uint32>());
                    break;
                case E_EQUIP_dwAddCritDamage:
                    equip->SetCritDamage( DynamicStruct.getProperty(E_EQUIP_dwAddCritDamage).get<uint32>());
                    break;
                case E_EQUIP_dwAddCritFree:
                    equip->SetCritFree( DynamicStruct.getProperty(E_EQUIP_dwAddCritFree).get<uint32>());
                    break;
                    
                case E_EQUIP_dwAddAllAtk:
                    equip->SetAllAtk( DynamicStruct.getProperty(E_EQUIP_dwAddAllAtk).get<uint32>());
                    break;
                default:
                    break;
            }
        }
        
        iter->second->AddConfigData();
    }
    else
    {
        CCLOG("Update equip Error: Can't find this equip KeyID_%u", dwEquipKeyID);
    }
}

//进化，重新刷新装备的Index}
bool CPacketDataMgr::UpdateEquipIndex(uint32 dwEquipKeyID, uint32 dwIndex)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwEquipKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        iter->second->SetIndex(dwIndex);
        iter->second->AddConfigData();
        return true;
    }
    else
    {
        CCLOG("Update equip index Error: Can't find this equip KeyID_%u", dwEquipKeyID);
        return false;
    }
}

//强化，改变装备等级}
bool CPacketDataMgr::UpdateEquipLevel(uint32 dwEquipKeyID, uint8 byLv)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwEquipKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        iter->second->SetLevel(byLv);
        return true;
    }
    else
    {
        CCLOG("Update equip level Error: Can't find this equip KeyID_%u", dwEquipKeyID);
        return false;
    }
}

//穿着卸下装备，更新对应的宠物KeyID}
bool CPacketDataMgr::UpdateEquipWearPetID(uint32 dwEquipKeyID, uint32 dwPetID)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwEquipKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        iter->second->SetWearPetID(dwPetID);
        return true;
    }
    else
    {
        CCLOG("Update equip wearPetID Error: Can't find this equip KeyID_%u", dwEquipKeyID);
        return false;
    }
}

//镶嵌，更新装备开孔数}
bool CPacketDataMgr::UpdateEquipRuneCount(uint32 dwEquipKeyID, uint32 dwRuneCount)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwEquipKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        iter->second->SetRunesCnt(dwRuneCount);
        return true;
    }
    else
    {
        CCLOG("Update equip runeCount Error: Can't find this equip KeyID_%u", dwEquipKeyID);
        return false;
    }
}

//镶嵌，更新装备对应位置上镶嵌的符文}
bool CPacketDataMgr::UpdateEquipRune(uint32 dwEquipKeyID, uint32 dwRuneKeyID, int nPos)
{
    map<uint32, CEquip*>::iterator iter = m_mapEquipPacket.find(dwEquipKeyID);
    if (iter != m_mapEquipPacket.end())
    {
        if (nPos == 1)
        {
            iter->second->SetRune1(dwRuneKeyID);
        }
        else
        {
            iter->second->SetRune2(dwRuneKeyID);
        }
        return true;
    }
    else
    {
        CCLOG("Update equip rune Error: Can't find this equip KeyID_%u", dwEquipKeyID);
        return false;
    }
}

//========符文===========}

bool CPacketDataMgr::AddNewRuneToMap(const CRune* pRune)
{
    map<uint32, CRune*>::iterator iter = m_mapRunePacket.find(pRune->GetIndex());
    if (iter == m_mapRunePacket.end())
    {
        m_mapRunePacket.insert(make_pair(pRune->GetIndex(), const_cast<CRune*>(pRune)));
        g_EquipData->AddShowRuneKeyID(pRune->GetIndex());
        return true;
    }
    else
    {
        CCLOG("Add new rune error: rune KeyID_%u, Index_%u have been existed.", pRune->GetIndex(), pRune->GetIndex());
        return false;//外部获得false记得delete}
    }
}

void CPacketDataMgr::ClearRuneMap()
{
    m_mapRunePacket.clear();
    g_EquipData->ClearShowRuneKeyID();
}

void CPacketDataMgr::DelRuneByKeyID(uint32 dwKeyID)
{
    map<uint32, CRune*>::iterator iter = m_mapRunePacket.find(dwKeyID);
    if (iter != m_mapRunePacket.end())
    {
        delete iter->second;
        iter->second = NULL;
        m_mapRunePacket.erase(iter);
        g_EquipData->DelKeyIDFormRuneShowVector(dwKeyID);
    }
    else
    {
        CCLOG("Delete rune Error: Can't find this rune KeyID_%u", dwKeyID);
    }
}

const CRune* CPacketDataMgr::GetRuneInfoByKeyID(uint32 dwKeyID)
{
    map<uint32, CRune*>::iterator iter = m_mapRunePacket.find(dwKeyID);
    if (iter != m_mapRunePacket.end())
    {
        return iter->second;
    }
    else
    {
        CCLOG("Get rune info error: can't find this rune, KeyID_%u.", dwKeyID);
        return NULL;
    }
}

int CPacketDataMgr::GetAllRunesCountByIndex(uint32 dwIndex)
{
    map<uint32, CRune*>::iterator iter = m_mapRunePacket.begin();
    int nCount = 0;
    for (; iter != m_mapRunePacket.end(); iter++)
    {
        if (iter->second->GetIndex() == dwIndex)
        {
            nCount++;
        }
    }
    return nCount;
}

int CPacketDataMgr::GetRunesCountWithoutInlayByIndex(uint32 dwIndex)
{
    map<uint32, CRune*>::iterator iter = m_mapRunePacket.begin();
    int nCount = 0;
    for (; iter != m_mapRunePacket.end(); iter++)
    {
        if (iter->second->GetIndex() == dwIndex)
        {
            nCount++;
        }
    }
    return nCount;
}

int CPacketDataMgr::GetRuneCountByIndex(uint32 dwIndex)
{
    const CRune *rune = g_PacketDataMgr->GetRuneInfoByKeyID(dwIndex);
    if (rune) {
        return rune->GetCnt();
    }
    return 0;
}

bool CPacketDataMgr::UpdateRuneWearEquipID(uint32 dwRuneKeyID,uint32 dwEquipKeyID)
{
    map<uint32, CRune*>::iterator iter = m_mapRunePacket.find(dwRuneKeyID);
    if (iter != m_mapRunePacket.end())
    {
//        iter->second->SetWearEquipID(dwEquipKeyID);
        iter->second->SetCnt(dwEquipKeyID);
        return true;
    }
    else
    {
        CCLOG("Update rune wearEquipID: Can't find this rune KeyID_%u", dwRuneKeyID);
        return false;
    }
}

string CPacketDataMgr::GetRuneIconByIndex(uint32 dwIndex)
{
    string path = PIC_DEFAULT;
    RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig, dwIndex);
    if (pRuneConfig)
    {
        path = GET_ITEM_ICON(pRuneConfig->dwIcon);
        
        CCTexture2D *t2d = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
        if (!t2d) {
            path = PIC_DEFAULT;
        }
    }
    
    return path;
}

string CPacketDataMgr::GetEmblemIconByIndex(uint32 dwIndex)
{
    string path = PIC_DEFAULT;
    EmblemConfig::STC_EMBLEM_CONFIG* cfg = GET_CONFIG_STC(EmblemConfig, dwIndex);
    if (cfg)
    {
        path = GET_EMBLEM_ICON(cfg->wIcon);
        
        CCTexture2D *t2d = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
        if (!t2d) {
            path = PIC_DEFAULT;
        }
    }
    
    return path;
}
//============通==用==============}

string CPacketDataMgr::GetObjectNameByIndex(uint32 dwIndex)
{
    int nObjectType = dwIndex / E_UNITE_BASE_FABIO;
    switch (nObjectType)
    {
        case E_UNITE_TYPE_PET:
        {
            PetConfig::STC_PET_CONFIG* pPetConfig = GET_CONFIG_STC(PetConfig, dwIndex);
            if (pPetConfig)
                return pPetConfig->strName;
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        case E_UNITE_TYPE_CHEST:
        {
            ItemConfig::STC_ITEM_CONFIG* pItemConfig = GET_CONFIG_STC(ItemConfig, dwIndex);
            if (pItemConfig)
                return pItemConfig->strName;
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            EquipNewConfig::STC_EQUIP_CONFIG* pEquipConfig = GET_CONFIG_STC(EquipNewConfig, dwIndex);
            if (pEquipConfig)
                return pEquipConfig->strName;
        }
            break;
        case E_UNITE_TYPE_RUNES:
        {
            RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig, dwIndex);
            if (pRuneConfig)
                return pRuneConfig->strName;
        }
            break;
        case E_UNITE_TYPE_GEM:
            
            break;
        case E_UNITE_TYPE_EMBLEM:
        {
            EmblemConfig::STC_EMBLEM_CONFIG* pEmblemConfig = GET_CONFIG_STC(EmblemConfig, dwIndex);
            if (pEmblemConfig)
                return pEmblemConfig->strName;
        }
            break;
        default:
            break;
    }
    CCLOG("Get object_%u name error.", dwIndex);
    return "";
}

string CPacketDataMgr::GetObjectIconByIndex(uint32 dwIndex)
{
    int nObjectType = dwIndex / E_UNITE_BASE_FABIO;
    switch (nObjectType)
    {
        case E_UNITE_TYPE_PET:
        {
            return GET_PET_HEAD(dwIndex);
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        case E_UNITE_TYPE_CHEST:
        {
            return GetItemIconByIndex(dwIndex);
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            return GetEquipIconByIndex(dwIndex);
        }
            break;
        case E_UNITE_TYPE_RUNES:
        {
            return GetRuneIconByIndex(dwIndex);
        }
            break;
        
        case E_UNITE_TYPE_GEM:
            break;
        case E_UNITE_TYPE_EMBLEM:
        {
            return GetEmblemIconByIndex(dwIndex);
        }
            break;
        default:
            break;
    }
    return PIC_DEFAULT;
}

string CPacketDataMgr::GetObjectDescByIndex(uint32 dwIndex)
{
    int nObjectType = dwIndex / E_UNITE_BASE_FABIO;
    switch (nObjectType)
    {
        case E_UNITE_TYPE_PET:
        {
            PetConfig::STC_PET_CONFIG* pPetConfig = GET_CONFIG_STC(PetConfig, dwIndex);
            if (pPetConfig)
                return pPetConfig->strDes;
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        case E_UNITE_TYPE_CHEST:
        {
            ItemConfig::STC_ITEM_CONFIG* pItemConfig = GET_CONFIG_STC(ItemConfig, dwIndex);
            if (pItemConfig)
                return pItemConfig->strDesc;
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            EquipNewConfig::STC_EQUIP_CONFIG* pEquipConfig = GET_CONFIG_STC(EquipNewConfig, dwIndex);
            if (pEquipConfig)
                return pEquipConfig->strDesc;
        }
            break;
        case E_UNITE_TYPE_RUNES:
        {
            RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig, dwIndex);
            if (pRuneConfig)
                return pRuneConfig->strDesc;
        }
            break;
        case E_UNITE_TYPE_GEM:
            
            break;
        case E_UNITE_TYPE_EMBLEM:
        {
            EmblemConfig::STC_EMBLEM_CONFIG* pEmblemConfig = GET_CONFIG_STC(EmblemConfig, dwIndex);
            if (pEmblemConfig)
                return pEmblemConfig->strDes;
        }
            break;
        default:
            break;
    }
    CCLOG("Get object_%u description error.", dwIndex);
    return "";
}

uint32 CPacketDataMgr::GetObjectCountByIndex(uint32 dwIndex)
{
    int nObjectType = dwIndex / E_UNITE_BASE_FABIO;
    switch (nObjectType)
    {
        case E_UNITE_TYPE_PET:
        {
            return CPetCtrl::Get()->getPetNumByIndex(dwIndex);
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        case E_UNITE_TYPE_CHEST:
        {
            return GetItemCountByIndex(dwIndex);
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            return GetAllEquipsCountByIndex(dwIndex);
        }
            break;
        case E_UNITE_TYPE_RUNES:
        {
            return GetAllRunesCountByIndex(dwIndex);
        }
            break;
        case E_UNITE_TYPE_GEM:
            
            break;
        case E_UNITE_TYPE_EMBLEM:
        {

        }
            break;
        default:
            break;
    }
    
    return 0;
}

uint8 CPacketDataMgr::getObjectQualityByIndex(uint32 dwIndex)
{
    int nObjectType = dwIndex / E_UNITE_BASE_FABIO;
    switch (nObjectType)
    {
        case E_UNITE_TYPE_PET:
        {
            PetConfig::STC_PET_CONFIG* cfg = GET_CONFIG_STC(PetConfig, dwIndex);
            if (cfg) {
                if (cfg->byStarLv <= 2){
                    return 1;
                }
                else if (cfg->byStarLv == 3){
                    return 2;
                }
                else if (cfg->byStarLv == 4){
                    return 3;
                }
                else {
                    return 4;
                }
            }
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        {
            ItemConfig::STC_ITEM_CONFIG* cfg = GET_CONFIG_STC(ItemConfig, dwIndex);
            if (cfg)
            {
                if (cfg->byQuality <= 2) {
                    return 0;
                }
                if (cfg->byQuality == 3) {
                    return 1;
                }
                else if (cfg->byQuality == 4) {
                    return 2;
                }
                else if (cfg->byQuality == 5) {
                    return 3;
                }
                else {
                    return 4;
                }
            }
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            EquipNewConfig::STC_EQUIP_CONFIG* pEquipConfig = GET_CONFIG_STC(EquipNewConfig, dwIndex);
            if (pEquipConfig)
                return pEquipConfig->byQuality;
        }
            break;
        case E_UNITE_TYPE_RUNES:
            return 2;
            break;
        case E_UNITE_TYPE_CHEST:
            
            break;
        case E_UNITE_TYPE_GEM:
            
            break;
        
        case E_UNITE_TYPE_EMBLEM:
        {
            EmblemConfig::STC_EMBLEM_CONFIG* pEmblemConfig = GET_CONFIG_STC(EmblemConfig, dwIndex);
            if (pEmblemConfig)
            {
                if (pEmblemConfig->byStarLv <= 2) {
                    return 0;
                }
                if (pEmblemConfig->byStarLv == 3) {
                    return 1;
                }
                else if (pEmblemConfig->byStarLv == 4) {
                    return 2;
                }
                else if (pEmblemConfig->byStarLv == 5) {
                    return 3;
                }
            }
//                return pEmblemConfig->strDes;
        }
            break;
        default:
            break;
    }
//    CCLOG("Get object_%u description error.", dwIndex);
    return 0;
}

//获取品质颜色
ccColor3B CPacketDataMgr::getQualityColor(uint8 quality)
{
    switch (quality) {
        case 0:
            return ccWHITE;
            break;
        case 1:
            return ccQuaGreen;
            break;
        case 2:
            return ccQuaBlue;
            break;
        case 3:
            return ccQuaPurple;
            break;
        case 4:
            return ccQuaOrange;
            break;
        default:
            return ccWHITE;
            break;
    }
}

std::string CPacketDataMgr::getAttrText(uint8 attr)
{
    std::string str = "";
    uint16 str_type = 0;
    
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
    
    switch (attr) {
        case E_ATTR_HP:
            str_type = Str_hp;
            break;
        case E_ATTR_CATT:
            str_type = Str_catk;
            break;
        case E_ATTR_CDEF:
            str_type = Str_cdef;
            break;
        case E_ATTR_REV:
            str_type = Str_rev;
            break;
        case E_ATTR_SATT:
            str_type = Str_satk;
            break;
        case E_ATTR_SDEF:
            str_type = Str_sdef;
            break;
            
        case E_ATTR_CRIT:
            str_type = Str_crit;
            break;
        case E_ATTR_HIT:
            str_type = Str_hit;
            break;
        case E_ATTR_SPEED:
            str_type = Str_speed;
            break;
        case E_ATTR_DODGE:
            str_type = Str_dodge;
            break;
        case E_ATTR_CRIT_HURT:
            str_type = Str_crit_hurt;
            break;
        case E_ATTR_CRIT_FREE:
            str_type = Str_crit_free;
            break;
            
        case E_ATTR_ALL_ATT:
            str_type = Str_atk;
            break;
        default:
            break;
    }
    
    if (str_type == 0) {
        return "";
    }

    str = GET_STR(str_type);
    
    return str;
}

CCSpriteFrame* CPacketDataMgr::getAttrTexture(uint8 attr)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/petshow/pic_property.plist");
    
    string framePath = CCString::createWithFormat("pro_%d.png", attr)->getCString();
    
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str());
}

uint8 CPacketDataMgr::getObjectStarByIndex(uint32 dwIndex)
{
    uint8 star = 0;
    
    int nObjectType = dwIndex / E_UNITE_BASE_FABIO;
    switch (nObjectType)
    {
        case E_UNITE_TYPE_PET:
        {
            PetConfig::STC_PET_CONFIG* pPetConfig = GET_CONFIG_STC(PetConfig, dwIndex);
            if (pPetConfig)
                star = pPetConfig->byStarLv;
        }
            break;
        case E_UNITE_TYPE_ITEM:
        case E_UNITE_TYPE_SPECIAL:
        case E_UNITE_TYPE_CHEST:
        {
            ItemConfig::STC_ITEM_CONFIG* pItemConfig = GET_CONFIG_STC(ItemConfig, dwIndex);
            if (pItemConfig)
                star =  pItemConfig->byQuality;
        }
            break;
        case E_UNITE_TYPE_EQUIP:
        {
            EquipNewConfig::STC_EQUIP_CONFIG* pEquipConfig = GET_CONFIG_STC(EquipNewConfig, dwIndex);
            if (pEquipConfig)
                star = pEquipConfig->byStar;
        }
            break;
        case E_UNITE_TYPE_RUNES:

            break;

        case E_UNITE_TYPE_GEM:
            
            break;
        case E_UNITE_TYPE_EMBLEM:
        {
            EmblemConfig::STC_EMBLEM_CONFIG* pEmblemConfig = GET_CONFIG_STC(EmblemConfig, dwIndex);
            if (pEmblemConfig)
                star = pEmblemConfig->byStarLv;
        }
            break;
        default:
            break;
    }
    
    return star;
}

//物品品质框}
CCSpriteFrame* CPacketDataMgr::getQualityFrameSF(uint8 quality)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/quality.plist");
    string framePath = CCString::createWithFormat("quality_%d.png", quality)->getCString();
   
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str());

}

//物品品质底纹}
CCSpriteFrame* CPacketDataMgr::getQualityBgSF(uint8 quality)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/quality.plist");
    string framePath = CCString::createWithFormat("quality_back_%d.png", quality)->getCString();
    
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str());
}

//物品星级Icon}
CCSpriteFrame* CPacketDataMgr::getStarSF(uint8 starLv)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/star.plist");
    
    string framePath = CCString::createWithFormat("star_%d.png", starLv)->getCString();
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str());
}

//判断对应位置是否有可用装备}
bool CPacketDataMgr::checkHasCanUseEquip(uint8 part, uint32 equipId)
{
    bool ret = false;
    const CEquip* equip = GetEquipInfoByKeyID(equipId);
    
    uint32 qua1 = 0;
    uint32 value1 = 0;
    if (equip)
    {
        qua1 = equip->GetConfigData().byQuality * 10000 + equip->GetLevel();
        value1 = equip->GetCAtk() + equip->GetSAtk() + equip->GetRev() + equip->GetHP() + equip->GetSAtk()+
        equip->GetSDef() + equip->GetCrit() / 100;
    }
    
    map<uint32, CEquip*>::iterator it = m_mapEquipPacket.begin();
    for (; it != m_mapEquipPacket.end(); it++) {
        if (!it->second ||
            it->second->GetConfigData().byPos != part) {
            continue;
        }
        if(g_EquipTeamData->checkEquipIsWear(it->first))
        {
            continue;
        }
        uint32 qua2 = 0;
        uint32 value2 = 0;
        const CEquip* pEquip2 = it->second;

        qua2 = pEquip2->GetConfigData().byQuality * 10000 + pEquip2->GetLevel();
        value2 = pEquip2->GetCAtk() + pEquip2->GetSAtk() + pEquip2->GetRev() + pEquip2->GetHP() + pEquip2->GetSAtk()+
        pEquip2->GetSDef() + pEquip2->GetCrit() / 100;

        if (qua1 < qua2 || (qua1 == qua2 && value2 > value1)) {
            return true;
        }
    }
    
    return ret;
}
//判断是否有可替换装备
bool CPacketDataMgr::checkHasCanChangeEquip(uint32 petObjId)
{
    bool ret = false;
    
    uint32 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_UNIT_EQUIP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        return ret;
    }
    
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(petObjId);
    if (!pet) {
        return ret;
    }
    uint8 bySite = CTeamCtrl::getSiteByPetId(petObjId);
    for (int i = 1; i <= 4; i++) {
        uint32 equipId = g_EquipTeamData->getEquipIdBySiteAPart(bySite, i-1);
        if (checkHasCanUseEquip(i, equipId)) {
            return true;
        }
    }
    
    return ret;
}

//获取天气图标
CCSpriteFrame* CPacketDataMgr::getWeatherSF(uint8 weather){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/pavilion/pavilion_weather.plist");
    
    string framePath = CCString::createWithFormat("weather_%d.png", weather)->getCString();
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(framePath.c_str());
}


//获取战斗中宠物狂
CCSpriteFrame* CPacketDataMgr::getBattleFrame(uint16 petId)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/battle/pet_frame.plist");
    uint8 qua = getObjectQualityByIndex(petId);
    CCString *str = CCString::createWithFormat("b_quality_%d.png", qua);
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
}
//获取竞技场中宠物狂
CCSpriteFrame* CPacketDataMgr::getArenaFrame(uint16 petId)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/battle/pet_frame.plist");
    uint8 qua = getObjectQualityByIndex(petId);
    CCString *str = CCString::createWithFormat("a_quality_%d.png", qua);
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
}

//获取队伍中宠物狂
CCSpriteFrame* CPacketDataMgr::getTeamFrame(uint16 petId)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/battle/pet_frame.plist");
    uint8 qua = getObjectQualityByIndex(petId);
    CCString *str = CCString::createWithFormat("t_quality_%d.png", qua);
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
}

//获取主界面中宠物狂
CCSpriteFrame* CPacketDataMgr::getMainFrame(uint16 petId)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/battle/pet_frame.plist");
    uint8 qua = getObjectQualityByIndex(petId);
    CCString *str = CCString::createWithFormat("m_quality_%d.png", qua);
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
}
