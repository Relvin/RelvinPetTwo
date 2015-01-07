//
//  platform_pp.mm
//  client
//
//  Created by YQ on 13-3-5.
//
//

#include "platform_pp.h"
#import <PPAppPlatformKit/PPAppPlatformKit.h>
//#include "GameSession.h"
#import "ASIHTTPRequest.h"
#import "JSONKit.h"
#include "StartGameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "ShopDataMgr.h"
#include "LoginSystem.h"
#include "support.h"
static std::string s_userid;
static std::string s_username;

@interface PPDelegate : NSObject <PPAppPlatformKitDelegate>
+ (PPDelegate*)instance;
@end

@implementation PPDelegate
+ (PPDelegate*)instance
{
    static PPDelegate *instance = nil;
    if(instance == nil) {
        instance = [[PPDelegate alloc] init];
    }
    return instance;
}

- (void)OnReopenLogin:(NSTimer*)timer
{
    Account::shareInstance()->login();
}

- (void)ppPayResultCallBack:(PPPayResultCode)paramPPPayResultCode
{
    if(paramPPPayResultCode == PPPayResultCodeSucceed){
        //购买成功发放道具
    }else{
        
    }
}

- (void)ppVerifyingUpdatePassCallBack
{
    Account::shareInstance()->login();
}

- (void)ppLoginStrCallBack:(NSString *)paramStrToKenKey
{
    if([[PPAppPlatformKit sharedInstance] loginState] == 1) {
        NSURL *url = [NSURL URLWithString:@"http://passport_i.25pp.com:8080/index?tunnel-command=2852126756"];
        
        ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
        [request appendPostData:[paramStrToKenKey dataUsingEncoding:NSUTF8StringEncoding]];
        [request startSynchronous];
        
        if (![request error]) {
            NSString *response = [[[NSString alloc] initWithData:[request responseData] encoding:NSUTF8StringEncoding] autorelease];
            NSDictionary *responseJson = [[NSString stringWithFormat:@"{%@}", response] objectFromJSONString];
            
            NSNumber *status = [responseJson objectForKey:@"status"];
            if([status intValue] == 0) {
                NSString *userId = [NSString stringWithFormat:@"%@",[responseJson objectForKey:@"userid"]];
                s_username = [[responseJson objectForKey:@"username"] UTF8String];
                
                
               StartGameLayer::GetCurLayer()->login("", "", [userId UTF8String]);
                
                [[PPAppPlatformKit sharedInstance] getUserInfoSecurity];
            }
        }
    }
}

- (void)ppCloseWebViewCallBack:(PPWebViewCode)paramPPWebViewCode
{
}

- (void)ppClosePageViewCallBack:(PPPageCode)paramPPPageCode
{
    if ([[PPAppPlatformKit sharedInstance] loginState] == 0) {
        NSTimer* timer = [NSTimer timerWithTimeInterval:1.0f target:self selector:@selector(OnReopenLogin:) userInfo:nil repeats:NO];
        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    }
}

- (void)ppLogOffCallBack
{
    CGameSession::BackToLogin();
}
@end



void PPAccount::init()
{
    [[PPAppPlatformKit sharedInstance] setAppId:4765 AppKey:@"3e31041a6133b3713a7350b1739dc148"];
    [[PPAppPlatformKit sharedInstance] setRechargeAmount:10];
    [[PPAppPlatformKit sharedInstance] setIsLongComet:YES];
    [[PPAppPlatformKit sharedInstance] setIsLogOutPushLoginView:NO];
    [[PPAppPlatformKit sharedInstance] setIsOpenRecharge:YES];
    [[PPAppPlatformKit sharedInstance] setCloseRechargeAlertMessage:@"请在游戏商城内充值"];
    [[PPAppPlatformKit sharedInstance] setDelegate:[PPDelegate instance]];
    
#ifdef RELEASE
    [[PPAppPlatformKit sharedInstance] setIsNSlogData:NO];
#else
    [[PPAppPlatformKit sharedInstance] setIsNSlogData:YES];
#endif
    
    [PPUIKit sharedInstance];
    [PPUIKit setIsDeviceOrientationLandscapeLeft:YES];
    [PPUIKit setIsDeviceOrientationLandscapeRight:YES];
    [PPUIKit setIsDeviceOrientationPortrait:YES];
    [PPUIKit setIsDeviceOrientationPortraitUpsideDown:YES];
}

void PPAccount::login()
{
    [[PPAppPlatformKit sharedInstance] showLogin];
}

void PPAccount::center()
{
    [[PPAppPlatformKit sharedInstance] showCenter];
}

void PPAccount::logout()
{
    [[PPAppPlatformKit sharedInstance] PPlogout];
}

void PPAccount::buy(uint32 good_id )
{
    CRole *prole = CGameSession::GetRole();
    
    STORE_PAY_LIST_INFO* pPayItemInfo = CShopDataMgr::Get()->GetStorePayGoodsInfoById(good_id);
    if (!pPayItemInfo) {
        return;
    }
    int price = pPayItemInfo->dwPrice/100;
    NSString *billNo = [NSString stringWithUTF8String:CShopDataMgr::Get()->GetOrderSerialByGoodsId(good_id)];
    
    NSString *title = [NSString stringWithUTF8String:pPayItemInfo->strSecondLine.c_str()] ;
    NSString *roleId = [NSString stringWithFormat:@"%d",prole->GetdwAccountId()];
    
    int zoneId = LoginSystem::Get()->getAreaId();
    
        [[PPAppPlatformKit sharedInstance] exchangeGoods:price
                                                  BillNo:billNo
                                               BillTitle:title
                                                  RoleId:roleId
                                                  ZoneId:zoneId];
}

bool PPAccount::applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString)
{
    NSURL *url = (NSURL*)iosNSURL;
    
    [[PPAppPlatformKit sharedInstance] alixPayResult:url];
    
    return true;
}
