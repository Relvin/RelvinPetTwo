//
//  game_config.h
//  client
//
//  Created by 庆 尹 on 12-7-27.}
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.}
//

#ifndef client_game_config_h
#define client_game_config_h

#include "ConfigData.h"
#include "PropertyList.h"
#include "ResourceStringConverter.h"

namespace Client 
{
    extern ComboIdConfig            g_ComboidConfig;
    extern LeaderSkillConfig        g_LeaderSkillConfig;
    extern PassiveSkillConfig       g_PassiveSkillConfig;
    extern PetConfig                g_PetConfig;
    extern PetExpConfig             g_PetExpConfig;
    extern SkillEffectConfig        g_SkillEffectConfig;
    extern UltimateSkillConfig      g_UltimateSkillConfig;
    extern ResourcePicConfig        g_ResourcePicConfig;
    extern EffectGroupConfig        g_EffectGroupConfig;
    extern TriggerConfig            g_TriggerConfig;
    extern SkillBuffConfig          g_SkillBuffConfig;
    extern ResourceStringClientConfig g_ResourceStringClientConfig;
    extern InterPlayConfig          g_InterPlayConfig;
    extern PetModel                 g_PetModelConfig;
    extern MapConfig                g_MapConfig;
    extern EvolveConfig             g_EvolveConfig;
    extern ItemConfig               g_ItemConfig;
    extern RankRewardConfig         g_RankRewardConfig;
    extern GemConfig                g_GemConfig;
    extern UserLvConfig             g_UserLvConfig;
//    extern EquipConfig              g_EquipConfig;
    extern EquipNewConfig           g_EquipNewConfig;
    extern EquipEvoConfig           g_EquipEvoConfig;
    extern RuneConfig               g_RuneConfig;
    extern EquipStrengthenConfig    g_EquipStrengthenConfig;
    extern EquipCompoundConfig      g_EquipCompoundConfig;
    extern TalentConfig             g_TalentConfig;
    extern UltimateSkillExpConfig   g_UltimateSkillExpConfig;
    extern AnimationEffectConfig    g_AnimationEffectConfig;
    extern SpecialMapConfig         g_SpecialMapConfig;
    extern EventReward7Config       g_EventReward7Config;
    extern EventReward30Config      g_EventReward30Config;
    extern GuideConfig              g_GuideConfig;
    extern GuideButtonConfig        g_GuideButtonConfig;
    extern AchieveRewardConfig      g_AchieveRewardConfig;
    extern DailyQuestConfig         g_DailyQuestConfig;
    extern RandomNameConfig         g_RandomNameConfig;
    extern PetFuseConfig            g_PetFuseConfig;
    extern InviteConfig             g_InviteConfig;
    extern InviteeConfig            g_InviteeConfig;
    extern EpitasisConfig           g_EpitasisConfig;
    extern EvolveInfoConfig         g_EvolveInfoConfig;
    extern GrowPlanConfig           g_GrowPlanConfig;
    extern SystemDebLockingConfig   g_SystemDebLockingConfig;
    extern StageConfig              g_StageConfig;
    extern StageHConfig             g_StageHConfig;
    extern StageShowConfig          g_StageShowConfig;
    extern VipShowConfig            g_VipShowConfig;
    extern ActiveStageConfig        g_ActiveStageConfig;
    extern ArenaRewardConfig        g_ArenaRewardConfig;
    extern FirstRechargeConfig      g_FirstRechargeConfig;
    extern ComboOffConfig           g_ComboOffConfig;
    extern EmblemConfig             g_EmblemConfig;
    extern ExpConfig                g_ExpConfig;
    extern TowerConfig              g_TowerConfig;
    extern SupportSkillConfig       g_SupportSkillConfig;
    extern ChallengeBuffConfig      g_ChallengeBuffConfig;
    extern ChallengeConfig          g_ChallengeConfig;
    extern StageBonusConfig         g_StageBonusConfig;
    extern MusicConfig              g_MusicConfig;
    extern ArmatureConfig           g_ArmatureConfig;
    extern TipsConfig               g_TipsConfig;
    extern VipBuyConfig             g_VipBuyConfig;
    extern PetLiuWeiConfig          g_PetLiuWeiConfig;
    extern MysteryShopConfig        g_MysteryShopConfig;
    extern ArenaShopConfig          g_ArenaShopConfig;
    extern DailyRewardConfig        g_DailyRewardConfig;
    extern ChestConfig              g_ChestConfig;
    extern WorldBossInfoConfig      g_WorldBossInfoConfig;
    extern WorldBossRewardConfig    g_WorldBossRewardConfig;
    extern QingYuanConfig           g_QingYuanConfig;
    extern EmblemShowConfig         g_EmblemShowConfig;
    extern ShareConfig              g_ShareConfig;
    extern EquipGroupConfig         g_EquipGroupConfig;
    
    extern std::map< std::string, ConfigBase* > g_ConfigMap;
    extern PetModel::STC_PET_MODEL_CONFIG* GetModelByPetId( uint32 dwPetId );

	//BuildingConfig::STC_BUILDING_CONFIG* config = g_building_config.GetById( 13 );
    
}

#endif
