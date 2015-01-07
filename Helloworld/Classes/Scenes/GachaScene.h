//
//  GachaScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-22.}
//
//

#ifndef __HelloWorld__GachaScene__
#define __HelloWorld__GachaScene__

#include "cocos2d.h"
#include "cocos-ext.h"

class GachaScene : public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
    
public:
    GachaScene() {
        m_pLabelTTFName = NULL;
    };
    ~GachaScene();
    
    static cocos2d::CCScene* scene();
    // Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GachaScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
private:
	// Attributes for CCB
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* defined(__HelloWorld__GachaScene__) */
