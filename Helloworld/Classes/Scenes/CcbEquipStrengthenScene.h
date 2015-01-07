//
//  CcbEquipStrengthenScene.h
//  HelloWorld
//
//  Created by jun on 14-2-17.
//
//

#ifndef __HelloWorld__CcbEquipStrengthenScene__
#define __HelloWorld__CcbEquipStrengthenScene__

#include <iostream>
#include "CcbEquipStrengthenLayer.h"

USING_NS_CC;

class CcbEquipStrengthenScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbEquipStrengthenScene();
    ~CcbEquipStrengthenScene();
    
    CREATE_FUNC(CcbEquipStrengthenScene);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode);
    static cocos2d::CCScene* scene();
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
};

#endif /* defined(__HelloWorld__CcbEquipStrengthenScene__) */
