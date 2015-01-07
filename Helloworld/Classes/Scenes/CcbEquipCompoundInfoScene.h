//
//  CcbEquipCompoundInfoScene.h
//  HelloWorld
//
//  Created by jun on 14-2-18.
//
//

#ifndef __HelloWorld__CcbEquipCompoundInfoScene__
#define __HelloWorld__CcbEquipCompoundInfoScene__

#include <iostream>
#include "CcbEquipCompoundInfoLayer.h"

USING_NS_CC;

class CcbEquipCompoundInfoScene
: public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    CcbEquipCompoundInfoScene();
    ~CcbEquipCompoundInfoScene();
    
    CREATE_FUNC(CcbEquipCompoundInfoScene);
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

#endif /* defined(__HelloWorld__CcbEquipCompoundInfoScene__) */
