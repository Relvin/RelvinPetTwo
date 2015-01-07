//
//  platform_pp.h
//  client
//
//  Created by YQ on 13-3-5.
//
//

#ifndef __client__platform_pp__
#define __client__platform_pp__

#include <iostream>
#include "Account.h"

class PPAccount : public Account
{
public:
    virtual void init();
    virtual void login();
    virtual void logout();
    virtual void center();
    virtual void buy(uint32 good_id);
    
public:
    virtual bool applicationOpenURL(void *iosUIApplication, void *iosNSURL, void *iosNSString);
};

#endif /* defined(__client__platform_pp__) */
