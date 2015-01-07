//
//  CCFlowFire.h
//  HelloWorld
//
//  Created by long on 14-3-25.
//
//

#ifndef __HelloWorld__CCFlowFire__
#define __HelloWorld__CCFlowFire__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;


class CCFlowFire : public CCLayer
{
public:
    CCFlowFire();
    ~CCFlowFire();
    
    /**
     @brief 默认一个100*100的矩形}
     */
    static CCFlowFire* create();
    
    static CCFlowFire* createCircle(float radius, CCPoint center);
    /**
     @brief arrPoint   必须是大于等于3个点的闭环
     */
    static CCFlowFire* createPolygon(std::vector<CCPoint> arrPoint);
    
    bool init(std::vector<CCPoint> arrPoint);
    
    bool initCircle(float radius, CCPoint center);
    
    virtual void onEnter();
    virtual void onExit();
private:
    int speed;
    float m_radius;
    float m_fAngle;
    CCPoint m_center;
    std::vector<CCPoint> m_arrPoint;
    int curPoint;
    CCParticleSystemQuad *particle1;
    CCParticleSystemQuad *particle2;
//    CCPoint nextPoint;}
    void updateForCircle(float time);
    void actionForPolygon();
};

#endif /* defined(__HelloWorld__CCFlowFire__) */
