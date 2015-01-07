//
//  CcbManager.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-8-17.}
//
//

#include "CcbManager.h"
#include "StartGameLayer.h"
#include "MainBottomLayer.h"
#include "MainHeadLayer.h"
#include "MainLayer.h"
#include "TextCriticalLayer.h"
#include "TextSparkLayer.h"
#include "CcbBegin20Layer.h"
#include "CcbBegin21Layer.h"
#include "CcbBegin22Layer.h"
#include "BuyMiddleLayer.h"
#include "CcbPetBagLayer.h"
#include "CcbHeaderBackLayer.h"
#include "MapLayer.h"
#include "StageLayer.h"
#include "StageNode.h"
#include "CcbPetShowLayer.h"
#include "CcbPetShowTitle.h"
#include "CcbLeftArrow.h"
#include "CcbRightArrow.h"
#include "CcbUnitMiddleLayer.h"
#include "CcbEvolveLayer.h"
#include "CcbSortLayer.h"
#include "CcbTeamFrameLayer.h"
#include "CcbTeamLayer.h"
#include "CcbTeamMemberLayer.h"
#include "CcbPetEnhanceLayer.h"
#include "CCApplication.h"
#include "LoadingLayer.h"
#include "CcbPetBagSaleLayer.h"
#include "CcbPetEvolveSuccessLayer.h"
#include "CcbArenaIndexLayer.h"
#include "CcbArenaBattleLayer.h"
#include "CcbArenaRankLayer.h"
#include "CcbArenaRewardLayer.h"
#include "CcbArenaMyInfoLayer.h"
#include "CcbCountryLayer.h"
#include "CcbCaptureFrameLayer.h"
#include "CcbCaptureLayer.h"
#include "CcbFriendLayer.h"
#include "CcbFriendNodeLayer.h"
#include "CcbPetShowBackLayer.h"
#include "CcbPetSkillLayer.h"
#include "CcbPetBattleCtrl.h"
#include "CcbPetBattleLayer.h"
#include "CcbCaptureMasterLayer.h"
#include "CcbRescueFrameLayer.h"
#include "CcbMainTeamLayer.h"
#include "CcbMailListLayer.h"
#include "CcbArenaPetCtrl.h"
#include "CcbArenaFightLayer.h"
#include "CcbArenaResultWinLayer.h"
#include "CcbArenaShopLayer.h"
#include "CcbArenaShopFrameLayer.h"
#include "CcbArenaRankRewardLayer.h"
#include "CcbArenaRankRewardFrameLayer.h"
#include "CcbArenaReportLayer.h"
#include "CcbFightRewardLayer.h"
#include "CcbSystemLayer.h"
#include "CcbSystemLayer2.h"
#include "CcbPetTujianLayer.h"
#include "CcbItemListLayer.h"
#include "CcbItemIconLayer.h"
#include "CcbItemFrameLayer.h"
#include "CcbItemInfoLayer.h"
#include "CcbItemInfoButtonLayer.h"
#include "SystemMessage.h"
#include "CcbTujianShowLayer.h"
#include "CcbAnnounceLayer.h"
#include "CcbAccountLayer.h"
#include "CcbRegistLayer.h"
#include "CcbServerListLayer.h"
#include "CcbServerNode.h"
#include "CcbFindFriendLayer.h"
#include "CcbActivityLayer.h"
#include "CcbActivityNodeLayer.h"
#include "CcbGMLayer.h"
#include "CcbGmInsertLayer.h"
#include "CcbGmItemLayer.h"
#include "CcbGmUserLayer.h"
#include "CcbPlistShowLayer.h"
#include "CcbBuildUpLayer.h"
#include "CcbFriendMailLayer.h"
#include "CcbPetIconCtrl.h"
#include "CcbDropBoxLayer.h"
#include "CcbAltSkillEffLayer.h"
#include "CcbCaptureFrameLayer.h"
#include "CcbShopSelectNumScene.h"
#include "CcbShopGemListLayer.h"
#include "CcbShopNormalListLayer.h"
#include "CcbShopItemFrameLayer.h"
#include "CcbGemListFrameLayer.h"
#include "CcbVipListLayer.h"
#include "CcbVipFrameLayer.h"
#include "CcbNoServiceLayer.h"
#include "CcbPetIcon.h"
#include "CcbEquipNormalFrameLayer.h"
#include "CcbEquipListLayer.h"
#include "CcbEquipInlayLayer.h"
#include "CcbRuneIconLayer.h"
#include "CcbEquipStrengthenLayer.h"
#include "CcbEquipEvolveLayer.h"
#include "CcbEquipCompoundListLayer.h"
#include "CcbEquipCompoundInfoLayer.h"
#include "CcbEquipCompoundFrame1Layer.h"
#include "CcbEquipCompoundFrame2Layer.h"
#include "CcbBossWarningLayer.h"
#include "CcbLostLayer.h"
#include "CcbFightStart.h"
#include "CcbWinLayer.h"
#include "CcbPadLayer.h"
#include "MainBottomInnerLayer.h"
#include "CcbCoinCarRewardLayer.h"
#include "CcbEventMainLayer.h"
#include "CcbEventIconLayer.h"
#include "CcbEventRecoverEnergyLayer.h"
#include "CcbEventReward7Layer.h"
#include "CcbEventReward30Layer.h"
#include "CcbEventRewardFrameLayer.h"
#include "CcbEventFirstRechargeLayer.h"
#include "CcbEventGrowPlanLayer.h"
#include "CcbEventGrowPlanFrameLayer.h"
#include "CcbPetEquipIcon.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "CcbUpdateResourceLayer.h"
#endif

