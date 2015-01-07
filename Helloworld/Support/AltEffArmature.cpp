//
//  AltEffArmature.cpp
//  MyGame
//
//  Created by long on 14/10/21.
//
//

#include "AltEffArmature.h"

AltEffArmature *AltEffArmature::create(const char* path, const char* name)
{
    // remove sigle resource
//    CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(path);
    
    // load resource directly
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(path);
    
    AltEffArmature *armature = new AltEffArmature();
    if (armature && armature->init(name))
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}
/**
 *  @js ctor
 */
AltEffArmature::AltEffArmature()
{
    
}
/**
 *  @js NA
 */
AltEffArmature::~AltEffArmature(void)
{
    
}

bool AltEffArmature::init(const char *name)
{
    if(!CCArmature::init(name))
    {
        return false;
    }
    getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(AltEffArmature::movemetEvent));
    return true;
}

void AltEffArmature::onEnter()
{
    CCArmature::onEnter();
    getAnimation()->play("act_eff");
    
}

void AltEffArmature::movemetEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID)
{
    if (movementType == COMPLETE) {
        armature->getAnimation()->setMovementEventCallFunc(NULL, NULL);
        if (strcmp(movementID, "act_eff") == 0) {
            armature->getAnimation()->stop();
            armature->removeFromParentAndCleanup(true);
        }
    }
}