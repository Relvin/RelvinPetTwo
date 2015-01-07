//
//  CcbManager.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-8-17.}
//
//

#ifndef __HelloWorld__CcbManager__
#define __HelloWorld__CcbManager__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;


class CcbManager {
    
public:
    static CcbManager* sharedManager();
    CcbManager();
    ~CcbManager();
    
    CCNode* LoadStartGameLayer( CCObject* owner );      // 进入游戏的第一个界面，登陆}

    CCNode* LoadMainLayer( CCObject* owner );           // 主界面}
    CCNode* LoadCcbMainTopLayer( CCObject* owner );     // 主界面头部}
    
    CCNode* LoadTextCriticalLayer(  );   // 暴击动画}
    CCNode* LoadTextSparkLayer(  );      // 连击动画}
    
    CCNode* LoadBuyMiddleLayer( CCObject* owner );      // 购买界面}
    CCNode* LoadPetBagLayer( CCObject* owner );
    CCNode* LoadCcbHeaderBackLayer( CCObject* owner );
    CCNode* LoadMapLayer( CCObject* owner );            // 地图界面}
    CCNode* LoadStageLayer( CCObject* owner );          // 关卡列表界面}
    CCNode* LoadStageNode( CCObject* owner );           // 关卡Node}
    CCNode* LoadCcbPetShowLayer( CCObject* owner );
    CCNode* LoadCcbUnitMiddleLayer( CCObject* owner );  // 精灵一览，队伍编辑，出售等入口}

    CCNode* LoadCcbEvolveLayer( CCObject* owner );
    CCNode* LoadCcbSortLayer( CCObject* owner );
    CCNode* LoadCcbTeamLayer( CCObject* owner );
    CCNode* LoadCcbTeamFrameLayer( CCObject* owner );
    CCNode* LoadCcbTeamMemberLayer( CCObject* owner );
    CCNode* LoadCcbPetEnhanceLayer( CCObject* owner );

    CCNode* LoadCcbPetBagSaleLayer( CCObject* owner );
    
    CCNode* LoadCcbArenaIndexLayer( CCObject* owner );      //竞技场主界面}
    CCNode* LoadCcbArenaRankLayer( CCObject* owner );       //竞技场排行界面}
    CCNode* LoadCcbArenaBattleLayer( CCObject* owner );     //竞技场挑战列表}
    CCNode* LoadCcbArenaResultWinLayer( CCObject* owner );     //竞技场结算}
    CCNode* LoadCcbArenaShopLayer( CCObject* owner );       //竞技场商店}
    CCNode* LoadCcbArenaShopFrameLayer( CCObject* owner );  //竞技场商店兑换的选择条}
    CCNode* LoadCcbArenaRankRewardLayer( CCObject* owner ); //竞技场排行榜奖励}
    CCNode* LoadCcbArenaRankRewardFrameLayer( CCObject* owner );//竞技场排行榜奖励条目}
    CCNode* LoadCcbArenaReportLayer( CCObject* owner );         //竞技场战报}
    
    CCNode* LoadCcbPetEvolveSuccessLayer( CCObject* owner );
    CCNode* LoadCcbCountryLayer( CCObject* owner );     // 乡村界面}
    CCNode* LoadCcbCaptureLayer( CCObject* owner );     // 抓捕界面}
    CCNode* LoadCcbFriendLayer( CCObject* owner );      // 好友界面}
    CCNode* LoadCcbFriendNodeLayer( CCObject* owner );  // 好友节点}
    CCNode* LoadCcbPetBattleLayer( CCObject* owner );
    CCNode* LoadCcbCaptureFrameLayer( CCObject* owner );    // 抓捕时，如果是主人显示的奴隶界面}
    CCNode* LoadCcbCaptureMasterLayer( CCObject* owner );   // 抓捕时，如果被抓捕的主人界面}
    CCNode* LoadCcbRescueFrameLayer( CCObject* owner );     // 解救界面}
    CCNode* LoadCcbMailListLayer(CCObject* owner);          //邮件主界面}
//    CCNode* LoadCcbPetBattleSkillBgLayer( CCObject* owner ) ;
    CCNode* LoadCcbArenaFightLayer( CCObject* owner );      //竞技场战斗界面}
    
