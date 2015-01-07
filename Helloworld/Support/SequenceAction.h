//
//  SequenceAction.h
//  HelloWorld
//
//  Created by long on 14-1-19.
//
//

#ifndef __HelloWorld__SequenceAction__
#define __HelloWorld__SequenceAction__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;

#define SEQ_ACT_STAND  "stand"
#define SEQ_ACT_ATTACK "atk"
class SequencePet;

class SequenceAction : public CCAnimate
{
public:
    SequenceAction();
    ~SequenceAction();
    
    static SequenceAction* create(SequencePet* delegate, std::string actName);
    
    bool init(SequencePet* delegate, std::string actName);

private:
    SequencePet* m_delegate;
    std::string curActName;
    
    int m_curFrame;
    float m_frameCT;
    float m_frameTT;
};


class SequenceFPSAction : public CCNode
{
public:
    SequenceFPSAction();
    virtual ~SequenceFPSAction();
    
public:
    bool initWithActionName( SequencePet* pTarget, const std::string actionName);
    void stop();
    
public:
    static SequenceFPSAction* create( SequencePet* pTarget, const std::string actionName );
   
private:
    std::string m_strActionName;
    float       m_fLastUpdate;
    bool        m_bRestart;
    uint16      m_wFrameLast;
    uint16      m_wCurFrame;
    void update(float time);
    int stopFrame;
    SequencePet* m_myTarget;
    CCCallFunc *m_CallFunc;
};
#endif /* defined(__HelloWorld__SequenceAction__) */
