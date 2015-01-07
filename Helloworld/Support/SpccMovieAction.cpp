#include "SpccMovieAction.h"

SpccMovieAction::SpccMovieAction(){}
SpccMovieAction::~SpccMovieAction(){}

SpccMovieAction* SpccMovieAction::create(SpccMovieClip *pTarget, uint8 byFps )
{
    SpccMovieAction* ret = new SpccMovieAction();
    if ( ret->init( pTarget, byFps, 0 ) )
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE( ret );
    return NULL;
}

SpccMovieAction* SpccMovieAction::create( SpccMovieClip* pTarget, uint8 byFps,  uint16 startFromFrameIdx )
{
    SpccMovieAction* ret = new SpccMovieAction();
    if ( ret->init( pTarget, byFps, startFromFrameIdx ) )
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE( ret );
    return NULL;
}

bool SpccMovieAction::init(SpccMovieClip *pTarget, uint8 byFps, uint16 startFromFrameIdx )
{
    if ( pTarget == NULL || byFps == 0 ) return false;
    if ( startFromFrameIdx > pTarget->getTotalFrame() ) return false;
    
    m_startFrame = startFromFrameIdx; 
    
    CCActionInterval::initWithDuration( ( pTarget->getTotalFrame() - m_startFrame ) / (float)byFps );
    return true;
}

void SpccMovieAction::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCActionInterval::startWithTarget( pTarget );
    
    SpccMovieClip* mc = dynamic_cast<SpccMovieClip*>(pTarget);
    CCAssert( mc != NULL, "SpccMovieAction Only Support SpccMovieClip As Target!" );
    mc->setFrameIdx( m_startFrame );
}

void SpccMovieAction::stop()
{
    CCActionInterval::stop();
}

void SpccMovieAction::update( float time )
{
    SpccMovieClip* mc = dynamic_cast<SpccMovieClip*>(m_pTarget);
    
    if ( time == 1.0f ) return;
    
    mc->setFrameIdx( m_startFrame + time * ( mc->getTotalFrame() - m_startFrame ) );
}