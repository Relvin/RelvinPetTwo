/**
* CcbDropTipFrameLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-09-20 17:31:17
*/

#ifndef __CCBDROPTIPFRAMELAYER__H__
#define __CCBDROPTIPFRAMELAYER__H__

//CcbDropTipFrameLayer.h come from ccb/petshow_droptip_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CCScrollButton;
class CcbDropTipFrameLayer:
	public cocos2d::CCLayer
,	public cocos2d::extension::CCBMemberVariableAssigner
,	public cocos2d::extension::CCBSelectorResolver
,	public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
	CcbDropTipFrameLayer()
	{
		m_pLabelTTFDropplace = NULL;
		m_pLabelTTFWeikaiqi = NULL;
		m_pControlButtonGo = NULL;
        m_pSpriteDropRate = NULL;
	}
	~CcbDropTipFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbDropTipFrameLayer, create);
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
	cocos2d::CCLabelTTF* m_pLabelTTFDropplace;
	cocos2d::CCLabelTTF* m_pLabelTTFWeikaiqi;
	CCScrollButton* m_pControlButtonGo;
    cocos2d::CCSprite *m_pSpriteDropRate;
    uint32 m_stageId;
    uint8 m_stageType;
    
    /*!request the map
     */
    void requestMap(int _kind);
    
    /*!set map type
     */
    void checkMapOpen(int _kind);
    
    void showBtn();
    void hideBtn();
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

public:
	// Funcitons
    void loadData(uint32 stageId, uint8 stageType, uint8 byDorpProb);
    void setClipRect(cocos2d::CCRect rect);
	void onPressControlButtonGo(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
};

class CcbDropTipFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbDropTipFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbDropTipFrameLayer);
};


#endif // __CCBDROPTIPFRAMELAYER__H__