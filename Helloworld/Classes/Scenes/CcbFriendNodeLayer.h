/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 23:42:23
*/

#ifndef __CCBFRIENDNODELAYER__H__
#define __CCBFRIENDNODELAYER__H__

//CcbFriendNodeLayer.h come from ccb/friend_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FriendCtrl.h"
#include "SystemMessage.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCScrollButton;
class CcbPetIcon;
class CcbFriendNodeLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbFriendNodeLayer()
	{
        m_pLayerHead = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFGroup = NULL;
		m_pControlButtonAccept = NULL;
		m_pControlButtonReject = NULL;
        m_pControlButtonSelf = NULL;
		m_pLabelTTFLv = NULL;
        m_pLabelTTFTitle = NULL;
        m_dwMailId = 0;
        m_dwFriendId = 0;
	}
	~CcbFriendNodeLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendNodeLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFGroup;
	CCScrollButton* m_pControlButtonAccept;
	CCScrollButton* m_pControlButtonReject;
    CCScrollButton* m_pControlButtonSelf;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
    cocos2d::CCLabelTTF* m_pLabelTTFTitle;

    uint32 m_dwCurUserId;
    uint16 m_wLeaderId;
    uint8 m_byMailType;     // 区分好友邮件还是好友申请}
    
    cocos2d::CCPoint m_pStart;
    bool TouchInTable(cocos2d::CCPoint point);
    
    uint32 m_dwMailId;      // 邮件ID}
    uint32 m_dwFriendId;    // 好友ID}
    
    void setGroupString(uint8 byGroupId);
    void setLvString(uint16 wRoleLv);
    void setHeadPicture(uint16 wLeadId);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setNode(FriendCtrl::STC_USER_INFO nodeInfo);
    void setMsgInfo(FriendCtrl::STC_FRIEND_MAIL sMail, uint8 byType);
public:
	// Funcitons
	void onPressControlButtonSelf(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAccept(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonReject(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonHead(CCObject* pSender, CCControlEvent event);

    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
};

class CcbFriendNodeLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendNodeLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendNodeLayer);
};


#endif // __CCBFRIENDNODELAYER__H__