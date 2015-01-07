//
//  FriendMailScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-25.}
//
//

#ifndef __HelloWorld__FriendMailScene__
#define __HelloWorld__FriendMailScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FriendMailScene : 
    public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner {
    
public:
    FriendMailScene() {
        m_pLabelTTFName = NULL;
    }
    ~FriendMailScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    }
    
    static CCScene* scene();
    
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FriendMailScene, create);
    CREATE_FUNC(FriendMailScene);
    
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    
private:
    CCLabelTTF* m_pLabelTTFName;
    
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
};

#endif /* defined(__HelloWorld__FriendMailScene__) */
