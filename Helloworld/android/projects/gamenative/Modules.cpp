#include "Modules.h"
#include "PlatformMgr.h"

#include "LoginSystem.h"

using namespace platform;

static char params[512]={0};


void UmengSocialShareDirect(std::string method, std::string desc, std::string image)
{
	sprintf(params, "Method=%s|Image=%s|Desc=%s", method.c_str(), image.c_str(), desc.c_str());
	
	platform::PlatformMgr::getInstance()->call("UmengSocial", "ShareDirect", params);
    
}

#if 0

// Changwan
void PlatformChangwanReport(int type)
{
	int serverId = Client::LoginSystem::GetSystem().getSelectedServer();
	const char* userName = Client::PlayerInfo::GetPlayerInfo().GetUserName().c_str();
	
	sprintf(params, "Type=%d|ServerId=%d|UserName=%s", type, serverId, userName);
	
	platform::PlatformMgr::getInstance()->call(ACT_CHANGWAN_REPORT, params);
}

// Chba
void Changba_PostMac(int status)
{
	sprintf(params, "State=%d", status);
	platform::PlatformMgr::getInstance()->call(ACT_CHBA_POSTMAC, params);
}

// Dena
void onShowButton()
{
	platform::PlatformMgr::getInstance()->call(ACT_DENA_SHOW_ICON, params);
}
void onHideButton()
{
	platform::PlatformMgr::getInstance()->call(ACT_DENA_HIDE_ICON, params);
}

// Gfan
bool isTryAccount()
{
	// Needed ?
}
void onRegesiter()
{
}

// PPS
void setServerID(int serverId){
	sprintf(params, "ServerId=%d", serverId);
	platform::PlatformMgr::getInstance()->call(ACT_PPS_SET_SERVERID, params);
}
void PlatformPpsReportEvent(const char* eventId){
    CCLog("PlatformPpsReportEvent eventid=%s", eventId);

    // Report main city only when first enter game
    static bool reportMainCity = true;
    if(strcmp(PPS_ANDROID_EVENT_CONN_GAME_SERVER_OK, eventId) == 0)
    {
        reportMainCity = true;
    }
    if(strcmp(PPS_ANDROID_EVENT_ENTER_MAIN_CITY, eventId) == 0)
    {
        if(!reportMainCity)
        {
            CCLog("PlatformPpsReportEvent skip eventid=%s", eventId);
            return;
        }
        reportMainCity = false;
    }
    CCLog("PlatformPpsReportEvent do eventid=%s", eventId);
    
	sprintf(params, "EventId=%s", eventId);
	platform::PlatformMgr::getInstance()->call(ACT_PPS_REPORT_EVENT, params);
}

// CMCC
bool PlatformCMCCGetMusicOn()
{
	std::string resultStr = platform::PlatformMgr::getInstance()->call(ACT_CMCC_MUSICON, params);
    Request result = Request(resultStr);
    bool on = result.getInt("Result", 0) == 1;
	return on;
}

// 51
void Platform51LogoutRole(int gameLevel)
{
	platform::PlatformMgr::getInstance()->call(ACT_REPORT_LOGOUT, NULL);
}
void Platform51CreateRole(const char* role, const char* nickName)
{
	sprintf(params, "Role=%s|UserName=%s", role, nickName);
	platform::PlatformMgr::getInstance()->call(ACT_REPORT_CREATE_ROLE, params);
}
void Platform51LoginServer(int serverId, const char* serverName, int gameLevel)
{
	sprintf(params, "ServerId=%d|ServerName=%s|RoleLv=%d", serverId, serverName, gameLevel);
	platform::PlatformMgr::getInstance()->call(ACT_REPORT_LOGIN, params);
}

// facebook(tw)
void FBLogin()
{
}
void FBLogout()
{
}
void FBInvite(const char *title, const char *message)
{
}
void FBFeed(const char *link, const char *picture, const char *name, const char *caption, const char *description)
{
}

// txwy
void PlatformTxwyCreateRole()
{
	CCLog("PlatformTxwyCreateRole Not impl yet");
}


// oppo
void PlatformOppoReportLogin(int serverId, const char* roleName, int level)
{
	sprintf(params, "ServerId=%d|UserName=%s|RoleLv=%d", serverId, roleName, level);
	platform::PlatformMgr::getInstance()->call(ACT_OPPO_REPORT_LOGIN, params);
}

// Umeng
void UMengEvent(const char* _event) {
    sprintf(params, "Id=%s", _event);
    PlatformMgr::getInstance()->call("Umeng", "Event", params);
}
void UMengShare(const char* _txt, const char* _url, bool _req_reward)
{
    sprintf(params, "Desc=%s", _txt);
    PlatformMgr::getInstance()->call("Umeng", "Share", params);
}
std::string UmengetRemoteCfg(const char*key)
{
    sprintf(params, "Key=%s", key);
    Request result = PlatformMgr::getInstance()->call("Umeng", "GetCfg", params);
    return result.getString("Value");
}
#endif
