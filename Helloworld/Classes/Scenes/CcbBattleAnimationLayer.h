/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2014-09-10 11:55:35
*/

#ifndef __CCBBATTLEANIMATIONLAYER__H__
#define __CCBBATTLEANIMATIONLAYER__H__

//CcbBattleAnimationLayer.h come from ccb/pet_battle_ctrl_ani.ccb

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbBattleAnimationLayer : public cocos2d::CCLayer
{
public:
	// Constructor
	CcbBattleAnimationLayer()
	{

	}
	~CcbBattleAnimationLayer();
    CREATE_FUNC(CcbBattleAnimationLayer);
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
};

class CcbBattleAnimationLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbBattleAnimationLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbBattleAnimationLayer);
};


#endif // __CCBBATTLEANIMATIONLAYER__H__