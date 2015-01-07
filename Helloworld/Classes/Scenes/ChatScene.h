//
//  ChatScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-6-16.}
//
//

#ifndef __HelloWorld__ChatScene__
#define __HelloWorld__ChatScene__

#include "cocos2d.h"
#include "cocos-ext.h"

class ChatScene : public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
    
public:
    ChatScene() {
        m_pLabelTTFName = NULL;
    }
    ~ChatScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    }
    
    static cocos2d::CCScene* scene();
    
    // Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChatScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    
private:
	// Attributes for CCB
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    
public:
    bool init();
    void onEnter();
    void onExit();
};

#endif /* defined(__HelloWorld__ChatScene__) */
