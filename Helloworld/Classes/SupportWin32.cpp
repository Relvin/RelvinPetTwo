
#include "Support.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "LoginSystem.h"



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
	return "Win32idfv";
}

const char* Support::appIdfa()
{
	return "Win32idfa";
}

// MODEL
const char* Support::deviceType()
{
	return "Win32";
}

// todo 系统版本号}
const char* Support::deviceOS()
{

	return "Windows7";
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
	return "pet2_1234566";
}

void Support::delUdidInKeyChain()
{
}

// todo 版本号}
const char* Support::appVersion()
{
	return "1.0.0";
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
    return 1;
}

void Support::networkDis()
{
    LoginSystem::Get()->EnterBackGround();
    LoginSystem::Get()->ShowNoServiceLayer();
}

void Support::addLocalNotificationByType(bool twoDayNotiOpen) {
    //TODO: win32通知
}

const char* Support::umengKey() {
    return "5412c177fd98c50b03007c10";
}

const char* Support::appStoreUrl() {
    //TODO: 返回win32下载地址
}

const char* Support::weChatAppId() {
    return "wxe8152f24a1f16deb";
}

const char* Support::talkingData() {
    return "62CB5BDB740F52C73AC19CC817178B8B";
}

#endif
