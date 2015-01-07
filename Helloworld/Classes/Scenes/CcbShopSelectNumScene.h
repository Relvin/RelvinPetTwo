//
//  CcbShopSelectNumScene.h
//  HelloWorld
//
//  Created by jun on 13-12-26.
//
//

#ifndef __HelloWorld__CcbShopSelectNumScene__
#define __HelloWorld__CcbShopSelectNumScene__

#include <iostream>
#include "CcbShopSelectNumLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbShopSelectNumScene : public cocos2d::CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbShopSelectNumScene();
    ~CcbShopSelectNumScene();
    
    CREATE_FUNC(CcbShopSelectNumScene);
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

#endif /* defined(__HelloWorld__CcbShopSelectNumScene__) */