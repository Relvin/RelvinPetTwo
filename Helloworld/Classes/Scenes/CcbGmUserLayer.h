/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-13 15:46:10
*/

#ifndef __CCBGMUSERLAYER__H__
#define __CCBGMUSERLAYER__H__

//CcbGmUserLayer.h come from ccb/gm_user.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbGmInsertLayer.h"

class CcbGmUserLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbGmUserLayer()
	{
		m_pLayerInsert_Lv = NULL;
		m_pLayerInsert_Coin = NULL;
		m_pLayerInsert_Dollor = NULL;
		m_pLayerInsert_Vip = NULL;
		m_pLayerInsert_Energy = NULL;
		m_pLayerInsert_Arena = NULL;
        m_pLayerInsert_Soul = NULL;
	}
	~CcbGmUserLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGmUserLayer, create);
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
	CcbGmInsertLayer* m_pLayerInsert_Lv;
    CcbGmInsertLayer* m_pLayerInsert_Coin;
    CcbGmInsertLayer* m_pLayerInsert_Dollor;
    CcbGmInsertLayer* m_pLayerInsert_Vip;
    CcbGmInsertLayer* m_pLayerInsert_Energy;
    CcbGmInsertLayer* m_pLayerInsert_Arena;
    CcbGmInsertLayer* m_pLayerInsert_Soul;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    cocos2d::CCString* getGmString();
    
private:
    void loadData();




};

class CcbGmUserLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGmUserLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGmUserLayer);
};


#endif // __CCBGMUSERLAYER__H__