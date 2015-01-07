//
//  CcbMailListScene.h
//  HelloWorld
//
//  Created by jun on 13-11-18.
//
//

#ifndef __HelloWorld__CcbMailListScene__
#define __HelloWorld__CcbMailListScene__

#include <iostream>
#include "CcbMailListLayer.h"

USING_NS_CC;

class CcbMailListScene:public CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    CcbMailListScene();
    ~CcbMailListScene();
    
    CREATE_FUNC(CcbMailListScene);

    static cocos2d::CCScene* scene();
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	//virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
    
    
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
    
    
private:
    
};

#endif /* defined(__HelloWorld__CcbMailListScene__) */
