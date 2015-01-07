/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 23:41:41
*/

#ifndef __CCBCAPTUREFRAMELAYER__H__
#define __CCBCAPTUREFRAMELAYER__H__

//CcbCaptureFrameLayer.h come from ccb/capture_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "Observer.h"

class CcbCaptureFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   CObserverMsg
{
public:
	// Constructor
	CcbCaptureFrameLayer()
	{
		m_pLabelTTFTimeL = NULL;
		m_pLabelTTFTimeR = NULL;
		m_pLabelTTFNameL = NULL;
		m_pLabelTTFNameR = NULL;
		m_pControlButtonL = NULL;
		m_pControlButtonR = NULL;
        m_bLSlaveEmpty = m_bRSlaveEmpty = true;
	}
	~CcbCaptureFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbCaptureFrameLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFTimeL;
	cocos2d::CCLabelTTF* m_pLabelTTFTimeR;
	cocos2d::CCLabelTTF* m_pLabelTTFNameL;
	cocos2d::CCLabelTTF* m_pLabelTTFNameR;
	cocos2d::extension::CCControlButton* m_pControlButtonL;
	cocos2d::extension::CCControlButton* m_pControlButtonR;

    bool m_bLSlaveEmpty, m_bRSlaveEmpty;
    
    uint32 m_dwLLeftTime, m_dwRLeftTime;
    
    void updateTime(float dt);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
    void RefeashLayer();
    void SetSlaveInfo();
public:
	// Funcitons
	void onPressControlButtonLeft(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbCaptureFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbCaptureFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbCaptureFrameLayer);
};


#endif // __CCBCAPTUREFRAMELAYER__H__