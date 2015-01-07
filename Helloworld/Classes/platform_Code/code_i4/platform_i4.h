//
//  platform_i4.h
//  client
//
//  Created by CX_ZSY on 14-7-7.
//
//

#ifndef __client__platform_i4__
#define __client__platform_i4__
#include "Account.h"
#include <iostream>

class i4Account : public Account
{
public:
    virtual void init();
    virtual void login();
    virtual void logout();
    virtual void center();
    virtual void buy(uint32 good_id);
    virtual bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString);
    static void setViewController(void *iosUIApplication);
};

#endif /* defined(__client__platform_i4__) */
