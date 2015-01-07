//
//  GameTalkingAnalytics.h
//  dota
//
//  Created by panhong on 14-8-18.
//  Copyright (c) 2014年 D9Dark. All rights reserved.
//

#ifndef __dota__GameTalkingAnalytics__
#define __dota__GameTalkingAnalytics__
//#include "VBaseAnalytics.h"


//注意 ，要想统计数据，必须先调用 void  ReportPlayerInfo(const char* roleId, int roleLv, const char* gameServer)  函数
class GameTalkingAnalytics
{
public:
    bool	InitAnalyticsSDK() ;
    void	CleanupAnalyticsSDK() ;
    
    
    /*  只传事件id*/  // 自定义事件
    void 	SendEvent( const char * eventID, const char * accountID ) ;
    void 	SendEvent( const char * eventID, const char * accountID, const char * edata ) ;

    void sendSocialEvent(const char * msg, const char* iconPath);
    

    const char *	GetConfigParams( const char *key ) ;
    
    
    //任务分析
    void  ReportMission(const char* missionId, int status, const char* failReason);
    
    // 等级账号分析
    // accountId ： 账号id  gameServer：区服  level：等级
    void  ReportPlayerInfo(const char* roleId, int roleLv, const char* gameServer, int _type);
    

    // 购买商品，goodsName ：商品名字，num：数量 price：单价
    void OnPurchase(const char* goodsName, int num, int price);
    
    // 使用物品  goodsName ：商品名字，num：数量
    void useGoods(const char* goodsName, int num);
    
    //  开始充值
    // orderId:订单ID，iapId:充值包ID currencyAmount:现金金额  currencyType:货币类型  virtualCurrencyAmount：虚拟币金额  paymentType：支付的途径
    void onChargeRequest(const char* orderId,const char* iapId,int currencyAmount,const char* currencyType,int virtualCurrencyAmount,const char* paymentType);
    
    //充值成功
    //orderId:订单id
    void  onChargeSuccess(const char* orderId);
    
    // 自定义事件  eventId自定义事件id   map中为事件的键--值，例如 eventId= “dead”，死亡的场景 值："沼泽地阿卡村"，健：@"map"  死亡时间 值：18：22 健：time
    //    void sendSelfEvent(std::map<std::string,std::string> maps,const char * eventId);
protected:
    const char* 	GetAnalyticsAppKey() ;
};

#endif /* defined(__dota__GameTalkingAnalytics__) */
