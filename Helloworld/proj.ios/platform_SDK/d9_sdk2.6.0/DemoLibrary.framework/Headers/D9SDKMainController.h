//
//  D9SDKMainController.h
//  PingMuUpSide
//
//  Created by panhong on 14-1-10.
//  Copyright (c) 2014年 panhong. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "D9ViewDelegate.h"



@interface D9SDKMainController : UIViewController<D9ViewDelegate>
{
}
@property (nonatomic ,retain) NSString *platformID;
@property (nonatomic ,retain) NSString *appID;
@property (nonatomic ,retain) NSString *appKey;
@property (nonatomic ,assign) D9UpdateLevel updataLevel;
@property (nonatomic ,assign) id <D9ViewDelegate> delegate;
@property (nonatomic ,assign,readonly) BOOL isHadLogin;
@property (nonatomic ,retain,readonly) NSString *userID;
@property (nonatomic ,retain,readonly) NSString *username;


- (id)initWithAppid:(NSString *)appID
         platformID:(NSString *)platformID
             appKey:(NSString *)appkey
        updataLevel:(D9UpdateLevel)d9UpDateLevel;
// go to LoginView
- (void)showLoginView;

// go to registerView
- (void)showRegisterView;



// 单例模式
+ (D9SDKMainController*)sharedController;


/* Pay View, open the pay view dialog
 * @param roleID        the login account role id
 * @param goodsId       your goods id
 * @param goodsCnt      your buy goods count
 * @param goodsName     your goods name
 * @param totalMoney    your goods cost in CNY
 * @param payDescription extra description, can be nil or ""
 */
- (void) enterPayViewWithRoleId:(NSString *)roleID
                     andGoodsId:(NSString *)goodsId
                    andGoodsCnt:(NSString *)goodsCnt
                   andGoodsName:(NSString *)goodsName
                  andTotalMoney:(NSString *)totalMoney
                      andPayDes:(NSString *)payDescription;





// appStore支付

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
- (BOOL)appStorePay:(NSString *)appId
                uid:(NSString *)uid
             roleId:(NSString *)roleId
          productId:(NSString *)productId
            goodsId:(NSString *)goodsId
         goodsCount:(NSString *)goodscount
          goodsName:(NSString *)goodsName
              price:(NSString *)price
           currency:(NSString *)currency
        description:(NSString *)description;



//  显示之前位置的D9图标（如果没有 默认为左上角）
- (void)showToolBar:(BOOL)isShow;


//  显示D9图标并且设置位置
- (void)showAssistiveView:(D9ToolBarPlace)place;




//展示个人中心
- (void)showsSelfCenter;


//  切换账号
- (void)switchCount;


// 登出账号
- (void)loginOut;

// 进入游戏中心 传一个值extra
- (void)enterGameCenter:(NSString *)extra;

//进入游戏中心,传键值组合
- (void)enterGameCenterVar:(NSMutableDictionary *)centerDict;

@end
