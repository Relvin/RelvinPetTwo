//
//  CcbVipListScene.h
//  HelloWorld
//
//  Created by jun on 14-6-5.
//
//

#ifndef __HelloWorld__CcbVipListScene__
#define __HelloWorld__CcbVipListScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbVipListScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbVipListScene();
    ~CcbVipListScene();
    
    CREATE_FUNC(CcbVipListScene);
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

#endif /* defined(__HelloWorld__CcbVipListScene__) */
