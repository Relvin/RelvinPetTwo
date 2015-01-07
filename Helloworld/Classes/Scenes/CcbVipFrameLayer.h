/**
 * CcbVipFrameLayer.h
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Relvin
 * Date: 2014-10-23 16:16:11
 */

#ifndef __VIP_FRAME__H__
#define __VIP_FRAME__H__

//CcbVipFrameLayer.h come from ccb/vip_frame.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbVipFrameLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbVipFrameLayer();
    
	~CcbVipFrameLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbVipFrameLayer, create);
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
	
private:
	// Attributes for CCB
	cocos2d::CCSprite* m_pSpritePermission;
	cocos2d::CCLabelTTF* m_pLabelTTFText;
	cocos2d::CCLabelTTF* m_pLabelTTFRecharge;

    
public:
	// Virtual Functions
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    
	
public:
	// Funcitons
    void setFrameInfoByIndex(int index);
    

    

};

class CcbVipFrameLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbVipFrameLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbVipFrameLayer);
};


#endif // __VIP_FRAME__H__