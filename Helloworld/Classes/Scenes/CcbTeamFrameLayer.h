/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-24 22:01:41
*/

#ifndef __CCBTEAMFRAMELAYER__H__
#define __CCBTEAMFRAMELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbTeamMemberLayer;
class CcbTeamLayer;
class CcbTeamFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbTeamFrameLayer()
	{
		m_pLabelTTFTeamId = NULL;
		
		m_pLabelTTFLeaderSkillName = NULL;
		m_pLabelTTFLeaderSkillDes = NULL;
		m_pLayerMask = NULL;
		m_pSpritePetBg_2 = NULL;
		m_pSpritePetBg_4 = NULL;
		m_pSpritePetBg_6 = NULL;
		m_pSpritePetBg_1 = NULL;
		m_pSpritePetBg_3 = NULL;
		m_pSpritePetBg_5 = NULL;
		m_pLayerMember_2 = NULL;
		m_pLayerMember_4 = NULL;
		m_pLayerMember_6 = NULL;
		m_pLayerMember_1 = NULL;
		m_pLayerMember_3 = NULL;
		m_pLayerMember_5 = NULL;
        m_pLabelTTFSetLeader = NULL;
	}
	~CcbTeamFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTeamFrameLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFTeamId;
	
	cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillName;
	cocos2d::CCLabelTTF* m_pLabelTTFLeaderSkillDes;
	cocos2d::CCLayer* m_pLayerMask;
	cocos2d::CCSprite* m_pSpritePetBg_2;
	cocos2d::CCSprite* m_pSpritePetBg_4;
	cocos2d::CCSprite* m_pSpritePetBg_6;
	cocos2d::CCSprite* m_pSpritePetBg_1;
	cocos2d::CCSprite* m_pSpritePetBg_3;
	cocos2d::CCSprite* m_pSpritePetBg_5;
	CcbTeamMemberLayer* m_pLayerMember_2;
	CcbTeamMemberLayer* m_pLayerMember_4;
	CcbTeamMemberLayer* m_pLayerMember_6;
	CcbTeamMemberLayer* m_pLayerMember_1;
	CcbTeamMemberLayer* m_pLayerMember_3;
	CcbTeamMemberLayer* m_pLayerMember_5;
    CCLabelTTF* m_pLabelTTFSetLeader;
    uint8 m_wTeamId;
    //key就是site，不管怎么变，key与site对应}
    std::map<uint8, CcbTeamMemberLayer*> m_mapMember;
    CCSprite *arrMemBg[7];
    CcbTeamMemberLayer *arrMembers[7];
//    std::vector<cocos2d::CCSprite*> arrPetSpriteBg;
    CCPoint arrPos[7];
    CCPoint posFrom;
    bool isMove;
    bool isChgLeader;
    uint8 m_bySiteFrom;
    uint8 m_byMoveSite;
    CcbTeamMemberLayer* m_FromPet;
    
    CcbTeamLayer* m_delegate;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
	
public:
	// Funcitons

    void setTeamId(uint16 wTeamId);
    void loadData();
    
//    void hidePetBaseValue();
    void showPetBaseValue(bool isShow);
    void startLeaderChg();
    void setDelegate(CcbTeamLayer* delegate){m_delegate = delegate;};
private:
    void chgLeader(uint8 bySite);
    void chgSiteFrom(uint8 bySiteFrom);
    
    void chgSiteTo(uint8 bySiteTo);
    void moveBack(uint8 bysite);
    
    void endLeaderChg();
    
    void resetZorder();
};

class CcbTeamFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTeamFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTeamFrameLayer);
};


#endif // __CCBTEAMFRAMELAYER__H__