//
//  UMAnalytics.h
//  dota
//
//  Created by 黄 义 on 13-12-26.
//  Copyright (c) 2013年 D9Dark. All rights reserved.
//

#ifndef dota_UMAnalytics_h
#define dota_UMAnalytics_h

// Juniechu:友盟和talkingData差距太大，不使用基类统一
//#include "VBaseAnalytics.h"


class UMAnalytics// : public VDataAnalytics
{
    
    
public:
    bool	InitAnalyticsSDK() ;
    void	CleanupAnalyticsSDK() ;
    
    /** 自定义事件,数量统计.
     使用前，请先到友盟App管理后台的设置->编辑自定义事件 中添加相应的事件ID，然后在工程中传入相应的事件ID
     
     @param  eventId 网站上注册的事件Id.
     @param  edata 分类标签。不同的标签会分别进行统计，方便同一事件的不同标签的对比,为nil或空字符串时后台会生成和eventId同名的标签.
     @return void.
     */
    void 	SendEvent( const char * eventID, const char * accountID ) ;
    void 	SendEvent( const char * eventID, const char * accountID, const char * edata ) ;
    
    //  获取友盟在线参数
    const char *	GetConfigParams( const char *key ) ;
    
    /*!
     页面统计
     
     @param pageName 页面名称
     */
    void    SendBeginPageView(const char* pageName);
    void    SendEndPageView(const char* pageName);
    
    void    DidBecomeActive();
    
    void    updateUmengOnlineParams();
    
    /*!
     @brief 友盟的值
     */
    int getUmengKey(const char* key);
    
    /*
#ifdef DATA_ABALY_TKD_TYPE  // 使用gameTalking 统计
    //任务分析
    void  ReportMission(const char* missionId, int status, const char* failReason);
    
    // 等级账号分析
    // accountId ： 账号id  accountName：账号名  gameServer：区服  level：等级  性别（0未知，1男，2女）age：年龄 （未知传0）
    void  ReportPlayerInfo(const char* roleId, int roleLv, const char* extra);
    
    // 自定义事件  eventId自定义事件id   map中为事件的键--值，例如 eventId= “dead”，死亡的场景 值："沼泽地阿卡村"，健：@"map"  死亡时间 值：18：22 健：time
//    void sendSelfEvent(std::map<std::string,std::string> maps,const char * eventId);
    
#endif
*/
public:
//    VSocialDelegate * _delegate;
protected:
    const char* 	GetAnalyticsAppKey() ;
    
    
};


#endif
