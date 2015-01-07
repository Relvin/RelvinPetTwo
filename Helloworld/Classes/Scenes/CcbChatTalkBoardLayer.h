/**
* CcbChatTalkBoardLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-17 20:24:52
*/

#ifndef __CCBCHATTALKBOARDLAYER__H__
#define __CCBCHATTALKBOARDLAYER__H__

//CcbChatTalkBoardLayer.h come from ccb/CcbChatTalkBoardLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ChatDataMgr.h"

class CcbPetIcon;
class CcbChatTalkBoardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbChatTalkBoardLayer()
	{
		m_pLayerHead = NULL;
		m_pScale9SpriteTalkBoard = NULL;
		m_pScale9SpriteVipTalkBoard = NULL;
		m_pLabelTTFWords = NULL;
        m_pControlButtonHead = NULL;
	}
	~CcbChatTalkBoardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChatTalkBoardLayer, create);
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
	CcbPetIcon* m_pLayerHead;
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteTalkBoard;
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteVipTalkBoard;
	cocos2d::CCLabelTTF* m_pLabelTTFWords;
    cocos2d::extension::CCControlButton* m_pControlButtonHead;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
public:
	// Funcitons
    void setNodeData(const ChatDataMgr::STC_CHAT_MSG& chatMsg);
    void onPressControlButtonHead(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbChatTalkBoardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChatTalkBoardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChatTalkBoardLayer);
};


#endif // __CCBCHATTALKBOARDLAYER__H__