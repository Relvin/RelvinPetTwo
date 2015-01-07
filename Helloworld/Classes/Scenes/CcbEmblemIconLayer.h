/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-08 11:39:32
*/

#ifndef __CCBEMBLEMICONLAYER__H__
#define __CCBEMBLEMICONLAYER__H__

//CcbEmblemIconLayer.h come from ccb/badge_choose_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"
#include "CcbItemIconLayer.h"

class CcbEmblemChooseListLayer;

class CcbEmblemIconLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEmblemIconLayer()
	{
		m_pLayerIcon = NULL;
		m_pSpriteTick = NULL;
		m_pLabelTTFName = NULL;
        m_btnChoose = NULL;
        m_pLayerClip = NULL;
        m_delegate = NULL;

	}
	~CcbEmblemIconLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEmblemIconLayer, create);
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
	CcbItemIconLayer* m_pLayerIcon;
	cocos2d::CCSprite* m_pSpriteTick;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
    CCLayer* m_pLayerClip;
    CcbEmblemChooseListLayer* m_delegate;
    CCScrollButton* m_btnChoose;
    uint32 m_dwEmbObjId;
    bool m_isSelected;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void onPressControlButtonChoose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void setEmbObjId(uint32 dwObjId);
    void loadData();
    void setDelegate(CcbEmblemChooseListLayer* delegate){m_delegate = delegate;};

    void setRect(CCRect rect);
    
    void isCanSelect(bool isCan);

};

class CcbEmblemIconLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEmblemIconLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEmblemIconLayer);
};


#endif // __CCBEMBLEMICONLAYER__H__