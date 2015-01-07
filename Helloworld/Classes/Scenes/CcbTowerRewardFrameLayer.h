/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-07-16 10:53:35
*/

#ifndef __CCBTOWERREWARDFRAMELAYER__H__
#define __CCBTOWERREWARDFRAMELAYER__H__

//CcbTowerRewardFrameLayer.h come from ccb/climbtower_boxframe.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbItemIconLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbTowerRewardFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
{
public:
	// Constructor
	CcbTowerRewardFrameLayer()
	{
		m_pLabelTTFFloor = NULL;
		m_pLayerIcon1 = NULL;
        m_pLayerIcon2 = NULL;
        m_pLayerIcon3 = NULL;
        m_pLayerIcon4 = NULL;

	}
	~CcbTowerRewardFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbTowerRewardFrameLayer, create);
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
    
	// Attributes for CCB
	CCLabelTTF* m_pLabelTTFFloor;
	CcbItemIconLayer* m_pLayerIcon1;
    CcbItemIconLayer* m_pLayerIcon2;
    CcbItemIconLayer* m_pLayerIcon3;
    CcbItemIconLayer* m_pLayerIcon4;

    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons

    void CreateRewardData(uint16 wIndex);



};

class CcbTowerRewardFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbTowerRewardFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbTowerRewardFrameLayer);
};


#endif // __CCBTOWERREWARDFRAMELAYER__H__