/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-16 10:53:35
*/

#ifndef __CCBTOWERRANKFRAMELAYER__H__
#define __CCBTOWERRANKFRAMELAYER__H__

//CcbTowerRankFrameLayer.h come from ccb/climbtower_rankframe.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CcbPetIcon.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbTowerRankFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbTowerRankFrameLayer()
	{
		m_pLabelTTFFlood = NULL;
		m_pLabelTTFName = NULL;
		m_pLabelTTFRank = NULL;
		m_pLayerPetIcon = NULL;

	}
	~CcbTowerRankFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTowerRankFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
public:
	// Attributes for CCB
	CCLabelTTF* m_pLabelTTFFlood;
	CCLabelTTF* m_pLabelTTFName;
	CCLabelTTF* m_pLabelTTFRank;
	CcbPetIcon* m_pLayerPetIcon;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons

    void loadData(uint16 wIndex);



};

class CcbTowerRankFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTowerRankFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTowerRankFrameLayer);
};


#endif // __CCBTOWERRANKFRAMELAYER__H__