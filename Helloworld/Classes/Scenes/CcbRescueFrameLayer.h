/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-14 12:11:56
*/

#ifndef __CCBRESCUEFRAMELAYER__H__
#define __CCBRESCUEFRAMELAYER__H__

//CcbRescueFrameLayer.h come from ccb/rescue_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbRescueFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbRescueFrameLayer()
	{
		m_pSpriteIcon = NULL;
		m_pLabelTTFLv = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFInfo = NULL;
		m_pControlButtonCatRes = NULL;
        m_pSpriteCR = NULL;
	}
	~CcbRescueFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbRescueFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    // Touch Delegate
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFLv;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFInfo;
	cocos2d::extension::CCControlButton* m_pControlButtonCatRes;
    cocos2d::CCSprite* m_pSpriteCR;
    
    float m_fUpBound, m_fDownBound;

    bool m_bMove;
    cocos2d::CCPoint m_pStart;
    bool TouchInTable(cocos2d::CCPoint point);
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void SetData(int idx);
    void setUpDownBound(float fUp, float fDown);
public:
	// Funcitons
	void onPressControlButtonCatRes(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbRescueFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbRescueFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbRescueFrameLayer);
};


#endif // __CCBRESCUEFRAMELAYER__H__