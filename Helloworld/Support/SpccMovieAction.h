#ifndef __SPCC_MOVIE_ACTION_H__
#define __SPCC_MOVIE_ACTION_H__

#include "cocos2d.h"
#include "SpccMovieClip.h"

USING_NS_CC;

class SpccMovieAction : public CCActionInterval
{
public:
    SpccMovieAction();
    virtual ~SpccMovieAction();
    
public:
    static SpccMovieAction* create( SpccMovieClip* pTarget, uint8 byFps );
    static SpccMovieAction* create( SpccMovieClip* pTarget, uint8 byFps,  uint16 startFromFrameIdx );
    
public:
    
    bool init( SpccMovieClip* pTarget, uint8 byFps, uint16 startFromFrameIdx );
    
    virtual void startWithTarget( CCNode* pTarget );
    
    virtual void stop();
    virtual void update( float time );
    
protected:
    
    uint16 m_startFrame;
    
};


#endif
