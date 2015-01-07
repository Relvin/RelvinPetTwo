/**
* CcbPatchFrameLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-11-24 14:30:51
*/

#ifndef __CCBPATCHFRAMELAYER__H__
#define __CCBPATCHFRAMELAYER__H__

//CcbPatchFrameLayer.h come from ccb/CcbPatchFrameLayer.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"

class CcbItemIconLayer;
class CCScrollButton;
class CcbPatchFrameLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbPatchFrameLayer();
	
	~CcbPatchFrameLayer();

	// Create Method
//	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbPatchFrameLayer, create);
    static CcbPatchFrameLayer* createCCNode(cocos2d::CCNode *pParent, cocos2d::extension::CCBReader *pCCBReader);
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
	cocos2d::CCLabelTTF* m_pLabelTTFItemName;
	cocos2d::CCLabelTTF* m_pLabelTTFItemCount;
	CcbItemIconLayer* m_pLayerIcon;
	CCScrollButton* m_pControlButtonCompound;
	cocos2d::CCLabelTTF* m_pLabelTTFNotEnough;
    cocos2d::CCNode* m_pNodeNotEnough;


public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();


	
public:
	// Funcitons
	void onPressControlButtonCompound(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);
    void onPressControlButtonGoto(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event);

    //Self Functions
    CC_SYNTHESIZE(uint32, m_dwItemIndex, ItemShowIndex);
    void setAnimationManager(cocos2d::extension::CCBAnimationManager *animationMgr);
    void updateShowItemInfo();
    void setClipRect(cocos2d::CCRect rect);
private:
    cocos2d::extension::CCBAnimationManager *m_pAnimationmanager;

};

class CcbPatchFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbPatchFrameLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
//    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbPatchFrameLayer);
    virtual CcbPatchFrameLayer * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        return CcbPatchFrameLayer::createCCNode(pParent, pCCBReader);
    }
};


#endif // __CCBPATCHFRAMELAYER__H__