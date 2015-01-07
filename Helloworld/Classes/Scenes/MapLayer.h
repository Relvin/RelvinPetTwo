//
//  MapLayer.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-10-17.}
//
//

#ifndef __HelloWorld__MapLayer__
#define __HelloWorld__MapLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EffectLayer.h"
#include "Defines.h"

const static int Map_Circle = 4; //4个map轮回转，凑成一个圈，转动更新map背景图}

class MapLayer:
public cocos2d::CCLayerRGBA,
public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
,   public EffectLayerProtocol
{
public:
	// Constructor
	MapLayer()
	{
		m_pControlButtonActivity = NULL;
        m_pControlButtonNormal = NULL;
        m_pSpriteBg = NULL;
		m_pSpriteMap1 = NULL;
		m_pSpriteMap2 = NULL;
		m_pSpriteMap3 = NULL;
        m_pSpriteMap4 = NULL;
        m_pControlButtonBack = NULL;
        m_pLayerActivity = NULL;
        wMapId = 0;
        wStageId = 0;
        m_pLabelTTFDiffcult = NULL;
        m_pNodeMap1 = NULL;
        m_pNodeMap2 = NULL;
        m_pNodeMap3 = NULL;
        m_pNodeMap4 = NULL;
        
        m_pMapPoint1 = NULL;
        m_pMapPoint2 = NULL;
	}
	~MapLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MapLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
    // EffectLayerProtocol
    virtual void onActionOver();
    
    void kalilil();
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::extension::CCControlButton* m_pControlButtonActivity;
    cocos2d::extension::CCControlButton* m_pControlButtonNormal;
	cocos2d::CCSprite* m_pSpriteMap1;
	cocos2d::CCSprite* m_pSpriteMap2;
	cocos2d::CCSprite* m_pSpriteMap3;
    cocos2d::CCSprite* m_pSpriteMap4;
    cocos2d::CCSprite* m_pSpriteBg;
    cocos2d::extension::CCControlButton* m_pControlButtonBack;
    cocos2d::CCLayer* m_pLayerActivity;
    cocos2d::CCLabelTTF* m_pLabelTTFDiffcult;
    cocos2d::CCNode* m_pNodeMap1;
    cocos2d::CCNode* m_pNodeMap2;
    cocos2d::CCNode* m_pNodeMap3;
    cocos2d::CCNode* m_pNodeMap4;
    
    cocos2d::CCSprite* m_pMaps[Map_Circle];
    cocos2d::CCNode* m_pNodeMaps[Map_Circle];
    cocos2d::CCPoint m_pointStart;
    cocos2d::CCSize winSize;

    /*!
     0 -- 默认}
     1 -- 开启第二章大地图
     2 -- 开启第三章大地图
     3 -- ...
     */
    char mapFirstIdx[64];       // 新的大地图第一次开启，跳转到新大地图}
    
    uint16 wMapId;      // pass map id sended from server
    uint16 wStageId;    // pass stage id sended from server
    
    float m_fMapRotation[Map_Circle];
    
    int m_nViewIdx; // 当前Area扇形地图的Idx}
    int m_nAreaIdx; // 当前选中的Area Id，数据层Idx}
    bool bIsMoveLeft; // 是否往左移}
    bool bCanMoveLeft, bCanMoveRight;   // 是否到达边界，能否往左右移}
    bool bCanTouch;     // 执行action中无法进行touch事件}
    bool bFromBegin;    // 是否从TouchBegin开始的？我告诉你这里是有必要做这个判断的，滑动一直停在边界的时候会有不从begin开始的move}
    bool bMoved;        // 是否移动了}
    
    cocos2d::CCPoint m_pNewPoint;   // 新的地图点的位置}

    cocos2d::CCNode* m_pMapPoint1;  // 第一个地图点
    cocos2d::CCNode* m_pMapPoint2;  // 第二个地图点
    EffectLayer* m_pEffect;
    int m_nVecIdx;
private:
    void updateRotationWithDistance(float distance);
    void adjustMapPosition(float distance);
    
    void addMapPointsToArea(int nDataIdx, int nViewIdx);  // 将地图点加入到Area中，第一个参数为第几个Area数据，第二个参数为第几个Area图层来加载该Area内的地图点信息。}
    void upLeftRightStatus();       // 更新左右是否可以移动的状态}
    void mapRunAction(float offset);
    void setControlTouchEnable();
    int getCycleSpriteIdx(int curIdx);  // AreaId，即ViewIdx的轮循指针}
    void placeMapPoint();       // 初始化时候放置三个Area上的map点}
    
    void addGuideLayer();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	
public:
	// Funcitons
	void onPressControlButtonBack(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
	void onPressControlButtonActivity(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonStage(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent controlEvent);
    
    virtual void setOpacity(GLubyte opacity);
};

class MapLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MapLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MapLayer);
};


#endif /* defined(__HelloWorld__MapLayer__) */
