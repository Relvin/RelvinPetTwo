#include "GameSession.h"
#include "CmdDefine.h"
#include "NetClient.h"
#include "AppDelegate.h"
#include "ConfigData.h"
#include "Role.h"
#include "StartGameLayer.h"
#include "StartGameScene.h"
#include "PetCtrl.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "GlobalData.h"
#include "ArenaDataMgr.h"
#include "MailDataMgr.h"
#include "ItemDataMgr.h"
#include "GachaDataMgr.h"
#include "BackCtrl.h"
#include "SystemMessage.h"
#include "ServerListCtrl.h"
#include "FriendCtrl.h"
#include "StageScene.h"
#include "BuildUpScene.h"
#include "ShopDataMgr.h"
#include "LoginSystem.h"
#include "CPetMgr.h"
#include "EquipDataMgr.h"
#include "FightAI.h"
#include "EventDataMgr.h"
#include "GuideData.h"
#include "TaskDataMgr.h"
#include "CFuseDadaMgr.h"
#include "BuyDataMgr.h"
#include "ChatDataMgr.h"
#include "EmblemDataMgr.h"
#include "TowerDataMgr.h"
#include "PacketDataMgr.h"
#include "CcbCache.h"
#include "ChallengeDataMgr.h"
#include "SystemNoticeDataMgr.h"
#include "ResourcePic.h"
#include "ChallengeCtrl.h"
#include "UserInfoDataMgr.h"
#include "WorldInfoDataMgr.h"
#include "WorldBossDataMgr.h"
#include "FriendUnitDataMgr.h"
#include "CcbJumpTipLayer.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

#include "CheckPointMgr.h"
#include "GuideBtnPos.h"
#include "MapScene.h"

USING_NS_CC;

CRole * CGameSession::m_pRole = NULL;
std::set<CObserverMsg *> CGameSession::m_setObservers;

bool CGameSession::Init()
{
    m_setObservers.clear();
    if (!m_pRole)
    {
        m_pRole = new CRole();
        if (!m_pRole)
        {
            CCMessageBox("Create Role Info Erroe", "Error");
            return false;
        }
    }
    CCLog("Game Session Init");
    CPetCtrl::Get()->Create();
    CArenaDataMgr::Get()->Create();
    CMailDataMgr::Get()->Create();
    CItemDataMgr::Get()->Create();
    CGachaDataMgr::Get()->Create();
    ServerListCtrl::Get()->Create();
    FriendCtrl::Get()->Create();
    StageCtrl::Get()->Create();
    CBuildUpDataMgr::Get()->Create();
    CShopDataMgr::Get()->Create();
    LoginSystem::Get()->Create();
    CPetMgr::Get()->Create();
    g_EquipData->Create();
    g_EventData->Create();
    FightAI::Get()->Create();
    CcbCache::clearDataMap();

    GuideData::GetInstance();
    g_TaskData->Create();
    
    g_FuseDada->Create();
    BuyDataMgr::Get()->Create();
    ChatDataMgr::Get()->Create();
    g_EmblemData->Create();
    g_TowerDataMgr->Create();
    g_PacketDataMgr->Create();
    g_ChallengeDataMgr->Create();
    g_SystemNoticeDataMgr->Create();
    g_EquipTeamData->Create();
    ChallengeCtrl::Get()->Create();
    UserInfoDataMgr::Get()->Create();
    CheckPointMgr::Get()->Create();
    GuideBtnPos::Get()->Create();
    WorldInfoDataMgr::Create();
    g_WorldBossData->Create();
    FriendUnitDataMgr::Get()->Create();
    CShowJumpTip::Get()->Create();
    
    CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile(GET_PIC(Pic_face_plist), GET_PIC(Pic_face_pvr_ccz));
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("launch_over");
#endif
    return true;
}

