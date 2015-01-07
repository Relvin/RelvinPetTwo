//
//  CcbAchieveRewardScene.h
//  HelloWorld
//
//  Created by jun on 14-4-4.
//
//

#ifndef __HelloWorld__CcbAchieveRewardScene__
#define __HelloWorld__CcbAchieveRewardScene__

//#include <iostream>
//#include "CcbAchieveRewardLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbAchieveRewardScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbAchieveRewardScene();
    ~CcbAchieveRewardScene();
    
    CREATE_FUNC(CcbAchieveRewardScene);
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
#endif /* defined(__HelloWorld__CcbAchieveRewardScene__) */
