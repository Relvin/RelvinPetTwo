/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-16 18:36:10
*/

#ifndef __CCBLEFTARROW__H__
#define __CCBLEFTARROW__H__

#include "cocos2d.h"
#include "cocos-ext.h"


class CcbLeftArrow:
	public cocos2d::CCLayer
{
public:
	// Constructor
	CcbLeftArrow()
	{

	}
	~CcbLeftArrow();

	// must have
//	static cocos2d::CCScene* scene();
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbLeftArrow, create);

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

};

class CcbLeftArrowLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbLeftArrowLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbLeftArrow);
};


#endif // __CCBLEFTARROW__H__