//
//  CcbCache.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-8-11.}
//
//

#ifndef __MyGame__CcbCache__
#define __MyGame__CcbCache__

#include <iostream>
#include "cocos-ext.h"
#include <map>
#include <string>

USING_NS_CC_EXT;

class CcbCache {
    
public:
    static std::map<std::string, CCData*> m_mapData;
    
    static void clearDataMap();
    static void addDataToMap(std::string pKey, CCData* pData);
    static CCData* getDataFromMapWithKey(std::string pKey);
};

#endif /* defined(__MyGame__CcbCache__) */
