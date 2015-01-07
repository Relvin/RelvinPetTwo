//
//  GameStateManager.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-8-2.}
//
//

#include "GameStateManager.h"
#include "game_config.h"
#include "GlobalData.h"
#include "cocos2d.h"

#define LOAD_CSV( clz, config, path )    \
snprintf(strBuf64, BUFFER_SIZE_64, "config_c/%s", path);   \
config.Load( cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename( strBuf64 ).c_str() );   \
Client::g_ConfigMap[clz::GetName()] = &config;     \
CCLOG("%s",strBuf64);


GameStateManager* GameStateManager::sharedManager()
{
    static GameStateManager game_state_manager;
    return &game_state_manager;
}

#define RELOAD_CSV( clz, config, path )    \
snprintf(strBuf64, BUFFER_SIZE_64, "config_c/%s", path);    \
config.Reload( cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename( strBuf64 ).c_str() );    \
Client::g_ConfigMap[clz::GetName()] = &config;     \
CCLOG("Reload %s", strBuf64);    \

void GameStateManager::Reload() {
    Client::g_ConfigMap.clear();
    
    RELOAD_CSV(ComboIdConfig, Client::g_ComboidConfig, "comboid.csv" );
    RELOAD_CSV(LeaderSkillConfig, Client::g_LeaderSkillConfig, "leaderskill.csv" );
    RELOAD_CSV(PassiveSkillConfig, Client::g_PassiveSkillConfig, "passiveskill.csv" );
    RELOAD_CSV(PetConfig, Client::g_PetConfig, "pet.csv" );
    RELOAD_CSV(PetExpConfig, Client::g_PetExpConfig, "petexp.csv" );
    RELOAD_CSV(SkillEffectConfig, Client::g_SkillEffectConfig, "skilleffect.csv" );
    RELOAD_CSV(UltimateSkillConfig, Client::g_UltimateSkillConfig, "ultimateskill.csv" );
    RELOAD_CSV(ResourcePicConfig, Client::g_ResourcePicConfig, "resourcepic.csv" );
    RELOAD_CSV(EffectGroupConfig, Client::g_EffectGroupConfig, "effectgroup.csv" );
    RELOAD_CSV(SkillBuffConfig, Client::g_SkillBuffConfig, "skillbuff.csv" );
    RELOAD_CSV(TriggerConfig, Client::g_TriggerConfig, "trigger.csv" );
    RELOAD_CSV(ResourceStringClientConfig, Client::g_ResourceStringClientConfig, "resourcestringclient.csv"  );
    RELOAD_CSV(InterPlayConfig, Client::g_InterPlayConfig, "interplay.csv"  );
    RELOAD_CSV(MapConfig, Client::g_MapConfig, "map.csv" );
    RELOAD_CSV(ItemConfig, Client::g_ItemConfig, "item.csv" );
    RELOAD_CSV(GemConfig, Client::g_GemConfig, "jade.csv" );
    RELOAD_CSV(EvolveConfig, Client::g_EvolveConfig, "petevolve.csv" );
    RELOAD_CSV(RankRewardConfig, Client::g_RankRewardConfig, "arena_battleinfo.csv" );
    RELOAD_CSV(UserLvConfig, Client::g_UserLvConfig, "userlv.csv" );
//    RELOAD_CSV(EquipConfig, Client::g_EquipConfig, "equip.csv" );
    RELOAD_CSV(EquipNewConfig, Client::g_EquipNewConfig, "equip_new.csv" );
    RELOAD_CSV(EquipEvoConfig, Client::g_EquipEvoConfig, "equip_evo.csv" );
    RELOAD_CSV(RuneConfig, Client::g_RuneConfig, "rune.csv" );
    RELOAD_CSV(EquipStrengthenConfig, Client::g_EquipStrengthenConfig, "qianghua.csv" );
    RELOAD_CSV(EquipCompoundConfig, Client::g_EquipCompoundConfig, "equip_hecheng.csv" );
    RELOAD_CSV(TalentConfig, Client::g_TalentConfig, "talent.csv" );
    RELOAD_CSV(UltimateSkillExpConfig, Client::g_UltimateSkillExpConfig, "ultimateskill_exp.csv" );
    RELOAD_CSV(AnimationEffectConfig, Client::g_AnimationEffectConfig, "ani_effect.csv" );
    RELOAD_CSV(SpecialMapConfig, Client::g_SpecialMapConfig, "active_map.csv" );
    RELOAD_CSV(EventReward7Config, Client::g_EventReward7Config, "7day.csv" );
    RELOAD_CSV(EventReward30Config, Client::g_EventReward30Config, "30day.csv" );
    RELOAD_CSV(GuideConfig, Client::g_GuideConfig, "guide.csv" );
    RELOAD_CSV(GuideButtonConfig, Client::g_GuideButtonConfig, "guide_button.csv" );
    RELOAD_CSV(AchieveRewardConfig, Client::g_AchieveRewardConfig, "achieve.csv" );
    RELOAD_CSV(DailyQuestConfig, Client::g_DailyQuestConfig, "dailyquest.csv" );
    RELOAD_CSV(RandomNameConfig, Client::g_RandomNameConfig, "random_name.csv" );
    RELOAD_CSV(PetFuseConfig, Client::g_PetFuseConfig, "fuse.csv" );
    RELOAD_CSV(InviteConfig, Client::g_InviteConfig, "invite_reward.csv" );
    RELOAD_CSV(InviteeConfig, Client::g_InviteeConfig, "invitee_reward.csv" );
    RELOAD_CSV(EpitasisConfig, Client::g_EpitasisConfig, "checkpoint_epitasis.csv" );
    RELOAD_CSV(EvolveInfoConfig, Client::g_EvolveInfoConfig, "item_info.csv" );
    RELOAD_CSV(GrowPlanConfig, Client::g_GrowPlanConfig, "growup.csv" );
    RELOAD_CSV(SystemDebLockingConfig, Client::g_SystemDebLockingConfig, "system_deblocking.csv" );
    RELOAD_CSV(StageConfig, Client::g_StageConfig, "stage.csv" );
    RELOAD_CSV(StageHConfig, Client::g_StageHConfig, "stage_h.csv" );
    RELOAD_CSV(StageShowConfig, Client::g_StageShowConfig, "stageshow.csv" );
    RELOAD_CSV(VipShowConfig, Client::g_VipShowConfig, "vip.csv" );
    RELOAD_CSV(ActiveStageConfig, Client::g_ActiveStageConfig, "active_stage.csv" );
    RELOAD_CSV(ArenaRewardConfig, Client::g_ArenaRewardConfig, "arena_reward.csv" );
    RELOAD_CSV(FirstRechargeConfig, Client::g_FirstRechargeConfig, "first_recharge.csv" );
    RELOAD_CSV(ComboOffConfig, Client::g_ComboOffConfig, "combo_xy.csv" );
    RELOAD_CSV(EmblemConfig, Client::g_EmblemConfig, "emblem.csv" );
    RELOAD_CSV(ExpConfig, Client::g_ExpConfig, "exp.csv" );
    RELOAD_CSV(TowerConfig, Client::g_TowerConfig, "tower.csv" );
    RELOAD_CSV(ChallengeBuffConfig, Client::g_ChallengeBuffConfig, "challenge_buff.csv" );
    RELOAD_CSV(ChallengeConfig, Client::g_ChallengeConfig, "challenge.csv" );
    RELOAD_CSV(StageBonusConfig, Client::g_StageBonusConfig, "stage_bouns.csv" );
    RELOAD_CSV(MusicConfig, Client::g_MusicConfig, "music.csv" );
    RELOAD_CSV(ArmatureConfig, Client::g_ArmatureConfig, "armature.csv" );
    RELOAD_CSV(TipsConfig, Client::g_TipsConfig, "tips.csv" );
    RELOAD_CSV(VipBuyConfig, Client::g_VipBuyConfig, "vipbuy.csv" );
    RELOAD_CSV(PetLiuWeiConfig, Client::g_PetLiuWeiConfig, "pet_liuwei.csv" );
    RELOAD_CSV(MysteryShopConfig, Client::g_MysteryShopConfig, "mystery_shop.csv" );
    RELOAD_CSV(ArenaShopConfig, Client::g_ArenaShopConfig, "arena_shop.csv" );
    RELOAD_CSV(DailyRewardConfig, Client::g_DailyRewardConfig, "dailyreward.csv" );
    RELOAD_CSV(ChestConfig, Client::g_ChestConfig, "chest.csv");
    RELOAD_CSV(WorldBossInfoConfig, Client::g_WorldBossInfoConfig, "boss_info.csv" );
    RELOAD_CSV(WorldBossRewardConfig, Client::g_WorldBossRewardConfig, "boss_reward.csv" );
    RELOAD_CSV(QingYuanConfig, Client::g_QingYuanConfig, "qingyuan.csv" );
    RELOAD_CSV(EmblemShowConfig, Client::g_EmblemShowConfig, "qingyuan_show.csv" );
    RELOAD_CSV(ShareConfig, Client::g_ShareConfig, "share_reward.csv" );
    RELOAD_CSV(EquipGroupConfig, Client::g_EquipGroupConfig, "equip_group.csv" );
}

