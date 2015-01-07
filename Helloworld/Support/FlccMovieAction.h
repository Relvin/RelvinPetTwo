#ifndef __FLCC_MOVIE_ACTION_H__
#define __FLCC_MOVIE_ACTION_H__

#include "cocos2d.h"
#include "FlccMovieClip.h"

USING_NS_CC;

#define FLCC_ACT_STAND  "Action_Stand"
#define FLCC_ACT_ATTACK "Action_Attack"
#define FLCC_ACT_WAIT   "Action_Wait"

class FlccMovieAction : public CCActionInterval
{
public:
    FlccMovieAction();
    virtual ~FlccMovieAction();
    
public:
    virtual void startWithTarget( CCNode* pTarget );
    
    //virtual bool isDone();
    
    //virtual void step( float dt );
    virtual void stop();
    virtual void update( float time );
    
    bool initWithActionName( FlccMovieClip* pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast );
    
    virtual CCActionInterval* reverse();
    
public:
    static FlccMovieAction* create( FlccMovieClip* pTarget, const std::string actionName );
    static FlccMovieAction* create( FlccMovieClip* pTarget, const std::string actionName, bool bRestart );
    static FlccMovieAction* create( FlccMovieClip* pTarget, const std::string actionName, bool bRestart, uint16 wFrameLast );
    
private:
    std::string m_strActionName;
    float       m_fLastUpdate;
    bool        m_bRestart;
    uint16      m_wFrameLast;
    
    FlccMovieClip* m_myTarget;
};


#endif
