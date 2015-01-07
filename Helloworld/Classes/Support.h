/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_SUPPORT_H
#define __CC_SUPPORT_H

#include "platform/CCCommon.h"
#include <string>
#include "platform/CCApplicationProtocol.h"

USING_NS_CC;

#define kD9URLSchemePrefix              @"D9_"
#define kD9KeychainUDID                 @"D9UDID"

#ifdef VERSION_I4
    #define kD9KeychainSuffix               @"_I4_SUFFIX"
#elif defined VERSION_D9
    #define kD9KeychainSuffix               @"_D9_SUFFIX"
#elif defined VERSION_D9
    #define kD9KeychainSuffix               @"_91_SUFFIX"
#else
    #define kD9KeychainSuffix               @"_IOS_SUFFIX"
#endif


class Support
{
public:
    Support();
    virtual ~Support();
    
    static Support* sharedInstance();
    
    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform();
    
    /**
     @brief Check whether it is iPad
     */
    bool isIpad();
    
    /*!
     @brief 取唯一UDID
     */
    const char* uniqueId();
    
    /**
     @brief Get IDFV, IDFV will change by reset SYSTEM.
     获取设备唯一信息，如果没有渠道idfv则继续取idfa，否则自动生成一个
     */
    const char* appIdfv();
    
    /**
     @brief Get IDFA, IDFA can change in SETTINGS.
     */
    const char* appIdfa();
    
    /**
     @brief Get device type
     */
    const char* deviceType();
    
    /**
     @brief Get device OS version
     */
    const char* deviceOS();
    const char* systemVersion();
    
    /**
     @brief Get iPhone Type
     @return    true    iPhone5
     false   iPhone4
     */
    bool isPhone5();
    
    float getScreenHWRadio();
    
    /**
     @brief save/read/delete udid in keychain
     */
    void saveUdidToKeyChain();
    const char* readUdidFromKeyChain();
    void delUdidInKeyChain();
    
    /**
     @brief Get App Version / Name
     */
    const char* appVersion();
    const char* appName();
    
    /**
     @brief 保持屏幕常亮}
     */
    void makeScreenAlwaysOn();
    void makeScreenDefault();
    
    /**
     @brief 渠道号
     */
    int appChannel();

    void networkDis();
    void addLocalNotificationByType(bool twoDayNotiOpen);
    
    /*!
     @brief 友盟Key
     */
    const char* umengKey();
    
    /*!
     @brief 苹果下载地址
     */
    const char* appStoreUrl();
    
    /*!
     @brief 微信AppId
     */
    const char* weChatAppId();
    
    /*!
     @brief talking data app key
     */
    const char* talkingData();
    
    double usedMem();
    
    /*!
     @brief 去除启动图
     */
    void setSplashGone();
    
    /*!
     @brief 获取对应的Umeng开关
     @param key Umeng的参数
     */
    int getUmengInt(const char * key);
    
    void setUmengDataAfterUmengUpdateCallBack();
    
};


#endif	// end of __CC_APPLICATION_IOS_H__}
