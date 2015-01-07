/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-13 14:34:29
*/

#ifndef __CCBARENAMYINFOLAYER__H__
#define __CCBARENAMYINFOLAYER__H__

//CcbArenaMyInfoLayer.h come from ccb/arena_myinform.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"
#include "CcbPetIcon.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaMyInfoLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverMsg
{
public:
	// Constructor
	CcbArenaMyInfoLayer()
    : m_pLabelTTFRank(NULL)
	{
		m_pLayerLeaderIcon = NULL;
		m_pLabelTTFDoubleWinValue = NULL;
		m_pLabelTTFDoubleWin = NULL;
		m_pLabelTTF2 = NULL;
		m_pLabelTTF3 = NULL;
		m_pLabelTTFRecords = NULL;
		m_pLabelTTF1 = NULL;
		m_pLabelTTFPlayerName = NULL;
		m_pLabelTTFGroupName = NULL;
        m_pSpriteRankBadge = NULL;
        m_pLabelTTFRank = NULL;
        m_pLabelTTFArenaCnt = NULL;
	}
	~CcbArenaMyInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaMyInfoLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual void RefeashLayer();
    void CreateDlgData();

private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CcbPetIcon* m_pLayerLeaderIcon;
	CCLabelTTF* m_pLabelTTFDoubleWinValue;
	CCLabelTTF* m_pLabelTTFDoubleWin;
	CCLabelTTF* m_pLabelTTF2;
	CCLabelTTF* m_pLabelTTF3;
	CCLabelTTF* m_pLabelTTFRecords;
	CCLabelTTF* m_pLabelTTF1;
	CCLabelTTF* m_pLabelTTFPlayerName;
	CCLabelTTF* m_pLabelTTFGroupName;
    CCSprite* m_pSpriteRankBadge;
    CCLabelTTF* m_pLabelTTFRank;
    CCLabelTTF* m_pLabelTTFArenaCnt;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

};

class CcbArenaMyInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaMyInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaMyInfoLayer);
};


#endif // __CCBARENAMYINFOLAYER__H__