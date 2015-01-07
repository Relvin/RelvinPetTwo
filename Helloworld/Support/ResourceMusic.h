//
//  ResourceMusic.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-8-18.}
//
//

#ifndef MyGame_ResourceMusic_h
#define MyGame_ResourceMusic_h

enum {
    Bgm_start               = 1,    //"music/main_title.mp3"
    Bgm_arena               = 2,    //"music/arena.mp3"
    Bgm_activity_normal     = 3,    //"music/battle_normal_02.mp3"
    Bgm_activity_boss       = 4,    //"music/battle_boss_02.mp3"
    Bgm_new_4select1        = 5,    //"music/pet_4select1.mp3"
    Eff_next                = 6,    //"music/ui_next.mp3"
    Eff_return              = 7,    //"music/ui_return.mp3"
    Eff_boss_show           = 8,    //"music/AlarmSound.wav"
    Eff_pve_win             = 9,    //"music/battle_victory.wav"
    Eff_pve_lose            = 10,   //"music/battle_lose.mp3"
    Eff_player_lv_up        = 11,   //"music/ui_playerlvup.mp3"
    Eff_pet_upgrade         = 12,   //"music/pet_upgrade.wav"
    Eff_pet_lv_up           = 13,   //"music/pet_lvup.mp3"
    Eff_pet_evolve          = 14,   //"music/pet_evolve.mp3"
    Eff_open_pack           = 15,   //"music/ui_openpack.mp3"
    Eff_armor_upgrade       = 16,   //"music/armor_upgrade.mp3"
    Eff_rune_beset          = 17,   //"music/rune_beset.mp3"
    Eff_buy_good            = 18,   //"music/ui_gold.wav"
    Eff_pet_fuse            = 19,   //"music/ui_pet2fs.mp3"
    /*!
     * 装备融合}
     */
    Eff_armor_fuse          = 20,   //"music/ui_armor2rune.mp3"
    /*!
     * 符文合成}
     */
    Eff_rune_compose        = 21,   //"music/ui_rune_fusion.wav"
    Eff_arena_win           = 22,   //"music/arena_victory.wav"
    Eff_arena_lose          = 23,   //"music/arena_lose.wav"
    Eff_get_reward          = 24,   //"music/ui_getbigreward.wav"
    Eff_gacha_pet           = 25,   //"music/get_new_pet.mp3"
    Eff_confirm             = 26,   //"music/confirm.wav"
    Eff_egg_show            = 27,   //"music/danfeichu.wav"
    Eff_rare                = 28,   //"music/BLevelEffect.wav"
    Eff_more_rare           = 29,   //"music/ALevelEffect.wav"
    Eff_most_rare           = 30,   //"music/SLevelEffect.wav"
    Eff_rank_up             = 31,   //"music/rankup.wav"
    Bgm_stage_normal        = 32,   //"music/bgm_battle.mp3"
    Bgm_main_scene          = 33,   //"music/bgm_main.mp3"
    Eff_pickup              = 45,	//拿起精灵	ui_pickup.wav}
    Eff_pet_change          = 46,	//交换精灵	ui_change.wav}
    Eff_putdown             = 47,	//放下精灵	ui_putdown.wav}
    Eff_battle_push_uskill  = 48,   //battle_push_uskill.wav
    Eff_ui_lock             = 49,   //ui_lock.wav
    Eff_ui_unlock           = 50,   //ui_unlock.wav
    Eff_rune_put_down       = 51,   //music/rune_unset.mp3
    Eff_rune_open           = 52,   //music/rune_newhole.mp3
    Eff_heart_heal          = 53,   //music/battle_heartheal.wav
    Eff_drop_item           = 54,   //music/drop_item.wav
    Eff_get_epic_pet        = 55,   //music/get_epic_pet.mp3
    Eff_arean_battle        = 56,   //music/battle_arena.mp3
    Eff_armor_lvup          = 57,   //music/armor_lvup.mp3
    Bgm_new_begin           = 58,   //"music/bgm_prologue.mp3"
    Eff_get_chest           = 59,   //"music/ui_getchest.mp3"
    Eff_open_chest          = 60,   //"music/ui_openchest.mp3"
};

#endif