#include "CcbLeaderSkillEffLayer.h"
#include "CcbUserInfoLayer.h"
#include "CcbFightFinishLayer.h"
#include "CcbFightWaveLayer.h"
#include "CcbAwardCenterLayer.h"
#include "CcbAchieveRewardLayer.h"
#include "CcbAchieveRewardFrameLayer.h"
#include "CcbDailyQuestRewardLayer.h"
#include "CcbDailyQuestRewardFrameLayer.h"
#include "CcbShareFrameLayer.h"
#include "CcbExchangeCodeLayer.h"
#include "CcbInviteFriendLayer.h"
#include "CcbInviteFriendFrameLayer.h"
#include "CcbPetBattleHpBarLayer.h"
#include "CcbPetFuseLayer.h"
#include "CcbCreateNameLayer.h"
#include "CcbChoosePetLayer.h"
#include "CcbEventMySteryShopFrameLayer.h"
#include "CcbEventMySteryShopLayer.h"
#include "CcbPetChooseInfoLayer.h"
#include "CcbSettingsLayer.h"
#include "CcbShowGetLayer.h"
#include "CcbAccountBindingLayer.h"
#include "CcbHeaderBackLayer2.h"
#include "CcbGachaResultLayer.h"
#include "CcbGachaResultStar.h"
#include "CcbGachaResultEgg.h"
#include "CcbGachaResultXiyou.h"
#include "CcbGachaResultChaoXiyou.h"
#include "CcbGachaResultChaojueXiyou.h"
#include "CcbSystemBootInfoLayer.h"
#include "CcbFuseListLayer.h"
#include "CcbSysFriendFrameLayer.h"
#include "CcbArenaBattleListLayer.h"
#include "CcbArenaRankListLayer.h"
#include "CcbBoxRewardFrame.h"
#include "CcbActivityTipLayer.h"
#include "CcbNewGachaLayer.h"
#include "CcbUserLvUpLayer.h"
#include "CcbDropTipLayer.h"
#include "CcbFingerUpLayer.h"
#include "CcbFingerDownLayer.h"
#include "CcbBattleDead.h"
#include "CcbBattleLeaderPlus.h"
#include "CcbJumpTipLayer.h"
#include "TextMissLayer.h"
#include "CcbBattleDust.h"
#include "CcbChatLayer.h"
#include "CcbSystemBootLose.h"
#include "CcbChatFaceLayer.h"
#include "CcbBegin1Layer.h"
#include "CcbPetBattleAltLoad.h"
#include "CcbEvoInfoFrameLayer.h"
#include "CcbEvoInfoListLayer.h"
#include "CcbPetBattleLoading.h"
#include "CcbEmblemFrameLayer.h"
#include "CcbEmblemListLayer.h"
#include "CcbEmblemInfoLayer.h"
#include "CcbExcPetFrameLayer.h"
#include "CcbEmblemEnhanceLayer.h"
#include "CcbEmblemIconLayer.h"
#include "CcbTowerMainLayer.h"
#include "CcbTowerRankListLayer.h"
#include "CcbTowerRankFrameLayer.h"
#include "CcbTowerRewardListLayer.h"
#include "CcbTowerRewardFrameLayer.h"
#include "CcbTextLianXieLayer.h"
#include "CcbMainTopLayer.h"
#include "CcbChallengeLayer.h"
#include "CcbChallengeMapLayer.h"
#include "CcbChallengeOverRewardLayer.h"
#include "CcbLianXieBgLayer.h"
#include "CcbLianXieBgLayer2.h"
#include "CcbLianXieBgLayer3.h"
#include "CcbLianXieBgLayer4.h"
#include "CcbLianXieBgLayer5.h"
#include "CcbLianXieBgLayer6.h"
#include "CcbSystemNoticeLayer.h"
#include "CcbSystemNoticeFrameLayer.h"
#include "CcbMailDetailLayer.h"
#include "CcbMainPetCardLayer.h"
#include "CcbSweepLayer.h"
#include "CCScrollButton.h"
#include "CcbBattleAnimationLayer.h"
#include "CcbActiveStageLayer.h"
#include "CcbBattleSkillBgLayer.h"
#include "CcbDropTipFrameLayer.h"
#include "CcbEquipIntegrationLayer.h"
#include "CcbGachaOpenEgg.h"
#include "CcbStageEffLayer.h"
#include "CcbMapPointLayer.h"
#include "CcbCoinCatDesLayer.h"
#include "CcbSystemMailBoardLayer.h"
#include "CcbPetInfoLayer.h"
#include "CcbPetBattleBossLayer.h"
#include "CcbBegin200Layer.h"
#include "CcbEmblemChooseListLayer.h"
#include "CcbPetFuseLowQualityGetLayer.h"
#include "CcbPetFuseHighQualityGetLayer.h"
#include "CcbTujianFrame.h"
#include "CcbShopGiftView.h"
#include "CcbShopGiftViewFrame.h"
#include "CcbWorldBossLayer.h"
#include "CcbChallengeNodeLayer.h"
#include "CcbChallengeMissionStageLayer.h"
#include "CcbWorldBossFightLayer.h"
#include "CcbChallengeIndexLayer.h"
#include "CcbChallengeBossLayer.h"
#include "CcbChallengeSelectBoardLayer.h"
#include "CcbChallengeNode2Layer.h"
#include "CcbChallengeType1Layer.h"
#include "CcbChallengeType2Layer.h"
#include "CcbChallengeType3Layer.h"
#include "CcbWorldBossRankLayer.h"
#include "CcbWorldBossRankRewardFrame.h"
#include "CcbWorldBossRankRewardLayer.h"
#include "CcbChallengetype3ScrollLayer.h"
#include "CcbChatTalkBoardLayer.h"
#include "CcbGachaBoardLayer.h"
#include "CcbFriendUnitLayer.h"
#include "CcbFriendCntLayer.h"
#include "CcbFriendListFrameLayer.h"
#include "CcbFriendFindFrameLayer.h"
#include "CcbFriendGetEnergyFrameLayer.h"
#include "CcbFriendGetAllEnergyLayer.h"
#include "CcbFriendSocialBoardLayer.h"
#include "CcbFriendMailFrameLayer.h"
#include "CcbPatchFrameLayer.h"
#include "CcbItemPatchLayer.h"
#include "CcbWorldLootLayer.h"
#include "CcbArenaResultHighestLayer.h"
#include "CcbEventAnnounceFrame.h"
#include "CcbEventAnnounceLayer.h"
#include "CcbGrowPlanTitleLayer.h"
#include "CcbMJShopFindLayer.h"
#include "CcbMapPointJumpLayer.h"

