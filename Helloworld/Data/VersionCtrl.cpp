//}
//  VersionCtrl.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-25.}
//
//

#include "VersionCtrl.h"
#include "cocos2d.h"
#include "Log.h"
#include "Defines.h"
#include "Version.h"
#include "GlobalData.h"

VersionCtrl::VersionCtrl() {
    
}

VersionCtrl::~VersionCtrl() {
    
}

bool VersionCtrl::needUpdate(int remote)
{
    int nCurVer;
    
    nCurVer = curVerCode();
    
    // 当前的版本号，比服务器给过来的版本号还要低，那么需要更新。默认初始化服务器列表数据等于IPA自身的资源版本号，正常情况下肯定小于等于remote版本号}
    CCLOG("local version:%d, remote version:%d", nCurVer, remote);
    if (nCurVer < remote) {
        return true;
    }
    return false;
}

int VersionCtrl::curVerCode()
{
    int localVer = 0;
    localVer = cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(D9_RESOURCE_VERSION);
    
    if (localVer == 0) {
        // 新版本安装，返回自身的IPA包中的版本号}
        localVer = CUR_RESOURCE_VERSION;
    }
    // 当前ipa的资源版本号和Documets中资源版本号的比较}
    if (CUR_RESOURCE_VERSION > localVer) {
        localVer = CUR_RESOURCE_VERSION;
    }
    
    return localVer;
}

const char* VersionCtrl::versionCode()
{
    char temp[16];
    sprintf(temp, "%d", curVerCode());
    
    std::string strVer(temp);
    
    return strVer.c_str();
}


void VersionCtrl::updateCallback(int latestVersion)
{

    cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey(D9_RESOURCE_VERSION, latestVersion);
    IME_LOG("Latest Version Code is:%d", latestVersion);
    checkUseWhichResource();
    return;
}

bool VersionCtrl::checkUseWhichResource()
{
    if (curVerCode() > CUR_RESOURCE_VERSION) {
        GlobalData::bUseIpaResource = false;
    } else {
        GlobalData::bUseIpaResource = true;
    }
    return GlobalData::bUseIpaResource;
}

