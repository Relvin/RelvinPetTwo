/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-15 16:43:27
*/

#ifndef __CCBMAILDETAILLAYER__H__
#define __CCBMAILDETAILLAYER__H__

//CcbMailDetailLayer.h come from ccb/mail_text.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "FriendUnitDataMgr.h"

class CcbMailDetailLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbMailDetailLayer()
	{
//		m_pSpriteMailIcon = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFTitle = NULL;
		m_pLabelTTFTime = NULL;
		m_pLabelTTFMailContent = NULL;
        m_pControlButtonClose = NULL;
        m_pControlButtonDelete = NULL;
        m_pControlButtonReply = NULL;
	}
	~CcbMailDetailLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbMailDetailLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    uint32 m_dwMailId;      // 记录邮件Id}
    uint32 m_dwSenderId;    // 发信人Id}
    std::string m_strSenderName;
    std::string m_strTitle;
    cocos2d::CCString* m_strSendTime;
public:
	// Attributes for CCB
//	cocos2d::CCSprite* m_pSpriteMailIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFTitle;
	cocos2d::CCLabelTTF* m_pLabelTTFTime;
	cocos2d::CCLabelTTF* m_pLabelTTFMailContent;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::extension::CCControlButton* m_pControlButtonDelete;
    cocos2d::extension::CCControlButton* m_pControlButtonReply;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setMailDetailContent(
                              FriendUnitDataMgr::STC_MAIL_CONTENT& mailContent,
                              std::string strSenderName,
                              std::string strTitle
                              );
public:
	// Funcitons
	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonDelete(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonReply(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbMailDetailLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbMailDetailLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbMailDetailLayer);
};


#endif // __CCBMAILDETAILLAYER__H__