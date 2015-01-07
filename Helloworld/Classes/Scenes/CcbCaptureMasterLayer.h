/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-13 11:10:40
*/

#ifndef __CCBCAPTUREMASTERLAYER__H__
#define __CCBCAPTUREMASTERLAYER__H__

//CcbCaptureMasterLayer.h come from ccb/capture_slave_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbCaptureMasterLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbCaptureMasterLayer()
	{
		m_pControlButtonRevolt = NULL;
		m_pSpriteMasterHead = NULL;
		m_pLabelTTFMasterName = NULL;
		m_pLabelTTFMasterGroup = NULL;
		m_pLabelTTFCageTime = NULL;

	}
	~CcbCaptureMasterLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbCaptureMasterLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonRevolt;
	cocos2d::CCSprite* m_pSpriteMasterHead;
	cocos2d::CCLabelTTF* m_pLabelTTFMasterName;
	cocos2d::CCLabelTTF* m_pLabelTTFMasterGroup;
	cocos2d::CCLabelTTF* m_pLabelTTFCageTime;

    uint32 m_dwLeftTime;
    
    void updateTime(float dt);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setMasterInfo();
public:
	// Funcitons
	void onPressControlButtonRevolt(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbCaptureMasterLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbCaptureMasterLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbCaptureMasterLayer);
};


#endif // __CCBCAPTUREMASTERLAYER__H__