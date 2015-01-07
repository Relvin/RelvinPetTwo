/**
* CcbGachaBoardLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-19 13:38:42
*/

#ifndef __CCBGACHABOARDLAYER__H__
#define __CCBGACHABOARDLAYER__H__

//CcbGachaBoardLayer.h come from ccb/CcbGachaBoardLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbGachaBoardLayer:
	public cocos2d::CCLayer,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbGachaBoardLayer()
	{
		m_pLayerPetScroll = NULL;
		m_pLabelBMFontTitle = NULL;
		m_pControlButtonClose = NULL;
		m_pControlButtonPreview = NULL;
		m_pControlButtonLeft = NULL;
		m_pControlButtonRight = NULL;
		m_pControlButtonTicket = NULL;
		m_pSpriteTicket = NULL;
		m_pLabelTTFTicket = NULL;
		m_pLabelTTFTicketDes = NULL;
		m_pNodeType1 = NULL;
		m_pLabelTTFTicketFreeTimes = NULL;
		m_pNodeType2 = NULL;
		m_pNodeTicket = NULL;
		m_pControlButtonOne = NULL;
		m_pControlButtonTen = NULL;
		m_pSpriteText_ChaoZhi = NULL;
		m_pLabelTTFOneDollar = NULL;
		m_pLabelTTFTenDollar = NULL;
		m_pLabelBMFontLeftCnt = NULL;
		m_pNodeDiamond = NULL;
		m_pSpriteLvStar = NULL;
        m_pLabelTTFTime = NULL;
        m_pSpriteTextLastGet = NULL;
        mAnimationManager = NULL;

        
        m_petPaintPer = NULL;
        m_petPaintCur = NULL;
        m_petPaintNext = NULL;
        m_bCanTouchBtn = false;
	}
	~CcbGachaBoardLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbGachaBoardLayer, create);
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
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    virtual void registerWithTouchDispatcher(void);
    virtual void visit(void);
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCLayer* m_pLayerPetScroll;
	cocos2d::CCLabelBMFont* m_pLabelBMFontTitle;
	cocos2d::extension::CCControlButton* m_pControlButtonClose;
	cocos2d::extension::CCControlButton* m_pControlButtonPreview;
	cocos2d::extension::CCControlButton* m_pControlButtonLeft;
	cocos2d::extension::CCControlButton* m_pControlButtonRight;
	cocos2d::extension::CCControlButton* m_pControlButtonTicket;
	cocos2d::CCSprite* m_pSpriteTicket;
	cocos2d::CCLabelTTF* m_pLabelTTFTicket;
	cocos2d::CCLabelTTF* m_pLabelTTFTicketDes;
	cocos2d::CCNode* m_pNodeType1;
	cocos2d::CCLabelTTF* m_pLabelTTFTicketFreeTimes;
	cocos2d::CCNode* m_pNodeType2;
	cocos2d::CCNode* m_pNodeTicket;
	cocos2d::extension::CCControlButton* m_pControlButtonOne;
	cocos2d::extension::CCControlButton* m_pControlButtonTen;
	cocos2d::CCSprite* m_pSpriteText_ChaoZhi;
	cocos2d::CCLabelTTF* m_pLabelTTFOneDollar;
	cocos2d::CCLabelTTF* m_pLabelTTFTenDollar;
	cocos2d::CCLabelBMFont* m_pLabelBMFontLeftCnt;
	cocos2d::CCNode* m_pNodeDiamond;
	cocos2d::CCSprite* m_pSpriteLvStar;
    cocos2d::CCLabelTTF* m_pLabelTTFTime;
    cocos2d::CCSprite* m_pSpriteTextLastGet;
    cocos2d::extension::CCBAnimationManager *mAnimationManager;
    
    int m_nTicketCnt;
    int m_dwLeftTime;
    int m_dwFreeLeftTime;
    
    int m_curMoveTime;
    int m_stopTime;
    bool m_moveFlag;
    float m_fMoveX;
    
    cocos2d::CCPoint m_tTouchPoint;
    float m_fTouchLength;
    float m_fTouchHeight;
    
    cocos2d::CCRect m_layerRect;
    
    cocos2d::CCSprite* m_petPaintPer;
    cocos2d::CCSprite* m_petPaintCur;
    cocos2d::CCSprite* m_petPaintNext;
    
    cocos2d::CCSprite* arrPetPaint[3];
    
    cocos2d::CCSize winSize;
    float m_fPerX;
    float m_fNextX;
    float m_fCurX;
    
    uint8 m_byType;
    uint32 m_curPage;
    std::vector<uint16> arrCurShowPet;
    
    void addGuideLayer();
    bool m_bCanTouchBtn;
    void restoreTouch();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

private:
    void loadPet();
    void updateTime(float cTime);
    void updateForMove(float cTime);
    void changePage(int off);
    void setPetStar();
    void openTouch(CCObject* node);
    void afterAnimationFinishedCallBack();
public:
	// Funcitons
    void loadData();
    
    void setCDTime(uint32 dwLeftTime, uint32 dwFreeLeftTime);
    
    void onShow();
    
	void onPressControlButtonClose(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonPreview(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonLeft(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonRight(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTicket(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonOne(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonTen(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);



};

class CcbGachaBoardLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbGachaBoardLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbGachaBoardLayer);
};


#endif // __CCBGACHABOARDLAYER__H__