

#include "cocos2d.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>
#include <cstring>

#include "platform_game.h"
#include "PlatformMgr.h"

using namespace platform;
USING_NS_CC;


// Game specific cals from native to java

#define PLATFORM_PACKAGE_NAME "com/gamed9/platform/PlatformGame"

static char cmd[512] = {0};

std::string PlatformGetDeviceId()
{
	JniMethodInfo t;
	if(!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME,"jniGetDeviceId","()Ljava/lang/String;")){
		return "";
	}
    
    jstring jid = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID);
	std::string id = JniHelper::jstring2string(jid);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(jid);

	return id;
}

int PlatformGetAccountChannel()
{
	JniMethodInfo t;
 	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "jniGetAccountChannel", "()I")) {
		return 0;
	}

	int accountChannel = t.env->CallStaticIntMethod(t.classID, t.methodID);
    t.env->DeleteLocalRef(t.classID);

    return accountChannel;
}

int PlatformGetNetworkState()
{
	JniMethodInfo t;
 	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "jniGetNetworkState", "()I")) {
		return 0;
	}
    
	int state = t.env->CallStaticIntMethod(t.classID, t.methodID);
    t.env->DeleteLocalRef(t.classID);

    return state;

}

std::string PlatformGetAppVersion(){
	JniMethodInfo t;
	std::string  appVer;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME,
		"jniGetAppVersion","()Ljava/lang/String;")){
		return "";
	}
    
    jstring version = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID);
    appVer = JniHelper::jstring2string(version);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(version);
	return appVer;
}

void PlatformOpenUrl(const char* url)
{
	JniMethodInfo t;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "jniOpenUrl",
			"(Ljava/lang/String;)V")) {
		return;
	}

    jstring jstr = t.env->NewStringUTF(url);
	t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(jstr);

}


std::string PlatformGetDeviceIdType(){
	JniMethodInfo t;
	std::string  value;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME,
		"jniGetDeviceIdType","()Ljava/lang/String;")){
		return "";
	}
    
    jstring jvalue = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID);
    value = JniHelper::jstring2string(jvalue);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(jvalue);

	return value;
}

std::string PlatformGetDeviceName(){
	JniMethodInfo t;
	std::string  appVer;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME,
		"jniGetDeviceName","()Ljava/lang/String;")){
		return "";
	}
    
    jstring version = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID);
    appVer = JniHelper::jstring2string(version);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(version);

	return appVer;
}

void PlatformAddNotification(const char *id, int seconds,const char *desc)
{
	JniMethodInfo t;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "jniAddNotification",
			"(Ljava/lang/String;ILjava/lang/String;)V")) {
		return;
	}

    jstring jstr = t.env->NewStringUTF(id);
    jstring jinfo = t.env->NewStringUTF(desc);
	t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr, seconds,jinfo);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(jstr);
    t.env->DeleteLocalRef(jinfo);
}

void PlatformAddNotificationInWeek(const char *id, int day,int hour,int minites,const char *desc)
{
	JniMethodInfo t;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "jniAddNotificationInWeek",
			"(Ljava/lang/String;IIILjava/lang/String;)V")) {
		return;
	}

    jstring jstr = t.env->NewStringUTF(id);
    jstring jinfo = t.env->NewStringUTF(desc);
	t.env->CallStaticVoidMethod(t.classID, t.methodID, jstr, day, hour, minites, jinfo);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(jstr);
    t.env->DeleteLocalRef(jinfo);
}

void PlatformSetSplashGone()
{
	JniMethodInfo methodInfo;
	if (! JniHelper::getStaticMethodInfo(methodInfo, "com.gamed9.pet2.Pet2", "setSplashGone",
		"()V"))
	{
		CCLOG("%s %d: error to get setSplashGone", __FILE__, __LINE__);
        return;
	}
	else
	{
		methodInfo.env->CallStaticObjectMethod(methodInfo.classID,methodInfo.methodID);
    }
}
void PlatformDelAllNotification()
{
	JniMethodInfo t;
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "delAllNotification",
			"()V")) {
		return;
	}

	t.env->CallStaticVoidMethod(t.classID, t.methodID);
    t.env->DeleteLocalRef(t.classID);
}

int PlatformGetNetType()
{
	JniMethodInfo t;
 	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME, "jniGetNetType", "()I")) {
		return 0;
	}
    
	int value = t.env->CallStaticIntMethod(t.classID, t.methodID);
    t.env->DeleteLocalRef(t.classID);

    return value;
}

std::string PlatformGetRemoteCfg(const char*key)
{
    sprintf(cmd, "Key=%s", key);
    Request result = PlatformMgr::getInstance()->call("Umeng", "GetCfg", cmd);
    std::string value = result.getString("Value");
    CCLog("PlatformGetRemoteCfg: %s:%s", key, value.c_str());

    return value;
}

int PlatformGetRemoteCfgInt(const char* key, int def)
{
    int ret = def;
    
    std::string value = PlatformGetRemoteCfg(key).c_str();
    std::stringstream ss;
    ss << value;
    ss >> ret;
    CCLog("PlatformGetRemoteCfgInt [%s:%s][%d]", key, value.c_str(), ret);
    return ret;
}

void PlatformUMengEvent(const char *id, const char *info,int count)
{
    sprintf(cmd, "Id=%s", id);
    PlatformMgr::getInstance()->call("Umeng", "Event", cmd);
}

void PlatformUMengShare(const char *info, const char* img)
{
    sprintf(cmd, "Desc=%s", info);
    PlatformMgr::getInstance()->call("Umeng", "Share", cmd);
}

void PlatformTdEvent(const char *id, const char *info,int count)
{
	sprintf(cmd, "Id=%s", id);
	platform::PlatformMgr::getInstance()->call("TalkingData", "Event", cmd);
}



std::string PlatformGameCall(std::string cmd)
{
	JniMethodInfo t;
	static std::string  value;
    value = "";
	if (!JniHelper::getStaticMethodInfo(t, PLATFORM_PACKAGE_NAME,
		"jniPlatformGameCall","(Ljava/lang/String;)Ljava/lang/String;")){
		return "";
	}
    
    jstring jcmd = t.env->NewStringUTF(cmd.c_str());
    jstring jvalue = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID, jcmd);
    value = JniHelper::jstring2string(jvalue);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(jvalue);
    t.env->DeleteLocalRef(jcmd);

	return value;
}

float PlatformGetUsedMemMB()
{
    std::string memInfo = PlatformGameCall("Cmd="PLATFORM_GAME_CMD_DEV_MEMSIZE);
    int available = 0;
    int total = 0;
    int cnt = sscanf(memInfo.c_str(), "%dMB/%dMB", &available, &total);
    int used = 0;
    if(cnt == 2)
    {
        used = (total - available);
    }
    CCLog("PlatformGetUsedMemMB %d", used);
    return used;
}