void CGameSession::UnInit()
{
    GlobalData::bLoginAccount = true;
    CCLog("Game Session UnInit");
    
    BackCtrl::ClearSceneStack();
    CPetCtrl::Get()->Destory();
    CTeamCtrl::UnInit();
    SystemMessage::UnInit();
    
    BuyDataMgr::Get()->Destory();
    CArenaDataMgr::Get()->Destory();
    CMailDataMgr::Get()->Destory();
    CItemDataMgr::Get()->Destory();
    CGachaDataMgr::Get()->Destory();
    ServerListCtrl::Get()->Destory();
    FriendCtrl::Get()->Destory();
    StageCtrl::Get()->Destory();\
    CBuildUpDataMgr::Get()->Destory();
    CShopDataMgr::Get()->Destory();
    LoginSystem::Get()->Destory();
    CPetMgr::Get()->Destory();
    g_EquipData->Destory();
    g_EventData->Destory();
    GuideData::DestoryInstace();
    g_TaskData->Destory();
    g_FuseDada->Destory();
    ChatDataMgr::Get()->Destory();
    g_EmblemData->Destory();
    g_TowerDataMgr->Destory();
    g_PacketDataMgr->Destory();
    g_ChallengeDataMgr->Destory();
    g_SystemNoticeDataMgr->Destory();
    g_EquipTeamData->Destory();
    ChallengeCtrl::Get()->Destory();
    UserInfoDataMgr::Get()->Destory();
    CheckPointMgr::Get()->Destory();
    GuideBtnPos::Get()->Destory();
    WorldInfoDataMgr::Destory();
    g_WorldBossData->Destory();
    FriendUnitDataMgr::Get()->Destory();
    CShowJumpTip::Get()->Destory();
    
    GlobalData::bUseIpaResource = false;
    GlobalData::bFromPetChoose = false;
    GlobalData::kBottomTag = GlobalData::kMainBottom;
    GlobalData::nCurNormalAreaIdx = -1;
    GlobalData::nCurHeroAreaIdx = -1;
    
    CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->removeSpriteFramesFromFile(GET_PIC(Pic_face_plist));
    
    CcbCache::clearDataMap();
    GlobalData::nReconnetCnt = 0;
    
    CCDirector::sharedDirector()->purgeCachedData();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void CGameSession::BackToLogin()
{
    GlobalData::bReConnectFlag = false;

    LoginSystem::Get()->setConnectStatus(LoginSystem::E_UNCONNECTED);
    if (!StartGameLayer::GetCurLayer()) {
        CGameSession::UnInit();
    }
    AppDelegate::sharedAppDelegate()->netClient()->OnDisConnect();
    
    while(CCDirector::sharedDirector()->GetSceneStackCnt() > 1) {
        CCScene *runningScene = CCDirector::sharedDirector()->getNowScene();
		runningScene->cleanup();
		CCDirector::sharedDirector()->popScene();
    }

    if (!StartGameLayer::GetCurLayer()) {
        CCScene* pScene = StartGameScene::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
        m_pRole->SetwGuideTrigger(0);
    }
}

void CGameSession::SendLoginTest()
{
    WorldPacket packet(CMD_LOGIN_CS_TEST);
    packet << "LoginServerHeartBeatTest";   // 24
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

void CGameSession::SendTest()
{
    WorldPacket packet(CMD_CS_TEST);
    packet << "GameServerHeartBeatTest.";   // 24
	CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
	pNetClient->SendData(packet);
}

void CGameSession::SendUserLoginServer(uint32 dwUserId, uint16 wAreaId)
{
    WorldPacket packet(CMD_LOGIN_CS_GM_LOGIN);
    packet << dwUserId << wAreaId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

void CGameSession::SendUserGameServer(uint32 dwUserId, uint16 wAreaId)
{
    WorldPacket packet(CMD_CS_GM_LOGIN);
    packet << dwUserId << wAreaId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//    #define CMD_LOGIN_CS_REQ_LIST			CMD_MAKE_CLIENT(0x0055)		//客户端 获取服务器列表}
void CGameSession::SendRequestServerList(
                                         string strAccount,
                                         string strDevice,
                                         string strVersion,
                                         uint32 dwPaltFrom
                                         )
{
    WorldPacket packet(CMD_LOGIN_CS_REQ_LIST);
    packet << strAccount << strDevice << strVersion << dwPaltFrom;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
	pNetClient->SendData(packet);
}

//    #define CMD_LOGIN_CS_LOGIN				CMD_MAKE_CLIENT(0x0051)		//注册帐号 登录{ std::string uid + uint32版本号 string name + string pwd  + uint16 wAreaId}
void CGameSession::SendGameLogin(std::string strUid,
                          uint32 dwVer,
                          std::string strName,
                          std::string strPwd,
                          uint16 wAreaId)
{
    WorldPacket packet(CMD_LOGIN_CS_LOGIN);
    packet << strUid;
    packet << dwVer;
    packet << strName;
    packet << strPwd;
    packet << wAreaId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//    #define CMD_LOGIN_CS_REG				CMD_MAKE_CLIENT(0x0052)		//注册帐号 注册 {std::string uid + uint32版本号 string name + string pwd + string mail + string reg_device + string reg_device_type}
void CGameSession::SendGameReg(std::string strUid,
                        uint32 dwVer,
                        std::string strName,
                        std::string strPwd,
                        std::string strMail,
                        std::string strDevice,
                        std::string strDevType,
                        uint32 dwPlatForm)
{
    // [2014-04-25] add dwPlatForm, 渠道号}
    WorldPacket packet(CMD_LOGIN_CS_REG);
    packet << strUid;
    packet << dwVer;
    packet << strName;
    packet << strPwd;
    packet << strMail;
    packet << strDevice;
    packet << strDevType;
    packet << dwPlatForm;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//    #define CMD_LOGIN_CS_FAST_LOGIN			CMD_MAKE_CLIENT(0x0053)		//快速登录 { std::string uid + uint32版本号 + string name + string pwd + uint16 wAreaId + string reg_device + string reg_device_type}
void CGameSession::SendGameFastLogin(std::string strUid,
                              uint32 dwVer,
                              std::string strName,
                              std::string strPwd,
                              uint16 wAreaId,
                              std::string strDevice,
                              std::string strDevType,
                                     uint32 dwPlatForm)
{
    // [2014-04-25] add dwPlatForm, 渠道号}
    WorldPacket packet(CMD_LOGIN_CS_FAST_LOGIN);
    packet << strUid;
    packet << dwVer;
    packet << strName;
    packet << strPwd;
    packet << wAreaId;
    packet << strDevice;
    packet << strDevType;
    packet << dwPlatForm;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//    #define \		CMD_MAKE_CLIENT(0x0054)		//第三方平台 登录 { std::string uid +  uint32版本号 + string name +  string pwd + uint16 wAreaId + string reg_device + string reg_device_type}
void CGameSession::SendGameOtherLogin(std::string strUid,
                               uint32 dwVer,
                               std::string strName,
                               std::string strPwd,
                               uint16 wAreaId,
                               std::string strDevice,
                               std::string strDevType,
                                      uint32 dwPlatForm)
{
    // [2014-04-25] add dwPlatForm, 渠道号}
    
    CCLog("send uid:%s", strUid.c_str());
    
    WorldPacket packet(CMD_LOGIN_CS_OTHER_LOGIN);
    packet << strUid;
    packet << dwVer;
    packet << strName;
    packet << strPwd;
    packet << wAreaId;
    packet << strDevice;
    packet << strDevType;
    packet << dwPlatForm;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//CMD_CS_REQ_PEV_BATTLE_INFO
//void CGameSession::SendReqPVEBattleInfo()
//{
//    WorldPacket packet(CMD_CS_REQ_PEV_BATTLE_INFO);
//
//    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
//    pNetClient->SendData(packet);
//
//}

//#define CMD_CS_CLIENT_AUTH			CMD_MAKE_CLIENT(0x0001) //注册账号 请求认证{string strUid + uint32 dwVersion + string strAcess + string 密码 + uint16 wAreaId }
void CGameSession::SendAccountAuth(std::string strUid, uint32 dwVersion, std::string strUsername, std::string strPassword, uint16 wAreaId, std::string strDevice)
{
    // [2014-04-25] add strDevice, separate iOS or Android
    WorldPacket packet(CMD_CS_CLIENT_AUTH);
    
    packet << strUid << dwVersion << strUsername << strPassword << wAreaId << strDevice;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_FAST_AUTH			CMD_MAKE_CLIENT(0x0002) //快速登录 请求认证{string strUid,uint32 dwVersion string(32)用户名;string(32)密码 + uint16 wAreaId}
void CGameSession::SendFastAuth(std::string strUid, uint32 dwVersion, std::string strUsername, std::string strPassword, uint16 wAreaId, std::string strDevice)
{
    // [2014-04-25] add strDevice, separate iOS or Android
    WorldPacket packet(CMD_CS_FAST_AUTH);
    
    packet << strUid << dwVersion << strUsername << strPassword << wAreaId << strDevice;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_OTHER_AUTH			CMD_MAKE_CLIENT(0x0003) //客户端请求91快速认证{string strUid,uint32 dwVersion string(32)用户名;string(32)密码+ uint16 wAreaId}
void CGameSession::SendThirdAuth(std::string strUid, uint32 dwVersion, std::string strUsername, std::string strPassword, uint16 wAreaId, std::string strDevice)
{
    // [2014-04-25] add strDevice, separate iOS or Android
    WorldPacket packet(CMD_CS_OTHER_AUTH);
    
    packet << strUid << dwVersion << strUsername << strPassword << wAreaId << strDevice;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

void CGameSession::SendReqPVPBattleInfo()
{
    WorldPacket packet(CMD_CS_TEST_AUTO_FIGHT);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

// #define CMD_CS_REQ_ACTIVE_LIST			CMD_MAKE_CLIENT(0x0022) // 请求普通活动}
void CGameSession::SendNormalMap()
{
    WorldPacket packet(CMD_CS_REQ_ACTIVE_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define  CMD_CS_REQ_STAGE_INFO			CMD_MAKE_CLIENT(0x0005)  // 客户端请求Stage List {uint16 wMapId ]}
void CGameSession::SendReqStageInfo(uint8 byType, uint16 wMapId)
{
    // 提前取得是否是新地图点信息
    MapCtrl::setMapPointClicked(MapCtrl::kMapStarNormal, MapCtrl::nSelectedMapId);
    
    WorldPacket packet(CMD_CS_REQ_STAGE_INFO);
    packet << byType;
    packet << wMapId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define  CMD_CS_BATTLE_STAGE_INFO		CMD_MAKE_CLIENT(0x0006)  // 客户端请求战斗 { uint16 wMapId + uint16 wStageId }
void CGameSession::SendStartBattle(uint8 byType, uint16 wMapId, uint16 wStageId, uint8 byIsPay)
{
    WorldPacket packet(CMD_CS_BATTLE_STAGE_INFO);
    packet << byType << wMapId << wStageId << byIsPay;
    
    snprintf(strBuf64, BUFFER_SIZE_64, "type:%d_%d_%d", byType, wMapId, wStageId);
    AnalysicsManager::sharedAnalyticsMgr()->beginMission(strBuf64);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//CMD_CS_CLIENT_BATTLE_INFO		CMD_MAKE_CLIENT(0x0011)  // 客户端战斗报 { 战斗类型 {uint8 byType + uint16 para1 + uint16 para2 +  uint16 para3} 战斗结果 {uint8 byResult} 战斗包信息}
void CGameSession::SendBattleResult(uint8 byType, uint16 para1, uint16 para2,  uint16 para3, uint8 byResult)
{
    WorldPacket packet(CMD_CS_CLIENT_BATTLE_INFO);
    packet << byType << para1 << para2 << para3 << byResult;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}
//    #define  CMD_CS_OPERATE_BATTLE_BAG		CMD_MAKE_CLIENT(0x000A)  // 客户端发送操控宠物背包之后背包信息 { uint8 byIndex + uint8 byLeaderSite + uint8 bySize +{ uint32 dwPetId { 1-6 号位的宠物} }}
void CGameSession::SendTeamUpdate(std::map<uint8, CTeam*> mapTeam)
{
    WorldPacket packet(CMD_CS_OPERATE_BATTLE_BAG);
    std::map<uint8, CTeam*>::iterator ii = mapTeam.begin();
    uint8 size = mapTeam.size();
    packet << size;
    for (; ii != mapTeam.end(); ii++) {
        if (!ii->second) {
            continue;
        }
        CTeam *team = ii->second;
        packet << team->getbyTeamId() << team->getbyLeaderSite();
        uint8 cnt = team->getarrPetObId().size() - 1;
        packet << cnt;
        for (int i = 1; i < team->getarrPetObId().size(); i++)
        {
            packet << team->getarrPetObId()[i];
        }
    }
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//     #define CMD_CS_ELECT_BATTLE_TEAM		CMD_MAKE_CLIENT(0x000D)   // 选择替换出战队伍 {  uint8 byTeamInId  + uint8 buTeamOutId}
void CGameSession::SendChdBattleTeam(uint8 byInTeamId, uint8 OutTeamId)
{
    WorldPacket packet(CMD_CS_ELECT_BATTLE_TEAM);
    packet << byInTeamId << OutTeamId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//    #define CMD_CS_PET_SELL					CMD_MAKE_CLIENT(0x0029)   // 卖宠物 {uint32 dwPetObjId}
void CGameSession::SendPetSell(uint8 bySize, std::vector<uint32> arrPetObjId)
{
    WorldPacket packet(CMD_CS_PET_SELL);
    packet << bySize;
    for (int i = 0; i < bySize; i ++) {
        packet << arrPetObjId[i];
    }
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_PET_EAT					CMD_MAKE_CLIENT(0x001F) // 宠物吃　强化　｛主吃　uint32 dwPetObjId +　 uint8 bySize + {　被吃 uint32 dwPetObjId}｝}
void CGameSession::SendPetEat(uint32 dwPetObjId, uint8 bySize, std::vector<uint32> arrBeEatObjId)
{
    WorldPacket packet(CMD_CS_PET_EAT);
    packet << dwPetObjId;
    packet << bySize;
    for (int i = 0; i < bySize; i ++) {
        packet << arrBeEatObjId[i];
    }
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_PET_EVOLVE				CMD_MAKE_CLIENT(0x0020) // 宠物进化　｛uint32 dwPetObjId ｝}
void CGameSession::SendPetEvolve(uint32 dwPetObjId)
{
    WorldPacket packet(CMD_CS_PET_EVOLVE);
    packet << dwPetObjId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_CLIENT_BATTLE_INFO		CMD_MAKE_CLIENT(0x0011)  // 客户端战斗报 { 战斗类型 {uint8 byType + uint16 para1 + uint16 para2 +  uint16 para3} 战斗结果 {uint8 byResult} 战斗包信息}
void CGameSession::SendPveFightResult(uint8 byType, uint16 para1,  uint16 para2,   uint16 para3, uint8 byRet, uint32 dwDamage, uint32 dwMoney)
{
    WorldPacket packet(CMD_CS_CLIENT_BATTLE_INFO);
    packet << byType << para1 << para2 << para3 << byRet << dwDamage << dwMoney;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_ARENA_LIST			CMD_MAKE_CLIENT(0x0013)  // 请求竞技场页面 {}
void CGameSession::SendEnterArenaSceneRequest()
{
    WorldPacket packet(CMD_CS_REQ_ARENA_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ARENA_FIHGT_LIST			CMD_MAKE_CLIENT(0x0027)   // 请求竞技场 挑战序列}
void CGameSession::SendArenaBattleListRequest()
{
    WorldPacket packet(CMD_CS_ARENA_FIHGT_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ARENA_RANK_LIST			CMD_MAKE_CLIENT(0x0028)   // 请求竞技场 排行榜}
void CGameSession::SendArenaRankListRequest()
{
    WorldPacket packet(CMD_CS_ARENA_RANK_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ARENA_LEARN				CMD_MAKE_CLIENT(0x0026)  // 竞技场切磋 {uint32 dwUserId + uint32 dwRank}
void CGameSession::SendArenaLearn(uint32 dwUserId, uint32 dwRank)
{
    WorldPacket packet(CMD_CS_ARENA_LEARN);
    packet << dwUserId << dwRank;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_FIGHT_IN_ARENA			CMD_MAKE_CLIENT(0x0012)  // 竞技场战斗 {uint32 dwUserId + uint32 dwRank}
void CGameSession::SendArenaBattle(uint32 dwUserId, uint32 dwRank)
{
    WorldPacket packet(CMD_CS_FIGHT_IN_ARENA);
    packet << dwUserId << dwRank;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ARENA_REWARD				CMD_MAKE_CLIENT(0x0025)  // 竞技场领奖}
void CGameSession::SendArenaReward()
{
    WorldPacket packet(CMD_CS_ARENA_REWARD);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_ARENA_SHOP_LIST				CMD_MAKE_CLIENT(0x0072) // 请求竞技商店列表}
void CGameSession::SendRequestArenaShopList()
{
    WorldPacket packet(CMD_CS_REQ_ARENA_SHOP_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ARENA_SHOP_EXCHANGE				CMD_MAKE_CLIENT(0x0073) // 竞技商店 兑换 {uint32 dwIndex }
void CGameSession::SendArenaShopExchange(uint32 dwIndex)
{
    WorldPacket packet(CMD_CS_ARENA_SHOP_EXCHANGE);
    packet << dwIndex;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_FARM_INFO			CMD_MAKE_CLIENT(0x002A)   // 请求庄园 生产型基本信息/}
void CGameSession::SendCountryRequest()
{
    WorldPacket packet(CMD_CS_REQ_FARM_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_CLICK_FARM_REWARD		CMD_MAKE_CLIENT(0x002C)	// 点击领取奖励 { uint8 byType }
void CGameSession::SendFarmRewardClick(uint8 byType)
{
    WorldPacket packet(CMD_CS_CLICK_FARM_REWARD);
    packet << byType;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

////#define CMD_CS_REQ_UPGRADE_BUILDER		CMD_MAKE_CLIENT(0x002B) // 请求建筑升级信息}
//void CGameSession::SendBuildUpgrade()
//{
//    WorldPacket packet(CMD_CS_REQ_UPGRADE_BUILDER);
//    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
//    pNetClient->SendData(packet);
//}

//#define CMD_CS_REQ_RES_OTHER_INFO		CMD_MAKE_CLIENT(0x002F)  // 请求具体庄园 掠夺型建筑信息 {uint8 byType}
void CGameSession::SendCaptureReq(uint8 byType)
{
    WorldPacket packet(CMD_CS_REQ_RES_OTHER_INFO);
    packet << byType;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_CAPTURE_LIST			CMD_MAKE_CLIENT(0x0032) // 请求挑战列表}
void CGameSession::SendCaptureList()
{
    WorldPacket packet(CMD_CS_REQ_CAPTURE_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ROB_CLICK_FARM_REWARD    CMD_MAKE_CLIENT(0x0030) // 领奖　｛ uint8 byType + uint8 byFarmId｝}
void CGameSession::SendRobRewardClick(uint8 byType, uint8 byFarmId)
{
    WorldPacket packet(CMD_CS_ROB_CLICK_FARM_REWARD);
    
    packet << byType << byFarmId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

void CGameSession::SendRescueFriendReq()
{
    WorldPacket packet(CMD_CS_REQ_FRIEND_HELP_LIST);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

////#define CMD_CS_REQ_MAIL_LIST			CMD_MAKE_CLIENT(0x0037) // 请求邮件列表}
//void CGameSession::SendMailListRequest(uint8 byMailType)
//{
//    WorldPacket packet(CMD_CS_REQ_MAIL_LIST);
//    packet << byMailType;
//    
//    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
//    pNetClient->SendData(packet);
//}

//#define CMD_CS_REQ_MAIL_INFO			CMD_MAKE_CLIENT(0x0038) // 请求邮件详细信息　{uint32 dwMailId}
void CGameSession::SendReadMailInfo(uint32 dwMailId)
{
    WorldPacket packet(CMD_CS_REQ_MAIL_INFO);
    packet << dwMailId;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_MAIL_REWARD				CMD_MAKE_CLIENT(0x0039) // 领取邮件奖励　{uint32 dwMailid }
void CGameSession::SendMailReward(uint8 byType, uint32 dwMailId)
{
    WorldPacket packet(CMD_CS_MAIL_REWARD);
    packet << byType;
    packet << dwMailId;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_DEL_MAIL					CMD_MAKE_CLIENT(0x003A) // 删除普通邮件 { uint32 dwMailId }
void CGameSession::SendDelMail(uint32 dwMailId)
{
    WorldPacket packet(CMD_CS_DEL_MAIL);
    packet << dwMailId;
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}
//#define CMD_CS_BATTLE_CAPTURE_SLAVE		CMD_MAKE_CLIENT(0x0033) // 抓奴隶　战斗　{ uint32 dwObjId + uint8 byType + uint8 byFarmId }
void CGameSession::SendCaptureSlave(uint32 dwObjId, uint8 byType, uint8 byFarmId)
{
    WorldPacket packet(CMD_CS_BATTLE_CAPTURE_SLAVE);
    packet << dwObjId << byType << byFarmId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_BATTLE_SLAVE_HELP		CMD_MAKE_CLIENT(0x0035) // 解救帮助　战斗　{ uint32 dwSlaveId }
void CGameSession::SendSlaveHelp(uint32 dwSlaveId)
{
    WorldPacket packet(CMD_CS_BATTLE_SLAVE_HELP);
    packet << dwSlaveId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_BATTLE_SLAVE_REVOLT		CMD_MAKE_CLIENT(0x0034) // 奴隶反抗　战斗　{ uint32 dwMasterId + uint8 byType + uint8 byFarmId }
void CGameSession::SendSlaveRevolt(uint32 dwMasterId, uint8 byType, uint8 byFarmId)
{
    WorldPacket packet(CMD_CS_BATTLE_SLAVE_REVOLT);
    packet << dwMasterId << byType << byFarmId;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_GM_CMD					CMD_MAKE_CLIENT(0x0021) // Gm 命令 {std::string }
void CGameSession::SendGM(std::string gmStr)
{
    WorldPacket packet(CMD_CS_GM_CMD);
    packet << gmStr;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_LOTTERY				CMD_MAKE_CLIENT(0x004A) //  请求抽奖　｛uint8 byType + byIsTen｝}
void CGameSession::SendReqLottery(uint8 byType, uint8 byIsTen)
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    if (byIsTen) {
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("gacha_ten");
    } else {
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("gacha_one");
    }
#endif
    
    WorldPacket packet(CMD_CS_REQ_LOTTERY);
    packet << byType << byIsTen;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_LOTTERY_BLOAD		CMD_MAKE_CLIENT(0x004B) // 请求抽奖 面板信息}
void CGameSession::SendLotteryInfo()
{
    WorldPacket packet(CMD_CS_REQ_LOTTERY_BLOAD);
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_LOTTERY_DOLLAR		CMD_MAKE_CLIENT(0x004C) // 请求抽取 钻石 ｛uint8 byType + byIsTen｝}
void CGameSession::SendReqLotteryDollar(uint8 byType, uint8 byIsTen)
{
    WorldPacket packet(CMD_CS_REQ_LOTTERY_DOLLAR);
    
    packet << byType << byIsTen;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_PASSIVE_SPELL_UPGRADE	CMD_MAKE_CLIENT(0x0015) // 被动技能升级 { uint32 dwPetObjId + uint8 byOffset + uint16 wSpellId  + bySize +{uint32 dwItemId + uint32 dwCnt}}
void CGameSession::SendPassiveSpellUpgrade(uint32 dwPetObjId, uint8 byOffset, uint32 wSpellId, vector<uint32> vecSkillBookIDs)
{
    WorldPacket packet(CMD_CS_PASSIVE_SPELL_UPGRADE);
    packet << dwPetObjId;   //当前宠物ObjID}
    packet << byOffset;     //当前技能的位置编号}
    packet << wSpellId;     //当前技能ID}
    
    uint32 dwItemID[5] = {};
    uint32 wCount[5] = {};
    uint16 wAllcount = 0;
    uint8 bySize = 0;
    
    //将重复的BookID叠加起来}
    for (int i = 0; i < vecSkillBookIDs.size(); i++)
    {
        for (int j = wAllcount; j < vecSkillBookIDs.size(); j++)
        {
            if(dwItemID[i] == 0)
            {
                dwItemID[i] = vecSkillBookIDs[j];
                wCount[i] = 1;
                wAllcount++;
            }
            else if (dwItemID[i] != 0 && dwItemID[i] == vecSkillBookIDs[j])
            {
                wCount[i]++;
                wAllcount++;
            }
            
            if (wAllcount >= vecSkillBookIDs.size())
            {
                break;
            }            
        }
        bySize++;
        if (wAllcount >= vecSkillBookIDs.size())
        {
            break;
        }
    }
    
    packet << bySize;
    for (int i = 0; i < bySize; i++)
    {
        packet << dwItemID[i];      //道具ID}
        packet << wCount[i];    //道具数量}
    }
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_PASSIVE_SPELL_ADD		CMD_MAKE_CLIENT(0x0016) // 被动技能添加 {  uint32 dwPetObjId + uint8 byOffset + uint32 dwItemId  技能书Id}
void CGameSession::SendPassiveSpellAdd(uint32 dwPetObjId, uint8 byOffset, uint32 dwItemId)
{
    WorldPacket packet(CMD_CS_PASSIVE_SPELL_ADD);
    packet << dwPetObjId;   //当前宠物ObjID}
    packet << byOffset;     //当前技能的位置编号}
    packet << dwItemId;     //道具ID}
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_PASSIVE_SPELL_EFFECT		CMD_MAKE_CLIENT(0x0017) // 被动技能生效 { uint32 dwPetObjId + uint8 byOffset + uint32 dwSpellId + 技能书Id}
void CGameSession::SendPassiveSpellEffect(uint32 dwPetObjId, uint8 byOffset, uint32 dwSpellId, uint32 dwItemId)
{
    WorldPacket packet(CMD_CS_PASSIVE_SPELL_EFFECT);
    packet << dwPetObjId;   //当前宠物ObjID}
    packet << byOffset;     //当前技能的位置编号}
    packet << dwSpellId;    //技能ID}
    packet << dwItemId;     //道具ID}
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);

}
//#define CMD_CS_SELL_ITEM				CMD_MAKE_CLIENT(0x0018) // 卖出物品　｛uint32 dwItemObjId + uint16 wNum｝}
void CGameSession::SendSellItem(uint32 dwItemObjId, uint16 wNum)
{
    WorldPacket packet(CMD_CS_SELL_ITEM);
    packet << dwItemObjId;  //道具ID}
    packet << wNum;         //道具数量}
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ITEM_USE					CMD_MAKE_CLIENT(0x0019) // 使用物品　{uint32 dwItemObjId + uint16 wNum}
void CGameSession::SendItemUse(uint32 dwItemObjId, uint16 wNum)
{
    WorldPacket packet(CMD_CS_ITEM_USE);
    packet << dwItemObjId;  //道具ID}
    packet << wNum;         //道具数量}
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_PET_LOCKED				CMD_MAKE_CLIENT(0x0024) // 宠物锁定 {uint8 bySize +{ uint32 dwPetObjId + uint8 bIsLock(1 解锁 0 加锁)} }
void CGameSession::SendPetLocked(std::map<uint32, bool> mapPetLocked)
{
    WorldPacket packet(CMD_CS_PET_LOCKED);
    uint8 bySize = mapPetLocked.size();
    packet << bySize;
    
    std::map<uint32, bool>::iterator it = mapPetLocked.begin();
    for (; it != mapPetLocked.end(); it++) {
        if (!it->first) {
            continue;
        }
        packet << it->first;
        uint8 lock = it->second;
        packet << lock;
    }
    
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_ITEM_BAG_ENLARGE			CMD_MAKE_CLIENT(0x005D) // 背包扩充 {}
void CGameSession::SendItemBagEnlager(uint8 byType)
{
    WorldPacket packet(CMD_CS_ITEM_BAG_ENLARGE);
    packet << byType;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_BAG_ENLARGE_DOLLAR   CMD_MAKE_CLIENT(0x005E) // 请求背包扩充 需要钻石D}
void CGameSession::SendReqBagEnlagerDollar(int tag)
{
    WorldPacket packet(CMD_CS_REQ_BAG_ENLARGE_DOLLAR);
    uint8 byTag = tag;
    packet << byTag;
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_NO_FRIEND_LIST		CMD_MAKE_CLIENT(0x0046) // 请求人物信息 {uint32 dwUserId}
void CGameSession::SendReqFindFriend(uint32 dwUserId)
{
    WorldPacket packet(CMD_CS_REQ_NO_FRIEND_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwUserId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_APPLE_FRIEND			CMD_MAKE_CLIENT(0x0042) // 申请加别人好友　｛uint32 dwUserId｝}
void CGameSession::SendReqApplyFriend(uint32 dwUserId)
{
    WorldPacket packet(CMD_CS_REQ_APPLE_FRIEND);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwUserId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_AGREE_APPLY				CMD_MAKE_CLIENT(0x0044) // 同意加好友 ｛uint32 dwUserId｝}
void CGameSession::SendAgreeFriendApply(uint32 dwUserId)
{
    WorldPacket packet(CMD_CS_AGREE_APPLY);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwUserId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_DISAFREE_APPLY			CMD_MAKE_CLIENT(0x0045) // 拒绝加好友 ｛uint32 dwUserId｝}
void CGameSession::SendDisagreeFriendApply(uint32 dwUserId)
{
    WorldPacket packet(CMD_CS_DISAFREE_APPLY);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwUserId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_DELTE_FRIEND				CMD_MAKE_CLIENT(0x0043) // 删除好友 ｛uint32 dwUserId｝}
void CGameSession::SendDelFriend(uint32 dwUserId)
{
    WorldPacket packet(CMD_CS_DELTE_FRIEND);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwUserId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_ADD_GEM_PET				CMD_MAKE_CLIENT(0x005A) // 宠物添加宝石 {uint32 dwPetObjId + uint32 dwGemKeyId }
void CGameSession::SendAddGemToPet(uint32 dwPetObjId, uint32 dwGemKeyId)
{
    WorldPacket packet(CMD_CS_ADD_GEM_PET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwPetObjId;
    packet << dwGemKeyId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_SELL_GEM					CMD_MAKE_CLIENT(0x005B) // 卖宝石 { uint32 dwGemKeyId }
void CGameSession::SendSellGem(uint32 dwGemKeyId)
{
    WorldPacket packet(CMD_CS_SELL_GEM);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwGemKeyId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_VAIL_GEM					CMD_MAKE_CLIENT(0x005C) // 卸下宝石 {uint32 dwPetObjId + uint32 dwGemKeyId}
void CGameSession::SendVailGem(uint32 dwPetObjId, uint32 dwGemKeyId)
{
    WorldPacket packet(CMD_CS_VAIL_GEM);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwPetObjId;
    packet << dwGemKeyId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_ACTIVE_MAP_LIST		CMD_MAKE_CLIENT(0x0007)  // 客户端请求活动Map序列}
void CGameSession::SendSpecialMapList()
{
    WorldPacket packet(CMD_CS_REQ_ACTIVE_MAP_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_ACTIVE_STAGE_INFO	CMD_MAKE_CLIENT(0x0008)  // 客户端请求活动Stage List {uint16 wMapId ]}
void CGameSession::SendSpecialStageInfo(uint16 wMapId)
{
    WorldPacket packet(CMD_CS_REQ_ACTIVE_STAGE_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << wMapId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_UPGRADE_BUILDER		CMD_MAKE_CLIENT(0x002B) // 请求建筑升级信息}
void CGameSession::SendReqUpgradeBuildInfo()
{
    WorldPacket packet(CMD_CS_REQ_UPGRADE_BUILDER);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_UPGRADE_FARM_BUILD		CMD_MAKE_CLIENT(0x002D)// 升级庄园建筑　{uint8 byType}
void CGameSession::SendUpgradeBuild(uint8 byType)
{
    WorldPacket packet(CMD_CS_UPGRADE_FARM_BUILD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType;
    pNetClient->SendData(packet);
}

//#define CMD_CS_SEND_MSG					CMD_MAKE_CLIENT(0x003B) // 发送留言 {uint32 dwUserId + std::string strTitle + std::string strContent}
void CGameSession::SendFriendMsg(uint32 dwUserId, std::string strTitle, std::string strContent)
{
    WorldPacket packet(CMD_CS_SEND_MSG);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwUserId << strTitle << strContent;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_SHOP_INFO			CMD_MAKE_CLIENT(0x0060) // 进入商城请求信息 {}
void CGameSession::SendOpenShopRequest()
{
    WorldPacket packet(CMD_CS_REQ_SHOP_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_SHOP_BUY_INFO			CMD_MAKE_CLIENT(0x0061) // 普通购买 {uint32 dwGoodsId + uint32 dwNum}
void CGameSession::SendShopBuyItem(uint32 dwGoodsId, uint32 dwNum)
{
    WorldPacket packet(CMD_CS_SHOP_BUY_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwGoodsId << dwNum;
    
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    snprintf(strBuf64, BUFFER_SIZE_64, "%d", dwGoodsId);
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("item_id", strBuf64);
    AnalysicsManager::sharedAnalyticsMgr()->onPurchase(strBuf64, dwNum, 0);
#endif
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_SHOP_OTHER_PAY			CMD_MAKE_CLIENT(0x0062) // 充值购买 {uint32 dwGoodsId  + .... }
void CGameSession::SendShopBuyOtherPay()
{
    WorldPacket packet(CMD_CS_SHOP_OTHER_PAY);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_SELL_EQUIP				CMD_MAKE_CLIENT(0x001A) // 卖出装备　{ uint8 bySize + {uint32 dwEquipObjId } }
void CGameSession::SendSellEquip(vector<uint32> vecEquipObjId)
{
    WorldPacket packet(CMD_CS_SELL_EQUIP);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    uint8 bySize;
    bySize = vecEquipObjId.size();
    packet << bySize;
    for (int i = 0; i < bySize; i++)
    {
        packet <<  vecEquipObjId[i];
    }
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EQUIP_TO_TEAM						CMD_MAKE_CLIENT(0x0144)
/** 装备装备队伍}
 uint32	dwEquipObjId
 uint8	bySite
 uint8	byOffset
 */
void CGameSession::SendEquipToPet(uint32 dwEquipId, uint8 bySite, uint8 byOffset)
{
    WorldPacket packet(CMD_CS_EQUIP_TO_TEAM);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipId;
    packet << bySite;
    packet << byOffset;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_UPGRADE_EQUIP			CMD_MAKE_CLIENT(0x001C) // 装备升级　｛uint32 dwEquipObjId + uint8 byType (0 普通 1 一键升级)｝}
void CGameSession::SendUpgradeEquip(uint32 dwEquipObjId, uint8 byType)
{
    WorldPacket packet(CMD_CS_UPGRADE_EQUIP);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipObjId;
    packet << byType;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EQUIP_VAIL_TEAM						CMD_MAKE_CLIENT(0x0145)
/** 装备脱下}
 uint32 dwEquipId
 uint8  bySite
 uint8  byOffset
 */
void CGameSession::SendEquipVail(uint32 dwEquipId, uint8 bySite, uint8 byOffset)
{
    WorldPacket packet(CMD_CS_EQUIP_VAIL_TEAM);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipId;
    packet << bySite;
    packet << byOffset;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EQUIP_RUNES				CMD_MAKE_CLIENT(0x0063) // 装备符文 {uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId}
void CGameSession::SendRuneToEquip(uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId)
{
    WorldPacket packet(CMD_CS_EQUIP_RUNES);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipId;
    packet << byOffset;
    packet << dwRunesId;
    
    pNetClient->SendData(packet);
}
//#define CMD_CS_UNDRESS_RUNES			CMD_MAKE_CLIENT(0x0064) // 脱下符文 {uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId}
void CGameSession::SendRuneUnload(uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId)
{
    WorldPacket packet(CMD_CS_UNDRESS_RUNES);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipId;
    packet << byOffset;
    packet << dwRunesId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_MATERIAL_SYNC			CMD_MAKE_CLIENT(0x0066) // 物品合成 {uint32 dwIndex + uint8 byType + uint8 IsSenior}
void CGameSession::SendEquipCompound(uint32 dwIndex, uint8 byType, uint8 isSenior)
{
    WorldPacket packet(CMD_CS_MATERIAL_SYNC);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwIndex;
    packet << byType;
    packet << isSenior;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EQUIP_ENLARGE_RUNES		CMD_MAKE_CLIENT(0x0068) // 装备开符文槽 {uint32 dwEquipId }
void CGameSession::SendEquipEnlageRune(uint32 dwEquipId)
{
    WorldPacket packet(CMD_CS_EQUIP_ENLARGE_RUNES);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_ACTIVE_BATTLE_STAGE_INFO CMD_MAKE_CLIENT(0x0009)  // 客户端请求活动战斗 { uint16 wMapId + uint16 wStageId }
void CGameSession::SendSpecialBattle(uint16 wMapId, uint16 wStageId, uint8 byIsPay)
{
    WorldPacket packet(CMD_CS_ACTIVE_BATTLE_STAGE_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << wMapId << wStageId << byIsPay;
    
    snprintf(strBuf64, BUFFER_SIZE_64, "active:%d_%d", wMapId, wStageId);
    AnalysicsManager::sharedAnalyticsMgr()->beginMission(strBuf64);
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EARN_ENERGY_REW			CMD_MAKE_CLIENT(0x0069) // 领取每日能量奖励}
void CGameSession::SendEarnEnergyReward()
{
    WorldPacket packet(CMD_CS_EARN_ENERGY_REW);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EARN_SEVEN_ONLINE_REW	CMD_MAKE_CLIENT(0x006A) // 领取每日登陆奖励 7日}
void CGameSession::SendEarnSevenReward()
{
    WorldPacket packet(CMD_CS_EARN_SEVEN_ONLINE_REW);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EARN_THIRTY_ONLINE_REW	CMD_MAKE_CLIENT(0x006B) // 领取新手30日登陆奖励}
void CGameSession::SendEarnThirtyReward()
{
    WorldPacket packet(CMD_CS_EARN_THIRTY_ONLINE_REW);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_ADD_SPELL_EXP					CMD_MAKE_CLIENT(0x006E) // 添加祭炼值 	{ bySize +{uint32 dwItemId + uint32 dwCnt}}
void CGameSession::SendSkillExpAdd(std::vector<uint32> arrItemId)
{
    WorldPacket packet(CMD_CS_ADD_SPELL_EXP);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    uint8 bySize = arrItemId.size();
    packet << bySize;
    for (int i = 0; i < bySize; i++) {
        uint32 dwItemId = arrItemId[i];
        uint32 dwCnt = 1;
        packet << dwItemId;
        packet << dwCnt;
    }
    
    pNetClient->SendData(packet);
}
//#define CMD_CS_SPELL_UPGRADE					CMD_MAKE_CLIENT(0x006F) // 技能升级		{ uint32 dwPetObjId + uint8 byOffset + uint32 dSpellId + uint32 dwExp }
void CGameSession::SendSkillUpgread(uint32 dwPetObjId, uint8 byOffset, uint32 dSpellId, uint32 dwExp)
{
    WorldPacket packet(CMD_CS_SPELL_UPGRADE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << dwPetObjId;
    packet << byOffset;
    packet << dSpellId;
    packet << dwExp;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_UPDATE_ENERGY_REC_TIME			CMD_MAKE_CLIENT(0x0071) // 请求更新能量回复时间}
void CGameSession::SendUpdateEnergyRecTime()
{
    WorldPacket packet(CMD_CS_UPDATE_ENERGY_REC_TIME);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_NEW_ROLE_NUM						CMD_MAKE_CLIENT(0x0078) // 新手流程数字 {uint16 wProgress}
void CGameSession::SendTriggerNum(uint16 wProgress)
{
    WorldPacket packet(CMD_CS_NEW_ROLE_NUM);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    CCLog("send >>>> trigger:%d to server", wProgress);
    packet << wProgress;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_CHOOSE_NAME						CMD_MAKE_CLIENT(0x0079) // 选择名字 {std::string Name}
void CGameSession::SendChooseName(std::string strName) {
    WorldPacket packet(CMD_CS_CHOOSE_NAME);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << strName;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_CHOOSE_PET						CMD_MAKE_CLIENT(0x007A) // 选择宠物 {uint16 wPetId}
void CGameSession::SendChoosePet(uint16 wPetId) {
    WorldPacket packet(CMD_CS_CHOOSE_PET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << wPetId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_DAILY_QUEST_REWARD				CMD_MAKE_CLIENT(0x006C) // 0日常任务奖励 {uint32 dwIndex}
void CGameSession::SendDailyQuestRewardRequest(uint8 byType, uint32 dwIndex)
{
    WorldPacket packet(CMD_CS_DAILY_QUEST_REWARD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType << dwIndex;
    pNetClient->SendData(packet);
}

//#define CMD_CS_ACHIEVE_REWARD					CMD_MAKE_CLIENT(0x006D) // 成就奖励 {uint32 dwType + uint32 dwIndex}
void CGameSession::SendAchieveRewardRequest(uint32 dwType, uint32 dwIndex)
{
    WorldPacket packet(CMD_CS_ACHIEVE_REWARD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwType;
    packet << dwIndex;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_FRIEND_SHARE						CMD_MAKE_CLIENT(0x007C) // 好友分享}
void CGameSession::SendFriendShareRequest()
{
    WorldPacket packet(CMD_CS_FRIEND_SHARE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_INVITE_CODE						CMD_MAKE_CLIENT(0x007B) // 邀请码 { std::string strInvideCode }
void CGameSession::SendInviteCode(std::string strInvideCode)
{
    WorldPacket packet(CMD_CS_INVITE_CODE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << strInvideCode;
    
    pNetClient->SendData(packet);
}
//#define CMD_CS_REQ_REFERRER						CMD_MAKE_CLIENT(0x007E) // 请求邀请人界面}
void CGameSession::SendEnterInviteSceneRequest()
{
    WorldPacket packet(CMD_CS_REQ_REFERRER);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_FRIEND_REFERRER					CMD_MAKE_CLIENT(0x007D) // 好友邀请  { uint32 dwReferrerId }
void CGameSession::SendInviteID(uint32 dwReferrerId)
{
    WorldPacket packet(CMD_CS_FRIEND_REFERRER);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwReferrerId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_PET_FUSE							CMD_MAKE_CLIENT(0x0074)
/**
 * 	宠物融合 兑换 融合石}
 * 	[uint8] count
 * 		[uint32] dwPetKeyId
 * */
void CGameSession::SendPetFuse(uint8 byType, std::vector<uint32> arrPetId)
{
    WorldPacket packet(CMD_CS_PET_FUSE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType;
    
    uint8 count = arrPetId.size();
    packet << count;
    
    for (int i = 0; i < count; i ++) {
        if (!arrPetId[i]) {
            continue;
        }
        packet << arrPetId[i];
    }
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_MYSTERY_SHOP_LIST			CMD_MAKE_CLIENT(0x0075) // 请求神秘商城列表}
void CGameSession::SendReqMySteryShopList()
{
    WorldPacket packet(CMD_CS_REQ_MYSTERY_SHOP_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();

    pNetClient->SendData(packet);
}

//#define CMD_CS_MYSTERY_SHOP_BUY					CMD_MAKE_CLIENT(0x0076) // 神秘商城购买 { uint32 dwGoodId }
void CGameSession::SendMySteryShopBy(uint32 dwGoodsId)
{
    WorldPacket packet(CMD_CS_MYSTERY_SHOP_BUY);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwGoodsId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_MYSTERY_SHOP_UPDATE				CMD_MAKE_CLIENT(0x0077) // 神秘商城刷新}
void CGameSession::SendMySteryShopUpdate()
{
    WorldPacket packet(CMD_CS_MYSTERY_SHOP_UPDATE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_BIND_ACCOUNT					CMD_MAKE_CLIENT(0x0080) // 请求账号绑定信息}
void CGameSession::SendBindingRequest()
{
    WorldPacket packet(CMD_CS_REQ_BIND_ACCOUNT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_BIND_AUTO_ACCOUNT				CMD_MAKE_CLIENT(0x0081) // 账号绑定 {std::string strMail + std::string strAccount + std::string strPwd }
void CGameSession::SendBindingAccount(string strMail, string strAccount, string strPwd)
{
    WorldPacket packet(CMD_CS_BIND_AUTO_ACCOUNT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << strMail;
    packet << strAccount;
    packet << strPwd;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_GROW_UP_REWARD					CMD_MAKE_CLIENT(0x0109)
/**	成长奖励领取}
 [uint32] dwIndex
 */
void CGameSession::SendGrowUpReward(uint32 dwIndex)
{
    WorldPacket packet(CMD_CS_GROW_UP_REWARD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwIndex;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_BUY_GROW_UP						CMD_MAKE_CLIENT(0x010A)
/** 购买成长计划}
 */
void CGameSession::SendBuyGrowUp()
{
    WorldPacket packet(CMD_CS_BUY_GROW_UP);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_FIRST_PAY_REWARD					CMD_MAKE_CLIENT(0x010B)
/** 首冲奖励领取}
 */
void CGameSession::SendFirstPayReward()
{
    WorldPacket packet(CMD_CS_FIRST_PAY_REWARD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

void CGameSession::SendReqShopCnt()
{
    WorldPacket packet(CMD_CS_REQ_SHOP_CNT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

void CGameSession::SendChatMsg(uint8 byChannel, uint32 dwTargetId, const string strTargetName, const string strContent)
{
    WorldPacket packet(CMD_CS_CHAT_SEND);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << byChannel << dwTargetId << strTargetName << strContent;
    pNetClient->SendData(packet);
}

void CGameSession::SendChatSwitch(bool bIsBanned)
{
    WorldPacket packet(CMD_CS_CHAT_SWITCH);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << bIsBanned;
    pNetClient->SendData(packet);
}

void CGameSession::SendGetChat()
{
    WorldPacket packet(CMD_CS_CHAT_GET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_OTHER_ROLE_INFO				CMD_MAKE_CLIENT(0x0107)
/** 请求其他人物信息}
 [uint32] dwAccountId
 */
void CGameSession::SendReqOtherRoleInfo(uint32 dwAccountId)
{
    WorldPacket packet(CMD_CS_REQ_OTHER_ROLE_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwAccountId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_EQUIP_EVOLVE						CMD_MAKE_CLIENT(0x010D)
/** 装备进阶}
 [uint32 dwEquipKeyId]
 */
void CGameSession::SendReqEquipEvolve(uint32 dwEquipKeyId)
{
    WorldPacket packet(CMD_CS_EQUIP_EVOLVE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEquipKeyId;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_EMBLEM_EAT						CMD_MAKE_CLIENT(0x010E)
//    /** 徽章升级 吃}
//     [uint32]	dwEmblemId		// 升级的徽章 keyId}
//     [uint8]		byCount
//     [uint32] dwEmblemId // 被吃的keyId}
//     */
void CGameSession::SendEmblemEat(uint32 dwEmblemId, std::vector<uint32> arrElem){
    WorldPacket packet(CMD_CS_EMBLEM_EAT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEmblemId;
    uint8 byCount = arrElem.size();
    packet << byCount;
    
    for (int i = 0; i < arrElem.size(); i++) {
        packet << arrElem[i];
    }
    pNetClient->SendData(packet);
}

//#define CMD_CS_EMBLEM_TO_PET						CMD_MAKE_CLIENT(0x010F)
//    /** 徽章装备}
//     [uint32]	dwPetKeyId
//     [uint32]	dwEmblemKeyId
//     */
//
void CGameSession::SendEmblemWear(uint32 dwPetObjId, uint32 dwEmblemObjId){
    WorldPacket packet(CMD_CS_EMBLEM_TO_PET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwPetObjId;
    packet << dwEmblemObjId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_EMBLEM_VAIL_PET						CMD_MAKE_CLIENT(0x0110)
//    /** 徽章卸下}
//     [uint32]	dwEmblemKeyId
//     */
void CGameSession::SendEmblemTakeOff(uint32 dwEmblemObjId){
    WorldPacket packet(CMD_CS_EMBLEM_VAIL_PET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwEmblemObjId;
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_TOWER_INFO						CMD_MAKE_CLIENT(0x011A)
/** 请求塔基本信息}
 */
void CGameSession::SendRequestTowerInfo()
{
    WorldPacket packet(CMD_CS_REQ_TOWER_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();

    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_TOWER_RANK						CMD_MAKE_CLIENT(0x011B)
/** 请求塔排行榜}
 */
void CGameSession::SendRequestTowerRank()
{
    WorldPacket packet(CMD_CS_REQ_TOWER_RANK);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_RESET_TOWER_FLOOR					CMD_MAKE_CLIENT(0x011C)
/** 重置塔当前层数}
 */
void CGameSession::SendResetTowerFloor()
{
    WorldPacket packet(CMD_CS_RESET_TOWER_FLOOR);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_FIGHT_TOWER							CMD_MAKE_CLIENT(0x011D)
/** 挑战塔}
 *		[uint8] byType ( 1, 普通挑战 2, 自动爬塔)
 */
void CGameSession::SendFightTower(uint8 byType)
{
    WorldPacket packet(CMD_CS_FIGHT_TOWER);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType;
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_STORE_PAY_LIST					CMD_MAKE_CLIENT(0x0126)}
/** 请求充值List
 **/
void CGameSession::SendRequestStorePayList()
{
    WorldPacket packet(CMD_CS_REQ_STORE_PAY_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_WRESTLE_INFO						CMD_MAKE_CLIENT(0x0120)}
//    /** 请求道馆信息}
//     **/
void CGameSession::SendReqChallengeInfo()
{
    WorldPacket packet(CMD_CS_REQ_WRESTLE_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}
//#define CMD_CS_REQ_WRESTLE_FIGHT_LIST				CMD_MAKE_CLIENT(0x0121)
//    /** 请求道馆挑战列表}
//     *		[uint32] dwMapId
//     **/
void CGameSession::SendReqChallengeLevleInfo(uint32 dwMapId)
{
    WorldPacket packet(CMD_CS_REQ_WRESTLE_FIGHT_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwMapId;
    pNetClient->SendData(packet);
}
//#define CMD_CS_RESET_WRESTLE_BLESS					CMD_MAKE_CLIENT(0x0122)
//    /** 道观祝福}
//     *		[uint32] dwMapId
//     **/
void CGameSession::SendResetChallengeBless()
{
    WorldPacket packet(CMD_CS_RESET_WRESTLE_BLESS);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_WRESTLE_REWARD						CMD_MAKE_CLIENT(0x0123)
//    /** 道观领奖}
//     *		[uint32] dwMapId
//     **/
void CGameSession::SendGetChallengeReward()
{
    WorldPacket packet(CMD_CS_WRESTLE_REWARD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();

    pNetClient->SendData(packet);
}
//#define CMD_CS_WRESTLE_FIGHT						CMD_MAKE_CLIENT(0x0124)
//    /** 道观挑战}
//     **/
void CGameSession::SendReqChallengeFight()
{
    WorldPacket packet(CMD_CS_WRESTLE_FIGHT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

//#define CMD_CS_NOTICE_GET						CMD_MAKE_CLIENT(0x0103)
/** 获取游戏公告}
 */
void CGameSession::SendNoticeGet()
{
    WorldPacket packet(CMD_CS_NOTICE_GET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

void CGameSession::SendStageSweep(uint16 wStageId, uint8 byMapType, uint8 byCnt)
{
    WorldPacket packet(CMD_CS_STAGE_SWEEP);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << wStageId << byMapType << byCnt;
    pNetClient->SendData(packet);
}

void CGameSession::SendMapSweep(uint16 wMapId, uint8 byMapType)
{
    WorldPacket packet(CMD_CS_MAP_SWEEP);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << wMapId << byMapType;
    pNetClient->SendData(packet);
}

void CGameSession::SendMapPassStarRew(uint16 wMapId, uint8 byMapType, uint8 byOffset)
{
    WorldPacket packet(CMD_CS_MAP_PASS_STAR_REW);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << wMapId << byMapType << byOffset;
    pNetClient->SendData(packet);
}

//#define CMD_CS_BUY_ARENA_POINT						CMD_MAKE_CLIENT(0x0143)
/** 购买竞技点
 **/
void CGameSession::SendBuyAreanPoint()
{
    WorldPacket packet(CMD_CS_BUY_ARENA_POINT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_arena");
    pNetClient->SendData(packet);
}

//#define  CMD_CS_OPERATE_BATTLE_CUR_TEAM	CMD_MAKE_CLIENT(0x000B)
/** 客户端发送操控宠物背包之后背包信息
 uint8 byIndex
 uint8 byLeaderSite
 uint8 bySize
 uint32 dwPetId { 1-6 号位的宠物}
 */
void CGameSession::SendCurTeam(CTeam* team)
{
    WorldPacket packet(CMD_CS_OPERATE_BATTLE_CUR_TEAM);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    uint8 byIndex = team->getbyTeamId();
    uint8 byLeaderSite = team->getbyLeaderSite();
    uint8 bySize = team->getarrPetObId().size();
    packet << byIndex;
    packet << byLeaderSite;
    packet << (uint8)(bySize-1);
    for (int i = 1; i < bySize; i++) {
        uint32 dwPetId = team->getarrPetObId()[i];
        packet << dwPetId;
    }
    
    pNetClient->SendData(packet);
}

void CGameSession::SendBuyStageFightCnt(uint8 byType, uint16 wStageId) {
    WorldPacket packet(CMD_CS_BUY_STAGE_FIGHT_CNT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    if (byType == E_BUY_STAGE_NORMAL) {
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_normal_stage");
    } else if (byType == E_BUY_STAGE_HERO) {
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_hero_stage");
    } else if (byType == E_BUY_STAGE_MONEY_CAT) {
        AnalysicsManager::sharedAnalyticsMgr()->SendEvent("buy_money_cat");
    }
    
    packet << byType << wStageId;
    pNetClient->SendData(packet);
}

void CGameSession::SendClearSweepCDTime(uint8 byType,uint32 dwDollar)
{
    WorldPacket packet(CMD_CS_CLEAR_SWEEP_CD_TIME);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType << dwDollar;
    pNetClient->SendData(packet);
}

//#define CMD_CS_ENTER_WORLD_BOSS_BLOAD				CMD_MAKE_CLIENT(0x0160)
/** 请求世界BOSS 基本信息
 */
void CGameSession::SendWorldBossInfo()
{
    WorldPacket packet(CMD_CS_ENTER_WORLD_BOSS_BLOAD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_REQ_WORLD_BOSS_LIST					CMD_MAKE_CLIENT(0x0161)
/** 请求世界BOSS 排行榜 上期
 */
void CGameSession::SendReqWorldBossList()
{
    WorldPacket packet(CMD_CS_REQ_WORLD_BOSS_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_WORLD_BOSS_BLESS						CMD_MAKE_CLIENT(0x0162)
/** 世界BOSS 鼓舞
 *		[uint8]  byType (1 coin; 2 dollar)
 */
void CGameSession::SendWorldBossBless(uint8 byType)
{
    WorldPacket packet(CMD_CS_WORLD_BOSS_BLESS);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType;
    pNetClient->SendData(packet);
}


//#define CMD_CS_WORLD_BOSS_FIGHT						CMD_MAKE_CLIENT(0x0163)
/** 世界BOSS 战斗 
 byType 0:正常；1:自动(不进战斗)
 */
void CGameSession::SendWorldBossFight(uint8 byType)
{
    WorldPacket packet(CMD_CS_WORLD_BOSS_FIGHT);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << byType;
    pNetClient->SendData(packet);
}


//#define CMD_CS_WORLD_BOSS_CLEAR_CD					CMD_MAKE_CLIENT(0x0164)
/** 世界BOSS 清除战斗CD
 */
void CGameSession::SendWorldBossClearCD()
{
    WorldPacket packet(CMD_CS_WORLD_BOSS_CLEAR_CD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_WORLD_BOSS_UPDATE_INFO				CMD_MAKE_CLIENT(0x0165)
/** 世界BOSS 刷新基本信息
 */
void CGameSession::SendWorldBossUpdateInfo()
{
    WorldPacket packet(CMD_CS_WORLD_BOSS_UPDATE_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_WORLD_BOSS_END_REWARD				CMD_MAKE_CLIENT(0x0166)
/** 世界BOSS 结束结算
 */
void CGameSession::SendWorldBossEndReward()
{
    WorldPacket packet(CMD_CS_WORLD_BOSS_END_REWARD);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_RECOMMEND_FRIEND_LIST			CMD_MAKE_CLIENT(0x007F)
/** 请求推荐好友列表
 */
void CGameSession::SendReqRecommendFriendList()
{
    WorldPacket packet(CMD_CS_RECOMMEND_FRIEND_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    pNetClient->SendData(packet);
}

//#define CMD_CS_FRIEND_ENERGY_GIVE					CMD_MAKE_CLIENT(0x0130)
/** 好友赠送体力
	[uint32] dwFriendId
 **/
void CGameSession::SendFriendEnergyGive(uint32 dwFriendId) {
    WorldPacket packet(CMD_CS_FRIEND_ENERGY_GIVE);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    packet << dwFriendId;
    pNetClient->SendData(packet);
}

void CGameSession::SendGetFriendEnergy(uint8 byIsAll, uint32 dwFriendId) {
    WorldPacket packet(CMD_CS_FRIEND_ENERGY_GET);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << byIsAll << dwFriendId;
    pNetClient->SendData(packet);
}

void CGameSession::SendFightWithFriend(uint32 dwFriendId) {
    WorldPacket packet(CMD_CS_FIGHT_WITH_FRIEND);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << dwFriendId;
    pNetClient->SendData(packet);
}

void CGameSession::SendRequestActiveList()
{
    WorldPacket packet(CMD_CS_CLICK_ACTIVE_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

void CGameSession::SendRequestActiveInfoById(uint32 dwActId)
{
    WorldPacket packet(CMD_CS_CLICK_ACTIVE_INFO);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << dwActId;
    pNetClient->SendData(packet);
}

void CGameSession::SendGetActiveRewardByActIdAndCellId(uint32 ActiveId,uint32 dwCellId)
{
    WorldPacket packet(CMD_CS_CLICK_ACTIVE_REW);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << ActiveId << dwCellId;
    pNetClient->SendData(packet);
}

void CGameSession::SendReqMJShopList()
{
    WorldPacket packet(CMD_CS_REQ_TIME_SHOP_LIST);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    pNetClient->SendData(packet);
}

void CGameSession::SendMJShopBuy(uint32 dwShopId)
{
    WorldPacket packet(CMD_CS_TIME_SHOP_BUY);
    CNetClient* pNetClient = AppDelegate::sharedAppDelegate()->netClient();
    
    packet << dwShopId;
    pNetClient->SendData(packet);
}

