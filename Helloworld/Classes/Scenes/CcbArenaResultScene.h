//
//  CcbArenaResultScene.h
//  HelloWorld
//
//  Created by jun on 14-1-13.
//
//

#ifndef __HelloWorld__CcbArenaResultScene__
#define __HelloWorld__CcbArenaResultScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CcbArenaResultScene:public CCLayer
{
public:
    CcbArenaResultScene();
    ~CcbArenaResultScene();
    
    CREATE_FUNC(CcbArenaResultScene);
    //virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    
};

#endif /* defined(__HelloWorld__CcbArenaResultScene__) */
