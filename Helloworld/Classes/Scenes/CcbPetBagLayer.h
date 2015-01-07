/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-15 14:10:35
*/

#ifndef __CCBPETBAGLAYER__H__
#define __CCBPETBAGLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "CcbSortLayer.h"
#include "CcbPetIconCtrl.h"
#include "Observer.h"
#define cellCnt 5

class PetBagScene:
public cocos2d::CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	// Constructor
	PetBagScene()
	{
        m_pLabelTTFName = NULL;
	}
	~PetBagScene();
    
	// must have
	static cocos2d::CCScene* scene();
    
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PetBagScene, create);
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );

    virtual bool onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue);
    
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLabelTTF* m_pLabelTTFName;
};


class CcbPetBagLayer:
	public cocos2d::CCLayer,
    public cocos2d::extension::CCBMemberVariableAssigner,
	public cocos2d::extension::CCBSelectorResolver,
	public cocos2d::extension::CCNodeLoaderListener,
    public cocos2d::extension::CCTableViewDataSource,
    public CObserverRole
{
public:
	// Constructor
	CcbPetBagLayer()
	{
		m_pLayerBg = NULL;
		m_pControlButtonSort = NULL;
		m_pLabelTTFCurCount = NULL;
		m_pLabelTTFMaxCount = NULL;
        m_pLayerPetBg = NULL;
        m_pLayerBack = NULL;
        m_pSpriteSort = NULL;
        m_pControlButtonExpandBag = NULL;
        
        m_sortLayer = NULL;
        m_pNode1 = NULL;
        
        m_curScene = NULL;
	}
	~CcbPetBagLayer();

	// must have
//	static cocos2d::CCScene* scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPetBagLayer, create);
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );

	// option
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    //tableView相关}
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    
    virtual void dwPetBagCntChanged(uint32 cnt);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerPetBg;
	cocos2d::extension::CCControlButton* m_pControlButtonSort;
	cocos2d::CCLabelTTF* m_pLabelTTFCurCount;
	cocos2d::CCLabelTTF* m_pLabelTTFMaxCount;
    cocos2d::CCLayer* m_pLayerBg;
    cocos2d::CCLayer* m_pLayerBack;
    cocos2d::CCSprite* m_pSpriteSort;
    cocos2d::extension::CCControlButton* m_pControlButtonExpandBag;
    cocos2d::extension::CCTableView *m_table;
    std::map<uint16, CcbPetIconCtrl*> m_mapPetIcon;
    std::vector<uint32> m_arrPetObjId;
    CcbSortLayer *m_sortLayer;
    CCRect m_clipRect;
    
    CCPoint m_scrollOff;
    bool bFlag;
    bool teamFlag;  //为true时，加移除队员按钮}
    bool emblemFlag; //为true时，加移除徽章按钮}
    
    CCSize winSzie;
    
    cocos2d::CCNode* m_pNode1;
    
    static CcbPetBagLayer* m_curScene;
private:
    void onRemoveMember(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event);
    void onRemoveEmblem(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent event);
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void RefeashLayer();
    
    
public:
	// Funcitons
    static CcbPetBagLayer* getCurScene(){return m_curScene;};

	void onPressControlButtonSort(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonExpandBag(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
//	void onPressControlButtonLock(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    void loadPet();
//	void RefeashLayer();
    
    void initSortLayer();
    void sortPetBag(std::vector<uint32> arrPetObjId);
    
    void ReflashPetBagNum();

};

class CcbPetBagLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPetBagLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPetBagLayer);
};


#endif // __CCBPETBAGLAYER__H__