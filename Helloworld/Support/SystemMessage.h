//
//  SystemMessage.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-26.}
//
//

#ifndef __HelloWorld__SystemMessage__
#define __HelloWorld__SystemMessage__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SystemMessageProtocol.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ReRichText;

class SystemMessage : public CCLayer,
    public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener {
public:
	typedef struct _STC_MSG
	{
        std::string strTitle;
		std::string strMsg;
	}STC_MSG;
    
    SystemMessage()
	{
		m_pControlButtonOk = NULL;
		m_pControlButtonCancel = NULL;
		m_pLabelTTFContent = NULL;
        mAnimationManager = NULL;
        m_pLayerColor = NULL;
        m_pLabelTTFTitle = NULL;
        m_pControlButtonClose = NULL;
        m_pRichText = NULL;
	}
	~SystemMessage()
    {
        CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
        CC_SAFE_RELEASE_NULL(m_pControlButtonCancel);
        CC_SAFE_RELEASE_NULL(m_pLabelTTFContent);
        CC_SAFE_RELEASE_NULL(mAnimationManager);
        CC_SAFE_RELEASE_NULL(m_pLayerColor);
        CC_SAFE_RELEASE_NULL(m_pLabelTTFTitle);
        CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    };
    
    // Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SystemMessage, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
#pragma mark Public Method
    static void showSystemMessage(int type, CCNode *parent, const char *text, SystemMessageProtocol *_delegate = NULL, bool bForceShow = false, int param = 0, const char *title = NULL, bool bHideClose = false);
    
    void onPressControlButtonOk(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	
	int getParam(){
		return param;
	}
	static void UnInit();

    // Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonOk;
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
	cocos2d::CCLabelTTF* m_pLabelTTFContent;
    cocos2d::CCLabelTTF* m_pLabelTTFTitle;
    CCLayer* m_pLayerColor;
    
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    void addGuideLayer();
private:
	SystemMessageProtocol *delegate;
	static std::vector<STC_MSG> m_vecPending;
    int param;
    ReRichText*      m_pRichText;

    void setDelegate(SystemMessageProtocol*);
    void showMessage(int type, CCNode *parent, const char *text, SystemMessageProtocol *_delegate = NULL, int param = 0, const char *title = NULL, bool bHideClose = false);
    
    static bool CheckCanDo();
	static void ProcessPending(CCNode *pNode);
};

class SystemMessageLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SystemMessageLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SystemMessage);
};

#endif /* defined(__HelloWorld__SystemMessage__) */
