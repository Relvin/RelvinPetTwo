/**
* CcbEmblemChooseListLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-10-29 20:40:11
*/

#ifndef __CCBEMBLEMCHOOSELISTLAYER__H__
#define __CCBEMBLEMCHOOSELISTLAYER__H__

//CcbEmblemChooseListLayer.h come from ccb/badge_choose.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


USING_NS_CC;
USING_NS_CC_EXT;


class EmblemChooseListScene :
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    EmblemChooseListScene() {
        m_pLabelTTFName = NULL;
    };
    ~EmblemChooseListScene();
    
    static cocos2d::CCScene* scene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EmblemChooseListScene, create);
    
    virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    
private:
    int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

class CcbEmblemChooseListLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public CCTableViewDataSource
{
public:
	// Constructor
	CcbEmblemChooseListLayer()
	{
		m_pLayerBadgeBg = NULL;
		m_pControlButtonUnSelect = NULL;
		m_pControlButtonOk = NULL;
		m_pLabelTTFExp = NULL;
		m_pLayerBack = NULL;
        m_pControlButtonYiji = NULL;

	}
	~CcbEmblemChooseListLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEmblemChooseListLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    //tableView相关}
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerBadgeBg;
	cocos2d::extension::CCControlButton* m_pControlButtonUnSelect;
	cocos2d::extension::CCControlButton* m_pControlButtonOk;
    cocos2d::extension::CCControlButton* m_pControlButtonYiji;
	cocos2d::CCLabelTTF* m_pLabelTTFExp;
	cocos2d::CCLayer* m_pLayerBack;

    std::vector<uint32> m_arrEmbObjId;
    cocos2d::CCRect m_clipRect;
    cocos2d::extension::CCTableView* m_table;
    cocos2d::CCPoint m_tableOff;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void getArrEmbObjId();
    void reflashSelected();
	void onPressControlButtonUnSelect(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonOk(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonYiji(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbEmblemChooseListLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEmblemChooseListLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEmblemChooseListLayer);
};


#endif // __CCBEMBLEMCHOOSELISTLAYER__H__