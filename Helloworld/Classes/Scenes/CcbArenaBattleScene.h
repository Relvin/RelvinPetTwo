//
//  CcbArenaBattleScene.h
//  HelloWorld
//
//  Created by jun on 13-11-6.
//
//

#ifndef __HelloWorld__CcbArenaBattleScene__
#define __HelloWorld__CcbArenaBattleScene__

#include <iostream>
#include "CcbArenaBattleLayer.h"

USING_NS_CC;

class CcbArenaBattleScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbArenaBattleScene();
    ~CcbArenaBattleScene();
    
    CREATE_FUNC(CcbArenaBattleScene);
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

#endif /* defined(__HelloWorld__CcbArenaBattleScene__) */
