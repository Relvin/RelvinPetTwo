/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-07 14:48:03
*/

#ifndef __CCBLIANXIEBGLAYER5__H__
#define __CCBLIANXIEBGLAYER5__H__

//CcbLianXieBgLayer5.h come from ccb/pet_battle_flash_5.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbLianXieBgLayer5:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbLianXieBgLayer5()
	{

	}
	~CcbLianXieBgLayer5();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbLianXieBgLayer5, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB

	void onRemoveSelf(cocos2d::CCNode *pNode);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons





};

class CcbLianXieBgLayer5Loader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbLianXieBgLayer5Loader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbLianXieBgLayer5);
};


#endif // __CCBLIANXIEBGLAYER5__H__