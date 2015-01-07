

#include "platform_android.h"

#include "AndroidAnalytics.h"

#include "cocos2d.h"

USING_NS_CC;

AndroidAnalytics* AndroidAnalytics::mInstance = NULL;

static char params[1024]={0};

AndroidAnalytics* AndroidAnalytics::getInstance()
{
	if(mInstance == NULL)
	{
		mInstance = new AndroidAnalytics();
	}
	return mInstance;
}
	

void AndroidAnalytics::SendEvent( const std::string& event_id,const std::string& value )
{
    PlatformUMengEvent(event_id.c_str(), "", -1);
    PlatformTdEvent(event_id.c_str(), "", -1);
}

void AndroidAnalytics::StartLevel(const std::string& level_id)
{
    ReportMission(level_id.c_str(), 0, NULL);
}


void AndroidAnalytics::FinishLevel(const std::string& level_id)
{
    ReportMission(level_id.c_str(), 1, NULL);
}


void AndroidAnalytics::FailLevel(const std::string& level_id,const std::string& info)
{
    ReportMission(level_id.c_str(), -1, info.c_str());
}

const std::string AndroidAnalytics::GetOnlineConifgWithKey(const std::string& key, const std::string& default_value)
{
	static std::string param = "";
	param = PlatformGetRemoteCfg(key.c_str());
    if(param.length() <= 0)
    {
        param = default_value;
    }
	CCLog("AndroidAnalytics::GetConfigParams [%s]=[%s]", key.c_str(), param.c_str());
    return param;
}


void AndroidAnalytics::ReportMission(const char* missionId, int status, const char* failReason)
{
	sprintf(params, "Id=%s|State=%s|FailReason=%s", 
        missionId == NULL ? "" : missionId, 
        status == 0 ? "Begin" : status == 1 ? "Completed" : "Failed",
        failReason == NULL ? "" : failReason);

	platform::PlatformMgr::getInstance()->call("TalkingData", "Mission", params);
	platform::PlatformMgr::getInstance()->call("Umeng", "Mission", params);
}

void AndroidAnalytics::ReportPlayerInfo(const char* roleId, int roleLv, const char* extra)
{
	sprintf(params, "Account=%s|RoleLv=%d|%s", 
        roleId == NULL ? "" : roleId, roleLv,
        extra == NULL ? "" : extra);

	platform::PlatformMgr::getInstance()->call("TalkingData", "SetUserInfo", params);
}


