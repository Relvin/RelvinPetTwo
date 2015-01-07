/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-04 13:51:10
*/

#ifndef __CCBSYSFRIENDFRAMELAYER__H__
#define __CCBSYSFRIENDFRAMELAYER__H__

//CcbSysFriendFrameLayer.h come from ccb/friend_sys_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"

class CcbSysFriendFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbSysFriendFrameLayer()
	{
		m_pControlButtonNode = NULL;
		m_pLabelTTFName = NULL;
        m_pSpriteTip = NULL;
	}
	~CcbSysFriendFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSysFriendFrameLayer, create);
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
	CCScrollButton* m_pControlButtonNode;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
    cocos2d::CCSprite* m_pSpriteTip;

//    CCScrollButton* m_pScrollButtonNode;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    enum {
        kFriendAddTag = 0,          // 好友添加}
        kFriendListTag = 1,         // 好友界面}
        kFriendMailTag = 2,         // 好友邮件}
        kFriendRequst = 3,          // 好友邀请}
        kSettingTujian = 4,         // 宠物图鉴}
        kSettingAnnounce = 5,       // 公告}
        kSettingInformation = 6,    // 个人中心}
    };
	
public:
	// Funcitons
	void onPressControlButtonNode(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void setNodeData(std::string strName, int tag);
};

class CcbSysFriendFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSysFriendFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSysFriendFrameLayer);
};


#endif // __CCBSYSFRIENDFRAMELAYER__H__