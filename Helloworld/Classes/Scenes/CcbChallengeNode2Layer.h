/**
* CcbChallengeNode2Layer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-15 14:35:49
*/

#ifndef __CCBCHALLENGENODE2LAYER__H__
#define __CCBCHALLENGENODE2LAYER__H__

//CcbChallengeNode2Layer.h come from ccb/CcbChallengeNode2Layer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CCScrollButton.h"


class CcbChallengeNode2Layer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
    CcbChallengeNode2Layer();
	~CcbChallengeNode2Layer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbChallengeNode2Layer, create);
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
	cocos2d::CCSprite* m_pSpriteBg;
	cocos2d::CCLayer* m_pLayerDrops;
	cocos2d::CCSprite* m_pSpriteLock;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    // TableView Functions
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx) ;
    virtual unsigned int numberOfCellsInTableView(CCTableView *table) ;
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx) ;

public:
	// Funcitons
    void onPressControlButtonNode(CCObject* pObject, CCControlEvent event);

    // Self Functions
    void setChallengeNodeInfoByIndex(uint16 wIndex);
    void setClipRect(CCRect rect);

    CC_SYNTHESIZE(uint16, m_wMapId, MapId);
    CC_SYNTHESIZE(uint16, m_wRoleLvLimit, RoleLvLimit);
    CC_SYNTHESIZE(std::string, m_strMapName, StrMapName);
private:
    CCScrollButton* m_pScrollButtonNode;
    cocos2d::extension::CCTableView* m_pTableView;
};

class CcbChallengeNode2LayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbChallengeNode2LayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbChallengeNode2Layer);
};


#endif // __CCBCHALLENGENODE2LAYER__H__