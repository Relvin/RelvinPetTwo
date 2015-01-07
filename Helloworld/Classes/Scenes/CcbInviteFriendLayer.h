/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-23 11:33:57
*/

#ifndef __CCBINVITEFRIENDLAYER__H__
#define __CCBINVITEFRIENDLAYER__H__

//CcbInviteFriendLayer.h come from ccb/invite_friend.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "FriendCtrl.h"
#include "ConfigData.h"

USING_NS_CC;
USING_NS_CC_EXT;


class CcbInviteFriendLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
,   public CCEditBoxDelegate
,   public CObserverMsg
{
public:
	// Constructor
	CcbInviteFriendLayer()
	{
		m_pLabelTTFInviter = NULL;
		m_pLabelTTFText2 = NULL;
		m_pNodeInviteInfo = NULL;
		m_pControlButtonConfirm = NULL;
		m_pScale9SpriteEnterID = NULL;
		m_pLabelTTFText1 = NULL;
		m_pNodeEnterInviter = NULL;
		m_pControlButtonBeInvited = NULL;
		m_pControlButtonInvite = NULL;
		m_pLayerView = NULL;
		m_pNodeViewParent = NULL;
		m_pScale9SpriteNum = NULL;
		m_pScale9SpritePlayerID = NULL;
		m_pLabelTTFInviteCount = NULL;
		m_pLabelTTFPlayerID = NULL;
        m_tableView = NULL;
        m_pEditBoxEnterInviteID = NULL;
        m_pSpriteDown = NULL;
        m_pLayerUp = NULL;
        
	}
	~CcbInviteFriendLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbInviteFriendLayer, create);
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
    
    //tableView相关}
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
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
	CCLabelTTF* m_pLabelTTFInviter;
	CCLabelTTF* m_pLabelTTFText2;
	CCNode* m_pNodeInviteInfo;
	CCControlButton* m_pControlButtonConfirm;
	CCScale9Sprite* m_pScale9SpriteEnterID;
	CCLabelTTF* m_pLabelTTFText1;
	CCNode* m_pNodeEnterInviter;
	CCControlButton* m_pControlButtonBeInvited;
	CCControlButton* m_pControlButtonInvite;
	CCLayer* m_pLayerView;
	CCNode* m_pNodeViewParent;
	CCScale9Sprite* m_pScale9SpriteNum;
	CCScale9Sprite* m_pScale9SpritePlayerID;
	CCLabelTTF* m_pLabelTTFInviteCount;
	CCLabelTTF* m_pLabelTTFPlayerID;
    CCTableView* m_tableView;
    CCEditBox* m_pEditBoxEnterInviteID;
    CCSprite* m_pSpriteDown;
    CCLayer* m_pLayerUp;
    int m_ShowType;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

	void InitData();
    vector<INVITE_LIST_SHOW_INFO> m_vecShowList[2];
public:
	// Funcitons


	void onPressControlButtonConfirm(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonBeInvited(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonInvite(CCObject* pSender, CCControlEvent event);

};

class CcbInviteFriendLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbInviteFriendLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbInviteFriendLayer);
};


#endif // __CCBINVITEFRIENDLAYER__H__