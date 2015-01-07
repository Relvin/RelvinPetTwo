//
//  CcbArenaRankScene.h
//  HelloWorld
//
//  Created by jun on 13-11-6.
//
//

#ifndef __HelloWorld__CcbArenaRankScene__
#define __HelloWorld__CcbArenaRankScene__

#include <iostream>
#include "CcbArenaRankLayer.h"

USING_NS_CC;

class CcbArenaRankScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbArenaRankScene();
    ~CcbArenaRankScene();
    
    CREATE_FUNC(CcbArenaRankScene);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    CCLabelTTF* m_pLabelTTFName;
};

#endif /* defined(__HelloWorld__CcbArenaRankScene__) */
