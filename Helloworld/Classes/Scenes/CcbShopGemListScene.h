//
//  CcbShopGemListScene.h
//  HelloWorld
//
//  Created by jun on 14-3-24.
//
//

#ifndef __HelloWorld__CcbShopGemListScene__
#define __HelloWorld__CcbShopGemListScene__

#include <iostream>
#include "CcbShopGemListLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbShopGemListScene : public cocos2d::CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbShopGemListScene();
    ~CcbShopGemListScene();
    
    CREATE_FUNC(CcbShopGemListScene);
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

#endif /* defined(__HelloWorld__CcbShopGemListScene__) */
