/**
* CcbChallengeNodeLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-14 18:35:04
*/

#ifndef __CCBCHALLENGENODELAYER__H__
#define __CCBCHALLENGENODELAYER__H__

//CcbChallengeNodeLayer.h come from ccb/CcbChallengeNodeLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbChallengeNodeLayer;
class ChallengeNodeClickedDelegate
{
public:
    virtual void challengeNodeClicked(CcbChallengeNodeLayer* pNode) = 0;
};

class CcbChallengeNodeLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
    
	// Constructor
    CcbChallengeNodeLayer();
	~CcbChallengeNodeLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeNodeLayer, create);
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
	cocos2d::CCSprite* m_pSpriteMissioonbg;
	cocos2d::CCSprite* m_pSpriteLock;
	cocos2d::CCLabelTTF* m_pLabelTTFMissionName;
    cocos2d::CCLabelTTF* m_pLabelTTFTimes;
	cocos2d::CCNode* m_pNodeName1;
	cocos2d::CCSprite* m_pSpriteDropicon;
    cocos2d::extension::CCControlButton* m_pControlButton;
    cocos2d::CCSprite* m_pSpriteSelected;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void onPressControlButtonClickedCallBack(cocos2d::CCObject *pObject, cocos2d::extension::CCControlEvent event);
    
    CC_SYNTHESIZE(uint8, m_byChallengeStage, ChallengeStage);   //选择挑战的关卡
    CC_SYNTHESIZE(uint32, m_dwIndex, ChallengeStageIndex); //挑战的关卡Id
    void setChallengeNodeInfoByIndex(uint32 dwIndex);
    void setDropItemIconVisible(bool bVisible);
    bool getDropItemIconVisible(){return m_pSpriteDropicon->getParent()->isVisible();};
    void setAttackCntVisible(bool bVisible);
    bool getAttackCntVisible(){return m_pLabelTTFTimes->getParent()->isVisible();};
    void setChallengeBackground(cocos2d::CCSpriteFrame* pSpriteFrame);
    void setLockVisible(bool isVisible);
    bool getLockVisible() {return m_pSpriteLock->isVisible();};
    void setShowTitle(const char* strTitle);
    void setSelectSpriteVisible(bool isVisible);
    cocos2d::extension::CCControlButton* getControlButton() {return m_pControlButton;};
    void onStageNodeButtonClicked();
    CC_SYNTHESIZE(ChallengeNodeClickedDelegate *, m_pDelegate, Delegate);
private:

    bool m_bCntVisible;
    bool m_bLockVisible;
    bool m_bDropItemVisible;

};

class CcbChallengeNodeLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeNodeLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeNodeLayer);
};


#endif // __CCBCHALLENGENODELAYER__H__