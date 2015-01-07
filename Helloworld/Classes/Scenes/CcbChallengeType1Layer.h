/**
* CcbChallengeType1Layer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-15 19:49:26
*/

#ifndef __CCBCHALLENGETYPE1LAYER__H__
#define __CCBCHALLENGETYPE1LAYER__H__

//CcbChallengeType1Layer.h come from ccb/CcbChallengeType1Layer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbChallengeMissionStageLayer.h"
#include "CcbItemIconLayer.h"


class ReRichText;
class CcbChallengeType1Layer;
class ChallengeType1Scene
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    ChallengeType1Scene();
    ~ChallengeType1Scene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(ChallengeType1Scene);
    bool init();
    
    
    bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onEnter();
//    void onPressControlButtonClickedCallBack;
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    CcbChallengeType1Layer* m_pChallengeType1Layer;
};

class CcbChallengeType1Layer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public ChallengeMissionStageDelegate
, public ItemIconTouchDelegate
{
public:
	// Constructor
    CcbChallengeType1Layer();
	~CcbChallengeType1Layer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeType1Layer, create);
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
	cocos2d::CCNode* m_pNodeTeam;
	cocos2d::CCLabelTTF* m_pLabelTTFDescribe;
	cocos2d::CCNode* m_pNodeReward;
    CcbChallengeMissionStageLayer* m_pMissionStageLayer;
    cocos2d::CCLabelTTF* m_pLabelTTFEnergy;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftCnt;
    cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillName;
    cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillDes;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    //Challenge Mission delegate
    virtual void updateCurrentLayerInfoByIndex(uint32 dwIndex);
    
    virtual void itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId) ;
public:
	// Funcitons
    void onPressControlButtonBattle(CCObject* pObject, cocos2d::extension::CCControlEvent event);
    
    void loadBattleTeamInfo();
    bool getTouchMoved(){ return m_pMissionStageLayer->getTouchMoved();};
private:
    ReRichText* m_pRerichText;
    CcbItemIconLayer* m_pItemIcon[6];
    cocos2d::CCSprite* m_pBattleType[6];
    cocos2d::CCSprite* m_pSpriteTip[6];
    int m_nCurIndex;
    


};

class CcbChallengeType1LayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeType1LayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeType1Layer);
};


#endif // __CCBCHALLENGETYPE1LAYER__H__