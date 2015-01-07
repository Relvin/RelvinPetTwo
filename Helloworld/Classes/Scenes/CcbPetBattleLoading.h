/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-30 14:16:29
*/

#ifndef __CCBPETBATTLELOADING__H__
#define __CCBPETBATTLELOADING__H__

//CcbPetBattleLoading.h come from ccb/pet_battle_loading.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConfigData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CcbPetBattleLoading:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbPetBattleLoading()
	{
        m_pLabelTTFTips = NULL;
        m_pSpritePaint = NULL;
        m_pSpriteLvStar = NULL;
        m_pLabelTTFPetname = NULL;
        m_pLabelTTFPetDes = NULL;
	}
	~CcbPetBattleLoading();

    static CCScene* scene();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetBattleLoading, create);
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
    cocos2d::CCLabelTTF* m_pLabelTTFTips;
    cocos2d::CCSprite* m_pSpritePaint;
    cocos2d::CCSprite* m_pSpriteLvStar;
    cocos2d::CCLabelTTF* m_pLabelTTFPetname;
    cocos2d::CCLabelTTF* m_pLabelTTFPetDes;
    
    int frameCnt;
    int waitFrame;
    bool loadedAll;
    std::vector<std::string> arrPetPath;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
//    static bool needShowPad();
//    static EpitasisConfig::STC_EPITASIS_CONFIG talkData(int nIdx);
//    static int talkDataCnt();
//private:
//    static void loadTalkPad();
    
private:
    void loadBattleImg();
    void callBack(CCObject* object);

    void updateForLoadImg(float time);
    void updateForWait(float time);
};

class CcbPetBattleLoadingLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetBattleLoadingLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetBattleLoading);
};


#endif // __CCBPETBATTLELOADING__H__