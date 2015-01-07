/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-13 14:34:29
*/

#ifndef __CCBARENAREWARDLAYER__H__
#define __CCBARENAREWARDLAYER__H__

//CcbArenaRewardLayer.h come from ccb/arena_reward.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbArenaRewardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbArenaRewardLayer()
    : m_pNodeEffect(NULL)
	{
		//m_pSpriteRewardIcon = NULL;
		m_pLabelTTFTime = NULL;
		//m_pLabelTTFRewardName = NULL;
		m_pControlButtonReward = NULL;
        //m_pNodeShowTime = NULL;
        //m_pNodeButtonReward = NULL;

	}
	~CcbArenaRewardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaRewardLayer, create);
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
public:
	// Attributes for CCB
	//cocos2d::CCSprite* m_pSpriteRewardIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFTime;
	//cocos2d::CCLabelTTF* m_pLabelTTFRewardName;
	cocos2d::extension::CCControlButton* m_pControlButtonReward;
    cocos2d::CCNode* m_pNodeEffect;
    //cocos2d::CCNode* m_pNodeShowTime;
    //cocos2d::CCNode* m_pNodeButtonReward;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void setEffectVisible(bool show);
	
public:
	// Funcitons
    void onPressControlButtonReward(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


};

class CcbArenaRewardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaRewardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaRewardLayer);
};


#endif // __CCBARENAREWARDLAYER__H__