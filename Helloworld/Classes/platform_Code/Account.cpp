//
//  Account.cpp
//  client
//
//  Created by yuxiao on 13-12-24.
//
//
#include "Account.h"

#if defined VERSION_APP
#include "platform_app_store.h"
#endif

#if defined VERSION_KY
#include "platform_ky.h"
#endif

#if defined VERSION_D9
#include "platform_d9.h"
#endif

#if defined VERSION_PP
#include "platform_pp.h"
#endif

#if defined VERSION_UC
#include "platform_uc.h"
#endif

#if defined VERSION_91
#include "platform_91.h"
#endif

#if defined VERSION_PPS
#include "platform_pps.h"
#endif

#if defined VERSION_IDS
#include "platform_ids.h"
#endif

#if defined VERSION_ITOOLS
#include "platform_itools.h"
#endif

#if defined VERSION_JJZS
#include "platform_txwy.h"
#endif

#if defined VERSION_TONGBUTUI
#include "platform_tbt.h"
#endif

#if defined VERSION_I4
#include "platform_i4.h"
#endif

#if defined VERSION_HAIMA
#include "platform_haima.h"
#endif

#if defined VERSION_XY
#include "platform_xy.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AndroidAccount.h"
#endif

Account *Account::shareInstance()
{
    static Account *account = NULL;
    
    if(account == NULL)
    {
#if defined VERSION_KY
        account = new KYAccount();
#elif defined VERSION_APP111 || VERSION_CHANGBA || VERSION_D9
        account = new D9Account();
#elif defined VERSION_PP
        account = new PPAccount();
#elif defined VERSION_UC
        account = new UCAccount();
#elif defined VERSION_91
        account = new NdComAccount();
#elif defined VERSION_PPS
        account = new PPSAccount();
#elif defined VERSION_IDS
        account = new IdsAccount();
#elif defined VERSION_ITOOLS
        account = new iToolsAccount();
#elif defined VERSION_JJZS
        account = new TxwyAccount();
#elif defined VERSION_TONGBUTUI
        account = new TBTAccount();
#elif defined VERSION_I4
        account = new i4Account();
#elif defined VERSION_HAIMA
        account = new haimaAccount();
#elif defined VERSION_XY
        account = new xyAccount();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        account = new AndroidAccount();
#else
        account = new Account();
#endif
    }    
    return account;
}


std::string Account::getGoodDescription(uint32 good_id)
{
    char value[128] = {0};
    return std::string(value);
}

void Account::buy(uint32 good_id)
{
}

