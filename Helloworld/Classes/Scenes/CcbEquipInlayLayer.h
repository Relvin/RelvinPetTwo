/**
* equip_inlay.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Relvin
* Date: 2014-10-29 12:21:54
*/

#ifndef __EQUIP_INLAY__H__
#define __EQUIP_INLAY__H__

//equip_inlay.h come from ccb/equip_inlay.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include <vector>
#include "CcbItemIconLayer.h"
#include "GameSession.h"
#include "SystemMessageProtocol.h"


class CcbEquipInlayLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
, public ItemIconTouchDelegate
, public SystemMessageProtocol
, public CObserverMsg
{
public:
    struct SHOW_RUNE_INFO
    {
        uint32 dwKeyID;
        int sort;
        
        bool operator < (const SHOW_RUNE_INFO &info) const
        {
            return sort < info.sort;
        }
    };
    
	// Constructor
    CcbEquipInlayLayer();
	~CcbEquipInlayLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbEquipInlayLayer, create);
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
	// Attributes for CCB
	cocos2d::CCLabelTTF* m_pLabelTTFEquipName;
	cocos2d::CCSprite* m_pSpriteEquipIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFProText_2;
	cocos2d::CCLabelTTF* m_pLabelTTFPro_2;
	cocos2d::CCLabelTTF* m_pLabelTTFProText_1;
	cocos2d::CCLabelTTF* m_pLabelTTFPro_1;
	cocos2d::CCLabelTTF* m_pLabelTTFRuneName2;
	cocos2d::CCLabelTTF* m_pLabelTTFRuneAttr2;
	cocos2d::CCSprite* m_pSpriteRuneIcon2;
	cocos2d::CCSprite* m_pSpriteLock;
	cocos2d::extension::CCControlButton* m_pControlButtonRuneIcon2;
	cocos2d::CCLabelTTF* m_pLabelTTFRuneAttr1;
	cocos2d::CCLabelTTF* m_pLabelTTFRuneName1;
	cocos2d::CCSprite* m_pSpriteRuneIcon1;
	cocos2d::extension::CCControlButton* m_pControlButtonRuneIcon1;
	cocos2d::CCSprite* m_pSpriteStarlv;
	cocos2d::CCLayer* m_pLayerEquipBg;
	cocos2d::CCSprite* m_pSpriteShowNothing;
	cocos2d::CCLabelTTF* m_pLabelTTFNeedNum;
	cocos2d::extension::CCControlButton* m_pControlButtonYiji;
	cocos2d::extension::CCControlButton* m_pControlButtonShop;
	cocos2d::CCLayer* m_pLayerRuneListParent;
    cocos2d::extension::CCControlButton* m_pControlButtonEquip;
    cocos2d::CCNode* m_pNodeEquip;
    cocos2d::CCNode* m_pNodeNothingtips;
    cocos2d::CCLabelTTF* m_pLabelRuneName1;
    cocos2d::CCLabelTTF* m_pLabelRuneName2;

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    //Self Functions
    void loadLayerDataInfo();
    void createShowList();
    void createLayerData();
    void RefeashLayer();
    bool NotifyErrorMsg(uint16 wErrorNo);
    
    // systemMessage Function
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    
    // Inhert CCTableView
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx) ;
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) ;
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table) ;
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    virtual void itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId);
public:
	// Funcitons
	void onPressControlButtonRuneIcon2(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRuneIcon1(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonYiji(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonShop(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonEquip(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    
    void showEquipInfoChanged();

private:
    cocos2d::extension::CCTableView *m_pTableView;
    cocos2d::CCRect m_clipRect;
    std::vector<SHOW_RUNE_INFO> m_vecRuneList;
    uint32 m_dwRuneID1;
    uint32 m_dwRuneID2;
};

class CcbEquipInlayLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbEquipInlayLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbEquipInlayLayer);
};


#endif // __EQUIP_INLAY__H__