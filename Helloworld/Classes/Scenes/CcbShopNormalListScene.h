//
//  CcbShopNormalListScene.h
//  HelloWorld
//
//  Created by jun on 14-3-24.
//
//

#ifndef __HelloWorld__CcbShopNormalListScene__
#define __HelloWorld__CcbShopNormalListScene__

#include <iostream>
#include "CcbShopNormalListLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbShopNormalListScene : public cocos2d::CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbShopNormalListScene();
    ~CcbShopNormalListScene();
    
    CREATE_FUNC(CcbShopNormalListScene);
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

#endif /* defined(__HelloWorld__CcbShopNormalListScene__) */
