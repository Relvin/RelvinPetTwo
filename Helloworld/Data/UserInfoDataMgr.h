//
//  UserInfoDataMgr.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-10-17.
//
//

#ifndef __MyGame__UserInfoDataMgr__
#define __MyGame__UserInfoDataMgr__

#include <iostream>
#include "Singleton.h"
#include "Defines.h"
#include "cocos2d.h"

class UserInfoDataMgr : public Singleton<UserInfoDataMgr> {
    
public:
    UserInfoDataMgr()
    : m_bGotoVip(false)
    {
        dwLocalRecTime = 0;
    }
    ~UserInfoDataMgr() {
        
    }
    
    void setLocalRecTime(uint32 _dwTime);
    uint32 localRecTime();
    
    CC_SYNTHESIZE(bool, m_bGotoVip, GotoVipFlag);
private:
    uint32 dwLocalRecTime;
};

#endif /* defined(__MyGame__UserInfoDataMgr__) */
