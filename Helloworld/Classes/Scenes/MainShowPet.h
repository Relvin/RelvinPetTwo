//
//  MainShowPet.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-1-8.}
//
//

#ifndef __HelloWorld__MainShowPet__
#define __HelloWorld__MainShowPet__

#include "cocos2d.h"
#include "Defines.h"
#include "SequencePet.h"
USING_NS_CC;

class MainShowPet : public CCLayerRGBA {
    
public:
    MainShowPet();
    ~MainShowPet();
    
    static MainShowPet* create(uint16 wPetIndex);
    bool init(uint16 wPetIndex);
    void onEnter();
    void onExit();
    
    void playAttackAction();
    void playStandAction();

    virtual void setOpacity(GLubyte opacity);
    
public:
    SequencePet* pMc;
    uint16 m_wPetIndex;
    bool bPlayIng;
    
private:
    void stopAttackAction();
    void onAttack();
};

#endif /* defined(__HelloWorld__MainShowPet__) */
