//
//  BackCtrl.cpp
//  HelloWorld
//
//  Created by junjie zhu on 13-10-9.
//
//

#include "BackCtrl.h"
#include "CcbManager.h"
#include "GlobalData.h"
#include "MainScene.h"
#include "BuyScene.h"
#include "MapScene.h"
#include "StageScene.h"
#include "CcbPetBagLayer.h"
#include "CcbUnitMiddleLayer.h"
#include "CcbPetShowLayer.h"
#include "CcbEvolveLayer.h"
#include "CcbTeamLayer.h"
#include "CcbPetEnhanceLayer.h"
#include "PetLoadingLayer.h"
#include "TeamCtrl.h"
#include "PetCtrl.h"
#include "CcbPetBagSaleLayer.h"
#include "CcbArenaIndexScene.h"
#include "CcbArenaRankScene.h"
#include "CcbArenaShopScene.h"
#include "CcbArenaRankRewardScene.h"
#include "CcbArenaBattleScene.h"
#include "CcbCountryLayer.h"
#include "CaptureScene.h"
#include "FriendScene.h"
#include "CcbMailListScene.h"
#include "GachaScene.h"
#include "CcbSystemLayer.h"
#include "CcbPetTujianLayer.h"
#include "CcbItemListScene.h"
#include "CcbPetBattleLayer.h"
#include "CcbArenaFightLayer.h"
#include "CcbTujianShowLayer.h"

#include "ActivityScene.h"
#include "BuildUpScene.h"
#include "FriendMailScene.h"
#include "CcbShopGemListScene.h"
#include "CcbShopNormalListScene.h"
#include "CcbEquipListScene.h"
#include "CcbEquipInlayScene.h"
#include "CcbEquipStrengthenScene.h"
#include "CcbEquipEvolveScene.h"
#include "CcbEquipCompoundListScene.h"
#include "CcbEquipCompoundInfoScene.h"
#include "CcbFightRewardLayer.h"
#include "CcbEventMainScene.h"
#include "CcbAwardCenterScene.h"
#include "CcbAchieveRewardScene.h"
#include "CcbDailyQuestRewardScene.h"
#include "CcbExchangeCodeScene.h"
#include "CcbPetFuseLayer.h"
#include "CcbInviteFriendScene.h"
#include "CcbSettingsScene.h"
#include "CcbAccountBindingScene.h"
#include "CcbGachaResultLayer.h"
#include "CcbPetEvolveSuccessLayer.h"
#include "CcbFuseListLayer.h"
#include "CcbVipListScene.h"
#include "CcbArenaResultScene.h"
#include "CCExTransition.h"
#include "ChatScene.h"
#include "CcbPetBattleLoading.h"
#include "CcbEmblemListLayer.h"
#include "CcbEmblemEnhanceLayer.h"
#include "CcbTowerMainScene.h"
#include "CcbChallengeMapLayer.h"
#include "CcbEquipIntegrationLayer.h"
#include "CcbPetInfoLayer.h"
#include "AnalysicsManager.h"
#include "Support.h"
#include "CcbEmblemChooseListLayer.h"
#include "ArenaDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "EmblemDataMgr.h"
#include "CcbWorldBossLayer.h"
#include "CcbWorldBossFightLayer.h"
#include "CcbChallengeIndexLayer.h"
#include "CcbChallengeType1Layer.h"
#include "CcbChallengeType2Layer.h"
#include "CcbChallengeType3Layer.h"
#include "FriendUnitScene.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "ChallengeCtrl.h"
#include "CcbItemPatchLayer.h"
#include "GachaDataMgr.h"
#include "CcbEventMySteryShopLayer.h"

BackCtrl::MAP_LAYER_FUNCS BackCtrl::m_mapLayerFuncs;
vector<int> BackCtrl::m_vecScene;
bool BackCtrl::bHaveWait = false;
int BackCtrl::m_waitIdx = 0;

static std::map<int, std::string> m_mapName;

USING_NS_CC;

void BackCtrl::UnInit() {
    m_vecScene.clear();
    m_mapLayerFuncs.clear();
    m_mapName.clear();
    bHaveWait = false;
}

