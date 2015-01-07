/**
* CcbChallengetype3ScrollLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-17 14:37:00
*/

#ifndef __CCBCHALLENGETYPE3SCROLLLAYER__H__
#define __CCBCHALLENGETYPE3SCROLLLAYER__H__

//CcbChallengetype3ScrollLayer.h come from ccb/CcbChallengetype3ScrollLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbChallengeNodeLayer.h"

class CcbChallengetype3ScrollLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbChallengetype3ScrollLayer();
	~CcbChallengetype3ScrollLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengetype3ScrollLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    CC_SYNTHESIZE(ChallengeNodeClickedDelegate *, m_pDelegate, Delegate);
    
    void setFirstButtonSelected();
	
private:

	// Attributes for CCB


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void setScrollLayerInfoByDiffiValue(uint8 byDiffiValue);



};

class CcbChallengetype3ScrollLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengetype3ScrollLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengetype3ScrollLayer);
};


#endif // __CCBCHALLENGETYPE3SCROLLLAYER__H__