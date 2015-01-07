//
//  FriendScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-8.}
//
//

#ifndef __HelloWorld__FriendScene__
#define __HelloWorld__FriendScene__

#include "cocos2d.h"
#include "cocos-ext.h"

class FriendScene :
    public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
    
public:
    FriendScene() {
        m_pLabelTTFName = NULL;
    };
    
    ~FriendScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    };
    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(FriendScene);
    
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );

private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* defined(__HelloWorld__FriendScene__) */
