//
//  ShareWeiboWeixin.m
//  HelloWorld
//
//  Created by jun on 14-4-17.
//
//

#include "ShareWeiboWeixin.h"
#include "GameSession.h"
#include "MailDataMgr.h"
#include "SystemMessage.h"
#include "ResourceStringClient.h"
#include "ConfigGet.h"
#include "Support.h"
#include "FlyTextLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CCUMSocialSDK.h"

USING_NS_UM_SOCIAL;
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform_android.h"
#endif

static const char* biaoqing[10] = {" ^o^", " ^_^", " ∩_∩", " ^﹏^", " ^__^", " ^L^", " :p", " ^O^", " ∩﹏∩", " ∩︿∩"};
static int flag = -1;

void ShareWeiboWeixin::onShareWeibo(const char *text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_shareText = text;
    // 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create(Support::sharedInstance()->umengKey());
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl(Support::sharedInstance()->appStoreUrl());
    if (!sdk->isAuthorized(SINA))
    {
        sdk->authorize(SINA, auth_selector(authCallback));
    }
    if (flag == -1) {
		srand(time(NULL));
		flag = rand() % 10;
	}
	flag = (flag + 1) % 10;
    m_shareText += biaoqing[flag];
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "screenshot.png";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->directShare(SINA, text,fullpath.c_str(), share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdk->directShare(SINA, m_shareText.c_str(),fullpath.c_str(), share_selector(shareCallback));
#endif
#endif


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // TODO take screenshot
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "screenshot.png";
    UmengSocialShareDirect("Sina", text, fullpath);
#endif

}

void ShareWeiboWeixin::onShareWeiXin(const char *text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_shareText = text;
    // 获取一个CCUMSocialSDK实例
    CCUMSocialSDK *sdk = CCUMSocialSDK::create(Support::sharedInstance()->umengKey());
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl(Support::sharedInstance()->appStoreUrl());
    sdk->setWeiXinAppId(Support::sharedInstance()->weChatAppId());
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "screenshot.png";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->directShare(WEIXIN_CIRCLE, text,fullpath.c_str(), share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdk->directShare(WEIXIN_CIRCLE, text,fullpath.c_str(), share_selector(shareCallback));
#endif
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "screenshot.png";
    UmengSocialShareDirect("WeixinCircle", text, fullpath);
#endif
}

void ShareWeiboWeixin::shareCallback(int platform, int stCode, const std::string &errorMsg)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if ( stCode == 100 )
    {
        CCLOG("#### HelloWorld 开始分享");
    }
    else if ( stCode == 200 )
    {
        CCLOG("#### HelloWorld 分享成功 = %s",GET_STR(Str_Share_success));
        CCDirector::sharedDirector()->getRunningScene()->addChild(FlyTextLayer::create(GET_STR(Str_Share_success)),1000);
        CGameSession::SendFriendShareRequest();
        if (CMailDataMgr::Get()) {
            CMailDataMgr::Get()->CloseShareFrameLayer();
        }
        CCNotificationCenter::sharedNotificationCenter()->postNotification("SHARE_SUCCESS");
    }
    else
    {
        CCUMSocialSDK *sdk = CCUMSocialSDK::create(Support::sharedInstance()->umengKey());
        // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
        if (sdk->isAuthorized(platform))
        {
            sdk->deleteAuthorization(platform, auth_selector(authCallback));
        }
        if (platform == SINA) {
            SystemMessage::showSystemMessage(1, NULL, GET_STR(Str_umeng_share_Failure),ShareWeiboWeixin::Get(),false,1);
        }
        
        CCLOG("#### HelloWorld 分享出错");
    }
    
    CCLOG("platform num is : %d.", platform);
#endif
}

void ShareWeiboWeixin::authCallback(int platform, int stCode, const std::map<std::string, std::string> &data)
{
//    200代表授权成功, 100代表开始授权, 0代表授权出错, -1代表取消授权
    if ( stCode == 100 )
    {
        CCLOG("#### HelloWorld 开始授权");
    }
    else if ( stCode == 200 )
    {
        CCLOG("#### HelloWorld 授权成功");
    }
    else if ( stCode == -1)
    {
        CCLOG("#### HelloWorld 取消授权");
    }
    else
    {
        CCLOG("#### HelloWorld 授权出错");
    }
    
    CCLOG("platform num is : %d.", platform);
}

void ShareWeiboWeixin::systemMessageOKTapped(SystemMessage *systemMessage)
{
    this->onShareWeibo(m_shareText.c_str());
}
