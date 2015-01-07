/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-24 17:40:37
*/

#ifndef __CCBEMBLEMICON__H__
#define __CCBEMBLEMICON__H__

//CcbEmblemIcon.h come from ccb/emblem_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


class CcbEmblemIcon:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEmblemIcon()
	{
		m_pSpriteIcon = NULL;
		m_pControlButtonShowEmblem = NULL;
		m_pSpriteIconFrame = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFLv = NULL;

	}
	~CcbEmblemIcon();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEmblemIcon, create);
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
	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::extension::CCControlButton* m_pControlButtonShowEmblem;
	cocos2d::CCSprite* m_pSpriteIconFrame;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;


    uint32 m_dwEmblemObjId;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


	void onPressControlButtonSkill(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadData(uint32 dwEmblemObjId);
    void setEnable(bool enable);

    void setIndex(uint32 index);
    void setLv(uint8 lv);
};

class CcbEmblemIconLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEmblemIconLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEmblemIcon);
};


#endif // __CCBEMBLEMICON__H__