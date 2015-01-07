//
//  UMAnalytics.h
//  dota
//
//  Created by 黄 义 on 13-12-26.
//  Copyright (c) 2013年 D9Dark. All rights reserved.
//

#ifndef ANDROID_ANALYTICS_H
#define ANDROID_ANALYTICS_H


#include "platform_game.h"



class AndroidAnalytics
{
public:
	static AndroidAnalytics* getInstance();

    virtual bool Init(const std::string& app_id, const std::string& channel_id){return true;}
	
    void 	SendEvent( const std::string& event_id,const std::string& value ) ;    
	virtual void StartLevel(const std::string& level_id);    
	virtual void FinishLevel(const std::string& level_id);    
	virtual void FailLevel(const std::string& level_id,const std::string& info);
	virtual const std::string GetOnlineConifgWithKey(const std::string& key, const std::string& default_value);

	// Talking data
    virtual void  ReportPlayerInfo(const char* roleId, int roleLv, const char* extra);
protected:
	// Talking data
    virtual void  ReportMission(const char* missionId, int status, const char* failReason);
	static AndroidAnalytics* mInstance;
};


#endif
