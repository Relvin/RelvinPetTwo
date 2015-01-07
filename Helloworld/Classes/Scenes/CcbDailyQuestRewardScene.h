//
//  CcbDailyQuestRewardScene.h
//  HelloWorld
//
//  Created by jun on 14-4-4.
//
//

#ifndef __HelloWorld__CcbDailyQuestRewardScene__
#define __HelloWorld__CcbDailyQuestRewardScene__

#include <iostream>
#include "CcbDailyQuestRewardLayer.h"

USING_NS_CC;

class CcbDailyQuestRewardScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbDailyQuestRewardScene();
    ~CcbDailyQuestRewardScene();
    
    CREATE_FUNC(CcbDailyQuestRewardScene);
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
#endif /* defined(__HelloWorld__CcbDailyQuestRewardScene__) */
