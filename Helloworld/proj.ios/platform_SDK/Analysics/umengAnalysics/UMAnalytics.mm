//
//  UMAnalytics.mm
//  dota
//
//  Created by 黄 义 on 13-12-26.
//  Copyright (c) 2013年 D9Dark. All rights reserved.
//

#include "UMAnalytics.h"
#include "MobClick.h"
#include "UMSocial.h"
#if DATA_ABALY_ONLINE_TYPE == 957
#include <FacebookSDK/FacebookSDK.h>
#endif
//#include <Accounts/Accounts.h>
//#if DATA_ABALY_ONLINE_TYPE == 957
//#include "UMSocialFacebookHandler.h"
//#endif

#include "Support.h"

//实现一个delegate

// delegate impl
@interface SocialDelegate : NSObject<UMSocialUIDelegate>
{
    
}
@end

@implementation SocialDelegate

-(void)sendSocialEvent :(NSString*)msg icon:(NSString*)icon
{

}

@end

class VSocialDelegate
{
public:
    VSocialDelegate():_sdlt(NULL)
    {
        
    };
    ~VSocialDelegate()
    {
        if(_sdlt != NULL)
        {                               //释放
            [_sdlt release];
            _sdlt = NULL;
        }
    };
    
    void initDelegate(){
        _sdlt = [SocialDelegate alloc];
    }
    
public:
    SocialDelegate* _sdlt;
};

bool	UMAnalytics::InitAnalyticsSDK()
{
//    this->_delegate = NULL;
    [MobClick startWithAppkey:[NSString stringWithCString: GetAnalyticsAppKey() encoding: NSUTF8StringEncoding] reportPolicy: REALTIME channelId: [NSString stringWithFormat:@"%d", Support::sharedInstance()->appChannel()] ];
    
    //设置umappkey
    [UMSocialData setAppKey:[NSString stringWithCString: GetAnalyticsAppKey() encoding: NSUTF8StringEncoding]];
    //设置um横屏弹出
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskLandscape];
    
//    this->_delegate = new VSocialDelegate();
//    this->_delegate->initDelegate();
    
    [MobClick updateOnlineConfig];
#ifndef NDEBUG
//    [MobClick setLogEnabled:YES];
//    [MobClick checkUpdate];
//    [UMSocialData openLog:YES];
#endif
    return true;
}

void UMAnalytics::CleanupAnalyticsSDK()
{
//    if(this->_delegate != NULL){
//        delete this->_delegate;
//        this->_delegate = NULL;
//    }
}

void UMAnalytics::SendEvent( const char * eventID, const char * accountID )
{
    [MobClick event:[NSString stringWithUTF8String: eventID] ];
}

void UMAnalytics::SendEvent( const char * eventID, const char * accountID, const char * edata )
{
    [MobClick event:[NSString stringWithUTF8String: eventID] label:[NSString stringWithUTF8String: edata] ];
}


const char * UMAnalytics::GetConfigParams( const char *key )
{
    [MobClick updateOnlineConfig];
    NSString *ck = [NSString stringWithCString: key encoding: NSUTF8StringEncoding];
    NSString * retv = [MobClick getConfigParams: ck];
    return [retv UTF8String];
}

void UMAnalytics::updateUmengOnlineParams()
{
    [MobClick updateOnlineConfig];
}

const char* 	UMAnalytics::GetAnalyticsAppKey()
{
    // 必须返回utf8编码的字符串
    return Support::sharedInstance()->umengKey();
}

void UMAnalytics::SendBeginPageView(const char *pageName) {
    NSString* strName = [NSString stringWithUTF8String:pageName];
    [MobClick beginLogPageView:strName];
}

void UMAnalytics::SendEndPageView(const char *pageName) {
    NSString* strName = [NSString stringWithUTF8String:pageName];
    [MobClick endLogPageView:strName];
}

int UMAnalytics::getUmengKey(const char *key) {
    NSString* cheatString = [MobClick getConfigParams:[NSString stringWithFormat:@"%s", key]];
    if ([cheatString isEqual:@"true"]) {
        return 1;
    }
    return 0;
}

/*
#ifdef DATA_ABALY_TKD_TYPE  // 使用gameTalking 统计
//任务分析
void  UMAnalytics::ReportMission(const char* missionId, int status, const char* failReason)
{}

// 等级账号分析
// accountId ： 账号id  accountName：账号名  gameServer：区服  level：等级  性别（0未知，1男，2女）age：年龄 （未知传0）
void  UMAnalytics::ReportPlayerInfo(const char* roleId, int roleLv, const char* extra){}

// 自定义事件  eventId自定义事件id   map中为事件的键--值，例如 eventId= “dead”，死亡的场景 值："沼泽地阿卡村"，健：@"map"  死亡时间 值：18：22 健：time
//void UMAnalytics::sendSelfEvent(std::map<std::string,std::string> maps,const char * eventId){}

#endif

*/