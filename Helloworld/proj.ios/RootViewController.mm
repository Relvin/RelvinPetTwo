//
//  HelloWorldAppController.h
//  HelloWorld
//
//  Created by long on 13-7-10.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import "RootViewController.h"
#include "MailDataMgr.h"
#include "GameSession.h"

#if defined VERSION_D9
#import <DemoLibrary/Reachability.h>
#else
#import "Reachability.h"
#endif

#include "Support.h"
#include "Version.h"
#include "LoginSystem.h"
#include "GlobalData.h"

#import <sys/sysctl.h>
#import <mach/mach.h>

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsPortrait( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskPortrait;
#endif
    return UIInterfaceOrientationMaskPortrait;
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    _sharedInstance = nil;
    [super dealloc];

    [[NSNotificationCenter defaultCenter] removeObserver:self name:kReachabilityChangedNotification object:nil];

    [hostReach release];

}


- (id)init {
    if ((self = [super init]))
    {
        _sharedInstance = self;
    }
    
    NSString* m_strLoginServerIp;
#ifndef NDEBUG
    m_strLoginServerIp = [NSString stringWithFormat:@"http://%s", DEBUG_IP];
#elif defined VERSION_I4
    m_strLoginServerIp = [NSString stringWithFormat:@"http://%s", I4_IP];
#else
    m_strLoginServerIp = [NSString stringWithFormat:@"http://%s", RELEASE_IP];
#endif
    

    hostReach = [[Reachability reachabilityWithHostName:m_strLoginServerIp] retain];
    [hostReach startNotifier];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reachabilityChanged:) name:kReachabilityChangedNotification object:nil];
    

    return self;
}

static RootViewController* _sharedInstance = nil;
+ (RootViewController *)sharedInstance
{
    if (!_sharedInstance)
    {
        NSLog(@"get RootViewController _sharedInstance error!");
        _sharedInstance = [[self alloc] init];
    }
    
    return _sharedInstance;
}



- (void)reachabilityChanged:(NSNotification*) note {
    Reachability* curReach = [note object];

    NSParameterAssert([curReach isKindOfClass:[Reachability class]]);
    NetworkStatus status = [curReach currentReachabilityStatus];
    
    if (status == NotReachable) {
        NSLog(@"net work not reachable");
//        if (!GlobalData::bOutGame) {
//            LoginSystem::Get()->ShowNoServiceLayer();
//        }
    } else if (status == ReachableViaWiFi) {
        NSLog(@"wifi net work");
    } else if (status == ReachableViaWWAN) {
//        CCMessageBox("当前为运营商网络，请注意当月剩余流量，虽然我们的游戏很省流量哒~", "温馨提示么么哒");
        NSLog(@"WAN net work");
    }

}


// 获取当前任务所占用的内存（单位：MB）
- (double)usedMemory
{
    task_basic_info_data_t taskInfo;
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(),
                                         TASK_BASIC_INFO,
                                         (task_info_t)&taskInfo,
                                         &infoCount);
    
    if (kernReturn != KERN_SUCCESS
        ) {
        return NSNotFound;
    }
    
    return taskInfo.resident_size / 1024.0 / 1024.0;
}




@end
