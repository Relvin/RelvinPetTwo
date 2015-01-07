//
//  SpccMovieFPSAction.cpp
//  HelloWorld
//
//  Created by long on 13-9-29.
//
//

#include "SpccMovieFPSAction.h"

SpccMovieFPSAction::SpccMovieFPSAction()
:stopFrame(0)
{
    
}
SpccMovieFPSAction::~SpccMovieFPSAction()
{
    m_myTarget = NULL;
}

SpccMovieFPSAction* SpccMovieFPSAction::create(SpccMovieClip *pTarget, uint8 byFps )
{
    SpccMovieFPSAction* ret = new SpccMovieFPSAction();
    if ( ret->init( pTarget, byFps, 0 ) )
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE( ret );
    return NULL;
}

SpccMovieFPSAction* SpccMovieFPSAction::create( SpccMovieClip* pTarget, uint8 byFps,  uint16 startFromFrameIdx )
{
    SpccMovieFPSAction* ret = new SpccMovieFPSAction();
    if ( ret->init( pTarget, byFps, startFromFrameIdx ) )
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE( ret );
    return NULL;
}

bool SpccMovieFPSAction::init(SpccMovieClip *pTarget, uint8 byFps, uint16 startFromFrameIdx )
{
    if ( pTarget == NULL || byFps == 0 ) return false;
    if ( startFromFrameIdx > pTarget->getTotalFrame() ) return false;
    
    m_myTarget = pTarget;
    m_Fps = byFps;
    m_startFrame = startFromFrameIdx;
    
//    CCActionInterval::initWithDuration( ( pTarget->getTotalFrame() - m_startFrame ) / (float)byFps );
    return true;
}

void SpccMovieFPSAction::startWithTarget()
{
//    CCActionInterval::startWithTarget( pTarget );
    
    SpccMovieClip* mc = dynamic_cast<SpccMovieClip*>(m_myTarget);
    CCAssert( mc != NULL, "SpccMovieFPSAction Only Support SpccMovieClip As Target!" );
    mc->setFrameIdx( m_startFrame );
    schedule(schedule_selector(SpccMovieFPSAction::update), 1.0/m_Fps);
}

void SpccMovieFPSAction::stop()
{
//    CCActionInterval::stop();
    unschedule(schedule_selector(SpccMovieFPSAction::update));
    this->removeFromParent();
}

void SpccMovieFPSAction::pause(int frame)
{
    stopFrame = frame;
}

void SpccMovieFPSAction::update( float time )
{
    if (stopFrame < 0) {
        return;
    }
    
    if (stopFrame > 0) {
        stopFrame--;
        return;
    }
    SpccMovieClip* mc = dynamic_cast<SpccMovieClip*>(m_myTarget);
    uint16 frameIdx = mc->getCurFrame();
    frameIdx++;
    CCLOG("SpccMovieClip Frame:%d", frameIdx);
    if (frameIdx >= mc->getTotalFrame()) {
        stop();
        return;
    }
    mc->setFrameIdx(frameIdx);
//    SpccMovieClip* mc = dynamic_cast<SpccMovieClip*>(m_pTarget);
//    
//    if ( time == 1.0f ) return;
    
//    mc->setFrameIdx( m_startFrame + time * ( mc->getTotalFrame() - m_startFrame ) );
}
