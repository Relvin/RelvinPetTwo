//
//  CcbArenaIndexScene.h
//  HelloWorld
//
//  Created by jun on 13-11-6.
//
//

#ifndef HelloWorld_CcbArenaIndexScene_h
#define HelloWorld_CcbArenaIndexScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbArenaIndexLayer.h"
#include "Defines.h"
#include "ByteBuffer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaIndexScene : public cocos2d::CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbArenaIndexScene();
    ~CcbArenaIndexScene();
    
    CREATE_FUNC(CcbArenaIndexScene);
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

#endif
