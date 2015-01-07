//
//  Rune.h
//  HelloWorld
//
//  Created by jun on 14-1-23.
//
//

#ifndef __HelloWorld__Rune__
#define __HelloWorld__Rune__

#include <iostream>
#include "Defines.h"
#include "ConfigGet.h"

using namespace std;

#define RUNE_SYNTHESIZE(varType, varName, funName)  \
private:                                            \
varType varName;                                \
public:                                             \
void Set##funName(varType var){ varName = var; }\
varType Get##funName(void) const { return varName; }


class CRune
{
public:
    CRune();
    ~CRune();
    
public:
    void AddConfigData();
    RUNE_CONFIG_DATA GetConfigData() const;
private:
    RUNE_CONFIG_DATA m_ConfigData;
    
//    RUNE_SYNTHESIZE(uint32, m_dwKeyID, KeyID);//唯一标识}
    RUNE_SYNTHESIZE(uint32, m_dwIndex, Index);//物品索引}
    RUNE_SYNTHESIZE(uint32, m_dwCnt, Cnt);//物品数量}
//    RUNE_SYNTHESIZE(uint32, m_dwWearEquipID, WearEquipID);//穿在装备上的装备KeyID}
};

#endif /* defined(__HelloWorld__Rune__) */
