//
//  CcbEventMainScene.h
//  HelloWorld
//
//  Created by jun on 14-3-11.
//
//

#ifndef __HelloWorld__CcbEventMainScene__
#define __HelloWorld__CcbEventMainScene__

#include <iostream>
#include "CcbEventMainLayer.h"

USING_NS_CC;

class CcbEventMainScene:public CCLayer
{
public:
    CcbEventMainScene();
    ~CcbEventMainScene();
    
    CREATE_FUNC(CcbEventMainScene);
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
#endif /* defined(__HelloWorld__CcbEventMainScene__) */
