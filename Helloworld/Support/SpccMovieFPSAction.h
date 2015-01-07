//
//  SpccMovieFPSAction.h
//  HelloWorld
//
//  Created by long on 13-9-29.
//
//

#ifndef __HelloWorld__SpccMovieFPSAction__
#define __HelloWorld__SpccMovieFPSAction__

#include "cocos2d.h"
#include "SpccMovieClip.h"

USING_NS_CC;

class SpccMovieFPSAction : public CCNode
{
public:
    SpccMovieFPSAction();
    virtual ~SpccMovieFPSAction();
    
public:
    static SpccMovieFPSAction* create( SpccMovieClip* pTarget, uint8 byFps );
    static SpccMovieFPSAction* create( SpccMovieClip* pTarget, uint8 byFps,  uint16 startFromFrameIdx );
    
public:
    
    bool init( SpccMovieClip* pTarget, uint8 byFps, uint16 startFromFrameIdx );
    
    void startWithTarget();
    
    void stop();
    void update( float time );
    
    void pause(int frame);
protected:
    SpccMovieClip *m_myTarget;
    uint16 m_startFrame;
    uint16 stopFrame;
    uint16 m_Fps;
};

#endif /* defined(__HelloWorld__SpccMovieFPSAction__) */
