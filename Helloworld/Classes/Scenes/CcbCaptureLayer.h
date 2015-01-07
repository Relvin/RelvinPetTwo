/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-07 23:40:38
*/

#ifndef __CCBCAPTURELAYER__H__
#define __CCBCAPTURELAYER__H__

//CcbCaptureLayer.h come from ccb/capture.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbCaptureMasterLayer;
class CcbCaptureFrameLayer;
class CcbCaptureLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDelegate
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbCaptureLayer()
	{
//		m_pControlButtonBack = NULL;
		m_pControlButtonSave = NULL;
		m_pLayerBottom = NULL;
		m_pLayerMsg = NULL;
        m_pTableMsg = NULL;
        m_pLayerMaster = NULL;
        m_pLayerSlave = NULL;
        m_pLayerFrameMaster = NULL;
        m_shared = NULL;
	}
	~CcbCaptureLayer();

    static CcbCaptureLayer* GetCurLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbCaptureLayer, create);
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
//	cocos2d::extension::CCControlButton* m_pControlButtonBack;
	cocos2d::extension::CCControlButton* m_pControlButtonSave;
	cocos2d::CCLayer* m_pLayerBottom;
	cocos2d::CCLayer* m_pLayerMsg;
    cocos2d::CCLayer* m_pLayerMaster;   // 自身作为主人时显示的界面}
    CcbCaptureFrameLayer* m_pLayerFrameMaster;  // 自身作为主人时显示的界面}
    CcbCaptureMasterLayer* m_pLayerSlave;    // 自身作为奴隶时显示的界面}

    cocos2d::extension::CCTableView* m_pTableMsg;
    static CcbCaptureLayer* m_shared;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    // CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
	
    void setCaptureInfo();
public:
	// Funcitons
//	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonSave(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbCaptureLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbCaptureLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbCaptureLayer);
};


#endif // __CCBCAPTURELAYER__H__