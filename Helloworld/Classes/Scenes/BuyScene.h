//
//  BuyScene.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-23.}
//
//

#ifndef __HelloWorld__BuyScene__
#define __HelloWorld__BuyScene__

#include "cocos2d.h"
#include "cocos-ext.h"

class BuyScene :
    public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner
{
    
public:
    BuyScene() {
        m_pLabelTTFName = NULL;
    };
    ~BuyScene();
    
    static cocos2d::CCScene* scene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BuyScene, create);
    
    virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* defined(__HelloWorld__BuyScene__) */
