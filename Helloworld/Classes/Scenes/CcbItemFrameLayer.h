/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-05-22 16:02:32
*/

#ifndef __CCBITEMFRAMELAYER__H__
#define __CCBITEMFRAMELAYER__H__

//CcbItemFrameLayer.h come from ccb/item_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SystemMessage.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CcbItemIconLayer;
class CCScrollButton;

class CcbItemFrameLayer:
	public CCLayer,
	public CCBMemberVariableAssigner
,	public CCBSelectorResolver
,	public CCNodeLoaderListener
,   public SystemMessageProtocol
{
public:
	// Constructor
	CcbItemFrameLayer()
	{
		m_pLabelTTFItemName = NULL;
		m_pLabelTTFItemDesc = NULL;
		m_pLabelTTFItemCount = NULL;
		m_pLayerIcon = NULL;
		m_pControlButtonUse = NULL;

	}
	~CcbItemFrameLayer();

	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbItemFrameLayer, create);
	// Inhert MemberVariableAssigner
	virtual bool onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode );
	virtual bool onAssignCCBCustomProperty( CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue );
	// Inhert CCBSelectorResolver
	virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_CCControlHandler onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName );
	virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName );
	// Inhert CCNodeLoaderListener
	virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
	
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    
    CCPoint m_StartTouchPos;
    CCPoint m_EndTouchPos;
private:
	int mCustomPropertyInt;
    float mCustomPropertyFloat;
    bool mCustomPropertyBoolean;
    std::string mCustomPropertyString;
    
public:
	// Attributes for CCB
	CCLabelTTF* m_pLabelTTFItemName;
	CCLabelTTF* m_pLabelTTFItemDesc;
	CCLabelTTF* m_pLabelTTFItemCount;
	CcbItemIconLayer* m_pLayerIcon;
	CCScrollButton* m_pControlButtonUse;

    CC_SYNTHESIZE(uint32, m_dwItemShowIndex, ItemShowIndex);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

    void CreateShowData();
	void setClipRect(CCRect rect);
    
private:
    bool checkBoxAndKey();
public:
	// Funcitons

	void onPressControlButtonUse(CCObject* pSender, CCControlEvent event);



};

class CcbItemFrameLayerLoader : public CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbItemFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbItemFrameLayer);
};


#endif // __CCBITEMFRAMELAYER__H__