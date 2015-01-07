#include "FlccMovieAction.h"

FlccMovieAction::FlccMovieAction()
{
    
}

FlccMovieAction::~FlccMovieAction()
{
    
}

FlccMovieAction* FlccMovieAction::create(FlccMovieClip *pTarget, const std::string actionName)
{
//    FlccMovieAction* pAction = new FlccMovieAction();
//    pAction->initWithActionName( pTarget, actionName, true, pTarget->getTotalFrameOf( actionName ) );
//    pAction->autorelease();
//    
//    return pAction;
    
    return create(pTarget, actionName, true, pTarget->getTotalFrameOf(actionName) );
}

FlccMovieAction* FlccMovieAction::create( FlccMovieClip* pTarget, const std::string actionName, bool bRestart )
{
//    FlccMovieAction* pAction = new FlccMovieAction();
//    pAction->initWithActionName( pTarget, actionName, bRestart, pTarget->getTotalFrameOf( actionName ) );
//    pAction->autorelease();
//    
//    return pAction;
    return create(pTarget, actionName, bRestart, pTarget->getTotalFrameOf(actionName) );
}

FlccMovieAction* FlccMovieAction::create(FlccMovieClip *pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast )
{
    FlccMovieAction* pAction = new FlccMovieAction();
    pAction->initWithActionName( pTarget, actionName, bRestart,wFrameLast );
    pAction->autorelease();
    
    return pAction;
}

bool FlccMovieAction::initWithActionName( FlccMovieClip* pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast )
{
    m_myTarget      = pTarget;
    m_strActionName = actionName;
    m_fLastUpdate   = -1;
    
    if ( bRestart )
    {
        m_fDuration = pTarget->getTotalFrameOf( actionName ) * pTarget->secondPerFrame();
    }
    else 
    {
        m_fDuration = pTarget->secondPerFrame() * wFrameLast;
    }
    
    m_bRestart      = bRestart;
    m_wFrameLast    = wFrameLast;
    
    return true;
}

void FlccMovieAction::startWithTarget( CCNode* pTarget )
{
    //CCLog( "Start Action [%s]", m_strActionName.c_str() ); 
    
    CCActionInterval::startWithTarget( pTarget );
    FlccMovieClip* mc = (FlccMovieClip*)m_myTarget;
    
    CCAssert( mc != NULL, "FlccMovieAction Only Support FlccMovieClip As Target!" );
    
    mc->setAction( m_strActionName, false, m_bRestart );
}

//bool FlccMovieAction::isDone()
//{
//    FlccMovieClip* mc = (FlccMovieClip*)m_pTarget;
    	
    
    //CCLog( "%s\t[%d/%d]", m_strActionName.c_str(), mc->getCurrentFrame(), mc->getTotalFrame() );
    //if ( mc->getCurrentFrame() >= mc->getTotalFrame() )
    //{
    //    CCLog( "Finish Action [%s]", m_strActionName.c_str() );
    //}
    
//    return mc->getCurrentFrame() >= m_wToFrameIdx;
//}

/*
void FlccMovieAction::step(float dt)
{
    if ( m_bFirstTick )
    {
        m_bFirstTick = false;
        ( (FlccMovieClip*)m_pTarget )->updateMovieClip();
    }
    else 
    {
        m_elapsed += dt;
    }
    ( (FlccMovieClip*)m_pTarget )->updateMovieClip( dt );
}
*/
CCActionInterval* FlccMovieAction::reverse()
{
    CCAssert( false , "reverse NOT SUPPORT in FlccMovieAction" );
    return NULL;
}

void FlccMovieAction::stop()
{
    //CCLog( "Stop Action [%s]", m_strActionName.c_str() );
    
    CCActionInterval::stop();
    m_fLastUpdate = -1;
}

void FlccMovieAction::update(float time)
{
//    CCLog("         FlccMovieAction time : %f", time);
    FlccMovieClip* mc = (FlccMovieClip*)m_myTarget;
    
    if ( m_fLastUpdate < 0 || time < m_fLastUpdate )
    {
        mc->updateMovieClip();
    }
    else 
    {
        if (m_strActionName == FLCC_ACT_WAIT) {
            CCLog("11111111");
        }
        mc->updateMovieClip( (time - m_fLastUpdate) * m_fDuration );
    }
    m_fLastUpdate = time;
    
    if (m_strActionName == FLCC_ACT_WAIT) {
        CCLog( "%s\t[%f  %d/%d]", m_strActionName.c_str(), time, mc->getCurrentFrame(), mc->getTotalFrame() );
    }
    
}
