#ifndef __SPCC_DATA_H__
#define __SPCC_DATA_H__

#include "Defines.h"
#include <vector>

typedef struct EffectFrameInfo
{
    int8 byPngIdx;
    int32 dwOffsetX;
    int32 dwOffsetY;
    
} EffectFrameInfo;

typedef struct SpccEffectConfig
{
    std::vector<EffectFrameInfo> frames;
    float lessScale;
    
} SpccEffectConfig;



#endif
