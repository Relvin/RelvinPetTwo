//
//  CScrollMsgDelegate.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-3-6.}
//
//

#ifndef HelloWorld_CScrollMsgDelegate_h
#define HelloWorld_CScrollMsgDelegate_h

#include "cocos2d.h"
USING_NS_CC;
class CScrollMsgDelegate {
    
public:
    virtual void AddMsg(const char *szName, ccColor3B colorName, const char* szMsg, ccColor3B colorMsg) {};
};

#endif