    CCNode* LoadCcbFightRewardLayer( CCObject* owner ); // 战斗结算面板}
    CCNode* LoadCcbSystemLayer( CCObject* owner );      // 系统界面，包括好友入口等}
    CCNode* LoadCcbPetTujianLayer( CCObject* owner );   //图鉴界面}
    CCNode* LoadCcbItemListLayer( CCObject* owner );    //道具界面}
    CCNode* LoadCcbItemChosenLayer( CCObject* owner );  //道具选择界面}
    CCNode* LoadCcbItemIconLayer(CCObject* owner);      //道具Icon}
    CCNode* LoadCcbItemFrameLayer( CCObject* owner );   //道具条目类型1}
    CCNode* LoadCcbItemFrame2Layer( CCObject* owner );  //道具条目类型2}
    CCNode* LoadCcbItemInfoLayer( CCObject* owner );    //道具详情弹出框}
    
    CCNode* LoadSystemMessage(  );       // 信息提示框，确定，取消弹出框}
    CCNode* LoadSystemMessage2(  );       // 信息提示框2}
    CCNode* LoadCcbTujianShowLayer( CCObject* owner ); //图鉴详细界面}

    CCNode* LoadCcbSkillEnhanceLayer( CCObject* owner );        //技能升级选择画面}
    CCNode* LoadCcbskillEnhanceResultLayer( CCObject* owner );  //技能升级结果画面}

    CCNode* LoadCcbAnnounceLayer( CCObject* owner );        // 公告界面}
    CCNode* LoadCcbAccountLayer(  );                        // 登陆账号界面}
    CCNode* LoadCcbRegistLayer(  );                         // 注册账号界面}
    CCNode* LoadCcbServerListLayer(  );                     // 服务器列表界面}
    CCNode* LoadCcbServerNode( CCObject* owner );           // 服务器node界面}
    CCNode* LoadCcbFindFriendLayer( CCObject* owner );      // 查找好友界面}


    CCNode* LoadCcbActivityLayer( CCObject* owner );        // 特殊活动界面}
    CCNode* LoadCcbActivityNodeLayer( CCObject* owner );    // 特殊活动Node}
    CCNode* LoadCcbGMLayer( CCObject* owner );              // GM界面}
    CCNode* LoadCcbGmItemLayer( CCObject* owner );
    CCNode* LoadCcbGmUserLayer( CCObject* owner );

    CCNode* LoadCcbPlistShowLayer( CCObject* owner );
    CCNode* LoadCcbBuildUpLayer( CCObject* owner );     // 建筑升级界面}
    CCNode* LoadCcbFriendMailLayer( CCObject* owner );  // 好友邮件界面}
    CCNode* LoadCcbPetIconCtrl( CCObject* owner );      // petIcon
    CCNode* LoadCcbDropBoxLayer( CCObject* owner );     // 战斗掉落的宝箱}
    
    CCNode* LoadCcbShopItemFrameLayer( CCObject* owner );   //商城列表显示的单个条目}
    CCNode* LoadCcbShopGemListLayer( CCObject* owner );     //钻石购买}
    CCNode* LoadCcbShopNormalListLayer( CCObject* owner );  //普通物品商城}
    CCNode* LoadCcbGemListFrameLayer(CCObject* owner);      //充值列表}
    CCNode* LoadCcbShopSelecNumLayer( );    //商城购买时弹出的选择数量界面}
    CCNode* LoadCcbVipListLayer( CCObject* owner ,CCSize parentSize);         //VIP特权界面}
    CCNode* LoadCcbVipFrameLayer( CCObject* owner ,CCSize parentSize );        //VIP条目}
    CCNode* LoadCcbTestLayer( CCObject* owner );
    CCNode* LoadCcbAltSkillEffLayer( );
    CCNode* LoadCcbPetIcon( CCObject* owner );   //宠物头像（只带属性球）}
    CCNode* LoadCcbEquipNormalFrameLayer( CCObject* owner );    //装备界面显示条目}
    CCNode* LoadCcbEquipListLayer( CCObject* owner );           //装备显示界面}
    CCNode* LoadCcbEquipInlayLayer( CCObject* owner );          //镶嵌符文界面}
    CCNode* LoadCcbRuneIconLayer( CCObject* owner );            //符文icon}
    CCNode* LoadCcbEquipStrengthenLayer( CCObject* owner );     //装备强化界面}
    CCNode* LoadCcbEquipEvolveLayer( CCObject* owner );              //装备进阶界面}
    CCNode* LoadCcbEquipCompoundListLayer( CCObject* owner );   //合成列表界面}
    CCNode* LoadCcbEquipCompoundInfoLayer( CCObject* owner );   //合成物品详情}
    CCNode* LoadCcbEquipCompoundFrame1Layer( CCObject* owner ); //合成列表选择条目}
    CCNode* LoadCcbEquipCompoundFrame2Layer( CCObject* owner ); //合成详情需要物品条目}
    CCNode* LoadCcbBossWarningLayer( );
    CCNode* LoadCcbFightStart( );
    CCNode* LoadCcbLostLayer( );
    CCNode* LoadCcbWinLayer( );
    CCNode* LoadCcbPadLayer( CCObject* owner ); // 弹版界面}
    CCNode* LoadCcbEventMainLayer( CCObject* owner );           //活动主界面}
    CCNode* LoadCcbEventRecoverEngergyLayer( CCObject* owner ); //回复体力}
    CCNode* LoadCcbEventReward7Layer( CCObject* owner );        //7天奖励}
    CCNode* LoadCcbEventReward30Layer( CCObject* owner );       //30天奖励}
    CCNode* LoadCcbEventRewardFrameLayer( CCObject* owner);    //领取活动奖励}
    CCNode* LoadCcbEventIconLayer( CCObject* owner );           //活动图标}
    CCNode* LoadCcbEventFirstRechargeLayer( CCObject* owner );  //首充奖励}
    CCNode* LoadCcbEventGrowPlanLayer( CCObject* owner );       //成长计划}
    CCNode* LoadCcbEventGrowPlanFrameLayer( CCObject* owner );  //成长计划}
    CCNode* LoadCcbUpdateResourceLayer( CCObject* owner );      //更新资源界面}
    CCNode* LoadCcbPetEquipIcon( CCObject* owner );             //宠物详情界面装备Icon}

