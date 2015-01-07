//
//  HelloWorldAppController.mm
//  HelloWorld
//
//  Created by long on 13-7-10.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#include "PetLoadingLayer.h"
#include "AnalysicsManager.h"
#import "UMSocial.h"
#include "Support.h"
#include "GameSession.h"
#import "platform_i4.h"
#include "MobClick.h"
#import "UIDevice+IdentifierAddition.h"

@implementation AppController

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

/*
 * add by Relvin
 * (define Local Notification)
 */

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    //TODO: 此处的启动检测加在main函数中更加准确
    AnalysicsManager::sharedAnalyticsMgr()->SendEvent("open_game");
    
    // Override point for customization after application launch.
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES           // 2013-12-04 hyl , clippingNode在ios上无效时修改, 原为GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];
    
    // Use RootViewController manage EAGLView
    //viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController = [[RootViewController alloc] init];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
        [window setRootViewController:viewController];
        
#if defined VERSION_I4
        i4Account::setViewController(viewController);
#endif
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden: YES];
#if __clang_major__ >= 6
    // IOS8 新系统需要使用新的代码咯}
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings
                                                                             settingsForTypes:UIUserNotificationTypeAlert
                                                                             categories:nil]];
        
        
        [[UIApplication sharedApplication] registerForRemoteNotifications];
    }
    else
#endif
    {
        //这里还是原来的代码}
        [[UIApplication sharedApplication] registerForRemoteNotificationTypes:UIRemoteNotificationTypeAlert];
    }
    
    cocos2d::CCApplication::sharedApplication()->run();
    //每次启动的时候,去掉所有的本地通知}
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onlineConfigCallBack:) name:UMOnlineConfigDidFinishedNotification object:nil];
    
    NSString * appKey = [NSString stringWithFormat:@"%s", Support::sharedInstance()->umengKey()];
    NSString * deviceName = [[[UIDevice currentDevice] name] stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString * mac = [[UIDevice currentDevice] macaddress];
    NSString * idfa = [NSString stringWithFormat:@"%s", Support::sharedInstance()->appIdfa()];
    NSString * idfv = [NSString stringWithFormat:@"%s", Support::sharedInstance()->appIdfv()];
    NSString * urlString = [NSString stringWithFormat:@"http://log.umtrack.com/ping/%@/?devicename=%@&mac=%@&idfa=%@&idfv=%@", appKey, deviceName, mac, idfa, idfv];
    [NSURLConnection connectionWithRequest:[NSURLRequest requestWithURL: [NSURL URLWithString:urlString]] delegate:nil];

    
    return YES;
}

- (void)onlineConfigCallBack:(NSNotification *)notification {
    Support::sharedInstance()->setUmengDataAfterUmengUpdateCallBack();
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    CGameSession::NotifyRefeashLayer();
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window {
    return UIInterfaceOrientationMaskAll;
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    /*
     add by Relvin
     Open Local Notification
     */
    Support::sharedInstance()->addLocalNotificationByType(true);
    
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    //每次从后台回来的时候，去除所有通知
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
    cocos2d::CCDirector::sharedDirector()->purgeCachedData();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}


- (void)dealloc {
    [super dealloc];
}

//- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
//{
//    return [WeiboSDK handleOpenURL:url delegate:[RootViewController sharedInstance]];
//}


- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id) annotation
{
    if ([[url host] hasPrefix:@"platformId="])
    {
       return [UMSocialSnsService handleOpenURL:url];
    }
#if defined VERSION_I4 ||VERSION_PP
    return Account::shareInstance()->applicationOpenURL(application, url, sourceApplication);
#else
    return NO;
#endif
    
}

- (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    
    NSString *token = [NSString stringWithFormat:@"%@",deviceToken];
    [[NSUserDefaults standardUserDefaults] setObject:token forKey:@"token"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{

}


- (void)application:(UIApplication *)app didFailToRegisterForRemoteNotificationsWithError:(NSError *)err {
    NSLog(@"RegisterForRemoteNotificationsWithError%@",err);
}

@end

