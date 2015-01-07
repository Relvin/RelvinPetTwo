/**
* Create by GenerateCppCodeFromCCBFile.lua
* All right received
* Author: Junie Chu
* Date: 2013-09-26 16:46:47
*/

#ifndef __STARTGAMESCENE__H__
#define __STARTGAMESCENE__H__

#include "cocos2d.h"
#include "cocos-ext.h"

class StartGameScene:
	public cocos2d::CCLayer
{
public:
	// Constructor
	StartGameScene()
	{

	}
	~StartGameScene();

	// must have
	static cocos2d::CCScene* scene();
	CREATE_FUNC(StartGameScene);

#pragma mark Public Method Declare
public:
	// Virtual Functions
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
};

#endif // __STARTGAMESCENE__H__