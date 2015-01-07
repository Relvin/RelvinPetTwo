#ifndef _GAME_SESSION_H
#define _GAME_SESSION_H

#include "Defines.h"
#include "Observer.h"
#include <string>
#include "WorldPacket.h"
#include <vector>

using namespace std;

class CTeam;
class CRole;
class CGameSession
{
public:
	static bool Init();
	static void UnInit();
    
    static void SendLoginTest();
    static void SendTest();
    
    static void BackToLogin();
    
    
//    #define CMD_LOGIN_CS_REQ_LIST			CMD_MAKE_CLIENT(0x0055)		//客户端 获取服务器列表}
    static void SendRequestServerList(
                                      string strAccount,
                                      string strDevice,
                                      string strVersion,
                                      uint32 dwPaltFrom
                                      );
//    #define CMD_LOGIN_CS_LOGIN				CMD_MAKE_CLIENT(0x0051)		//注册帐号 登录{ std::string uid + uint32版本号 string name + string pwd  + uint16 wAreaId} }
    static void SendGameLogin(
                              std::string strUid,
                              uint32 dwVer,
                              std::string strName,
                              std::string strPwd,
                              uint16 wAreaId
                              );
//#define CMD_LOGIN_CS_GM_LOGIN			CMD_MAKE_CLIENT(0x0056)		// UserId登陆 {uint32 dwUserId + uint16 wAreaId}
    static void SendUserLoginServer(
                                    uint32 dwUserId,
                                    uint16 wAreaId
                                    );
//#define CMD_CS_GM_LOGIN				CMD_MAKE_CLIENT(0x0004) // ｛UserId登陆 {uint32 dwUserId + uint16 wAreaId}｝}
    static void SendUserGameServer(
                                   uint32 dwUserId,
                                   uint16 wAreaId
                                   );
    
//    #define CMD_LOGIN_CS_REG				CMD_MAKE_CLIENT(0x0052)		//注册帐号 注册 {std::string uid + uint32版本号 string name + string pwd + string mail + string reg_device + string reg_device_type}
    static void SendGameReg(
                            std::string strUid,
                            uint32 dwVer,
                            std::string strName,
                            std::string strPwd,
                            std::string strMail,
                            std::string strDevice,
                            std::string strDevOs,
                            uint32 dwPlatForm
                            );
//    #define CMD_LOGIN_CS_FAST_LOGIN			CMD_MAKE_CLIENT(0x0053)		//快速登录 { std::string uid + uint32版本号 + string name + string pwd + uint16 wAreaId + string reg_device + string reg_device_type}
    static void SendGameFastLogin(
                                  std::string strUid,
                                  uint32 dwVer,
                                  std::string strName,
                                  std::string strPwd,
                                  uint16 wAreaId,
                                  std::string strDevice,
                                  std::string strDevType,
                                  uint32 dwPlatForm
                                  );
//    #define CMD_LOGIN_CS_OTHER_LOGIN		CMD_MAKE_CLIENT(0x0054)		//第三方平台 登录 { std::string uid +  uint32版本号 + string name +  string pwd + uint16 wAreaId + string reg_device + string reg_device_type}
    static void SendGameOtherLogin(
                                   std::string strUid,
                                   uint32 dwVer,
                                   std::string strName,
                                   std::string strPwd,
                                   uint16 wAreaId,
                                   std::string strDevice,
                                   std::string strDevType,
                                   uint32 dwPlatForm
                                   );
//#define CMD_CS_CLIENT_AUTH			CMD_MAKE_CLIENT(0x0001) //注册账号 请求认证{string strUid + uint32 dwVersion + string strAcess + string 密码 + uint16 wAreaId }
    static void SendAccountAuth(
                                std::string strUid,
                                uint32 dwVersion,
                                std::string strUsername,
                                std::string strPassword,
                                uint16 wAreaId,
                                std::string strDevice
                                );
//#define CMD_CS_FAST_AUTH			CMD_MAKE_CLIENT(0x0002) //快速登录 请求认证{string strUid,uint32 dwVersion string(32)用户名;string(32)密码 + uint16 wAreaId}
    static void SendFastAuth(
                             std::string strUid,
                             uint32 dwVersion,
                             std::string strUsername,
                             std::string strPassword,
                             uint16 wAreaId,
                             std::string strDevice
                             );
//#define CMD_CS_OTHER_AUTH			CMD_MAKE_CLIENT(0x0003) //客户端请求91快速认证{string strUid,uint32 dwVersion string(32)用户名;string(32)密码+ uint16 wAreaId}
    static void SendThirdAuth(
                              std::string strUid,
                              uint32 dwVersion,
                              std::string strUsername,
                              std::string strPassword,
                              uint16 wAreaId,
                              std::string strDevice
                              );
    
    static void SendReqPVPBattleInfo();
    
    
    static void Attach(CObserverMsg * pObserver)
	{
		m_setObservers.insert(pObserver);
	}
	static void Detach(CObserverMsg * pObserver)
	{
		m_setObservers.erase(pObserver);
	}
	static void NotifyRefeashLayer()
	{
		std::set<CObserverMsg *>::iterator ii = m_setObservers.begin();
		for(; ii != m_setObservers.end(); ++ii)
		{
			(*ii)->RefeashLayer();
		}
	}
    
