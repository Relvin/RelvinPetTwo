//
//  Instruments.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-15.}
//
//

#include "Instruments.h"
#include "deelx.h"
#include "Defines.h"
#include "EnumDefines.h"
#include "ConfigGet.h"
#include "PetCtrl.h"
#include "UISupport.h"
#include "d9_base64.h"
#include "ResourceStringClient.h"
//#include "CCUserDefault.h"
#include <sstream>

CCString* getFullTimeFromInt(int dwTime) {
    if (dwTime < 0) {
        dwTime = 0;
    }
    struct tm *t;
    time_t ttime = dwTime;
    t = localtime(&ttime);
    CCString* strTime = CCString::createWithFormat("%04d-%02d-%02d %02d:%02d:%02d",t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return strTime;
}

CCString* getTimeFromInt(int dwTime)
{
    if (dwTime < 0) {
        dwTime = 0;
    }
    struct tm *t;
    time_t ttime = dwTime;
    t = localtime(&ttime);
    CCString* strTime = CCString::createWithFormat("%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
    return strTime;
}

CCString* getLeftTimeFromInt(int dwTime)
{
    if (dwTime < 0) {
        dwTime = 0;
    }
    int hour, minute, second;
    second = dwTime % 60;
    dwTime /= 60;
    minute = dwTime % 60;
    hour = dwTime / 60;
    CCString* strTime = CCString::createWithFormat("%02d:%02d:%02d", hour, minute, second);
    return strTime;
}

CCString* getDayTimeFromInt(uint32 dwTime)
{
    time_t time1 = dwTime;
    struct tm* showTime = localtime(&time1);
//    strftime(szTemp, 60, "%F", showTime);//只显示日期}
    CCString* strTime = CCString::createWithFormat("%04d-%02d-%02d", showTime->tm_year+1900, showTime->tm_mon + 1, showTime->tm_mday);
//    CCString* strTime = CCString::createWithFormat("%04d-%02d-%02d", hour, minute, second);
    return strTime;
}

CCString* getLeftDayTimeChFormatFromInt(uint32 dwTime)
{
    
    std::string tempTime;
    int day, hour, minute, second;
    day = dwTime / 3600 / 24;
    if (day > 0) {
        tempTime = CCString::createWithFormat("%d%s",day,GET_STR(Str_Ch_Day))->getCString();
    }
    hour = dwTime / 3600 % 24;
    if (day > 0 || hour > 0) {
        tempTime += CCString::createWithFormat("%02d%s",hour,GET_STR(Str_Ch_Hour))->getCString();
    }
    
    dwTime %= 3600;
    minute = dwTime / 60;
    if (day > 0 || hour > 0 || minute > 0) {
        tempTime += CCString::createWithFormat("%02d%s",minute,GET_STR(Str_Ch_Min))->getCString();
    }
    second = dwTime % 60;
    
    CCString* strTime = CCString::createWithFormat("%s%02d%s",tempTime.c_str(),second,GET_STR(Str_Ch_Sec));
    return strTime;
}

CCString *getMoneyStrFormat(int money)
{
    if (money < 0) {
        money = 0;
    }
    CCString *moneyString = NULL;
    float temp = money;
    // 2014-01-24 changed by Juniechu, 策划新需求，不要加K和KW了~}
    if (money > 10000000)
    {
        moneyString = CCString::createWithFormat("%.1fkW", temp / 10000000);
    }
    else if(money > 10000)
    {
        if (money / 1000 % 10 == 0)
        {
            moneyString = CCString::createWithFormat("%dW", money / 10000);
        }
        else
        {
            moneyString = CCString::createWithFormat("%.1fW", temp / 10000);
        }
    }
    else if(money > 1000)
    {
        if (money / 100 % 10 == 0)
        {
            moneyString = CCString::createWithFormat("%dK", money / 1000);
        }
        else
        {
            moneyString = CCString::createWithFormat("%.1fK", temp / 1000);
        }
    }
    else
    {
        moneyString = CCString::createWithFormat("%d", money);
    }
    return moneyString;
}

bool checkAccountOk(std::string &strAccount) {
	CRegexpT <char> regexp("([a-zA-Z0-9]|[_]){4,16}$");
	//CRegexpT <char> regexp("([a-zA-Z0-9]|[∞°]){5,10}$");
	// test
	MatchResult result = regexp.MatchExact(strAccount.c_str());
    
	// matched or not
	int nRet = result.IsMatched();
	return nRet ? true : false;
}

bool checkPasswordOk(std::string &strPassword) {
    CRegexpT <char> regexp("([a-zA-Z0-9]|[_]){4,16}$");
    
	// test
	MatchResult result = regexp.MatchExact(strPassword.c_str());
    
	// matched or not
	return result.IsMatched();
}

bool checkMailOk(std::string &strMail) {
    CRegexpT <char> regexp("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
	//CRegexpT <char> regexp("([a-zA-Z0-9]|[∞°]){5,10}$");
	// test
	MatchResult result = regexp.MatchExact(strMail.c_str());
    
	// matched or not
	int nRet = result.IsMatched();
	return nRet ? true : false;
}

int getLocalCurTimeSec() {
    timeval nowTime;
    gettimeofday(&nowTime, NULL);
    int curSec = (int)nowTime.tv_sec;
    return curSec;
}


bool checkInArea(int nvert, CCPoint* vert, CCPoint point) {
    
    // PNPoly Algorithm
    bool c = false;
    for (int i = 0, j = nvert - 1; i < nvert; j = i++) {
        if ( ((vert[i].y > point.y) != (vert[j].y > point.y)) && (point.x < (vert[j].x-vert[i].x)*(point.y-vert[i].y)/(vert[j].y-vert[i].y)+vert[i].x) ) {
            c = !c;
        }
    }
    return c;
}


void d9_encode_save(const char* pKey, std::string str) {
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(pKey, encoded);
}

std::string d9_decode_get(const char* pKey) {
    std::string decoded = CCUserDefault::sharedUserDefault()->getStringForKey(pKey);
    if (decoded == "" || decoded.empty()) {
        return decoded;
    }
    decoded = base64_decode(decoded);
    return decoded;
}

void d9_encode_save(const char* pKey, int k) {
    std::stringstream ss;
    ss << k;
    d9_encode_save(pKey, ss.str());
}

int d9_decode_get_int(const char* pKey) {
    std::string strK = d9_decode_get(pKey);
    if (strK == "" || strK.empty()) {
        return 0;
    }
    return atoi(strK.c_str());
}

std::string cvtInt2String(int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

void cvtPosToScreen(CCPoint& pos) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pos.x += winSize.width*0.5 - 160.0f;
    pos.y += winSize.height*0.5 - 240.0f;
}

int arr1[]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
std::string arr2[]={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};

std::string covert2Roman(uint8 n)
{
    std::string s;
    int i=0;
    while(n){
        if(n>=arr1[i]){
            n-=arr1[i];
            s+=arr2[i];
        }
        else {
            i++;
        }
    }
    return s;
}

