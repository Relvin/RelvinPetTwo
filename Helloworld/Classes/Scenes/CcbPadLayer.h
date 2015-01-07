/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-02-28 17:09:17
*/

#ifndef __CCBPADLAYER__H__
#define __CCBPADLAYER__H__

//CcbPadLayer.h come from ccb/talkpad.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;

class PadLayerDelegate {
    
public:
    virtual void showStep() {} ;
};

//#define TalkPadIconCnt 4

class CcbPadLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPadLayer()
	{
		m_pSpriteCharac = NULL;
		m_pLabelTTFName = NULL;
        m_pControlButtonSelf = NULL;
        m_colorName = ccWHITE;
        m_colorDes = ccWHITE;
        m_pNodeTop = NULL;
        m_pDelegate = NULL;
        m_bErase = false;
        m_pLabelTTFContent = NULL;
        m_pLayerMask = NULL;
	}
	~CcbPadLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPadLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    enum {
        kDesPad = 1,
        kXXXX1 = 2,     // 第一个按钮,确定功能后修改名字}
        kXXXX2 = 4,
        kXXXX3 = 8,
        kXXXX4 = 16,
    };
    
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteCharac;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
    cocos2d::ccColor3B m_colorName;
    cocos2d::ccColor3B m_colorDes;
    cocos2d::extension::CCControlButton* m_pControlButtonSelf;
    cocos2d::CCNode* m_pNodeTop;
    cocos2d::CCLabelTTF* m_pLabelTTFContent;
    cocos2d::CCLayer* m_pLayerMask;
    
    int m_nKind;
    bool m_bErase;  // 是否支持点击所有区域，remove自身。如果只是描述，则支持，如果有其他按钮，则不支持，如果和maskLayer在一起，也不支持。}
    PadLayerDelegate* m_pDelegate;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    /**  */
    void setPadStyle(int code);
    
    void setScrollMsg(const char* szName, ccColor3B cName, const char* szMsg, ccColor3B cMsg);
	void setLadyInfo(uint16 wPicPath, uint8 byPicOff, uint16 wScale = 100);
    
    enum {
        E_DEFAULT = 0,
        E_BATTLE_LOSE,
        E_GUIDE,
    };
    void setFromKind(int kind);
    void setTouchErase(bool fade);
    void setDelegate(PadLayerDelegate* delegate) { m_pDelegate = delegate; };
    
    void removeSelf();
    /*!
     在引导中与MaskLayer同时出现的时候去除自身遮罩}
     */
    void removeMask();
public:
	// Funcitons
    void onPressControlButtonSelf(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    // Touch Method
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

class CcbPadLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPadLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPadLayer);
};


#endif // __CCBPADLAYER__H__