//
//  FlccMovieFPSAction.h
//  HelloWorld
//
//  Created by long on 13-9-23.
//
//

#ifndef __HelloWorld__FlccMovieFPSAction__
#define __HelloWorld__FlccMovieFPSAction__

#include <iostream>
#include "cocos2d.h"
#include "FlccMovieClip.h"


class FlccMovieFPSAction : public CCNode
{
public:
    FlccMovieFPSAction();
    virtual ~FlccMovieFPSAction();
    
public:
//    virtual void startWithTarget( CCNode* pTarget );
    
    //virtual bool isDone();
    
    //virtual void step( float dt );
//    virtual void stop();
//    virtual void update( float time );
    
    bool initWithActionName( FlccMovieClip* pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast );
    
//    virtual CCActionInterval* reverse();
    
    void startWithTarget();
    
    void pause(int frame);
    
    void stop();
    
public:
    static FlccMovieFPSAction* create( FlccMovieClip* pTarget, const std::string actionName );
    static FlccMovieFPSAction* create( FlccMovieClip* pTarget, const std::string actionName, bool bRestart );
    static FlccMovieFPSAction* create( FlccMovieClip* pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast );
    
private:
    std::string m_strActionName;
    float       m_fLastUpdate;
    bool        m_bRestart;
    uint16      m_wFrameLast;
    uint16      m_wCurFrame;
    void update(float time);
    int stopFrame;
    FlccMovieClip* m_myTarget;
    CCCallFunc *m_CallFunc;
};


#endif /* defined(__HelloWorld__FlccMovieFPSAction__) */
