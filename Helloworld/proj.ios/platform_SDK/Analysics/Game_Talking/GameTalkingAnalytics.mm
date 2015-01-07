//
//  GameTalkingAnalytics.cpp
//  dota
//
//  Created by panhong on 14-8-18.
//  Copyright (c) 2014年 D9Dark. All rights reserved.
//

#include "GameTalkingAnalytics.h"
#import "TalkingDataGA.h"
#include "Support.h"

bool	GameTalkingAnalytics::InitAnalyticsSDK()
{
    [TalkingDataGA onStart:[NSString stringWithFormat:@"%s", Support::sharedInstance()->talkingData()] withChannelId:[NSString stringWithFormat:@"%d", Support::sharedInstance()->appChannel()]];
#ifdef DEBUG
    [TalkingDataGA setVerboseLogDisabled];
#endif
    
    return YES;
}

void	GameTalkingAnalytics::CleanupAnalyticsSDK()
{

}

void 	GameTalkingAnalytics::SendEvent( const char * eventID, const char * accountID )
{
    NSMutableDictionary* pDic = [[NSMutableDictionary alloc] init];
    [pDic setObject:[NSString stringWithFormat:@"%s", accountID] forKey:@"user_id"];
    [TalkingDataGA onEvent:[NSString stringWithUTF8String: eventID] eventData:pDic];
    [pDic release];
}

void 	GameTalkingAnalytics::SendEvent( const char * eventID, const char * accountID, const char * edata )
{
    NSMutableDictionary* pDic = [[NSMutableDictionary alloc] init];
    [pDic setObject:[NSString stringWithFormat:@"%s", accountID] forKey:@"user_id"];
    [pDic setObject:[NSString stringWithFormat:@"%s", edata] forKey:@"good_id"];
    [TalkingDataGA onEvent:[NSString stringWithUTF8String: eventID] eventData:pDic];
    [pDic release];
}



////////////////  以下函数暂不使用
const char *	GameTalkingAnalytics::GetConfigParams( const char *key ){return "";}



const char* 	GameTalkingAnalytics::GetAnalyticsAppKey(){// 必须返回utf8编码的字符串
    return "";}
////////////////////



/*    任务分析*/

void  GameTalkingAnalytics::ReportMission(const char* missionId, int status, const char* failReason)
{
    if (status == 0) {
        [TDGAMission onBegin:[NSString stringWithUTF8String: missionId]];
    }else if (status == 1)
    {
        [TDGAMission onCompleted:[NSString stringWithUTF8String: missionId]];
    }else if (status == -1)
    {
        [TDGAMission onFailed:[NSString stringWithUTF8String: missionId] failedCause:[NSString stringWithUTF8String: failReason]];
    }
}



//  等级分析
void GameTalkingAnalytics::ReportPlayerInfo(const char* roleId, int roleLv, const char* gameServer, int _type)
{
    TDGAAccount *acount = [TDGAAccount setAccount:[NSString stringWithUTF8String: roleId]];
    [acount setLevel:roleLv];
    [acount setGameServer:[NSString stringWithUTF8String: gameServer]];
    [acount setAccountType:(TDGAAccountType)_type];
}


// 购买商品，goodsName ：商品名字，num：数量 price：单价
void GameTalkingAnalytics::OnPurchase(const char* goodsName, int num, int price)
{
    [TDGAItem onPurchase: [NSString stringWithUTF8String: goodsName] itemNumber:num priceInVirtualCurrency:price];
}

// 使用物品  goodsName ：商品名字，num：数量
void GameTalkingAnalytics::useGoods(const char* goodsName, int num)
{
    [TDGAItem onUse:[NSString stringWithUTF8String: goodsName] itemNumber:num];
}


// orderId:订单ID，iapId:充值包ID currencyAmount:现金金额  currencyType:货币类型  virtualCurrencyAmount：虚拟币金额  paymentType：支付的途径
void GameTalkingAnalytics::onChargeRequest(const char* orderId,const char* iapId,int currencyAmount,const char* currencyType,int virtualCurrencyAmount,const char* paymentType)
{
    [TDGAVirtualCurrency onChargeRequst:[NSString stringWithUTF8String: orderId] iapId:[NSString stringWithUTF8String: iapId] currencyAmount:currencyAmount currencyType:[NSString stringWithUTF8String: currencyType] virtualCurrencyAmount:virtualCurrencyAmount paymentType: [NSString stringWithUTF8String: paymentType]];
}

 void  GameTalkingAnalytics::onChargeSuccess(const char* orderId)
{
    [TDGAVirtualCurrency onChargeSuccess: [NSString stringWithUTF8String: orderId]];
}
//  自定义事件
/*
void GameTalkingAnalytics::sendSelfEvent(std::map<std::string,std::string> maps,const char * eventId)
{    NSMutableDictionary *dict = [[[NSMutableDictionary alloc] init] autorelease];
    
    std::map<std::string ,std::string>::iterator iter;
    for (iter = maps.begin(); iter != maps.end(); iter++) {
        [dict setValue:[NSString stringWithFormat:@"%s", iter->first.c_str()] forKey:[NSString stringWithFormat:@"%s", iter->
second.c_str()]];
    }
    [TalkingDataGA onEvent:[NSString stringWithUTF8String: eventId] eventData:dict];
}
*/