void GameStateManager::Initialize()
{
    Client::g_ConfigMap.clear();
    
    // 考虑到资源更新，必须使用蓝色文件夹，否则相对路径找不到更新的文件}
    
    LOAD_CSV(ComboIdConfig, Client::g_ComboidConfig, "comboid.csv" );
    LOAD_CSV(LeaderSkillConfig, Client::g_LeaderSkillConfig, "leaderskill.csv" );
    LOAD_CSV(PassiveSkillConfig, Client::g_PassiveSkillConfig, "passiveskill.csv" );
    LOAD_CSV(PetConfig, Client::g_PetConfig, "pet.csv" );
    LOAD_CSV(PetExpConfig, Client::g_PetExpConfig, "petexp.csv" );
    LOAD_CSV(SkillEffectConfig, Client::g_SkillEffectConfig, "skilleffect.csv" );
    LOAD_CSV(UltimateSkillConfig, Client::g_UltimateSkillConfig, "ultimateskill.csv" );
    LOAD_CSV(ResourcePicConfig, Client::g_ResourcePicConfig, "resourcepic.csv" );
    LOAD_CSV(EffectGroupConfig, Client::g_EffectGroupConfig, "effectgroup.csv" );
    LOAD_CSV(SkillBuffConfig, Client::g_SkillBuffConfig, "skillbuff.csv" );
    LOAD_CSV(TriggerConfig, Client::g_TriggerConfig, "trigger.csv" );
    LOAD_CSV(ResourceStringClientConfig, Client::g_ResourceStringClientConfig, "resourcestringclient.csv"  );
    LOAD_CSV(InterPlayConfig, Client::g_InterPlayConfig, "interplay.csv"  );
    LOAD_CSV(MapConfig, Client::g_MapConfig, "map.csv" );
    LOAD_CSV(ItemConfig, Client::g_ItemConfig, "item.csv" );
    LOAD_CSV(GemConfig, Client::g_GemConfig, "jade.csv" );
    LOAD_CSV(EvolveConfig, Client::g_EvolveConfig, "petevolve.csv" );
    LOAD_CSV(RankRewardConfig, Client::g_RankRewardConfig, "arena_battleinfo.csv" );
    LOAD_CSV(UserLvConfig, Client::g_UserLvConfig, "userlv.csv" );
//    LOAD_CSV(EquipConfig, Client::g_EquipConfig, "equip.csv" );
    LOAD_CSV(EquipNewConfig, Client::g_EquipNewConfig, "equip_new.csv" );
    LOAD_CSV(EquipEvoConfig, Client::g_EquipEvoConfig, "equip_evo.csv" );
    LOAD_CSV(RuneConfig, Client::g_RuneConfig, "rune.csv" );
    LOAD_CSV(EquipStrengthenConfig, Client::g_EquipStrengthenConfig, "qianghua.csv" );
    LOAD_CSV(EquipCompoundConfig, Client::g_EquipCompoundConfig, "equip_hecheng.csv" );
    LOAD_CSV(TalentConfig, Client::g_TalentConfig, "talent.csv" );
    LOAD_CSV(UltimateSkillExpConfig, Client::g_UltimateSkillExpConfig, "ultimateskill_exp.csv" );
    LOAD_CSV(AnimationEffectConfig, Client::g_AnimationEffectConfig, "ani_effect.csv" );
    LOAD_CSV(SpecialMapConfig, Client::g_SpecialMapConfig, "active_map.csv" );
    LOAD_CSV(EventReward7Config, Client::g_EventReward7Config, "7day.csv" );
    LOAD_CSV(EventReward30Config, Client::g_EventReward30Config, "30day.csv" );
    LOAD_CSV(GuideConfig, Client::g_GuideConfig, "guide.csv" );
    LOAD_CSV(GuideButtonConfig, Client::g_GuideButtonConfig, "guide_button.csv" );
    LOAD_CSV(AchieveRewardConfig, Client::g_AchieveRewardConfig, "achieve.csv" );
    LOAD_CSV(DailyQuestConfig, Client::g_DailyQuestConfig, "dailyquest.csv" );
    LOAD_CSV(RandomNameConfig, Client::g_RandomNameConfig, "random_name.csv" );
    LOAD_CSV(PetFuseConfig, Client::g_PetFuseConfig, "fuse.csv" );
    LOAD_CSV(InviteConfig, Client::g_InviteConfig, "invite_reward.csv" );
    LOAD_CSV(InviteeConfig, Client::g_InviteeConfig, "invitee_reward.csv" );
    LOAD_CSV(EpitasisConfig, Client::g_EpitasisConfig, "checkpoint_epitasis.csv" );
    LOAD_CSV(EvolveInfoConfig, Client::g_EvolveInfoConfig, "item_info.csv" );
    LOAD_CSV(GrowPlanConfig, Client::g_GrowPlanConfig, "growup.csv" );
    LOAD_CSV(SystemDebLockingConfig, Client::g_SystemDebLockingConfig, "system_deblocking.csv" );
    LOAD_CSV(StageConfig, Client::g_StageConfig, "stage.csv" );
    LOAD_CSV(StageHConfig, Client::g_StageHConfig, "stage_h.csv" );
    LOAD_CSV(StageShowConfig, Client::g_StageShowConfig, "stageshow.csv" );
    LOAD_CSV(VipShowConfig, Client::g_VipShowConfig, "vip.csv" );
    LOAD_CSV(ActiveStageConfig, Client::g_ActiveStageConfig, "active_stage.csv" );
    LOAD_CSV(ArenaRewardConfig, Client::g_ArenaRewardConfig, "arena_reward.csv" );
    LOAD_CSV(FirstRechargeConfig, Client::g_FirstRechargeConfig, "first_recharge.csv" );
    LOAD_CSV(ComboOffConfig, Client::g_ComboOffConfig, "combo_xy.csv" );
    LOAD_CSV(EmblemConfig, Client::g_EmblemConfig, "emblem.csv" );
    LOAD_CSV(ExpConfig, Client::g_ExpConfig, "exp.csv" );
    LOAD_CSV(TowerConfig, Client::g_TowerConfig, "tower.csv" );
    LOAD_CSV(ChallengeBuffConfig, Client::g_ChallengeBuffConfig, "challenge_buff.csv" );
    LOAD_CSV(ChallengeConfig, Client::g_ChallengeConfig, "challenge.csv" );
    LOAD_CSV(StageBonusConfig, Client::g_StageBonusConfig, "stage_bouns.csv" );
    LOAD_CSV(MusicConfig, Client::g_MusicConfig, "music.csv" );
    LOAD_CSV(ArmatureConfig, Client::g_ArmatureConfig, "armature.csv" );
    LOAD_CSV(TipsConfig, Client::g_TipsConfig, "tips.csv" );
    LOAD_CSV(VipBuyConfig, Client::g_VipBuyConfig, "vipbuy.csv" );
    LOAD_CSV(PetLiuWeiConfig, Client::g_PetLiuWeiConfig, "pet_liuwei.csv" );
    LOAD_CSV(MysteryShopConfig, Client::g_MysteryShopConfig, "mystery_shop.csv" );
    LOAD_CSV(ArenaShopConfig, Client::g_ArenaShopConfig, "arena_shop.csv" );
    LOAD_CSV(DailyRewardConfig, Client::g_DailyRewardConfig, "dailyreward.csv" );
    LOAD_CSV(ChestConfig, Client::g_ChestConfig, "chest.csv");
    LOAD_CSV(WorldBossInfoConfig, Client::g_WorldBossInfoConfig, "boss_info.csv" );
    LOAD_CSV(WorldBossRewardConfig, Client::g_WorldBossRewardConfig, "boss_reward.csv" );
    LOAD_CSV(QingYuanConfig, Client::g_QingYuanConfig, "qingyuan.csv" );
    LOAD_CSV(EmblemShowConfig, Client::g_EmblemShowConfig, "qingyuan_show.csv" );
    LOAD_CSV(ShareConfig, Client::g_ShareConfig, "share_reward.csv" );
    LOAD_CSV(EquipGroupConfig, Client::g_EquipGroupConfig, "equip_group.csv" );
}




