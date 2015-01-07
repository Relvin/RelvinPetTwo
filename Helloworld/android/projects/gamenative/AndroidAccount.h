//
#ifndef _ANDROID_ACCOUNT_H_
#define _ANDROID_ACCOUNT_H_


#include <iostream>
#include "Defines.h"
#include "cocos2d.h"
#include "Account.h"

class AndroidAccount : public Account
{
public:
    AndroidAccount(){};
    ~AndroidAccount(){};
    
    virtual void login();
    virtual void logout();
    virtual void center();
    virtual void switchAccount();
	virtual bool exit();
    
    virtual void buy(uint32 good_id);
protected:
	virtual std::string getGoodDescription(uint32 good_id);
};

#endif /* defined(__client__AccountBase__) */
