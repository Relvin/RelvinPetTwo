//
//  platform_91.cpp
//  client
//
//  Created by yuxiao on 14-1-17.
//
//

#include "platform_91.h"
#import <NdComPlatform/NDComPlatform.h>
#include "StartGameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "ShopDataMgr.h"
#include "LoginSystem.h"
#import "NSString+MD5Addition.h"
#import <commoncrypto/CommonDigest.h>
@interface NdComListener : NSObject
+ (NdComListener*)instance;
@property (readonly, getter=isInitFinished) BOOL initFinished;
@end

@implementation NdComListener

+ (NdComListener*)instance
{
    static NdComListener *instance = nil;
    if(instance == nil) {
        instance = [[NdComListener alloc] init];
    }
    return instance;
}

- (id)init
{
    if(self = [super init])
    {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdCPInitDidFinish:)
                                                     name:(NSString *)kNdCPInitDidFinishNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdCPLoginResult:)
                                                     name:(NSString *)kNdCPLoginNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdCPSessionInvalid:)
                                                     name:(NSString *)kNdCPSessionInvalidNotification object:nil];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(NdCPBuyResult:)
                                                     name:(NSString *)kNdCPBuyResultNotification object:nil];
    }
    return self;
}

- (void)NdCPInitDidFinish:(NSNotification *)notify
{
    _initFinished = YES;
    
    Account::shareInstance()->login();
}

- (void)NdCPLoginResult:(NSNotification *)notify
{
    NSDictionary *dict = [notify userInfo];
	BOOL success = [[dict objectForKey:@"result"] boolValue];
    
	if([[NdComPlatform defaultPlatform] isLogined] && success) {
        // send message
        NSString *userId = [[NdComPlatform defaultPlatform] loginUin];
        
        StartGameLayer::GetCurLayer()->login("", "", [userId UTF8String]);
	}
	else
    {
        // logout
        CGameSession::BackToLogin();
    }
}

- (void)NdCPSessionInvalid:(NSNotification *)notify
{
    NSLog(@"session out");
    CGameSession::BackToLogin();
}

- (void)NdCPBuyResult:(NSNotification *)notify
{
    
}
@end


NdComAccount *NdComAccount::shareInstance()
{
    NdComAccount *account = dynamic_cast<NdComAccount *>(Account::shareInstance());
    return account;
}

void NdComAccount::init()
{
    NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
    cfg.appid = 116181;
    cfg.appKey = @"c6c7021f2167eb16ab98e8f256069ea01f5d311613ca5f52";
    cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_NORMAL;
    cfg.orientation = UIDeviceOrientationPortrait;
    cfg.autoRotate = YES;
    [[NdComPlatform defaultPlatform] NdInit:cfg];
    
#ifndef RELEASE
	[[NdComPlatform defaultPlatform] NdSetDebugMode:0];
#endif
    
    [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtTopLeft];
    
    [NdComListener instance];
}

void NdComAccount::login()
{
    if (![[NdComListener instance] isInitFinished])
        return;
    
    if ([[NdComPlatform defaultPlatform] isLogined]) {
        NSString *userId = [[NdComPlatform defaultPlatform] loginUin];
        StartGameLayer::GetCurLayer()->login("", "", [userId UTF8String]);
    }
    else {
        [[NdComPlatform defaultPlatform] NdLogin:0];
    }
}

void NdComAccount::logout()
{
    if ([[NdComPlatform defaultPlatform] isLogined]) {
		[[NdComPlatform defaultPlatform] NdLogout:0];
	}
}

void NdComAccount::center()
{
	[[NdComPlatform defaultPlatform] NdEnterPlatform:0];
}

void NdComAccount::feedback()
{
	[[NdComPlatform defaultPlatform] NdUserFeedBack];
}

void NdComAccount::bbs()
{
    [[NdComPlatform defaultPlatform] NdEnterAppBBS:0];
}

void NdComAccount::switchAccount()
{
    if (![[NdComListener instance] isInitFinished])
        return;
    
    [[NdComPlatform defaultPlatform] NdSwitchAccount];
}

void NdComAccount::buy(uint32 good_id)
{
    if (![[NdComPlatform defaultPlatform] isLogined]) {
		[[NdComPlatform defaultPlatform] NdLogin:0];
		return;
	}

//    }
    
    
    CRole *prole = CGameSession::GetRole();
    
    STORE_PAY_LIST_INFO* pPayItemInfo = CShopDataMgr::Get()->GetStorePayGoodsInfoById(good_id);
    if (!pPayItemInfo) {
        return;
    }
    int price = pPayItemInfo->dwPrice/100;
    NSString *billNo = [NSString stringWithUTF8String:CShopDataMgr::Get()->GetOrderSerialByGoodsId(good_id)];
    
    
    NSDate* dat = [NSDate dateWithTimeIntervalSinceNow:0];
    NSTimeInterval a=[dat timeIntervalSince1970];
    //订单号必须唯一！
    NSString *str = [NSString stringWithFormat:@"%s%.2f", [billNo UTF8String], a];
    
    
    NSString *title = [NSString stringWithUTF8String:pPayItemInfo->strSecondLine.c_str()] ;
    NSString *roleId = [NSString stringWithFormat:@"%d",prole->GetdwAccountId()];
    
    int zoneId = LoginSystem::Get()->getAreaId();
    
    NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
    buyInfo.cooOrderSerial = [[str stringFromMD5] substringToIndex:32];
    
    //你的产品id
    buyInfo.productId = [NSString stringWithFormat:@"%d", good_id];
    buyInfo.productName = [NSString stringWithUTF8String:[title UTF8String]];
    buyInfo.productPrice = price;
    buyInfo.productOrignalPrice = price; //原价不能为0！
    buyInfo.productCount = 1;
    // description
    buyInfo.payDescription = [NSString stringWithUTF8String:[billNo UTF8String]];
    
    int res = [[NdComPlatform defaultPlatform] NdUniPayAsyn:buyInfo];
    if (res < 0) {
        NSLog(@"参数错误");
        //输入参数有错！无法提交购买请求
    }
    else {
    }
}




void NdComAccount::applicationWillEnterForeground(void *iosUIApplication)
{
    [[NdComPlatform defaultPlatform] NdPause];
}
