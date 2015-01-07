//
//  BackCtrl.h
//  HelloWorld
//
//  Created by junjie zhu on 13-10-9.
//
//

#ifndef __HelloWorld__BackCtrl__
#define __HelloWorld__BackCtrl__

#include "cocos2d.h"

enum kBackEnum {
    // 一级根目录root}
    kMainScene = 0,
    
    // 二级根目录}
    kUintScene = 1,         //精灵一览，队伍入口}
    kChatScene = 2,         // 聊天界面}
    kBuyScene = 3,          //充值，购买入口}
    kCountryScene = 5,      //乡村入口}
    kArenaIndexScene = 6,   //竞技场主界面}
    kMailListScene = 7,     //普通邮件列表界面}
    kGachaScene = 8,        //抽奖界面}
    kSystemScene = 9,       //系统入口}
    kEventScene = 10,       //活动奖励领取界面}
    kAwardCenterScene = 11, //领奖入口}
    kFriendSystemScene = 12,      // 好友界面}
    kFriendUnitScene = 13,      // 好友Unit界面
    
    kUnitMiddleLayer = 16,
    kMapScene = 17,         //地图}
    
    // 其他目录}
    kStageScene = 20,       //关卡}
    kPetShowScene  = 21,
    kPetBagScene = 22,
    kEvolveScene = 23,
    kTeamScene = 24,
    kCaptureScene = 25,             //抓捕型建筑界面}
    kFriendScene = 26,              //好友，解救，抓捕列表界面}
    
    kEnhanceScene = 28,
    kPetBagSaleScene = 29,
    kArenaRankListScene = 30,       //竞技场中的排行榜列表界面}
    kArenaBattleListScene = 31,     //竞技场中的挑战列表界面}
    kArenaShopScene = 32,           //竞技场中的兑换商店}
    kArenaRankRewardScene = 33,     //竞技场中的排行榜奖励一览界面}
    
    kPetTujian = 36,                //宠物图鉴}
    kShowPetTujian = 37,            //图鉴}
    kItemListScene = 38,            //道具列表}
    kItemChosenScene = 40,          //道具选择界面}
    kPveBattleScene = 41,           //pve战斗界面}
    kArenaFightScene = 42,          //pvp战斗界面}


    kActivityMapScene = 46,          //特殊活动界面}
    kBuildUpScene = 47,             //建筑升级界面}
    kFriendMailScene = 48,          //好友邮件界面}
    kShopGemListScene = 49,         //钻石购买界面}
    kShopNoramlListScene = 50,      //普通商城购买界面}

    kEquipListScene = 52,           //装备显示界面}
    kEquipInlayScene = 53,          //镶嵌符文界面}
    kEquipStrengthenScene = 54,     //装备强化界面}
    kEquipCompoundListScene = 55,   //合成列表界面}
    kEquipCompoundInfoScene = 56,   //合成详情界面}
    kEquipEvolveScene = 57,         //装备进化界面}
    
    kFightRewad = 59,               //战斗奖励界面}
    kAchieveRewardScene = 60,       //成就}
    kDailyQuestRewardScene = 61,    //每日任务}
    kPetFuse = 62,                  //宠物融合}}
    kExchangeCodeScene = 63,        //兑换码界面}
    kInviteFriendScene = 64,        //好友邀请}
    kAccountBindingScene = 65,      //账号绑定}
    kGachaResultScene = 66,         //召唤结果}
    kEvolveResult = 67,             //进化结果}
    kFuseList = 68,                 //融合列表界面}
    kVipListScene = 69,             //VIP界面}
    kArenaResultScene = 70,         //竞技场结算}
    kPetBattleLoadingScene = 71,    //战斗过渡场景}
    kEmblemListSenec = 72,          //徽章一览}
    kEmblemEnhSenec = 73,           //徽章强化}
    
    kTowerMainScene = 74,           //爬塔主界面}
    kChallengeMapScene = 75,        //道馆挑战}
    kEquipIntegrationScene = 76,    //装备强化进化}
    kPetInfoScene = 77,             //宠物详细信息}
    kEmblemChooseScene = 78,        //徽章强化素材选择界面}
    kWorldBossScene  =79,           //世界boss
    kChallengeIndexScene = 80,      //探索
    kChallengeType1Scene = 81,      //龙之螺旋塔
    kChallengeType2Scene = 82,      //深奥之地
    kChallengeType3Scene = 83,      //古代密道
    kWorldBossFightScene = 84,
    kItemPatchScene = 85,           //碎片
    kMySteryShopScene = 86,         //神秘商店界面
};

enum kTransEnum {
    kDelayTrans = 0,
    kFadeTrans = 1,
    kNormalTrans = 2,
    
    kOnlyForBack = 99,
};

class BackCtrl {

public:
	typedef void(*LAYER_FUNC)(int kind);
    typedef std::map<int, LAYER_FUNC> MAP_LAYER_FUNCS;

	static void Init();
    static void UnInit();

	static LAYER_FUNC FindSceneFunc(int key);

	/** 增加子界面，传入子页面的value值，如果需要网络通信bConnect为true，只针对其他目录}
	 @brief value   需要传入的子界面的枚举值，见kBackEnum}
	 kind    选择需要用的切换方式，见kTransEnum} */
    static bool InsertNextScene(int value, int kind = 0);
    
