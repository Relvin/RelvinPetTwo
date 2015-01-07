#ifndef PLATFORM_GAME_H
#define PLATFORM_GAME_H

#include <string>


#define PLATFORM_GAME_CMD_DEV_TYPE "PLATFORM_GAME_CMD_DEV_TYPE"
#define PLATFORM_GAME_CMD_DEV_OS_VER "PLATFORM_GAME_CMD_DEV_OS_VER"
#define PLATFORM_GAME_CMD_DEV_MEMSIZE "PLATFORM_GAME_CMD_DEV_MEMSIZE"

// Game specific cals from native to java
std::string PlatformGetDeviceId();
int  PlatformGetAccountChannel();
int PlatformGetNetworkState();
std::string PlatformGetAppVersion();
void PlatformSetSplashGone();
void PlatformOpenUrl(const char*);

std::string PlatformGetDeviceIdType();
std::string PlatformGetDeviceName();
void PlatformAddNotification(const char *id, int seconds,const char *desc);
void PlatformAddNotificationInWeek(const char *id, int day,int hour,int minites,const char *desc);
void PlatformDelAllNotification();
int PlatformGetNetType();
std::string PlatformGameCall(std::string cmd);
void PlatformUMengEvent(const char *id, const char *info,int count);
void PlatformTdEvent(const char *id, const char *info,int count);
std::string PlatformGetRemoteCfg(const char* key);
int PlatformGetRemoteCfgInt(const char* key, int def);
void PlatformUMengShare(const char* msg, const char* img);
float PlatformGetUsedMemMB();

// Game specific cals from java to native. No protypes needed


#endif


