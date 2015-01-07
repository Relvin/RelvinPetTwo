//
//  Instruments.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-15.}
//
//

#ifndef __HelloWorld__Instruments__
#define __HelloWorld__Instruments__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;

CCString* getTimeFromInt(int dwTime);
CCString* getLeftTimeFromInt(int dwTime);
CCString* getMoneyStrFormat(int money);
CCString* getFullTimeFromInt(int dwTime);
CCString* getDayTimeFromInt(uint32 dwTime);
CCString* getLeftDayTimeChFormatFromInt(uint32 dwTime);

bool checkAccountOk(std::string &strAccount);
bool checkPasswordOk(std::string &strPassword);
bool checkMailOk(std::string &strMail);

/*!
 @brief 获得本地时间的秒数
 */
int getLocalCurTimeSec();

bool checkInArea(int nvert, CCPoint* vert, CCPoint point);


void d9_encode_save(const char* pKey, std::string str);
std::string d9_decode_get(const char* pKey);

void d9_encode_save(const char* pKey, int k);
int d9_decode_get_int(const char* pKey);

std::string cvtInt2String(int n);

void cvtPosToScreen(CCPoint& pos);

std::string covert2Roman(uint8 num);
#endif /* defined(__HelloWorld__Instruments__) */
