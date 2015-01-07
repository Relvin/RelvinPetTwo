//
//  Account.h
//  client
//
//  Created by yuxiao on 13-12-24.
//
//

#ifndef __client__Account__
#define __client__Account__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"

class Account
{
public:
    static Account *shareInstance();

    virtual void init() {};

    virtual void login() {};
    virtual void logout() {};
    virtual void center() {};
    virtual void switchAccount() {};
	/*
		false: platform don't need this event. native can exit app now
		true: platform will handle exit. do not exit app now.
	*/
	virtual bool exit(){return false;}
    
    virtual void buy(uint32 good_id);
    
protected:
    static std::string getGoodDescription(uint32 good_id);
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
public:
    virtual void applicationWillResignActive(void *iosUIApplication);
    virtual void applicationDidBecomeActive(void *iosUIApplication);
    virtual void applicationDidEnterBackground(void *iosUIApplication);
    virtual void applicationWillEnterForeground(void *iosUIApplication);
    virtual void applicationWillTerminate(void *iosUIApplication);
    virtual void applicationDidRegisterForRemoteNotificationsWithDeviceToken(void *iosNSData);
    virtual void applicationDidReceiveRemoteNotification(void *iosNSDictionary);
    virtual bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString);
#endif
};

#endif /* defined(__client__AccountBase__) */
