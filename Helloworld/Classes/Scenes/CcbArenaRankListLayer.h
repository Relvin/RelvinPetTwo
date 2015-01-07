/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-27 11:17:34
*/

#ifndef __CCBARENARANKLISTLAYER__H__
#define __CCBARENARANKLISTLAYER__H__

//CcbArenaRankListLayer.h come from ccb/arena_rank_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

class CcbArenaRankListLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbArenaRankListLayer()
	{
		m_pControlButtonBattle = NULL;
		m_pSpriteIcon = NULL;
		m_pSpriteCrown = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFRank = NULL;
		m_pLabelTTFMoney = NULL;
		m_pLabelTTFReputation = NULL;
		m_pLabelTTFWin = NULL;
		m_pLabelTTFLose = NULL;

        m_localTag = 0;
	}
	~CcbArenaRankListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaRankListLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
public:
	CCControlButton* m_pControlButtonBattle;
	CCSprite* m_pSpriteIcon;
	CCSprite* m_pSpriteCrown;
	CCLabelTTF* m_pLabelTTFName;
	CCLabelTTF* m_pLabelTTFRank;
	CCLabelTTF* m_pLabelTTFMoney;
	CCLabelTTF* m_pLabelTTFReputation;
	CCLabelTTF* m_pLabelTTFWin;
	CCLabelTTF* m_pLabelTTFLose;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	CC_SYNTHESIZE(int, m_localTag, LocalTag);
public:
	// Funcitons


	void onPressControlButtonBattle(CCObject* pSender, CCControlEvent event);



};

class CcbArenaRankListLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaRankListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaRankListLayer);
};


#endif // __CCBARENARANKLISTLAYER__H__