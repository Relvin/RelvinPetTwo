//
//  LRActionInterval.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-31.}
//
//

#ifndef __HelloWorld__LRActionInterval__
#define __HelloWorld__LRActionInterval__

#include "cocos2d.h"

USING_NS_CC;

// 定义一个结构来包含确定椭圆的参数}
typedef struct _lrTuoyuanConfig {
	//中心点坐标}
	CCPoint centerPosition;
	//椭圆a长，三角斜边}
	float aLength;
	//椭圆c长，三角底边}
	float cLength;
} lrTuoyuanConfig;

class   LRTuoyuanBy : public CCActionInterval
{
public:
    //用“动作持续时间”和“椭圆控制参数”初始化动作}
    bool initWithDuration(float t, const lrTuoyuanConfig& c, float delta);
    virtual void update(float time);//利用update函数来不断的设定坐标}
public:
    //用“动作持续时间”和“椭圆控制参数”创建动作}
    static LRTuoyuanBy* create(float t, const lrTuoyuanConfig& c, float delta);
    
protected:
    lrTuoyuanConfig m_sConfig;
    float m_fDelta;
//    CCPoint m_startPosition;
//    CCPoint s_startPosition;
};

#endif /* defined(__HelloWorld__LRActionInterval__) */
