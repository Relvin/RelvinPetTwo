/**
* CcbArenaResultHighestLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-27 14:12:27
*/

#ifndef __CCBARENARESULTHIGHESTLAYER__H__
#define __CCBARENARESULTHIGHESTLAYER__H__

//CcbArenaResultHighestLayer.h come from ccb/arena_result_highest.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbArenaResultWinLayer;

class CcbArenaResultHighestLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbArenaResultHighestLayer()
	{
		m_pControlButtonOK = NULL;
		m_pLabelBMFontPreRank = NULL;
		m_pLabelBMFontCurRank = NULL;
		m_pLabelTTFRewardNums = NULL;
		m_pLabelBMFontUpNums = NULL;
        m_delegate = NULL;

	}
	~CcbArenaResultHighestLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaResultHighestLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonOK;
	cocos2d::CCLabelBMFont* m_pLabelBMFontPreRank;
	cocos2d::CCLabelBMFont* m_pLabelBMFontCurRank;
	cocos2d::CCLabelTTF* m_pLabelTTFRewardNums;
	cocos2d::CCLabelBMFont* m_pLabelBMFontUpNums;

    CcbArenaResultWinLayer* m_delegate;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void setDelegate(CcbArenaResultWinLayer *delegate){
        m_delegate = delegate;
    };

	void onPressControlButtonOK(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbArenaResultHighestLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaResultHighestLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaResultHighestLayer);
};


#endif // __CCBARENARESULTHIGHESTLAYER__H__