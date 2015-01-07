/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-12-20 17:56:59
*/

#ifndef __CCBBUILDUPLAYER__H__
#define __CCBBUILDUPLAYER__H__

//CcbBuildUpLayer.h come from ccb/build_up.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BuildUpScene.h"

class CcbBuildUpLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbBuildUpLayer()
	{
		m_pControlButtonUpFarm = NULL;
		m_pSpriteFarm = NULL;
		m_pLabelBMFontFarmLv = NULL;
		m_pLabelTTFFarmCoin = NULL;
		m_pLabelTTFFarmCH = NULL;
		m_pControlButtonMine = NULL;
		m_pSpriteMine = NULL;
		m_pLabelBMFontMineLv = NULL;
		m_pLabelTTFMineCoin = NULL;
		m_pLabelTTFMineCH = NULL;
		m_pControlButtonTree = NULL;
		m_pSpriteTree = NULL;
		m_pLabelBMFontTreeLv = NULL;
		m_pLabelTTFTreeCoin = NULL;
		m_pLabelTTFTreeCH = NULL;
		m_pControlButtonRiver = NULL;
		m_pSpriteRiver = NULL;
		m_pLabelBMFontRiverLv = NULL;
		m_pLabelTTFRiverCoin = NULL;
		m_pLabelTTFRiverCH = NULL;
        m_shared = NULL;
	}
	~CcbBuildUpLayer();

    static CcbBuildUpLayer* GetCurLayer();
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbBuildUpLayer, create);
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
	cocos2d::extension::CCControlButton* m_pControlButtonUpFarm;
	cocos2d::CCSprite* m_pSpriteFarm;
	cocos2d::CCLabelBMFont* m_pLabelBMFontFarmLv;
	cocos2d::CCLabelTTF* m_pLabelTTFFarmCoin;
	cocos2d::CCLabelTTF* m_pLabelTTFFarmCH;
	cocos2d::extension::CCControlButton* m_pControlButtonMine;
	cocos2d::CCSprite* m_pSpriteMine;
	cocos2d::CCLabelBMFont* m_pLabelBMFontMineLv;
	cocos2d::CCLabelTTF* m_pLabelTTFMineCoin;
	cocos2d::CCLabelTTF* m_pLabelTTFMineCH;
	cocos2d::extension::CCControlButton* m_pControlButtonTree;
	cocos2d::CCSprite* m_pSpriteTree;
	cocos2d::CCLabelBMFont* m_pLabelBMFontTreeLv;
	cocos2d::CCLabelTTF* m_pLabelTTFTreeCoin;
	cocos2d::CCLabelTTF* m_pLabelTTFTreeCH;
	cocos2d::extension::CCControlButton* m_pControlButtonRiver;
	cocos2d::CCSprite* m_pSpriteRiver;
	cocos2d::CCLabelBMFont* m_pLabelBMFontRiverLv;
	cocos2d::CCLabelTTF* m_pLabelTTFRiverCoin;
	cocos2d::CCLabelTTF* m_pLabelTTFRiverCH;

    static CcbBuildUpLayer* m_shared;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons

    void UpdateInfo(CBuildUpDataMgr::MAP_INFO map_build);
	void onPressControlButtonFarm(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonMine(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTree(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRiver(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void onPressUpgrade(uint8 byType);

};

class CcbBuildUpLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbBuildUpLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbBuildUpLayer);
};


#endif // __CCBBUILDUPLAYER__H__