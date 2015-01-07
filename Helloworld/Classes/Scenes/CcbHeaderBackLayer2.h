/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-13 16:39:09
*/

#ifndef __CCBHEADERBACKLAYER2__H__
#define __CCBHEADERBACKLAYER2__H__

//CcbHeaderBackLayer2.h come from ccb/header_back2.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbHeaderBackLayer2:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbHeaderBackLayer2()
	{
//		m_pSpriteAttribute = NULL;
//		m_pLabelTTFName = NULL;
		m_pControlButtonBack = NULL;
		m_pNodeBg = NULL;

	}
	~CcbHeaderBackLayer2();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbHeaderBackLayer2, create);
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
//	cocos2d::CCSprite* m_pSpriteAttribute;
//	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::extension::CCControlButton* m_pControlButtonBack;
	cocos2d::CCNode* m_pNodeBg;

    bool m_backFlag;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbHeaderBackLayer2Loader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbHeaderBackLayer2Loader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbHeaderBackLayer2);
};


#endif // __CCBHEADERBACKLAYER2__H__