#define INIT_SCENE( enum, method, name )    \
    m_mapLayerFuncs[enum] = method; \
    m_mapName[enum] = name; \


void BackCtrl::Init()
{
    m_vecScene.clear();
    m_mapLayerFuncs.clear();
    m_mapName.clear();
    bHaveWait = false;
    
    INIT_SCENE(kMainScene, MainSceneReplace, "MainScene");
    INIT_SCENE(kPetBagScene, PetBagSceneReplace, "PetBagScene");
    INIT_SCENE(kBuyScene, BuySceneReplace, "BuyScene");
    INIT_SCENE(kCountryScene, CountrySceneReplace, "CountryScene");
    INIT_SCENE(kMapScene, MapSceneReplace, "MapScene");
    INIT_SCENE(kStageScene, StageSceneReplace, "StageScene");
    INIT_SCENE(kEnhanceScene, EnhanceSceneReplace, "PetEnhanceScene");
    INIT_SCENE(kUintScene, UintSceneReplace, "UnitScene");
    INIT_SCENE(kPetShowScene, PetShowSceneReplace, "PetShowScene");
    INIT_SCENE(kEvolveScene, EvolveSceneReplace, "EvolveScene");
    INIT_SCENE(kTeamScene, TeamSceneReplace, "EditTeamScene");
    INIT_SCENE(kPetBagSaleScene, PetBagSaleSceneReplace, "PetBagSaleScene");
    INIT_SCENE(kArenaIndexScene, ArenaIndexSceneReplace, "ArenaMainScene");
    INIT_SCENE(kArenaRankListScene, ArenaRankListSceneReplace, "ArenaRankScene");
    INIT_SCENE(kArenaBattleListScene, ArenaBattleListSceneReplace, "ArenaBattleListScene");
    INIT_SCENE(kArenaShopScene, ArenaShopSceneReplace, "ArenaShopScene");
    INIT_SCENE(kArenaRankRewardScene, ArenaArenaRankRewardReplace, "ArenaRankRewardScene");
    INIT_SCENE(kCaptureScene, CaptureSceneReplace, "CaptureScene");
    INIT_SCENE(kFriendScene, FriendSceneReplace, "FriendScene");
    INIT_SCENE(kMailListScene, MailListSceneReplace, "MailListScene");
    INIT_SCENE(kGachaScene, GachaSceneReplace, "GachaScene");
    INIT_SCENE(kSystemScene, SystemSceneReplace, "SettingsScene");
    INIT_SCENE(kPetTujian, PetTujianSceneReplace, "PetTujianScene");
    INIT_SCENE(kItemListScene, ItemListSceneReplace, "ItemListScene");
    INIT_SCENE(kPveBattleScene, PveBattleSceneReplace, "PetPveBattleScene");
    INIT_SCENE(kArenaFightScene, ArenaFightSceneReplace, "AreanFightPvPSecne");
    INIT_SCENE(kShowPetTujian, PettujianShowSceneReplace, "PetTujianShowScene");

    INIT_SCENE(kActivityMapScene, ActivityMapSceneReplace, "ActivityScene");
    INIT_SCENE(kBuildUpScene, BuildUpSceneReplace, "BuildUpScene");
    INIT_SCENE(kFriendMailScene, FriendMailSceneReplace, "FriendMailScene");
    INIT_SCENE(kShopGemListScene, EnterShopGemListReplace, "ShopGemListScene");
    INIT_SCENE(kShopNoramlListScene, EnterShopNormalListReplace, "ShopNormalListScene");
    INIT_SCENE(kEquipListScene, EquipListSceneReplace, "EquipListScene");
    INIT_SCENE(kEquipInlayScene, EquipInlaySceneReplace, "EquipInlayScene");
    INIT_SCENE(kEquipStrengthenScene, EquipStrengthenSceneReplace, "EquipStrengthenScene");
    INIT_SCENE(kEquipEvolveScene, EquipEvolveSceneReplace, "EquipEvolveScene");
    INIT_SCENE(kEquipCompoundListScene, EquipCompoundListSceneReplace, "EquipCompoundListScene");
    INIT_SCENE(kEquipCompoundInfoScene, EquipCompoundInfoSceneReplace, "EquipCompoundInfoScene");
    INIT_SCENE(kFightRewad, FightRewardSceneReplace, "FightRewardScene");
    INIT_SCENE(kEventScene, EventMainSceneReplace, "EventMainScene");
    INIT_SCENE(kAwardCenterScene, EnterAwardCenterSceneReplace, "AwardCenterScene");
    INIT_SCENE(kAchieveRewardScene, EnterAchieveRewardSceneReplace, "AchieveRewardScene");
    INIT_SCENE(kDailyQuestRewardScene, EnterDailyQuestRewardSceneReplace, "DailyQuestRewardScene");
    INIT_SCENE(kExchangeCodeScene, EnterExchangeCodeSceneReplace, "ExchangeCodeScene");
    INIT_SCENE(kPetFuse, PetFuseSceneReplace, "PetFuseScene");
    INIT_SCENE(kInviteFriendScene, InviteFriendSceneReplace, "InviteFriendScene");
    INIT_SCENE(kAccountBindingScene, AccountBindingSceneReplace, "AccountBindingScene");
    INIT_SCENE(kGachaResultScene, GachaResultSceneReplace, "GachaResultScene");
    INIT_SCENE(kFriendSystemScene, FriendSystemSceneReplace, "SystemScene");
    INIT_SCENE(kEvolveResult, PetEvolveSceneReplace, "PetEvolveSuccessScene");
    INIT_SCENE(kFuseList, FuseListSceneReplace, "FuseListScene");
    INIT_SCENE(kVipListScene, VIPListSceneReplace, "VipListScene");
    INIT_SCENE(kArenaResultScene, ArenaResultSceneReplace, "ArenaResultScene");
    INIT_SCENE(kChatScene, ChatSceneReplace, "ChatScene");
    INIT_SCENE(kPetBattleLoadingScene, PetBattleLoadingSceneReplace, "PetBattleLoading");
    INIT_SCENE(kEmblemListSenec, EmblemSceneReplace, "EmblemListScene");
    INIT_SCENE(kEmblemEnhSenec, EmblemEnhSceneReplace, "EmblemEnhanceScene");
    INIT_SCENE(kTowerMainScene, TowerMainSceneReplace, "TowerMainScene");
    INIT_SCENE(kChallengeMapScene, ChallengeMapSceneReplace, "ChallengeMapLayer");
    INIT_SCENE(kEquipIntegrationScene, EquipIntegrationSceneReplace, "EquipIntegrationScene");
    INIT_SCENE(kPetInfoScene, PetInfoSceneReplace, "PetInfoScene");
    INIT_SCENE(kEmblemChooseScene, EmblemChooseSceneReplace, "EmblemChooseScene");
    INIT_SCENE(kWorldBossScene, WorldBossSceneReplace, "WorldBossScene");
    INIT_SCENE(kChallengeIndexScene, ChallengeIndexSceneReplace, "ChallengeIndexScene");
    INIT_SCENE(kChallengeType1Scene, ChallengeType1SceneReplace, "ChallengeType1Scene");
    INIT_SCENE(kChallengeType2Scene, ChallengeType2SceneReplace, "ChallengeType2Scene");
    INIT_SCENE(kChallengeType3Scene, ChallengeType3SceneReplace, "ChallengeType3Scene");
    INIT_SCENE(kWorldBossFightScene, WorldBossFightSceneReplace, "WorldBossFightScene");
    INIT_SCENE(kFriendUnitScene, FriendUnitSceneReplace, "FriendUnitScene");
    INIT_SCENE(kItemPatchScene, ItemPatchSceneReplace, "ItemPatchScene");
    INIT_SCENE(kMySteryShopScene, MySteryShopSceneReplace, "MySteryShopScene");
}

