//
//  CcbSettingsScene.h
//  HelloWorld
//
//  Created by jun on 14-5-9.
//
//

#ifndef __HelloWorld__CcbSettingsScene__
#define __HelloWorld__CcbSettingsScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbSettingsScene:public CCLayer
, public CCBMemberVariableAssigner
{
public:
    CcbSettingsScene();
    ~CcbSettingsScene();
    
    CREATE_FUNC(CcbSettingsScene);
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

#endif /* defined(__HelloWorld__CcbSettingsScene__) */
