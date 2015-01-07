//
//  platform_pp.mm
//  client
//
//  Created by YQ on 13-3-5.
//
//

#include "platform_d9.h"
#include "StartGameLayer.h"
#include "GameSession.h"
#include "Role.h"
#include "ShopDataMgr.h"
#include "LoginSystem.h"
#include "support.h"
#import <DemoLibrary/D9SDKMainController.h>
#import <DemoLibrary/D9DealBackGroundManager.h>

static D9SDKMainController *s_d9SDK = NULL;


@interface D9StudioDelegate : NSObject <D9ViewDelegate>
+(D9SDKMainController*)instance;
@end

@implementation D9StudioDelegate
+(D9StudioDelegate*)instance
{
    static D9StudioDelegate *instance = nil;
    if(instance == nil) {
        instance = [[D9StudioDelegate alloc] init];
    }
    return instance;
}



//登陆成功回调
- (void)loginSuccess:(NSMutableDictionary *)result
{
    [[D9SDKMainController sharedController] showAssistiveView:D9ToolBarAtTopRight];
    NSLog(@"Dependent App: D9StudioSDK Logged in.");
    
    NSString *userID = [result objectForKey:@"userid"];

    StartGameLayer::GetCurLayer()->login("", "", [userID UTF8String]);
}

//注册成功回调
-(void)registerSuccess:(NSMutableDictionary *)result
{
    [[D9SDKMainController sharedController] showToolBar:YES];
}

// 改密成功回调
- (void)changePassWordSuccess:(NSMutableDictionary *)result
{
    CGameSession::BackToLogin();
}


//快速登回调
- (void)quicklyLogin:(NSString *)userId
{
    if (userId) {
        StartGameLayer::GetCurLayer()->login("", "", [userId UTF8String]);
    }
    
}
// 关闭个人中心回调
- (void)d9CloseView:(D9CloseView)selfCenterView
{
    [[D9SDKMainController sharedController] showToolBar:YES];
}

// 切换账号回调
- (void)switchCountback{
    CGameSession::BackToLogin();
}

- (void)loginIn
{
    [s_d9SDK showLoginView];
}
@end

void D9Account ::switchAccount()
{
    if ([s_d9SDK isHadLogin]) {
        [s_d9SDK switchCount];
    }
}

void D9Account::init()
{
    if(s_d9SDK == NULL) {
        s_d9SDK  = [[D9SDKMainController sharedController] initWithAppid:@"100009" platformID:[NSString stringWithFormat:@"%d",Support::sharedInstance()->appChannel()]appKey:@"1acdda4ba094e8117f7c40db0711d910" updataLevel:D9Update_Level_Strict];
    }
    
    [s_d9SDK setDelegate:[D9StudioDelegate instance]];
}

void D9Account::login()
{
        [s_d9SDK showLoginView];
        //        NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:[D9StudioDelegate shareInstance] selector:@selector(loginIn) userInfo:nil repeats:NO];
        //        [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

void D9Account::logout()
{
    if ([s_d9SDK isHadLogin]) {
        [s_d9SDK switchCount];
    }
}
void D9Account::center()
{
    if ([s_d9SDK isHadLogin]) {
        [s_d9SDK showsSelfCenter];
    }

}
///  吃出透传字段需要重新填写
void D9Account::buy(uint32 good_id)
{
    if(![s_d9SDK isHadLogin]) {
        return;
    }
    
    CRole *prole = CGameSession::GetRole();
    
    STORE_PAY_LIST_INFO* pPayItemInfo = CShopDataMgr::Get()->GetStorePayGoodsInfoById(good_id);
    if (!pPayItemInfo) {
        return;
    }
    
    int price = pPayItemInfo->dwPrice/100;
    NSString *billNo = [NSString stringWithUTF8String:CShopDataMgr::Get()->GetOrderSerialByGoodsId(good_id)];
    
    NSString *title = [NSString stringWithUTF8String:pPayItemInfo->strSecondLine.c_str()] ;
    NSString *roleId = [NSString stringWithFormat:@"%d",prole->GetdwAccountId()];
    
    /*
     appid     应用id （由服务器分配）
     uid    萌果账号id  (登陆时候反回的uid)
     roleid     游戏内用户id （游戏角色id）
     productId      产品id  (就是在苹果注册产品的时候，使用的id)
     goodid         商品id  (游戏商品id)
     goodscount        商品数量
     goodsName         //商品名字
     currency         //货币类型
     description        //商品描述
     price      //  价格
     */

    [s_d9SDK appStorePay:@"100009"
                     uid:[NSString stringWithUTF8String:prole->GetstrAccount().c_str()]
                  roleId:roleId
               productId:[NSString stringWithUTF8String:pPayItemInfo->strAppleId.c_str()]
                 goodsId:[NSString stringWithFormat:@"%d",good_id]
              goodsCount:@"1"
               goodsName:title
                   price:[NSString stringWithFormat:@"%d",price]
                currency:@"CNY"
             description:billNo];
    
//    1	com.pet2.product.10001
//    2	com.pet2.product.10000
//    4	com.pet2.product.10002
//    5	com.pet2.product.10003
//    6	com.pet2.product.10004
//    7	com.pet2.product.10005
//    8	com.pet2.product.10006
//    9	com.pet2.product.10007
//    10	com.pet2.product.10008
//    20    com.pet2.product.100018

//        [s_d9SDK enterPayViewWithRoleId:roleId
//                             andGoodsId:billNo
//                            andGoodsCnt:@"1"
//                           andGoodsName:title
//                          andTotalMoney:[NSString stringWithFormat:@"%d",price]
//                              andPayDes:@"随便写"];
}

const char *D9Account::getProductIdByGoldsId(uint32 dwGoodsId)
{
    CCString *strProductId = NULL;
    switch (dwGoodsId) {
        case 1:
        case 2:
            strProductId = CCString::createWithFormat("com.pet2.product.1000%d",dwGoodsId - 1);
            break;
        default:
            strProductId = CCString::createWithFormat("com.pet2.product.1000%d",dwGoodsId - 2);
            break;
    }
    return strProductId->getCString();
    
}

