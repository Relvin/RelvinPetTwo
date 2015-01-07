//
//  CcbAwardCenterScene.h
//  HelloWorld
//
//  Created by jun on 14-4-4.
//
//

#ifndef __HelloWorld__CcbAwardCenterScene__
#define __HelloWorld__CcbAwardCenterScene__

#include <iostream>
#include "CcbAwardCenterLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbAwardCenterScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbAwardCenterScene();
    ~CcbAwardCenterScene();
    
    CREATE_FUNC(CcbAwardCenterScene);
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

#endif /* defined(__HelloWorld__CcbAwardCenterScene__) */