BackCtrl::LAYER_FUNC BackCtrl::FindSceneFunc(int key)
{
    switch (key) {
        case kMainScene:
            GlobalData::kBottomTag = GlobalData::kMainBottom;
            break;
        case kUintScene:
            GlobalData::kBottomTag = GlobalData::kTeamBottom;
            break;
        case kCountryScene:
            GlobalData::kBottomTag = GlobalData::kCityBottom;
            break;
        case kGachaScene:
            GlobalData::kBottomTag = GlobalData::kGachaBottom;
            break;
        case kBuyScene:
            GlobalData::kBottomTag = GlobalData::kShopBottom;
            break;
        case kEventScene:
            GlobalData::kBottomTag = GlobalData::kEventBottom;
            break;
        case kFriendScene:
            GlobalData::kBottomTag = GlobalData::kFriendBottom;
            break;
        case kStageScene:
            GlobalData::kBottomTag = GlobalData::kStageBottom;
            break;
        case kChatScene:
            GlobalData::kBottomTag = GlobalData::kChatBottom;
            break;
        case kArenaIndexScene:
            GlobalData::kBottomTag = GlobalData::kAreanBottom;
            break;
        case kActivityMapScene:
            GlobalData::kBottomTag = GlobalData::kActiveMapBottom;
            break;
        default:
            GlobalData::kBottomTag = 999;
            break;
    }
    
    AnalysicsManager::sharedAnalyticsMgr()->SendBeginPageView(m_mapName[key].c_str());
    
    MAP_LAYER_FUNCS::iterator ii = m_mapLayerFuncs.find(key);
    if (ii == m_mapLayerFuncs.end()) {
        CCMessageBox("Wrong Scene Index, check BackCtrl for more", "Error");
        return NULL;
    }
    return ii->second;
}

