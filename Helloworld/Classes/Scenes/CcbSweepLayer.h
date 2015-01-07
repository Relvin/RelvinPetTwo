/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-21 21:18:41
*/

#ifndef __CCBSWEEPLAYER__H__
#define __CCBSWEEPLAYER__H__

//CcbSweepLayer.h come from ccb/fight_bot.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "ReCountDown.h"
#include "WorldPacket.h"
#include "Observer.h"

class CcbSweepLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public ReCountDownDelegate
, public CObserverMsg
, public CObserverRole
{
public:
    enum
    {
//        (1, 请求钻石; 2, 清除CD)
        ENUM_REQDIAMOND = 1,
        ENUM_CLEARCD = 2,
    };
    
    static CcbSweepLayer* shareInstance();
	// Constructor
	CcbSweepLayer()
    : m_pSpriteTicket(NULL)
    , m_pControlButtonClear(NULL)
    , m_pLabelTTFCostDaimond(NULL)
    , m_pLabelCountDown(NULL)
    , m_pCountDown(NULL)
    , m_nClearCDDollar(0)
	{
		m_pControlButtonPlus = NULL;
		m_pControlButtonMinus = NULL;
		m_pLabelTTFCnt = NULL;
		m_pLabelTTFEnergy = NULL;
		m_pControlButtonOk = NULL;
		m_pControlButtonBack = NULL;
        m_pLabelTTFLeftInfo = NULL;
	}
	~CcbSweepLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSweepLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonPlus;
	cocos2d::extension::CCControlButton* m_pControlButtonMinus;
	cocos2d::CCLabelTTF* m_pLabelTTFCnt;
	cocos2d::CCLabelTTF* m_pLabelTTFEnergy;
	cocos2d::extension::CCControlButton* m_pControlButtonOk;
	cocos2d::extension::CCControlButton* m_pControlButtonBack;
    cocos2d::CCLabelTTF* m_pLabelTTFLeftInfo;
    cocos2d::CCSprite* m_pSpriteTicket;
    cocos2d::extension::CCControlButton* m_pControlButtonClear;
    cocos2d::CCLabelTTF* m_pLabelTTFCostDaimond;
    cocos2d::CCLabelTTF* m_pLabelCountDown;

    uint16 m_wStageId;
    int m_nMaxCnt;
    int m_nCurCnt;
    uint8 m_byCostEnergy;
    
    
    void refreashText();
    //重新刷界面}
    virtual void RefeashLayer();
    virtual void dwSweepCDTimeChanged(uint32 dwSweepCDTime);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    // CountDown Functions
    void countDownScheduleCallBack(float cTime,CountType type);
    
    // Receive Function

    void handlerClearSweepCDTimeResult(WorldPacket& packet);
public:
	// Funcitons
	void onPressControlButtonPlus(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonMinus(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonOk(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClear(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
private:
    ReCountDown* m_pCountDown;
    uint32  m_nClearCDDollar;
};

class CcbSweepLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSweepLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSweepLayer);
};


#endif // __CCBSWEEPLAYER__H__