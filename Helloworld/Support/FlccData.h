#ifndef __FlccData_h__
#define __FlccData_h__

#include "Defines.h"
#include "cocos2d.h"
#include "string.h"
#include <vector>

USING_NS_CC;

/**
 * //////////////////////
 * ///FLCC FILE FORMAT
 * //////////////////////
 * 
 * // we may use 'modelId_partId_alterId' to find png resouce
 * // we use matrix to make transform
 *
 *              | a  b  0 |
 *  (x, y, 1) * | c  d  0 |
 *              | tx ty 1 | 
 *
 * [uint16] modelId
 * 
 * // Dim Symbol Library
 * [uint16] symbolCount
 * 		[uint8] partId
 * 		[uint8] alterId
 * 		[float] offsetX
 * 		[float] offsetY
 * 
 * // Dim Action
 * [uint8] actionCount
 * 		[string] actionName
 * 		[uint8] totalFrame
 * 		[uint8]	partCount
 * 			[uint8] partId
 * 			(length = totalFrame)
 * 				[float] a
 * 				[float] b
 * 				[float] c
 *              [float] d
 *              [float] tx
 *              [float] ty
 *              [float] alpha
 */

typedef struct FrameInfo
{
    float a;
    float b;
    float c;
    float d;
    float tx;
    float ty;
    
    float alpha;
    uint8 alterId;
    uint8 frameId;
}FrameInfo;

typedef struct SymbolInfo
{
    uint8   partId;
    uint8   alterId;
    uint8   frameId;
    CCPoint offset;
    
} SymbolInfo;

typedef struct PartInfo
{
    uint8                   partId;
    uint8                   zOrder;
    std::vector<FrameInfo>  frames;
    
}PartInfo;

typedef struct ActionInfo
{
    std::string             name;
    uint16                  totalFrame;
    std::vector<PartInfo>   parts;
    
}ActionInfo;

typedef struct FlccAnimationConfig
{
    uint16                  modelId;
    std::vector<SymbolInfo> symbols;
    std::vector<ActionInfo> actions;
    float                   lessScale;
    
}FlccAnimationConfig;

#endif
