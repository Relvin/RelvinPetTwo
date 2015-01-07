/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-06-16 16:56:40
*/

#ifndef __CCBSYSTEMBOOTLOSE__H__
#define __CCBSYSTEMBOOTLOSE__H__

//CcbSystemBootLose.h come from ccb/system_boot_lose.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbSystemBootLose:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbSystemBootLose()
	{
        m_pControlButtonBack = NULL;
        m_pControlButtonTeam = NULL;
        m_pControlButtonGacha = NULL;
        m_pControlButtonEquip = NULL;
        m_pControlButtonEvo = NULL;
        m_pControlButtonEnh = NULL;

	}
	~CcbSystemBootLose();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSystemBootLose, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::extension::CCControlButton* m_pControlButtonBack;
    cocos2d::extension::CCControlButton* m_pControlButtonTeam;
    cocos2d::extension::CCControlButton* m_pControlButtonGacha;
    cocos2d::extension::CCControlButton* m_pControlButtonEquip;
    cocos2d::extension::CCControlButton* m_pControlButtonEvo;
    cocos2d::extension::CCControlButton* m_pControlButtonEnh;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


    static void showLose();
    
private:
    void checkBtn();
	
public:
	// Funcitons

    void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonTeam(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonGacha(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEvolve(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEnh(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbSystemBootLoseLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSystemBootLoseLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSystemBootLose);
};


#endif // __CCBSYSTEMBOOTLOSE__H__