void BackCtrl::endCurScene() {
    int k = GetCurSceneIdx();
    AnalysicsManager::sharedAnalyticsMgr()->SendEngPageView(m_mapName[k].c_str());
    CCLog("end scene name:%s, used mem:%lf", m_mapName[k].c_str(), Support::sharedInstance()->usedMem());
}

bool BackCtrl::BacktoUpperScene(int kind)
{
    endCurScene();
    if ((GetCurSceneIdx() == kTeamScene && GlobalData::bNeecConnection)) {
        m_waitIdx = GetPreviousIdx();
        bHaveWait = true;
        CTeamCtrl::SaveTeamUpdate();
//        PetLoadingLayer::sharedLayer()->WaitForPacket();
        return true;
    } else {
        BackCtrl::LAYER_FUNC pFunc;
        if (GetCurSceneIdx() == kMapScene) {
            pFunc = FindSceneFunc(kMainScene);
            m_vecScene.clear();
        }
        else {
            pFunc = FindSceneFunc(GetPreviousIdx());
        }
        if (pFunc) {
            (*pFunc)(kind);
            return true;
        } else {
            CCMessageBox("Back to Upper Scene Error", "Error");
            return false;
        }
    }
}

bool BackCtrl::InsertNextScene(int value, int kind)
{
    endCurScene();
    if (kind == kOnlyForBack) {
        m_vecScene.push_back(value);
        return true;
    }
    if (GlobalData::bNeecConnection) {
        m_vecScene.push_back(value);
        m_waitIdx = value;
        bHaveWait = true;
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        if (CTeamCtrl::GetTeamChanged()) {
            CTeamCtrl::SaveTeamUpdate();
        }
    }
    
    // 不支持同一个界面加载两次}
    //[2014-12-10] Stage界面支持多次加载，新需求需要从当前关卡跳转到下一个新开关卡
    if (value == GetCurSceneIdx() && value != kStageScene) {
        return false;
    }
    
    // 抓捕成功后服务器重发数据包，不能直接加界面，需要重建界面，因为之前的为抓捕界面}
    
    if (CCDirector::sharedDirector()->GetSceneStackCnt() > 1) { //
        CCMessageBox("Warning!!!!!", "Warning");
    }
    
    if (value == kMapScene) {
        m_vecScene.clear();
        m_vecScene.push_back(kMainScene);
    }
    
    // 此时有战斗等其他界面，需要等其结束之后再跳转，战斗后都是跳转到前面出现过的scene。}
    if (GetCurSceneIdx() == kPveBattleScene || GetCurSceneIdx() == kArenaFightScene) {
        if (value != kFightRewad) {
            return false;
        }
    }
    
    BackCtrl::LAYER_FUNC pFunc = FindSceneFunc(value);
    if (pFunc) {
        (*pFunc)(kind);
        m_vecScene.push_back(value);
        return true;
    } else {
        CCMessageBox("Insert Scene Error", "Error");
        return false;
    }
    return true;
}

