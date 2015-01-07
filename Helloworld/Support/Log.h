//
//  Log.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-23.}
//
//

#ifndef HelloWorld_Log_h
#define HelloWorld_Log_h

#include "cocos2d.h"

#define IME_LOG( fmt, ...) CCLOG( fmt, ##__VA_ARGS__)
#define IME_ERROR( fmt, ... ) CCLOGERROR( fmt, ##__VA_ARGS__ )

#endif
