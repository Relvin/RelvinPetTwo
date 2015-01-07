/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-09-03 20:57:44
*/

#ifndef __TEXTCRITICALLAYER__H__
#define __TEXTCRITICALLAYER__H__

#include "cocos2d.h"
#include "cocos-ext.h"


class TextCriticalLayer:
	public cocos2d::CCLayer
{
public:
	// Constructor
	TextCriticalLayer()
	{

	}
	~TextCriticalLayer();

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TextCriticalLayer, create);

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
};

class TextCriticalLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TextCriticalLayerLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TextCriticalLayer);
};


#endif // __TEXTCRITICALLAYER__H__