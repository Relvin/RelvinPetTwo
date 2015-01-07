//
//  CcbShopItemFrameScene.h
//  HelloWorld
//
//  Created by jun on 13-12-26.
//
//

#ifndef __HelloWorld__CcbShopItemFrameScene__
#define __HelloWorld__CcbShopItemFrameScene__

#include <iostream>
#include "CcbShopItemFrameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbShopItemFrameScene : public cocos2d::CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbShopItemFrameScene();
    ~CcbShopItemFrameScene();
    
    CREATE_FUNC(CcbShopItemFrameScene);
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

#endif /* defined(__HelloWorld__CcbShopItemFrameScene__) */
