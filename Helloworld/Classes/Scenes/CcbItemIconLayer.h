/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-11-26 11:26:05
*/

#ifndef __CCBITEMICONLAYER__H__
#define __CCBITEMICONLAYER__H__

//CcbItemIconLayer.h come from ccb/item_icon.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCScrollButton.h"
#include "ItemDataMgr.h"
#include "Defines.h"
#include "CCScrollButton.h"
#include "EnumDefines.h"

USING_NS_CC;
USING_NS_CC_EXT;
class CcbItemIconLayer;
class ItemIconTouchDelegate
{
public:
    virtual void itemIconTouchedCallBack(CcbItemIconLayer* pItemIcon, uint32 dwItemId) = 0;
};

class CcbItemIconLayer:
	public cocos2d::CCLayerRGBA,
	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbItemIconLayer()
    : m_pDelegate(NULL)
    , m_pNodeStar(NULL)
    , m_bSetNameColor(false)
	{
		m_pSpriteIcon = NULL;
		m_pLabelTTFItemName = NULL;
		m_pLabelTTFItemNum = NULL;
		m_pSpriteBg = NULL;
        m_pLabelTTFItemLv = NULL;
        m_pSpriteIconFrame = NULL;
        m_pLabelTTFItemEvoLv = NULL;
		m_pLabelTTFItemStarLv = NULL;
		m_pSpriteStar = NULL;
        m_btnShow = NULL;
        m_pSpriteAttribute = NULL;
        m_pSpriteNumBg = NULL;
        m_pSpriteChip = NULL;
	}
	~CcbItemIconLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemIconLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector( cocos2d::CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    CC_SYNTHESIZE(ItemIconTouchDelegate*, m_pDelegate, Delegate);

private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpriteIcon;
	cocos2d::CCLabelTTF* m_pLabelTTFItemName;
	cocos2d::CCLabelTTF* m_pLabelTTFItemNum;
    cocos2d::CCLabelTTF* m_pLabelTTFItemLv;
	cocos2d::CCSprite* m_pSpriteBg;
    cocos2d::CCSprite* m_pSpriteIconFrame;
    cocos2d::CCLabelTTF* m_pLabelTTFItemEvoLv;
	cocos2d::CCLabelTTF* m_pLabelTTFItemStarLv;
	cocos2d::CCSprite* m_pSpriteStar;
    cocos2d::CCSprite* m_pSpriteAttribute;
    cocos2d::CCSprite* m_pSpriteNumBg;
    CCScrollButton* m_btnShow;
    cocos2d::CCSprite* m_pSpriteChip; //碎片
    cocos2d::CCNode* m_pNodeStar;
    
    
    float m_NumBgW;
    //物品indexId}
    uint32 m_itemIndexId;
    //物品obj Id}
    uint32 m_itemObjId;
    //物品星级}
    uint8 m_byStar;
    //以obj id加载时，设置物品类型}
    E_UNITE_TYPE m_byType;
    
    //是否显示掉落信息}
    bool m_isShowDropInfo;
    
    bool m_bSetNameColor;
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    virtual void setTouchPriority(int priority);
    void onPressControlButtonSelect(CCObject* pSender, CCControlEvent event);
    
    //以obj Id 加载}
    void loadObjData(uint32 itemObjId, E_UNITE_TYPE byType);
    //以index Id加载}
    void loadIndexData(uint32 itemIndexId);
    
    //仅显示icon}
    void showIconOnly();
    //隐藏等级/强化等级}
    void hideLv();
    //显示等级/强化等级}
    void showLv(uint16 lv);
    //隐藏名字}
    void hideName();
    //显示名字}
    void showName();
    //隐藏数量}
    void hideCnt();
    //显示数量}
    void showCnt(uint32 cnt);
    void showCntFromTo(uint32 cntF, uint32 cntTo);
    //显示星级}
    void showStarLv(uint8 lv = 0);
    //隐藏星级}
    void hideStarLv();
    //显示阶级等级}
    void showEvoLv(uint16 lv);
    //隐藏进阶等级}
    void hideEvoLv();
    /*!
     * 设置数量文字的字号大小
     */
    void setCntFont(float fontSize);
    /*!
     * 设置名字的描边
     */
    void setNameStroke(ccColor3B color = ccBLACK);
    /*!
     * 取消名字的描边
     */
    void hideNameStroke();
    
    //设置是否显示掉落信息（目前仅用于精灵进阶材料）}
    void setIsShowDropInfo(bool isShow){m_isShowDropInfo = isShow;};
    
    //设置按钮可用性}
    void setBtnEnable(bool enable);
    //设置按钮触摸区域（相对于世界）}
    void setClipRect(CCRect rect);
    
    void setLabelNameColor(ccColor3B color);
    
    CCLabelTTF* getItemCntLabel();
    
public:

};

class CcbItemIconLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbItemIconLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbItemIconLayer);
};


#endif // __CCBITEMICONLAYER__H__