    static bool NotifyErrorMessage(uint16 wErrorNo)
    {
        std::set<CObserverMsg *>::iterator ii = m_setObservers.begin();
        for(; ii != m_setObservers.end(); ++ii)
        {
            if ((*ii)->NotifyErrorMsg(wErrorNo)) {
                return true;
            }
        }
        return false;
    }
    
//#define CMD_CS_REQ_ACTIVE_LIST			CMD_MAKE_CLIENT(0x0022) // 请求普通活动}
    static void SendNormalMap();
//#define  CMD_CS_REQ_STAGE_INFO			CMD_MAKE_CLIENT(0x0005)  // 客户端请求Stage List {uint16 wMapId ]}
    static void SendReqStageInfo(uint8 byType, uint16 wMapId);

//#define  CMD_CS_BATTLE_STAGE_INFO		CMD_MAKE_CLIENT(0x0006)  // 客户端请求战斗 { uint16 wMapId + uint16 wStageId }
    static void SendStartBattle(uint8 byType, uint16 wMapId, uint16 wStageId, uint8 byIsPay);
    
    //CMD_CS_CLIENT_BATTLE_INFO		CMD_MAKE_CLIENT(0x0011)  // 客户端战斗报 { 战斗类型 {uint8 byType + uint16 para1 + uint16 para2 +  uint16 para3} 战斗结果 {uint8 byResult} 战斗包信息}
    static void SendBattleResult(uint8 byType, uint16 para1, uint16 para2,  uint16 para3, uint8 byResult);
    
//    #define  CMD_CS_OPERATE_BATTLE_BAG		CMD_MAKE_CLIENT(0x000A)  // 客户端发送操控宠物背包之后背包信息 { uint8 byIndex + uint8 byLeaderSite + uint8 bySize +{ uint32 dwPetId { 1-6 号位的宠物} }}
    static void SendTeamUpdate(std::map<uint8, CTeam*> mapTeam);
    
//     #define CMD_CS_ELECT_BATTLE_TEAM		CMD_MAKE_CLIENT(0x000D)   // 选择替换出战队伍 {  uint8 byTeamInId  + uint8 buTeamOutId}
    static void SendChdBattleTeam(uint8 byInTeamId, uint8 OutTeamId);
    
//    #define CMD_CS_PET_SELL					CMD_MAKE_CLIENT(0x0029)   // 卖宠物 {uint32 dwPetObjId}
    static void SendPetSell(uint8 bySize, std::vector<uint32> arrPetObjId);
    
//#define CMD_CS_PET_EAT					CMD_MAKE_CLIENT(0x001F) // 宠物吃　强化　｛主吃　uint32 dwPetObjId +　 uint8 bySize + {　被吃 uint32 dwPetObjId}｝}
    static void SendPetEat(uint32 dwPetObjId, uint8 bySize, std::vector<uint32> arrBeEatObjId);
    
//#define CMD_CS_PET_EVOLVE				CMD_MAKE_CLIENT(0x0020) // 宠物进化　｛uint32 dwPetObjId ｝}
    static void SendPetEvolve(uint32 dwPetObjId);
    
//#define CMD_CS_CLIENT_BATTLE_INFO		CMD_MAKE_CLIENT(0x0011)  // 客户端战斗报 { 战斗类型 {uint8 byType + uint16 para1 + uint16 para2 +  uint16 para3} 战斗结果 {uint8 byResult} 战斗包信息}
    static void SendPveFightResult(uint8 byType, uint16 para1,  uint16 para2,   uint16 para3, uint8 byRet, uint32 dwDamage, uint32 dwMoney);

//#define CMD_CS_REQ_ARENA_LIST			CMD_MAKE_CLIENT(0x0013)  // 请求竞技场页面 {}
    static void SendEnterArenaSceneRequest();
    
//#define CMD_CS_ARENA_FIHGT_LIST			CMD_MAKE_CLIENT(0x0027)   // 请求竞技场 挑战序列}
    static void SendArenaBattleListRequest();
    
//#define CMD_CS_ARENA_RANK_LIST			CMD_MAKE_CLIENT(0x0028)   // 请求竞技场 排行榜}
    static void SendArenaRankListRequest();
//#define CMD_CS_ARENA_LEARN				CMD_MAKE_CLIENT(0x0026)  // 竞技场切磋 {uint32 dwUserId + uint32 dwRank}
    static void SendArenaLearn(uint32 dwUserId, uint32 dwRank);
    
//#define CMD_CS_FIGHT_IN_ARENA			CMD_MAKE_CLIENT(0x0012)  // 竞技场战斗 {uint32 dwUserId + uint32 dwRank}
    static void SendArenaBattle(uint32 dwUserId, uint32 dwRank);
//#define CMD_CS_ARENA_REWARD				CMD_MAKE_CLIENT(0x0025)  // 竞技场领奖}
    static void SendArenaReward();
//#define CMD_CS_REQ_ARENA_SHOP_LIST				CMD_MAKE_CLIENT(0x0072) // 请求竞技商店列表}
    static  void SendRequestArenaShopList();
//#define CMD_CS_ARENA_SHOP_EXCHANGE				CMD_MAKE_CLIENT(0x0073) // 竞技商店 兑换 {uint32 dwIndex }
    static void SendArenaShopExchange(uint32 dwIndex);
//#define CMD_CS_REQ_FARM_INFO			CMD_MAKE_CLIENT(0x002A)   // 请求庄园 生产型基本信息/}
    static void SendCountryRequest();
//#define CMD_CS_CLICK_FARM_REWARD		CMD_MAKE_CLIENT(0x002C)	// 点击领取奖励 { uint8 byType }
    static void SendFarmRewardClick(uint8 byType);
////#define CMD_CS_REQ_UPGRADE_BUILDER		CMD_MAKE_CLIENT(0x002B) // 请求建筑升级信息}
//    static void SendBuildUpgrade();
//#define CMD_CS_REQ_RES_OTHER_INFO		CMD_MAKE_CLIENT(0x002F)  // 请求具体庄园 掠夺型建筑信息 {uint8 byType}
    static void SendCaptureReq(uint8 byType);
    
//#define CMD_CS_REQ_CAPTURE_LIST			CMD_MAKE_CLIENT(0x0032) // 请求挑战列表}
    static void SendCaptureList();
//#define CMD_CS_ROB_CLICK_FARM_REWARD    CMD_MAKE_CLIENT(0x0030) // 领奖}　｛ uint8 byType + uint8 byFarmId｝}
    static void SendRobRewardClick(uint8 byType, uint8 byFarmId);
//#define CMD_CS_REQ_FRIEND_HELP_LIST		CMD_MAKE_CLIENT(0x0036) // 请求好友解救列表}
    static void SendRescueFriendReq();
////#define CMD_CS_REQ_MAIL_LIST			CMD_MAKE_CLIENT(0x0037) // 请求邮件列表}
//    static void SendMailListRequest(uint8 byMailType);
//#define CMD_CS_REQ_MAIL_INFO			CMD_MAKE_CLIENT(0x0038) // 请求邮件详细信息　{uint32 dwMailId}
    static void SendReadMailInfo(uint32 dwMailId);
//#define CMD_CS_MAIL_REWARD				CMD_MAKE_CLIENT(0x0039) // 领取邮件奖励　{uint32 dwMailid }
    static void SendMailReward(uint8 byType, uint32 dwMailId = 0);
//#define CMD_CS_DEL_MAIL					CMD_MAKE_CLIENT(0x003A) // 删除普通邮件 { uint32 dwMailId }
    static void SendDelMail(uint32 dwMailId);
    //同一个解救界面，不同按钮}
//#define CMD_CS_BATTLE_CAPTURE_SLAVE		CMD_MAKE_CLIENT(0x0033) // 抓奴隶　战斗　{ uint32 dwObjId + uint8 byType + uint8 byFarmId }
    static void SendCaptureSlave(uint32 dwObjId, uint8 byType, uint8 byFarmId);
//#define CMD_CS_BATTLE_SLAVE_HELP		CMD_MAKE_CLIENT(0x0035) // 解救帮助　战斗　{ uint32 dwSlaveId }
    static void SendSlaveHelp(uint32 dwSlaveId);

//#define CMD_CS_BATTLE_SLAVE_REVOLT		CMD_MAKE_CLIENT(0x0034) // 奴隶反抗　战斗　{ uint32 dwMasterId + uint8 byType + uint8 byFarmId }
    static void SendSlaveRevolt(uint32 dwMasterId, uint8 byType, uint8 byFarmId);
    //    #define CMD_CS_GM_CMD					CMD_MAKE_CLIENT(0x0021) // Gm 命令 {std::string }
    static void SendGM(std::string gmStr);
//#define CMD_CS_REQ_FRIEND_LIST			CMD_MAKE_CLIENT(0x0040) // 请求好友列表}
    static void SendFriendReq();
//#define CMD_CS_REQ_LOTTERY				CMD_MAKE_CLIENT(0x004A) //  请求抽奖　｛uint8 byType + byIsTen｝}
    static void SendReqLottery(uint8 byType, uint8 byIsTen);
//#define CMD_CS_REQ_LOTTERY_BLOAD		CMD_MAKE_CLIENT(0x004B) // 请求抽奖 面板信息}
    static void SendLotteryInfo();
//#define CMD_CS_REQ_LOTTERY_DOLLAR		CMD_MAKE_CLIENT(0x004C) // 请求抽取 钻石 ｛uint8 byType + byIsTen｝}
    static void SendReqLotteryDollar(uint8 byType, uint8 byIsTen);
//#define CMD_CS_PASSIVE_SPELL_UPGRADE	CMD_MAKE_CLIENT(0x0015) // 被动技能升级 { uint32 dwPetObjId + uint8 byOffset + uint16 wSpellId  + bySize +{uint32 dwItemId + uint32 dwCnt}}
    static void SendPassiveSpellUpgrade(uint32 dwPetObjId, uint8 byOffset, uint32 wSpellId, vector<uint32> vecSkillBookIDs);
//#define CMD_CS_PASSIVE_SPELL_ADD		CMD_MAKE_CLIENT(0x0016) // 被动技能添加 {  uint32 dwPetObjId + uint8 byOffset + uint32 dwItemId  技能书Id}
    static void SendPassiveSpellAdd(uint32 dwPetObjId, uint8 byOffset, uint32 dwItemId);
//#define CMD_CS_PASSIVE_SPELL_EFFECT		CMD_MAKE_CLIENT(0x0017) // 被动技能生效 { uint32 dwPetObjId + uint8 byOffset + uint32 dwSpellId + 技能书Id}
    static void SendPassiveSpellEffect(uint32 dwPetObjId, uint8 byOffset, uint32 dwSpellId, uint32 dwItemId);
//#define CMD_CS_SELL_ITEM				CMD_MAKE_CLIENT(0x0018) // 卖出物品　｛uint32 dwItemObjId + uint16 wNum｝}
    static void SendSellItem(uint32 dwItemObjId, uint16 wNum);
//#define CMD_CS_ITEM_USE					CMD_MAKE_CLIENT(0x0019) // 使用物品　{uint32 dwItemObjId + uint16 wNum}
    static void SendItemUse(uint32 dwItemObjId, uint16 wNum);
//#define CMD_CS_PET_LOCKED				CMD_MAKE_CLIENT(0x0024) // 宠物锁定 {uint8 bySize +{ uint32 dwPetObjId + uint8 bIsLock(1 解锁 0 加锁)} }
    static void SendPetLocked(std::map<uint32, bool> mapPetLocked);
//#define CMD_CS_ITEM_BAG_ENLARGE			CMD_MAKE_CLIENT(0x005D) // 商城行为 {}
    static void SendItemBagEnlager(uint8 byType);
//#define CMD_CS_REQ_BAG_ENLARGE_DOLLAR   CMD_MAKE_CLIENT(0x005E) // 请求背包扩充 需要钻石D}
    static void SendReqBagEnlagerDollar(int tag);
//#define CMD_CS_REQ_NO_FRIEND_LIST		CMD_MAKE_CLIENT(0x0046) // 请求人物信息 {uint32 dwUserId}
    static void SendReqFindFriend(uint32 dwUserId);
//#define CMD_CS_REQ_APPLE_FRIEND			CMD_MAKE_CLIENT(0x0042) // 申请加别人好友　｛uint32 dwUserId｝}
    static void SendReqApplyFriend(uint32 dwUserId);
//#define CMD_CS_AGREE_APPLY				CMD_MAKE_CLIENT(0x0044) // 同意加好友 ｛uint32 dwUserId｝}
    static void SendAgreeFriendApply(uint32 dwUserId);
//#define CMD_CS_DISAFREE_APPLY			CMD_MAKE_CLIENT(0x0045) // 拒绝加好友 ｛uint32 dwUserId｝}
    static void SendDisagreeFriendApply(uint32 dwUserId);
//#define CMD_CS_DELTE_FRIEND				CMD_MAKE_CLIENT(0x0043) // 删除好友 ｛uint32 dwUserId｝}
    static void SendDelFriend(uint32 dwUserId);

//#define CMD_CS_ADD_GEM_PET				CMD_MAKE_CLIENT(0x005A) // 宠物添加宝石 {uint32 dwPetObjId + uint32 dwGemKeyId }
    static void SendAddGemToPet(uint32 dwPetObjId, uint32 dwGemKeyId);
//#define CMD_CS_SELL_GEM					CMD_MAKE_CLIENT(0x005B) // 卖宝石 { uint32 dwGemKeyId }
    static void SendSellGem(uint32 dwGemKeyId);
//#define CMD_CS_VAIL_GEM					CMD_MAKE_CLIENT(0x005C) // 卸下宝石 {uint32 dwPetObjId + uint32 dwGemKeyId}
    static void SendVailGem(uint32 dwPetObjId, uint32 dwGemKeyId);

//#define CMD_CS_REQ_ACTIVE_MAP_LIST		CMD_MAKE_CLIENT(0x0007)  // 客户端请求活动Map序列}
    static void SendSpecialMapList();
//#define CMD_CS_REQ_ACTIVE_STAGE_INFO	CMD_MAKE_CLIENT(0x0008)  // 客户端请求活动Stage List {uint16 wMapId ]}
    static void SendSpecialStageInfo(uint16 wMapId);
//#define CMD_CS_REQ_UPGRADE_BUILDER		CMD_MAKE_CLIENT(0x002B) // 请求建筑升级信息}
    static void SendReqUpgradeBuildInfo();
//#define CMD_CS_UPGRADE_FARM_BUILD		CMD_MAKE_CLIENT(0x002D)// 升级庄园建筑　{uint8 byType}
    static void SendUpgradeBuild(uint8 byType);
//#define CMD_CS_SEND_MSG					CMD_MAKE_CLIENT(0x003B) // 发送留言 {uint32 dwUserId + std::string strTitle + std::string strContent}
    static void SendFriendMsg(uint32 dwUserId, std::string strTitle, std::string strContent);
//#define CMD_CS_REQ_SHOP_INFO			CMD_MAKE_CLIENT(0x0060) // 进入商城请求信息 {}
    static void SendOpenShopRequest();
//#define CMD_CS_SHOP_BUY_INFO			CMD_MAKE_CLIENT(0x0061) // 普通购买 {uint32 dwGoodsId + uint32 dwNum}
    static void SendShopBuyItem(uint32 dwGoodsId, uint32 dwNum);
//#define CMD_CS_SHOP_OTHER_PAY			CMD_MAKE_CLIENT(0x0062) // 充值购买 {uint32 dwGoodsId  + .... }
    static void SendShopBuyOtherPay();
//#define CMD_CS_SELL_EQUIP				CMD_MAKE_CLIENT(0x001A) // 卖出装备　{ uint8 bySize + {uint32 dwEquipObjId } }
    static void SendSellEquip(vector<uint32> vecEquipObjId);
    
    
//#define CMD_CS_EQUIP_TO_TEAM						CMD_MAKE_CLIENT(0x0144)
    /** 装备装备队伍}
     uint32	dwEquipObjId
     uint8	bySite
     uint8	byOffset
     */
    static void SendEquipToPet(uint32 dwEquipId, uint8 bySite, uint8 byOffset);
//#define CMD_CS_UPGRADE_EQUIP			CMD_MAKE_CLIENT(0x001C) // 装备升级　｛uint32 dwEquipObjId + uint8 byType (0 普通 1 一键升级)｝}
    static void SendUpgradeEquip(uint32 dwEquipObjId, uint8 byType = 0);

//#define CMD_CS_EQUIP_VAIL_TEAM						CMD_MAKE_CLIENT(0x0145)
    /** 装备脱下}
     uint32 dwEquipId
     uint8  bySite
     uint8  byOffset
     */
    static void SendEquipVail(uint32 dwEquipId, uint8 bySite, uint8 byOffset);
//#define CMD_CS_EQUIP_RUNES				CMD_MAKE_CLIENT(0x0063) // 装备符文 {uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId}
    static void SendRuneToEquip(uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId);
//#define CMD_CS_UNDRESS_RUNES			CMD_MAKE_CLIENT(0x0064) // 脱下符文 {uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId}
    static void SendRuneUnload(uint32 dwEquipId, uint8 byOffset, uint32 dwRunesId);
//#define CMD_CS_MATERIAL_SYNC			CMD_MAKE_CLIENT(0x0066) // 物品合成 {uint32 dwIndex + uint8 byType + uint8 IsSenior}
    static void SendEquipCompound(uint32 dwIndex, uint8 byType, uint8 isSenior);
//#define CMD_CS_EQUIP_ENLARGE_RUNES		CMD_MAKE_CLIENT(0x0068) // 装备开符文槽 {uint32 dwEquipId }
    static void SendEquipEnlageRune(uint32 dwEquipId);
    
//#define CMD_CS_ACTIVE_BATTLE_STAGE_INFO CMD_MAKE_CLIENT(0x0009)  // 客户端请求活动战斗 { uint16 wMapId + uint16 wStageId }
    static void SendSpecialBattle(uint16 wMapId, uint16 wStageId, uint8 byIsPay);

//#define CMD_CS_EARN_ENERGY_REW			CMD_MAKE_CLIENT(0x0069) // 领取每日能量奖励}
    static void SendEarnEnergyReward();
//#define CMD_CS_EARN_SEVEN_ONLINE_REW	CMD_MAKE_CLIENT(0x006A) // 领取每日登陆奖励 7日}
    static void SendEarnSevenReward();
//#define CMD_CS_EARN_THIRTY_ONLINE_REW	CMD_MAKE_CLIENT(0x006B) // 领取新手30日登陆奖励}
    static void SendEarnThirtyReward();
    
