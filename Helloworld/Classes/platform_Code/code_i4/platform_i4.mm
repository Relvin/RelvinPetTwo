//
//  platform_i4.cpp
//  client
//
//  Created by CX_ZSY on 14-7-7.
//
//

#include "platform_i4.h"
#import  "AsInfoKit.h"
#include "AsPlatformSDK.h"
#include "StartGameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "ShopDataMgr.h"
#include "LoginSystem.h"

@interface i4Listener : UIViewController<AsPlatformSDKDelegate>
+ (i4Listener*)instance;
@end


@implementation i4Listener

+ (i4Listener*)instance
{
    static i4Listener *instance = nil;
    if(instance == nil) {
        instance = [[i4Listener alloc] init];
    }
    return instance;
}

//-SDK 1.4.1 - 新增的关闭用户中心回调
- (void)asClosedCenterViewCallBack
{
    NSLog(@"SDK center view Closed");
}


/**
 * @brief   余额大于所购买道具
 * @param   INPUT   paramAsPayResultCode       接口返回的结果编码
 * @return  无返回
 */
- (void)asPayResultCallBack:(AsPayResultCode)paramPPPayResultCode
{
    if(paramPPPayResultCode == AsPayResultCodeSucceed){
        //购买成功发放道具
    }else{
        
    }
}
- (void)asAlixPayResultCallBack:(int)statusCode
{}

//-SDK 1.5.2 - 新增的银联sdk支付的结果回调
/**
 * @brief   银联sdk的支付结果回调
 * @param   INPUT   result       接口返回的结果
 * success  支付成功
 * fail     支付失败
 * cancel   用户取消支付。
 * @return  无返回
 */
- (void)asUPPayPluginResultCallBack:(NSString *)result
{}

/**
 * @brief   验证更新成功后
 * @noti    分别在非强制更新点击取消更新和暂无更新时触发回调用于通知弹出登录界面
 * @return  无返回
 */
- (void)asVerifyingUpdatePassCallBack
{
    [[AsPlatformSDK sharedInstance] showLogin];
}

// 登录成功回调
- (void)asLoginCallBack:(NSString *)paramToken
{
    NSLog(@"userId: %llu", [[AsPlatformSDK sharedInstance] currentUserId]);
    NSLog(@"userName: %@", [[AsPlatformSDK sharedInstance] currentUserName]);
    
    int _id = [[AsPlatformSDK sharedInstance] currentUserId];
    NSString *userId = [ NSString stringWithFormat:@"%d",_id ];
    StartGameLayer::GetCurLayer()->login("", "", [userId UTF8String]);
}


// 关闭Web页面后的回调
- (void)asCloseWebViewCallBack:(AsWebViewCode)paramWebViewCode
{
    NSLog(@"SDK Web View Closed");
}


// 关闭SDK客户端页面后的回调
- (void)asClosePageViewCallBack:(AsPageCode)paramPPPageCode
{
    NSLog(@"SDK Page View Closed");
}


// 注销通知处理
- (void)asLogOffCallBack
{
    NSLog(@"Logout");
    CGameSession::BackToLogin();
}

@end


void i4Account::init()
{
    [[AsInfoKit sharedInstance] setAppId:278];
    [[AsInfoKit sharedInstance] setAppKey:@"cc2bd8b931b44d91a75aa2b068e2240d"];
    [[AsInfoKit sharedInstance] setCloseRecharge:NO]; // 如果游戏在开放充值情况下测试请在这⾥里设 置NO
    [[AsInfoKit sharedInstance] setLongComet:YES];
    
#ifdef RELEASE
    [[AsInfoKit sharedInstance] setLogData:NO]; // 游戏正式上线时务必设置为NO
#else
    [[AsInfoKit sharedInstance] setLogData:YES]; // 游戏正式上线时务必设置为NO
#endif
    
    /*
     解决游戏在iOS 5 上 无法显示爱思充值/支付页面、银联支付页面
     若游戏有根视图控制器（RootViewController），则设置为 self.asViewController(为自己的根视图控制器名称)
     若无根视图控制器，则设置为 nil
     */
    //    [[AsInfoKit sharedInstance] setRootViewController:self.asViewController];
    
    [[AsPlatformSDK sharedInstance] setDelegate:[i4Listener instance]];
    [[AsInfoKit sharedInstance] setOrientationOfGame:UIInterfaceOrientationMaskPortrait|UIInterfaceOrientationMaskPortraitUpsideDown];
    [[AsPlatformSDK sharedInstance] checkGameUpdate];
    
}

void i4Account::login()
{
    
    [[AsPlatformSDK sharedInstance] showLogin];
}

void i4Account::logout()
{
    [[AsPlatformSDK sharedInstance] asLogout];
    [[[AsPlatformSDK sharedInstance] delegate] asLogOffCallBack];
    [[AsPlatformSDK sharedInstance] showLogin];
}

void i4Account::center()
{
    [[AsPlatformSDK sharedInstance] showCenter];
}

void i4Account::buy(uint32 good_id)
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
    
    [[AsPlatformSDK sharedInstance] exchangeGoods:price
                                           BillNo:billNo
                                        BillTitle:title
                                           RoleId:roleId
                                           ZoneId:zoneId];
}

bool i4Account::applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString)
{
    NSString *sourceApplication = (NSString *)iosNSString;
    NSURL *url = (NSURL *)iosNSURL;
    if ([sourceApplication isEqualToString:@"com.alipay.iphoneclient"])
    {
        [[AsInfoKit sharedInstance] alixPayResult:url];
    }
    else if ([sourceApplication
              isEqualToString:@"com.alipay.safepayclient"])
    {
        [[AsInfoKit sharedInstance] alixPayResult:url];
    }
    else if ([sourceApplication isEqualToString:@"com.tencent.xin"])
    {
        [[AsInfoKit sharedInstance] weChatPayResult:url];
    }
    return false;
}
void i4Account::setViewController(void *cont)
{
    UIViewController *controller = (UIViewController *)cont;
    [[AsInfoKit sharedInstance] setRootViewController:controller];
}