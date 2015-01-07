//
//  FlccMovieFPSAction.cpp
//  HelloWorld
//
//  Created by long on 13-9-23.
//
//

#include "FlccMovieFPSAction.h"

FlccMovieFPSAction::FlccMovieFPSAction()
{
    
}

FlccMovieFPSAction::~FlccMovieFPSAction()
{
    
}

FlccMovieFPSAction* FlccMovieFPSAction::create(FlccMovieClip *pTarget, const std::string actionName)
{
    FlccMovieFPSAction* pAction = new FlccMovieFPSAction();
    pAction->initWithActionName( pTarget, actionName, true, pTarget->getTotalFrameOf( actionName ) );
    pAction->autorelease();
    
    return pAction;
}

FlccMovieFPSAction* FlccMovieFPSAction::create( FlccMovieClip* pTarget, const std::string actionName, bool bRestart )
{
    FlccMovieFPSAction* pAction = new FlccMovieFPSAction();
    pAction->initWithActionName( pTarget, actionName, bRestart, pTarget->getTotalFrameOf( actionName ) );
    pAction->autorelease();
    
    return pAction;
}

FlccMovieFPSAction* FlccMovieFPSAction::create(FlccMovieClip *pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast )
{
    FlccMovieFPSAction* pAction = new FlccMovieFPSAction();
    pAction->initWithActionName( pTarget, actionName, bRestart,wFrameLast );
    pAction->autorelease();
    
    return pAction;
}

bool FlccMovieFPSAction::initWithActionName( FlccMovieClip* pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast )
{
    m_myTarget      = pTarget;
    m_strActionName = actionName;
    m_fLastUpdate   = -1;
    
//    if ( bRestart )
//    {
//        m_fDuration = pTarget->getTotalFrameOf( actionName ) * pTarget->secondPerFrame();
//    }
//    else
//    {
//        m_fDuration = pTarget->secondPerFrame() * wFrameLast;
//    }
    
    m_bRestart      = bRestart;
    m_wFrameLast    = wFrameLast;
    m_wCurFrame     = 0;
    stopFrame       = 0;
    return true;
}

void FlccMovieFPSAction::startWithTarget()
{
//    m_CallFunc = NULL;
//    m_CallFunc = callFunc;
    //CCLog( "Start Action [%s]", m_strActionName.c_str() );
    
//    CCActionInterval::startWithTarget( pTarget );
    FlccMovieClip* mc = (FlccMovieClip*)m_myTarget;
    
//    CCAssert( mc != NULL, "FlccMovieFPSAction Only Support FlccMovieClip As Target!" );
    
    mc->setAction( m_strActionName, false, m_bRestart );
    
    schedule(schedule_selector(FlccMovieFPSAction::update), 1.0 / mc->getFPS());
}


//CCActionInterval* FlccMovieFPSAction::reverse()
//{
//    CCAssert( false , "reverse NOT SUPPORT in FlccMovieFPSAction" );
//    return NULL;
//}
//
//void FlccMovieFPSAction::stop()
//{
//    //CCLog( "Stop Action [%s]", m_strActionName.c_str() );
//    
//    CCActionInterval::stop();
//    m_fLastUpdate = -1;
//}

void FlccMovieFPSAction::update(float time)
{
    if (stopFrame < 0) {
        return;
    }
    
    if (stopFrame > 0) {
        stopFrame--;
        return;
    }
    
    CCLog("     FlccMovieFPSAction  :  %d", m_wCurFrame);
    if (m_wCurFrame > m_wFrameLast) {
        if (m_myTarget) {
            m_myTarget->callBackFPSAction();
        }
        stop();
        return;
    }    

    FlccMovieClip* mc = (FlccMovieClip*)m_myTarget;

    mc->updateMovieClip(1.0/mc->getFPS());
    
    m_wCurFrame++;
//    if ( m_fLastUpdate < 0 || time < m_fLastUpdate )
//    {
//        mc->updateMovieClip();
//    }
//    else
//    {
////        mc->updateMovieClip( (time - m_fLastUpdate) * m_fDuration );
//    }
//    m_fLastUpdate = time;
    
    
    //CCLog( "%s\t[%f  %d/%d]", m_strActionName.c_str(), time, mc->getCurrentFrame(), mc->getTotalFrame() );
}

void FlccMovieFPSAction::pause(int frame)
{
    stopFrame = frame;
}

void FlccMovieFPSAction::stop()
{
    unschedule(schedule_selector(FlccMovieFPSAction::update));
    this->removeFromParent();
}
