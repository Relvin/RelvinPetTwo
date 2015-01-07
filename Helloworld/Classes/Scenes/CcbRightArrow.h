/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-10-16 18:36:20
*/

#ifndef __CCBRIGHTARROW__H__
#define __CCBRIGHTARROW__H__

#include "cocos2d.h"
#include "cocos-ext.h"

class CcbRightArrow:
	public cocos2d::CCLayer
{
public:
	// Constructor
	CcbRightArrow()
	{

	}
	~CcbRightArrow();

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CcbRightArrow, create);

public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
};

class CcbRightArrowLoader : public cocos2d::extension::CCLayerLoader {
public:
    // 用于创建一个自身的实例，保存为一个CCLayerLoader。}
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CcbRightArrowLoader, loader);
protected:
    // 用于创建一个类型为HelloCocosBuilderLayer的CCNode。}
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CcbRightArrow);
};


#endif // __CCBRIGHTARROW__H__