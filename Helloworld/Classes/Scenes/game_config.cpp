//
//  game_config.cpp
//  client
//
//  Created by 庆 尹 on 12-7-27.}
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.}
//

#include <iostream>
#include "game_config.h"
#include "ConfigGet.h"

namespace Client 
{
    ComboIdConfig               g_ComboidConfig;
    LeaderSkillConfig           g_LeaderSkillConfig;
    PassiveSkillConfig          g_PassiveSkillConfig;
    PetConfig                   g_PetConfig;
    PetExpConfig                g_PetExpConfig;
    SkillEffectConfig           g_SkillEffectConfig;
    UltimateSkillConfig         g_UltimateSkillConfig;
    ResourcePicConfig           g_ResourcePicConfig;
    EffectGroupConfig           g_EffectGroupConfig;
    TriggerConfig               g_TriggerConfig;
    SkillBuffConfig             g_SkillBuffConfig;
    ResourceStringClientConfig  g_ResourceStringClientConfig;
    InterPlayConfig             g_InterPlayConfig;
    PetModel                    g_PetModelConfig;
    MapConfig                   g_MapConfig;
    EvolveConfig                g_EvolveConfig;
    ItemConfig                  g_ItemConfig;
    GemConfig                   g_GemConfig;
    RankRewardConfig            g_RankRewardConfig;
    UserLvConfig                g_UserLvConfig;
//    EquipConfig                 g_EquipConfig;
    EquipNewConfig              g_EquipNewConfig;
    EquipEvoConfig              g_EquipEvoConfig;
    RuneConfig                  g_RuneConfig;
    EquipStrengthenConfig       g_EquipStrengthenConfig;
    EquipCompoundConfig         g_EquipCompoundConfig;
    TalentConfig                g_TalentConfig;
    UltimateSkillExpConfig      g_UltimateSkillExpConfig;
    AnimationEffectConfig       g_AnimationEffectConfig;
    SpecialMapConfig            g_SpecialMapConfig;
    GuideConfig                 g_GuideConfig;
    GuideButtonConfig           g_GuideButtonConfig;
    EventReward7Config          g_EventReward7Config;
    EventReward30Config         g_EventReward30Config;
    AchieveRewardConfig         g_AchieveRewardConfig;
    DailyQuestConfig            g_DailyQuestConfig;
    RandomNameConfig            g_RandomNameConfig;
    PetFuseConfig               g_PetFuseConfig;
    InviteConfig                g_InviteConfig;
    InviteeConfig               g_InviteeConfig;
    EpitasisConfig              g_EpitasisConfig;
    EvolveInfoConfig            g_EvolveInfoConfig;
    GrowPlanConfig              g_GrowPlanConfig;
    SystemDebLockingConfig      g_SystemDebLockingConfig;
    StageConfig                 g_StageConfig;
    StageHConfig                g_StageHConfig;
    StageShowConfig             g_StageShowConfig;
    VipShowConfig               g_VipShowConfig;
    ActiveStageConfig           g_ActiveStageConfig;
    ArenaRewardConfig           g_ArenaRewardConfig;
    FirstRechargeConfig         g_FirstRechargeConfig;
    ComboOffConfig              g_ComboOffConfig;
    EmblemConfig                g_EmblemConfig;
    ExpConfig                   g_ExpConfig;
    TowerConfig                 g_TowerConfig;
    SupportSkillConfig          g_SupportSkillConfig;
    ChallengeBuffConfig         g_ChallengeBuffConfig;
    ChallengeConfig             g_ChallengeConfig;
    StageBonusConfig            g_StageBonusConfig;
    MusicConfig                 g_MusicConfig;
    ArmatureConfig              g_ArmatureConfig;
    TipsConfig                  g_TipsConfig;
    VipBuyConfig                g_VipBuyConfig;
    PetLiuWeiConfig             g_PetLiuWeiConfig;
    MysteryShopConfig           g_MysteryShopConfig;
    ArenaShopConfig             g_ArenaShopConfig;
    DailyRewardConfig           g_DailyRewardConfig;
    ChestConfig                 g_ChestConfig;
    WorldBossInfoConfig         g_WorldBossInfoConfig;
    WorldBossRewardConfig       g_WorldBossRewardConfig;
    QingYuanConfig              g_QingYuanConfig;
    EmblemShowConfig            g_EmblemShowConfig;
    ShareConfig                 g_ShareConfig;
    EquipGroupConfig            g_EquipGroupConfig;
    
    std::map< std::string, ConfigBase* > g_ConfigMap;
    
    PetModel::STC_PET_MODEL_CONFIG* GetModelByPetId( uint32 dwPetId )
    {
        uint32 dwModelId = ConfigGet::GetPetModelId( dwPetId );
        if ( dwModelId == 0 )
        {
            IME_ERROR( "ModelId Not Found, id=%u", dwPetId );
            dwModelId = 1;
        }
        
        PetModel::STC_PET_MODEL_CONFIG *pPetModel = g_PetModelConfig.GetById(dwModelId);
        if ( pPetModel == NULL )
        {
            IME_ERROR( "ModelConfig Not Found, id=%u", dwModelId );
            return g_PetModelConfig.GetById( 1010 );
        }
        return pPetModel;
    }
}