    //#define CMD_CS_ADD_SPELL_EXP					CMD_MAKE_CLIENT(0x006E) // 添加祭炼值 	{ bySize +{uint32 dwItemId + uint32 dwCnt}}
    static void SendSkillExpAdd(std::vector<uint32> arrItemId);
    //#define CMD_CS_SPELL_UPGRADE					CMD_MAKE_CLIENT(0x006F) // 技能升级		{ uint32 dwPetObjId + uint8 byOffset + uint32 dSpellId + uint32 dwExp }
    static void SendSkillUpgread(uint32 dwPetObjId, uint8 byOffset, uint32 dSpellId, uint32 dwExp);
//#define CMD_CS_UPDATE_ENERGY_REC_TIME			CMD_MAKE_CLIENT(0x0071) // 请求更新能量回复时间}
    static void SendUpdateEnergyRecTime();
//#define CMD_CS_NEW_ROLE_NUM						CMD_MAKE_CLIENT(0x0078) // 新手流程数字 {uint16 wProgress}
    static void SendTriggerNum(uint16 wProgress);
    
//#define CMD_CS_CHOOSE_NAME						CMD_MAKE_CLIENT(0x0079) // 选择名字 {std::string Name}
    static void SendChooseName(std::string strName);
//#define CMD_CS_CHOOSE_PET						CMD_MAKE_CLIENT(0x007A) // 选择宠物 {uint16 wPetId}
    static void SendChoosePet(uint16 wPetId);
//#define CMD_CS_DAILY_QUEST_REWARD				CMD_MAKE_CLIENT(0x006C) // 0日常任务奖励 {uint32 dwIndex}
    static void SendDailyQuestRewardRequest(uint8 byType, uint32 dwIndex);
//#define CMD_CS_ACHIEVE_REWARD					CMD_MAKE_CLIENT(0x006D) // 成就奖励 {uint32 dwType + uint32 dwIndex}
    static void SendAchieveRewardRequest(uint32 dwType, uint32 dwIndex);
//#define CMD_CS_FRIEND_SHARE						CMD_MAKE_CLIENT(0x007C) // 好友分享}
    static void SendFriendShareRequest();
//#define CMD_CS_INVITE_CODE						CMD_MAKE_CLIENT(0x007B) // 邀请码 { std::string strInvideCode }
    static void SendInviteCode(std::string strInvideCode);
//#define CMD_CS_REQ_REFERRER						CMD_MAKE_CLIENT(0x007E) // 请求邀请人界面}
    static void SendEnterInviteSceneRequest();
//#define CMD_CS_FRIEND_REFERRER					CMD_MAKE_CLIENT(0x007D) // 好友邀请  { uint32 dwReferrerId }
    static void SendInviteID(uint32 dwReferrerId);
//#define CMD_CS_PET_FUSE							CMD_MAKE_CLIENT(0x0074)
    /**
     * 	宠物融合 兑换 融合石}
     * 	[uint8] count
     * 		[uint32] dwPetKeyId
     * */
    static void SendPetFuse(uint8 byType, std::vector<uint32> arrPetId);
//#define CMD_CS_REQ_MYSTERY_SHOP_LIST			CMD_MAKE_CLIENT(0x0075) // 请求神秘商城列表}
    static void SendReqMySteryShopList();
//#define CMD_CS_MYSTERY_SHOP_BUY					CMD_MAKE_CLIENT(0x0076) // 神秘商城购买 { uint32 dwGoodId }
    static void SendMySteryShopBy(uint32 dwGoodsId);
//#define CMD_CS_MYSTERY_SHOP_UPDATE				CMD_MAKE_CLIENT(0x0077) // 神秘商城刷新}
    static void SendMySteryShopUpdate();
//#define CMD_CS_REQ_BIND_ACCOUNT					CMD_MAKE_CLIENT(0x0080) // 请求账号绑定信息}
    static void SendBindingRequest();
//#define CMD_CS_BIND_AUTO_ACCOUNT				CMD_MAKE_CLIENT(0x0081) // 账号绑定 {std::string strMail + std::string strAccount + std::string strPwd }
    static void SendBindingAccount(string strMail, string strAccount, string strPwd);
//#define CMD_CS_GROW_UP_REWARD					CMD_MAKE_CLIENT(0x0109)
    /**	成长奖励领取}
     [uint32] dwIndex
     */
    static void SendGrowUpReward(uint32 dwIndex);
//#define CMD_CS_BUY_GROW_UP						CMD_MAKE_CLIENT(0x010A)
    /** 购买成长计划}
     */
    static void SendBuyGrowUp();
//#define CMD_CS_FIRST_PAY_REWARD					CMD_MAKE_CLIENT(0x010B)
    /** 首冲奖励领取}
     */
    static void SendFirstPayReward();
//#define CMD_CS_REQ_SHOP_CNT						CMD_MAKE_CLIENT(0x0106)
    /** 请求 商城基本信息}
     */
    static void SendReqShopCnt();
//#define CMD_CS_CHAT_SEND						CMD_MAKE_CLIENT(0x0100)
    /** 聊天发言}
     * 	[uint8] ChatChannel Enum
     *  [uint32] target_id   (非私聊填0)}
     * 	[string] target_name (非私聊填0)}
     * 	[string] content */
    static void SendChatMsg(uint8 byChannel, uint32 dwTargetId, const string strTargetName, const string strContent);
//#define CMD_CS_CHAT_SWITCH						CMD_MAKE_CLIENT(0x0101)}
    /** 设置是否接受玩家聊天信息}
     [bool] bIsBanned
     */
    static void SendChatSwitch(bool bIsBanned);
    
//#define CMD_CS_CHAT_GET							CMD_MAKE_CLIENT(0x0102)}
    /** 获取最近的聊天信息}
     */
    static void SendGetChat();

//#define CMD_CS_REQ_OTHER_ROLE_INFO				CMD_MAKE_CLIENT(0x0107)}
    /** 请求其他人物信息
     [uint32] dwAccountId
     */
    static void SendReqOtherRoleInfo(uint32 dwAccountId);

//#define CMD_CS_EQUIP_EVOLVE						CMD_MAKE_CLIENT(0x010D)}
    /** 装备进阶
     [uint32 dwEquipKeyId]
     */
    static void SendReqEquipEvolve(uint32 dwEquipKeyId);
    
//#define CMD_CS_EMBLEM_EAT						CMD_MAKE_CLIENT(0x010E)}
//    /** 徽章升级 吃}
//     [uint32]	dwEmblemId		// 升级的徽章 keyId}
//     [uint8]		byCount
//     [uint32] dwEmblemId // 被吃的keyId}
//     */
    static void SendEmblemEat(uint32 dwEmblemId, std::vector<uint32> arrElem);
    
//#define CMD_CS_EMBLEM_TO_PET						CMD_MAKE_CLIENT(0x010F)
//    /** 徽章装备}
//     [uint32]	dwPetKeyId
//     [uint32]	dwEmblemKeyId
//     [uint8]		bySite  (装备位置 0 或 1)}
//     */
//
    static void SendEmblemWear(uint32 dwPetObjId, uint32 dwEmblemObjId);
//#define CMD_CS_EMBLEM_VAIL_PET						CMD_MAKE_CLIENT(0x0110)
//    /** 徽章卸下}
//     [uint32]	dwPetKeyId
//     [uint32]	dwEmblemKeyId
//     [uint8]		bySite  (装备位置 0 或 1)}
//     */
    static void SendEmblemTakeOff(uint32 dwEmblemObjId);
    
//#define CMD_CS_REQ_TOWER_INFO						CMD_MAKE_CLIENT(0x011A)
    /** 请求塔基本信息}
     */
    static void SendRequestTowerInfo();
    
//#define CMD_CS_REQ_TOWER_RANK						CMD_MAKE_CLIENT(0x011B)
    /** 请求塔排行榜}
     */
    static void SendRequestTowerRank();
    
//#define CMD_CS_RESET_TOWER_FLOOR					CMD_MAKE_CLIENT(0x011C)
    /** 重置塔当前层数}
     */
    static void SendResetTowerFloor();
    
//#define CMD_CS_FIGHT_TOWER							CMD_MAKE_CLIENT(0x011D)
    /** 挑战塔}
     *		[uint8] byType ( 1, 普通挑战 2, 自动爬塔)}
     */
    static void SendFightTower(uint8 byType);
    
//#define CMD_CS_REQ_STORE_PAY_LIST					CMD_MAKE_CLIENT(0x0126)}
    /** 请求充值List}
     **/
    static void SendRequestStorePayList();
    
    
//#define CMD_CS_REQ_WRESTLE_INFO						CMD_MAKE_CLIENT(0x0120)}
//    /** 请求道馆信息}
//     **/
    static void SendReqChallengeInfo();
//#define CMD_CS_REQ_WRESTLE_FIGHT_LIST				CMD_MAKE_CLIENT(0x0121)
//    /** 请求道馆挑战列表}
//     *		[uint32] dwMapId
//     **/
    static void SendReqChallengeLevleInfo(uint32 dwMapId);
//#define CMD_CS_RESET_WRESTLE_BLESS					CMD_MAKE_CLIENT(0x0122)
//    /** 道观祝福}
//     *		[uint32] dwMapId
//     **/
    static void SendResetChallengeBless();
    
//#define CMD_CS_WRESTLE_REWARD						CMD_MAKE_CLIENT(0x0123)
//    /** 道观领奖}
//     *		[uint32] dwMapId
//     **/
    static void SendGetChallengeReward();
//#define CMD_CS_WRESTLE_FIGHT						CMD_MAKE_CLIENT(0x0124)
//    /** 道观挑战}
//     **/
    static void SendReqChallengeFight();
    
//#define CMD_CS_NOTICE_GET						CMD_MAKE_CLIENT(0x0103)
    /** 获取游戏公告}
     */
    static void SendNoticeGet();
//#define CMD_CS_STAGE_SWEEP							CMD_MAKE_CLIENT(0x0133)
    /** 地图扫荡}
     [uint16] wStageId
     [uint8]  byMapType [ 1 普通 ; 2 精英]
     [uint8]  byCnt		扫荡次数
     **/
    static void SendStageSweep(uint16 wStageId, uint8 byMapType, uint8 byCnt);
//#define CMD_CS_MAP_SWEEP							CMD_MAKE_CLIENT(0x0134)
    /** 地图扫荡
     [uint16] wMapId
     [uint8]  byMapType [ 1 普通 ; 2 精英]
     **/
    static void SendMapSweep(uint16 wMapId, uint8 byMapType);
//#define CMD_CS_MAP_PASS_STAR_REW					CMD_MAKE_CLIENT(0x0132)}
    /** 地图通关星级奖励
     [uint16] wMapId
     [uint8]  byMapType [ 1 普通 ; 2 精英]
     [uint8]  byOffSet	条件[0, 1, 2]
     **/
    static void SendMapPassStarRew(uint16 wMapId, uint8 byMapType, uint8 byOffset);
    
//#define CMD_CS_BUY_ARENA_POINT						CMD_MAKE_CLIENT(0x0143)
    /** 购买竞技点
     **/
    static void SendBuyAreanPoint();
    
