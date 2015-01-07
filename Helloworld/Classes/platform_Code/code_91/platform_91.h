//
//  platform_91.h
//  client
//
//  Created by yuxiao on 14-1-17.
//
//

#ifndef __client__platform_91__
#define __client__platform_91__

#include "Account.h"

class NdComAccount : public Account
{
public:
    static NdComAccount *shareInstance();
    
    virtual void init();
    virtual void login();
    virtual void logout();
    virtual void center();
    virtual void switchAccount();
    virtual void buy(uint32 good_id);
    
    void feedback();
    void bbs();
    
public:
    virtual void applicationWillEnterForeground(void *iosUIApplication);
};

#endif /* defined(__client__platform_91__) */
