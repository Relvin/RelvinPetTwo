//
//  Item.h
//  HelloWorld
//
//  Created by jun on 14-1-23.
//
//

#ifndef __HelloWorld__Item__
#define __HelloWorld__Item__

#include <iostream>
#include "Defines.h"
#include "ConfigGet.h"

using namespace std;

#define ITEM_SYNTHESIZE(varType, varName, funName)  \
private:                                            \
    varType varName;                                \
public:                                             \
    void Set##funName(varType var){ varName = var; }\
    varType Get##funName(void) const { return varName; }

class CItem
{
public:
    CItem();
    ~CItem();
    
    ITEM_SYNTHESIZE(uint32, m_dwIndex, Index);     //ID}
    ITEM_SYNTHESIZE(uint32, m_dwCount, Count);     //数量}
    
public:
    void AddConfigData();
    ITEM_CONFIG_DATA GetConfigData() const;
private:
    ITEM_CONFIG_DATA m_ConfigData;
    
};


#endif /* defined(__HelloWorld__Item__) */
