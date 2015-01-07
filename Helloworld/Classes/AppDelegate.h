//
//  HelloWorldAppDelegate.h
//  HelloWorld
//
//  Created by long on 13-7-10.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.}
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"

class CNetClient;
/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function is called when the application enters the background
    @param  the pointer of the application instance
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function is called when the application enters the foreground
    @param  the pointer of the application instance
    */
    virtual void applicationWillEnterForeground();
    
    static AppDelegate* sharedAppDelegate() { return (AppDelegate*)(CCApplication::sharedApplication()); }
    CNetClient* netClient() { return m_netClient; }
private:
    CNetClient* m_netClient;
};

#endif // _APP_DELEGATE_H_

