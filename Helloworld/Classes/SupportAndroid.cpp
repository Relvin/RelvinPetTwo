
#include "Support.h"
#include "LoginSystem.h"
#include "platform_android.h"
#include "GlobalData.h"


static Support* sm_pSharedSupport = NULL;

Support* Support::sharedInstance()
{
    if (!sm_pSharedSupport) {
        sm_pSharedSupport = new Support;
    }
    return sm_pSharedSupport;
}

Support::Support()
{
    
}

Support::~Support()
{
    sm_pSharedSupport = NULL;
}


// todo 系统版本号}
TargetPlatform Support::getTargetPlatform()
{
	return kTargetAndroid;
}

bool Support::isIpad()
{
    return false;
}

const char* Support::appIdfv()
{
	return "androididfv";
}

const char* Support::appIdfa()
{
	return "androididfa";
}

// MODEL
const char* Support::deviceType()
{
	return "android";
}

// todo 系统版本号}
const char* Support::deviceOS()
{
    std::string dev = PlatformGameCall(PLATFORM_GAME_CMD_DEV_TYPE);
    std::string osVer = PlatformGameCall(PLATFORM_GAME_CMD_DEV_OS_VER);
    static std::string devOs = dev + osVer;
	return devOs.c_str();
}

const char* Support::systemVersion()
{
    static std::string osVer = PlatformGameCall(PLATFORM_GAME_CMD_DEV_OS_VER);
    return osVer.c_str();
}

bool Support::isPhone5()
{
	return false;
}

float Support::getScreenHWRadio()
{
    return 1.77;
}

void Support::saveUdidToKeyChain()
{
}

// todo 设备ID}
const char* Support::readUdidFromKeyChain()
{
	return PlatformGetDeviceId().c_str();
}

void Support::delUdidInKeyChain()
{
}

// todo 版本号}
const char* Support::appVersion()
{
	return PlatformGetAppVersion().c_str();
}

const char* Support::appName()
{
	return "幻想精灵2";
}

void Support::makeScreenAlwaysOn()
{
}

// todo 屏幕常亮}
void Support::makeScreenDefault()
{
}

// todo 渠道号}
int Support::appChannel()
{
    return PlatformGetAccountChannel();
}

void Support::networkDis()
{
    LoginSystem::Get()->EnterBackGround();
    LoginSystem::Get()->ShowNoServiceLayer();
}

void Support::addLocalNotificationByType(bool twoDayNotiOpen) {
    //TODO: android通知
}

const char* Support::umengKey() {
    return "5412c177fd98c50b03007c10";
}

const char* Support::appStoreUrl() {
    //TODO: 返回安卓下载地址
}

const char* Support::weChatAppId() {
    return "wxe8152f24a1f16deb";
}

const char* Support::talkingData() {
    return "62CB5BDB740F52C73AC19CC817178B8B";
}

double Support::usedMem()
{
	return PlatformGetUsedMemMB();
}

void Support::setSplashGone()
{
	PlatformSetSplashGone();
    setUmengDataAfterUmengUpdateCallBack();
}


int Support::getUmengInt(const char * key)
{
    return PlatformGetRemoteCfgInt(key, 0);
}

void Support::setUmengDataAfterUmengUpdateCallBack() {
    
    CCLog("Support::setUmengDataAfterUmengUpdateCallBack");
    GlobalData::shared()->setVipSwitch(getUmengInt("VIPSwitch"));
    GlobalData::shared()->setShareSwitch(getUmengInt("ShareSwitch"));
    GlobalData::shared()->setGachaSwitch(getUmengInt("GachaSwitch"));
    GlobalData::shared()->setShopListSwitch(getUmengInt("ShopListSwitch"));
}
