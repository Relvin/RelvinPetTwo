//
//  ReCountDown.h
//  MyGame
//
//  Created by Relvin on 14/11/4.
//
//

#ifndef __MyGame__ReCountDown__
#define __MyGame__ReCountDown__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"


class ReCountDownDelegate
{
public:
    typedef enum _CountType
    {
        ENUM_START,
        ENUM_UPDATE,
        ENUM_COMPLETE,
    }CountType;
    virtual void countDownScheduleCallBack(float cTime,CountType type);
};

class ReCountDown
:public cocos2d::CCNode
{
public:
    
    ReCountDown();
    virtual ~ReCountDown();
    static ReCountDown* create();
    static ReCountDown* create(cocos2d::CCLabelTTF* object);
    
    void initCountDownNode(cocos2d::CCLabelTTF* object);
    
    virtual void onEnter();
    virtual void onExit();
    void setTime(int ttime);
    void scheduleCountDown(float cTime);
    void updateCountDown(float cTime);
    void startUpdateCountDown();
    void stopUpdateCountDown();
    cocos2d::CCLabelTTF      *_label;
    int                 time;
    void setDelegate(ReCountDownDelegate *_delegate) {m_pDelegate = _delegate;};
private:
    ReCountDownDelegate *m_pDelegate;
};


#endif /* defined(__MyGame__ReCountDown__) */
