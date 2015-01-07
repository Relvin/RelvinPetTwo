//
//  HelloWorldAppController.h
//  HelloWorld
//
//  Created by long on 13-7-10.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import <UIKit/UIKit.h>

@class Reachability;

@interface RootViewController :  UIViewController //<UMSocialUIDelegate>
{
    Reachability *hostReach;
}

+ (RootViewController *)sharedInstance;

- (double)usedMemory;


@end