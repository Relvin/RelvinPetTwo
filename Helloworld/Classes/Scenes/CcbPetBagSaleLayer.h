/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-01 11:16:47
*/

#ifndef __CCBPETBAGSALELAYER__H__
#define __CCBPETBAGSALELAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbSortLayer.h"
//#include "PetIconCtrl.h"
#include "SystemMessage.h"
#include "CcbPetIconCtrl.h"
#include "Observer.h"

class PetBagSaleScene :
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
    PetBagSaleScene()
	{
        m_pLabelTTFName  = NULL;
	}
	~PetBagSaleScene();
    
    static cocos2d::CCScene *scene();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PetBagSaleScene, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
    cocos2d::CCLabelTTF* m_pLabelTTFName;
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
};


class CcbPetBagSaleLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public cocos2d::extension::CCTableViewDataSource
,   public CObserverMsg
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbPetBagSaleLayer()
	{
		m_pLayerPetBg = NULL;
		m_pControlButtonSort = NULL;
		m_pLabelTTFMoney = NULL;
		m_pLabelTTFExp = NULL;
		m_pLayerBack = NULL;
        m_pLabelTTFCurCount = NULL;
        m_pLabelTTFMaxCount = NULL;
        m_pLabelTTFMoneyText = NULL;
        
        m_sortLayer = NULL;
	}
	~CcbPetBagSaleLayer();

    static CcbPetBagSaleLayer* shareLayer(){return m_shareLayer;};
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetBagSaleLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    //tableView相关}
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
private:
    static CcbPetBagSaleLayer * m_shareLayer;
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerPetBg;
	cocos2d::extension::CCControlButton* m_pControlButtonSort;
	cocos2d::CCLabelTTF* m_pLabelTTFMoney;
	cocos2d::CCLabelTTF* m_pLabelTTFExp;
	cocos2d::CCLayer* m_pLayerBack;
    cocos2d::CCLabelTTF* m_pLabelTTFCurCount;
	cocos2d::CCLabelTTF* m_pLabelTTFMaxCount;
    cocos2d::CCLabelTTF* m_pLabelTTFMoneyText;
//    cocos2d::extension::CCScrollView *pScrollViewBag;
    cocos2d::extension::CCTableView *m_table;
    
    std::map<uint32, CcbPetIconCtrl*> m_mapPetIcon;
    std::vector<uint32> m_arrPetObjId;
    CcbSortLayer *m_sortLayer;
    CCRect m_clipRect;
    cocos2d::CCPoint m_scrollOff;
    bool bFlag;
    
private:
    void clearSelected();
    void checkSale();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    virtual void RefeashLayer();
	virtual void systemMessageOKTapped(SystemMessage *systemMessage);
public:
	// Funcitons


	void onPressControlButtonSort(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonUnSelete(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonOk(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);


    void loadPet();
//	void RefeashLayer();
    
    void initSortLayer();
    void sortPetBag(std::vector<uint32> arrPetObjId);
    
    void ReflashPetBagNum();

};

class CcbPetBagSaleLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetBagSaleLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetBagSaleLayer);
};


#endif // __CCBPETBAGSALELAYER__H__