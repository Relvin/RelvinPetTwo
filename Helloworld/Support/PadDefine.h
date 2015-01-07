//
//  PadDefine.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-8-29.}
//
//

#ifndef __MyGame__PadDefine__
#define __MyGame__PadDefine__

#include "ccTypes.h"


typedef enum {
    kBrown,
    kRed,
    kBlue,
    kYellow,
} D9PadTextColor;
/*!
 0 -- 棕色}
 1 -- 红色
 2 -- 蓝色
 3 -- 黄色
 */
static const ccColor3B padColorArr[] = {{19, 15, 15}, ccRED, ccBLUE, ccYELLOW};

/*!
 0 -- 小智
 1 -- 皮卡丘
 2 -- 喵喵
 */
typedef enum {
    kXiaozhi,
    kPikaqiu,
    kMiaomiao,
    kWuzang,
    kXiaocilang,
    kDamowang,
} D9PadHeadPic;

/*!
 0 -- 居左
 1 -- 居右
 */
typedef enum {
    kLeftOff,
    kRightOff,
} D9PadPicOffset;

#endif /* defined(__MyGame__PadDefine__) */
