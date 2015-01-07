//
//  HttpLog.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-2-8.}
//
//

#ifndef __HelloWorld__HttpLog__
#define __HelloWorld__HttpLog__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class HttpLog : public CCLayer {
    
    CREATE_FUNC(HttpLog);
    
    void onRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    
    HttpLog();
    ~HttpLog();
    
public:
    virtual bool init();
    virtual void onExit();
    
    static HttpLog* GetInstance();
    
    void addLogInfo(string key, string value);
    void sendLogInfo();
private:
    static HttpLog* m_pShared;
    CCDictionary* m_pReqDic;
};

#endif /* defined(__HelloWorld__HttpLog__) */
