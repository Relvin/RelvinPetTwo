//
//  CcbEquipListScene.h
//  HelloWorld
//
//  Created by jun on 14-2-11.
//
//

#ifndef __HelloWorld__CcbEquipListScene__
#define __HelloWorld__CcbEquipListScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbEquipListScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbEquipListScene();
    ~CcbEquipListScene();
    
    CREATE_FUNC(CcbEquipListScene);
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

#endif /* defined(__HelloWorld__CcbEquipListScene__) */
