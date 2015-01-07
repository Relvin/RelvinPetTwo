/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-12 10:49:11
*/

#ifndef __CcbArenaBattleListLayer__H__
#define __CcbArenaBattleListLayer__H__

//CcbArenaBattleListLayer.h come from ccb/arena_fight_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "SystemMessageProtocol.h"
USING_NS_CC;
USING_NS_CC_EXT;
class CCScrollButton;
class CcbPetIcon;
class CcbArenaBattleListLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbArenaBattleListLayer();
	~CcbArenaBattleListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbArenaBattleListLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;

    // Attributes for CCB
	CCScrollButton* m_pControlButtonBattle;
	cocos2d::CCSprite* m_pSpriteCrown;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCLabelTTF* m_pLabelTTFRank;
//	cocos2d::CCLabelTTF* m_pLabelTTFRankWin;
//	cocos2d::CCLabelTTF* m_pLabelTTFRankLose;
//	cocos2d::CCLabelTTF* m_pLabelTTFMoney;
//	cocos2d::CCLabelTTF* m_pLabelTTFReputation;
//	cocos2d::CCLabelTTF* m_pLabelTTFDayReputation;
    cocos2d::CCLabelTTF* m_pLabelFightScore;
    cocos2d::CCNode* m_pNodeUserteam;
    cocos2d::CCLabelTTF* m_pLabelTTFUserLv;
    
    int m_localTag;
    uint8 m_byType;
    cocos2d::CCRect m_ClipRect;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

	void addGuideLayer();
    void updateLayerInfo();
    
private:
    void onBuyUse();
public:
	// Funcitons
	void onPressControlButtonBattle(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadData(int localTag, uint8 byType);
    void setClipRect(CCRect rect);
};

class CcbArenaBattleListLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbArenaBattleListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbArenaBattleListLayer);
};


#endif // __CcbArenaBattleListLayer__H__