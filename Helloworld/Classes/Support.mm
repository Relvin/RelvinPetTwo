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

#import "Support.h"
#import <UIKit/UIKit.h>

#import "CCDirectorCaller.h"
#include "RootViewController.h"
#import <AdSupport/AdSupport.h>
#import "UIDevice+IdentifierAddition.h"
#import "SFHFKeychainUtils.h"
#include "LoginSystem.h"
#include "GameSession.h"
#include "Role.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "AnalysicsManager.h"
#include "GlobalData.h"


#define LOCALNOTI(KIND) \
if (fireDate != NULL) {\
note = [[UILocalNotification alloc] init];\
note.timeZone = [NSTimeZone systemTimeZone];\
note.alertBody = [NSString stringWithCString:GET_STR(STR_NOTI_##KIND) encoding:NSUTF8StringEncoding];\
note.fireDate = fireDate;\
[[UIApplication sharedApplication] scheduleLocalNotification:note];\
[note release];\
}

static Support* sm_pSharedSupport = NULL;

Support* Support::sharedInstance()
{
    if (!sm_pSharedSupport) {
        sm_pSharedSupport = new Support;
    }
    return sm_pSharedSupport;
}

Support::Support()
{
    
}

Support::~Support()
{
    sm_pSharedSupport = NULL;
}


TargetPlatform Support::getTargetPlatform()
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) // idiom for iOS <= 3.2, otherwise: [UIDevice userInterfaceIdiom] is faster.
    {
        return kTargetIpad;
    }
    else
    {
        return kTargetIphone;
    }
}

bool Support::isIpad()
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        return true;
    }
    return false;
}

const char* Support::uniqueId() {
    UIDevice* device = [UIDevice currentDevice];
    NSString* md5mac = [device uniqueMacAddressIdentifier];
    
    if (md5mac.length < 10 || [md5mac isEqualToString:@"0f607264fc6318a92b9e13c65db7cd3c"]) {
        md5mac = [NSString stringWithFormat:@"%s", appIdfv()];;
    }
    if (md5mac.length < 10) {
        md5mac = [NSString stringWithFormat:@"%s", appIdfa()];
    }
    if (md5mac.length < 10) {
        md5mac = [NSString stringWithFormat:@"d9donotgetuuid-%03df-%03du-%03dc-%03dk", rand()%1000, rand()%1000, rand()%1000, rand()%1000];
    }
    return [md5mac cStringUsingEncoding:NSUTF8StringEncoding];
}

const char* Support::appIdfv()
{
    NSString * idfv = @"";
    if([[UIDevice currentDevice] respondsToSelector:@selector( identifierForVendor)]) {
        idfv = [[UIDevice currentDevice].identifierForVendor UUIDString];
    }
    
    return [idfv cStringUsingEncoding:NSUTF8StringEncoding];
}

const char* Support::appIdfa()
{
    NSString* idfa = @"";
    NSBundle *adSupportBundle = [NSBundle bundleWithPath:@"/System/Library/Frameworks/AdSupport.framework"];
    [adSupportBundle load];
    
    if (adSupportBundle == nil) {
//        return @"";
        return "";
    }
    else{
        
        Class asIdentifierMClass = NSClassFromString(@"ASIdentifierManager");
        
        if(asIdentifierMClass == nil){
//            return @"";
            return "";
        }
        else{
            
            //for no arc
            //ASIdentifierManager *asIM = [[[asIdentifierMClass alloc] init] autorelease];
            //for arc
            ASIdentifierManager *asIM = [[asIdentifierMClass alloc] init];
            
            if (asIM == nil) {
//                return @"";
                return "";
            }
            else{
                
                if(asIM.advertisingTrackingEnabled){
                    idfa = [asIM.advertisingIdentifier UUIDString];
                }
                else{
                    idfa = [asIM.advertisingIdentifier UUIDString];
                }
            }
        }
    }
    return [idfa cStringUsingEncoding:NSUTF8StringEncoding];
}

const char* Support::deviceType()
{
    return "ios";
//    UIDevice* device = [UIDevice currentDevice];
//    NSString* type = [device model];
//    return [type cStringUsingEncoding:NSUTF8StringEncoding];
}

