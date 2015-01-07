/**
* CcbFriendMailFrameLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-22 17:55:41
*/

#ifndef __CCBFRIENDMAILFRAMELAYER__H__
#define __CCBFRIENDMAILFRAMELAYER__H__

//CcbFriendMailFrameLayer.h come from ccb/CcbFriendMailFrameLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FriendUnitDataMgr.h"
#include "Defines.h"

class CcbPetIcon;
class CcbFriendMailFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFriendMailFrameLayer()
	{
		m_pLayerHead = NULL;
		m_pControlButtonAccept = NULL;
		m_pControlButtonRefuse = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFLv = NULL;
		m_pLabelTTFTitle = NULL;
		m_pLabelTTFWord = NULL;
		m_pLabelTTFFightPower = NULL;
        m_nFrameType = 0;
        m_dwTargetId = 0;
	}
	~CcbFriendMailFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendMailFrameLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonAccept;
	cocos2d::extension::CCControlButton* m_pControlButtonRefuse;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCLabelTTF* m_pLabelTTFTitle;
	cocos2d::CCLabelTTF* m_pLabelTTFWord;
	cocos2d::CCLabelTTF* m_pLabelTTFFightPower;

    int m_nFrameType;   // 判断是邮件还是好友申请
    uint32 m_dwTargetId;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setFrameData(const FriendUnitDataMgr::STC_FRIEND_MAIL& _info);
public:
	// Funcitons
	void onPressControlButtonAccept(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRefuse(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbFriendMailFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendMailFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendMailFrameLayer);
};


#endif // __CCBFRIENDMAILFRAMELAYER__H__