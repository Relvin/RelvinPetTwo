//
//  ConfigGet.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-7-16.}
//
//

#include "ConfigGet.h"
#include "ResourceDefine.h"
#include "ConfigUtil.h"
#include "GlobalData.h"

uint32 ConfigGet::GetPetModelId( uint32 dwPetFullId )
{
    PetConfig::STC_PET_CONFIG *pConfig = GET_CONFIG_STC( PetConfig, dwPetFullId);// GetPetBaseId(dwPetFullId));
    if ( pConfig )
    {
        return pConfig->dwModelIndex;
    }
    return 0;
}

uint32 ConfigGet::GetPetBaseId( uint32 dwHeroFullId )
{
    return dwHeroFullId % 10000;
}

std::string ConfigGet::GetResourcePic(uint32 dwPicId)
{
    std::string strName;
    ResourcePicConfig::STC_CONFIG_RESOURCE_PIC *pConfig = GET_CONFIG_STC( ResourcePicConfig, dwPicId );
    if ( pConfig ) {
        return pConfig->strPicName;
    }
    return PIC_DEFAULT;
}

std::string ConfigGet::GetResourceStringClient(uint32 dwId) {
    std::string strText;
    ResourceStringClientConfig::STC_CONFIG_RESOURCE_STRING_CLIENT *pConfig = GET_CONFIG_STC( ResourceStringClientConfig, dwId );
    if ( pConfig ) {
        if (GlobalData::shared()->getVipSwitch()) {
            if (pConfig->strText.find("vip") != std::string::npos) {
                return "";
            }
        }
        
        return pConfig->strText;
    }
    return CUtil::StrFormat( "Error Id {0}", dwId, FORMAT_PARAM_END);
}

std::string ConfigGet::GetMusicPath(uint16 wMusicId)
{
    std::string strName;
    MusicConfig::STC_CONFIG_MUSIC* pMusicCfg = GET_CONFIG_STC(MusicConfig, wMusicId);
    if (pMusicCfg) {
        return pMusicCfg->strPath;
    }
    return "";
}

std::string ConfigGet::GetBattleNormalMusicPath(uint16 wMusicId)
{
    return  CUtil::StrFormat( BATTLE_NOR_BGM , wMusicId, FORMAT_PARAM_END );
}

std::string ConfigGet::GetBattleBossMusicPath(uint16 wMusicId)
{
    return  CUtil::StrFormat( BATTLE_BOSS_BGM , wMusicId, FORMAT_PARAM_END );
}

std::string ConfigGet::GetPetHeadIcon( uint16 wPetId )
{
    return  CUtil::StrFormat( PET_HEAD , 10000 + wPetId, FORMAT_PARAM_END );
}

std::string ConfigGet::GetItemIconByIndexID(uint32 wIndexID)
{
    return CUtil::StrFormat( ITEM_ICON, wIndexID, FORMAT_PARAM_END);
}

std::string ConfigGet::GetSkillIconByIndexID(uint32 wIndexID)
{
    return CUtil::StrFormat( SKILL_ICON, wIndexID, FORMAT_PARAM_END);
}

std::string ConfigGet::GetGemIconByIndexID(uint32 wIndexID)
{
    return CUtil::StrFormat( GEM_ICON, wIndexID, FORMAT_PARAM_END);
}

std::string ConfigGet::GetArenaBadgePic(uint16 wIndexID)
{
    return CUtil::StrFormat( ARENA_BADGE_PIC, wIndexID, FORMAT_PARAM_END);
}

std::string ConfigGet::GetEquipIcon(uint32 dwIcon)
{
    return CUtil::StrFormat( EQUIP_ICON, dwIcon, FORMAT_PARAM_END);
}

std::string ConfigGet::GetRuneIcon(uint32 dwIcon)
{
    return CUtil::StrFormat( RUNE_ICON, dwIcon, FORMAT_PARAM_END);
}

std::string ConfigGet::GetPetSound(uint16 wSoundId)
{
    return CUtil::StrFormat( PET_SOUND, wSoundId, FORMAT_PARAM_END);
}

std::string ConfigGet::GetEmblemIcon(uint32 dwIcon)
{
     return CUtil::StrFormat( EMBLEM_ICON, dwIcon, FORMAT_PARAM_END);
}

std::string ConfigGet::GetBattleListEffPath(std::string effId)
{
    char buf[256];
    sprintf(buf, BATTLE_LIST_EFF, effId.c_str());
    return buf;
}

