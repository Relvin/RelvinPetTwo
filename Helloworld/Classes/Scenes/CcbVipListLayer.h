/**
 * CcbVipListLayer.h
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Relvin
 * Date: 2014-10-23 16:16:30
 */

#ifndef __VIP_LIST__H__
#define __VIP_LIST__H__

//CcbVipListLayer.h come from ccb/vip_list.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbVipListLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate
{
public:
	// Constructor
    CcbVipListLayer();
    
	~CcbVipListLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbVipListLayer, create);
    virtual bool init();
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    // Inhert CCTableView
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx) ;
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx) ;
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table) ;
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
	
    //Touch Functions
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    virtual void setVisible(bool visible);
private:
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteTitle;
	cocos2d::CCNode* m_pNodeTable;
	cocos2d::extension::CCControlButton* m_pControlButtonLeft;
	cocos2d::extension::CCControlButton* m_pControlButtonRight;

    
public:
	// Virtual Functions
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    void updateTableViewPos(int moveDir);
    void setTitleShowInfo(int index );
public:
	// Funcitons
    void onPressControlButtonLeft(CCObject* pObject, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonRight(CCObject* pObject, cocos2d::extension::CCControlEvent event);
    
private:
    cocos2d::extension::CCTableView* m_pTableView;
    cocos2d::CCPoint m_TouchBeginPos;
    int m_nCurPage;
    int m_nTotalPage;
    bool m_bTouchMoved;
    

};

class CcbVipListLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbVipListLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbVipListLayer);
};


#endif // __VIP_LIST__H__