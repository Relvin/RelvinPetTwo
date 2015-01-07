//
//  CcbEquipCompoundScene.h
//  HelloWorld
//
//  Created by jun on 14-2-17.
//
//

#ifndef __HelloWorld__CcbEquipCompoundScene__
#define __HelloWorld__CcbEquipCompoundScene__

#include <iostream>
#include "CcbEquipCompoundListLayer.h"

USING_NS_CC;

class CcbEquipCompoundListScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbEquipCompoundListScene();
    ~CcbEquipCompoundListScene();
    
    CREATE_FUNC(CcbEquipCompoundListScene);
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


#endif /* defined(__HelloWorld__CcbEquipCompoundScene__) */
