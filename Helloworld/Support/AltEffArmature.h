//
//  AltEffArmature.h
//  MyGame
//
//  Created by long on 14/10/21.
//
//

#ifndef __MyGame__AltEffArmature__
#define __MyGame__AltEffArmature__

#include <stdio.h>

#include "cocos2d.h"
#include "Defines.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class AltEffArmature : public CCArmature
{
public:
    static AltEffArmature *create(const char* path, const char* name);
    /**
     *  @js ctor
     */
    AltEffArmature();
    /**
     *  @js NA
     */
    ~AltEffArmature(void);
    virtual bool init(const char *name);
    
    virtual void onEnter();
private:
    void movemetEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
    
};

#endif /* defined(__MyGame__AltEffArmature__) */
