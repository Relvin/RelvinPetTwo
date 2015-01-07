//
//  ConfigGet.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-7-16.}
//
//

#ifndef __HelloWorld__ConfigGet__
#define __HelloWorld__ConfigGet__

#include "Defines.h"
#include "ConfigData.h"
#include "game_config.h"

class ConfigGet {
    
public:
    static uint32 GetPetModelId( uint32 dwPetFullId );
    static uint32 GetPetBaseId( uint32 dwPetFullId );

    static std::string GetResourcePic( uint32 dwPicId );
    static std::string GetResourceStringClient( uint32 dwId );
    
    static std::string GetPetHeadIcon( uint16 wPetId );
    static std::string GetItemIconByIndexID(uint32 wIndexID);
    
    static std::string GetSkillIconByIndexID(uint32 wIndexID);
    static std::string GetGemIconByIndexID(uint32 wIndexID);
    static std::string GetEquipIcon(uint32 dwIcon);
    static std::string GetRuneIcon(uint32 dwIcon);
    static std::string GetPetSound(uint16 wSoundId);
    
    static std::string GetArenaBadgePic(uint16 wIndexID);
    
    static std::string GetEmblemIcon(uint32 dwIcon);
    
    static std::string GetMusicPath(uint16 wMusicId);
    
    static std::string GetBattleNormalMusicPath(uint16 wMusicId);
    static std::string GetBattleBossMusicPath(uint16 wMusicId);
    
    static std::string GetBattleListEffPath(std::string effId);
};

#define GET_ERROR_STR(x) ConfigGet::GetResourceStringClient(10000+x).c_str()
#define GET_PIC(x) ConfigGet::GetResourcePic(x).c_str()
#define GET_STR(x) ConfigGet::GetResourceStringClient(x).c_str()
#define GET_PET_HEAD(x) ConfigGet::GetPetHeadIcon(x).c_str()
#define GET_ITEM_ICON(x) ConfigGet::GetItemIconByIndexID(x).c_str()
#define GET_SKILL_ICON(x) ConfigGet::GetSkillIconByIndexID(x).c_str()
#define GET_GEM_ICON(x) ConfigGet::GetGemIconByIndexID(x).c_str()
#define GET_EQUIP_ICON(x) ConfigGet::GetEquipIcon(x).c_str()
#define GET_RUNE_ICON(x) ConfigGet::GetRuneIcon(x).c_str()
#define GET_PET_SOUND(x) ConfigGet::GetPetSound(x).c_str()

#define GET_ARENA_BADGE_PIC(x) ConfigGet::GetArenaBadgePic(x).c_str()

#define GET_EMBLEM_ICON(x) ConfigGet::GetEmblemIcon(x).c_str()

#define GET_MUSIC(x) ConfigGet::GetMusicPath(x).c_str()
#define GET_BATTLE_NOR_MUSIC(x) ConfigGet::GetBattleNormalMusicPath(x).c_str()
#define GET_BATTLE_BOSS_MUSIC(x) ConfigGet::GetBattleBossMusicPath(x).c_str()

#define GET_BATTLE_LIST_EFF(x) ConfigGet::GetBattleListEffPath(x).c_str()

#endif /* defined(__HelloWorld__ConfigGet__) */