    CCNode* LoadCcbLeaderSkillEffLayer( CCObject* owner );      //队长技能特效}
    CCNode* LoadCcbUserInfoLayer( CCObject* owner );            //人物详情界面}
    CCNode* LoadCcbFightFinishLayer();                          //战斗结束动画}
    CCNode* LoadCcbFightWaveLayer( CCObject* owner );           //战斗波次动画}
    CCNode* LoadCcbAwardCenterLayer( CCObject* owner );             //进入选择领奖界面}
    CCNode* LoadCcbAchieveRewardLayer( CCObject* owner );           //成就界面}
    CCNode* LoadCcbAchieveRewardFrameLayer( CCObject* owner );      //成就界面选择条}
    CCNode* LoadCcbDailyQuestRewardLayer( CCObject* owner );        //每日任务界面}
    CCNode* LoadCcbDailyQuestRewardFrameLayer( CCObject* owner );   //每日任务界面选择条}
    CCNode* LoadShareFrameLayer();                 //分享界面}
    CCNode* LoadCcbExchangeCodeLayer( CCObject* owner );            //输入兑换码界面}
    CCNode* LoadCcbInviteFriendLayer( CCObject* owner );            //好友邀请界面}
    CCNode* LoadCcbInviteFriendFrameLayer( CCObject* owner );       //邀请奖励条目}
    CCNode* LoadCcbPetBattleHpBarLayer( CCObject* owner );          //战斗界面宠物血条}
    CCNode* LoadCcbCreateNameLayer( CCObject* owner );      // 创建用户名}
    CCNode* LoadCcbChoosePetLayer( CCObject* owner );       // 选择4个宠物界面}
    CCNode* LoadCcbPetFuseLayer( CCObject* owner );         //宠物融合界面}
    CCNode* LoadCcbEventMySteryShopFrameLayer( CCObject* owner );   //神秘商店Frame}
    CCNode* LoadCcbEventMySteryShopLayer( CCObject* owner );        //神秘商店}
    CCNode* LoadCcbPetChooseInfoLayer( CCObject* owner );           // 选择宠物的详情界面}
    CCNode* LoadCcbNewGachaLayer( CCObject* owner );        // 抽奖界面}
    
    CCNode* LoadCcbSettingsLayer( CCObject* owner );        //设置界面}

    CCNode* LoadCcbShowGetLayer( );     // show get Layer

    CCNode* LoadCcbAccountBindingLayer( CCObject* owner = NULL );//账号绑定界面}
    CCNode* LoadCcbPetSkillLayer( CCObject* owner );
    CCNode* LoadCcbGachaResultLayer( CCObject* owner );
    CCNode* LoadCcbGachaResultStar( CCObject* owner );
    CCNode* LoadCcbGachaResultEgg( CCObject* owner );
    CCNode* LoadCcbGachaResultXiyou( CCObject* owner );
    CCNode* LoadCcbGachaResultChaoXiyou( CCObject* owner );
    CCNode* LoadCcbGachaResultChaojueXiyou( CCObject* owner );
    CCNode* LoadCcbMailDetailLayer(  );         // 好友邮件内容}
    CCNode* LoadCcbSystemBootInfoLayer();       //系统引导}
    CCNode* LoadCcbSysFriendFrameLayer( CCObject* owner );      // 好友大界面Frame条目，与设置的同一款条目}

