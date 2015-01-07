/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-08 10:32:33
*/

#ifndef __CCBEMBLEMINFOLAYER__H__
#define __CCBEMBLEMINFOLAYER__H__

//CcbEmblemInfoLayer.h come from ccb/badge_wear.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "EmblemDataMgr.h"
#include "CcbItemIconLayer.h"

class CcbEmblemInfoLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbEmblemInfoLayer()
	{
		m_pLayerBadgeBg = NULL;
		m_pLayerIcon = NULL;
		m_pLabelTTFName = NULL;
		m_pSpriteStar = NULL;
		m_pLabelTTFLevel = NULL;
		m_pLabelTTFAttri1 = NULL;
		m_pLabelTTFAttri2 = NULL;
		m_pLabelTTFAttri3 = NULL;
		m_pControlButtonClose = NULL;
        m_pLabelTTFAttr_1 = NULL;
        m_pLabelTTFAttr_2 = NULL;
        m_pLabelTTFAttr_3 = NULL;
        
	}
	~CcbEmblemInfoLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEmblemInfoLayer, create);
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
	
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerBadgeBg;
	cocos2d::CCLabelTTF* m_pLabelTTFName;
	cocos2d::CCSprite* m_pSpriteStar;
	cocos2d::CCLabelTTF* m_pLabelTTFLevel;
	cocos2d::CCLabelTTF* m_pLabelTTFAttri1;
	cocos2d::CCLabelTTF* m_pLabelTTFAttri2;
	cocos2d::CCLabelTTF* m_pLabelTTFAttri3;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_1;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_2;
    cocos2d::CCLabelTTF* m_pLabelTTFAttr_3;

	cocos2d::extension::CCControlButton* m_pControlButtonClose;
    CcbItemIconLayer* m_pLayerIcon;
    uint32 m_dwEmbObjId;
    std::vector<STC_EXC_PET> arrPet;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	static void showEmblemInfo(uint32 dwEmbObjId);
public:
	// Funcitons


	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void setEmblemObjId(uint32 dwEmbObjId);
    void loadData();
    
private:
    CCTableView* m_pTableView;
    

};

class CcbEmblemInfoLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEmblemInfoLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEmblemInfoLayer);
};


#endif // __CCBEMBLEMINFOLAYER__H__