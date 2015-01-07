/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-15 18:34:37
*/

#ifndef __CCBSORTLAYER__H__
#define __CCBSORTLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
USING_NS_CC;

class CObserverMsg;
class CcbPetBagLayer;

class CcbSortLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBSelectorResolver,
	public cocos2d::extension::CCBMemberVariableAssigner,
	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbSortLayer()
	{
		m_pControlButtonLv = NULL;
		m_pControlButtonAttack = NULL;
		m_pControlButtonStar = NULL;
		m_pControlButtonNature = NULL;
		m_pControlButtonBirthday = NULL;
		m_pControlButtonDefense = NULL;
		m_pControlButtonRecover = NULL;
        m_pControlButtonClose = NULL;
        m_pControlButtonHP = NULL;
        m_pControlButtonSpeDefense = NULL;
	}
	~CcbSortLayer();

	// must have
//	static cocos2d::CCScene* scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbSortLayer, create);
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );

	// option
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonLv;
	cocos2d::extension::CCControlButton* m_pControlButtonAttack;
	cocos2d::extension::CCControlButton* m_pControlButtonStar;
	cocos2d::extension::CCControlButton* m_pControlButtonNature;
	cocos2d::extension::CCControlButton* m_pControlButtonBirthday;
	cocos2d::extension::CCControlButton* m_pControlButtonDefense;
	cocos2d::extension::CCControlButton* m_pControlButtonRecover;
    cocos2d::extension::CCControlButton* m_pControlButtonClose;
    cocos2d::extension::CCControlButton* m_pControlButtonHP;
    cocos2d::extension::CCControlButton* m_pControlButtonSpeDefense;
    CObserverMsg *m_delegate;

    std::vector<cocos2d::extension::CCControlButton*> arrSortButton;
    std::vector<std::string> arrBtnName;
    
    bool bFlag;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

    void setOwner(CObserverMsg *delegate){m_delegate = delegate;};
	void onShow();
    void onHide();
private:
    void changeButton(uint8 old, uint8 sortType);
    
    void loadData();
public:
	// Funcitons

    void onPressControlButtonSort(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    
//	void onPressControlButtonLv(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonAttack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonStar(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonNature(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonBirthday(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonDefense(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonRecover(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbSortLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbSortLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbSortLayer);
};


#endif // __CCBSORTLAYER__H__