//
//  D9DealBackGroundManager.h
//  PingMuUpSide
//
//  Created by panhong on 14-5-23.
//  Copyright (c) 2014年 panhong. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum  _D9STatictalEvent     // 更新类型
{
	D9STatictalEventStartUp = 100,			/**<每次启动自动汇报*/
	D9STatictalEventInstall,                // 升级版本或者刚刚安装时候汇报
    D9STatictalEventRoleInfo,              // 角色信息统计
    D9STatictalEventPay,                   // 支付统计
    D9STatictalEventSelfDefine,            // 自定义统计类型
} D9STatictalEvent;

// 使用block回调
typedef void (^OneLineCallBack)(id dict);
@interface D9DealBackGroundManager : NSObject

+ (id)sharedController;


- (BOOL)isNeedToUpdata:(id)target selector:(SEL)selector;


//  统计数据
/*
     若事件类型为 D9STatictalEventRoleInfo  必须传入的参数包括 serverid（必须数字）,roleid（必须数字）,name,level（必须数字）,exp（必须数字）,gold  （必须数字）
     若事件类型为 D9STatictalEventPay       必须传入的参数包括 serverid（必须数字）,roleid（必须数字）,price(float)（必须数字）,productid
 
     若事件类型为 D9STatictalEventSelfDefine  必须传入的参数为 st1,st2,int1（必须数字）至少传入一个
 */
- (void)StatisticalData:(NSMutableDictionary *)sendDict
             eventStyle:(D9STatictalEvent)eventStyle;

// 在线参数 key为请求参数的关键字 callback为请求回调
- (void)onlineParameter:(NSString *)key
               callback:(OneLineCallBack)callback;
@end