static CcbManager* m_pShared = NULL;

CcbManager* CcbManager::sharedManager()
{
    if (!m_pShared) {
        m_pShared = new CcbManager();
        CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        pLoaderLib->registerCCNodeLoader( "StartGameLayer", StartGameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "MainLayer", MainLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "MainHeadLayer", MainHeadLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "MainBottomLayer", MainBottomLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBattleAnimationLayer", CcbBattleAnimationLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbMainTeamLayer", CcbMainTeamLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "MainBottomInnerLayer", MainBottomInnerLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "TextCriticalLayer", TextCriticalLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "TextSparkLayer", TextSparkLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "BuyMiddleLayer", BuyMiddleLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbHeaderBackLayer2", CcbHeaderBackLayer2Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBagLayer", CcbPetBagLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetShowLayer", CcbPetShowLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetShowTitle", CcbPetShowTitleLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetShowBackLayer", CcbPetShowBackLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetEquipIcon", CcbPetEquipIconLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "StageLayer", StageLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbHeaderBackLayer", CcbHeaderBackLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbUnitMiddleLayer", CcbUnitMiddleLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLeftArrow", CcbLeftArrowLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbRightArrow", CcbRightArrowLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetIcon", CcbPetIconLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEvolveLayer", CcbEvolveLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbTeamFrameLayer", CcbTeamFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbTeamMemberLayer", CcbTeamMemberLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbTeamLayer", CcbTeamLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetEnhanceLayer", CcbPetEnhanceLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBagSaleLayer", CcbPetBagSaleLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaIndexLyaer", CcbArenaIndexLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaRewardLayer", CcbArenaRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaMyInfoLayer", CcbArenaMyInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaRankLayer", CcbArenaRankLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaBattleLayer", CcbArenaBattleLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaResultWinLayer", CcbArenaResultWinLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaShopLayer", CcbArenaShopLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaRankRewardLayer", CcbArenaRankRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaRankRewardFrameLayer", CcbArenaRankRewardFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaReportLayer", CcbArenaReportLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetEvolveSuccessLayer", CcbPetEvolveSuccessLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbCountryLayer", CcbCountryLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbCaptureLayer", CcbCaptureLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbCaptureFrameLayer", CcbCaptureFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendLayer", CcbFriendLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendNodeLayer", CcbFriendNodeLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFightRewardLayer", CcbFightRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGmItemLayer", CcbGmItemLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGmInsertLayer", CcbGmInsertLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBattleLayer", CcbPetBattleLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBattleCtrl", CcbPetBattleCtrlLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFightWaveLayer", CcbFightWaveLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSystemLayer", CcbSystemLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbMailListLayer", CcbMailListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbItemListLayer", CcbItemListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaFightLayer", CcbArenaFightLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaPetCtrl", CcbArenaPetCtrlLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetTujianLayer", CcbPetTujianLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbNewGachaLayer", CcbNewGachaLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbTujianShowLayer", CcbTujianShowLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetSkillLayer", CcbPetSkillLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBuildUpLayer", CcbBuildUpLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "MapLayer", MapLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "StageNode", StageNodeLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSortLayer", CcbSortLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbArenaShopFrameLayer", CcbArenaShopFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPlistShowLayer", CcbPlistShowLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGmUserLayer", CcbGmUserLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGMLayer", CcbGMLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbActivityNodeLayer", CcbActivityNodeLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbActivityLayer", CcbActivityLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFindFriendLayer", CcbFindFriendLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbServerNode", CcbServerNodeLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbServerListLayer", CcbServerListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbServerNode", CcbServerNodeLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbRegistLayer", CcbRegistLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAccountLayer", CcbAccountLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAnnounceLayer", CcbAnnounceLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "SystemMessage", SystemMessageLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "SystemMessage2", CcbSystemLayer2Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbItemFrameLayer", CcbItemFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbItemInfoLayer", CcbItemInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbItemInfoButtonLayer", CcbItemInfoButtonLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbItemIconLayer", CcbItemIconLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbRescueFrameLayer", CcbRescueFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbCaptureMasterLayer", CcbCaptureMasterLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShopSelectNumLayer", CcbShopSelectNumLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGemListFrameLayer", CcbGemListFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShopNormalListLayer", CcbShopNormalListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShopGemListLayer", CcbShopGemListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAltSkillEffLayer", CcbAltSkillEffLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShopItemFrameLayer", CcbShopItemFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbDropBoxLayer", CcbDropBoxLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetIconCtrl", CcbPetIconCtrlLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendMailLayer", CcbFriendMailLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFightFinishLayer", CcbFightFinishLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbUserInfoLayer", CcbUserInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLeaderSkillEffLayer", CcbLeaderSkillEffLayerLoader::loader() );
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
		pLoaderLib->registerCCNodeLoader( "CcbUpdateResourceLayer", CcbUpdateResourceLayerLoader::loader() );
#endif
        pLoaderLib->registerCCNodeLoader( "CcbEventGrowPlanFrameLayer", CcbEventGrowPlanFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventGrowPlanLayer", CcbEventGrowPlanLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventFirstRechargeLayer", CcbEventFirstRechargeLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventIconLayer", CcbEventIconLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventRewardFrameLayer", CcbEventRewardFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventReward30Layer", CcbEventReward30LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventReward7Layer", CcbEventReward7LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventRecoverEnergyLayer", CcbEventRecoverEnergyLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventMainLayer", CcbEventMainLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPadLayer", CcbPadLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbWinLayer", CcbWinLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLostLayer", CcbLostLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFightStart", CcbFightStartLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBossWarningLayer", CcbBossWarningLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundFrame2Layer", CcbEquipCompoundFrame2LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundFrame1Layer", CcbEquipCompoundFrame1LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundInfoLayer", CcbEquipCompoundInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipCompoundListLayer", CcbEquipCompoundListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipStrengthenLayer", CcbEquipStrengthenLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipEvolveLayer", CcbEquipEvolveLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbRuneIconLayer", CcbRuneIconLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipInlayLayer", CcbEquipInlayLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipListLayer", CcbEquipListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipNormalFrameLayer", CcbEquipNormalFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaResultChaojueXiyou", CcbGachaResultChaojueXiyouLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaResultChaoXiyou", CcbGachaResultChaoXiyouLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaResultXiyou", CcbGachaResultXiyouLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaResultEgg", CcbGachaResultEggLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaResultStar", CcbGachaResultStarLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaResultLayer", CcbGachaResultLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAccountBindingLayer", CcbAccountBindingLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShowGetLayer", CcbShowGetLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSettingsLayer", CcbSettingsLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetChooseInfoLayer", CcbPetChooseInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventMySteryShopLayer", CcbEventMySteryShopLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventMySteryShopFrameLayer", CcbEventMySteryShopFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetFuseLayer", CcbPetFuseLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChoosePetLayer", CcbChoosePetLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbCreateNameLayer", CcbCreateNameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBattleHpBarLayer", CcbPetBattleHpBarLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbInviteFriendFrameLayer", CcbInviteFriendFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbInviteFriendLayer", CcbInviteFriendLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbExchangeCodeLayer", CcbExchangeCodeLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShareFrameLayer", CcbShareFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbDailyQuestRewardFrameLayer", CcbDailyQuestRewardFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbDailyQuestRewardLayer", CcbDailyQuestRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAchieveRewardFrameLayer", CcbAchieveRewardFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAchieveRewardLayer", CcbAchieveRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbAwardCenterLayer", CcbAwardCenterLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSystemBootInfoLayer", CcbSystemBootInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSysFriendFrameLayer", CcbSysFriendFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFuseListLayer", CcbFuseListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaBattleListLayer", CcbArenaBattleListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaRankListLayer", CcbArenaRankListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBoxRewardFrame", CcbBoxRewardFrameLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbActivityTipLayer", CcbActivityTipLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbUserLvUpLayer", CcbUserLvUpLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbDropTipLayer", CcbDropTipLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFingerUpLayer", CcbFingerUpLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFingerDownLayer", CcbFingerDownLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBattleDead", CcbBattleDeadLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBattleLeaderPlus", CcbBattleLeaderPlusLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbJumpTipLayer", CcbJumpTipLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "TextMissLayer", TextMissLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBattleDust", CcbBattleDustLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChatLayer", CcbChatLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSystemBootLose", CcbSystemBootLoseLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChatFaceLayer", CcbChatFaceLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBegin1Layer", CcbBegin1LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBattleAltLoad", CcbPetBattleAltLoadLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEvoInfoFrameLayer", CcbEvoInfoFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEvoInfoListLayer", CcbEvoInfoListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBattleLoading", CcbPetBattleLoadingLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEmblemFrameLayer", CcbEmblemFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEmblemListLayer", CcbEmblemListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEmblemInfoLayer", CcbEmblemInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbExcPetFrameLayer", CcbExcPetFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEmblemIconLayer", CcbEmblemIconLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEmblemEnhanceLayer", CcbEmblemEnhanceLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbTowerMainLayer", CcbTowerMainLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbTowerRankListLayer", CcbTowerRankListLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbTowerRankFrameLayer", CcbTowerRankFrameLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbTowerRewardListLayer", CcbTowerRewardListLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbTowerRewardFrameLayer", CcbTowerRewardFrameLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbTextLianXieLayer", CcbTextLianXieLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbMainTopLayer", CcbMainTopLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChallengeLayer", CcbChallengeLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChallengeMapLayer", CcbChallengeMapLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChallengeOverRewardLayer", CcbChallengeOverRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer", CcbLianXieBgLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer2", CcbLianXieBgLayer2Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer3", CcbLianXieBgLayer3Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer4", CcbLianXieBgLayer4Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer5", CcbLianXieBgLayer5Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbLianXieBgLayer6", CcbLianXieBgLayer6Loader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSystemNoticeLayer", CcbSystemNoticeLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbSystemNoticeFrameLayer", CcbSystemNoticeFrameLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbMailDetailLayer", CcbMailDetailLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbMainPetCardLayer", CcbMainPetCardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CCScrollButton", CCScrollButtonLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSweepLayer", CcbSweepLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "LoadingLayer", LoadingLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbHaloLightLayer", CcbHaloLightLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbActiveStageLayer", CcbActiveStageLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBattleSkillBgLayer", CcbBattleSkillBgLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBegin20Layer", CcbBegin20LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBegin22Layer", CcbBegin22LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBegin21Layer", CcbBegin21LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbDropTipFrameLayer", CcbDropTipFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEquipIntegrationLayer", CcbEquipIntegrationLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaOpenEgg", CcbGachaOpenEggLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbStageEffLayer", CcbStageEffLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbMapPointLayer", CcbMapPointLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbCoinCatDesLayer", CcbCoinCatDesLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbSystemMailBoardLayer", CcbSystemMailBoardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetInfoLayer", CcbPetInfoLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetBattleBossLayer", CcbPetBattleBossLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbBegin200Layer", CcbBegin200LayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEmblemChooseListLayer", CcbEmblemChooseListLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetFuseLowQualityGetLayer", CcbPetFuseLowQualityGetLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPetFuseHighQualityGetLayer", CcbPetFuseHighQualityGetLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbTujianFrame", CcbTujianFrameLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbShopGiftView", CcbShopGiftViewLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbShopGiftViewFrame", CcbShopGiftViewFrameLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbWorldBossLayer", CcbWorldBossLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChallengeNodeLayer", CcbChallengeNodeLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeMissionStageLayer", CcbChallengeMissionStageLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbWorldBossFightLayer", CcbWorldBossFightLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChallengeIndexLayer", CcbChallengeIndexLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeBossLayer", CcbChallengeBossLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeSelectBoardLayer", CcbChallengeSelectBoardLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeNode2Layer", CcbChallengeNode2LayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeType1Layer", CcbChallengeType1LayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeType2Layer", CcbChallengeType2LayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChallengeType3Layer", CcbChallengeType3LayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbWorldBossRankRewardLayer", CcbWorldBossRankRewardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbWorldBossRankRewardFrame", CcbWorldBossRankRewardFrameLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbWorldBossRankLayer", CcbWorldBossRankLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbChallengetype3ScrollLayer", CcbChallengetype3ScrollLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbChatTalkBoardLayer", CcbChatTalkBoardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGachaBoardLayer", CcbGachaBoardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendUnitLayer", CcbFriendUnitLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendCntLayer", CcbFriendCntLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendListFrameLayer", CcbFriendListFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendFindFrameLayer", CcbFriendFindFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendGetEnergyFrameLayer", CcbFriendGetEnergyFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendGetAllEnergyLayer", CcbFriendGetAllEnergyLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendSocialBoardLayer", CcbFriendSocialBoardLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbFriendMailFrameLayer", CcbFriendMailFrameLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbPatchFrameLayer", CcbPatchFrameLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbItemPatchLayer", CcbItemPatchLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbWorldLootLayer", CcbWorldLootLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbArenaResultHighestLayer", CcbArenaResultHighestLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventAnnounceFrame", CcbEventAnnounceFrameLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbEventAnnounceLayer", CcbEventAnnounceLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbGrowPlanTitleLayer", CcbGrowPlanTitleLayerLoader::loader());
        pLoaderLib->registerCCNodeLoader( "CcbMJShopFindLayer", CcbMJShopFindLayerLoader::loader() );
        pLoaderLib->registerCCNodeLoader( "CcbMapPointJumpLayer", CcbMapPointJumpLayerLoader::loader() );
    }
    return m_pShared;
}

CcbManager::CcbManager()
{
    
}

CcbManager::~CcbManager()
{
    if(m_pShared)
    {
        delete m_pShared;
        m_pShared = NULL;
    }
}

CCNode* CcbManager::LoadStartGameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode;
    pNode = pCCBReader->readNodeGraphFromFile("ccb/start_layer4.ccbi", owner);

	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadMainLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCNode* pNode;
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    pNode = pCCBReader->readNodeGraphFromFile("ccb/mainscene.ccbi", owner);

	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadTextCriticalLayer(  ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/critical.ccbi");
//    ((TextCriticalLayer*)owner)->setAnimationManager(pCCBReader->getAnimationManager());
    
	pCCBReader->release();
	return pNode;
}

CCNode* CcbManager::LoadTextSparkLayer(  ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/spark.ccbi");
//    ((TextSparkLayer*)owner)->setAnimationManager(pCCBReader->getAnimationManager());
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadBuyMiddleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/buy_middle.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadPetBagLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile( "ccb/bag_pet.ccbi", owner );
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbHeaderBackLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/header_back.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadMapLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/map_scene.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}
CCNode* CcbManager::LoadCcbPetShowLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadStageLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/stage.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadStageNode( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/missionframe.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbUnitMiddleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/unit_middle.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbEvolveLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_evo.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbSortLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/sort.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbTeamFrameLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/teamframe.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbTeamLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/teamview.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbTeamMemberLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/teamcircleset.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbPetEnhanceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_enhance.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbPetBagSaleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/bag_pet_mix.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场主界面}
CCNode* CcbManager::LoadCcbArenaIndexLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_index.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场排行界面}
CCNode* CcbManager::LoadCcbArenaRankLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场挑战列表}
CCNode* CcbManager::LoadCcbArenaBattleLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_battle.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场结算}
CCNode* CcbManager::LoadCcbArenaResultWinLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_result_win.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