    /** 点击下方的切换主页面按钮，传入下方按钮的value值，只针对二级根目录} */
    static bool ChangeRootScene(int value, int kind = 0);
    
    /** 返回上一级页面，点击Back按钮} **/
    static bool BacktoUpperScene(int kind = 0);
    
    /** 获得当前层的enum值} */
    static int GetCurSceneIdx();
    
    /** 网络通信后加入scene,} */
    
    static bool AddWaitScene();
    
    /** 跳转到指定的scene }*/
    static bool JumpToScene(int value, int cycle = 0);
    
    /** PVP战斗后跳转到之前的界面, 1.抓捕，2.竞技场，3.切磋 }*/
    static bool PvpJumpBack();
    
    /** 替换当前层 }*/
    static bool ReplaceCurScene(int value, int kind = 0);
    
    static void ClearSceneStack();
    
    /*!
     current scene end
     */
    static void endCurScene();
    
    static void changeNextSceneWithSafety(int value,int child = 0);
    
    static void changeNextSceneWithSafety(const char * nextScene);
    
#pragma mark Layer Loader Header
    static void MainSceneReplace(int kind);
    static void PetBagSceneReplace(int kind);
    static void BuySceneReplace(int kind);
    static void CountrySceneReplace(int kind);
    static void MapSceneReplace(int kind);
    static void StageSceneReplace(int kind);
    static void EnhanceSceneReplace(int kind);
    static void UintSceneReplace(int kind);
    static void PetShowSceneReplace(int kind);
    static void EvolveSceneReplace(int kind);
    static void TeamSceneReplace(int kind);
    static void PetBagSaleSceneReplace(int kind);
    static void CaptureSceneReplace(int kind);
    static void FriendSceneReplace(int kind);
    static void ArenaIndexSceneReplace(int kind);
    static void ArenaRankListSceneReplace(int kind);
    static void ArenaBattleListSceneReplace(int kind);
    static void ArenaShopSceneReplace(int kind);
    static void ArenaArenaRankRewardReplace(int kind);
    static void MailListSceneReplace(int kind);
    static void GachaSceneReplace(int kind);
    static void SystemSceneReplace(int kind);
    static void PetTujianSceneReplace(int kind);
    static void ItemListSceneReplace(int kind);
    static void PveBattleSceneReplace(int kind);
    static void ArenaFightSceneReplace(int kind);
    static void PettujianShowSceneReplace(int kind);

    static void ActivityMapSceneReplace(int kind);
    static void BuildUpSceneReplace(int kind);
    static void FriendMailSceneReplace(int kind );
    static void EnterShopGemListReplace(int kind);
    static void EnterShopNormalListReplace(int kind);
    static void EquipListSceneReplace(int kind);
    static void EquipInlaySceneReplace(int kind);
    static void EquipStrengthenSceneReplace(int kind);
    static void EquipEvolveSceneReplace(int kind);
    static void EquipCompoundListSceneReplace(int kind);
    static void EquipCompoundInfoSceneReplace(int kind);
    static void FightRewardSceneReplace(int kind);
    static void EventMainSceneReplace(int kind);
    static void EnterAwardCenterSceneReplace(int kind);
    static void EnterAchieveRewardSceneReplace(int kind);
    static void EnterDailyQuestRewardSceneReplace(int kind);
    static void EnterExchangeCodeSceneReplace(int kind);
    static void PetFuseSceneReplace(int kind);
    static void InviteFriendSceneReplace(int kind);
    static void AccountBindingSceneReplace(int kind);
    static void GachaResultSceneReplace(int kind);
    static void FriendSystemSceneReplace(int kind);
    static void PetEvolveSceneReplace(int kind);
    static void FuseListSceneReplace(int kind);
    static void VIPListSceneReplace(int kind);
    static void ArenaResultSceneReplace(int kind);
    static void ChatSceneReplace(int kind);
    static void PetBattleLoadingSceneReplace(int kind);
    static void EmblemSceneReplace(int kind);
    static void EmblemEnhSceneReplace(int kind);
    static void TowerMainSceneReplace(int kind);
    static void ChallengeMapSceneReplace(int kind);
    static void EquipIntegrationSceneReplace(int kind);
    static void PetInfoSceneReplace(int kind);
    static void EmblemChooseSceneReplace(int kind);
    static void WorldBossSceneReplace(int kind);
    static void ChallengeIndexSceneReplace(int kind);
    static void ChallengeType1SceneReplace(int kind);
    static void ChallengeType2SceneReplace(int kind);
    static void ChallengeType3SceneReplace(int kind);
    static void WorldBossFightSceneReplace(int kind);
    static void FriendUnitSceneReplace(int kind);
    static void ItemPatchSceneReplace(int kind);
    static void MySteryShopSceneReplace(int kind);
private:
    static void SceneReplace(int kind, cocos2d::CCScene* pScene);
    /** 获得上一层的enum值 }*/
    static int GetPreviousIdx();
    
    static MAP_LAYER_FUNCS m_mapLayerFuncs;
    static std::vector<int> m_vecScene;
    
    static int m_waitIdx;
    static bool bHaveWait;  //scene切换之间有网络通信，在回包时加入等待的scene，该标志位表明有等待的scene需要切入，否则还停留在当前scene}
};

#endif /* defined(__HelloWorld__BackCtrl__) */
