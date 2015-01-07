/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-15 14:10:02
*/

#ifndef __CCBSHAREFRAMELAYER__H__
#define __CCBSHAREFRAMELAYER__H__

//CcbShareFrameLayer.h come from ccb/share_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#define ENABLE_SHARE 1
#endif

class CcbShareFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbShareFrameLayer()
    : m_pNodeShareReward(NULL)
	{
		m_pScale9SpriteImage = NULL;
        m_pScale9SpriteImageFrame = NULL;
		m_pControlButtonWeiBo = NULL;
		m_pControlButtonWeiXin = NULL;
        m_pControlButtonCancel = NULL;

	}
	~CcbShareFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbShareFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCScale9Sprite* m_pScale9SpriteImage;
    CCScale9Sprite* m_pScale9SpriteImageFrame;
	CCControlButton* m_pControlButtonWeiBo;
	CCControlButton* m_pControlButtonWeiXin;
    CCControlButton* m_pControlButtonCancel;
    CCNode* m_pNodeShareReward;
    
    uint16 m_shareType;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
private:
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
    std::string getShareText();
public:
	// Funcitons
    static void showShare(CCLayer* layer, uint16 shareType);
    void loadData(CCSpriteFrame* photo, uint16 shareType);
    
	void onPressControlButtonWeiBo(CCObject* pSender, CCControlEvent event);
	void onPressControlButtonWeiXin(CCObject* pSender, CCControlEvent event);
    void onPressControlButtonCancel(CCObject* pSender, CCControlEvent event);
    
    void setShareRewardInfo();

};

class CcbShareFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbShareFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbShareFrameLayer);
};


#endif // __CCBSHAREFRAMELAYER__H__