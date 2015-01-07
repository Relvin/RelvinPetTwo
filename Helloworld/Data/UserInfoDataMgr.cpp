//
//  UserInfoDataMgr.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-10-17.
//
//

#include "UserInfoDataMgr.h"
#include "Instruments.h"
#include "cocos2d.h"

void UserInfoDataMgr::setLocalRecTime(uint32 _dwTime) {
    dwLocalRecTime = _dwTime;
    dwLocalRecTime += getLocalCurTimeSec();
}

uint32 UserInfoDataMgr::localRecTime() {
    return dwLocalRecTime - getLocalCurTimeSec();
}
