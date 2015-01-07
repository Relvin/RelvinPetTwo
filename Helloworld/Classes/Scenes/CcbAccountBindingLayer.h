/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-04 19:51:24
*/

#ifndef __CCBACCOUNTBINDINGLAYER__H__
#define __CCBACCOUNTBINDINGLAYER__H__

//CcbAccountBindingLayer.h come from ccb/account_binding.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "SystemMessageProtocol.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbAccountBindingLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCEditBoxDelegate
,   public CObserverMsg
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbAccountBindingLayer()
	{
		//m_pControlButtonClose = NULL;
		m_pLabelTTFErrorDesc = NULL;
		m_pScale9SpriteAccount = NULL;
		m_pScale9SpritePassword = NULL;
		m_pScale9SpriteMail = NULL;
		m_pScale9SpriteMail2 = NULL;
        m_pLayerParent1 = NULL;
		m_pLayerParent2 = NULL;
		m_pLabelTTFMail = NULL;
		m_pLayerParent3 = NULL;
		m_pControlButtonBinding = NULL;
        m_pEditBoxAccount = NULL;
        m_pEditBoxPassword = NULL;
        m_pEditBoxMail = NULL;
        m_pEditBoxMail2 = NULL;
	}
	~CcbAccountBindingLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbAccountBindingLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void RefeashLayer();
    
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    
    //Edit Box
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	//CCControlButton* m_pControlButtonClose;
	CCLabelTTF* m_pLabelTTFErrorDesc;
	CCScale9Sprite* m_pScale9SpriteAccount;
	CCScale9Sprite* m_pScale9SpritePassword;
	CCScale9Sprite* m_pScale9SpriteMail;
	CCLayer* m_pLayerParent1;
	CCScale9Sprite* m_pScale9SpriteMail2;
	CCLayer* m_pLayerParent2;
	CCLabelTTF* m_pLabelTTFMail;
	CCLayer* m_pLayerParent3;
	CCControlButton* m_pControlButtonBinding;
    CCEditBox* m_pEditBoxAccount;
    CCEditBox* m_pEditBoxPassword;
    CCEditBox* m_pEditBoxMail;
    CCEditBox* m_pEditBoxMail2;
    
    CCPoint m_EditBoxAccountPos;
    CCPoint m_EditBoxPasswordPos;
    CCPoint m_EditBoxMail;
    CCPoint m_EditBoxMail2;
    
    void CreateEditeWithAccountPassword();
    void CreateEditeWithOnlyMail();

    bool CheckAccountPasswordMail();
    bool CheckMail2();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	//void onPressControlButtonClose(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonBinding(CCObject* pSender, CCControlEvent event);



};

class CcbAccountBindingLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbAccountBindingLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbAccountBindingLayer);
};


#endif // __CCBACCOUNTBINDINGLAYER__H__