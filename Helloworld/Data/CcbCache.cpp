//
//  CcbCache.cpp
//  MyGame
//
//  Created by 朱 俊杰 on 14-8-11.}
//
//

#include "CcbCache.h"

std::map<std::string, CCData*> CcbCache::m_mapData;

void CcbCache::clearDataMap()
{
    std::map<std::string, CCData*>::iterator pIt;
    for (pIt = m_mapData.begin(); pIt != m_mapData.end(); pIt++) {
        CC_SAFE_FREE(pIt->second);
    }
    m_mapData.clear();
    return;
}

void CcbCache::addDataToMap(std::string pKey, cocos2d::extension::CCData *pData)
{
    CCData* dataCopy = new CCData(pData);
    m_mapData.insert(std::make_pair(pKey, dataCopy));
    return;
}

CCData* CcbCache::getDataFromMapWithKey(std::string pKey)
{
    std::map<std::string, CCData*>::iterator pIt;
    pIt = m_mapData.find(pKey);
    
    if (pIt != m_mapData.end()) {
        return pIt->second;
    }
    return NULL;
}


