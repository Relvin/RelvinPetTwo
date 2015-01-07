//
//  GlobalData.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-30.}
//
//

#include "GlobalData.h"
#include "cocos2d.h"
#include <algorithm>

USING_NS_CC;

bool GlobalData::bNeecConnection = false;
int GlobalData::nCurNormalAreaIdx = -1;
int GlobalData::nCurHeroAreaIdx = -1;
bool GlobalData::bReConnectFlag = false;
int GlobalData::kBottomTag = 0;
bool GlobalData::bFromPetChoose = false;
bool GlobalData::bUseIpaResource = false;
bool GlobalData::bCloseForce = false;
bool GlobalData::bStillAlive = true;
bool GlobalData::bLoginAccount = true;
int GlobalData::nReconnetCnt = 0;
//bool GlobalData::bOutGame = true;
bool GlobalData::bFirst2003 = false;
bool GlobalData::bIsAutoFight = false;
bool GlobalData::bJumpToTwo = false;

static GlobalData *g_shared = NULL;


GlobalData::GlobalData()
: m_bVipSwitch(true)
, m_bShareSwitch(true)
, m_bGachaSwitch(true)
, m_nDailyLayerType(0)
{
    bNeecConnection = false;
}

GlobalData* GlobalData::shared()
{
    if (!g_shared) {
        g_shared = new GlobalData;
        g_shared->initColorMap();
    }
    return g_shared;
}

#pragma mark GlobalData

void GlobalData::GetCurTime()
{
    struct cc_timeval now;
    cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
    
    struct tm *tm;
    long long hsec = ((long long)(now.tv_sec)) * 1000 + now.tv_usec * 0.001;
    time_t timep = now.tv_sec;
    tm = localtime(&timep);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    int hour = tm->tm_hour;
    int min = tm->tm_min;
    int sec = tm->tm_sec;
    
    
    CCLog("[%d-%d-%d] >>> %d:%d:%d:%lld", year, month, day, hour, min, sec, hsec);
}

void GlobalData::initColorMap()
{
    m_colorMap.clear();
    m_colorMap["red"] = ccc4(255, 0, 0, 255);
}

ccColor4B GlobalData::getColorByKey(const char *color)
{
    std::string str = color;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::map<std::string, ccColor4B>::iterator it = m_colorMap.find(str);
    if (it == m_colorMap.end()) {
        return ccc4(0, 0, 0, 255);
    }
    return it->second;
}
