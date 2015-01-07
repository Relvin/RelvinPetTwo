/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-08-15 14:14:20
*/

#ifndef __CCBMAINTEAMLAYER__H__
#define __CCBMAINTEAMLAYER__H__

//CcbMainTeamLayer.h come from ccb/mainteam.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbMainPetCardLayer.h"

class CcbMainTeamLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbMainTeamLayer()
	{
		m_pLayerMember_1 = NULL;
		m_pLayerMember_2 = NULL;
		m_pLayerMember_3 = NULL;
		m_pLayerMember_4 = NULL;
		m_pLayerMember_5 = NULL;
		m_pLayerMember_6 = NULL;

	}
	~CcbMainTeamLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbMainTeamLayer, create);
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
	CcbMainPetCardLayer* m_pLayerMember_1;
	CcbMainPetCardLayer* m_pLayerMember_2;
	CcbMainPetCardLayer* m_pLayerMember_3;
	CcbMainPetCardLayer* m_pLayerMember_4;
	CcbMainPetCardLayer* m_pLayerMember_5;
	CcbMainPetCardLayer* m_pLayerMember_6;


    int m_wTeamId;
    std::map<uint16, CcbMainPetCardLayer*> m_mapMember;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void setTeamId(uint16 wTeamId);
    
private:
    void loadData();



};

class CcbMainTeamLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbMainTeamLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbMainTeamLayer);
};


#endif // __CCBMAINTEAMLAYER__H__