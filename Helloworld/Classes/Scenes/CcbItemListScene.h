//
//  CcbItemListScene.h
//  HelloWorld
//
//  Created by jun on 13-11-26.
//
//

#ifndef __HelloWorld__CcbItemListScene__
#define __HelloWorld__CcbItemListScene__

#include <iostream>
#include "CcbItemListLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemListScene : public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    CcbItemListScene();
    ~CcbItemListScene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemListScene, create);
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

#endif /* defined(__HelloWorld__CcbItemListScene__) */
