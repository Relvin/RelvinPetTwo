/**
* CcbItemPatchLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-24 14:31:07
*/

#ifndef __CCBITEMPATCHLAYER__H__
#define __CCBITEMPATCHLAYER__H__

//CcbItemPatchLayer.h come from ccb/CcbItemPatchLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include <vector>
#include "Observer.h"

class ItemPatchScene
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    ItemPatchScene();
    ~ItemPatchScene();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(ItemPatchScene);
    bool init();
    
    
    bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    virtual void onEnter();
private:
    cocos2d::CCLabelTTF* m_pLabelTTFName;
};


class CcbItemPatchLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public CObserverMsg
{
public:
	// Constructor
    CcbItemPatchLayer();
	
	~CcbItemPatchLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemPatchLayer, create);
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
	cocos2d::CCLayer* m_pLayerForView;
	cocos2d::CCLayer* m_pLayerDown;
	cocos2d::extension::CCControlButton* m_pControlButtonJingYing;
	cocos2d::extension::CCControlButton* m_pControlButtonMySteryShop;
	cocos2d::CCLayer* m_pLayerUp;
    cocos2d::CCSprite* m_pSpriteLine;
    cocos2d::CCSprite* m_pSpriteTip_Pet;
    cocos2d::CCSprite* m_pSpriteTip_Equip;
    cocos2d::CCSprite* m_pSpriteTip_Emblem;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    //tableView相关}
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	
    //ReFresh Functions
    virtual void RefeashLayer();
public:
	// Funcitons
	void onPressControlButtonJingYing(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonMySteryShop(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTab(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    //Self Functions
    void changeShowInfoByTab(int tab);
    static bool cmpItem(uint32 index1,uint32 index2);
private:
    cocos2d::extension::CCControlButton* m_pCurButton;
    cocos2d::CCRect m_clipRect;
    cocos2d::extension::CCTableView* m_pTableView;
    std::vector<uint32> m_vecShowList;
    cocos2d::CCPoint m_offPos;
    
    void checkTip();

};

class CcbItemPatchLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbItemPatchLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbItemPatchLayer);
};


#endif // __CCBITEMPATCHLAYER__H__