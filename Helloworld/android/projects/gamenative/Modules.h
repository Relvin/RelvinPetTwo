//
#ifndef ANDROID_PLATFORM_MODULES_H
#define ANDROID_PLATFORM_MODULES_H

#include <string>

// Umengsocial
void UmengSocialShareDirect(std::string method, std::string desc, std::string image);

// Hero 
#define	ACT_NATIVE_PAUSE_MUSIC	"NativePauseMusic"
#define	ACT_NATIVE_RESUME_MUSIC	"NativeResumeMusic"

// Changwan
#define ACT_CHANGWAN_REPORT	"ChanwanReport"
void PlatformChangwanReport(int type);

// Chba
#define	ACT_CHBA_POSTMAC	"ChbaPostMac"
void Changba_PostMac(int status);

// Dena
#define	ACT_DENA_SHOW_ICON  "DenaShowIcon"
#define	ACT_DENA_HIDE_ICON  "DenaHideIcon"
#define	ACT_DENA_PAY_RESULT  "DenaPayResult"
void onShowButton();
void onHideButton();

// Gfan
bool isTryAccount();
void onRegesiter();

// PPS
#define	ACT_PPS_SET_SERVERID	"PpsSetServerId"
#define	ACT_PPS_REPORT_EVENT	"PpsReportEvent"
#define PPS_ANDROID_EVENT_CREATE_ROLE "create_role"
#define PPS_ANDROID_EVENT_CONN_GAME_SERVER_OK "conn_game_server_ok"
#define PPS_ANDROID_EVENT_ENTER_MAIN_CITY "enter_main_city"
void setServerID(int serverId);
void PlatformPpsReportEvent(const char* eventId);

// CMCC
#define	ACT_CMCC_MUSICON	"CmccMusicOn"
bool PlatformCMCCGetMusicOn();

// 51
#define	ACT_REPORT_LOGIN		"ReportLogin"
#define	ACT_REPORT_LOGOUT		"ReportLogout"
#define	ACT_REPORT_CREATE_ROLE	"ReportCreateRole"
void Platform51LogoutRole(int gameLevel);
void Platform51CreateRole(const char* role, const char* nickName);
void Platform51LoginServer(int serverId, const char* serverName, int gameLevel);

// Facebook(tw)
void FBLogin();
void FBLogout();
void FBInvite(const char *title, const char *message);
void FBFeed(const char *link, const char *picture, const char *name, const char *caption, const char *description);

// txwy
void PlatformTxwyCreateRole();

// oppo
#define	ACT_OPPO_REPORT_LOGIN		"ReportLogin"
void PlatformOppoReportLogin(int serverId, const char* roleName, int level);

// youmi
// "ReportLogin"
//  ServerId=serverid|ServerName=servername|RoleId=id|UserName=roleName|RoleLv=level

// appchina
void openYYHSplash();

// Umeng
void UMengEvent(const char* _event);
void UMengShare(const char* _txt, const char* _url, bool _req_reward);
std::string UmengetRemoteCfg(const char*key);

#endif
