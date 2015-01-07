//
//  platform_d9.h
//  client
//
//  Created by mj1225 on 13-6-24.
//
//

#ifndef client_platform_d9_h
#define client_platform_d9_h

#include "Account.h"

class D9Account : public Account
{
public:
    virtual void init();
    virtual void login();
    virtual void logout();
    virtual void buy(uint32 good_id);
    virtual void switchAccount();
    virtual void center();
    const char* getProductIdByGoldsId(uint32 dwGoodsId);
};

#endif
