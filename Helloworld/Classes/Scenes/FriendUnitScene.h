//
//  FriendUnitScene.h
//  MyGame
//
//  Created by 朱 俊杰 on 14/11/20.
//
//

#ifndef __MyGame__FriendUnitScene__
#define __MyGame__FriendUnitScene__

#include "cocos2d.h"
#include "cocos-ext.h"

class FriendUnitScene : public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
    
public:
    FriendUnitScene() {
        m_pLabelTTFName = NULL;
    }
    
    virtual ~FriendUnitScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    }
    
    static cocos2d::CCScene* scene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FriendUnitScene, create);
    
    // Inhert MemberVariableAssigner
    virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
    
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* defined(__MyGame__FriendUnitScene__) */
