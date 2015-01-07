/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-23 11:33:57
*/

#ifndef __CCBINVITEFRIENDFRAMELAYER__H__
#define __CCBINVITEFRIENDFRAMELAYER__H__

//CcbInviteFriendFrameLayer.h come from ccb/invite_friend_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"
#include "FriendCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbInviteFriendFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbInviteFriendFrameLayer()
	{
		m_pLayerIcon_1 = NULL;
        m_pLayerIcon_2 = NULL;
        m_pLayerIcon_3 = NULL;
        m_pLayerIcon_4 = NULL;
		m_pLabelTTFRewardDesc = NULL;
		m_pSpriteFinish = NULL;

	}
	~CcbInviteFriendFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbInviteFriendFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CcbItemIconLayer* m_pLayerIcon_1;
    CcbItemIconLayer* m_pLayerIcon_2;
    CcbItemIconLayer* m_pLayerIcon_3;
    CcbItemIconLayer* m_pLayerIcon_4;
	CCLabelTTF* m_pLabelTTFRewardDesc;
	CCSprite* m_pSpriteFinish;

    CcbItemIconLayer* pNodeItem[4];
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void loadData(INVITE_LIST_SHOW_INFO showInfo);
    void setClipRect(CCRect rect);
};

class CcbInviteFriendFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbInviteFriendFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbInviteFriendFrameLayer);
};


#endif // __CCBINVITEFRIENDFRAMELAYER__H__