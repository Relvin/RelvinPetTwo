/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-10 13:28:03
*/

#ifndef __CCBARENARANKREWARDFRAMELAYER__H__
#define __CCBARENARANKREWARDFRAMELAYER__H__

//CcbArenaRankRewardFrameLayer.h come from ccb/arena_rank_reward_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaRankRewardFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbArenaRankRewardFrameLayer()
	{
		m_pSpriteCanGet = NULL;
		m_pLabelTTFRankNum = NULL;
		m_pSpriteRankType = NULL;
        m_pLabelTTFGroupName = NULL;
        m_pLayerIcon1 = NULL;
        m_pLayerIcon2 = NULL;
        m_pLayerIcon3 = NULL;
        m_pLayerIcon4 = NULL;

	}
	~CcbArenaRankRewardFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaRankRewardFrameLayer, create);
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
	CcbItemIconLayer* m_pLayerIcon1;
    CcbItemIconLayer* m_pLayerIcon2;
    CcbItemIconLayer* m_pLayerIcon3;
    CcbItemIconLayer* m_pLayerIcon4;
	CCSprite* m_pSpriteCanGet;
	CCLabelTTF* m_pLabelTTFRankNum;
	CCSprite* m_pSpriteRankType;
    CCLabelTTF* m_pLabelTTFGroupName;

    std::vector<CcbItemIconLayer*> arrIcon;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons


    void loadData(uint16 index);


};

class CcbArenaRankRewardFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaRankRewardFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaRankRewardFrameLayer);
};


#endif // __CCBARENARANKREWARDFRAMELAYER__H__