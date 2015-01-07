/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-16 11:57:47
*/

#ifndef __CCBCHATLAYER__H__
#define __CCBCHATLAYER__H__

//CcbChatLayer.h come from ccb/chat.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "SystemMessage.h"
#include "ChatDataMgr.h"
//#include "Defines.h"
//#include <string>

USING_NS_CC;

class CcbChatLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCEditBoxDelegate
//,   public cocos2d::ui::ReLinkTextDelegate
//,   public SystemMessageProtocol
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbChatLayer()
	{
		m_pLayerChatRoom = NULL;
		m_pControlButtonSent = NULL;
		m_pScale9SpriteText = NULL;
		m_pControlButtonSmilies = NULL;
        m_pControlButtonWorld = NULL;
        m_pControlButtonPersonal = NULL;
        m_pControlButtonAlliance = NULL;
        m_pControlButtonClose = NULL;
        m_pScale9SpriteInputID = NULL;
        m_pNodePersonal = NULL;
        
        m_pLayerDown = NULL;
        m_pEditBoxInput = NULL;
        m_pNodeBg = NULL;
        m_nFaceCnt = 0;
        m_pTableMsg = NULL;
        m_nCurType = 0;
        
//        m_dwTargetId = 0;
//        m_strTargetName = "";
	}
	~CcbChatLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChatLayer, create);
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
	cocos2d::CCLayer* m_pLayerChatRoom;
	cocos2d::extension::CCControlButton* m_pControlButtonSent;
	cocos2d::extension::CCScale9Sprite* m_pScale9SpriteText;
    cocos2d::extension::CCScale9Sprite* m_pScale9SpriteInputID;
	cocos2d::extension::CCControlButton* m_pControlButtonSmilies;
    cocos2d::extension::CCControlButton* m_pControlButtonWorld;
    cocos2d::extension::CCControlButton* m_pControlButtonPersonal;
    cocos2d::extension::CCControlButton* m_pControlButtonAlliance;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::CCNode* m_pNodePersonal;       // 世界不显示，私聊显示
    
    cocos2d::CCLayer* m_pLayerDown;
    cocos2d::CCNode* m_pNodeBg;

    cocos2d::extension::CCEditBox* m_pEditBoxInput;
    cocos2d::extension::CCEditBox* m_pEditBoxId;
    cocos2d::CCPoint tablePos;
    cocos2d::extension::CCTableView* m_pTableMsg;
    
    static CcbChatLayer* m_shared;
    
//    void chatMsgList(int _channel);
    
    ccColor4B cc4WorldChannel;
    ccColor4B cc4LeagueChannel;
    ccColor4B cc4Name;
    ccColor4B cc4Text;
    
    int m_nFaceCnt;
    int m_nCurType;
    
    void showEditBox();
    
    uint32 m_dwTargetId;
    const char* m_strName;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    static CcbChatLayer* getInstance() { return m_shared; }
    void touchToPrivate(uint32 dwAccount);
    
    int faceNum() { return m_nFaceCnt; }
public:
	// Funcitons
	void onPressControlButtonSent(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonSmilies(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonWorld(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonPersonal(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAlliance(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    // CCEditBoxDelegate
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
//    virtual void linkTextClickedCallBack(cocos2d::ui::ReLinkText *pLinkText);
//    void addNewMsg(const ChatDataMgr::STC_CHAT_MSG& chatMsg);
    void addFaceCode(int _code);
//    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    
    // Touch Delegate
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    // CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(CCTableView *table);
    
    void reloadData();
};

class CcbChatLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChatLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChatLayer);
};


#endif // __CCBCHATLAYER__H__