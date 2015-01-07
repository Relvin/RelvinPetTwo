//
//  GlobalData.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-30.}
//
//

#ifndef __HelloWorld__GlobalData__
#define __HelloWorld__GlobalData__

#include <iostream>
#include "cocos2d.h"

#define BUFFER_SIZE_64 64
static char strBuf64[BUFFER_SIZE_64];

#define BUFFER_SIZE_512 512
static char strBuf512[BUFFER_SIZE_512];

#define BUFFER_SIZE_1024 1024
static char strBuff1024[BUFFER_SIZE_1024];

class GlobalData
{
    
public:
    GlobalData();
    static GlobalData* shared();
    void initColorMap();
    cocos2d::ccColor4B getColorByKey(const char * color);
    enum {
        kMainBottom = 0,
        kTeamBottom,
        kCityBottom,
        kGachaBottom,
        kShopBottom,
        kSystemBottom,
        kEventBottom,
        kUnionBottom,
        kFriendBottom,
        kStageBottom,
        kChatBottom,
        kAreanBottom,
        kActiveMapBottom,
    };
    
    static bool bNeecConnection;
    static int nCurNormalAreaIdx;   // 当前所在的大地图位置 AreaId}
    static int nCurHeroAreaIdx;     // 当前所在精英大地图}
    static bool bReConnectFlag;     // 重连Flag}
    static int kBottomTag;      // 下方的按钮index}
    static bool bUseIpaResource;    // 判断是否需要使用Ipa包中的资源，true表明当前Ipa内的资源比Document中的高，false表明ipa的资源比Document的低，需要读取Document中更新的资源。}
    
    static bool bFromPetChoose;
    static bool bLoginAccount;      // 登录账号进入主界面，第一次才请求公告}
    static int nReconnetCnt;        // 重连次数，三次之后，主界面退出游戏(待定)，其他界面返回到主界面
//    static bool bOutGame;         // 是否还没进入到游戏中，用于是否跳出网络重连界面
    static bool bFirst2003;         // 是否是第一次过2003，跳出装备引导
    
    // 时间}
    static void GetCurTime();

    // 强制关闭NoServiceLayer}
    static bool bCloseForce;
    // 心跳包，默认网络正常true}
    static bool bStillAlive;
    
    //自动战斗开关
    static bool bIsAutoFight;
    
    /*!
     专为新手增加的变量，第一章跳转到第二章
     */
    static bool bJumpToTwo;
    
    CC_SYNTHESIZE(bool, m_bVipSwitch, VipSwitch);
    CC_SYNTHESIZE(bool, m_bShareSwitch, ShareSwitch);
    CC_SYNTHESIZE(bool, m_bGachaSwitch, GachaSwitch);
    CC_SYNTHESIZE(int, m_nDailyLayerType, DailyLayerType);
    CC_SYNTHESIZE(bool, m_bShopListSwitch, ShopListSwitch);
private:
    
    std::map<std::string, cocos2d::ccColor4B> m_colorMap;
    
};

#endif /* defined(__HelloWorld__GlobalData__) */
