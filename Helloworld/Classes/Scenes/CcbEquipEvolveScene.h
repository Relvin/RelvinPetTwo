//
//  CcbEquipEvolveScene.h
//  MyGame
//
//  Created by jun on 14-7-3.
//
//

#ifndef __MyGame__CcbEquipEvolveScene__
#define __MyGame__CcbEquipEvolveScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipEvolveScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbEquipEvolveScene();
    ~CcbEquipEvolveScene();
    
    CREATE_FUNC(CcbEquipEvolveScene);
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

#endif /* defined(__MyGame__CcbEquipEvolveScene__) */
