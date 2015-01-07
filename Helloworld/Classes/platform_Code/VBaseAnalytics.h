//
//  VBaseAnalytics.h
//  dota
//
//  Created by 黄 义 on 13-12-26.
//  Copyright (c) 2013年 D9Dark. All rights reserved.
//

#ifndef dota_VBaseAnalytics_h
#define dota_VBaseAnalytics_h
#include <map>
#include <string>
class VSocialDelegate;

class VDataAnalytics
{
    
public:
    VDataAnalytics(){};
    virtual ~VDataAnalytics(){};
    
    virtual bool	InitAnalyticsSDK() = 0;
    virtual void	CleanupAnalyticsSDK() = 0;
    
    virtual void 	SendEvent( const char * eventID, const char * accountID ) = 0;
    virtual void 	SendEvent( const char * eventID, const char * accountID, const char * edata ) = 0;
    
    virtual const char *	GetConfigParams( const char *key ) = 0;
    
    
    //sxp 14-05-12 社会化平台需要调用的接口
    /**
     *  msg 分享文字
     *  iconPath可以为空
     */

	/**
        汇报任务信息
        status: 0 任务开始; 1 任务完成; -1 任务失败;
        failReason: status -1时传失败原因; 其他传NULL
    */
    virtual void  ReportMission(const char* missionId, int status, const char* failReason){}

	/**
		汇报玩家信息(选好角色进入游戏进行调用)
		roleId: 玩家唯一角色id(建议拼上服务器)
		roleLv: 玩家等级
		extra: 其他信息, "Param1=value1|Param2=value2|...."
    */
    virtual void  ReportPlayerInfo(const char* roleId, int roleLv, const char* extra){}
    
protected:
    virtual const char* 	GetAnalyticsAppKey() = 0;		// 必须返回utf8编码的字符串
    
    const char *	GetOnlineName()
    {
        
#if DATA_ABALY_ONLINE_TYPE == 958
        return "AISgame";
#endif
        return "";
    };
    
};




#endif
