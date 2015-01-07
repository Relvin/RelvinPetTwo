/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-12 17:46:47
*/

#ifndef __CCBACTIVITYNODELAYER__H__
#define __CCBACTIVITYNODELAYER__H__

//CcbActivityNodeLayer.h come from ccb/activity_node.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollButton.h"
#include "Defines.h"

class CcbActivityNodeLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbActivityNodeLayer()
	{
		m_pSpriteActive = NULL;
        m_pSpriteLock = NULL;
        m_pScrollButtonNode = NULL;
        m_pSpriteWeather = NULL;
        m_strMapName = "";
        m_wRoleLvLimit = 0;
        
        m_pNode = NULL;
	}
	~CcbActivityNodeLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbActivityNodeLayer, create);
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
    cocos2d::CCSprite* m_pSpriteActive;
    cocos2d::CCSprite* m_pSpriteLock;
    cocos2d::CCSprite* m_pSpriteWeather;
    CCScrollButton* m_pScrollButtonNode;
    
    
    uint16          m_wMapId;
    std::string     m_strMapName;
    uint16          m_wRoleLvLimit;
    
    cocos2d::CCNode* m_pNode;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setNode(int mapIdx);
	
public:
	// Funcitons
	void onPressControlButtonNode(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void setClipRect(CCRect rect);
};

class CcbActivityNodeLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbActivityNodeLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbActivityNodeLayer);
};


#endif // __CCBACTIVITYNODELAYER__H__