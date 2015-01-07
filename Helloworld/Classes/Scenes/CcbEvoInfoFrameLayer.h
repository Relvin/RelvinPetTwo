/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-25 15:05:24
*/

#ifndef __CCBEVOINFOFRAMELAYER__H__
#define __CCBEVOINFOFRAMELAYER__H__

//CcbEvoInfoFrameLayer.h come from ccb/evo_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbEvoInfoFrameLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbEvoInfoFrameLayer()
	{
//		m_pSpriteIcon = NULL;
		m_pLabelTTFPetLv = NULL;
		m_pSpriteNext = NULL;
		m_pLabelTTFSkillName = NULL;
		m_pLabelTTFHp = NULL;
		m_pLabelTTFRev = NULL;
		m_pLabelTTFAtt = NULL;
		m_pLabelTTFDef = NULL;
		m_pLabelTTFEvoLv = NULL;

        
	}
	~CcbEvoInfoFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEvoInfoFrameLayer, create);
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
//	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFPetLv;
	cocos2d::CCSprite* m_pSpriteNext;
	cocos2d::CCLabelTTF* m_pLabelTTFSkillName;
	cocos2d::CCLabelTTF* m_pLabelTTFHp;
	cocos2d::CCLabelTTF* m_pLabelTTFRev;
	cocos2d::CCLabelTTF* m_pLabelTTFAtt;
	cocos2d::CCLabelTTF* m_pLabelTTFDef;
	cocos2d::CCLabelTTF* m_pLabelTTFEvoLv;

    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
    void loadData(uint32 evoId);




};

class CcbEvoInfoFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEvoInfoFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEvoInfoFrameLayer);
};


#endif // __CCBEVOINFOFRAMELAYER__H__