//
//  D9ViewDelegate.h
//  PingMuUpSide
//
//  Created by panhong on 14-1-14.
//  Copyright (c) 2014年 panhong. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum  _D9ToolBarPlace   //悬浮框位置
{
	D9ToolBarAtTopLeft = 1,			/**< 左上 */
	D9ToolBarAtTopRight,              /**< 右上 */
    D9ToolBarAtMiddleLeft,            /**< 左中 */
	D9ToolBarAtMiddleRight,           /**< 右中 */
	D9ToolBarAtBottomLeft,            /**< 左下 */
	D9ToolBarAtBottomRight,           /**< 右下 */
}	D9ToolBarPlace;

typedef enum  _D9CloseView        // 关闭的视图类型
{
	D9CloseMainView = 1,			/**< 个人中心主视图 */
	D9CloseOfficialView ,              /**< 官网 */
    D9CloseChangePassWord,            /**< 改密视图 */
    D9ClosePayWebView,                 // 网页支付
    D9CloseBindAccountView,             //  绑定手机视图
    D9CloseForgotPasswordView,          //  关闭找回密码视图
    D9CloseUserProtocolView               //  关闭萌果协议
} D9CloseView;


typedef enum  _D9UpdateLevel       // 更新类型  默认 D9Update_Level_Normal
{
	D9Update_Level_Strict = 1,			/**< 强制更新  检测版本失败卡界面*/
	D9Update_Level_Normal              // 非强制更新 ,版本检测失败不会仍然可以登陆
} D9UpdateLevel;






@protocol D9ViewDelegate <NSObject>

@optional

//快速登回调
- (void)quicklyLogin:(NSString *)userId;

//登陆成功回调
- (void)loginSuccess:(NSMutableDictionary *)result;

//注册成功回调
-(void)registerSuccess:(NSMutableDictionary *)result;

// 改密成功回调
- (void)changePassWordSuccess:(NSMutableDictionary *)result;


// 关闭个人中心回调
- (void)d9CloseView:(D9CloseView)selfCenterView;

// 切换账号回调
- (void)switchCountback;

@end
