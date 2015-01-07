/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-24 22:54:28
*/

#ifndef __CCBBATTLETEAMSHOWLAYER__H__
#define __CCBBATTLETEAMSHOWLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "Team.h"

class CTeam;
class CcbPetIcon;
class CcbBattleTeamShowLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbBattleTeamShowLayer()
	{
        m_pSpriteLeader = NULL;
        m_pLayerM6 = NULL;
        m_pLayerM1 = NULL;
        m_pLayerM2 = NULL;
        m_pLayerM3 = NULL;
        m_pLayerM4 = NULL;
        m_pLayerM5 = NULL;
        m_pControlButtonTeam = NULL;
		m_pLabelTTFLeaderDes = NULL;
		m_pLabelTTFLeaderName = NULL;

        m_pLabelTTFTeamId = NULL;
	}
	~CcbBattleTeamShowLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbBattleTeamShowLayer, create);
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

    cocos2d::CCSprite* m_pSpriteLeader;
    cocos2d::CCLayer* m_pLayerM6;
    cocos2d::CCLayer* m_pLayerM1;
    cocos2d::CCLayer* m_pLayerM2;
    cocos2d::CCLayer* m_pLayerM3;
    cocos2d::CCLayer* m_pLayerM4;
    cocos2d::CCLayer* m_pLayerM5;
    cocos2d::extension::CCControlButton* m_pControlButtonTeam;
	cocos2d::CCLabelTTF* m_pLabelTTFLeaderDes;
	cocos2d::CCLabelTTF* m_pLabelTTFLeaderName;

    cocos2d::CCLabelTTF* m_pLabelTTFTeamId;
    
    CcbPetIcon* m_pBossIcon[6];
    cocos2d::extension::CCControlButton *m_pPetBtn[6];
    CTeam *m_team;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
    void onPressControlButtonTeam(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void SetTeamInfo(CTeam* teamInfo);
};

class CcbBattleTeamShowLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbBattleTeamShowLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbBattleTeamShowLayer);
};


#endif // __CCBBATTLETEAMSHOWLAYER__H__