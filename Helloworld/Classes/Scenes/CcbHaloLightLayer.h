/**
 * halo_light.h
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Relvin
 * Date: 2014-09-10 16:55:02
 */

#ifndef __HALO_LIGHT__H__
#define __HALO_LIGHT__H__

//CcbHaloLightLayer.h come from ccb/halo_light.ccb

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"


class CcbHaloLightLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCNodeLoaderListener
{
public:
	// Constructor
    CcbHaloLightLayer();
    
	~CcbHaloLightLayer();
    
	// Create Method
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbHaloLightLayer, create);
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
	cocos2d::CCLayer* m_pLayerbg;

    
public:
	// Virtual Functions
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
    
    
	
public:
	// Funcitons
    void setShowInfoByIndex(uint16 wIndex);

    

};

class CcbHaloLightLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbHaloLightLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbHaloLightLayer);
};


#endif // __HALO_LIGHT__H__