/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-29 10:12:02
*/

#ifndef __CCBCHALLENGELAYER__H__
#define __CCBCHALLENGELAYER__H__

//CcbChallengeLayer.h come from ccb/pavilion_vielist.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;
class CcbChallengeLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbChallengeLayer()
	{
        m_pLabelTTFDeffenceLv = NULL;
        m_pLabelTTFDeffenceName = NULL;
        m_pLayerDefIcon_1 = NULL;
        m_pLayerDefIcon_2 = NULL;
        m_pLayerDefIcon_3 = NULL;
        m_pLayerDefIcon_4 = NULL;
        m_pLayerDefIcon_5 = NULL;
        m_pLayerDefIcon_6 = NULL;
        m_pNodeDeffencePet = NULL;
        m_pLayerGetCoin = NULL;
        m_pLayerGetEmblem = NULL;
        m_pNodeChallengeReward = NULL;
        m_pLabelTTFChallengeNum = NULL;
        m_pControlButtonGochallenge = NULL;
        m_pControlButtonClose = NULL;

	}
	~CcbChallengeLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLabelTTF* m_pLabelTTFDeffenceLv;
    cocos2d::CCLabelTTF* m_pLabelTTFDeffenceName;
    cocos2d::CCLayer* m_pLayerDefIcon_1;
    cocos2d::CCLayer* m_pLayerDefIcon_2;
    cocos2d::CCLayer* m_pLayerDefIcon_3;
    cocos2d::CCLayer* m_pLayerDefIcon_4;
    cocos2d::CCLayer* m_pLayerDefIcon_5;
    cocos2d::CCLayer* m_pLayerDefIcon_6;
    cocos2d::CCNode* m_pNodeDeffencePet;
    cocos2d::CCLayer* m_pLayerGetCoin;
    cocos2d::CCLayer* m_pLayerGetEmblem;
    cocos2d::CCNode* m_pNodeChallengeReward;
    cocos2d::CCLabelTTF* m_pLabelTTFChallengeNum;
    cocos2d::extension::CCControlButton* m_pControlButtonGochallenge;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;

    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    void loadData();

    void onPressControlButtonGochallenge(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

};

class CcbChallengeLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeLayer);
};


#endif // __CCBCHALLENGELAYER__H__