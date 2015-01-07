/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-09-15 15:55:11
*/

#ifndef __TEXTWINLAYER__H__
#define __TEXTWINLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"


class TextWinLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBSelectorResolver,
	public cocos2d::extension::CCBMemberVariableAssigner,
	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	TextWinLayer()
	{

	}
	~TextWinLayer();

	// must have
	static cocos2d::CCScene* scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TextWinLayer, create);
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );

	// option
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();


	
public:
	// Funcitons





};

class TextWinLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TextWinLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TextWinLayer);
};


#endif // __TEXTWINLAYER__H__