/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-13 11:57:27
*/

#ifndef __CCBRUNEICONLAYER__H__
#define __CCBRUNEICONLAYER__H__

//CcbRuneIconLayer.h come from ccb/equip_rune_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbRuneIconLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbRuneIconLayer()
	{
		m_pSpriteRuneIcon = NULL;
		m_pSpriteRuneFrame = NULL;
        m_pLabelTTFName = NULL;

	}
	~CcbRuneIconLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbRuneIconLayer, create);
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
	
public:
    // Attributes for CCB
	cocos2d::CCSprite* m_pSpriteRuneIcon;
	cocos2d::CCSprite* m_pSpriteRuneFrame;
    cocos2d::CCLabelTTF* m_pLabelTTFName;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


    void CreateRuneData();
public:
	// Funcitons
    CC_SYNTHESIZE(int, m_localTag, LocalTag);
    CCScrollButton* m_pScrollButtonSelect;
    void onPressScrollButtonSelect(CCObject* pSender, CCControlEvent event);


};

class CcbRuneIconLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbRuneIconLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbRuneIconLayer);
};


#endif // __CCBRUNEICONLAYER__H__