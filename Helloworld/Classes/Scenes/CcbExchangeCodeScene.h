//
//  CcbExchangeCodeScene.h
//  HelloWorld
//
//  Created by jun on 14-4-22.
//
//

#ifndef __HelloWorld__CcbExchangeCodeScene__
#define __HelloWorld__CcbExchangeCodeScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbExchangeCodeScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbExchangeCodeScene();
    ~CcbExchangeCodeScene();
    
    CREATE_FUNC(CcbExchangeCodeScene);
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

#endif /* defined(__HelloWorld__CcbExchangeCodeScene__) */