    CCNode* LoadCcbFuseListLayer( CCObject* owner );
    
    CCNode* LoadCcbArenaBattleListLayer( CCObject* owner );
    CCNode* LoadCcbArenaRankListLayer( CCObject* owner );
    CCNode* LoadCcbBoxRewardFrame( CCObject* owner );
    CCNode* LoadCcbActivityTipLayer();
    CCNode* LoadCcbUserLvUpLayer( CCObject* owner );
    CCNode* LoadCcbDropTipLayer();
    CCNode* LoadCcbFingerUpLayer( CCObject* owner );        // 手指向上的新手}
    CCNode* LoadCcbFingerDownLayer( CCObject* owner );      // 手指向下的新手}
    CCNode* LoadCcbBattleDead( CCObject* owner );
    CCNode* LoadCcbBattleLeaderPlus( CCObject* owner );
    CCNode* LoadCcbJumpTipLayer( CCObject* owner );         //跳转界面}
    CCNode* LoadTextMissLayer();
    CCNode* LoadCcbBattleDust();
    CCNode* LoadCcbChatLayer( CCObject* owner );            // 聊天界面}
    CCNode* LoadCcbSystemBootLose();
    CCNode* LoadCcbChatFaceLayer( CCObject* owner );
    
    CCNode* LoadCcbBegin1Layer( CCObject* owner );      // 开场动画1}
    CCNode* LoadCcbBegin20Layer( CCObject* owner );     // 新开场动画2_0}
    CCNode* LoadCcbBegin200Layer( CCObject* owner );    // 新手加的一个黑幕
    CCNode* LoadCcbBegin21Layer( CCObject* owner );     // 新开场动画2_1}
    CCNode* LoadCcbBegin22Layer( CCObject* owner );     // 新开场动画2_2}
    
    CCNode* LoadCcbPetBattleAltLoad();
    CCNode* LoadCcbEvoInfoFrameLayer( );
    
    CCNode* LoadCcbEvoInfoListLayer( );
    CCNode* LoadCcbPetBattleLoading( CCObject* owner );
    CCNode* LoadCcbEmblemFrameLayer( CCObject* owner );
    CCNode* LoadCcbEmblemListLayer( CCObject* owner );
    CCNode* LoadCcbEmblemInfoLayer( );
    CCNode* LoadCcbExcPetFrameLayer( );
    CCNode* LoadCcbEmblemIconLayer( CCObject* owner );
    CCNode* LoadCcbEmblemEnhanceLayer( CCObject* owner );
    CCNode* LoadCcbTowerMainLayer( CCObject* owner );       //爬塔主界面}
    CCNode* LoadCcbTowerRankListLayer( CCObject* owner = NULL );   //爬塔排行榜界面}
    CCNode* LoadCcbTowerRankFrameLayer( CCObject* owner );  //爬塔排行榜条目}
    CCNode* LoadCcbTowerRewardListLayer( CCObject* owner ); //爬塔奖励预览界面}
    CCNode* LoadCcbTowerRewardFrameLayer( CCObject* owner );//爬塔奖励条目}
    CCNode* LoadCcbTextLianXieLayer();
    CCNode* LoadCcbChallengeLayer( CCObject* owner );
    CCNode* LoadCcbChallengeMapLayer( CCObject* owner );
    CCNode* LoadCcbChallengeOverRewardLayer( CCObject* owner );
    
    CCNode* LoadCcbLianXieBgLayer();
    CCNode* LoadCcbLianXieBgLayer2();
    CCNode* LoadCcbLianXieBgLayer3();
    CCNode* LoadCcbLianXieBgLayer4();
    CCNode* LoadCcbLianXieBgLayer5();
    CCNode* LoadCcbLianXieBgLayer6();
    CCNode* chooseLianXieBgLayer(uint8 cnt);
    
    CCNode* LoadCcbSystemNoticeLayer( CCObject* owner = NULL ); //系统公告}
    CCNode* LoadCcbSystemNoticeFrameLayer( CCObject* owner );
    
    CCNode* LoadCcbSweepLayer( CCObject* owner );       // 扫荡界面}
    CCNode* LoadLoadingLayer();
    
