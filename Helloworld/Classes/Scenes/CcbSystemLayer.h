/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-22 22:56:16
*/

#ifndef __CCBSYSTEMLAYER__H__
#define __CCBSYSTEMLAYER__H__

//CcbSystemLayer.h come from ccb/system.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SystemScene : public cocos2d::CCLayer
,   	public cocos2d::extension::CCBMemberVariableAssigner
{
    SystemScene() {
        m_pLabelTTFName = NULL;
    };
    ~SystemScene() {
        CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    };
    
    CREATE_FUNC(SystemScene);
    // Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
    
    cocos2d::CCLabelTTF* m_pLabelTTFName;
public:
    static cocos2d::CCScene* scene();
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
    virtual void onExit();
};

#pragma mark ---

class CcbSystemLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
{
public:
	// Constructor
	CcbSystemLayer()
	{
        m_pLayerHeadBack = NULL;
        m_pLayerViewSize = NULL;
        
        m_pTableList = NULL;
        m_fDelta = 0.02f;
        m_bRestored = false;
        m_vecCell.clear();
        m_nTableCnt = 0;
	}
	~CcbSystemLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSystemLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLayer* m_pLayerHeadBack;
    cocos2d::CCLayer* m_pLayerViewSize;
    
    cocos2d::extension::CCTableView* m_pTableList;
    
    int m_nTableCnt;
    
    typedef struct _STC_SYS {
        std::string strName;
        int nTag;
    }STC_SYS;
    
    std::vector<STC_SYS> m_vecSystem;
    std::vector<CCNode*> m_vecCell;
    
    CCSize winSize;
    bool m_bRestored;
    float m_fDelta;
    float m_fDelay;
    void setTouchRestore();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    // CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView* table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual CCSize cellSizeForTable(CCTableView *table);
};

class CcbSystemLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSystemLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSystemLayer);
};


#endif // __CCBSYSTEMLAYER__H__