bool BackCtrl::ChangeRootScene(int value, int kind)
{
    endCurScene();
    m_vecScene.clear();
    if (GlobalData::bNeecConnection) {
        m_vecScene.push_back(value);
        m_waitIdx = value;
        bHaveWait = true;
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        if (CTeamCtrl::GetTeamChanged()) {
            CTeamCtrl::SaveTeamUpdate();
        }
        return true;
    }
    
    BackCtrl::LAYER_FUNC pFunc = FindSceneFunc(value);
    if (pFunc) {
        (*pFunc)(kind);
        m_vecScene.push_back(value);
        return true;
    } else {
        CCMessageBox("Change Root Scene error", "Error");
        return false;
    }
    
    return true;
}

bool BackCtrl::AddWaitScene()
{
    endCurScene();;
    CCLog(">>>>>>>>>>>>>>>>>>>>%d", m_waitIdx);
    PetLoadingLayer::sharedLayer()->End();
    if (!bHaveWait) {
        return true;
    }
    CCLOG("add wait scene:%d", m_waitIdx);
    bHaveWait = false;
    
    BackCtrl::LAYER_FUNC pFunc = FindSceneFunc(m_waitIdx);
    if (pFunc) {
        (*pFunc)(0);
        m_waitIdx = 0;
        return true;
    } else {
        CCMessageBox("Add Wait Scene error", "Error");
        return false;
    }
    return false;
}

bool BackCtrl::JumpToScene(int value, int cycle)
{
    endCurScene();
    if (m_vecScene.empty()) {
        value = 0;
    } else {
        while ( !(m_vecScene.back() == value && cycle == 0) ) {
            if (m_vecScene.empty()) {
                value = 0;
                break;
            } else {
                if (m_vecScene.back() == value) {
                    cycle--;
                }
                m_vecScene.pop_back();
            }
        }
    }
    BackCtrl::LAYER_FUNC pFunc = FindSceneFunc(value);
    if (pFunc) {
        (*pFunc)(0);
        return true;
    } else {
        CCMessageBox("Jump Scene Error", "Error");
        return false;
    }
    return true;
}

bool BackCtrl::PvpJumpBack()
{
    endCurScene();
    int value = 0;
    while (!m_vecScene.empty()) {
        if (m_vecScene.back() == kCaptureScene) {
            // 抓捕界面跳转}
            value = kCaptureScene;
            break;
        }
        if (m_vecScene.back() == kArenaIndexScene) {
            value = kArenaIndexScene;
            break;
        }
        m_vecScene.pop_back();
    }
    BackCtrl::LAYER_FUNC pFunc = FindSceneFunc(value);
    if (pFunc) {
        (*pFunc)(0);
        return true;
    } else {
        CCMessageBox("PvP Jump Back Error", "Error");
        return false;
    }
    return true;
}

bool BackCtrl::ReplaceCurScene(int value, int kind)
{
    endCurScene();
    if (!m_vecScene.empty()) {
        GetPreviousIdx();
    }
    
    BackCtrl::LAYER_FUNC pFunc = FindSceneFunc(value);
    if (pFunc) {
        (*pFunc)(kind);
        m_vecScene.push_back(value);
        return true;
    } else {
        CCMessageBox("Replace Scene error", "Error");
        return false;
    }
    
    return true;
}

int BackCtrl::GetCurSceneIdx()
{
    int k = 0;
    if (!m_vecScene.empty()) {
        k = m_vecScene.back();
    }
    return k;
}

int BackCtrl::GetPreviousIdx()
{
    int cur = 0;
    
    if (!m_vecScene.empty()) {
        m_vecScene.pop_back();
    }
    if (!m_vecScene.empty()) {
        cur = m_vecScene.back();
    }
    
    return cur;
}

void BackCtrl::ClearSceneStack()
{
    m_vecScene.clear();
    m_waitIdx = 0;
    bHaveWait = false;
}

