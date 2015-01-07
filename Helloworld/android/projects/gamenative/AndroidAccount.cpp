//
//  Account.cpp
//  client
//
//  Created by yuxiao on 13-12-24.
//
//

#include "AndroidAccount.h"
#include "PlatformMgr.h"
#include "cocos2d.h"
#include "StartGameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "ShopDataMgr.h"
#include "LoginSystem.h"
#include "ShopDataMgr.h"
#include "ServerListCtrl.h"

USING_NS_CC;

using namespace platform;

#if 1

static void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst )
{
 std::string::size_type pos = 0;
 std::string::size_type srclen = strsrc.size();
 std::string::size_type dstlen = strdst.size();
 
 while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
 {
  strBig.replace( pos, srclen, strdst );
  pos += dstlen;
 }
} 


void AndroidAccount::login()
{
    PlatformMgr::getInstance()->call(MODULE_USER, ACT_LOGIN, NULL);
}

void AndroidAccount::logout()
{
    PlatformMgr::getInstance()->call(ACT_LOGOUT, NULL);
}
	
void AndroidAccount::center()
{
    PlatformMgr::getInstance()->call(ACT_UCENTER, NULL);
}
	
void AndroidAccount::switchAccount()
{
    PlatformMgr::getInstance()->call(MODULE_NATIVE, ACT_LOGOUT_RESULT, NULL);
    PlatformMgr::getInstance()->call(MODULE_USER, ACT_SWITCH_ACCOUNT, NULL);
}

static char buyBuf[1024];
void AndroidAccount::buy(uint32 goodsId)
{
    CRole *prole = CGameSession::GetRole();        
    STORE_PAY_LIST_INFO* pPayItemInfo = CShopDataMgr::Get()->GetStorePayGoodsInfoById(goodsId);    
    if (!pPayItemInfo) {
        return;   
    }

#if 1
    CRole *pRole = CGameSession::GetRole();
    int roleId = pRole->GetdwAccountId();

    int intPrice = pPayItemInfo->dwPrice/100;
    float floatPrice = pPayItemInfo->dwPrice/100.00f;

    const char* goodsName = pPayItemInfo->strSecondLine.c_str();
    std::string payDescription = CShopDataMgr::Get()->GetOrderSerialByGoodsId(goodsId);
    const char* productId = "iap_id_not_set";
    const char* serverName = ServerListCtrl::Get()->selectedServerName();
    int serverId = LoginSystem::Get()->getAreaId();
    int roleLv = pRole->GetwRoleLv();
    std::string userName = pRole->GetstrUserName();

    // for miui
    int diamondBalance = pRole->GetdwDollar();
    int vipLv = pRole->GetbyVipLv();
    std::string guild_name = "";

    string_replace(userName, "|", " ");
    string_replace(guild_name, "|", " ");
    sprintf(buyBuf,"RoleId=%d|TotalMoney=%d|FloatPrice=%.2f|GoodsName=%s|PayDescription=%s|ProductId=%s|GoodsId=%d|ServerName=%s|ServerId=%d|RoleLv=%d|UserName=%s|DiamondBalance=%d|VipLv=%d|GuidName=%s", 
            roleId, intPrice, floatPrice, goodsName, payDescription.c_str(), productId, goodsId, serverName, serverId, roleLv, userName.c_str(),
            diamondBalance, vipLv, guild_name.c_str());

    PlatformMgr::getInstance()->call(MODULE_PAY, ACT_PAY, buyBuf);
#endif
}


bool AndroidAccount::exit()
{
    std::string resultStr = PlatformMgr::getInstance()->call(ACT_EXIT, NULL);
    Request result = Request(resultStr);
    bool handled = result.getInt("Result", 0) == 1;
    CCLog("AndroidAccount::exit [%d]", handled);
    return handled;
}

std::string AndroidAccount::getGoodDescription(uint32 good_id)
{
#if 0
    int platform_id = Client::LoginSystem::GetPlatformID();
    int server_id = Client::LoginSystem::GetSystem().getSelectedServer();
    uint32 user_id = Client::PlayerInfo::GetPlayerInfo().GetAccountId();
    
    char value[128] = {0};
    snprintf(value, sizeof(value), "%d-%d-%u-%u-%u", platform_id, server_id, user_id, good_id, (uint32)1);
    
    return std::string(value);
#endif
	return "";
}

#endif
