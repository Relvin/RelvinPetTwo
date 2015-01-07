/**
* CcbWorldBossRankRewardFrame.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-16 17:59:20
*/

#ifndef __CCBWORLDBOSSRANKREWARDFRAME__H__
#define __CCBWORLDBOSSRANKREWARDFRAME__H__

//CcbWorldBossRankRewardFrame.h come from ccb/wolrd_boss_rewardframe.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbItemIconLayer;

class CcbWorldBossRankRewardFrame:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbWorldBossRankRewardFrame()
	{
		m_pLayerIcon1 = NULL;
		m_pLayerIcon2 = NULL;
		m_pLayerIcon3 = NULL;
		m_pLayerIcon4 = NULL;
		m_pLabelTTFRank = NULL;

	}
	~CcbWorldBossRankRewardFrame();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbWorldBossRankRewardFrame, create);
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
	CcbItemIconLayer* m_pLayerIcon1;
	CcbItemIconLayer* m_pLayerIcon2;
	CcbItemIconLayer* m_pLayerIcon3;
	CcbItemIconLayer* m_pLayerIcon4;
	cocos2d::CCLabelTTF* m_pLabelTTFRank;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void loadData(uint32 rewId);
    void setClipRect(cocos2d::CCRect rect);
    
    
};

class CcbWorldBossRankRewardFrameLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbWorldBossRankRewardFrameLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbWorldBossRankRewardFrame);
};


#endif // __CCBWORLDBOSSRANKREWARDFRAME__H__