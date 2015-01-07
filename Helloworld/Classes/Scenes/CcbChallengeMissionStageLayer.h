/**
* CcbChallengeMissionStageLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-14 18:35:15
*/

#ifndef __CCBCHALLENGEMISSIONSTAGELAYER__H__
#define __CCBCHALLENGEMISSIONSTAGELAYER__H__

//CcbChallengeMissionStageLayer.h come from ccb/CcbChallengeMissionStageLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "ChallengeCtrl.h"

class ChallengeMissionStageDelegate
{
public:
    virtual void updateCurrentLayerInfoByIndex(uint32 dwIndex) = 0;
};

class CcbChallengeNodeLayer;
class CcbChallengeMissionStageLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbChallengeMissionStageLayer();
	~CcbChallengeMissionStageLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeMissionStageLayer, create);
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
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerStage;
    cocos2d::CCNode* m_pNodeType1;
    

public:
	// Virtual Functions
	virtual bool init();
    virtual void visit();

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void onPressControlButtonLeft(CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonRight(CCObject* pSender, cocos2d::extension::CCControlEvent event);

    // Touch Functions
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    // Self Functions
    void beforeDraw();
    void afterDraw();
    void updateStageNodePosByOffset(float offset);
    void autoAdjustStageNodePos();
    void loadMissionStageInfobyIndex(int index);
    void afterAnimationFinishCallBack();
    CC_SYNTHESIZE(ChallengeMissionStageDelegate*, m_pDelegate, Delegage);
    CC_SYNTHESIZE(bool, m_bTouchMoved, TouchMoved);
    void setButtonVisible(bool bVisible);
    
    void changeStageNodeTagByDir(int nDir);
private:
    ChallengeCtrl::VECSTAGE *m_vecStageInfo;
    cocos2d::CCPoint m_StagePoint[5];
    float m_fStageScale[5];
    cocos2d::CCPoint m_BeginPoint;
    CcbChallengeNodeLayer* m_pCurNode;
    
    
    cocos2d::CCRect m_layerRect;
    float m_fDistance;
    int m_nCurIndex;

};

class CcbChallengeMissionStageLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeMissionStageLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeMissionStageLayer);
};


#endif // __CCBCHALLENGEMISSIONSTAGELAYER__H__