/**
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Junie Chu
 * Date: 2013-12-05 16:24:19
 */

#ifndef __MAINHEADLAYER__H__
#define __MAINHEADLAYER__H__

//MainHeadLayer.h come from ccb/mainhead.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Observer.h"

USING_NS_CC;
USING_NS_CC_EXT;


static const int JJC_POINT = 10;

class MainHeadLayer:
public cocos2d::CCLayer
,   public cocos2d::extension::CCBMemberVariableAssigner
,	public CCNodeLoaderListener
,   public CObserverRole
{
public:
	// Constructor
	MainHeadLayer();

	~MainHeadLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainHeadLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    float m_fExpBarWidth ;                                  // 经验进度条宽度}
    float m_fEnergyBarWidth;                                // 体力进度条宽度}
    
	// Attributes for CCB
	cocos2d::CCLabelTTF*        m_pLabelTTFCoin;            // 金币标签}
	cocos2d::CCLabelTTF*        m_pLabelTTFRonheStone;      //  融合石头}
	cocos2d::CCLabelTTF*        m_pLabelTTFDollar;          // 钻石标签}
	cocos2d::CCSprite*          m_pSpriteEnergy;            // 体力条}
	cocos2d::CCSprite*          m_pSpriteExp;               // 经验条}
	cocos2d::CCLabelTTF*        m_pLabelTTFUserName;        // 用户名}
    cocos2d::CCLabelTTF*        m_pLabelTTFUserLv;          // 用户等级，改为TTF方式}
    cocos2d::CCLabelTTF*        m_pLabelTTFEnergy;          // 体力进度条上显示的数字}
    cocos2d::CCLabelTTF*        m_pLabelTTFontTitle;        // 竞技场分组}
    cocos2d::CCLabelTTF*        m_pLabelTTFExp;             // 经验条上显示的数字}
    cocos2d::CCLabelTTF*        m_pLabelTTFArenaCnt;        // 竞技点}
    cocos2d::CCSprite*          m_pSpriteRankBadge;         // 徽章}
    cocos2d::CCLabelTTF*        m_pLabelTTFVip;             // vip等级}
    cocos2d::CCNode*            m_pNodeNotice;
    cocos2d::CCNode*            m_pNodeVip;
    CCSize winSize;
    cocos2d::CCLabelTTF*        m_pLabelTTFFightValue;
    
    void energyChanged();
    void expChanged();
    
    void setData();
    
    uint32 m_dwEnergy;
    uint32 m_dwMaxEnergy;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void dwCoinChanged(uint32 dwCoin);
    virtual void dwDollarChanged(uint32 dwDollar);
    virtual void wRoleLvChanged(uint16 wRoleLv);
    virtual void byVipLvChanged(uint8 byVip);
    virtual void strUserNameChanged(std::string strUserName);
    
    virtual void dwEnergyChanged(uint32 dwEnergy);
    virtual void dwEnergyMaxChanged(uint32 dwEnergyMax);
    
    virtual void dwRoleExpChanged(uint32 dwRoleExp);
    virtual void dwRoleMaxExpChanged(uint32 dwRoleMaxExp);

    virtual void byArenaUseCntChanged(uint8 byArenaUseCnt);
    virtual void byArenaGroupChanged(uint8 byArenaGroup);
    virtual void dwResFarmNumChanged(uint32 dwResFarmNum);
    virtual void dwRoleFightValueChanged(uint32 dwRoleFightValue);
    
public:
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

class MainHeadLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainHeadLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainHeadLayer);
};

#endif // __MAINHEADLAYER__H__