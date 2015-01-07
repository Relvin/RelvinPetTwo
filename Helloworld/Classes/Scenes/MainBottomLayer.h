/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-08-29 15:58:34
*/

#ifndef __MAINBOTTOMLAYER__H__
#define __MAINBOTTOMLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"

class MainBottomLayer:
	public cocos2d::CCLayer
{
public:
	// Constructor
	MainBottomLayer()
	{
	}
	~MainBottomLayer();

    CREATE_FUNC(MainBottomLayer);

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();

};

class MainBottomLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainBottomLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainBottomLayer);
};


#endif // __MAINBOTTOMLAYER__H__