    //#define  CMD_CS_OPERATE_BATTLE_CUR_TEAM	CMD_MAKE_CLIENT(0x000B)
    /** 客户端发送操控宠物背包之后背包信息
     uint8 byIndex
     uint8 byLeaderSite
     uint8 bySize
     uint32 dwPetId { 1-6 号位的宠物}
     */
    static void SendCurTeam(CTeam* team);
    
//#define CMD_CS_BUY_STAGE_FIGHT_CNT					CMD_MAKE_CLIENT(0x0146)
    /** 挑战次数购买
     uint8  byType [1 普通地图 , 2 ,精英地图 ， 3 , 活动地图, 4 摇钱树]
     uint16 wStageId
     */
    static void SendBuyStageFightCnt(uint8 byType, uint16 wStageId);
    
//#define CMD_CS_CLEAR_SWEEP_CD_TIME					CMD_MAKE_CLIENT(0x0151)
    /** 清除扫荡　CD时间
     *		[uint8] byType (1, 请求钻石; 2, 清除CD)
     *		[uint32] dwDollar
     */
    static void SendClearSweepCDTime(uint8 byType,uint32 dwDollar = 0);

//#define CMD_CS_ENTER_WORLD_BOSS_BLOAD				CMD_MAKE_CLIENT(0x0160)
    /** 请求世界BOSS 基本信息
     */
    static void SendWorldBossInfo();
//#define CMD_CS_REQ_WORLD_BOSS_LIST					CMD_MAKE_CLIENT(0x0161)
    /** 请求世界BOSS 排行榜 上期
     */
    static void SendReqWorldBossList();
//#define CMD_CS_WORLD_BOSS_BLESS						CMD_MAKE_CLIENT(0x0162)
    /** 世界BOSS 鼓舞
     *		[uint8]  byType (1 coin; 2 dollar)
     */
    static void SendWorldBossBless(uint8 byType);
    
//#define CMD_CS_WORLD_BOSS_FIGHT						CMD_MAKE_CLIENT(0x0163)
    /** 世界BOSS 战斗
     */
    static void SendWorldBossFight(uint8 byType);
    
//#define CMD_CS_WORLD_BOSS_CLEAR_CD					CMD_MAKE_CLIENT(0x0164)
    /** 世界BOSS 清除战斗CD
     */
    static void SendWorldBossClearCD();
    
//#define CMD_CS_WORLD_BOSS_UPDATE_INFO				CMD_MAKE_CLIENT(0x0165)
    /** 世界BOSS 刷新基本信息
     */
    static void SendWorldBossUpdateInfo();
    
//#define CMD_CS_WORLD_BOSS_END_REWARD				CMD_MAKE_CLIENT(0x0166)
    /** 世界BOSS 结束结算
     */
    static void SendWorldBossEndReward();
    
//#define CMD_CS_RECOMMEND_FRIEND_LIST			CMD_MAKE_CLIENT(0x007F)
    /** 请求推荐好友列表
     */
    static void SendReqRecommendFriendList();
    
//#define CMD_CS_FRIEND_ENERGY_GIVE					CMD_MAKE_CLIENT(0x0130)
    /** 好友赠送体力
     [uint32] dwFriendId
     **/
    static void SendFriendEnergyGive(uint32 dwFriendId);
    
//#define CMD_CS_FRIEND_ENERGY_GET					CMD_MAKE_CLIENT(0x0131)
    /** 好友赠送体力领取
     [uint8]  bIsAll			(是否一键领取)
     [uint32] dwFriendId
     **/
    static void SendGetFriendEnergy(uint8 byIsAll, uint32 dwFriendId);
    
//#define CMD_CS_FIGHT_WITH_FRIEND		CMD_MAKE_CLIENT(0x0041)
    /**  好友切磋
     uint32 dwUserId
     */
    static void SendFightWithFriend(uint32 dwFriendId);
    
//#define CMD_CS_CLICK_ACTIVE_LIST					CMD_MAKE_CLIENT(0x0140)
    /** 请求活动列表
     **/
    static void SendRequestActiveList();
    
//#define CMD_CS_CLICK_ACTIVE_INFO					CMD_MAKE_CLIENT(0x0141)
    /** 请求活动具体信息
     [uint32] dwActId
     **/
    static void SendRequestActiveInfoById(uint32 dwActId);
    
//#define CMD_CS_CLICK_ACTIVE_REW						CMD_MAKE_CLIENT(0x0142)
    /** 点击活动内容 按钮 （领奖 兑换 购买 使用 等）
     [uint32] dwActId
     [uint32] dwClickId
     **/
    static void SendGetActiveRewardByActIdAndCellId(uint32 ActiveId,uint32 dwCellId);
    
//#define CMD_CS_REQ_TIME_SHOP_LIST					CMD_MAKE_CLIENT(0x016A)
    /** 请求秘境商店列表
     */
    static void SendReqMJShopList();
    
//#define CMD_CS_TIME_SHOP_BUY						CMD_MAKE_CLIENT(0x016B)
    /** 秘境商店购买
     *		[uint32] dwShopId
     */
    static void SendMJShopBuy(uint32 dwShopId);
public:
    static CRole* GetRole() { return m_pRole;};
private:
	CGameSession() {};
	~CGameSession() {};
    
    static CRole* m_pRole;
    static std::set<CObserverMsg *> m_setObservers;
};

#endif
