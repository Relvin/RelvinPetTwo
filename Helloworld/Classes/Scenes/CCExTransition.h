//
//  CCExTransition.h
//  MyGame
//
//  Created by 朱 俊杰 on 14-6-24.}
//
//

#ifndef __MyGame__CCExTransition__
#define __MyGame__CCExTransition__

#include "cocos2d.h"
USING_NS_CC;

class CCTransitionFog : public CCTransitionScene {
    
public:
    CCTransitionFog();
    virtual ~CCTransitionFog();
    
    static CCTransitionFog* create(float duration, CCScene* scene);
    
    virtual bool initWithDuration(float t, CCScene* scene);
    virtual void onEnter();
    virtual void onExit();
};


class CCTransitionLoading : public CCTransitionScene {
    
public:
    CCTransitionLoading();
    virtual ~CCTransitionLoading();
    
    static CCTransitionLoading* create(float duration, CCScene* scene);
    
    virtual bool initWithDuration(float t, CCScene* scene);
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MyGame__CCExTransition__) */