#pragma mark Replace Methods

void BackCtrl::SceneReplace(int kind, cocos2d::CCScene *pScene)
{
    switch (kind) {
        case kDelayTrans:
            CCDirector::sharedDirector()->replaceScene(CCTransitionDelay::create(TRANS_DUR, pScene));
            break;
        case kFadeTrans:
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(TRANS_DUR, pScene));
            break;
        case kNormalTrans:
            CCDirector::sharedDirector()->replaceScene(pScene);//CCTransitionLoading::create(TRANS_DUR, pScene));
        default:
            break;
    }
}

void BackCtrl::MainSceneReplace(int kind)
{
    CCScene* pScene = MainScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::BuySceneReplace(int kind)
{
    CCScene* pScene = BuyScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PetBagSceneReplace(int kind)
{
    CCScene* pScene = PetBagScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::CountrySceneReplace(int kind)
{
    CCScene* pScene = CountryScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::MapSceneReplace(int kind)
{
    CCScene* pScene = MapScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::StageSceneReplace(int kind)
{
    CCScene* pScene = StageScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnhanceSceneReplace(int kind)
{
    CCScene* pScene = PetEnhanceScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::UintSceneReplace(int kind)
{
    CCScene *pScene = UnitMiddleScene::scene();
    SceneReplace(kind, pScene);
}
void BackCtrl::PetShowSceneReplace(int kind)
{
    CCScene *pScene = CcbPetShowScene::scene();
    SceneReplace(kind, pScene);
}
void BackCtrl::EvolveSceneReplace(int kind)
{
    CCScene *pScene = EvolveScene::scene();
    SceneReplace(kind, pScene);
}
void BackCtrl::TeamSceneReplace(int kind)
{
    CCScene *pScene = TeamScene::scene();
    SceneReplace(kind, pScene);
}
void BackCtrl::PetBagSaleSceneReplace(int kind)
{
    CCScene *pScene = PetBagSaleScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::CaptureSceneReplace(int kind)
{
    CCScene* pScene = CaptureScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::FriendSceneReplace(int kind)
{
    CCScene* pScene = FriendScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaIndexSceneReplace(int kind)
{
    CCScene* pScene = CcbArenaIndexScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaRankListSceneReplace(int kind)
{
    CCScene* pScene = CcbArenaRankScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaBattleListSceneReplace(int kind)
{
    CCScene* pScene = CcbArenaBattleScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaShopSceneReplace(int kind)
{
    CCScene* pScene = CcbArenaShopScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaArenaRankRewardReplace(int kind)
{
    CCScene* pScene = CcbArenaRankRewardScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::MailListSceneReplace(int kind)
{
    CCScene* pScene = CcbMailListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::GachaSceneReplace(int kind)
{
    CCScene* pScene = GachaScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::SystemSceneReplace(int kind)
{
    CCScene* pScene = CcbSettingsScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PetTujianSceneReplace(int kind)
{
    CCScene *pScene = PetTujianScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ItemListSceneReplace(int kind)
{
    CCScene *pScene = CcbItemListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PveBattleSceneReplace(int kind)
{
    CCScene* pScene = PetBattleScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaFightSceneReplace(int kind)
{
    CCScene* pScene = AreanFightSecne::scene();
    SceneReplace(kind, pScene);
}


void BackCtrl::PettujianShowSceneReplace(int kind)
{
    CCScene *pScene = PetTujianShowScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ActivityMapSceneReplace(int kind)
{
    CCScene* pScene = ActivityScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::BuildUpSceneReplace(int kind)
{
    CCScene* pScene = BuildUpScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::FriendMailSceneReplace(int kind)
{
    CCScene* pScene = FriendMailScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnterShopGemListReplace(int kind)
{
    CCScene* pScene = CcbShopGemListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnterShopNormalListReplace(int kind)
{
    CCScene* pScene = CcbShopNormalListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipListSceneReplace(int kind)
{
    CCScene* pScene = CcbEquipListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipInlaySceneReplace(int kind)
{
    CCScene* pScene = CcbEquipInlayScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipStrengthenSceneReplace(int kind)
{
    CCScene* pScene = CcbEquipStrengthenScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipEvolveSceneReplace(int kind)
{
    CCScene* pScene = CcbEquipEvolveScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipCompoundListSceneReplace(int kind)
{
    CCScene* pScene = CcbEquipCompoundListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipCompoundInfoSceneReplace(int kind)
{
    CCScene* pScene = CcbEquipCompoundInfoScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::FightRewardSceneReplace(int kind)
{
    CCScene* pScene = FightRewardScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EventMainSceneReplace(int kind)
{
    CCScene* pScene = CcbEventMainScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnterAwardCenterSceneReplace(int kind)
{
    CCScene* pScene = CcbAwardCenterScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnterAchieveRewardSceneReplace(int kind)
{
    CCScene* pScene = CcbAchieveRewardScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnterDailyQuestRewardSceneReplace(int kind)
{
    CCScene* pScene = CcbDailyQuestRewardScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EnterExchangeCodeSceneReplace(int kind)
{
    CCScene* pScene = CcbExchangeCodeScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PetFuseSceneReplace(int kind)
{
    CCScene* pScene = PetFuseScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::InviteFriendSceneReplace(int kind)
{
    CCScene* pScene = CcbInviteFriendScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::AccountBindingSceneReplace(int kind)
{
    CCScene* pScene = CcbAccountBindingScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::GachaResultSceneReplace(int kind)
{
    CCScene* pScene = GachaResultScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::FriendSystemSceneReplace(int kind)
{
    CCScene* pScene = SystemScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PetEvolveSceneReplace(int kind)
{
    CCScene* pScene = PetEvolveSuccessScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::FuseListSceneReplace(int kind)
{
    CCScene* pScene = FuseListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::VIPListSceneReplace(int kind)
{
    CCScene* pScene = CcbVipListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ArenaResultSceneReplace(int kind)
{
    CCScene* pScene = CcbArenaResultScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ChatSceneReplace(int kind)
{
    CCScene* pScene = ChatScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PetBattleLoadingSceneReplace(int kind)
{
    CCScene* pScene = CcbPetBattleLoading::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EmblemSceneReplace(int kind)
{
    CCScene* pScene = EmblemListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EmblemEnhSceneReplace(int kind)
{
    CCScene* pScene = EmblemEnhanceScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::TowerMainSceneReplace(int kind)
{
    CCScene* pScene = CcbTowerMainScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ChallengeMapSceneReplace(int kind)
{
    CCScene* pScene = CcbChallengeMapLayer::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EquipIntegrationSceneReplace(int kind)
{
    CCScene* pScene = CcbEquipIntegrationScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::PetInfoSceneReplace(int kind)
{
    CCScene* pScene = CcbPetInfoScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::EmblemChooseSceneReplace(int kind)
{
    CCScene* pScene = EmblemChooseListScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::WorldBossSceneReplace(int kind)
{
    CCScene* pScene = WorldBossScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ChallengeIndexSceneReplace(int kind)
{
    CCScene* pScene = ChallengeIndexScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ChallengeType1SceneReplace(int kind)
{
    CCScene* pScene = ChallengeType1Scene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ChallengeType2SceneReplace(int kind)
{
    CCScene* pScene = ChallengeType2Scene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ChallengeType3SceneReplace(int kind)
{
    CCScene* pScene = ChallengeType3Scene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::WorldBossFightSceneReplace(int kind)
{
    CCScene* pScene = WorldBossFightScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::FriendUnitSceneReplace(int kind) {
    CCScene* pScene = FriendUnitScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::ItemPatchSceneReplace(int kind)
{
    CCScene* pScene = ItemPatchScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::MySteryShopSceneReplace(int kind)
{
    CCScene* pScene = CcbMySteryShopScene::scene();
    SceneReplace(kind, pScene);
}

void BackCtrl::changeNextSceneWithSafety(int value,int childValue)
{
    switch (value) {
        case kChatScene:
        {
            BackCtrl::InsertNextScene(value);
            break;
        }
        case kArenaIndexScene:
        {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ARENA);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            
            if (g_ArenaData->GetPlayerInfo().dwUserId != 0) {
                BackCtrl::ChangeRootScene(kArenaIndexScene);
            }
            else
            {
                PetLoadingLayer::sharedLayer()->WaitForPacket(true);
                CGameSession::SendEnterArenaSceneRequest();
            }
            break;
        }
        case kGachaScene:
        {
            CPetCtrl::Get()->setPetTujianShowId(0);
            g_GachaData->setIsBoardOpen(false);
            PetLoadingLayer::sharedLayer()->WaitForPacket(true);
            BackCtrl::InsertNextScene(kGachaScene);
            break;
        }
        case kMapScene:
        {
            StageCtrl::Get()->setKind(StageCtrl::kNormalStage);
            CGameSession::SendNormalMap();
            break;
        }
        case kStageScene:
        {
            
            break;
        }
        case kEnhanceScene:
        {
//            CPetCtrl::Get()->SetIntensifyPet(CPetCtrl::Get()->GetShowPetObjId());
            CPetCtrl::Get()->SetPetBagType(CPetCtrl::E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY);
            BackCtrl::InsertNextScene(kPetBagScene);
            break;
        }
        case kActivityMapScene:
        {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_ACTIVITY);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            
            StageCtrl::Get()->setFromJump(false);
            if (childValue != 0) {
                SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, childValue);
                if (!pConfig) {
                    CCLog("Cannot get Special Map config.");
                    return;
                }                
                std::string m_strMapName = pConfig->strMapName;
                
                StageCtrl::Get()->setSelectedActivityMapIdx(childValue);
                StageCtrl::Get()->setCurMapPointName(m_strMapName);
                ChallengeCtrl::Get()->setChallengeType(childValue);
                CGameSession::SendSpecialStageInfo(childValue);
            }
            else
            {
                
                ChallengeCtrl::Get()->setChallengeStage(ChallengeCtrl::E_CHALLENGE_NONE);
                CGameSession::SendSpecialMapList();
            }
            
            break;
        }
        case kEmblemListSenec:
        {
            {
                uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
                SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
                if (cfg) {
                    FlyTextLayer::showTips(cfg->strDescShow.c_str());
                    PetLoadingLayer::sharedLayer()->End();
                    return;
                }
            }
            g_EmblemData->setEmbInType(E_EMB_IN_TYPE_ALL);
            BackCtrl::InsertNextScene(kEmblemListSenec);
            break;
        }
        case kTowerMainScene:
        {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_PATA);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            
            CGameSession::SendRequestTowerInfo();
            break;
        }
        case kChallengeMapScene:
        {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_YIJI);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                return;
            }
            
            CGameSession::SendReqChallengeInfo();
            break;
        }
        case kEquipIntegrationScene:
        {
            uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_UNIT_EQUIP);
            SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
            if (cfg) {
                FlyTextLayer::showTips(cfg->strDescShow.c_str());
                PetLoadingLayer::sharedLayer()->End();
                return;
            }
            g_EquipData->SetDressEquipPart(0);
            g_EquipData->setIsEquipShow(false);
            BackCtrl::InsertNextScene(kEquipIntegrationScene);
            break;
        }
        default:
        {
            CCLOG("Have Unknow Scene value = %d",value);
            break;
        }
    }
}

void BackCtrl::changeNextSceneWithSafety(const char *nextScene)
{
    if (!nextScene) {
        return;
    }
    int nNextScene = 0,nChild = 0;
    CCString* cStr = NULL;
    CCArray* pArray = ccs(nextScene)->componentsSeparatedByString("_");
    for (int i = 0;pArray && i < pArray->count(); i++) {
        cStr = (CCString *)pArray->objectAtIndex(i);
        if (!cStr) {
            continue;
        }
        switch (i) {
            case 0:
                nNextScene = atoi(cStr->getCString());
                break;
            case 1:
            {
                nChild = atoi(cStr->getCString());
                break;
            }
            default:
                break;
        }
    }
    BackCtrl::changeNextSceneWithSafety(nNextScene,nChild);
}