    CCNode* LoadCcbBattleAnimationLayer(  );        // 大招流光界面}
    CCNode* LoadCcbActiveStageLayer( CCObject* owner );     // 活动战斗关卡}
    CCNode* LoadCcbBattleSkillBgLayer( CCObject* owner );
    CCNode* LoadCcbDropTipFrameLayer( );
    CCNode* LoadCcbEquipIntegrationLayer( CCObject* owner );
    CCNode* LoadCcbStageEffLayer(  );       // 若引导特效添加
    CCNode* LoadCcbMapPointLayer( CCObject* owner );    // 地图点
    CCNode* LoadCcbCoinCatDesLayer( );      //招财猫金币奖励说明
    CCNode* LoadCcbSystemMailBoardLayer( ); //系统邮件详情
    CCNode* LoadCcbPetInfoLayer( );//宠物详情信息
    CCNode* LoadCcbPetBattleBossLayer( );//大魔王
    
    CCNode* LoadCcbEmblemChooseListLayer( CCObject* owner);
    
    CCNode* createNodeByCCBData( CCData *pData,CCObject *pOwner); //add by Relvin
    
    CCNode* LoadCcbPetFuseLowQualityGetLayer();
    CCNode* LoadCcbPetFuseHighQualityGetLayer();
    CCNode* LoadCcbTujianFrame();
    CCNode* LoadCcbShopGiftViewLayer();
    CCNode* LoadCcbShopGiftViewFrame();
    CCNode* LoadCcbWorldBossLayer( CCObject* owner );   //世界boss
    CCNode* LoadCcbChallengeMissionStageLayer();
    CCNode* LoadCcbChallengeNodeLayer( CCObject* owner ) ;
    CCNode* LoadCcbWorldBossFightLayer( CCObject* owner );
    CCNode* LoadCcbChallengeIndexLayer( CCObject* owner );  //挑战界面
    CCNode* LoadCcbChallengeSelectBoardLayer();
    CCNode* LoadCcbChallengeNode2Layer();
    CCNode* LoadCcbChallengeType1Layer( CCObject* owner );  //
    CCNode* LoadCcbChallengeType2Layer( CCObject* owner );  //
    CCNode* LoadCcbChallengeType3Layer( CCObject* owner );  //
    
    CCNode* LoadCcbWorldBossRankRewardLayer();  //世界boss奖励一览
    CCNode* LoadCcbWorldBossRankRewardFrame();  //世界boss奖励一览
    CCNode* LoadCcbWorldBossRankLayer();        //世界boss伤害排行
    CCNode* LoadCcbChallengetype3ScrollLayer(CCObject* owner,CCSize winSize);
    CCNode* LoadCcbChatTalkBoardLayer( CCObject* owner );       // 聊天条目
    CCNode* LoadCcbGachaBoardLayer();
    
    CCNode* LoadCcbFriendUnitLayer( CCObject* owner );      // 新好友界面，好友Unit
    CCNode* LoadCcbFriendCntLayer( CCObject* owner );       // 新好友界面，下方数量条
    CCNode* LoadCcbFriendListFrameLayer( CCObject* owner ); // 新好友界面，好友一览Cell
    CCNode* LoadCcbFriendFindFrameLayer( CCObject* owner ); // 新好友界面，好友推荐Cell
    CCNode* LoadCcbFriendGetEnergyFrameLayer( CCObject* owner );    // 体力Cell
    CCNode* LoadCcbFriendGetAllEnergyLayer( CCObject* owner );  // 全部领取条
    CCNode* LoadCcbFriendSocialBoardLayer( CCObject* owner );   // 好友社交弹框
    CCNode* LoadCcbFriendMailFrameLayer( CCObject* owner );     // 邮件Cell
    CCNode* LoadCcbItemPatchLayer( CCObject* owner );
    CCNode* LoadCcbPatchFrameLayer();
    CCNode* LoadCcbWorldLootLayer();  //天降宝箱
    CCNode* LoadCcbArenaResultHighestLayer(); //竞技场最高排名奖励
    CCNode* LoadCcbEventAnnounceFrame();    //活动公告frame
    CCNode* LoadCcbEventAnnounceLayer();    //活动公告Layer
    CCNode* LoadCcbMJShopFindLayer();       //秘境商人出现
    CCNode* LoadCcbMapPointJumpLayer( CCObject* owner );    // 地图通关跳转
};

#endif /* defined(__HelloWorld__CcbManager__) */
