/**
* CcbStageEffLayer.h
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-09-28 18:15:13
*/

#ifndef __CCBSTAGEEFFLAYER__H__
#define __CCBSTAGEEFFLAYER__H__

//CcbStageEffLayer.h come from ccb/missionframelight.ccb

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbStageEffLayer:
	public cocos2d::CCLayer
{
public:
	// Constructor
	CcbStageEffLayer()
	{

	}
	~CcbStageEffLayer();

    CREATE_FUNC(CcbStageEffLayer);
    
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();

};

class CcbStageEffLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbStageEffLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbStageEffLayer);
};


#endif // __CCBSTAGEEFFLAYER__H__