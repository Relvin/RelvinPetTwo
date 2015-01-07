/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-21 16:23:03
*/

#ifndef __CCBCREATENAMELAYER__H__
#define __CCBCREATENAMELAYER__H__

//CcbCreateNameLayer.h come from ccb/createname.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CreateNameScene : cocos2d::CCLayer {
    
public:
    CreateNameScene() {}
    ~CreateNameScene() {}
    
    static cocos2d::CCScene* scene();
    CREATE_FUNC(CreateNameScene);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
};

#pragma mark CcbCreateNameLayer

class CcbCreateNameLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
{
public:
	// Constructor
	CcbCreateNameLayer()
	{
		m_pScale9SpriteName = NULL;
		m_pControlButtonRandom = NULL;
		m_pControlButtonConfirm = NULL;
        m_pLayerCenter = NULL;
	}
	~CcbCreateNameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbCreateNameLayer, create);
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
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteName;
	cocos2d::extension::CCControlButton* m_pControlButtonRandom;
	cocos2d::extension::CCControlButton* m_pControlButtonConfirm;
    cocos2d::CCLayer* m_pLayerCenter;

    cocos2d::extension::CCEditBox* m_pInputBox;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    std::vector<std::string> m_vecFirstName;
    std::vector<std::string> m_vecSecondName;
    std::vector<std::string> m_vecThirdName;
	
public:
	// Funcitons
	void onPressControlButtonRandom(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonConfirm(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onConfirm();

    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

};

class CcbCreateNameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbCreateNameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbCreateNameLayer);
};


#endif // __CCBCREATENAMELAYER__H__