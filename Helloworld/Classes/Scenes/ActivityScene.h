//
//  ActivityScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-12-12.}
//
//

#ifndef __HelloWorld__ActivityScene__
#define __HelloWorld__ActivityScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton.h"

USING_NS_CC;



class ActivityScene :
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    ActivityScene()
	{
        m_pLabelTTFName  = NULL;
	}
	~ActivityScene();
    
    static cocos2d::CCScene *scene();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ActivityScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
};

#endif /* defined(__HelloWorld__ActivityScene__) */
