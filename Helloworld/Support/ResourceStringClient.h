//
//  ResourceStringClient.h
//  HelloWorld
//
//  Created by long on 13-12-11.
//
//

#ifndef _ResourceStringClient_h
#define _ResourceStringClient_h

enum
{
    Str_test                    = 1,    //1,这是测试消息，整数##0##，文字##1##，浮点数##2##。}
    Str_delete                  = 2,    //"删除"
    Str_reject                  = 3,    //"拒绝"
    Str_find_friend             = 4,    //"查找好友"
    Str_friend_list             = 5,    //"好友列表"
    Str_capture_list            = 6,    //"抓捕列表"
    Str_rescue_list             = 7,    //"解救列表"
    Str_friend_request_list     = 8,    //"好友请求列表"
    
    Str_layer_unit              = 9,    //UNIT
    Str_layer_petBag            = 10,   //宠物背包}
    Str_layer_team              = 11,   //出战队伍}
    Str_layer_chgLeader         = 12,   //切换队长}
    Str_layer_chgSite           = 13,   //位置变更}
    Str_layer_pet_enhance       = 14,   //宠物强化}
    Str_layer_pet_evolve        = 15,   //宠物进化}
    Str_layer_pet_tujian        = 16,   //宠物图鉴}
    Str_item_cnt                = 17,   //"数量：##0##"
    Str_arena_rank              = 18,   //第##0##名}
    Str_arena_record            = 19,   //战绩：##0##胜##1##败}
    Str_arena_get               = 20,   //胜利获得：##0##金钱##1##声望}
    Str_arena_reputation        = 21,   //声望：##0##}
    Str_energy_max              = 22,   //体力已满}
    Str_plz_input_np            = 23,   //请输入用户名密码}
    Str_reg_error_format        = 24,   //用户名密码格式不正确(至少六位)}
    Str_cpwd_error              = 25,   //两次密码输入不一样}
    Str_reg_mail_error          = 26,   //邮箱格式不正确}
    Str_pwd_error               = 27,   //密码格式不正确}
    Str_name_not_null           = 28,   //名字不能为空}
    Str_name_min_len            = 29,   //名字最短两个字}
    Str_gacha_tip               = 30,   //本次扭蛋需要##0##钻石}
    Str_account_error           = 31,   //账号格式不正确(4-16位之间)}
    Str_regist_suc              = 32,   //注册成功}
    Str_already_have_account    = 33,   //账户已存在}
    Str_other_error             = 34,   //其他错误，联系客服}
    Str_unit_0                  = 35,   //精灵一览}
    Str_unit_1                  = 36,   //编辑队伍}
    Str_unit_2                  = 37,   //精灵强化}
    Str_unit_3                  = 38,   //精灵进阶}
    Str_unit_4                  = 39,   //宝石镶嵌}
    Str_unit_5                  = 40,   //道具一览}
    Str_unit_6                  = 41,   //装备一览}
    Str_unit_7                  = 42,   //徽章一览}
    Str_unit_8                  = 43,   //宠物碎片}
    Str_unit_9                  = 44,   //宠物融合}
    Str_unit_10                 = 45,   //道具合成}
    Str_unit_11                 = 46,   //精灵出售}
    Str_max_pet_lv              = 47,   //宠物达到最高等级}
    Str_func_not_open           = 48,   //功能尚未开放}
    Str_arena_list              = 49,   //49,战斗列表}
    Str_can_reward              = 50,   //50,可领奖}
    Str_arena                   = 51,   //51,竞技场}
    Str_no_arena_group          = 52,//    52,所在竞技组不存在}
    Str_xwin_xlose              = 53,//    53,%d胜%d败}
    Str_dijiming                = 54,//    54,第%d名}
    Str_dijiming_later          = 55,//    55,第%d名以后}
    Str_money                   = 56,//    56,金钱}
    Str_reputation              = 57,//    57,声望}
    Str_rank_reward             = 58,//    58,排行榜奖励一览}
    Str_rank                    = 59,//    59,排行榜}
    Str_reputation_can_exchange = 60,//    60,%d声望可以兑换}
    Str_arena_shop              = 61,//    61,竞技场商店}
    Str_team                    = 62,//    62,队伍}
    Str_tower                   = 63,//    63,爬塔挑战}
    Str_dijiceng                = 64,//    64,第%d层}
    Str_no_init                 = 65,//    65,未初始化}
    Str_pet_bag_full            = 66,//    66,宠物背包已满仓了，主人。}
    Str_item_bag_full           = 67,//    67,道具背包已满仓了，主人。}
    Str_shop_no_energy          = 68,//    68,体力不足，是否前往购买体力？}
    Str_shop_no_money           = 69,//    69,金币不足，是否前往商城购买金币？}
    Str_shop_no_reputation      = 70,//    70,兑换所需声望不足，无法兑换。}
    Str_how_get_raputation      = 71,//    71,提示：声望可以通过竞技场挑战获得。}
    Str_no_fuse                 = 72,//    72,兑换所需融合石不足，无法兑换。}
    Str_how_get_fuse            = 73,//    73,提示：融合石可以通过融合宠物获得。}
    Str_friend                  = 74,//    74,好友界面}
    Str_friend_invite           = 75,//    75,好友邀请}
    Str_email_search            = 76,//    76,检索邮件}
    Str_friend_add              = 78,//    78,添加好友}
    Str_cost_for_add_energy     = 79,//    79,花费%d钻石回复%d点体力}
    Str_cost_for_add_item_bag   = 80,//    80,花费%d钻石扩展%d格背包}
    Str_jige                    = 81,//    81,%d格}
    Str_cur_bag                 = 82,//    82,当前背包：}
    Str_cost_for_add_pet_bag    = 83,//    83,花费%d钻石扩展%d格宠物包}
    Str_cost_for_add_money      = 84,//    84,花费%d钻石可以获得%d金币}
    Str_atk                     = 85,//    85,攻击}
    Str_hp                      = 86,//    86,生命}
    /*!
     87,回复
     */
    Str_rev                     = 87,
    Str_crit                    = 88,//    88,暴击}
    Str_def                     = 89,//    89,防御}
    Str_compound                = 90,//    90,合成详情}
    Str_choose_rune             = 91,//    91,符文合成选择}
    Str_equip_evolve            = 92,//    92,装备进阶}
    Str_equip_inlay             = 93,//    93,镶嵌}
    Str_equip_in_who            = 94,//    94,装备于%s}
    Str_rune_inlay              = 96,//    96,宝石镶嵌}
    Str_sure_sale_equip         = 97,//    97,确定出售该装备吗？}
    Str_equip_enhance           = 98,//    98,装备强化}
    Str_the_same_rune           = 99,//    99,已经镶嵌过同种类型的符文}
    Str_evolve_emlm_gift        = 100,//    100,进阶素材礼包}
    Str_exchange_cnt            = 101,//    101,兑换次数: %d}
    Str_sure_reflash_mystery_rock = 102,//    102,刷新神秘商店将消耗%d个刷新石，确定刷新吗？}
    Str_sure_reflash_mystery_dollar = 103,//    103,刷新神秘商店将消耗%d钻石，确定刷新吗？}
    Str_mystery_reflash_des     = 104,//    104,每日00:00准时刷新神秘商店物品。您可以使用“刷新石”或者 %d 钻石立即刷新。}
    Str_cannot_get              = 105,//    105,还未到领取时间。}
    Str_wenxing_tishi           = 106,//    106,温馨提示}
    Str_get_tommorrow           = 107,//    107,记得明天来领取。}
    Str_ge                      = 108,//    108,个}
    Str_email_title_cannot_empty = 109,//    109,邮件标题不能为空}
    Str_eamil_cannot_empty      = 110,//    110,确定不给你的好基友写点什么吗？}
    Str_sure_del_friend         = 111,//    111,确定删除好友？}
    Str_friend_apply            = 112,//    112,好友申请}
    Str_input_inviter_id        = 113,//    113,输入邀请人ID}
    Str_input_useful_id         = 114,//    114,请输入有效ID}
    Str_input_error             = 115,//    115,输入错误}
    Str_tishi                   = 116,//    116,提示}
    Str_has_choose              = 117,//    117,已选择：%lu}
    Str_all_items               = 118,      //所有物品}
    Str_item                    = 119,//    119,道具}
    Str_equip                   = 120,//    120,装备}
    Str_rune                    = 121,//    121,宝玉}
    Str_gift                    = 122,//    122,礼包}
    Str_skill_book              = 123,//    123,技能书}
    Str_choose_sp_skillbook     = 124,//    124,选择被祭炼的技能书}
    Str_all_item                = 125,//    125,物品一览}
    Str_sure_sale_item          = 126,//    126,是否出售该物品}
    Str_first_pay_gift          = 127,//    127,首充超值大礼包}
    Str_shuliang                = 128,//    128,数量}
    Str_sure_sale_pet_lv        = 129,//    129,出售的宠物中有满级的，确定要出售吗？}
    Str_sure_sale_pet_star      = 130,//    130,出售的宠物中有3星级以上的，确定要出售吗？}
    Str_sure_eat_pet_star       = 131,//    131,被吃的宠物中有3星级以上的，确定要吃吗？}
    Str_sure_eat_pet_lv         = 132,//    132,被吃的宠物中有满级的，确定要吃吗？}
    Str_choose_eat_pet          = 133,//    133,请点素材框选低级被吃宠物哦}
    Str_fuse_house              = 134,//    134,融合屋}
    Str_no_money                = 135,//    135,金币不足！}
    Str_pet                     = 136,//    136,精灵}
    Str_fuse_stone              = 137,//    137,融合石}
    Str_rune_stone              = 138,//    138,符文石}
    Str_sure_fuse               = 139,//    139,融合后%s消失，可以得到%d个%s，确定融合吗？}
    Str_fuse_des                = 140,//    140,1.将3星~5星宠物进行融合获得融合石。\n2.融合石能够在神秘商店兑换各种宠物及道具。\n3.将4星、5星装备进行融合可以获得符文石。\n4.符文石可以镶嵌在装备上，增强装备属性。}
    Str_evo_unlock              = 141,//    141,(进阶+%d解锁)}
    Str_leader_nature           = 142,//    142,当队长为%s属性}
    Str_reward_room             = 143,//    143,领奖中心}
    Str_system_email            = 144,//    144,系统邮件}
    Str_input_exchange          = 145,//    145,输入兑换码}
    Str_input_right_exchange    = 146,//    146,请输入有效的兑换码}
    Str_exchange_reward         = 147,//    147,兑换码奖励}
    Str_everyday_task           = 148,//    148,每日任务}
    Str_achievement             = 149,//    149,成就}
    Str_system                  = 150,//    150,系统}
    Str_userid_lock             = 151,//    151,账号绑定}
    Str_vip                     = 152,//    152,VIP 特权}
    Str_buy_dollar              = 153,//    153,钻石购买}
    Str_cannot_buy_dollar       = 154,//    154,暂不能购买钻石}
    Str_shop_buy                = 155,//    155,商城购买}
    Str_input_cnt               = 156,//    156,输入数量}
    Str_input_buy_cnt           = 157,//    157,请输入购买数量}
    Str_build_up                = 158,//    158,建筑升级}
    Str_no_cnt                  = 159,//    159,剩余次数不足}
    Str_shop                    = 160,//    160,购买界面}
    Str_reset                   = 161,//    161,重置(%d)}
    Str_relic                   = 162,//    162,遗迹之地}
    Str_before_the_time         = 163,//    163,时间还没到}
    Str_challenge_cur_reward    = 164,//    164,当前通过奖励}
    Str_challenge_first_reward  = 165,//    165,第一次通关奖励}
    Str_dijiguan                = 166,//    166,第%d关}
    Str_touch_the_face          = 167,//    167,请先点击表情符号！~}
    Str_input_text              = 168,//    168,输入文字}
    Str_sure_add_friend         = 169,//    169,确定加 %s 为好友？}
    Str_world                   = 170,//    170,世界}
    Str_union                   = 171,//    171,联盟}
    Str_input_name              = 172,//    172,请输入姓名}
    Str_emblem_enhance          = 173,//    173,徽章强化}
    Str_most_choose             = 174,//    174,最多只能选择%lu个！}
    Str_no_evo_emlm             = 177,//    177,进化材料不足}
    Str_friend_id               = 178,//    178,好友ID}
    Str_equip_pet               = 179,//    179,装备、宠物一览}
    Str_buxian                  = 180,//    180,不限}
    Str_no_network              = 181,//    181,您与网络断开连接}
    Str_lv                      = 182,//    182,等级}
    Str_nature                  = 183,//    183,属性}
    Str_birthday                = 184,//    184,时间}
    Str_star                    = 187,//    187,星级}
    Str_sort_up                 = 188,//    188,↑}
    Str_sort_down               = 189,//    189,↓}
    Str_lose_des                = 190,//    190,失败是成功的老母亲，不要气馁，通过以下方式可快速提升实力：}
    Str_one                     = 191,//    191,一}
    Str_two                     = 192,//    192,二}
    Str_three                   = 193,//    193,三}
    Str_four                    = 194,//    194,四}
    Str_five                    = 195,//    195,五}
    Str_six                     = 196,//    196,六}
    Str_team_no_lv              = 197,//    197,战斗位%d级开放！}
    Str_download_list_error     = 198,//    198,下载列表出错}
    Str_download_list           = 199,//    199,下载文件列表}
    Str_check_file              = 200,//    200,正在校验文件...%d%%}
    Str_check_file_error        = 201,//    201,比较文件出错}
    Str_update_file             = 202,//    202,正在更新文件...}
    Str_download_error          = 203,//    203,下载出错}
    Str_reload_file             = 204,//    204,重载文件}
    Str_update_error            = 205,//    205,更新失败}
    Str_update_success          = 206,//    206,更新成功}
    Str_team_site_open          = 207,//    207,战位开放}
    Str_email_write             = 208,//    208,写邮件}
    Str_speed                   = 210,//    210,速度}
    Str_hit                     = 211,//    211,命中}
    Str_apply_success           = 212,//    212,申请成功}
    Str_re_login                = 213,//    213,账号绑定成功，请重新登录}
    Str_can_evo                 = 214,// 214,%d级可以进化}
    Str_capture_title           = 215,      //抓捕界面}
    Str_capture_loli            = 216,      //快去抓一个萝莉吧}
    Str_capture_ol              = 217,      //快去抓一个御姐吧}
    Str_time_zero               = 218,      //00:00:00
    Str_file_cnt                = 219,      //文件个数}
    Str_file_size               = 220,      //文件大小}
    Str_hecheng_succ            = 221,      //合成成功}
    Str_attr_water              = 222,      //水}
    Str_attr_fire               = 223,      //火}
    Str_attr_grass              = 224,      //草}
    Str_attr_thunder            = 225,      //雷}
    Str_attr_light              = 226,      //光}
    Str_attr_dark               = 227,      //暗}
    Str_challenge_lv_name       = 228,      //%s之遗迹}
    Str_cur_free                = 229,      //当前免费}
    Str_apply                   = 230,      //申请}
    Str_cancel                  = 231,      //取消}
    Str_read                    = 232,      //读取}
    Str_accept                  = 233,      //接受}
    Str_binding                 = 234,      //账号已与%s绑定}
    Str_hecheng_failed          = 235,      //合成失败}
    Str_will_open_at_level      = 236,      //等级不足，%d级开放}
    Str_energy_cost             = 237,      //消耗体力:%d}
    Str_cnt_last                = 238,      //剩余%d次}
    Str_drop_first              = 239,      //首次掉落}
    Str_drop_normal             = 240,      //普通掉落}
    Str_dodge                   = 241,      //闪避}
    Str_pet_item_packet         = 242,      //扩展背包}
    Str_pet_strengthen          = 243,      //强化精灵}
    Str_power_no_enough         = 244,      //购买体力}
    Str_coin_no_enough          = 245,      //购买金币}
    Str_reputation_no_enough    = 246,      //竞技挑战}
    Str_fuse_stone_no_enouth    = 247,      //开始融合}
    Str_power_revert            = 248,      //体力恢复}
    Str_buy_item_packet         = 249,      //背包扩展}
    Str_buy_pet_packet          = 250,      //宠物栏扩展}
    Str_buy_coin                = 251,      //购买金币}
    Str_cur_power               = 252,      //当前体力：}
    Str_cur_pet_packet          = 253,      //当前宠物栏：}
    Str_tank                    = 254,      //防御}
    Str_dps                     = 255,      //输出}
    Str_sup                     = 256,      //辅助}
    Str_no_equip_site           = 408,      //没有装备空位！}
    Str_no_use_equip            = 258,      //没有可用装备！}
    Str_no_eat_pet              = 259,      //当前没有低级精灵}
    Str_no_item                 = 260,      //道具不足}
    Str_put_down_rune_first     = 261,      //该装备无法再次镶嵌}
    Str_wu                      = 262,      //无}
    Str_weishengxiao            = 263,      //未生效}
    Str_yincang                 = 264,      //隐藏}
    Str_xianshi                 = 265,      //显示}
    Str_open_sweep              = 266,      //%d级开启扫荡}
    Str_shouci_tongguan         = 267,      //首次通关}
    Str_shengyujici             = 268,      //（剩余 %d 次）}
    Str_update_dead             = 269,      //更新失败，网络通信中断，请重新登陆游戏，点击确定退出游戏}
    Str_share_text_petshow      = 270,      //《幻想精灵2》招募顶级玩家，下载就送稀有度5星的极品精灵更有无数顶级好礼！}
    Str_share_text_pve_win      = 271,      //RPG手游巨制《幻想精灵2》诚邀体验，成为救世之主还是灭世魔头，由您选择！}
    Str_share_text_pvp_win      = 272,      //养成您独一无二的极品精灵，与其它玩家PK获得神器装备，谁能成为《幻想精灵2的》竞技场之王？}
    Str_chat_head               = 273,      //聊天界面}
    Str_gacha_head              = 274,      //扭蛋界面}
    Str_warning                 = 275,      //提醒}
    Str_normal_diff             = 276,      //普通难度}
    Str_new_equip               = 277,      //新装备}
    Str_go_wear_equip           = 278,      //，快去精灵界面装备吧！}
    Str_new_pet_evo_elem        = 279,      //精灵进阶材料}
    Str_go_pet_evo              = 280,      //，快去进阶你的精灵吧！}
    Str_new_equip_evo_elem      = 281,      //装备进阶材料}
    Str_go_equip_evo            = 282,      //，快去进阶你的装吧！}
    Str_Discharge               = 283,      //卸下}
    Str_Equiped                 = 284,        //已装备}
    Str_Enhance                 = 285,        //强化}
    Str_first_charge            = 286,      //首充礼包}
    Str_grow_plan               = 287,      //成长计划}
    Str_30_day                  = 288,      //开服礼包}
    Str_7_day                   = 289,      //连续登陆}
    Str_get_energy              = 290,      //领取体力}
    Str_mystery_shop            = 291,      //神秘商店}
    Str_chinese_left            = 292,      //【}
    Str_chinese_right           = 293,      //】}
    Str_no_arena_report         = 294,      //无战报}
    Str_pet_tower               = 295,      //精灵之塔}
    Str_badge_challenge         = 296,      //道馆挑战}
    Str_email_send_suc          = 297,      //邮件已发送成功}
    Str_need_update             = 298,      //资源有更新，请下载}
    Str_buy_cnt                 = 299,      //购买次数}
    Str_tiaozhan                = 300,      //挑战}
    Str_no_buy_cnt              = 301,      //今天的购买次数已用完！}
    Str_sure_buy_arena_point    = 302,      //购买竞技点需要花费%d钻石，确定购买吗？}
    Str_gacha_text              = 303,      //扭蛋}
    Str_not_open_tip            = 304,      //活动未开启}
    Str_will_open_at            = 305,      //%s%d等级开放}
    Str_stage_not_open          = 306,      //关卡未开启}
    Str_account_login           = 307,      //账号登录}
    Str_open_at_lv              = 308,      //%d级开启}
    Str_plz_back_to_login       = 309,      //网络通信中断，请重新登陆游戏}
    Str_get_server_list_error   = 310,      //服务器列表获取失败}
    Str_server_list_error_exit  = 311,      //服务器列表获取失败，请退出游戏，检查网络}
    Str_open_bag_success        = 312,      //恭喜你扩展成功啦}
    Str_buy_energy_success      = 313,      //恭喜你恢复%d体力}
    Str_show_buy_message        = 314,      //花费%d钻石可以购买一次}
    Str_vip_need_up             = 315,      //升级vip}
    Str_today_left              = 316,      //今日剩余%d次}
    Str_free_sweep_not_enough   = 317,      //免费扫荡次数不足}
    Str_no_open_in_this_test    = 318,      //本次测试不开放充值}
    Str_towe_sweep              = 319,      //扫荡可以自动战斗到最高层数}
    Str_send_vip                = 320,      //VIP礼包赠送获得}
    Str_buy_tower_reset         = 321,      //花费%d钻石可以购买一次重置次数}
    Str_ji_lv_open              = 322,      //角色等级%d级开启}
    Str_face_not_too_much       = 323,      //一句话中表情符号不能超过%d个}
    Str_umeng_share_Failure     = 324,      //分享失败,请重试?}
    STR_NOTI_ENERGY             = 325,      //【主人，您的体力已满，快来冒险闯荡吧】}
    STR_NOTI_ENERGY_GET         = 326,      //【主人，可以在活动里领取免费的体力啦，快来获取吧】}
    STR_NOTI_LONG_TIME_NO_LOGIN = 327,      //【主人，您有太久没有来看望你您的精灵啦，快来照顾他们吧】}
    Str_five_star_pet_notice    = 328,      //其中5星精灵是进阶到高阶的必须素材，
    Str_sure_sale               = 329,      //确定要出售吗？
    Str_sure_enh                = 330,      //确定要强化吗？
    Str_sure_fus                = 331,      //确定要分解吗？
    Str_name_too_long           = 332,      //名字太长了，亲！那么长小咪会疼的}
    Str_ShopCard_Buy            = 333,      //已购买}
    Str_ShopCard_leftTimes      = 334,      //剩余可领取%d次}
    Str_ShopCard_LeftNotice1    = 335,      //周卡剩余2天可再次购买}
    Str_ShopCard_LeftNotice2    = 336,      //月卡剩余10天可再次购买}
    Str_back_to_main            = 337,      //网络连接出错，点击确定返回主界面。}
    Str_SDef                    = 338,      //特防}
    Str_Share_success           = 339,      //分享成功}
    Str_UserInfo_Music_on       = 340,      //已开启}
    Str_UserInfo_Music_off      = 341,      //已关闭
    Str_change                  = 342,      //更换}
    Str_catk                    = 343,      //普攻
    Str_satk                    = 344,      //特攻
    Str_sdef                    = 345,      //特防
    Str_crit_hurt               = 346,      //爆伤
    Str_crit_free               = 347,      //抗暴
    Str_cdef                    = 348,      //普防}
    Str_need_reconnect          = 349,      //检测到您的网络连接较慢，请重试
    Str_InlayLayer_No_Equip     = 350,      //请先选择需要镶嵌的装备
    Str_Item_Not_Enough         = 351,      //%s不足,是否前往商城购买?
    Str_Chat_System_message     = 352,      //|cFFFF0000[系统消息]%s|r
    Str_get_reward              = 353,      //领奖
    Str_weitongguan             = 354,      //未通关
    Str_LowVip2_notice_text     = 355,      //"连续登录5天，可在活动中最高领取VIP2"
    Str_Score                   = 356,      //"积分"
    Str_Get                     = 357,      //"领取"
    Str_Goto                    = 358,      //"前往"
    Str_jump_next               = 359,      //恭喜通关，现在可以跳转到下一章
    Str_ShowGetLayertitleCanget = 360,      //"可获得"
    Str_DailyReward_Get         = 361,      //"获得:"
    Str_Get_Energy              = 362,      //成功领取%d体力！
    Str_no_open_auto_fight      = 363,      //8级开启自动战斗
    Str_ItemBagLayer_Expand     = 364,      //"花费%d钻石扩展%d格吗？"
    Str_PetLayer_Expand         = 365,      //"花费%d钻石扩展%d格吗？"
    Str_fuse_pet_get            = 366,      //"分解当前精灵可获得："
    Str_fuse_equip_get          = 367,      //"分解当前装备可获得："
    Str_moon_shop               = 368,      //150钻石
    Str_cishuyiman              = 369,      //"今日挑战次数已满"
    Str_Times                   = 370,      //368,"%d次"
    Str_ShowGetLayer_title_get  = 371,        //"已获得"
    Str_ChallengeLayer_Title    = 372,      //探索
    Str_ChallengeType1_Title    = 373,      //"古代密道"
    Str_ChallengeType2_Title    = 374,      //"神奥之地"
    Str_ChallengeType3_Title    = 375,      //"龙之螺旋塔"
    Str_ChallengeIndex_1        = 376,      //"精灵之塔"
    Str_ChallengeIndex_2        = 377,      //"精灵遗迹"
    Str_ChallengeIndex_3        = 378,      //"精灵挑战"
    Str_ChallengeIndex_4        = 379,      //"精灵试炼"
    Str_ChallengeDifficultLevel = 380,      //"难度"
    Str_ChallengeRoleLvLimit    = 381,      //"等级尚未达到！"
    Str_Energy                  = 382,      //体力
    Str_Shop_Now_Price          = 385,      //"售价:"
    Str_Shop_Old_Price          = 386,      //"原价:"
    Str_Challenge_Type1_Text    = 387,
    Str_Challenge_Pet_Illegal   = 388,      //"宠物类型不符合"
    Str_Place                   = 389,      //"位"
    Str_use_ticket              = 390,      //使用%d张扭蛋券抽取%d次
    Str_no_ticket               = 391,      //还没有扭蛋券
    Str_ticket_not_enough       = 392,      //扭蛋券不足，每日登陆可以领取~
    Str_ticket_free_cnt         = 393,      //今日免费次数 %d / %d
    Str_no_ticket_free          = 394,      //今日免费次数已用完
    Str_gacha_normal            = 395,      //普通召唤
    Str_gacha_dollar            = 396,      //传说召唤
    Str_bless_full              = 397,      //祝福已达到上限
    Str_sure_fuhuo              = 398,      //复活需要花费%d钻石，确定立刻复活吗？
    Str_dollar                  = 399,      //钻石
    Str_bu_gou_la               = 400,      //不够啦
    Str_go_shop                 = 401,      //如果急需的话，可以前往商城购买哦~
    Str_mai_mai_mai             = 402,      //立刻购买
    Str_no_item_o               = 403,      //道具不足哦~
    Str_how_get_dollar          = 404,      //每日任务、活动、邮件都可以获得钻石哦。提升竞技场排名也能获得打了钻石。当然，现在商城促销，可以直接去购买哦~
    Str_no_dollar               = 405,      //钻石花光啦
    Str_buy_dollar_arOnce       = 406,      //立刻充值
    Str_get_vip                 = 407,      //充值得到更高的VIP等级可以获得更多的购买次数哦~
    Str_Ch_Day                  = 409,      //"天"
    Str_Ch_Hour                 = 410,      //"时"
    Str_Ch_Min                  = 411,      //"分"
    Str_Ch_Sec                  = 412,      //"秒"
    Str_Active_end              = 413,      //"活动已结束"
    
};

#endif
