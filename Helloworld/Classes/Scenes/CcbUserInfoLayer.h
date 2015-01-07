/**
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Junie Chu
 * Date: 2014-03-20 10:40:37
 */

#ifndef __CCBUSERINFOLAYER__H__
#define __CCBUSERINFOLAYER__H__

//CcbUserInfoLayer.h come from ccb/user_info.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

class CcbPetIcon;
class CcbUserInfoLayer:
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CObserverRole
,   public CObserverMsg
{
public:
	// Constructor
	CcbUserInfoLayer()
    : m_bMusicBg(true)
    , m_bMusicEffect(true)
    , m_pControlButtonUserCenter(NULL)
    , m_pControlButtonAnnounce(NULL)
    , m_pControlButtonMusic(NULL)
    , m_pControlButtonEffect(NULL)
    , m_pControlButtonExit(NULL)
    , m_pLabelEffect(NULL)
    , m_pLabelMusic(NULL)
    , m_pLabelTTFVip(NULL)
    , m_pLabelTTFUserLv(NULL)
    , m_pLabelTTF_Alliance(NULL)
    , m_pLabelTTFontTitle(NULL)
    , m_pControlButtonGoexchange(NULL)
    , m_pControlButtonGoVip(NULL)
	{
		m_pSpriteEnergy = NULL;
		m_pSpriteExp = NULL;
		m_pLabelTTFRecTime = NULL;
		m_pLabelTTFRecAll = NULL;
		m_pLabelTTFPetCnt = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFCoin = NULL;
		m_pLabelTTFDollar = NULL;
		m_pLabelTTFRonheStone = NULL;
		m_pLabelTTFExpDes = NULL;
		m_pLabelTTFEnergyDes = NULL;
        m_pControlButtonClose = NULL;
        m_pLayerHeadIcon = NULL;
        m_pLabelTTFID = NULL;
        m_pControlButtonOk = NULL;
        
	}
	~CcbUserInfoLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbUserInfoLayer, create);
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
    
    CcbPetIcon* m_pLayerHeadIcon;
    
	cocos2d::CCSprite* m_pSpriteEnergy;
	cocos2d::CCSprite* m_pSpriteExp;
	cocos2d::CCLabelTTF* m_pLabelTTFRecTime;
	cocos2d::CCLabelTTF* m_pLabelTTFRecAll;
	cocos2d::CCLabelTTF* m_pLabelTTFPetCnt;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFCoin;
	cocos2d::CCLabelTTF* m_pLabelTTFDollar;
	cocos2d::CCLabelTTF* m_pLabelTTFRonheStone;
	cocos2d::CCLabelTTF* m_pLabelTTFExpDes;
	cocos2d::CCLabelTTF* m_pLabelTTFEnergyDes;
    cocos2d::CCLabelTTF* m_pLabelTTFID;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::extension::CCControlButton* m_pControlButtonOk;
    
    cocos2d::extension::CCControlButton* m_pControlButtonUserCenter;
    cocos2d::extension::CCControlButton* m_pControlButtonAnnounce;
    cocos2d::extension::CCControlButton* m_pControlButtonMusic;
    cocos2d::extension::CCControlButton* m_pControlButtonEffect;
    cocos2d::extension::CCControlButton* m_pControlButtonExit;
    cocos2d::CCLabelTTF* m_pLabelEffect;
    cocos2d::CCLabelTTF* m_pLabelMusic;
    cocos2d::CCLabelTTF* m_pLabelTTFVip;
    cocos2d::CCLabelTTF* m_pLabelTTFUserLv;
    cocos2d::CCLabelTTF* m_pLabelTTF_Alliance;
    cocos2d::CCLabelTTF* m_pLabelTTFontTitle;
    cocos2d::extension::CCControlButton* m_pControlButtonGoexchange;
    cocos2d::extension::CCControlButton* m_pControlButtonGoVip;
    
    uint16 m_wLeaderIndexId;
    
    uint32 m_dwCurEnergy;
    uint32 m_dwEnergyMax;
    
    uint32 m_dwExpMax;
    uint32 m_dwCurExp;
    
    float m_fEnergyBarWidth;
    float m_fExpBarWidth;
    
    uint32 m_dwRecTime;
    
    uint32 m_dwRecAllTime;
    int m_nNeedEnergy;
    
    
    bool touchFlag;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    void updateTime(float dTime);
	
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonSet(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonFriend(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonExit(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonAnnounce(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonMusicCallBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEffectCallBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonUserCenter(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonExchange(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonGoVip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
public:
	// Funcitons
    virtual void dwDollarChanged(uint32 dwDollar);
    virtual void dwCoinChanged(uint32 dwCoin);
    virtual void dwResFarmNumChanged(uint32 dwResFarmNum);
    virtual void dwEnergyChanged(uint32 dwEnergy);
    
    virtual void RefeashLayer();
    void changeMusicButtonStatus();
private:
    bool m_bMusicBg;
    bool m_bMusicEffect;
};

class CcbUserInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbUserInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbUserInfoLayer);
};


#endif // __CCBUSERINFOLAYER__H__