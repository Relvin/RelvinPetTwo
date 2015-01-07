/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-30 17:12:42
*/

#ifndef __CCBSYSTEMBOOTINFOLAYER__H__
#define __CCBSYSTEMBOOTINFOLAYER__H__

//CcbSystemBootInfoLayer.h come from ccb/system_boot_info.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


class CcbSystemBootInfoLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbSystemBootInfoLayer()
	{
		m_pControlButtonCancel = NULL;
		m_pControlButtonGO = NULL;
		m_pLabelTTFText = NULL;

	}
	~CcbSystemBootInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSystemBootInfoLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonCancel;
	cocos2d::extension::CCControlButton* m_pControlButtonGO;
	cocos2d::CCLabelTTF* m_pLabelTTFText;

    uint32 m_dwSysLockId;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
	void onPressControlButtonCancel(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonGO(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadData(uint32 sysLockId);
    static void showSystemBootInfo(uint32 sysLockId, CCNode *parent);
};

class CcbSystemBootInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSystemBootInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSystemBootInfoLayer);
};


#endif // __CCBSYSTEMBOOTINFOLAYER__H__