/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-04-28 16:28:54
*/

#ifndef __CCBSETTINGSLAYER__H__
#define __CCBSETTINGSLAYER__H__

//CcbSettingsLayer.h come from ccb/settings.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;

class CcbSettingsLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCNodeLoaderListener
,   public CCTableViewDataSource
{
public:
	// Constructor
	CcbSettingsLayer()
	{
		m_pLayerView = NULL;
        m_tableView = NULL;
        m_fCellWidth = m_fCellHeight = 0.0f;
	}
	~CcbSettingsLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSettingsLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );

	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    //tableView相关}
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	CCLayer* m_pLayerView;
    CCTableView* m_tableView;
    
    float m_fCellWidth, m_fCellHeight;

    typedef struct _STC_SETTING {
        std::string strName;
        int nTag;
    }STC_SETTING;
    
    std::vector<STC_SETTING> m_vecSetting;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

};

class CcbSettingsLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSettingsLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSettingsLayer);
};


#endif // __CCBSETTINGSLAYER__H__