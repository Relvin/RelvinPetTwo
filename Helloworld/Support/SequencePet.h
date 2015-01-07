//
//  Sequence.h
//  HelloWorld
//
//  Created by long on 14-1-19.
//
//

#ifndef __HelloWorld__SequencePet__
#define __HelloWorld__SequencePet__

#include <iostream>
#include "cocos2d.h"
#include "Defines.h"
#include "SequenceAction.h"
#define seq_fps 12
USING_NS_CC;

class FightPetSprite;

class SequencePet : public CCSprite
{
public:
    SequencePet();
    //析构时注意清内存}
    ~SequencePet();
    //根据petId读序列帧图进内存}
    static SequencePet* create(uint32 petId);
    
    bool init(uint32 petId);
    //设置帧率}
    void setFPS(uint16 fps);
    uint16 getFPS(){return m_wFps;};
    //runAction 就用sprite自带的就OK了，还能有回调}
    
    uint32 getPetId(){return m_petId;};
    
    CCSprite *getStandPic();
    
    //按帧执行的动画}
    void runFPSAction(SequenceFPSAction *action, FightPetSprite *pet);
    void callBackFPSAction();
private:
    uint16 m_wFps;
    uint32 m_petId;
    SequenceFPSAction *m_fpsAction;
    FightPetSprite *m_FightPetSprite;
};
#endif /* defined(__HelloWorld__Sequence__) */