//竞技场商店}
CCNode* CcbManager::LoadCcbArenaShopLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_shop.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场商店兑换的选择条}
CCNode* CcbManager::LoadCcbArenaShopFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_shop_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场排行榜奖励}
CCNode* CcbManager::LoadCcbArenaRankRewardLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank_reward.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场排行榜奖励条目}
CCNode* CcbManager::LoadCcbArenaRankRewardFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank_reward_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//竞技场战报}
CCNode* CcbManager::LoadCcbArenaReportLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_report.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetEvolveSuccessLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_evo_result.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbCountryLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/country.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbCaptureLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/capture.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbCaptureFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/capture_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFriendLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFriendNodeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbPetBattleLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_scene.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbCaptureMasterLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/capture_slave_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbRescueFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/rescue_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbMailListLayer( CCObject* owner ){
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/mail_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbArenaFightLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_arena_battle_scene.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbNewGachaLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_new.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFightRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_reward.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSystemLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbPetTujianLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/tujian.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbItemListLayer( CCObject* owner ) {
   	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbItemChosenLayer( CCObject* owner ){
   	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_chosen.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbItemIconLayer( CCObject* owner)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_icon.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

//道具条目类型1}
CCNode* CcbManager::LoadCcbItemFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_frame.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

//道具条目类型2}
CCNode* CcbManager::LoadCcbItemFrame2Layer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_frame2.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

//道具详情弹出框}
CCNode* CcbManager::LoadCcbItemInfoLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_info.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadSystemMessage() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/message.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadSystemMessage2() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/message2.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbTujianShowLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/tujian_show.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSkillEnhanceLayer( CCObject* owner ) 
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/skill_enhance.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbskillEnhanceResultLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/skill_enhance_result.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbAnnounceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/announce.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbAccountLayer(  ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/account_login.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbRegistLayer(  ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/regist.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbServerListLayer(  ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/server_list.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbServerNode( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/server_node.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFindFriendLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/find_friend.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbActivityLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/activity.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbActivityNodeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/activity_node.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGmItemLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm_item.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}
CCNode* CcbManager::LoadCcbGMLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}
CCNode* CcbManager::LoadCcbGmUserLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm_user.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPlistShowLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/plist_show.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBuildUpLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/build_up.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFriendMailLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_mail.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetIconCtrl( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_icon_ctrl.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbDropBoxLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/box.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbShopItemFrameLayer( CCObject* owner )
{
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbAltSkillEffLayer() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_scene.ccbi");
	pCCBReader->release();
    
	return pNode;
}

//钻石购买}
CCNode* CcbManager::LoadCcbShopGemListLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_gem_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//普通物品商城}
CCNode* CcbManager::LoadCcbShopNormalListLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_normal_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//充值列表}
CCNode* CcbManager::LoadCcbGemListFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gem_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbShopSelecNumLayer( )
{
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	   
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_select_num.ccbi");
	pCCBReader->release();
    
	return pNode;
}

//VIP特权界面}
CCNode* CcbManager::LoadCcbVipListLayer( CCObject* owner ,CCSize parentSize)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbVipListLayer", CcbVipListLayerLoader::loader() );
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/vip_list.ccbi", owner,parentSize);
	pCCBReader->release();
    
	return pNode;
}

//VIP条目}
CCNode* CcbManager::LoadCcbVipFrameLayer( CCObject* owner ,CCSize parentSize)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbVipFrameLayer", CcbVipFrameLayerLoader::loader() );
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/vip_frame.ccbi", owner ,parentSize);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetIcon( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_icon.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//装备界面显示条目}
CCNode* CcbManager::LoadCcbEquipNormalFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_normal_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//装备显示界面}
CCNode* CcbManager::LoadCcbEquipListLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEquipInlayLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_inlay.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbRuneIconLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_rune_icon.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//装备强化界面}
CCNode* CcbManager::LoadCcbEquipStrengthenLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_strengthen.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

//装备进阶界面}
CCNode* CcbManager::LoadCcbEquipEvolveLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_evo.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

//合成列表界面}
CCNode* CcbManager::LoadCcbEquipCompoundListLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_list.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

//合成物品详情}
CCNode* CcbManager::LoadCcbEquipCompoundInfoLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_info.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

//合成列表选择条目}
CCNode* CcbManager::LoadCcbEquipCompoundFrame1Layer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_frame1.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//合成详情需要物品条目}
CCNode* CcbManager::LoadCcbEquipCompoundFrame2Layer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_compound_frame2.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBossWarningLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/boss.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFightStart( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	   
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbLostLayer() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/lose.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbWinLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/win.ccbi");
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbPadLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/talkpad.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEventMainLayer( CCObject* owner )    //活动主界面}
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_main.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventRecoverEngergyLayer( CCObject* owner )  //回复体力}
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_recover_energy.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventReward7Layer( CCObject* owner )     //7天奖励}
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_reward_7.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventReward30Layer( CCObject* owner )    //30天奖励}
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_reward_30.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventRewardFrameLayer( CCObject* owner) //领取活动奖励}
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode *pNode = NULL;
    pNode = pCCBReader->readNodeGraphFromFile("ccb/event_reward_frame.ccbi", owner);
    
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventIconLayer( CCObject *owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_icon.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventFirstRechargeLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_first_recharge.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventGrowPlanLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_grow_plan.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventGrowPlanFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_grow_plan_frame.ccbi", owner);
	pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbUpdateResourceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/update_resource.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetEquipIcon( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_equip_icon.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbLeaderSkillEffLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_ani.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbUserInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/user_info.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFightFinishLayer() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_finish.ccbi");
	pCCBReader->release();
    
	return pNode;
}

//进入选择领奖界面}
CCNode* CcbManager::LoadCcbAwardCenterLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/award_center.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//成就界面}
CCNode* CcbManager::LoadCcbAchieveRewardLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/achieve_reward.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//成就界面选择条}
CCNode* CcbManager::LoadCcbAchieveRewardFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/achieve_reward_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//每日任务界面}
CCNode* CcbManager::LoadCcbDailyQuestRewardLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/dailyquest_reward.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//每日任务界面选择条}
CCNode* CcbManager::LoadCcbDailyQuestRewardFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/dailyquest_reward_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//分享界面}
CCNode* CcbManager::LoadShareFrameLayer()
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/share_frame.ccbi");
	pCCBReader->release();
    
	return pNode;
}

//输入兑换码界面}
CCNode* CcbManager::LoadCcbExchangeCodeLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/exchange_code.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//好友邀请界面}
CCNode* CcbManager::LoadCcbInviteFriendLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/invite_friend.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//邀请奖励条目}
CCNode* CcbManager::LoadCcbInviteFriendFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/invite_friend_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//CCNode* CcbManager::LoadCcbBeginLayer( CCObject* owner ) {
//	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin.ccbi", owner);
//	pCCBReader->release();
//    
//	return pNode;
//}

//战斗界面宠物血条}
CCNode* CcbManager::LoadCcbPetBattleHpBarLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_hp_bar.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//CCNode* CcbManager::LoadCcbAfterBattleLayer( CCObject* owner ) {
//	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/after_battle.ccbi", owner);
//	pCCBReader->release();
//    
//	return pNode;
//}

CCNode* CcbManager::LoadCcbCreateNameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/createname.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbChoosePetLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChoosePetLayer.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetFuseLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_fuse.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEventMySteryShopFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_mysteryshop_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEventMySteryShopLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_mysteryshop.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetChooseInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/novicepetactive.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//设置界面}
CCNode* CcbManager::LoadCcbSettingsLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/settings.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbShowGetLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/reward_tip.ccbi");
	pCCBReader->release();
    
	return pNode;
}



//账号绑定界面}
CCNode* CcbManager::LoadCcbAccountBindingLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/account_binding.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetSkillLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_skill.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGachaResultLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_3.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGachaResultStar( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_star.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGachaResultEgg( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_egg.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGachaResultXiyou( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_level1.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGachaResultChaoXiyou( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_level2.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbGachaResultChaojueXiyou( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gacha_result_level3.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbMailDetailLayer(  ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/mail_text.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSystemBootInfoLayer() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_boot_info.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSysFriendFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_sys_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbFuseListLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fuse_list.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbArenaBattleListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_battle_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;

}

CCNode* CcbManager::LoadCcbArenaRankListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_rank_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBoxRewardFrame( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/box_reward_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbActivityTipLayer( ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/activity_tip.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbUserLvUpLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/user_levelup.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbDropTipLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_drop_tip.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFingerUpLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/guide_finger_up.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbFingerDownLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/guide_finger_down.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbBattleDead( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/battle_dead.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBattleLeaderPlus( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/battle_plus.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbJumpTipLayer(CCObject* owner)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbCostTipLayer.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadTextMissLayer() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/miss.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBattleDust() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/battle_dust.ccbi");
	pCCBReader->release();
	return pNode;
}

CCNode* CcbManager::LoadCcbChatLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/chat.ccbi", owner);
	pCCBReader->release();
	return pNode;
}


CCNode* CcbManager::LoadCcbSystemBootLose( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_boot_lose.ccbi");
	pCCBReader->release();
	return pNode;
}

CCNode* CcbManager::LoadCcbChatFaceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/chat_face.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBegin1Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_01.ccbi", owner);
	pCCBReader->release();

	return pNode;
}

CCNode* CcbManager::LoadCcbPetBattleAltLoad( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
		
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_skill_load.ccbi");
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbEvoInfoFrameLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/evo_frame.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEvoInfoListLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/evo_list.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetBattleLoading( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
    
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_loading.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEmblemFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_frame.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEmblemListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_list.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEmblemInfoLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_wear.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbExcPetFrameLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_excpet_frame.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEmblemIconLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_choose_icon.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbEmblemEnhanceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_strengthen.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//爬塔主界面}
CCNode* CcbManager::LoadCcbTowerMainLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_main.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//爬塔排行榜界面}
CCNode* CcbManager::LoadCcbTowerRankListLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_ranklist.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//爬塔排行榜条目}
CCNode* CcbManager::LoadCcbTowerRankFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_rankframe.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//爬塔奖励预览界面}
CCNode* CcbManager::LoadCcbTowerRewardListLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_boxlist.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//爬塔奖励条目}
CCNode* CcbManager::LoadCcbTowerRewardFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/climbtower_boxframe.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbTextLianXieLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/lianxie.ccbi");
	pCCBReader->release();
    
	return pNode;
}

// 主界面头部几个按钮}
CCNode* CcbManager::LoadCcbMainTopLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/top3.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbChallengeLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_vielist.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbChallengeMapLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
    
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_map.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//CCNode* CcbManager::LoadCcbChallengeOverRewardFrame( CCObject* owner ) {
//	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//	
//    
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_over_reward_frame.ccbi", owner);
//	pCCBReader->release();
//    
//	return pNode;
//}

CCNode* CcbManager::LoadCcbChallengeOverRewardLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_rewardlist.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

//CCNode* CcbManager::LoadCcbChallengeRewardFrame( CCObject* owner ) {
//	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
//	
//    
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pavilion_reward_frame.ccbi", owner);
//	pCCBReader->release();
//    
//	return pNode;
//}

CCNode* CcbManager::LoadCcbLianXieBgLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
		
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbLianXieBgLayer2( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash_2.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbLianXieBgLayer3( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash_3.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbLianXieBgLayer4( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash_4.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbLianXieBgLayer5( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash_5.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbLianXieBgLayer6( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_flash_6.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::chooseLianXieBgLayer(uint8 cnt)
{
    CCNode * node = NULL;
    switch (cnt) {
        case 2:
            node = LoadCcbLianXieBgLayer2();
            break;
        case 3:
            node = LoadCcbLianXieBgLayer3();
            break;
        case 4:
            node = LoadCcbLianXieBgLayer4();
            break;
        case 5:
            node = LoadCcbLianXieBgLayer5();
            break;
        case 6:
            node = LoadCcbLianXieBgLayer6();
            break;
            
        default:
            break;
    }
    
    return node;
}

CCNode* CcbManager::LoadCcbSystemNoticeLayer(CCObject* owner) //系统公告}
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_notice.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSystemNoticeFrameLayer( CCObject* owner )
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_notice_frame.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSweepLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/fight_bot.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadLoadingLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/loding.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBattleAnimationLayer(  ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_ctrl_ani.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbActiveStageLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/missionframe_active.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBattleSkillBgLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_skill_bg.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBegin20Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBegin21Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2_1.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbBegin22Layer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2_2.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}


CCNode* CcbManager::LoadCcbDropTipFrameLayer(  ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_droptip_frame.ccbi");
	pCCBReader->release();
    
	return pNode;
}

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipIntegrationLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
	   
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_integration.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbStageEffLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/missionframelight.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbMapPointLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/map_point.ccbi", owner);
	pCCBReader->release();
    
	return pNode;
}




//CcbManager.cpp
CCNode* CcbManager::LoadCcbCoinCatDesLayer( ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/cat_money.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbSystemMailBoardLayer() {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_reward_board.ccbi");
	pCCBReader->release();
    
	return pNode;
}

CCNode* CcbManager::LoadCcbPetInfoLayer( ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_information.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbPetBattleBossLayer( ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_boss.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbBegin200Layer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/begin_2_0.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbEmblemChooseListLayer(  CCObject* owner) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_choose.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::createNodeByCCBData( CCData *pData,CCObject *pOwner)
{
    CCNodeLoaderLibrary *nodeLoader = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader *ccbReader = new CCBReader(nodeLoader);
    CCNode *pNode = dynamic_cast<CCNode *>(ccbReader->readNodeGraphFromData(pData, pOwner, CCDirector::sharedDirector()->getWinSize()));
    CC_SAFE_DELETE(ccbReader);
    return pNode;
}


CCNode* CcbManager::LoadCcbPetFuseLowQualityGetLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_fuse_lowquality.ccbi");
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbPetFuseHighQualityGetLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
   

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_fuse_highquality.ccbi");
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbTujianFrame() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/tujian_frame.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbShopGiftViewLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_giftbag_view.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbShopGiftViewFrame() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/shop_giftbag_prerviewframe.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbWorldBossLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/world_boss.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeMissionStageLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeMissionStageLayer.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeNodeLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeNodeLayer.ccbi",owner);
    pCCBReader->release();
    
    return pNode;
}

//CcbManager.cpp
CCNode* CcbManager::LoadCcbWorldBossFightLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_boss_scene.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeIndexLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeIndexLayer.ccbi",owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeSelectBoardLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeSelectBoardLayer.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeNode2Layer()
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeNode2Layer.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeType1Layer(cocos2d::CCObject *owner)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeType1Layer.ccbi",owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeType2Layer(cocos2d::CCObject *owner)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeType2Layer.ccbi",owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengeType3Layer(cocos2d::CCObject *owner)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengeType3Layer.ccbi",owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbWorldBossRankRewardLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/world_boss_reward.ccbi");
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbWorldBossRankRewardFrame() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/wolrd_boss_rewardframe.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbWorldBossRankLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/world_boss_damagerank.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChallengetype3ScrollLayer(cocos2d::CCObject *owner, cocos2d::CCSize winSize)
{
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChallengetype3ScrollLayer.ccbi",owner,winSize);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbChatTalkBoardLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbChatTalkBoardLayer.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbGachaBoardLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbGachaBoardLayer.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendUnitLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_uint.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendCntLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_cnt.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendListFrameLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendListFrameLayer.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendFindFrameLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendFindFrameLayer.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendGetEnergyFrameLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendGetEnergyFrame.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendGetAllEnergyLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_send_energy.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendSocialBoardLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();

    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/friend_social_board.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbFriendMailFrameLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbFriendMailFrameLayer.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbItemPatchLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbItemPatchLayer.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbPatchFrameLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/CcbPatchFrameLayer.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbWorldLootLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_sbox.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbArenaResultHighestLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/arena_result_highest.ccbi");
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbEventAnnounceFrame() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_announce_frame.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbEventAnnounceLayer() {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_announcement.ccbi");
    pCCBReader->release();
    
    return pNode;
}


CCNode* CcbManager::LoadCcbMJShopFindLayer( ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/event_MJShop.ccbi");
    pCCBReader->release();
    
    return pNode;
}

CCNode* CcbManager::LoadCcbMapPointJumpLayer( CCObject* owner ) {
    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    CCBReader* pCCBReader = new CCBReader(pLoaderLib);
    CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/jump.ccbi", owner);
    pCCBReader->release();
    
    return pNode;
}





