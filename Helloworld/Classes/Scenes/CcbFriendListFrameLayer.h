/**
* CcbFriendListFrameLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-21 14:43:50
*/

#ifndef __CCBFRIENDLISTFRAMELAYER__H__
#define __CCBFRIENDLISTFRAMELAYER__H__

//CcbFriendListFrameLayer.h come from ccb/CcbFriendListFrameLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FriendUnitDataMgr.h"
#include "Defines.h"

class CcbPetIcon;
class CcbFriendListFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbFriendListFrameLayer()
	{
		m_pLayerIcon = NULL;
		m_pControlButtonSocial = NULL;
		m_pControlButtonSendEnergy = NULL;
		m_pLabelTTFFightPower = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFLv = NULL;
        m_pLabelTTFWord = NULL;
        m_dwTargetId = 0;
        m_strTargetName = "";
	}
	~CcbFriendListFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbFriendListFrameLayer, create);
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
	CcbPetIcon* m_pLayerIcon;
	cocos2d::extension::CCControlButton* m_pControlButtonSocial;
	cocos2d::extension::CCControlButton* m_pControlButtonSendEnergy;
	cocos2d::CCLabelTTF* m_pLabelTTFFightPower;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
    cocos2d::CCLabelTTF* m_pLabelTTFWord;

    uint32 m_dwTargetId;
    std::string m_strTargetName;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setFrameData(const FriendUnitDataMgr::STC_LIST_INFO& _info);
	
public:
	// Funcitons
	void onPressControlButtonSocial(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonSendEnergy(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbFriendListFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbFriendListFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbFriendListFrameLayer);
};


#endif // __CCBFRIENDLISTFRAMELAYER__H__