const char* Support::deviceOS()
{
    UIDevice* device = [UIDevice currentDevice];
    NSString* os = [NSString stringWithFormat:@"%@_%@", [device systemName], [device systemVersion]];
    return [os cStringUsingEncoding:NSUTF8StringEncoding];
}

const char* Support::systemVersion() {
    return "0";
    UIDevice* device = [UIDevice currentDevice];
    NSString* os = [NSString stringWithFormat:@"%@", [device systemVersion]];
    return [os cStringUsingEncoding:NSUTF8StringEncoding];
}

bool Support::isPhone5()
{
    BOOL iPhone5 =([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO);
    return iPhone5;
}

float Support::getScreenHWRadio()
{
    CGSize screen = [[UIScreen mainScreen] currentMode].size;
    float ratio = screen.height / screen.width;
    NSLog(@"ratio:%f, height:%f, width:%f", ratio, screen.height, screen.width);
    return ratio;
}


void Support::saveUdidToKeyChain()
{
    NSString* strUrlScheme = [NSString stringWithFormat:@"%@pet2", kD9URLSchemePrefix];
    NSString* strSuffix = [strUrlScheme stringByAppendingString:kD9KeychainSuffix];
    
    [SFHFKeychainUtils storeUsername:kD9KeychainUDID
                         andPassword:[NSString stringWithFormat:@"%s", uniqueId()]
                      forServiceName:strSuffix
                      updateExisting:YES
                               error:nil];
}

const char* Support::readUdidFromKeyChain()
{
    NSString* strUrlScheme = [NSString stringWithFormat:@"%@pet2", kD9URLSchemePrefix];
    NSString* strSuffix = [strUrlScheme stringByAppendingString:kD9KeychainSuffix];
    
    NSString* strUdid = [SFHFKeychainUtils getPasswordForUsername:kD9KeychainUDID
                                                   andServiceName:strSuffix
                                                            error:nil];
    if (strUdid == nil) {
        return "not_get";
    }
    return [strUdid cStringUsingEncoding:NSUTF8StringEncoding];
}

void Support::delUdidInKeyChain()
{
    NSString* strUrlScheme = [NSString stringWithFormat:@"%@pet2", kD9URLSchemePrefix];
    NSString* strSuffix = [strUrlScheme stringByAppendingString:kD9KeychainSuffix];
    
    [SFHFKeychainUtils deleteItemForUsername:kD9KeychainUDID
                              andServiceName:strSuffix
                                       error:nil];
}

const char* Support::appVersion()
{
    NSDictionary* infoDic = [[NSBundle mainBundle] infoDictionary];
//    NSString* version = [infoDic objectForKey:@"CFBundleVersion"];
    //CFBundleShortVersionString
    NSString* version = [infoDic objectForKey:@"CFBundleShortVersionString"];
    return [version cStringUsingEncoding:NSUTF8StringEncoding];
}

const char* Support::appName()
{
    NSDictionary* infoDic = [[NSBundle mainBundle] infoDictionary];
    NSString* name = [infoDic objectForKey:@"CFBundleDisplayName"];
    return [name cStringUsingEncoding:NSUTF8StringEncoding];
}

void Support::makeScreenAlwaysOn()
{

}

void Support::makeScreenDefault()
{

}

int Support::appChannel()
{
#ifdef VERSION_I4
    return 958;
#endif
    
#ifdef VERSION_D9
    return 100;
#endif
    
#ifdef NDEBUG
    // 商务服渠道号2}
    //TODO:增加商务target
    return 2;
#else
    return 1;
#endif
}

void Support::networkDis()
{
    LoginSystem::Get()->EnterBackGround();
    LoginSystem::Get()->ShowNoServiceLayer();
}

void Support::addLocalNotificationByType(bool twoDayNotiOpen)
{
    //进入后台的时候，加入各种通知
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
    UILocalNotification *note;
    CRole *pRole =  CGameSession::GetRole();
    unsigned unitFlags = NSDayCalendarUnit | NSMonthCalendarUnit | NSYearCalendarUnit |
    NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit;
    NSCalendar *gregorian = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    [gregorian setTimeZone:[NSTimeZone systemTimeZone]];
    NSDateComponents *comps = NULL;
    NSDate* fireDate = NULL;
    
    //能量回复满
    if (pRole) {
        if (pRole->GetdwEnergyMax() > pRole->GetdwEnergy()) {
            int nTime = (pRole->GetdwEnergyMax() - pRole->GetdwEnergy()) * 360;//3分钟回1点
            if (nTime != 0) {
                fireDate = [NSDate dateWithTimeIntervalSinceNow:nTime];
                LOCALNOTI(ENERGY);
            }
        }
        
    }
    NSDate *date = [NSDate date];
    comps = [gregorian components:unitFlags fromDate:date];
    [comps setTimeZone:[NSTimeZone systemTimeZone]];
    [comps setMinute:0];
    [comps setSecond:0];
    [comps setDay:comps.day];
    for (int i = 0; i < 7; i++)
    {
        if (i != 0) {
            [comps setDay:comps.day + 1];
        }
        if (i != 0 || [comps hour] < 12) {
            [comps setHour:12];
            fireDate = [gregorian dateFromComponents:comps];
            LOCALNOTI(ENERGY_GET);
        }
        if (i != 0 || [comps hour] < 18) {
            [comps setHour:18];
            fireDate = [gregorian dateFromComponents:comps];
            LOCALNOTI(ENERGY_GET);
        }
    }
    
    if (twoDayNotiOpen) {
        //从后天中午起连续7天都提醒,时间在每天中午12点
        NSDate *date = [NSDate date];
        comps = [gregorian components:unitFlags fromDate:date];
        [comps setTimeZone:[NSTimeZone systemTimeZone]];
        [comps setHour:11];
        [comps setMinute:30];
        [comps setSecond:0];
        [comps setDay:comps.day];
        for (int i = 0; i < 8; ++i) {
            if (i == 0)
            {
                [comps setDay:comps.day + 2];
            }
            else
            {
                [comps setDay:comps.day + 1];
            }
            fireDate = [gregorian dateFromComponents:comps];
            LOCALNOTI(LONG_TIME_NO_LOGIN);
        }
    }
    
}

const char* Support::umengKey() {
#ifdef VERSION_I4
    //new umeng key only for pet2
    return "5412c177fd98c50b03007c10";
#elif VERSION_D9
    return "5459d154fd98c5a9ac002401";
#else
    return "5459d154fd98c5a9ac002401";
    //pet1 umeng
//    return "5415bdf9fd98c518bb04707e";
#endif
}

const char* Support::appStoreUrl() {
    
#ifdef VERSION_I4
    return "http://hxjl2.gamed9.com/";
//    return "https://itunes.apple.com/cn/app/huan-xiang-jing-ling-mo-ni/id517185973?mt=8";
#elif VERSION_D9
    int appid = 938041105;
    return CCString::createWithFormat("http://itunes.apple.com/cn/app//id%d?mt=8", appid)->getCString();
#else
    return "https://itunes.apple.com/cn/app/huan-xiang-jing-ling-mo-ni/id517185973?mt=8";
#endif
}

const char* Support::weChatAppId() {
#ifdef VERSION_I4
    return "wx46b247f54c1f7644";
#elif defined VERSION_D9
    return "wx02a2ac366dd837f9";
#else
    return "wx02a2ac366dd837f9";
#endif
}

const char* Support::talkingData() {
#ifdef VERSION_I4
    return "62CB5BDB740F52C73AC19CC817178B8B";
#else
    return "62CB5BDB740F52C73AC19CC817178B8B";
#endif
}

double Support::usedMem()
{
    return [[RootViewController sharedInstance] usedMemory];
}

void Support::setSplashGone()
{
    
}

int Support::getUmengInt(const char *key) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return AnalysicsManager::sharedAnalyticsMgr()->getUMAnalytics()->getUmengKey(key);
#else
    return 0;
#endif
}

void Support::setUmengDataAfterUmengUpdateCallBack()
{
#ifndef NDEBUG
    GlobalData::shared()->setVipSwitch(false);
    GlobalData::shared()->setShareSwitch(false);
    GlobalData::shared()->setGachaSwitch(false);
    GlobalData::shared()->setShopListSwitch(false);
#else
    GlobalData::shared()->setVipSwitch(getUmengInt("VIPSwitch"));
    GlobalData::shared()->setShareSwitch(getUmengInt("ShareSwitch"));
    GlobalData::shared()->setGachaSwitch(getUmengInt("GachaSwitch"));
    GlobalData::shared()->setShopListSwitch(getUmengInt("ShopListSwitch"));
#endif
    
}

