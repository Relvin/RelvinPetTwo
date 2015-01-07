//
//  AnalysicsManager.h
//  MyGame
//
//  Created by panhong on 14-9-12.
//
//

#ifndef __MyGame__AnalysicsManager__
#define __MyGame__AnalysicsManager__

#include <stdio.h>
#include "Defines.h"

#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "UMAnalytics.h"
#include "GameTalkingAnalytics.h"
#endif

class AnalysicsManager
{
private:
    static  AnalysicsManager *   ms_pSharedAnalytics;
public:
    static  AnalysicsManager *   sharedAnalyticsMgr();
    virtual ~AnalysicsManager();
    AnalysicsManager();
    /*!
     eventID  ::  事件id
     accountID :: 传用户Id，
     edata ::  分类标签，用来区分不同的消费点，表明购买什么物品
     */
    void 	SendEvent( const char * eventID ) ;
    void 	SendEvent( const char * eventID, const char * edata ) ;
    
    /*!
     页面统计
     
     @param pageName 页面名称,暂时只提供给友盟
     */
    void    SendBeginPageView(const char* pageName);
    void    SendEngPageView(const char* pageName);
    
    /*!
     @brief 设置用户ID, only for talking data
     */
    void SetUserId(uint32 _dwId);
    
    /*!
     @brief 人物信息更新, only for talking data
     typedef enum {
     kAccountAnonymous = 0,      // 匿名帐户
     kAccountRegistered = 1,     // 显性注册帐户
     kAccountSinaWeibo = 2,      // 新浪微博
     kAccountQQ = 3,             // QQ帐户
     kAccountTencentWeibo = 4,   // 腾讯微博
     kAccountND91 = 5,           // 91帐户
     kAccountType1 = 11,         // 预留1
     kAccountType2 = 12,         // 预留2
     kAccountType3 = 13,         // 预留3
     kAccountType4 = 14,         // 预留4
     kAccountType5 = 15,         // 预留5
     kAccountType6 = 16,         // 预留6
     kAccountType7 = 17,         // 预留7
     kAccountType8 = 18,         // 预留8
     kAccountType9 = 19,         // 预留9
     kAccountType10 = 20         // 预留10
     } TDGAAccountType;
     
     @param serverName 服务器名称
     @param _type 默认1，显性注册账户
     */
    void reportPlayerInfo(int roleLv, const char* serverName = "", const char* roleId = "", int _type = 1);
    
    /*!
     @brief 开始关卡,暂时只提供给talking data
     */
    void beginMission(const char* _missionName);
    
    /*!
     @brief 完成关卡,暂时只提供给talking data
     */
    void completeMission(const char* _missionName);
    
    /*!
     @brief 关卡失败,暂时只提供给talking data
     */
    void failMission(const char* _missionName, const char* reason);
    
    /*!
     @brief 消费,暂时只提供给talking data
     */
    void onPurchase(const char* goodsName, int num, int price);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UMAnalytics *getUMAnalytics();
#endif
    
    void updateUmengOnlineParams();
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UMAnalytics *umeng;
    GameTalkingAnalytics *talkingData;
#endif
    uint32 m_dwUserId;
    std::string m_strServerName;
};
#endif /* defined(__MyGame__AnalysicsManager__) */
